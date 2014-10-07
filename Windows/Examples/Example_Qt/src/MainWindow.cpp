#include "MainWindow.h"
#include "TutorialBase.h"
#include "TutorialBaseAREL.h"

// Non-AREL tutorials are in separate classes
#include "TutorialHelloWorld.h"
#include "TutorialContentTypes.h"
#include "TutorialTrackingSamples.h"
#include "TutorialDynamicModels.h"
#include "TutorialQRCodeReader.h"
#include "TutorialInstantTracking.h"
#include "TutorialEdgeBasedInitialization.h"
#include "TutorialFaceTracking.h"
#include "TutorialDynamicLighting.h"
#include "TutorialCustomShading.h"
#include "TutorialStereoRendering.h"
#include "TutorialAdvancedRendering.h"

#include <QtGui>
#include <QGraphicsScene>
#include <QGLWidget>
#include <QSyntaxHighlighter>
#include <QTabWidget>
#include <QFile>
#include <QWebInspector>
#include <QMessageBox>



MainWindow::MainWindow() :
	m_pCurrentTutorial(0),
	m_pCurrentTutorialAREL(0)
{
	setupUi(this);

	quitTutorialButton->setVisible(false);

	QObject::connect(quitTutorialButton, SIGNAL(clicked()), this, SLOT(onQuitTutorialButtonClicked()));

	m_pMenu = new Menu(this, this);

	// Init the main view for the scene using OpenGL
	QGLWidget *glWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers));
	m_pGraphicsView = graphicsView;
	m_pGraphicsView->setScene(m_pMenu);
	m_pGraphicsView->setViewport(glWidget);
	m_pGraphicsView->setFrameShape(QFrame::NoFrame);

	// Do not show context menu in web view
	m_pGraphicsView->setContextMenuPolicy(Qt::NoContextMenu);

}


MainWindow::~MainWindow()
{
	m_pGraphicsView->setScene(0);
	delete m_pCurrentTutorial;
	m_pCurrentTutorial = 0;
	delete m_pCurrentTutorialAREL;
	m_pCurrentTutorialAREL = 0;

	delete m_pMenu;
	m_pMenu = 0;

	delete m_pGraphicsView;
	m_pGraphicsView = 0;
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
	if(e->key() == Qt::Key_Escape)
		close();
	else
		QWidget::keyPressEvent(e);
}


QBoxLayout* MainWindow::getButtonBar()
{
	return buttonLayout;
}


void MainWindow::onQuitTutorialButtonClicked()
{
	quitTutorialIfAny();
}


void MainWindow::quitTutorialIfAny()
{
	if(!m_pCurrentTutorial && !m_pCurrentTutorialAREL)
		return;

	quitTutorialButton->setVisible(false);

	// Switch back to displaying the menu web view
	m_pGraphicsView->setScene(m_pMenu);

	delete m_pCurrentTutorial;
	m_pCurrentTutorial = 0;

	delete m_pCurrentTutorialAREL;
	m_pCurrentTutorialAREL = 0;
}


void MainWindow::startTutorial(QString tutorialName)
{
	quitTutorialIfAny();

	qDebug("Starting non-AREL tutorial %s", tutorialName.toUtf8().constData());

	TutorialBase *tutorialImpl = 0;

	quitTutorialButton->setVisible(true);
	
	if (tutorialName == "HelloWorld") 
	{
		tutorialImpl = new TutorialHelloWorld();
	}
	else if (tutorialName == "ContentTypes")
	{
		tutorialImpl = new TutorialContentTypes(this);
	}
	else if (tutorialName == "TrackingSamples")
	{
		tutorialImpl = new TutorialTrackingSamples(this);
	}
	else if (tutorialName == "DynamicModels")
	{
		tutorialImpl = new TutorialDynamicModels();
	}
	else if (tutorialName == "QRCodeReader")
	{
		tutorialImpl = new TutorialQRCodeReader(this);
	}
	else if (tutorialName == "InstantTracking")
	{
		tutorialImpl = new TutorialInstantTracking(this);
	}
	else if (tutorialName == "EdgeBasedInitialization")
	{
		tutorialImpl = new TutorialEdgeBasedInitialization(this);
	}
	else if (tutorialName == "FaceTracking")
	{
		tutorialImpl = new TutorialFaceTracking();
	}
	else if (tutorialName == "DynamicLighting")
	{
		tutorialImpl = new TutorialDynamicLighting(this);
	}
	else if (tutorialName == "CustomShading")
	{
		tutorialImpl = new TutorialCustomShading(this);
	}
	else if (tutorialName == "StereoRendering")
	{
		tutorialImpl = new TutorialStereoRendering();
	}
	else if (tutorialName == "AdvancedRendering")
	{
		tutorialImpl = new TutorialAdvancedRendering();
	}
	else
	{
		QMessageBox::critical(
			this,
			"Tutorial not available",
			"Sorry, this tutorial is not available on Windows");
		quitTutorialButton->setVisible(false);
		return;
	}
	
	m_pGraphicsView->setScene(tutorialImpl);

	m_pCurrentTutorial = tutorialImpl;
}


void MainWindow::startTutorialAREL(QString tutorialName)
{
	qDebug("Starting AREL tutorial %s", tutorialName.toUtf8().constData());

	if(tutorialName == "LocationBasedAR" || tutorialName == "InteractiveFurniture" || tutorialName == "VisualSearch")
	{
		QMessageBox::critical(
			this,
			"Tutorial not available",
			"Sorry, this tutorial is not available on Windows");
		return;
	}

	quitTutorialIfAny();

	quitTutorialButton->setVisible(true);

	TutorialBaseAREL *tutorialImpl = new TutorialBaseAREL(this, tutorialName);

	m_pGraphicsView->setScene(tutorialImpl);

	m_pCurrentTutorialAREL = tutorialImpl;
}