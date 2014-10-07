#include "TutorialBase.h"

class MainWindow;

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class TutorialDynamicLighting : public TutorialBase
{
	Q_OBJECT

	public:
		TutorialDynamicLighting(MainWindow* mainWindow);
		virtual ~TutorialDynamicLighting();

	protected slots:
		void onDirectionalLightButtonClicked();
		void onPointLightButtonClicked();
		void onSpotLightButtonClicked();

	protected:
		MainWindow*						m_pMainWindow;

		QPushButton*					m_pDirectionalLightButton;
		QPushButton*					m_pPointLightButton;
		QPushButton*					m_pSpotLightButton;

		metaio::ILight*					m_pDirectionalLight;
		metaio::ILight*					m_pPointLight;
		metaio::ILight*					m_pSpotLight;
		metaio::IGeometry*				m_pDirectionalLightGeo;
		metaio::IGeometry*				m_pPointLightGeo;
		metaio::IGeometry*				m_pSpotLightGeo;

		metaio::IGeometry*				m_pModel;

		void addGUI();

		metaio::IGeometry* createLightGeometry();

		virtual void drawBackground(QPainter* painter, const QRectF & rect) override;

		virtual void loadContent() override;

		void updateLightIndicator(metaio::IGeometry* indicatorGeo, metaio::ILight* light);
};