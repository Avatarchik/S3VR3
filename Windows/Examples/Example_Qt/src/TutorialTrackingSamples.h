#include "TutorialBase.h"

class MainWindow;

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class TutorialTrackingSamples : public TutorialBase, protected metaio::IMetaioSDKCallback
{
	Q_OBJECT

	public:
		TutorialTrackingSamples(MainWindow* mainWindow);
		virtual ~TutorialTrackingSamples();

	protected slots:
		void onIdMarkerButtonClicked();
		void onPictureMarkerButtonClicked();
		void onMarkerlessButtonClicked();

	protected:
		MainWindow*			m_pMainWindow;

		QPushButton*		m_pIdMarkerButton;
		QPushButton*		m_pPictureMarkerButton;
		QPushButton*		m_pMarkerlessButton;

		metaio::IGeometry*	m_pMetaioMan;

		void addButtons();

		virtual void loadContent() override;

		// From IMetaioSDKCallback
		virtual void onTrackingEvent(const metaio::stlcompat::Vector<metaio::TrackingValues>& trackingValues) override ;

		void setActiveTrackingConfig(int index);
};