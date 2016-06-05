#include "ihcmiccam.h"

IHCMicCam::IHCMicCam(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	settingsWindow = new CallSettings();

	connect(ui.callSettingsButton, SIGNAL(clicked()), this, SLOT(openSettings()));
}

IHCMicCam::~IHCMicCam()
{

}

void IHCMicCam::openSettings()
{
	exit(0);
}