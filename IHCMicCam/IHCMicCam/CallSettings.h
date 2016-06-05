#ifndef CALLSETTINGS_H
#define CALLSETTINGS_H

#include "ui_CallSettings.h"

class CallSettings : public QObject
{
	Q_OBJECT

public:
	CallSettings();
	~CallSettings();

private:
	Ui::callSettings ui;


};

#endif // CALLSETTINGS_H
