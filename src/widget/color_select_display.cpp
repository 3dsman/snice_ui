// crafter interface library
// Funny Farm
// copyright © 2002 Wybren van Keulen
// www.funnyfarm.tv

// File modified by Tricoire Sebastien
// Date of creation : 2004 06 02
///
// File modified by Lionel Allorge
// Date of modification : 2004 06 02

/* ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version. The Blender
 * Foundation also sells licenses for use in proprietary software under
 * the Blender License.  See http://www.blender.org/BL/ for information
 * about this.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2002-2003 by Funny Farm.
 * www.funnyfarm.tv
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#include "include/color_conversion.h"
#include "../snice_UI.h"
#include "widget/color_select_display.h"
#include <cmath>

W_colorSelectdisplay::W_colorSelectdisplay(int x, int y, int w, int h, colorSelector selectorType, float red, float green, float blue, int pImageWidth, int pImageHeight)
		:UI_widget(x, y, w, h, red, green, blue)
{
	posx = x;
	posy = y;
	width = w;
	height = h;

	mode=selectorType;

    if ((mode==HUE)||(mode==SAT)||(mode==VAL))
        RGBtoHSV(red,green,blue,&redHue,&greenSat,&blueVal);
    else
    {
            redHue = red;
            greenSat = green;
            blueVal = blue;
    }

	switch (mode)
			{
				case HUE:
                    curx = greenSat; cury = blueVal; curz = redHue/360.0f;break;
				case SAT:
                    curx = redHue/360.0f; cury = blueVal; curz = greenSat; break;
				case VAL:
                    curx = redHue/360.0f; cury = greenSat; curz = blueVal; break;
				case RED:
                    curx = greenSat; cury = blueVal; curz = redHue; break;
				case GREEN:
                    curx = redHue; cury = blueVal; curz = greenSat; break;
				case BLUE:
                    curx = redHue; cury = greenSat; curz = blueVal; break;
			}

	quadImage.width  = pImageWidth;
	quadImage.height = pImageHeight;
	quadImage.bpp	= 24;
	quadImage.imageData	= (GLubyte *)malloc(pImageWidth*pImageHeight*3);
	glGenTextures(1, &quadImage.texID);

    RefreshImageXY();

    //gentex(lineImage);
	lineImage.width  = 4;
	lineImage.height = pImageHeight;
	lineImage.bpp	= 24;
	lineImage.imageData	= (GLubyte *)malloc(lineImage.width*lineImage.height*3);
	glGenTextures(1, &lineImage.texID);
    RefreshImageZ();

	glBindTexture(GL_TEXTURE_2D, quadImage.texID);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR  );
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR  );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, quadImage.width, quadImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, quadImage.imageData);

	glBindTexture(GL_TEXTURE_2D, lineImage.texID);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR  );
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR  );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lineImage.width, lineImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, lineImage.imageData);

}

W_colorSelectdisplay::~W_colorSelectdisplay()
{
	if (quadImage.imageData)
    {
        free(quadImage.imageData);
    }
    if (lineImage.imageData)
    {
        free(lineImage.imageData);
    }
}


void W_colorSelectdisplay::SetCursorXY(float curx, float cury){

	switch (mode)
    {
        case HUE:
            greenSat = curx; blueVal = cury;
            break;
        case SAT:
            redHue= curx*360.0f; blueVal = cury;
            break;
        case VAL:
            redHue= curx*360.0f; greenSat = cury;
            break;
        case RED:
            greenSat = curx; blueVal = cury; break;
        case GREEN:
            redHue = curx; blueVal = cury; break;
        case BLUE:
            redHue = curx; greenSat = cury; break;
    }

    RefreshImageZ();
}


void W_colorSelectdisplay::SetCursorZ(float curz){

	switch (mode)
			{
				case HUE:
                    redHue = curz*360.0f;
                    if (redHue==360.0f)redHue=0;
                    break;
				case SAT:
                    greenSat = curz;
                    break;
				case VAL:
                    blueVal = curz;
                    break;
				case RED:
                    redHue = curz;break;
				case GREEN:
                    greenSat = curz;break;
				case BLUE:
                    blueVal = curz;break;
			}

			RefreshImageXY();
}

void W_colorSelectdisplay::RefreshImageXY(){

	int k = 0;
	float red, green, blue;

	int i,j;
	for (i=0; i<int(quadImage.height); ++i){
		for (j=0; j<int(quadImage.width); ++j){
			switch (mode)
			{
				case HUE:
					HSVtoRGB(redHue,float(j)/ quadImage.width,float(i) / quadImage.height,&red,&green,&blue);
					break;

				case SAT:
					HSVtoRGB(float(j)/ quadImage.width*360.0f,greenSat,float(i) / quadImage.height,&red,&green,&blue);
					break;

				case VAL:
					HSVtoRGB(float(j)/ quadImage.width*360.0f,float(i) / quadImage.height,blueVal,&red,&green,&blue);
					break;

				case RED:
					red= redHue;
					green= float(j)/ quadImage.width;
					blue= float(i)/ quadImage.height;
					break;

				case GREEN:
					red= float(j)/ quadImage.width;
					green= greenSat;
					blue= float(i)/ quadImage.height;
					break;

				case BLUE:
					red= float(j)/ quadImage.width;
					green= float(i)/ quadImage.height;
					blue= blueVal;
					break;
			}

			quadImage.imageData[k++] = char(red * 255);
			quadImage.imageData[k++] = char(green * 255);
			quadImage.imageData[k++] = char(blue * 255);
		}
	}

	glBindTexture(GL_TEXTURE_2D, quadImage.texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, quadImage.width, quadImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, quadImage.imageData);

};

void W_colorSelectdisplay::RefreshImageZ(){

	int k = 0;
	float red = redHue;
	float green = greenSat;
	float blue =blueVal;

	for (unsigned int i=0; i<lineImage.height; i++){
        switch (mode)
        {
            case HUE:
            {
                //hue = float(i)/ float(lineImage.height)*360.0f;
                HSVtoRGB(float(i)/ float(lineImage.height)*360.0f,greenSat,blueVal,&red,&green,&blue);
                break;
            }

            case SAT:
            {
                //saturation = float(i) / float(lineImage.height);
                HSVtoRGB(redHue,float(i) / float(lineImage.height),blueVal,&red,&green,&blue);
                break;
            }

            case VAL:
            {
                //luminosity = float(i) / float(lineImage.height);

                HSVtoRGB(redHue,greenSat,float(i) / float(lineImage.height),&red,&green,&blue);
                break;
            }

            case RED:
            {
                red= float(i) / float(lineImage.height);
                break;
            }

            case GREEN:
            {
                green= float(i) / float(lineImage.height);
                break;
            }

            case BLUE:
            {
                blue= float(i) / float(lineImage.height);
                break;
            }
        }

        for (unsigned int j=0; j<lineImage.width; j++){
            lineImage.imageData[k++] = char(red * 255);
            lineImage.imageData[k++] = char(green * 255);
            lineImage.imageData[k++] = char(blue * 255);
        }
	}

	glBindTexture(GL_TEXTURE_2D, lineImage.texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lineImage.width, lineImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, lineImage.imageData);

};


void W_colorSelectdisplay::Draw()
{

	glEnable(GL_TEXTURE_2D);

	glTranslated(posx, posy, 0);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, quadImage.texID);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2d(1,-1);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2d(width-20, -1);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2d(width-20, -height+1);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2d(1, -height+1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, lineImage.texID);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2d(width-15,-1);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2d(width-1, -1);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2d(width-1, -height+1);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2d(width-15, -height+1);
	glEnd();

	glDisable(GL_TEXTURE_2D);

//if (refresh){refresh =false;};

	// draw the border
	glColor4f(1.0f,1.0f,1.0f,0.7f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures.slider.texID);//textures[8].texID				// Select Our Font Texture
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,1.0f);
		glVertex2d(0, 0);
		glTexCoord2f(0.25f,1.0f);
		glVertex2d(8, 0);
		glTexCoord2f(0.25,0.75f);
		glVertex2d(8, -8);
		glTexCoord2f(0.0f,0.75f);
		glVertex2d(0, -8);

		glTexCoord2f(0.49f,1.0f);
		glVertex2d(8, 0);
		glTexCoord2f(0.51f,1.0f);
		glVertex2d(width-8, 0);
		glTexCoord2f(0.51f,0.75f);
		glVertex2d(width-8, -8);
		glTexCoord2f(0.49f,0.75f);
		glVertex2d(8, -8);

		glTexCoord2f(0.75f,1.0f);
		glVertex2d(width-8, 0);
		glTexCoord2f(1.00f,1.0f);
		glVertex2d(width, 0);
		glTexCoord2f(1.00f,0.75f);
		glVertex2d(width, -8);
		glTexCoord2f(0.75f,0.75f);
		glVertex2d(width-8, -8);

		glTexCoord2f(0.75f,0.75f);
		glVertex2d(width-8, -8);
		glTexCoord2f(1.00f,0.75f);
		glVertex2d(width, -8);
		glTexCoord2f(1.00f,0.25f);
		glVertex2d(width, -height+8);
		glTexCoord2f(0.75f,0.25f);
		glVertex2d(width-8, -height+8);

		glTexCoord2f(0.75f,0.25f);
		glVertex2d(width-8, -height+8);
		glTexCoord2f(1.00f,0.25f);
		glVertex2d(width, -height+8);
		glTexCoord2f(1.00f,0.00f);
		glVertex2d(width, -height);
		glTexCoord2f(0.75f,0.00f);
		glVertex2d(width-8, -height);

		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -height+8);
		glTexCoord2f(0.75f,0.25f);
		glVertex2d(width-8, -height+8);
		glTexCoord2f(0.75,0.00f);
		glVertex2d(width-8, -height);
		glTexCoord2f(0.25f,0.00f);
		glVertex2d(8, -height);

		glTexCoord2f(0.0f,0.25f);
		glVertex2d(0, -height+8);
		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -height+8);
		glTexCoord2f(0.25f,0.00f);
		glVertex2d(8, -height);
		glTexCoord2f(0.0f,0.00f);
		glVertex2d(0, -height);

		glTexCoord2f(0.00f,0.75f);
		glVertex2d(0, -8);
		glTexCoord2f(0.25f,0.75f);
		glVertex2d(8, -8);
		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -height+8);
		glTexCoord2f(0.00f,0.25f);
		glVertex2d(0, -height+8);
	glEnd();
	/*
	glBindTexture(GL_TEXTURE_2D, textures[10].texID);
	glColor4f(1.0f,1.0f,1.0f,0.6f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,1.0f);
		glVertex2d(0, 0);
		glTexCoord2f(1.0f,1.0f);
		glVertex2d(width, 0);
		glTexCoord2f(1.0f,0.0f);
		glVertex2d(width,-height);
		glTexCoord2f(0.0f,0.0f);
		glVertex2d(0, -height);
	glEnd();
	*/

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_LINE_LOOP);
	glLineWidth(1);

	//glTranslatef(curx*(width-20),cury*height,0);
    // cursor circle
	for (int i = 0; i < 360 ;i+=5){
		glVertex2d(curx*(width-20)+sin(DEG2RAD(float(i)))*6, cury*height-height+cos(DEG2RAD(float(i)))*6);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 180 ;i+=5){
		glVertex2d((width-3)+sin(DEG2RAD(float(i)))*4, curz*height-height+cos(DEG2RAD(float(i)))*4);
	}
    for (int i = 180; i < 360 ;i+=5){
		glVertex2d((width-12)+sin(DEG2RAD(float(i)))*4, curz*height-height+cos(DEG2RAD(float(i)))*4);
	}
	//glTranslatef(-curx*(width-20),-cury*height,0);
    glEnd();
	glTranslated(-posx,-posy,0);
}

void W_colorSelectdisplay::UpdateColor(int x, int y){

	/*redHue = float(x)/float(width);
	greenSat = -(float(y)/float(height));
	blueVal = 0;*/
}

void W_colorSelectdisplay::GetColor(float* red, float* green, float* blue){
    if ((mode==HUE)||(mode==SAT)||(mode==VAL))
        HSVtoRGB(redHue,greenSat,blueVal, red, green, blue);
    else
    {
        *red = redHue;
        *green = greenSat;
        *blue = blueVal;
    }
};

UI_base* W_colorSelectdisplay::OnLButtonDown(int x, int y)
{
	if (Hittest(x,y))
	{
		pInterceptChild = this;
        if (x-posx<width-20)
        {
            curx = float(x-posx)/float(width-20);
            cury = 1+float(y-posy)/float(height);
            SetCursorXY(curx, cury);
            xy=true;
            return 0;
		}
		else if (x-posx>width-15)
		{
            curz = 1+float(y-posy)/float(height);
            SetCursorZ(curz);
            xy=false;
            return 0;
		}
    }
    pInterceptChild = 0;
    return 0;

}

UI_base* W_colorSelectdisplay::OnLButtonUp(int x, int y)
{
    UI_widget::OnLButtonUp(x, y);
	//action = false;
	pInterceptChild = 0;
    return 0;
}

UI_base* W_colorSelectdisplay::OnMouseMove(int x, int y, int prevx, int prevy)
{
	if(pInterceptChild == this)
	{
        if (xy)
        {
            curx = max(min(float(x-posx)/float(width-20),1.0f),0.0f);
            cury = max(min(1+float(y-posy)/float(height),1.0f),0.0f);
            SetCursorXY(curx, cury);
		}
		else
		{
            curz = max(min(1+float(y-posy)/float(height),1.0f),0.0f);
            SetCursorZ(curz);
		}
		return this;
		/*
		if (pParentUI_base)
			pParentUI_base->Callback(this,1);*/
	}
    return 0;
}



void W_colorSelectdisplay::LoadXML(TiXmlElement* element)
{

}
