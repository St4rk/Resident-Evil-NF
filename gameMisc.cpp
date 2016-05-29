#include "gameMisc.h"

gameMisc::gameMisc() {
	mtimer  = 0;
	mR      = 0;
	mG      = 0;
	mB      = 0;
	mA      = 0;
	mEnable = false;
	gTimer = 0;
	mtype   = TYPE_FADE_NONE;
}

gameMisc::~gameMisc() {

}


/*
 * setupFadeEffect
 * This function is used to initialize the fadeEffect params
 */
void gameMisc::setupFadeEffect(unsigned char type, float R, float G, float B, 
							   unsigned int  timer) {

	this->mtimer  = timer;
	this->mR      = R;
	this->mG      = G;
	this->mB      = B;
	this->mtype   = type;
	this->mEnable = true;
	this->gTimer = 0;

	if (mtype == TYPE_FADE_IN) {
		this->mA = 0;
	} else if (mtype == TYPE_FADE_OUT) {
		this->mA = 1.0;
	} else if (mtype == TYPE_FADE_OUT_AND_IN) {
		this->mA = 1.0;
		doubleMode = true;
	} else if (mtype == TYPE_FADE_SPECIAL) {
		this->mA = 0.0;
		specialMode = 0.0;
	}
}

/*
 * renderFadeEffect
 * This function does the fade in and fade out effect
 */
void gameMisc::renderFadeEffect() {

	/* verifies if fadeEffect is enable */
	if (mEnable) {
	        glDisable(GL_LIGHTING);
	        glDisable(GL_TEXTURE_2D);
	        
	        glLoadIdentity();

	        glBegin(GL_QUADS);                     
	            glColor4f(mR, mG, mB, mA);
	            glVertex3f(-3.0f, 2.0f, -3.0f);              
	            glVertex3f( 3.0f, 2.0f, -3.0f);              
	            glVertex3f( 3.0f,-2.0f, -3.0f);              
	            glVertex3f(-3.0f,-2.0f, -3.0f);                   
	        glEnd();

	        glEnable(GL_LIGHTING);
	        glEnable(GL_TEXTURE_2D);


	        /*
	         * here the Alpha is incremented or decremented according with its type
	         */

	         switch (mtype) {
	         	case TYPE_FADE_IN:
			         if (SDL_GetTicks() > gTimer) {
						gTimer = SDL_GetTicks() + mtimer;
						mA    += 0.1;

						if (mA >= 1.0) {
							mEnable = false;
						}
			         }

	         	break;

	         	case TYPE_FADE_OUT:
			         if (SDL_GetTicks() > gTimer) {
						gTimer = SDL_GetTicks() + mtimer;
						   mA -= 0.1;

						if (mA <= 0.0) {
							mEnable = false;
						}

			         }
	         	break;

	         	case TYPE_FADE_OUT_AND_IN:
	         		if (doubleMode) {
				         if (SDL_GetTicks() > gTimer) {
							gTimer = SDL_GetTicks() + mtimer;
							   mA -= 0.1;

							if (mA <= 0.0) {
								doubleMode = false;
							}
						}

	         		} else {
				         if (SDL_GetTicks() > gTimer) {
							gTimer = SDL_GetTicks() + mtimer;
							mA    += 0.1;

							if (mA >= 1.0) {
								mEnable = false;
							}
				         }
	         		}

	         	case TYPE_FADE_SPECIAL:
	         		switch (specialMode) {
	         			case 0:
					         if (SDL_GetTicks() > gTimer) {
					         	mR = 1.0f;
					         	mG = 1.0f;
					         	mB = 1.0f;
								gTimer = SDL_GetTicks() + 5;
								mA    += 0.25;

								if (mA >= 1.0) {
									specialMode = 1;
								}
					         }
	         			break;

	         			case 1:
					        if (SDL_GetTicks() > gTimer) {
					         	mR = 1.0f;
					         	mG = 1.0f;
					         	mB = 1.0f;
								gTimer = SDL_GetTicks() + mtimer;
								   mA -= 0.05;

								if (mA <= 0.0) {
									mR = 0.0f;
									mG = 0.0f;
									mB = 0.0f;
									specialMode = 2;
								}
							}

	         			break;

	         			case 2:
					        if (SDL_GetTicks() > gTimer) {
								gTimer = SDL_GetTicks() + mtimer;
								   mA += 0.05;

								if (mA >= 1.0) {
									mEnable = false;
								}
							}
	         			break;
	         		}

	         		break;
	         	break;


	         	default:

	         	break;
	         }

	}
}


/*
 * renderSquareWithColor
 * This function render a square with color and alpha
 */
void gameMisc::renderSquareWithColor(float R, float G, float B, float A) {
    glPushMatrix();
        glDepthMask(GL_FALSE);
        glDisable(GL_LIGHTING);


        glBegin(GL_QUADS);                     
            glColor4f(R,G,B,A);

            glVertex3f(-0.77f, 0.58f, -1.0f);   

            glVertex3f( 0.77f, 0.58f, -1.0f);  

            glVertex3f( 0.77f,-0.58f, -1.0f); 

            glVertex3f(-0.77f,-0.58f, -1.0f);     
        glEnd();

        glEnable(GL_LIGHTING);

   		glDepthMask(GL_TRUE);
    glPopMatrix();
}

/*
 * renderSquareWithTexture
 * This function render a square with a bitmap texture
 */
void gameMisc::renderSquareWithTexture(bmp_loader_24bpp *texture, bool ARGB) {
    glPushMatrix();
        glDepthMask(GL_FALSE);
        glDisable(GL_LIGHTING);
        glLoadIdentity();
        /*
         * This API is used to setup a texture to object
         */
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        if (ARGB) 
        	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, texture->bmpWidth, texture->bmpHeight, 0,GL_BGRA, GL_UNSIGNED_BYTE, texture->bmpBuffer);        
        else
        	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, texture->bmpWidth, texture->bmpHeight, 0,GL_BGR, GL_UNSIGNED_BYTE, texture->bmpBuffer);

        glBegin(GL_QUADS);                     
            glColor3f(1.0, 1.0, 1.0);
            glTexCoord2i(0,1);
            glVertex3f(-0.77f, 0.58f, -1.0f);   
            glTexCoord2i(1,1);
            glVertex3f( 0.77f, 0.58f, -1.0f);  
            glTexCoord2i(1,0);
            glVertex3f( 0.77f,-0.58f, -1.0f); 
            glTexCoord2i(0,0);
            glVertex3f(-0.77f,-0.58f, -1.0f);     
        glEnd();

        glEnable(GL_LIGHTING);
   		glDepthMask(GL_TRUE);
    glPopMatrix();
}



bool gameMisc::isInFade() { return mEnable; }