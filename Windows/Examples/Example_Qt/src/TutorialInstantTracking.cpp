#include "MainWindow.h"
#include "TutorialInstantTracking.h"

#include <QMessageBox>
#include <QPushButton>

#include <metaioSDK/GestureHandler.h>
#include <metaioSDK/IMetaioSDKWin32.h>

TutorialInstantTracking::TutorialInstantTracking(MainWindow* mainWindow) :
	m_isCloseToModel(false),
	m_pMainWindow(mainWindow),
	m_p2DButton(0),
	m_p2DRectifiedButton(0),
	m_p3DButton(0),
	m_pTiger(0)
{
}


TutorialInstantTracking::~TutorialInstantTracking()
{
	if (m_p2DButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_p2DButton);
		delete m_p2DButton;
		m_p2DButton = 0;
	}

	if (m_p2DRectifiedButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_p2DRectifiedButton);
		delete m_p2DRectifiedButton;
		m_p2DRectifiedButton = 0;
	}

	if (m_p3DButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_p3DButton);
		delete m_p3DButton;
		m_p3DButton = 0;
	}

	if (m_p2DSLAMButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_p2DSLAMButton);
		delete m_p2DSLAMButton;
		m_p2DSLAMButton = 0;
	}

	if (m_p2DSLAMExtrapolationButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_p2DSLAMExtrapolationButton);
		delete m_p2DSLAMExtrapolationButton;
		m_p2DSLAMExtrapolationButton = 0;
	}

	if (m_pStartButton)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pStartButton);
		delete m_pStartButton;
		m_pStartButton = 0;
	}
}

void TutorialInstantTracking::switchButtons()
{
	if (m_pStartButton->isVisible())
	{
		m_pStartButton->hide();
		m_p2DButton->show();
		m_p2DRectifiedButton->show();
		m_p3DButton->show();
		m_p2DSLAMButton->show();
		m_p2DSLAMExtrapolationButton->show();
	}
	else 
	{
		m_p2DButton->hide();
		m_p2DRectifiedButton->hide();
		m_p3DButton->hide();
		m_p2DSLAMButton->hide();
		m_p2DSLAMExtrapolationButton->hide();
		m_pStartButton->show();
	}
}


void TutorialInstantTracking::addButtons()
{
	QBoxLayout* layout = m_pMainWindow->getButtonBar();

	// Add buttons to switch between models
	m_p2DButton = new QPushButton("2D");
	layout->addWidget(m_p2DButton);
	QObject::connect(m_p2DButton , SIGNAL(clicked()), this, SLOT(on2DButtonClicked()));

	m_p2DRectifiedButton = new QPushButton("2D Rectified");
	layout->addWidget(m_p2DRectifiedButton);
	QObject::connect(m_p2DRectifiedButton, SIGNAL(clicked()), this, SLOT(onUnsupportedInstantTrackingModeButtonClicked()));

	m_p3DButton = new QPushButton("3D");
	layout->addWidget(m_p3DButton);
	QObject::connect(m_p3DButton, SIGNAL(clicked()), this, SLOT(on3DButtonClicked()));

	m_p2DSLAMButton = new QPushButton("2D SLAM");
	layout->addWidget(m_p2DSLAMButton);
	QObject::connect(m_p2DSLAMButton, SIGNAL(clicked()), this, SLOT(onUnsupportedInstantTrackingModeButtonClicked()));

	m_p2DSLAMExtrapolationButton = new QPushButton("2D SLAM + sensor extrapolation");
	layout->addWidget(m_p2DSLAMExtrapolationButton);
	QObject::connect(m_p2DSLAMExtrapolationButton, SIGNAL(clicked()), this, SLOT(onUnsupportedInstantTrackingModeButtonClicked()));

	m_pStartButton = new QPushButton("Start");
	layout->addWidget(m_pStartButton);
	QObject::connect(m_pStartButton , SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
	m_pStartButton->hide();
}


void TutorialInstantTracking::checkDistanceToTarget()
{
	const metaio::TrackingValues &trackingValues = m_pMetaioSDK->getTrackingValues(1);

	// If quality > 0, it means we're currently tracking
	if (trackingValues.quality <= 0)
		return;

	const float distanceToTarget = sqrtf(trackingValues.translation.x*trackingValues.translation.x +
										 trackingValues.translation.y*trackingValues.translation.y +
										 trackingValues.translation.z*trackingValues.translation.z);
	const float threshold = 250;

	if (m_isCloseToModel)
	{
		// If our distance is larger than our threshold (+ a little)
		if (distanceToTarget > (threshold + 10))
		{
			m_isCloseToModel = false;
			playSound();
			m_pTiger->startAnimation("meow", false);
		}
	}
	else
	{
		// We're not close yet, let's check if we are now
		if (distanceToTarget < threshold)
		{
			m_isCloseToModel = true;
			playSound();
			m_pTiger->startAnimation("meow", false);
		}
	}
}


void TutorialInstantTracking::loadContent()
{
	addButtons();

	m_pMetaioSDK->registerCallback(this);

	m_pTiger = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialInstantTracking/Assets/tiger.md2");
	if (!m_pTiger)
	{
		qCritical("Failed to load tiger model");
		return;
	}

	m_pTiger->setScale(metaio::Vector3d(8.0, 8.0, 8.0));

	// Do not set tracking config yet, only on button click
}


void TutorialInstantTracking::on2DButtonClicked()
{
	setActiveTrackingConfig(0, true);
	switchButtons();
}

void TutorialInstantTracking::onStartButtonClicked()
{
	setActiveTrackingConfig(0, false);
	switchButtons();
}

void TutorialInstantTracking::onUnsupportedInstantTrackingModeButtonClicked()
{
	QMessageBox::critical(
		m_pMainWindow,
		"Unimplemented",
		"This mode requires sensors and will thus not work on Windows/Qt at the moment.");
}


void TutorialInstantTracking::on3DButtonClicked()
{
	setActiveTrackingConfig(2);
}


void TutorialInstantTracking::onDrawFrame()
{
	TutorialBase::onDrawFrame();

	if (m_pTiger->isVisible())
		checkDistanceToTarget();
}


void TutorialInstantTracking::onInstantTrackingEvent(bool success, const metaio::stlcompat::String& file)
{
	if (success)
		m_pMetaioSDK->setTrackingConfiguration(file);
	else
		qCritical("Instant tracking timed out!");
}


void TutorialInstantTracking::playSound()
{
	if (!PlaySoundW(L"../../../tutorialContent_crossplatform/TutorialInstantTracking/Assets/meow.wav", 0, SND_ASYNC | SND_FILENAME | SND_NODEFAULT))
		qDebug("Could not play sound");
}


void TutorialInstantTracking::setActiveTrackingConfig(int index, bool enablePreview)
{
	switch(index)
	{
		case 0:
			m_pTiger->setRotation(metaio::Rotation(metaio::Vector3d(0, 0, (float)M_PI)));
			m_pMetaioSDK->startInstantTracking("INSTANT_2D", "", enablePreview);
			qDebug("Instant tracking snapshot is done");
			break;

		// Not implemented because a gravity-measuring sensor is not available on Windows
		/*case 1:
			m_pTiger->setRotation(metaio::Rotation(metaio::Vector3d(0, 0, (float)-M_PI)));
			m_pMetaioSDK->startInstantTracking("INSTANT_2D_GRAVITY");
			qDebug("Instant rectified tracking snapshot is done");
			break;*/

		case 2:
			m_pMetaioSDK->startInstantTracking("INSTANT_3D");
			qDebug("SLAM started");
			break;
	}
}