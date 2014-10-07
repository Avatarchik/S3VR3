#include "TutorialBase.h"

class MainWindow;

QT_BEGIN_NAMESPACE
class QPushButton;
class QGraphicsSceneMouseEvent;
class QFrame;
QT_END_NAMESPACE

class TutorialEdgeBasedInitialization : public TutorialBase, protected metaio::IMetaioSDKCallback
{
	Q_OBJECT

	enum EState
	{
		STATE_INITIALIZATION,
		STATE_TRACKING
	};

	public:
		TutorialEdgeBasedInitialization(MainWindow* mainWindow);
		virtual ~TutorialEdgeBasedInitialization();

	protected slots:
		void onResetButtonClicked();

	protected:
		EState				m_state;

		MainWindow*			m_pMainWindow;

		metaio::IGeometry*	m_pModel;
		metaio::IGeometry*	m_pVizAidModel;

		QPushButton*		m_pResetButton;

		virtual void loadContent() override; 
		virtual void onDrawFrame() override;

		void loadTrackingConfig();

		/// From IMetaioSDKCallback
		virtual void onTrackingEvent(const metaio::stlcompat::Vector<metaio::TrackingValues>& trackingValues) override;
};