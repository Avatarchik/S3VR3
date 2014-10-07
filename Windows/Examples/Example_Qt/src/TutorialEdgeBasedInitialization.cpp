#include "MainWindow.h"
#include "TutorialEdgeBasedInitialization.h"

#include <QMessageBox>
#include <QPushButton>
#include <QGraphicsSceneEvent>

#include <metaioSDK/GestureHandler.h>
#include <metaioSDK/IMetaioSDKWin32.h>

#define PATH2CONTENT std::string("../../../tutorialContent_crossplatform/TutorialEdgeBasedInitialization/Assets/")

TutorialEdgeBasedInitialization::TutorialEdgeBasedInitialization(MainWindow* mainWindow) :
	m_pMainWindow(mainWindow),
	m_state(STATE_INITIALIZATION),
	m_pResetButton(0)
{
	QBoxLayout* layout = m_pMainWindow->getButtonBar();

	// Add buttons to switch between models and configurations
	m_pResetButton = new QPushButton("Reset");
	layout->addWidget(m_pResetButton);
	QObject::connect(m_pResetButton , SIGNAL(clicked()), this, SLOT(onResetButtonClicked()));
}

TutorialEdgeBasedInitialization::~TutorialEdgeBasedInitialization()
{
	if(m_pResetButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pResetButton);
		delete m_pResetButton;
		m_pResetButton = 0;
	}
}

void TutorialEdgeBasedInitialization::loadContent()
{
	m_pMetaioSDK->registerCallback(this);

	m_pModel = m_pMetaioSDK->createGeometry(PATH2CONTENT + "Custom/rim.obj");
	if(!m_pModel)
	{
		qCritical("Failed to load model");
		return;
	} else {
		m_pModel->setCoordinateSystemID(1);
	}
	
	m_pVizAidModel = m_pMetaioSDK->createGeometry(PATH2CONTENT + "Custom/VizAid.obj");
	if(!m_pVizAidModel)
	{
		qCritical("Failed to load visualization-aid model");
		return;
	} else {
		m_pVizAidModel->setCoordinateSystemID(2);
	}
	
	m_pMetaioSDK->loadEnvironmentMap(PATH2CONTENT + "Custom/env_map.zip");

	loadTrackingConfig();
}


void TutorialEdgeBasedInitialization::onResetButtonClicked()
{
	loadTrackingConfig();
}

void TutorialEdgeBasedInitialization::onDrawFrame()
{
	TutorialBase::onDrawFrame();
}


void TutorialEdgeBasedInitialization::onTrackingEvent(const metaio::stlcompat::Vector<metaio::TrackingValues>& trackingValues)
{
	if (trackingValues.size() > 0 && 
		trackingValues[0].state == metaio::ETS_REGISTERED)
	{
		m_state = STATE_TRACKING;
	}
}


void TutorialEdgeBasedInitialization::loadTrackingConfig()
{
	bool result = m_pMetaioSDK->setTrackingConfiguration(PATH2CONTENT + "Custom/rim_tracking/Tracking.xml");

	if(!result)
	{
		qCritical("Failed to load tracking configuration.");
		return;
	}

	m_state = STATE_INITIALIZATION;
}

