#include "TutorialBase.h"

class TutorialDynamicModels : public TutorialBase, protected metaio::IMetaioSDKCallback
{
	Q_OBJECT

	public:
		TutorialDynamicModels();
		virtual ~TutorialDynamicModels() {}

	protected:
		bool				m_isCloseToModel;

		bool				m_isMetaioManTouched;

		metaio::IGeometry*	m_pMetaioMan;

		void checkDistanceToTarget();

		virtual void loadContent() override;

		void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);

		void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

		/// From IMetaioSDKCallback
		virtual void onAnimationEnd(metaio::IGeometry* geometry, const metaio::stlcompat::String& animationName) override;

		virtual void onDrawFrame() override;
};