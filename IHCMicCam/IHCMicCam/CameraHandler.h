#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <QTimer>

class QAudioPlayer;

class CameraHandler : QObject
{
	Q_OBJECT

public:
	CameraHandler(QString cameraIP, QList<QAudioPlayer*> audioPlayers, QWidget *parent = 0);
	~CameraHandler();

private:
	QList<QAudioPlayer*> audioPlayers;
	QAudioPlayer* currentPlayer;
	QTimer audioCheckTimer;
	QString cameraIP;
public slots:
	void changeCameraPreset();
	
	
};

#endif // CAMERAHANDLER_H
