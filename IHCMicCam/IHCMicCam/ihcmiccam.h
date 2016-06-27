#ifndef IHCMICCAM_H
#define IHCMICCAM_H

#include <QtWidgets/QMainWindow>
#include "ui_ihcmiccam.h"
#include <QList>

class CallSettings;
class IPCamPlayer;
class QAudioPlayer;
class CameraHandler;


class IHCMicCam : public QMainWindow
{
	Q_OBJECT

public:
	IHCMicCam(QWidget *parent = 0);
	~IHCMicCam();

	IPCamPlayer* camPlayer;
	QList<QAudioPlayer*> audioPlayers;
	CameraHandler* camHandler;
	

private:
	Ui::IHCMicCamClass ui;
	CallSettings* settingsWindow;

public slots:
	void openSettings();
	void startCall();

};

#endif // IHCMICCAM_H
