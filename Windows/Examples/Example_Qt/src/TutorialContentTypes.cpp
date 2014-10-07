#include "MainWindow.h"
#include "TutorialContentTypes.h"

#include <math.h>
#include <QPushButton>

#include <metaioSDK/GestureHandler.h>
#include <metaioSDK/Rotation.h>
#include <metaioSDK/IMetaioSDKWin32.h>

TutorialContentTypes::TutorialContentTypes(MainWindow* mainWindow) :
	m_pMainWindow(mainWindow),
	m_pSelectMetaioManButton(0),
	m_pSelectImageButton(0),
	m_pSelectTruckButton(0),
	m_pSelectMovieButton(0),
	m_pImagePlane(0),
	m_pMetaioMan(0),
	m_pMoviePlane(0),
	m_pTruck(0),
	m_selectedModel(-1)
{
}


TutorialContentTypes::~TutorialContentTypes()
{
	if(m_pSelectMetaioManButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pSelectMetaioManButton);
		delete m_pSelectMetaioManButton;
		m_pSelectMetaioManButton = 0;
	}

	if(m_pSelectImageButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pSelectImageButton);
		delete m_pSelectImageButton;
		m_pSelectImageButton = 0;
	}

	if(m_pSelectTruckButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pSelectTruckButton);
		delete m_pSelectTruckButton;
		m_pSelectTruckButton = 0;
	}

	if(m_pSelectMovieButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pSelectMovieButton);
		delete m_pSelectMovieButton;
		m_pSelectMovieButton = 0;
	}
}


void TutorialContentTypes::addButtons()
{
	QBoxLayout* layout = m_pMainWindow->getButtonBar();

	// Add buttons to switch between models
	m_pSelectMetaioManButton = new QPushButton("Model");
	layout->addWidget(m_pSelectMetaioManButton);
	QObject::connect(m_pSelectMetaioManButton, SIGNAL(clicked()), this, SLOT(onMetaioManButtonClicked()));

	m_pSelectImageButton = new QPushButton("Image");
	layout->addWidget(m_pSelectImageButton);
	QObject::connect(m_pSelectImageButton, SIGNAL(clicked()), this, SLOT(onImageButtonClicked()));

	m_pSelectTruckButton = new QPushButton("Truck");
	layout->addWidget(m_pSelectTruckButton);
	QObject::connect(m_pSelectTruckButton, SIGNAL(clicked()), this, SLOT(onTruckButtonClicked()));

	m_pSelectMovieButton = new QPushButton("Movie");
	layout->addWidget(m_pSelectMovieButton);
	QObject::connect(m_pSelectMovieButton, SIGNAL(clicked()), this, SLOT(onMovieButtonClicked()));
}


void TutorialContentTypes::loadContent()
{
	// We want to handle the onTrackingEvent event to pause/resume the movie texture while not tracking
	m_pMetaioSDK->registerCallback(this);

	addButtons();

	if(!m_pMetaioSDK->setTrackingConfiguration("../../../tutorialContent_crossplatform/TutorialContentTypes/Assets/TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");

	// Load metaio man
	m_pMetaioMan = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialContentTypes/Assets/metaioman.md2");
	if (m_pMetaioMan)
		m_pMetaioMan->setScale(metaio::Vector3d(4.0, 4.0, 4.0));
	else
		qCritical("Failed to load metaio man model");

	// Load image frame
	m_pImagePlane = m_pMetaioSDK->createGeometryFromImage("../../../tutorialContent_crossplatform/TutorialContentTypes/Assets/frame.png");
	if (m_pImagePlane)
		m_pImagePlane->setScale(metaio::Vector3d(3.0, 3.0, 3.0));
	else
		qCritical("Failed to load image frame model");

	// Load movie plane (true for transparent video)
	m_pMoviePlane = m_pMetaioSDK->createGeometryFromMovie("../../../tutorialContent_crossplatform/TutorialContentTypes/Assets/demo_movie.3g2", true);
	if (m_pMoviePlane)
	{
		m_pMoviePlane->setScale(metaio::Vector3d(2.0, 2.0, 2.0));
		m_pMoviePlane->setRotation(metaio::Rotation(0.0f, 0.0f, (float)-M_PI_2));
	}
	else
		qCritical("Failed to load movie plane");

	// Load truck
	m_pTruck = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialContentTypes/Assets/truck/truck.obj");
	if (m_pTruck)
	{
		m_pTruck->setScale(metaio::Vector3d(2.0, 2.0, 2.0));
		m_pTruck->setRotation(metaio::Rotation((float)M_PI_2, 0, (float)M_PI));
	}
	else
		qCritical("Failed to load truck model");

	// Start by displaying metaio man (hide other models)
	setActiveModel(0);
}


void TutorialContentTypes::onImageButtonClicked()
{
	setActiveModel(1);
}


void TutorialContentTypes::onMetaioManButtonClicked()
{
	setActiveModel(0);
}


void TutorialContentTypes::onMovieButtonClicked()
{
	setActiveModel(3);
}


void TutorialContentTypes::onTrackingEvent(const metaio::stlcompat::Vector<metaio::TrackingValues>& trackingValues)
{
	// We only have one COS, so there can only ever be one TrackingValues structure passed.
	// Play movie if the movie button was selected and we're currently tracking.
	if (trackingValues.empty() || !trackingValues[0].isTrackingState())
	{
		if (m_pMoviePlane)
			m_pMoviePlane->pauseMovieTexture();
	}
	else
	{
		if (m_pMoviePlane && m_selectedModel == 3)
			m_pMoviePlane->startMovieTexture(true);
	}
}


void TutorialContentTypes::onTruckButtonClicked()
{
	setActiveModel(2);
}


void TutorialContentTypes::setActiveModel(int modelIndex)
{
	m_selectedModel = modelIndex;

	m_pMetaioMan->setVisible(modelIndex == 0);
	m_pImagePlane->setVisible(modelIndex == 1);
	m_pTruck->setVisible(modelIndex == 2);
	m_pMoviePlane->setVisible(modelIndex == 3);

	if (m_selectedModel != 3)
		m_pMoviePlane->stopMovieTexture();

	// Start or pause movie according to tracking state
	onTrackingEvent(m_pMetaioSDK->getTrackingValues());
}
