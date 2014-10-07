#include "MainWindow.h"
#include "TutorialDynamicLighting.h"

#include <QDateTime>
#include <QPushButton>

#include <metaioSDK/IMetaioSDKWin32.h>


TutorialDynamicLighting::TutorialDynamicLighting(MainWindow* mainWindow) :
	m_pMainWindow(mainWindow),
	m_pDirectionalLightButton(0),
	m_pPointLightButton(0),
	m_pSpotLightButton(0),
	m_pDirectionalLight(0),
	m_pPointLight(0),
	m_pSpotLight(0),
	m_pDirectionalLightGeo(0),
	m_pPointLightGeo(0),
	m_pSpotLightGeo(0),
	m_pModel(0)
{
}


TutorialDynamicLighting::~TutorialDynamicLighting()
{
	QPushButton* buttons[] = { m_pDirectionalLightButton, m_pPointLightButton, m_pSpotLightButton };

	for (int i = 0; i < 3; ++i)
		if (buttons[i])
		{
			m_pMainWindow->getButtonBar()->removeWidget(buttons[i]);
			delete buttons[i];
		}
}


void TutorialDynamicLighting::addGUI()
{
	QBoxLayout* layout = m_pMainWindow->getButtonBar();

	// Add buttons to toggle the three lights
	m_pDirectionalLightButton = new QPushButton("Directional (ON)");
	layout->addWidget(m_pDirectionalLightButton);
	QObject::connect(m_pDirectionalLightButton, SIGNAL(clicked()), this, SLOT(onDirectionalLightButtonClicked()));

	m_pPointLightButton = new QPushButton("Point (ON)");
	layout->addWidget(m_pPointLightButton);
	QObject::connect(m_pPointLightButton, SIGNAL(clicked()), this, SLOT(onPointLightButtonClicked()));

	m_pSpotLightButton = new QPushButton("Spot (ON)");
	layout->addWidget(m_pSpotLightButton);
	QObject::connect(m_pSpotLightButton, SIGNAL(clicked()), this, SLOT(onSpotLightButtonClicked()));
}


metaio::IGeometry* TutorialDynamicLighting::createLightGeometry()
{
	metaio::IGeometry* ret = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialDynamicLighting/Assets/sphere_10mm.obj");
	if (!ret)
		qCritical("Failed to load light geometry");
	return ret;
}


void TutorialDynamicLighting::drawBackground(QPainter* painter, const QRectF & rect)
{
	TutorialBase::drawBackground(painter, rect);

	// Lights circle around
	double time = QDateTime::currentMSecsSinceEpoch() / 1000.0;
	const metaio::Vector3d lightPos(200*(float)cos(time), 120*(float)sin(0.25*time), 200*(float)sin(time));

	const double FREQ2MUL = 0.4;
	const metaio::Vector3d lightPos2(
		150*(float)cos(FREQ2MUL*2.2*time) * (1 + 2+2*(float)sin(FREQ2MUL*0.6*time)),
		30*(float)sin(FREQ2MUL*0.35*time),
		150*(float)sin(FREQ2MUL*2.2*time));

	const metaio::Vector3d directionalLightDir((float)cos(1.2*time), (float)sin(0.25*time), (float)sin(0.8*time));


	// This will only apply in the upcoming frame:

	// Directional light
	m_pDirectionalLight->setDirection(directionalLightDir);
	updateLightIndicator(m_pDirectionalLightGeo, m_pDirectionalLight);

	// Point light
	m_pPointLight->setTranslation(lightPos);
	updateLightIndicator(m_pPointLightGeo, m_pPointLight);

	// Spot light
	m_pSpotLight->setTranslation(lightPos2);
	m_pSpotLight->setDirection(-lightPos2); // spot towards origin of COS
	updateLightIndicator(m_pSpotLightGeo, m_pSpotLight);
}


void TutorialDynamicLighting::loadContent()
{
	addGUI();

	if(!m_pMetaioSDK->setTrackingConfiguration("../../../tutorialContent_crossplatform/TutorialDynamicLighting/Assets/TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");

	m_pModel = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialDynamicLighting/Assets/cube_50mm.obj");

	if (!m_pModel)
		qCritical("Failed to load model");

	m_pMetaioSDK->setAmbientLight(metaio::Vector3d(0.05f));

	m_pDirectionalLight = m_pMetaioSDK->createLight();
	m_pDirectionalLight->setType(metaio::ELIGHT_TYPE_DIRECTIONAL);
	m_pDirectionalLight->setAmbientColor(metaio::Vector3d(0, 0.15f, 0)); // slightly green
	m_pDirectionalLight->setDiffuseColor(metaio::Vector3d(0.6f, 0.2f, 0)); // orange
	m_pDirectionalLight->setCoordinateSystemID(1);
	m_pDirectionalLightGeo = createLightGeometry();
	m_pDirectionalLightGeo->setCoordinateSystemID(m_pDirectionalLight->getCoordinateSystemID());
	m_pDirectionalLightGeo->setDynamicLightingEnabled(false);

	m_pPointLight = m_pMetaioSDK->createLight();
	m_pPointLight->setType(metaio::ELIGHT_TYPE_POINT);
	m_pPointLight->setAmbientColor(metaio::Vector3d(0, 0, 0.15f)); // slightly blue ambient
	m_pPointLight->setAttenuation(metaio::Vector3d(0, 0, 40));
	m_pPointLight->setDiffuseColor(metaio::Vector3d(0, 0.8f, 0.05f)); // green-ish
	m_pPointLight->setCoordinateSystemID(1);
	m_pPointLightGeo = createLightGeometry();
	m_pPointLightGeo->setCoordinateSystemID(m_pPointLight->getCoordinateSystemID());
	m_pPointLightGeo->setDynamicLightingEnabled(false);

	m_pSpotLight = m_pMetaioSDK->createLight();
	m_pSpotLight->setAmbientColor(metaio::Vector3d(0.17f, 0, 0)); // slightly red ambient
	m_pSpotLight->setType(metaio::ELIGHT_TYPE_SPOT);
	m_pSpotLight->setRadiusDegrees(10);
	m_pSpotLight->setDiffuseColor(metaio::Vector3d(1, 1, 0)); // yellow
	m_pSpotLight->setCoordinateSystemID(1);
	m_pSpotLightGeo = createLightGeometry();
	m_pSpotLightGeo->setCoordinateSystemID(m_pSpotLight->getCoordinateSystemID());
	m_pSpotLightGeo->setDynamicLightingEnabled(false);
}


void TutorialDynamicLighting::onDirectionalLightButtonClicked()
{
	m_pDirectionalLight->setEnabled(!m_pDirectionalLight->isEnabled());
	m_pDirectionalLightButton->setText(m_pDirectionalLight->isEnabled() ? "Directional (ON)" : "Directional (OFF)");
}


void TutorialDynamicLighting::onPointLightButtonClicked()
{
	m_pPointLight->setEnabled(!m_pPointLight->isEnabled());
	m_pPointLightButton->setText(m_pPointLight->isEnabled() ? "Point (ON)" : "Point (OFF)");
}


void TutorialDynamicLighting::onSpotLightButtonClicked()
{
	m_pSpotLight->setEnabled(!m_pSpotLight->isEnabled());
	m_pSpotLightButton->setText(m_pSpotLight->isEnabled() ? "Spot (ON)" : "Spot (OFF)");
}


void TutorialDynamicLighting::updateLightIndicator(metaio::IGeometry* indicatorGeo, metaio::ILight* light)
{
	indicatorGeo->setVisible(light->isEnabled());

	if (!light->isEnabled())
		return;

	if (light->getType() == metaio::ELIGHT_TYPE_DIRECTIONAL)
	{
		metaio::Vector3d dir = light->getDirection();
		dir /= dir.norm();

		// Indicate "source" of directional light (not really the source because it's infinite)
		indicatorGeo->setTranslation(metaio::Vector3d(-200.0f * dir.x, -200.0f * dir.y, -200.0f * dir.z));
	}
	else
		indicatorGeo->setTranslation(light->getTranslation());
}