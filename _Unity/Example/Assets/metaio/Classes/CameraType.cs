namespace metaio
{
	public enum CameraType
	{
		Tracking = 1,
		RenderingLeft = 2,
		RenderingRight = 4,
		Rendering = RenderingLeft | RenderingRight
	}
}
