using UnityEngine;
using System.Collections;

public class StereoRenderingGUI : MonoBehaviour
{
	public GUIStyle buttonTextStyle;
	public GUIStyle buttonTextStyleSmall;
	float SizeFactor;

	void Start()
	{
		SizeFactor = GUIUtilities.SizeFactor;
	}

	void Update()
	{
		SizeFactor = GUIUtilities.SizeFactor;
	}

	void OnGUI()
	{
		if (GUIUtilities.ButtonWithText(new Rect(
			Screen.width - 200*SizeFactor,
			0,
			200*SizeFactor,
			100*SizeFactor), "Back", null, buttonTextStyle) || Input.GetKeyDown(KeyCode.Escape))
		{
			PlayerPrefs.SetInt("backFromARScene", 1);
			Application.LoadLevel("MainMenu");
		}

		if(GUIUtilities.ButtonWithText(new Rect(
			Screen.width - 400*SizeFactor,
			Screen.height - 100*SizeFactor,
			400*SizeFactor,
			100*SizeFactor), "Toggle stereo", null, buttonTextStyleSmall))
		{
			metaioSDK sdk = (metaioSDK)FindObjectOfType(typeof(metaioSDK));
			sdk.stereoRenderingEnabled = !sdk.stereoRenderingEnabled;
		}
		
		if(GUIUtilities.ButtonWithText(new Rect(
			Screen.width - 400*SizeFactor,
			Screen.height - 200*SizeFactor,
			400*SizeFactor,
			100*SizeFactor), "Toggle see-through", null, buttonTextStyleSmall))
		{
			metaioSDK sdk = (metaioSDK)FindObjectOfType(typeof(metaioSDK));
			sdk.seeThroughEnabled = !sdk.seeThroughEnabled;
		}
	}
}
