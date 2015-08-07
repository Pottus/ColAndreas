
#ifdef WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <pwd.h>
#endif

#include <cstdarg>

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>

#include <Main.hpp>
#include <QtMainWindow.hpp>

#include <ui_MainWindow.h>
#include <ui_License.h>
#include <ui_Settings.h>
#include <ui_Working.h>

MainWindow *mainWindow = NULL;

MainWindow::MainWindow() : QMainWindow()
{
	// Initialize MainWindow
	
	ui = new Ui::MainWindow();
	ui->setupUi(this);
	
	this->setWindowIcon(QIcon(":/icon.ico"));
	this->setWindowTitle("ColAndreas Wizard - " CA_VERSION);
	
	ui->headerImage->setPixmap(QPixmap(":/header.gif"));
	ui->statusBar->hide();
	ui->buttonBack->hide();
	ui->buttonNext->setEnabled(false);
	
	QPalette headerPalette(palette());
	headerPalette.setColor(QPalette::Background, Qt::black);
	ui->headerWidget->setAutoFillBackground(true);
	ui->headerWidget->setPalette(headerPalette);
	
	this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,	this->size(), qApp->desktop()->availableGeometry()));
	
	// Initialize licenseWidget
	
	licenseWidget = new QWidget(this);
	ui_license = new Ui::licenseWidget();
	ui_license->setupUi(licenseWidget);
	
	QFile licenseFile(":/license.html");
	licenseFile.open(QIODevice::ReadOnly);
	ui_license->licenseContainer->setHtml(licenseFile.readAll());
	
	ui->contentLayout->addWidget(licenseWidget);
	
	// Initialize settingsWidget
	
	settingsWidget = new QWidget(this);
	ui_settings = new Ui::settingsWidget();
	ui_settings->setupUi(settingsWidget);
	settingsWidget->hide();
	
	#ifdef WIN32
	HKEY key;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Rockstar Games\\GTA San Andreas\\Installation", REG_OPTION_OPEN_LINK, KEY_QUERY_VALUE, &key) == ERROR_SUCCESS)
	{
		DWORD size = MAX_PATH;
		char path[MAX_PATH];

		if(RegQueryValueEx(key, "ExePath", NULL, NULL, (BYTE*) path, &size) == ERROR_SUCCESS)
		{
			gamePath.append(path);
			gamePath.remove('"');
			
			if(gamePath.endsWith('/') || gamePath.endsWith('\\'))
			{
				gamePath.chop(1);
			}
			
			if(!QFile::exists(gamePath + "/gta_sa.exe"))
			{
				gamePath = "";
			}
		}

		RegCloseKey(key);
	}
	ui_settings->gamePathDisplay->setText(gamePath);
	#endif
	
	ui->contentLayout->addWidget(settingsWidget);
	
	// Initialize workWidget
	
	workWidget = new QWidget(this);
	ui_work = new Ui::workWidget();
	ui_work->setupUi(workWidget);
	workWidget->hide();
	ui->contentLayout->addWidget(workWidget);
	
	// Initialize timer
	
	threadTimer = new QTimer(this);
	threadTimer->setInterval(250);
	threadTimer->setSingleShot(false);
	
	// Set-up signals
	
	connect(ui->buttonNext, &QPushButton::released, this, &MainWindow::next);
	connect(ui->buttonBack, &QPushButton::released, this, &MainWindow::back);
	connect(ui->buttonCancel, &QPushButton::released, this, &MainWindow::cancel);
	
	connect(threadTimer, &QTimer::timeout, this, &MainWindow::updateThread);
	connect(ui_license->licenseAcceptRadio, &QRadioButton::toggled, this, &MainWindow::acceptsLicense);
	connect(ui_settings->gameBrowseButton, &QPushButton::released, this, &MainWindow::browseGame);
	connect(ui_settings->outputBrowseButton, &QPushButton::released, this, &MainWindow::browseOutput);
}

MainWindow::~MainWindow()
{ }

void MainWindow::beginWork()
{
	addFormattedMessage("Starting worker thread:\n\tGameDir = \"%s\"\n\tOutputFile = \"%s\"\n\tSAMPObjects = %s\n\tCustomObjects = %s\n\n", gamePath.toLocal8Bit().data(), outputPath.toLocal8Bit().data(), (ui_settings->sampObjectsBox->isChecked() ? "true" : "false"), (ui_settings->customObjectsBox->isChecked() ? "true" : "false"));
	updateThread();
	
	threadTimer->start();
	workerThread = new std::thread(doWork, gamePath.toStdString(), outputPath.toStdString(), ui_settings->sampObjectsBox->isChecked(), ui_settings->customObjectsBox->isChecked());
}

void MainWindow::addMessage(const char *msg)
{
	std::lock_guard<std::mutex> lock(workerMutex);
	
	workMessages.push(new std::string(msg));
}

void MainWindow::addFormattedMessage(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	
	vsnprintf(str, sizeof(str), format, args);
	workMessages.push(new std::string(str));
	
	va_end(args);
}

void MainWindow::setProgress(int progress)
{
	std::lock_guard<std::mutex> lock(workerMutex);
	
	workProgress = progress;
}

void MainWindow::reportProgress(int progress, const char* msg)
{
	std::lock_guard<std::mutex> lock(workerMutex);
	
	workProgress += progress;
	workMessages.push(new std::string(msg));
}

void MainWindow::updateThread()
{
	if(workerMutex.try_lock())
	{
		if(workProgress)
		{
			ui_work->workProgress->setMaximum(100);
			ui_work->workProgress->setValue(workProgress);
		}
			
		while(!workMessages.empty())
		{
			std::string *s = workMessages.front();
		
			ui_work->workMessages->appendPlainText(s->c_str());
			delete s;

			workMessages.pop();
		}
		
		if(workProgress == 100)
		{
			ui->buttonNext->hide();
			ui->buttonCancel->setText(tr("Quit"));
			
			threadTimer->stop();
			
			workerThread->join();
			delete workerThread;
			workerThread = NULL;
		}
		
		workerMutex.unlock();
	}
}

void MainWindow::hideAll()
{
	licenseWidget->hide();
	settingsWidget->hide();
}

void MainWindow::showCurrent()
{
	ui->buttonBack->show();
	ui->buttonNext->setText(tr("Next"));
	
	switch(currentPage)
	{
		case 0:
		{
			licenseWidget->show();
			ui->buttonBack->hide();
			break;
		}
		
		case 1:
		{
			settingsWidget->show();
			ui->buttonNext->setText(tr("Start"));
			break;
		}
		
		case 2:
		{
			workWidget->show();
			ui->buttonBack->hide();
			ui->buttonNext->setEnabled(false);
			beginWork();
			break;
		}
	}
}

void MainWindow::next()
{
	if(currentPage == 1)
	{
		if(!gamePath.length())
		{
			QMessageBox::critical(this, tr("ERROR"), tr("Please select your GTA:SA installation directory."));
			return;
		}
		
		if(!outputPath.length())
		{
			QMessageBox::critical(this, tr("ERROR"), tr("Please choose where to save the ColAndreas file."));
			return;
		}
	}
	
	hideAll();
	currentPage++;
	showCurrent();
}

void MainWindow::back()
{
	hideAll();
	currentPage--;
	showCurrent();
}

void MainWindow::cancel()
{
	QApplication::exit();
}

void MainWindow::acceptsLicense(bool accepts)
{
	if(accepts)
	{
		ui->buttonNext->setEnabled(true);
	}
	else
	{
		ui->buttonNext->setEnabled(false);
	}
}

void MainWindow::browseGame()
{
	#ifdef WIN32
	QString selectedDir = QFileDialog::getExistingDirectory(this, tr("Choose your GTA:SA installation folder."), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	#else
	const char *userHome = NULL;
	if ((userHome = getenv("HOME")) == NULL) 
	{
		passwd *userPasswd = getpwuid(getuid());
		if(userPasswd) userHome = userPasswd->pw_dir;
	}	
	QString selectedDir = QFileDialog::getExistingDirectory(this, tr("Choose your GTA:SA installation folder."), (userHome ? userHome : "/home"), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	#endif
	
	if(selectedDir.length())
	{
		if(selectedDir.endsWith('/') || selectedDir.endsWith('\\'))
		{
			selectedDir.chop(1);
		}
		
		if(!QFile::exists(selectedDir + "/gta_sa.exe"))
		{
			QMessageBox::critical(this, tr("ERROR"), tr("The folder you selected doesn't seem to be a valid GTA:SA installation."));
		}
		else
		{
			gamePath = selectedDir;
			ui_settings->gamePathDisplay->setText(gamePath);
		}
	}
}

void MainWindow::browseOutput()
{
	#ifdef WIN32
	QString selectedFile = QFileDialog::getSaveFileName(this, tr("Choose where to save the ColAndreas file."), QDir::homePath(), tr("ColAndreas database file (*.cadb)"));
	#else
	const char *userHome = NULL;
	if ((userHome = getenv("HOME")) == NULL) 
	{
		passwd *userPasswd = getpwuid(getuid());
		if(userPasswd) userHome = userPasswd->pw_dir;
	}
	QString selectedFile = QFileDialog::getSaveFileName(this, tr("Choose where to save the ColAndreas file."), (userHome ? userHome : "/home"), tr("ColAndreas database file (*.cadb)"));
	#endif
	
	if(selectedFile.length())
	{
		outputPath = selectedFile;
		ui_settings->outputPathDisplay->setText(outputPath);
	}
}
