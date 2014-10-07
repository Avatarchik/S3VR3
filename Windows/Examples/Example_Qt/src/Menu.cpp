#include "Menu.h"
#include "MainWindow.h"

#include <math.h>

#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsWebView>
#include <QWebFrame>
#include <QFileInfo>
#include <QUrl>
#include <QUrlQuery>
#include <QWebInspector>

#include <metaioSDK/IARELInterpreter.h>
#include <metaioSDK/IMetaioSDKWin32.h>
#include <metaioSDK/GestureHandler.h>

Menu::Menu(MainWindow* mainWindow, TutorialSelectionCallback* tutorialSelectionCallback)
	// do not set a parent so that this instance can be deconstructed manually (http://stackoverflow.com/a/13117414)
	: QGraphicsScene(),
	  m_pCallback(tutorialSelectionCallback)
{
	// Create a webview and connect the load finished event
	m_pWebView = new QGraphicsWebView();
	addItem(m_pWebView);
	m_pWebView->resize(800, 600);

	QObject::connect(m_pWebView, SIGNAL(linkClicked(const QUrl&)), this, SLOT(linkClicked(const QUrl&)));

	QTimer::singleShot(20, this, SLOT(loadContent()));
}


Menu::~Menu()
{
	// We passed ownership of m_pWebView to QGraphicsScene via addItem, so no need to delete it here
}


void Menu::loadContent()
{
	// Note that loading any HTML content in a QWebView will leave alleged memory leaks because QtWebKit
	// keeps caches in memory for a long time (http://lists.webkit.org/pipermail/webkit-qt/2012-March/002535.html)
	// which may then be recognized as memory leaks by debugging tools (e.g. _CrtDumpMemoryLeaks).
	m_pWebView->load(QUrl::fromLocalFile(QFileInfo("../../../tutorialContent_crossplatform/Menu/index.html").absoluteFilePath()));

	// To trigger the linkClicked signal
	m_pWebView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}


void Menu::linkClicked(const QUrl& url)
{
	if(url.host().contains("metaio.com"))
	{
		QDesktopServices::openUrl(url);
		return;
	}

	QUrlQuery urlQuery(url); 

	if(!urlQuery.hasQueryItem("startTutorialID"))
	{
		m_pWebView->load(url);
		return;
	}

	const QString tutorialName = urlQuery.queryItemValue("startTutorialID");

	if(url.scheme().toLower() == "metaiosdkexample")
		m_pCallback->startTutorial(tutorialName);
	else if(url.scheme().toLower() == "metaiosdkexamplearel")
		m_pCallback->startTutorialAREL(tutorialName);
	else
	{
		m_pWebView->load(url);
		return;
	}
}
