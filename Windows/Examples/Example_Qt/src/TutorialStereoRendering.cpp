#include "TutorialStereoRendering.h"

#include <metaioSDK/IMetaioSDKWin32.h>

void TutorialStereoRendering::loadContent()
{
	if(!m_pMetaioSDK->setTrackingConfiguration("../../../tutorialContent_crossplatform/TutorialStereoRendering/Assets/TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");

	metaio::IGeometry* geometry = m_pMetaioSDK->createGeometry("../../../tutorialContent_crossplatform/TutorialStereoRendering/Assets/metaioman.md2");
	if(geometry)
		geometry->setScale(4.f);
	else
		qCritical("Failed to load MD2 model file");

	// Adjust hand-eye calibration (i.e. difference in view of camera vs. left/right eye).
	// These are contrived example values. Real values should be gathered by an exact
	// calibration. Note that for typical scenarios, e.g. AR/VR glasses where the camera has
	// a translation to left/right eye, the camera image is still rendered as for the mono
	// case (it is not transformed by the hand-eye calibration to look correct). Therefore
	// on glasses, see-through mode should be enabled (see above).
	// Note that setStereoRendering automatically sets an initial hand-eye calibration for
	// known devices, so if you want to override it, you should instead call
	// setHandEyeCalibration *after* setStereoRendering(true)!
	m_pMetaioSDK->setHandEyeCalibration(
		metaio::Vector3d(70.f, 0.f, 0.f),
		metaio::Rotation(0.f, -18.0f * (float)M_PI/180.0f, 0.f),
		metaio::ECT_RENDERING_LEFT);

	m_pMetaioSDK->setHandEyeCalibration(
			metaio::Vector3d(10.f, 0.f, 0.f),
			metaio::Rotation(0.f, 7.f * (float)M_PI/180.0f, 0.f),
			metaio::ECT_RENDERING_RIGHT);

	// Enable stereo rendering
	m_pMetaioSDK->setStereoRendering(true);

	// Enable see through mode (e.g. on glasses)
	m_pMetaioSDK->setSeeThrough(true);
	m_pMetaioSDK->setSeeThroughColor(0, 0, 0, 255);
}