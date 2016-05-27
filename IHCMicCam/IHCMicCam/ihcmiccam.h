#ifndef IHCMICCAM_H
#define IHCMICCAM_H

#include <QtWidgets/QMainWindow>
#include "ui_ihcmiccam.h"

class IHCMicCam : public QMainWindow
{
	Q_OBJECT

public:
	IHCMicCam(QWidget *parent = 0);
	~IHCMicCam();

private:
	Ui::IHCMicCamClass ui;

public slots:
	void close();

};

#endif // IHCMICCAM_H
