#ifndef TUTORIALBASEAREL_H
#define TUTORIALBASEAREL_H

#include <QGLWidget>
#include <QWebView>
#include <QGraphicsScene>
#include <metaioSDK/IARELInterpreterCallback.h>
#include <metaioSDK/IGestureHandlerCallback.h>


class MainWindow;

namespace metaio
{
	class IARELInterpreter;
	class IMetaioSDKWin32;
	class GestureHandler;
}


class TutorialBaseAREL : public QGraphicsScene, public metaio::IARELInterpreterCallback
{
	Q_OBJECT

protected slots:
	/**
	* Callback, if a WebPage has been loaded
	* \param loaded true if it has been loaded successfully
	*/
	void loadFinished(bool loaded);

public:
	TutorialBaseAREL(MainWindow* mainWindow, QString tutorialNumber);
	virtual ~TutorialBaseAREL();

	/* IARELInterpreterCallback callbacks start */

	virtual void onSDKReady() override;

	/* IARELInterpreterCallback callbacks end */

protected:

	/// The WebView for HTML pages and javascript handling, needed for AREL
	QGraphicsWebView*			m_pWebView;
	/// true, if the tutorial has been initialized
	bool						m_initialized;
	/// the AREL interpreter
	metaio::IARELInterpreter*	m_pArelInterpreter;
	/// the mobile SDK
	metaio::IMetaioSDKWin32*	m_pMetaioSDK;
	/// handling touch events for AREL
	metaio::GestureHandler*		m_pGestureHandler;

	QString						m_tutorialName;

	/**
	* Load demo content, like tracking configuration (different depending on tutorial number)
	*/
	void loadContent();

	/**
	* QGraphicsScene inherited drawBackground function
	*
	* \param painter pointer to the QPainter object
	* \param rect the exposed rectangle
	*/
	void drawBackground(QPainter* painter, const QRectF & rect);

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
};


#endif
