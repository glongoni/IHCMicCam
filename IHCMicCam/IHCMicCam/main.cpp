#include "ihcmiccam.h"
#include "QVideoIPCam.h"
#include "IPCamPlayer.h"

#include <QMediaPlayer.h>

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(QMediaPlayer);
	
	QApplication a(argc, argv);
	IHCMicCam w;
	w.show();

	ConfigurationCameraIPModel* model = new ConfigurationCameraIPModel();
	model->setBitRate(4000);
	model->setCameraIPId(0);
	model->setFrameRate(30);
	model->setIFrameInterval(1);
	model->setImageSize("1920,1080");
	model->setIP("143.54.12.154");
	model->setMulticastIP("224.100.100.102");
	model->setPort(10000);
	model->setStreamType(ConfigurationCameraIPModel::StreamType::UNICAST);
	QVideoIPCam* ipcam = new QVideoIPCam(model, 0);

	IPCamPlayer* player = new IPCamPlayer(ipcam);

	player->show();

	player->play();

	return a.exec();
}
