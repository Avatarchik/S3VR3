using UnityEngine;
using System;

public class DynamicModelsGUI : MonoBehaviour
{	
	private GameObject metaioMan;
	public GUIStyle buttonTextStyle;
	float SizeFactor;
	
	// variables for ray tracing
	private RaycastHit hit;
	private LayerMask layerMask = 1<<4;

	private bool selected = false;
	private Vector3 offset = new Vector3(0.0f, 0.0f, 0.0f);
	
	void Start() 
	{
		SizeFactor = GUIUtilities.SizeFactor;
		
		// Find metaioman object
		metaioMan = GameObject.Find("metaioman");
	}
	
	// Update is called once per frame
	void Update()
	{	
		SizeFactor = GUIUtilities.SizeFactor;
	
		// only handle touchs or clicks when metaioman is active, i.e.
		// is visible on tracking pattern
		if (metaioMan.active)
		{
			if (Input.touchCount > 0)
				// if tracking, then evaluate touch point
				handleTouches();
			else if (Input.GetMouseButton(0))
				handleClicks();
			else
				selected = false;
		}
	}
	
	private void handleTouches()
	{
		// if there's touch points and the phase is began-->try to select the geometry
		if(Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Began)
			selectGameObject(Input.GetTouch(0).position);
		
		// if the touch point is moving and metaio man is selected
		if(Input.GetTouch(0).phase == TouchPhase.Moved && selected)
			moveGameObject(Input.GetTouch(0).position);
		else if(Input.GetTouch(0).phase == TouchPhase.Ended)
			// deselect metaio man if touch has ended
			selected = false;
	}
	
	public void handleClicks()
	{
		// if there's left mouse click-->try to select the geometry
		if (!selected && Input.GetMouseButtonDown(0))
			selectGameObject(Input.mousePosition);
		
		if (selected && Input.GetMouseButton(0))
			moveGameObject(Input.mousePosition);
	}
	
	public void selectGameObject(Vector2 position)
	{
		// get a ray from the touch point
		Ray ray = Camera.main.ScreenPointToRay(position);
			
		// layer mask, metaio man is on layer 4
		layerMask = 1<<4;
			
		// cast a ray on layer 4, if metaio man has been hit
		if (Physics.Raycast(ray, out hit, 5000, layerMask) && hit.collider.gameObject.name == "metaioman_mesh")
		{
			// metaio man is touched --> select it
			selected = true;
				
			// swith to layer 8, find the initial touch point on the plane and use it as a reference
			layerMask = 1<<8;
			if (Physics.Raycast(ray, out hit, 5000, layerMask))
			{
				// record the offset of the touch point and the object position point
				offset = hit.point - metaioMan.transform.position;
			}
		}
		else
			// not hit, don't select
			selected = false;
	}
	
	public void moveGameObject(Vector2 position)
	{
		// cast a ray on layer 8 (the plane) to calculate the hit position of the plane
		Ray ray = Camera.main.ScreenPointToRay(position);
		layerMask = 1<<8;
		if(Physics.Raycast(ray, out hit, 5000, layerMask) && hit.collider.gameObject.name == "Plane")
		{
			// move the metaio man to the intersect of the ray and the plane, offset should be accounted for
			metaioMan.transform.position = hit.point - offset;
		}
	}
	
	public void OnGUI()
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

