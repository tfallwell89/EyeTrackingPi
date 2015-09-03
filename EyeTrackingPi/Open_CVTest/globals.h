/*added by Thomas Fallwell 02/28/15
*this class is for mapping eyes to mouse
*/
#ifndef GLOBALS_H
#define GLOBALS_H
//#include "calibration.h"

class Gaze {
public:
	int MIN_X;
	int MIN_Y;
	int MAX_X;
	int MAX_Y;
};

struct GazePoint {
	int X = -1; int Y = -1; //init as -1
};

struct CursorSpeed {
	double X = 1; double Y = 1;
};

struct MissCount {
	int X_MAX = 0; int X_MIN = 0; int Y_MAX = 0; int Y_MIN = 0;
};
extern MissCount missCount;
extern GazePoint cursorPos;
extern GazePoint prevCursorPos;
extern Gaze gaze;
extern CursorSpeed cursor_speed;
extern int number_of_columns;
extern int number_of_rows;
#endif