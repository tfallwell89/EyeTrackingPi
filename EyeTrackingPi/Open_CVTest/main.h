#ifndef MAIN_H
#define MAIN_H
/*added by Thomas Fallwell 03/12/15
*this class is for mapping eyes to mouse
*/
extern int detectAndDisplay(cv::Mat frame, char*);
extern int captureFace(char*);
void initCapure();

#endif