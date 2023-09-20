/*
File:   main.h
Author: Taylor Robbins
Date:   09\19\2023
*/

#ifndef _MAIN_H
#define _MAIN_H

struct PigState_t
{
	bool initialized;
	
	oc_surface surface;
	oc_canvas canvas;
	oc_font font;
	v2 frameSize;
	v2i frameSizei;
	f64 lastSeconds;
	
	RandomSeries_t random;
};

#endif //  _MAIN_H
