#include "CallSettings.h"

CallSettings::CallSettings()
{
	ui.setupUi(this);

	this->camIP = ui.camAddressLineEdit->text();
	this->peerIP = ui.pcAddressLineEdit->text();

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(save()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}
CallSettings::~CallSettings()
{

}

void CallSettings::save()
{
	this->camIP = ui.camAddressLineEdit->text();
	this->peerIP = ui.pcAddressLineEdit->text();
	close();
}

QString CallSettings::getPeerIP()
{
	return peerIP;
}

QString CallSettings::getPeerCamIP()
{
	return camIP;
}