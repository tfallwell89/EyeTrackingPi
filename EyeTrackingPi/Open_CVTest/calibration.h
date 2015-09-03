#ifndef CALIBRATION_H
#define CALIBRATION_H
//added by Thomas Fallwell 02/28/15
class Calibration {
public:

	//for callibration
	int XMIN;
	int XMAX;
	int YMIN;
	int YMAX;
	//END ADDED


	Calibration();
	~Calibration();
	//unsigned int calcOffset(void* data);
	int calcOffset();
	void calibrate();
	void sleepcp(int, char*);
	void checkMiss(int, int);
private:
	int* checkCalibration(int, int, int);
};


extern Calibration cal;
#endif