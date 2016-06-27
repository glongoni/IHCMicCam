#include "ihcmiccam.h"

#include "QVideoIPCam.h"
#include "IPCamPlayer.h"

#include "ConfigurationAudioModel.h"
#include "QAudioMic.h"
#include "QAudioNet.h"
#include "QAudioPlayer.h"
#include "CameraHandler.h"
#include "CallSettings.h"

#include <QMessageBox>


IHCMicCam::IHCMicCam(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	settingsWindow = new CallSettings();

	connect(ui.callSettingsButton, SIGNAL(clicked()), this, SLOT(openSettings()));
	connect(ui.startCallButton, SIGNAL(clicked()), this, SLOT(startCall()));
}

IHCMicCam::~IHCMicCam()
{

}

void IHCMicCam::openSettings()
{
	settingsWindow->show();
}

void IHCMicCam::startCall()
{
	//Objeto com as configura��es de uma c�mera IP
	ConfigurationCameraIPModel* camModel = new ConfigurationCameraIPModel();
	
	//Isso � hardcoded mesmo tem que bater com as configura��es remotas da c�mera
	camModel->setBitRate(4000);
	camModel->setCameraIPId(0);
	camModel->setFrameRate(30);
	camModel->setIFrameInterval(1);
	camModel->setImageSize("1920,1080");
	camModel->setMulticastIP("224.100.100.102");
	camModel->setPort(10000);
	camModel->setStreamType(ConfigurationCameraIPModel::StreamType::UNICAST);

	QString lol = settingsWindow->getPeerCamIP();

	//Isso tem que ser parametro (IP da c�mera do usu�rio remoto)
	camModel->setIP(settingsWindow->getPeerCamIP());

	//Cria o stream e o player
	QVideoIPCam* ipcam = new QVideoIPCam(camModel, 0);
	camPlayer = new IPCamPlayer(ipcam);

	//Inicia exibi��o
	camPlayer->show();
	camPlayer->play();


	//Audio model tem a lista de microfones conectados
	ConfigurationAudioModel* audioModel = new ConfigurationAudioModel(-1);
	audioModel->setDefault();

	//Cria um stream para cada microfone e come�a a transmitir (M�ximo 3 microfones)
	QList<QAudioMic*> audioMics;
	int index = 0;
	foreach(QAudioDevice* mic, (QList<QAudioDevice*>) *(audioModel->getAudioDevicesList()))
	{
		QAudioMic* m = new QAudioMic(mic);
		m->start();
		m->setPort(12000 + index);
		m->startSend(settingsWindow->getPeerIP(), 12000 + index);
		m->setInputVolume(50);
		audioMics.append(m);
		index++;
	}

	//Inicia 3 recep��es de streams de �udio e cria 3 players de �udio
	for(int i = 0; i < 3; i++)
	{
		QAudioNet* aNet = new QAudioNet();
		aNet->setPort(12000 + i);
		QAudioPlayer* aPlayer = new QAudioPlayer(aNet, i + 1);
		aPlayer->play();
		audioPlayers.append(aPlayer);
		aPlayer->setOutputVolume(30);
	}

	camHandler = new CameraHandler(settingsWindow->getPeerCamIP(), audioPlayers);

}