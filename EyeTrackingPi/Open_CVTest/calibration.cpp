/*
Create by Thomas Fallwell 2/28/2015
For calibration of gaze points
*/
#include "calibration.h"

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

#include <Windows.h>
#include <WinDef.h>
#include <process.h>
#include <time.h>
#include "findEyeCenter.h"
#include "globals.h"
#include "main.h"

using namespace std;

//Gobal variables
Calibration cal;
Gaze gaze;
int number_of_columns = 6;
int number_of_rows = 3;

void shortBeep() {
	cout << '\a' << endl;
}

Calibration::Calibration() {
	
}

Calibration::~Calibration() {

}

void Calibration::checkMiss(int x, int y) {

	if (x > ::gaze.MAX_X) ::missCount.X_MAX++;
	if (x < ::gaze.MIN_X) ::missCount.X_MIN++;
	if (y > ::gaze.MAX_Y) ::missCount.Y_MAX++;
	if (y < ::gaze.MAX_Y) ::missCount.Y_MAX++;

	if ((::missCount.X_MAX % 10) == 0) {
		::gaze.MAX_X++;
		::gaze.MIN_X++;
	}
	if ((::missCount.X_MIN % 10) == 0) {
		::gaze.MIN_X--;
		::gaze.MAX_X--;
	}
	if ((::missCount.Y_MAX % 10) == 0) {
		::gaze.MAX_Y++;
		::gaze.MIN_Y++;
	}
	if ((::missCount.Y_MIN % 10) == 0) {
		::gaze.MIN_Y--;
		::gaze.MAX_Y--;
	}
}

void Calibration::sleepcp(int milliseconds, char* direction) {

	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	int i = 0, sum = 0;

	//while waiting for next calibration point to be drawn
	//capture summate gaze points
	while (clock() < time_end) {
		sum += captureFace(direction);
		i++;
	}
	if (i == 0) i = 1; //don't divide by 0
	//average where each min and max value are
	if (strcmp(direction, "left") == 0) {
		::gaze.MIN_X = sum / i;
	}
	else if (strcmp(direction,"top") == 0) {
		::gaze.MAX_Y = sum / i;
	}
	else if (strcmp(direction, "right") == 0) {
		::gaze.MAX_X = sum / i;
	}
	else if (strcmp(direction, "bottom") == 0) {
		::gaze.MIN_Y = sum / i;
	}
}

int* Calibration::checkCalibration(int min, int max, int range) {

	while ((max - min) < range) {
		max++;
		if ((max - min) < range)
			min--;
	}

	while ((max - min) > range) {
		max--;
		if ((max - min) > range)
			min++;
	}
	int arr[] = { min, max };

	return arr;
}

void Calibration::calibrate() {

	//draw calibration point and wait
	shortBeep();
	sleepcp(4000, "left");
	//top
	shortBeep();
	sleepcp(4000, "top");
	//draw 40 px circle on right side of screen
	shortBeep();
	sleepcp(4000, "right");
	//bottom
	shortBeep();
	sleepcp(4000, "bottom");

	//two beeps to signal that calibration is done
	shortBeep();
	shortBeep();
	//adjust calibration if points are way off
	int *x = checkCalibration(::gaze.MIN_X, ::gaze.MAX_X, ::number_of_columns);
	::gaze.MIN_X = *(x++);
	::gaze.MAX_X = *x;

	int *y = checkCalibration(::gaze.MIN_Y, ::gaze.MAX_Y, ::number_of_rows);
	::gaze.MIN_Y = *(y++);
	::gaze.MAX_Y = *y;
}

