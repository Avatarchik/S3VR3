using UnityEngine;
using System.Collections;

public class QRCodeReaderGUI : MonoBehaviour {

    public GUIStyle buttonTextStyle;
    public GUIStyle textStyle;
    float SizeFactor;

    private string qrCode;

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
            Screen.width - 200 * SizeFactor,
            0,
            200 * SizeFactor,
            100 * SizeFactor), "Back", null, buttonTextStyle) || Input.GetKeyDown(KeyCode.Escape))
        {
            PlayerPrefs.SetInt("backFromARScene", 1);
            Application.LoadLevel("MainMenu");
        }

        GUIUtilities.Text(new Rect(0, 0, 500 * SizeFactor, 300 * SizeFactor), "Last QR code read: \n" + qrCode, textStyle);
    }

    public void setCode(string qrCode)
    {
        this.qrCode = qrCode;
    }
}
