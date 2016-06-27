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
	//Objeto com as configurações de uma câmera IP
	ConfigurationCameraIPModel* camModel = new ConfigurationCameraIPModel();
	
	//Isso é hardcoded mesmo tem que bater com as configurações remotas da câmera
	camModel->setBitRate(4000);
	camModel->setCameraIPId(0);
	camModel->setFrameRate(30);
	camModel->setIFrameInterval(1);
	camModel->setImageSize("1920,1080");
	camModel->setMulticastIP("224.100.100.102");
	camModel->setPort(10000);
	camModel->setStreamType(ConfigurationCameraIPModel::StreamType::UNICAST);

	QString lol = settingsWindow->getPeerCamIP();

	//Isso tem que ser parametro (IP da câmera do usuário remoto)
	camModel->setIP(settingsWindow->getPeerCamIP());

	//Cria o stream e o player
	QVideoIPCam* ipcam = new QVideoIPCam(camModel, 0);
	camPlayer = new IPCamPlayer(ipcam);

	//Inicia exibição
	camPlayer->show();
	camPlayer->play();


	//Audio model tem a lista de microfones conectados
	ConfigurationAudioModel* audioModel = new ConfigurationAudioModel(-1);
	audioModel->setDefault();

	//Cria um stream para cada microfone e começa a transmitir (Máximo 3 microfones)
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

	//Inicia 3 recepções de streams de áudio e cria 3 players de áudio
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