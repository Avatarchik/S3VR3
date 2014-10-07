#include "MainWindow.h"
#include "TutorialCustomShading.h"

#include <QDateTime>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTextStream>

#include <metaioSDK/IMetaioSDKWin32.h>


// Set to 0 to enable auto-save-and-apply of shaders (allows faster testing of shaders)
#define MANUAL_SAVE_AND_APPLY_SHADERS 0


const char* const SHADER_MATERIALS_FILENAME = "../../../tutorialContent_crossplatform/TutorialCustomShading/Assets/shader_materials.xml";
const char* const VERTEX_SHADER_FILENAME = "../../../tutorialContent_crossplatform/TutorialCustomShading/Assets/vert.glsl";
const char* const FRAGMENT_SHADER_FILENAME = "../../../tutorialContent_crossplatform/TutorialCustomShading/Assets/frag.glsl";


static QString readFileToQString(const char* filename)
{
	QFile f(filename);

	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qCritical("Failed to read file %s", filename);
		return "";
	}

	QTextStream stream(&f);
	QString ret = stream.readAll();
	f.close();

	return ret;
}


static bool writeQStringToFile(const QString& content, const char* filename)
{
	QFile f(filename);

	if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qCritical("Failed to open file %s for writing", filename);
		return false;
	}

	QTextStream stream(&f);
	stream << content;
	f.close();
	return true;
}


TutorialCustomShading::TutorialCustomShading(MainWindow* mainWindow) :
	m_pMainWindow(mainWindow),
	m_pShaderErrorLabel(0),
	m_pVertexShaderEdit(0),
	m_pFragmentShaderEdit(0),
	m_pApplyShadersButton(0),
	m_pModel(0)
{
}


TutorialCustomShading::~TutorialCustomShading()
{
	if ((m_pVertexShaderEdit->toPlainText() != readFileToQString(VERTEX_SHADER_FILENAME) ||
		m_pFragmentShaderEdit->toPlainText() != readFileToQString(FRAGMENT_SHADER_FILENAME)) &&
		QMessageBox::question(
			m_pMainWindow,
			"Save shaders?",
			"Do you want to save changes to the shader files that were not applied yet?",
			QMessageBox::Save,
			QMessageBox::Discard) == QMessageBox::Save)
	{
		saveShaders();
	}

	if(m_pShaderErrorLabel)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pShaderErrorLabel);
		delete m_pShaderErrorLabel;
	}

	if(m_pVertexShaderEdit)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pVertexShaderEdit);
		delete m_pVertexShaderEdit;
	}

	if(m_pFragmentShaderEdit)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pFragmentShaderEdit);
		delete m_pFragmentShaderEdit;
	}

	if(m_pApplyShadersButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pApplyShadersButton);
		delete m_pApplyShadersButton;
	}
}


void TutorialCustomShading::addGUI()
{
	m_pMainWindow->showMaximized();

	QBoxLayout* layout = m_pMainWindow->getButtonBar();

	QFont fixedWidthFont("", 9); // 9pt font size
	fixedWidthFont.setStyleHint(QFont::Courier, QFont::PreferQuality);

	// Add buttons to switch between models
	m_pVertexShaderEdit = new QTextEdit();
	m_pVertexShaderEdit->setTabStopWidth(20);
	m_pVertexShaderEdit->setMinimumWidth(500);
	m_pVertexShaderEdit->setMinimumHeight(350);
	m_pVertexShaderEdit->setCurrentFont(fixedWidthFont);
	m_pVertexShaderEdit->setAcceptRichText(false);
	layout->addWidget(m_pVertexShaderEdit);

	m_pFragmentShaderEdit = new QTextEdit();
	m_pFragmentShaderEdit->setTabStopWidth(20);
	m_pFragmentShaderEdit->setMinimumWidth(500);
	m_pFragmentShaderEdit->setMinimumHeight(350);
	m_pFragmentShaderEdit->setCurrentFont(fixedWidthFont);
	m_pFragmentShaderEdit->setAcceptRichText(false);
	layout->addWidget(m_pFragmentShaderEdit);

	m_pShaderErrorLabel = new QLabel();
	layout->addWidget(m_pShaderErrorLabel);

	// Set to 0 to enable auto-save-and-apply of shaders
#if MANUAL_SAVE_AND_APPLY_SHADERS
	m_pApplyShadersButton = new QPushButton("Save to shader files && apply");
	layout->addWidget(m_pApplyShadersButton);
	QObject::connect(m_pApplyShadersButton, SIGNAL(clicked()), this, SLOT(onApplyShadersButtonClicked()));
#endif
}


void TutorialCustomShading::loadContent()
{
	addGUI();

	if(!m_pMetaioSDK->setTrackingConfiguration("../../../tutorialContent_crossplatform/TutorialCustomShading/Assets/TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");

	m_pModel = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialCustomShading/Assets/metaioman.md2");

	if (m_pModel)
	{
		// Register our own callback so that we can set custom shader uniforms. This can be done per
		// geometry, and the "extra" parameter in the onSetShaderMaterialConstants method can be
		// used to determine which geometry is being rendered (in this case we only have one).
		m_pModel->setShaderMaterialOnSetConstantsCallback(this);

		m_pModel->startAnimation("idle", true);

		// Make him look away from the pattern
		m_pModel->setScale(2);
		m_pModel->setRotation(metaio::Rotation(-(float)M_PI/2.0f, 0, 0));
		m_pModel->setTranslation(metaio::Vector3d(0, -100, 50));
	}
	else
		qCritical("Failed to load model");

	// Set initial shaders
	m_pVertexShaderEdit->setPlainText(readFileToQString(VERTEX_SHADER_FILENAME));
	m_pFragmentShaderEdit->setPlainText(readFileToQString(FRAGMENT_SHADER_FILENAME));

	// Apply shaders immediately
	onApplyShadersButtonClicked();

#if !MANUAL_SAVE_AND_APPLY_SHADERS
	connect(m_pVertexShaderEdit, SIGNAL(textChanged()), this, SLOT(onApplyShadersButtonClicked()));
	connect(m_pFragmentShaderEdit, SIGNAL(textChanged()), this, SLOT(onApplyShadersButtonClicked()));
#endif
}


void TutorialCustomShading::onApplyShadersButtonClicked()
{
	if (saveShaders() && m_pMetaioSDK->loadShaderMaterials(SHADER_MATERIALS_FILENAME))
	{
		m_pShaderErrorLabel->setText("SUCCESS");
		m_pShaderErrorLabel->setStyleSheet("color: green; font-weight: bold");

		m_pModel->setShaderMaterial("tutorial_customshading");
		m_pModel->setVisible(true);
	}
	else
	{
		m_pShaderErrorLabel->setText("ERROR");
		m_pShaderErrorLabel->setStyleSheet("color: red; font-weight: bold");

		qCritical("Shader material loading failed (see above errors), will hide metaio man");
		m_pModel->setVisible(false);
	}
}


void TutorialCustomShading::onSetShaderMaterialConstants(const metaio::stlcompat::String& shaderMaterialName, void* extra,
	metaio::IShaderMaterialSetConstantsService* constantsService)
{
	// This will be identical to m_pModel since we only assigned this callback to that single geometry:
	// metaio::IGeometry* geometry = static_cast<metaio::IGeometry*>(extra);

	// We just pass the positive sinus (range [0;1]) of absolute time in seconds so that we can
	// use it to fade our effect in and out.
	float time[1] = { 0.5f * (1.0f + (float)sin(QDateTime::currentMSecsSinceEpoch() / 1000.0)) };
	constantsService->setShaderUniformF("myValue", time, 1);
}


bool TutorialCustomShading::saveShaders()
{
	bool res = true;
	res = res && writeQStringToFile(m_pVertexShaderEdit->toPlainText(), VERTEX_SHADER_FILENAME);
	res = res && writeQStringToFile(m_pFragmentShaderEdit->toPlainText(), FRAGMENT_SHADER_FILENAME);
	return res;
}