#include "ihcmiccam.h"


#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(QMediaPlayer);
	
	QApplication a(argc, argv);
	
	//Mostra a janela principal
	IHCMicCam w;
	w.show();

	
	

	return a.exec();
}
