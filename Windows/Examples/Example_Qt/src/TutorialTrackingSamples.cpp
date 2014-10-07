#include "MainWindow.h"
#include "TutorialTrackingSamples.h"

#include <QPushButton>

#include <metaioSDK/GestureHandler.h>
#include <metaioSDK/Rotation.h>
#include <metaioSDK/IMetaioSDKWin32.h>

TutorialTrackingSamples::TutorialTrackingSamples(MainWindow* mainWindow) :
	m_pMainWindow(mainWindow),
	m_pIdMarkerButton(0),
	m_pPictureMarkerButton(0),
	m_pMarkerlessButton(0),
	m_pMetaioMan(0)
{
}


TutorialTrackingSamples::~TutorialTrackingSamples()
{
	if(m_pIdMarkerButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pIdMarkerButton);
		delete m_pIdMarkerButton;
		m_pIdMarkerButton = 0;
	}

	if(m_pPictureMarkerButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pPictureMarkerButton);
		delete m_pPictureMarkerButton;
		m_pPictureMarkerButton = 0;
	}

	if(m_pMarkerlessButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pMarkerlessButton);
		delete m_pMarkerlessButton;
		m_pMarkerlessButton = 0;
	}
}


void TutorialTrackingSamples::addButtons()
{
	QBoxLayout* layout = m_pMainWindow->getButtonBar();

	// Add buttons to switch between models
	m_pIdMarkerButton = new QPushButton("ID marker");
	layout->addWidget(m_pIdMarkerButton);
	QObject::connect(m_pIdMarkerButton , SIGNAL(clicked()), this, SLOT(onIdMarkerButtonClicked()));

	m_pPictureMarkerButton = new QPushButton("Picture");
	layout->addWidget(m_pPictureMarkerButton);
	QObject::connect(m_pPictureMarkerButton, SIGNAL(clicked()), this, SLOT(onPictureMarkerButtonClicked()));

	m_pMarkerlessButton = new QPushButton("Markerless");
	layout->addWidget(m_pMarkerlessButton);
	QObject::connect(m_pMarkerlessButton, SIGNAL(clicked()), this, SLOT(onMarkerlessButtonClicked()));
}


void TutorialTrackingSamples::loadContent()
{
	// We want to handle the onTrackingEvent event to pause/resume the movie texture while not tracking
	m_pMetaioSDK->registerCallback(this);

	addButtons();

	if(!m_pMetaioSDK->setTrackingConfiguration("../../../tutorialContent_crossplatform/TutorialTrackingSamples/Assets/TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");

	m_pMetaioMan = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialTrackingSamples/Assets/metaioman.md2");
	if(m_pMetaioMan)
		m_pMetaioMan->setScale(metaio::Vector3d(4.0, 4.0, 4.0));
	else
		qCritical("Failed to load metaio man model");

	// Do not set an active tracking configuration yet, only when button is pressed
}


void TutorialTrackingSamples::onIdMarkerButtonClicked()
{
	setActiveTrackingConfig(0);
}


void TutorialTrackingSamples::onPictureMarkerButtonClicked()
{
	setActiveTrackingConfig(1);
}


void TutorialTrackingSamples::onMarkerlessButtonClicked()
{
	setActiveTrackingConfig(2);
}


void TutorialTrackingSamples::setActiveTrackingConfig(int index)
{
	std::string trackingConfigFile;

	switch(index)
	{
		case 0:
			trackingConfigFile = "../../../tutorialContent_crossplatform/TutorialTrackingSamples/Assets/TrackingData_Marker.xml";
			break;

		case 1:
			trackingConfigFile = "../../../tutorialContent_crossplatform/TutorialTrackingSamples/Assets/TrackingData_PictureMarker.xml";
			break;

		case 2:
			trackingConfigFile = "../../../tutorialContent_crossplatform/TutorialTrackingSamples/Assets/TrackingData_MarkerlessFast.xml";
			break;

		default:
			qCritical("Invalid tracking configuration index");
			return;
	}

	if(!m_pMetaioSDK->setTrackingConfiguration(trackingConfigFile))
		qCritical("Failed to load tracking configuration (picture marker)");
}

void TutorialTrackingSamples::onTrackingEvent(const metaio::stlcompat::Vector<metaio::TrackingValues>& trackingValues)
{
	// if we detect any target, we bind the loaded geometry to this target
	if( !trackingValues.empty() && m_pMetaioMan)
	{
		m_pMetaioMan->setCoordinateSystemID( trackingValues[0].coordinateSystemID );
	}
}
