#include "TutorialDynamicModels.h"

#include <QGraphicsSceneMouseEvent>
#include <metaioSDK/GestureHandler.h>
#include <metaioSDK/IMetaioSDKWin32.h>

TutorialDynamicModels::TutorialDynamicModels() :
	m_pMetaioMan(0),
	m_isCloseToModel(false),
	m_isMetaioManTouched(false)
{
}


void TutorialDynamicModels::checkDistanceToTarget()
{
	const metaio::TrackingValues &trackingValues = m_pMetaioSDK->getTrackingValues(1);

	// If quality > 0, it means we're currently tracking
	if(trackingValues.quality <= 0)
		return;

	const float distanceToTarget = sqrtf(trackingValues.translation.x*trackingValues.translation.x +
										 trackingValues.translation.y*trackingValues.translation.y +
										 trackingValues.translation.z*trackingValues.translation.z);
	const float threshold = 800;

	if(m_isCloseToModel)
	{
		// If our distance is larger than our threshold (+ a little)
		if(distanceToTarget > (threshold + 10))
		{
			m_isCloseToModel = false;
			m_pMetaioMan->startAnimation("close_up", false);
		}
	}
	else
	{
		// We're not close yet, let's check if we are now
		if(distanceToTarget < threshold)
		{
			m_isCloseToModel = true;
			m_pMetaioMan->startAnimation("close_down", false);
		}
	}
}


void TutorialDynamicModels::loadContent()
{
	if(!m_pMetaioSDK->setTrackingConfiguration("../../../tutorialContent_crossplatform/TutorialDynamicModels/Assets/TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");

	m_pMetaioMan = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialDynamicModels/Assets/metaioman.md2");
	if(!m_pMetaioMan)
		qCritical("Failed to load metaio man model");

	m_pMetaioMan->setScale(metaio::Vector3d(4.0, 4.0, 4.0));

	m_pGestureHandler->addObject(m_pMetaioMan, 1);

	// We need to know when an animation ends (onAnimationEnd)
	m_pMetaioSDK->registerCallback(this);

	m_pMetaioMan->startAnimation("idle", true);
}


void TutorialDynamicModels::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	TutorialBase::mousePressEvent(mouseEvent);

	// See comment in TutorialBase::mouseMoveEvent()
	const int x = mouseEvent->scenePos().x() + 800/2;
	const int y = mouseEvent->scenePos().y() + 600/2;

	metaio::IGeometry *pickedGeometry = m_pMetaioSDK->getGeometryFromViewportCoordinates(x, y, true);
	if(pickedGeometry == m_pMetaioMan)
		m_isMetaioManTouched = true;
}


void TutorialDynamicModels::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	TutorialBase::mouseReleaseEvent(mouseEvent);

	// Start an animation after metaio man was touched/moved
	if(m_isMetaioManTouched)
	{
		m_pMetaioMan->startAnimation("shock_down", false);
		m_isMetaioManTouched = false;
	}
}


void TutorialDynamicModels::onAnimationEnd(metaio::IGeometry* geometry, const metaio::stlcompat::String& animationName)
{
	if(geometry != m_pMetaioMan)
		return;

	if(animationName == "shock_down")
	{
		geometry->startAnimation("shock_idle", false);
	}
	else if(animationName == "shock_idle")
	{
		geometry->startAnimation("shock_up", false);
	}
	else if(animationName == "shock_up" || animationName == "close_up")
	{
		if(m_isCloseToModel)
			geometry->startAnimation("close_idle", true);
		else
			geometry->startAnimation("idle", true );
	}
	else if(animationName == "close_down")
	{
		geometry->startAnimation( "close_idle", true);
	}
}


void TutorialDynamicModels::onDrawFrame()
{
	TutorialBase::onDrawFrame();

	if(m_pMetaioMan->isVisible())
		checkDistanceToTarget();
}