using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using metaio;

public class QRCodeReader : metaioCallback 
{
    override protected void onTrackingEvent(List<TrackingValues> trackingValues)
    {
		foreach (TrackingValues tv in trackingValues)
		{
			if (tv.state.isTrackingState())
			{
				string[] strList = tv.additionalValues.Split(new string[] { "::" }, 2, System.StringSplitOptions.RemoveEmptyEntries);
		        if (strList.Length > 1) 
		        {
		            GetComponent<QRCodeReaderGUI>().setCode(strList[1]);
					Debug.Log("QR code read:  "+strList[1]);
		        }
			}
		}
    }
}
