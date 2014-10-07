arel.sceneReady(function()
{
	console.log("sceneReady");

	// Set a listener to get information about when the image is tracked
	arel.Events.setListener(arel.Scene, trackingHandler);

	// Adjust hand-eye calibration (i.e. difference in view of camera vs. left/right eye).
	// These are contrived example values. Real values should be gathered by an exact
	// calibration. Note that for typical scenarios, e.g. AR/VR glasses where the camera has
	// a translation to left/right eye, the camera image is still rendered as for the mono
	// case (it is not transformed by the hand-eye calibration to look correct). Therefore
	// on glasses, see-through mode should be enabled (see above).
	// Note that setStereoRendering automatically sets an initial hand-eye calibration for
	// known devices, so if you want to override it, you should instead call
	// setHandEyeCalibration *after* setStereoRendering(true)!
	var rotationLeft = new arel.Rotation();
	rotationLeft.setFromEulerAngleDegrees(new arel.Vector3D(0, -18, 0));
	arel.Scene.setHandEyeCalibration(
		new arel.Vector3D(70, 0, 0),
		rotationLeft,
		arel.CameraType.RENDERING_LEFT);
	var rotationRight = new arel.Rotation();
	rotationRight.setFromEulerAngleDegrees(new arel.Vector3D(0, 7, 0));
	arel.Scene.setHandEyeCalibration(
		new arel.Vector3D(10, 0, 0),
		rotationRight,
		arel.CameraType.RENDERING_RIGHT);

	// Enable stereo rendering
	arel.Scene.setStereoRendering(true);

	// Enable see through mode (e.g. on glasses)
	arel.Scene.setSeeThrough(true);
	arel.Scene.setSeeThroughColor(new arel.Vector4D(0, 0, 0, 255));
});

function trackingHandler(type, param)
{
	// Check if there is tracking information available
	if(param[0] !== undefined)
	{
		if(type && type == arel.Events.Scene.ONTRACKING && param[0].getState() == arel.Tracking.STATE_TRACKING)
		{
			console.log("Tracking is active");
		}
		else if(type && type == arel.Events.Scene.ONTRACKING && param[0].getState() == arel.Tracking.STATE_NOTTRACKING)
		{
			console.log("Tracking is lost");
		}
	}
};