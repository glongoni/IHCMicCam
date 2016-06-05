#include <CameraHandler.h>
#include "QAudioPlayer.h"
#include "Tools.h"

CameraHandler::CameraHandler(QString cameraIP, QList<QAudioPlayer*> audioPlayers, QWidget *parent) : audioPlayers(audioPlayers), cameraIP(cameraIP)
{
	connect(&audioCheckTimer, SIGNAL(timeout()), this, SLOT(changeCameraPreset()));
	audioCheckTimer.start(1000);
	
	if(!audioPlayers.isEmpty())
	{
		currentPlayer = audioPlayers.first();
	}
}

CameraHandler::~CameraHandler()
{

}

void CameraHandler::changeCameraPreset()
{
	foreach(QAudioPlayer* ap, audioPlayers)
	{
		if(ap->getVU() > currentPlayer->getVU())
		{
			Tools::setCameraIPParameter(Tools::CameraIPMessageType::GET, this->cameraIP, "presetposition.cgi", "PresetCall", QString::number(ap->getId()) + ",24");
		}
	}
}
