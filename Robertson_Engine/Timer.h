#pragma once
#include <ctime>
class Timer
{
private:
	///<summary>The current time</summary>
	clock_t cur;
	///<summary>The time it was in the previous frame</summary>
	clock_t prev;
public:
	Timer();
	~Timer();

	///<summary>Time since the timer was created</summary>
	float t;
	///<summary>Delta time, the time it took for this frame to elapse</summary>
	float dt;
	///<summary>Frames per second of this frame</summary>
	float fps;

	///<summary>Updates the Timer for this frame</summary>
	void update();
};

