#include "ihcmiccam.h"
#include "QVideoIPCam.h"
#include "IPCamPlayer.h"
#include "ConfigurationAudioModel.h"
#include "QAudioMic.h"
#include "QAudioNet.h"
#include "QAudioPlayer.h"
#include "CameraHandler.h"

#include <QMediaPlayer.h>

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(QMediaPlayer);
	
	QApplication a(argc, argv);
	
	//Mostra a janela principal
	IHCMicCam w;
	w.show();

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

	//Isso tem que ser parametro (IP da c�mera do usu�rio remoto)
	camModel->setIP("143.54.12.154");

	//Cria o stream e o player
	QVideoIPCam* ipcam = new QVideoIPCam(camModel, 0);
	IPCamPlayer* player = new IPCamPlayer(ipcam);

	//Show e play tem que ser quando a reuni�o inicia
	player->show();
	player->play();

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
		m->startSend("143.54.12.139", 12000 + index);
		audioMics.append(m);
		index++;
		if(index > 2)
			break;
	}

	//Inicia 3 recep��es de streams de �udio e cria 3 players de �udio
	QList<QAudioPlayer*> audioPlayers;
	for(int i = 0; i < 3; i++)
	{
		QAudioNet* aNet = new QAudioNet();
		aNet->setPort(12000 + i);
		QAudioPlayer* aPlayer = new QAudioPlayer(aNet, i);
		aPlayer->play();
		audioPlayers.append(aPlayer);
	}

	CameraHandler* camHandler = new CameraHandler("143.54.12.154", audioPlayers);


	return a.exec();
}
