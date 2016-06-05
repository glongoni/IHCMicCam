#ifndef IHCMICCAM_H
#define IHCMICCAM_H

#include <QtWidgets/QMainWindow>
#include <CallSettings.h>
#include "ui_ihcmiccam.h"

class IHCMicCam : public QMainWindow
{
	Q_OBJECT

public:
	IHCMicCam(QWidget *parent = 0);
	~IHCMicCam();

private:
	Ui::IHCMicCamClass ui;
	CallSettings* settingsWindow;

public slots:
	void openSettings();

};

#endif // IHCMICCAM_H
