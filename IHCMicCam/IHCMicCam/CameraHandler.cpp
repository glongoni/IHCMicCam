#include <CameraHandler.h>
#include "QAudioPlayer.h"
#include "Tools.h"
#include <QDebug>

CameraHandler::CameraHandler(QString cameraIP, QList<QAudioPlayer*> audioPlayers, QWidget *parent) : audioPlayers(audioPlayers), cameraIP(cameraIP)
{
	connect(&audioCheckTimer, SIGNAL(timeout()), this, SLOT(changeCameraPreset()));
	audioCheckTimer.start(10);
	
	if(!audioPlayers.isEmpty())
	{
		currentPlayer = audioPlayers.first();
	}
	Tools::setCameraIPParameter(Tools::CameraIPMessageType::GET, this->cameraIP, "command/presetposition.cgi", "PresetCall", QString::number(currentPlayer->getId()) + ",24");
}

CameraHandler::~CameraHandler()
{

}

void CameraHandler::changeCameraPreset()
{ 
	qDebug() << "Current: " << currentPlayer->getId();
	foreach(QAudioPlayer* ap, audioPlayers)
	{
		qDebug() << "AP" << ap->getId() << ":" << ap->getVU();
		if(ap->getVU() > currentPlayer->getVU() && ap->getVU() > 150 && ap->getVU() < 5000)
		{
			qDebug() << "AP changed" << ap->getId();
			Tools::setCameraIPParameter(Tools::CameraIPMessageType::GET, this->cameraIP, "command/presetposition.cgi", "PresetCall", QString::number(ap->getId()) + ",24");
			currentPlayer = ap;
		}
	}
}
