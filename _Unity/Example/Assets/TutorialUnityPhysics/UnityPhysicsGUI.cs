using UnityEngine;
using System.Collections;

public class UnityPhysicsGUI : MonoBehaviour 
{
	private float SizeFactor;
	public GUIStyle buttonTextStyle;
	
	public GameObject[] spheres;
	
	// Use this for initialization
	void Start () 
	{
		SizeFactor = GUIUtilities.SizeFactor;
	}
	

	// Update is called once per frame
	void Update () 
	{
		SizeFactor = GUIUtilities.SizeFactor;
		
		// Reset spheres' position to re-animate
		foreach(GameObject sphere in spheres)
		{
			if(sphere.transform.position.y < -20f)
			{
				sphere.transform.position = new Vector3(0f, 200f, 0f);
			}
		}
	}
	
	void OnGUI () 
	{	
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
