using UnityEngine;
using System.Collections;

public class LocationBasedARGUI : MonoBehaviour {
	
	public GameObject munich;
	public GameObject london;
	public GameObject paris;
	public GameObject tokyo;
	public GameObject rome;
	
	private Vector3 londonScreen;
	private Vector3 parisScreen;
	private Vector3 tokyoScreen;
	private Vector3 romeScreen;
	
	public Camera myCamera;
	
	public GUIStyle buttonTextStyle;
	private float SizeFactor;
	
	public GUIStyle textStyle;
	public GUIStyle textShadowStyle;
	
	// Use this for initialization
	void Start () {
		SizeFactor = GUIUtilities.SizeFactor;
	}
	
	// Update is called once per frame
	void Update () {
		SizeFactor = GUIUtilities.SizeFactor;
		
		londonScreen = myCamera.WorldToScreenPoint(london.transform.position);
		parisScreen = myCamera.WorldToScreenPoint(paris.transform.position);
		tokyoScreen = myCamera.WorldToScreenPoint(tokyo.transform.position);
		romeScreen = myCamera.WorldToScreenPoint(rome.transform.position);
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
		
		if(londonScreen.z > 0)
		{
			GUIUtilities.Text(new Rect( londonScreen.x + 3 * SizeFactor, Screen.height - londonScreen.y + 3 * SizeFactor, 0, 0), "London", textShadowStyle);
			GUIUtilities.Text(new Rect( londonScreen.x, Screen.height - londonScreen.y,	0, 0), "London", textStyle);
		}
		if(parisScreen.z > 0)
		{
			GUIUtilities.Text(new Rect( parisScreen.x + 3 * SizeFactor, Screen.height - parisScreen.y + 3 * SizeFactor, 0, 0), "Paris", textShadowStyle);
			GUIUtilities.Text(new Rect( parisScreen.x, Screen.height - parisScreen.y, 0, 0), "Paris", textStyle);
		}
		if(tokyoScreen.z > 0)
		{
			GUIUtilities.Text(new Rect( tokyoScreen.x + 3 * SizeFactor, Screen.height - tokyoScreen.y + 3 * SizeFactor, 0, 0), "Tokyo", textShadowStyle);
			GUIUtilities.Text(new Rect( tokyoScreen.x, Screen.height - tokyoScreen.y, 0, 0), "Tokyo", textStyle);
		}
		if(romeScreen.z > 0)
		{
			GUIUtilities.Text(new Rect( romeScreen.x + 3 * SizeFactor, Screen.height - romeScreen.y + 3 * SizeFactor, 0, 0), "Rome", textShadowStyle);
			GUIUtilities.Text(new Rect( romeScreen.x, Screen.height - romeScreen.y, 0, 0), "Rome", textStyle);
			
		}

	}
}
