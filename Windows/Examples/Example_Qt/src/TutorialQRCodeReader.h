#include "TutorialBase.h"

class MainWindow;

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class TutorialQRCodeReader : public TutorialBase, protected metaio::IMetaioSDKCallback
{
	Q_OBJECT

	public:
		TutorialQRCodeReader(MainWindow* mainWindow);
		virtual ~TutorialQRCodeReader();

	protected:
		MainWindow*	m_pMainWindow;

		QLabel* m_pQRCodeLabel;
		QLabel* m_pQRCode;

		virtual void loadContent() override;
		virtual void onTrackingEvent(const metaio::stlcompat::Vector< metaio::TrackingValues > &trackingValues) override;
};