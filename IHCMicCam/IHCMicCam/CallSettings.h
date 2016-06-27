#ifndef CALLSETTINGS_H
#define CALLSETTINGS_H

#include "ui_CallSettings.h"

class CallSettings : public QWidget
{
	Q_OBJECT

public:
	CallSettings();
	~CallSettings();

	QString CallSettings::getPeerIP();
	QString CallSettings::getPeerCamIP();


private:
	Ui::callSettings ui;

	QString camIP;
	QString peerIP;

public slots:
	void save();


};

#endif // CALLSETTINGS_H
