#include "TutorialAdvancedRendering.h"

#include <metaioSDK/IMetaioSDKWin32.h>

void TutorialAdvancedRendering::loadContent()
{
	if(!m_pMetaioSDK->setTrackingConfiguration("../../../tutorialContent_crossplatform/TutorialAdvancedRendering/Assets/TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");

	metaio::IGeometry* geometry = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialAdvancedRendering/Assets/metaioman.md2");
	if(geometry)
		geometry->setScale(4.f);
	else
		qCritical("Failed to load MD2 model file");

	// Enable advanced rendering
	m_pMetaioSDK->setAdvancedRenderingFeatures(true);
	// As an alternative, metaioSDK.autoEnableAdvancedRenderingFeatures() should be used to
	// only enable advanced rendering on devices that are capable of performing it at a
	// decent speed.

	// Adjust effects
	m_pMetaioSDK->setDepthOfFieldParameters(0.1f, 0.6f, 0.2f);
	// Slightly reduce amount of motion blur
	m_pMetaioSDK->setMotionBlurIntensity(0.8f);
}