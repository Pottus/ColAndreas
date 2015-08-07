#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#ifdef WIN32
	#include <QtPlugin>
	Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#endif

#include <QtMainWindow.hpp>
#include <BuildManager.h>

char str[512];

int main(int argc, char **argv) 
{
	QApplication app(argc, argv);
	
	QSplashScreen splash(QPixmap(":/splash.gif"));
	splash.show();
	
	mainWindow = new MainWindow();
	
	QTimer::singleShot(3000, mainWindow, 
		[&]()
		{
			splash.finish(mainWindow);
			mainWindow->show();
		}
	);
	
	return app.exec();
}

void doWork(std::string gamePath, std::string outputPath, bool SAMPObjs, bool CustomObjs)
{
	BuildManager *thisBuild = new BuildManager(gamePath, outputPath, SAMPObjs, CustomObjs);
	
	mainWindow->reportProgress(1, "Processing: Image files (.img)");
	thisBuild->ExtractImageFiles();
	mainWindow->reportProgress(15, "Done.\n");

	mainWindow->reportProgress(1, "Processing: Collision files (.col)");
	thisBuild->ExtractCollisionFiles();
	mainWindow->reportProgress(15, "Done.\n");

	mainWindow->reportProgress(1, "Processing: Item placement files (.ipl)");
	thisBuild->ExtractItemPlacementFiles();
	mainWindow->reportProgress(15, "Done.\n");

	mainWindow->reportProgress(1, "Processing: Item definition files (.ide)");
	thisBuild->ExtractItemDefinitionFiles();
	mainWindow->reportProgress(15, "Done.\n");

	mainWindow->reportProgress(1, "Preparing database structures, this may take some time.");
	thisBuild->PrepareDatabaseStructures();
	mainWindow->reportProgress(15, "Done.\n");

	mainWindow->reportProgress(1, "Writing the database file.");
	thisBuild->WriteBinaryFile(outputPath.c_str());
	mainWindow->reportProgress(15, "Done.\n");
	
	mainWindow->addMessage("All done!");
	mainWindow->setProgress(100);
}
