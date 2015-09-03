#ifndef MOUSE_H
#define MOUSE_H
/*added by Thomas Fallwell 02/28/15
*this class is for mapping eyes to mouse
*/
class Mouse {
public:
	Mouse();
	~Mouse();
	void analogMouse(int, int);
	void directMapMouse(int, int);
	void checkCalibration(int, int);
	GazePoint* sleepcp(int, int, int);
};

extern bool threadStarted;
unsigned int __stdcall accelerate(void* data);

#endif