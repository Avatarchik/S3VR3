using UnityEngine;
using System.Collections;

public class ContentTypesGUI : MonoBehaviour 
{
	public GUIStyle buttonTextStyle;
	float SizeFactor;
	
	GameObject metaioman;
	GameObject image;
	GameObject truck;
	GameObject moviePlane;
	metaioMovieTexture movieTexture;
	
	// Use this for initialization
	void Start () 
	{
		SizeFactor = GUIUtilities.SizeFactor;
		
		metaioman = GameObject.Find("metaioman");
		image = GameObject.Find("image");
		truck = GameObject.Find("truck");
		moviePlane = GameObject.Find("moviePlane");
		movieTexture = moviePlane.GetComponent<metaioMovieTexture>();
		
		// Show only metaioman at the begining
		// TODO: Replace deprecated call SetActiveRecursively with SetActive if Unity 4.x is used
		metaioman.SetActiveRecursively(true);
		image.SetActiveRecursively(false);
		truck.SetActiveRecursively(false);
		moviePlane.SetActiveRecursively(false);
	}
	
	// Update is called once per frame
	void Update () 
	{
		SizeFactor = GUIUtilities.SizeFactor;
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
		
		if(GUIUtilities.ButtonWithText(new Rect(
				Screen.width - 300*SizeFactor,
				Screen.height - 400*SizeFactor,
				300*SizeFactor,
				100*SizeFactor),"Man",null,buttonTextStyle))
		{
			// Show only metaioman
			// TODO: Replace deprecated call SetActiveRecursively with SetActive if Unity 4.x is used
			metaioman.SetActiveRecursively(true);
			image.SetActiveRecursively(false);
			truck.SetActiveRecursively(false);
			moviePlane.SetActiveRecursively(false);
			movieTexture.pause();
		}
		
		if(GUIUtilities.ButtonWithText(new Rect(
				Screen.width - 300*SizeFactor,
				Screen.height - 300*SizeFactor,
				300*SizeFactor,
				100*SizeFactor),"Image",null,buttonTextStyle))
		{
			// Show only image
			// TODO: Replace deprecated call SetActiveRecursively with SetActive if Unity 4.x is used
			metaioman.SetActiveRecursively(false);
			image.SetActiveRecursively(true);
			truck.SetActiveRecursively(false);
			moviePlane.SetActiveRecursively(false);
			movieTexture.pause();
		}
		
		if(GUIUtilities.ButtonWithText(new Rect(
				Screen.width - 300*SizeFactor,
				Screen.height - 200*SizeFactor,
				300*SizeFactor,
				100*SizeFactor),"Truck",null,buttonTextStyle))
		{
			// Show only truck
			// TODO: Replace deprecated call SetActiveRecursively with SetActive if Unity 4.x is used
			metaioman.SetActiveRecursively(false);
			image.SetActiveRecursively(false);
			truck.SetActiveRecursively(true);
			moviePlane.SetActiveRecursively(false);
			movieTexture.pause();
		}
		
		if(GUIUtilities.ButtonWithText(new Rect(
				Screen.width - 300*SizeFactor,
				Screen.height - 100*SizeFactor,
				300*SizeFactor,
				100*SizeFactor),"Movie",null,buttonTextStyle))
		{
			// Show only movie
			// TODO: Replace deprecated call SetActiveRecursively with SetActive if Unity 4.x is used
			metaioman.SetActiveRecursively(false);
			image.SetActiveRecursively(false);
			truck.SetActiveRecursively(false);
			moviePlane.SetActiveRecursively(true);
			movieTexture.play(true);
		}
	}
}
