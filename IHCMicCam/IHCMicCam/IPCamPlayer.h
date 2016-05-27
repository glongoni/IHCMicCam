#ifndef IPCAMPLAYER_H
#define IPCAMPLAYER_H

#include "QVideoPlayer.h"
#include "QVideoIPCam.h"

class IPCamPlayer : public QVideoPlayer
{
	Q_OBJECT

public:
	IPCamPlayer(QVideoIPCam* stream);
	~IPCamPlayer();



};

#endif // IPCAMPLAYER_H
