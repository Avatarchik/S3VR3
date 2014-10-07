#include "TutorialBase.h"

class MainWindow;

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class TutorialContentTypes : public TutorialBase, protected metaio::IMetaioSDKCallback
{
	Q_OBJECT

	public:
		TutorialContentTypes(MainWindow* mainWindow);
		virtual ~TutorialContentTypes();

	protected slots:
		void onImageButtonClicked();
		void onMetaioManButtonClicked();
		void onMovieButtonClicked();
		void onTruckButtonClicked();

	protected:
		MainWindow*			m_pMainWindow;

		QPushButton*		m_pSelectMetaioManButton;
		QPushButton*		m_pSelectImageButton;
		QPushButton*		m_pSelectTruckButton;
		QPushButton*		m_pSelectMovieButton;

		metaio::IGeometry*	m_pImagePlane;
		metaio::IGeometry*	m_pMetaioMan;
		metaio::IGeometry*	m_pMoviePlane;
		metaio::IGeometry*	m_pTruck;
		int					m_selectedModel;

		void addButtons();

		virtual void loadContent() override;

		// From IMetaioSDKCallback
		virtual void onTrackingEvent(const metaio::stlcompat::Vector<metaio::TrackingValues>& trackingValues) override;

		void setActiveModel(int modelIndex);
};