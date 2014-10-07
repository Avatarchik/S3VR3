#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include <QGraphicsWebView>


class MainWindow;

namespace metaio
{
	class IARELInterpreter;
	class IMetaioSDKWin32;
	class GestureHandler;
}


class Menu : public QGraphicsScene
{
	Q_OBJECT

protected slots:
	/**
	* Load demo (HTML menu)
	*/
	void loadContent();

	void linkClicked(const QUrl& url);

public:
	class TutorialSelectionCallback
	{
		public:
			virtual ~TutorialSelectionCallback() {};

			virtual void startTutorial(QString tutorialName) = 0;

			virtual void startTutorialAREL(QString tutorialName) = 0;
	};

	Menu(MainWindow* mainWindow, TutorialSelectionCallback* tutorialSelectionCallback);
	virtual ~Menu();

protected:
	TutorialSelectionCallback*	m_pCallback;

	/// The WebView for HTML pages and javascript handling, needed for AREL
	QGraphicsWebView*			m_pWebView;
};


#endif
