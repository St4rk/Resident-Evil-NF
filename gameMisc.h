/***************************************************************************
** gameMisc is used to handle font, fadeEffect and others kind of stuff   **
** Written by St4rk                                                       **
** Nightmare Fiction Engine - NFE                                         **
***************************************************************************/

#ifndef GAME_MISC_H
#define GAME_MISC_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <GL/glut.h>
#include <SDL/SDL.h>
#include "gameStruct.h"

enum FADE_TYPE {
	TYPE_FADE_NONE       = 0,
	TYPE_FADE_IN         = 1,
	TYPE_FADE_OUT        = 2,
	TYPE_FADE_OUT_AND_IN = 3,
	TYPE_FADE_SPECIAL    = 4
};

class gameMisc {
public:
	gameMisc();
	~gameMisc();

	void renderSquareWithColor(float R, float G, float B, float A);
	void renderSquareWithTexture(bmp_loader_24bpp *texture, bool ARGB);
	void setupFadeEffect(unsigned char type, float R, float G, float B, 
					     unsigned int  timer);
	void renderFadeEffect();

	bool isInFade();

private:
	/*
	 * fadeEffect stuff
	 */
	unsigned int  mtimer;
	float mR;
	float mG;
	float mB;
	float mA;
	unsigned char mtype;
	unsigned int  gTimer;
	bool mEnable;

	bool doubleMode;
	unsigned char specialMode;
};


#endif