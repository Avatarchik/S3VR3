#include <QApplication>

#include <metaioSDK/IMetaioSDK.h>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
	#if _DEBUG
		// Do not print memory leaks at end of program (QtWebKit causes some invalid leaks, see Menu class)
		_CrtSetDbgFlag(_crtDbgFlag &~ _CRTDBG_LEAK_CHECK_DF);
	#endif

	QApplication app(argc, argv);

	app.setApplicationName("Example_Qt");

	MainWindow window;
	window.show();
	int res = app.exec();

	metaio::IMetaioSDK::shutdownLibrary();

	return res;
}