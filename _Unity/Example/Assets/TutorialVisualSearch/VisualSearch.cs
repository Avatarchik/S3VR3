using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using System.IO;
using metaio;

public class VisualSearch: metaioCallback 
{
	TextMesh resultText;
	
	private static String databaseID = "sdktest";
	private static String visualSearchServer = "cvs.junaio.com/vs";
	
	override protected void onSDKReady()
	{
		// Get reference to the TextMesh to display the result
		GameObject textObject = GameObject.Find("VSResultText");
		resultText = (TextMesh)textObject.GetComponent(typeof(TextMesh));
		
		MetaioSDKUnity.requestVisualSearch(databaseID, 1, visualSearchServer);
	}
	
	override protected void onVisualSearchResult(VisualSearchResponse[] response, int errorCode)
	{
//		Debug.Log("onVisualSearchResult: "+errorCode+", "+response.Length);
		
		if (errorCode == 0 && response.Length > 0)
		{	
			resultText.text = Path.GetFileNameWithoutExtension(response[0].TrackingConfigurationName);
			
			int result = MetaioSDKUnity.setTrackingConfiguration(response[0].TrackingConfiguration, 0);
			Debug.Log("New tracking configuration loaded: "+result);
		}
		else
		{
			MetaioSDKUnity.requestVisualSearch(databaseID, 1, visualSearchServer);
		}
	}
	
	override protected void onVisualSearchStatusChanged(String state)
	{
		Debug.Log("onVisualSearchStatusChanged: "+state);
	}
	
	override protected void onTrackingEvent(List<TrackingValues> trackingValues)
    {
		foreach (TrackingValues tv in trackingValues)
		{
			if (!tv.state.isTrackingState())
			{
				MetaioSDKUnity.requestVisualSearch(databaseID, 1, visualSearchServer);
				break;
			}
		}
    }
	
}
