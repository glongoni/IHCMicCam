#include "ihcmiccam.h"

IHCMicCam::IHCMicCam(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

IHCMicCam::~IHCMicCam()
{

}

void IHCMicCam::close()
{
	exit(0);
}