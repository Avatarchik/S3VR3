#include "TutorialBase.h"

class MainWindow;

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class TutorialInstantTracking : public TutorialBase, protected metaio::IMetaioSDKCallback
{
	Q_OBJECT

	public:
		TutorialInstantTracking(MainWindow* mainWindow);
		virtual ~TutorialInstantTracking();

	protected slots:
		void on2DButtonClicked();
		void onUnsupportedInstantTrackingModeButtonClicked();
		void on3DButtonClicked();
		void onStartButtonClicked();

	protected:
		bool				m_isCloseToModel;

		MainWindow*			m_pMainWindow;

		QPushButton*		m_p2DButton;
		QPushButton*		m_p2DRectifiedButton;
		QPushButton*		m_p3DButton;
		QPushButton*		m_p2DSLAMButton;
		QPushButton*		m_p2DSLAMExtrapolationButton;
		QPushButton*		m_pStartButton;

		metaio::IGeometry*	m_pTiger;

		void addButtons();

		void switchButtons();

		void checkDistanceToTarget();

		virtual void loadContent() override;

		virtual void onDrawFrame() override;

		/// From IMetaioSDKCallback
		virtual void onInstantTrackingEvent(bool success, const metaio::stlcompat::String& file) override;

		void playSound();

		void setActiveTrackingConfig(int index, bool enablePreview = false);
};