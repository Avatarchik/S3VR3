using UnityEngine;
using System.Collections;
using metaio;

public class InstantTrackingGUI : MonoBehaviour
{
	private float SizeFactor;
	public GUIStyle buttonTextStyle;

	// Update is called once per frame
	void Update()
	{
		SizeFactor = GUIUtilities.SizeFactor;
	}

	void OnGUI()
	{
		if(GUIUtilities.ButtonWithText(new Rect(
			Screen.width - 200*SizeFactor,
			0,
			200*SizeFactor,
			100*SizeFactor),"Back",null,buttonTextStyle) ||	Input.GetKeyDown(KeyCode.Escape)) {
			PlayerPrefs.SetInt("backFromARScene", 1);
			Application.LoadLevel("MainMenu");
		}

		if(GUIUtilities.ButtonWithText(new Rect(
				Screen.width - 300*SizeFactor,
				Screen.height - 480*SizeFactor,
				300*SizeFactor,
				90*SizeFactor),"2D",null,buttonTextStyle))
		{
			// start instant tracking, it will call the callback once done
			MetaioSDKUnity.startInstantTracking("INSTANT_2D", "");
			GUI.enabled = false;
		}

		if(GUIUtilities.ButtonWithText(new Rect(
				Screen.width - 300*SizeFactor,
				Screen.height - 390*SizeFactor,
				300*SizeFactor,
				90*SizeFactor),"2D Rectified",null,buttonTextStyle))
		{
#if UNITY_EDITOR || UNITY_STANDALONE_OSX || UNITY_STANDALONE_WIN
			Debug.LogError("This mode is currently not implemented for the Editor Preview and Windows/Mac Standalone, please try on a mobile device");
#else
			// start instant tracking, it will call the callback once done
			MetaioSDKUnity.startInstantTracking("INSTANT_2D_GRAVITY", "");
			GUI.enabled = false;
#endif
		}

		if(GUIUtilities.ButtonWithText(new Rect(
				Screen.width - 300*SizeFactor,
				Screen.height - 300*SizeFactor,
				300*SizeFactor,
				90*SizeFactor),"3D",null,buttonTextStyle))
		{
			// start instant tracking, it will call the callback once done
			MetaioSDKUnity.startInstantTracking("INSTANT_3D", "");
			GUI.enabled = false;
		}

		if(GUIUtilities.ButtonWithText(new Rect(
				Screen.width - 300*SizeFactor,
				Screen.height - 210*SizeFactor,
				300*SizeFactor,
				90*SizeFactor),"2D SLAM",null,buttonTextStyle))
		{
#if UNITY_EDITOR || UNITY_STANDALONE_OSX || UNITY_STANDALONE_WIN
			Debug.LogError("This mode is currently not implemented for the Editor Preview and Windows/Mac Standalone, please try on a mobile device");
#else
			// start instant tracking, it will call the callback once done
			MetaioSDKUnity.startInstantTracking("INSTANT_2D_GRAVITY_SLAM", "");
			GUI.enabled = false;
#endif
		}
		
		GUIStyle smallButtonTextStyle = new GUIStyle(buttonTextStyle);
		smallButtonTextStyle.fontSize = buttonTextStyle.fontSize * 4 / 5;

		if(GUIUtilities.ButtonWithText(new Rect(
				Screen.width - 300*SizeFactor,
				Screen.height - 120*SizeFactor,
				300*SizeFactor,
				120*SizeFactor),"2D SLAM + sensor extrapolation",null,smallButtonTextStyle))
		{
#if UNITY_EDITOR || UNITY_STANDALONE_OSX || UNITY_STANDALONE_WIN
			Debug.LogError("This mode is currently not implemented for the Editor Preview and Windows/Mac Standalone, please try on a mobile device");
#else
			// start instant tracking, it will call the callback once done
			MetaioSDKUnity.startInstantTracking("INSTANT_2D_GRAVITY_SLAM_EXTRAPOLATED", "");
			GUI.enabled = false;
#endif
		}
	}
}
