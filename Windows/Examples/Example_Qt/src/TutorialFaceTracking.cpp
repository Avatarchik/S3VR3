#include "TutorialFaceTracking.h"
#include <metaioSDK/IMetaioSDKWin32.h>

using namespace metaio;

void TutorialFaceTracking::loadContent()
{
	if(!m_pMetaioSDK->setTrackingConfiguration("FACE"))
	{
		qCritical("Failed to load tracking configuration");
	}

	IGeometry* geometry = m_pMetaioSDK->createGeometryFromImage("../../../tutorialContent_crossplatform/TutorialFaceTracking/Assets/Thought1.png");
	if(geometry)
	{
		geometry->setScale(0.5f);
		geometry->setTranslation(metaio::Vector3d(60.f, 80.f, 0.f));
	}
	else
	{
		qCritical("Failed to load the geometry");
	}

	geometry = m_pMetaioSDK->createGeometryFromImage("../../../tutorialContent_crossplatform/TutorialFaceTracking/Assets/Thought2.png");
	if(geometry)
	{
		geometry->setScale(0.5f);
		geometry->setTranslation(metaio::Vector3d(-60.f, -60.f, 0.f));
	}
	else
	{
		qCritical("Failed to load the geometry");
	}
}