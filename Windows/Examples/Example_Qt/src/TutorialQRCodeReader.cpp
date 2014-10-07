#include "TutorialQRCodeReader.h"

#include "MainWindow.h"

#include <metaioSDK/IMetaioSDKWin32.h>
#include <QLabel>
#include <QString>

TutorialQRCodeReader::TutorialQRCodeReader(MainWindow* mainWindow) :
	m_pMainWindow(mainWindow),
	m_pQRCode(0),
	m_pQRCodeLabel(0)
{
	QBoxLayout* layout = m_pMainWindow->getButtonBar();

		
	m_pQRCodeLabel = new QLabel("Last QR code read: ");
	layout->addWidget(m_pQRCodeLabel);

	m_pQRCode = new QLabel();
	layout->addWidget(m_pQRCode);
}


TutorialQRCodeReader::~TutorialQRCodeReader()
{
	if(m_pQRCode)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pQRCode);
		delete m_pQRCode;
	}
	
	if(m_pQRCodeLabel)
	{
		m_pMainWindow->getButtonBar()->removeWidget(m_pQRCodeLabel);
		delete m_pQRCodeLabel;
	}
}

void TutorialQRCodeReader::loadContent()
{
	// Set QRCode tracking configuration
	if(!m_pMetaioSDK->setTrackingConfiguration("QRCODE"))
		qCritical("Failed to load tracking configuration");

	m_pMetaioSDK->registerCallback(this);

}

void TutorialQRCodeReader::onTrackingEvent(const metaio::stlcompat::Vector<metaio::TrackingValues> &trackingValuesVector)
{
	for (unsigned long i = 0 ; i < trackingValuesVector.size(); i++) 
	{
		metaio::TrackingValues trackingValues = trackingValuesVector[i];
		if (trackingValues.isTrackingState()) 
		{
			// reading the code
			QString str = trackingValues.additionalValues.c_str();
			QStringList list = str.split("::");
			if (list.size() > 1) 
			{
				m_pQRCode->setText(list[1]);
			}
		}
	}
}

