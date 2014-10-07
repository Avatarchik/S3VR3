#ifndef TUTORIALBASE_H
#define TUTORIALBASE_H

#include <QGraphicsScene>
#include <metaioSDK/IGestureHandlerCallback.h>


namespace metaio
{
	class IMetaioSDKWin32;
	class GestureHandler;
}

/// Abstract base class for non-AREL tutorials
class TutorialBase : public QGraphicsScene
{
	Q_OBJECT

public:
	TutorialBase();
	virtual ~TutorialBase();

private:
	// Copying forbidden
	TutorialBase(const TutorialBase&);

protected:
	/// true if the tutorial has been initialized
	bool						m_initialized;

	/// the mobile SDK
	metaio::IMetaioSDKWin32*	m_pMetaioSDK;

	/// Gesture handler for touch events, can optionally be used by tutorial implementation
	metaio::GestureHandler*		m_pGestureHandler;

	/**
	* Load demo content, like tracking configuration (different depending on tutorial number)
	*/
	virtual void loadContent() = 0;

	/**
	* QGraphicsScene inherited drawBackground function
	*
	* \param painter pointer to the QPainter object
	* \param rect the exposed rectangle
	*/
	virtual void drawBackground(QPainter* painter, const QRectF & rect) override;

	/**
	* Inherited method for handling mouse move event
	*
	* \param mouseEvent the QGraphicsSceneMouseEvent mouse event
	*/
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	/**
	* Inherited method for handling mouse press event
	*
	* \param mouseEvent the QGraphicsSceneMouseEvent mouse event
	*/
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

	/**
	* Inherited method for handling mouse release event
	*
	* \param mouseEvent the QGraphicsSceneMouseEvent mouse event
	*/
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

	/**
	* Optional method that is called right before rendering a frame
	*/
	virtual void onDrawFrame() {};
};

#endif