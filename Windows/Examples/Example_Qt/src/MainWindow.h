#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include <QVBoxLayout>
#include <QWidget>
#include <QWebView>

class TutorialBase;
class TutorialBaseAREL;
#include "Menu.h"

#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
class QGraphicsView;
class QBoxLayout;
QT_END_NAMESPACE


class MainWindow : public QMainWindow, public Ui::MainWindow, public Menu::TutorialSelectionCallback
{
	Q_OBJECT

public:
	MainWindow();
	virtual ~MainWindow();

	QBoxLayout* getButtonBar();

protected slots:
	void onQuitTutorialButtonClicked();

protected:
	void keyPressEvent(QKeyEvent *event);

	void quitTutorialIfAny();

	void startTutorial(QString tutorialName);

	void startTutorialAREL(QString tutorialName);

	TutorialBase*				m_pCurrentTutorial;
	TutorialBaseAREL*			m_pCurrentTutorialAREL;
	QGraphicsView*				m_pGraphicsView;
	Menu*						m_pMenu;
};


#endif
