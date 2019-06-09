#ifndef FRAMEWORKDEFINE_H
#define FRAMEWORKDEFINE_H

#define SCREEN_HEIGHT 224

#define SCREEN_WIDTH 256

#define SAFE_DELETE(p)       if(p) { delete (p);     (p)=0; }

#define SAFE_DELETE_ARRAY(p) if(p) { delete[] (p);   (p)=0; }

#define SAFE_RELEASE(p)      if(p) { (p)->Release(); (p)=0; }


#define VELOC_ITEM_X		1.0f
#define VELOC_ITEM_Y		4.0f
#define ACCEL_ITEM_Y		-0.03f

#define	GAMETITLE	"Ninja Gaiden"
#define	FRAME_RATE	60

#define	SPRITEHANDLE LPD3DXSPRITE

#define DIRECTINPUT_HEADER_VERSION  0x0800

#define DIRECTINPUT_VERSION         DIRECTINPUT_HEADER_VERSION

#ifndef __CSOUNDSWITCH__
#define __CSOUNDSWITCH__
struct CSoundSwitch
{
	static bool IsExit;
	static bool IsMute;
};
#endif // __CSOUNDSWITCH__

#endif