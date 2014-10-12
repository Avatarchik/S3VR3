using UnityEngine;
using System.Collections;

public class HelloWorldGUI : MonoBehaviour {
	
	public GUIStyle buttonTextStyle;
	float SizeFactor;
	
	// Use this for initialization
	void Start () {
		SizeFactor = GUIUtilities.SizeFactor;
	}
	
	// Update is called once per frame
	void Update () {
		SizeFactor = GUIUtilities.SizeFactor;
	}
	
	void OnGUI () {
		
		if(GUIUtilities.ButtonWithText(new Rect(
			Screen.width - 200*SizeFactor,
			0,
			200*SizeFactor,
			100*SizeFactor),"Back",null,buttonTextStyle) ||	Input.GetKeyDown(KeyCode.Escape)) {
			PlayerPrefs.SetInt("backFromARScene", 1);
			Application.LoadLevel("MainMenu");
		}
	}
}
