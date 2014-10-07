#include "TutorialHelloWorld.h"

#include <metaioSDK/IMetaioSDKWin32.h>

void TutorialHelloWorld::loadContent()
{
	if(!m_pMetaioSDK->setTrackingConfiguration("../../../tutorialContent_crossplatform/TutorialHelloWorld/Assets/TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");

	metaio::IGeometry* geometry = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialHelloWorld/Assets/metaioman.md2");
	if(geometry)
		geometry->setScale(4.f);
	else
		qCritical("Failed to load MD2 model file");
}