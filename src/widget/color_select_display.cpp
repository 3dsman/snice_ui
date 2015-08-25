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
#include <GL/gl.h>
#include "widget/color_select_display.h"
#include <cmath>

W_colorSelectDisplay::W_colorSelectDisplay(int x, int y, int w, int h, colorSelector selectorType, float red, float green, float blue, int pImageWidth, int pImageHeight)
		:UI_widget(x, y, w, h, red, green, blue)
{
	posx = x;
	posy = y;
	width = w;
	height = h;

	mode=selectorType;
/*
    if ((mode==H)||(mode==S)||(mode==V))
        RGBtoHSV(red,green,blue,&redHue,&greenSat,&blueVal);
    else
    {
            redHue = red;
            greenSat = green;
            blueVal = blue;
    }

	switch (mode)
			{
				case H:
                    curx = greenSat; cury = blueVal; curz = redHue/360.0f;break;
				case S:
                    curx = redHue/360.0f; cury = blueVal; curz = greenSat; break;
				case V:
                    curx = redHue/360.0f; cury = greenSat; curz = blueVal; break;
				case R:
                    curx = greenSat; cury = blueVal; curz = redHue; break;
				case G:
                    curx = redHue; cury = blueVal; curz = greenSat; break;
				case B:
                    curx = redHue; cury = greenSat; curz = blueVal; break;
			}*/

	quadImage.SetWidth(pImageWidth);
	quadImage.SetHeight(pImageHeight);
	quadImage.SetBpp(24);
	quadImage.SetData((GLubyte *)malloc(pImageWidth*pImageHeight*3));
	//glGenTextures(1, &quadImage.texID);
	quadImage.gentex();

    //RefreshImageXY();

    //gentex(lineImage);
	lineImage.SetWidth(4);
	lineImage.SetHeight(pImageHeight);
	lineImage.SetBpp(24);
	lineImage.SetData((GLubyte *)malloc(lineImage.GetWidth()*lineImage.GetHeight()*3));
	lineImage.gentex();
	//glGenTextures(1, &lineImage.texID);
	
	SetColor(red,green,blue);
    //RefreshImageZ();

	//glBindTexture(GL_TEXTURE_2D, quadImage.texID);
	quadImage.BindTex();
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR  );
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR  );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, quadImage.GetWidth(), quadImage.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, quadImage.GetData());

	//glBindTexture(GL_TEXTURE_2D, lineImage.texID);
	lineImage.BindTex();
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR  );
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR  );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lineImage.GetWidth(), lineImage.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, lineImage.GetData());

}

W_colorSelectDisplay::~W_colorSelectDisplay()
{
	/*if (quadImage.GetData())
    {
        free(quadImage.tex.imageData);
    }
    if (lineImage.tex.imageData)
    {
        free(lineImage.tex.imageData);
    }*/
}


void W_colorSelectDisplay::SetCursorXY(float curx, float cury){

	switch (mode)
    {
        case H:
            greenSat = curx; blueVal = cury;
            break;
        case S:
            redHue= curx*360.0f; blueVal = cury;
            break;
        case V:
            redHue= curx*360.0f; greenSat = cury;
            break;
        case R:
            greenSat = curx; blueVal = cury; break;
        case G:
            redHue = curx; blueVal = cury; break;
        case B:
            redHue = curx; greenSat = cury; break;
    }

    RefreshImageZ();
}


void W_colorSelectDisplay::SetCursorZ(float curz){

	switch (mode)
			{
				case H:
                    redHue = curz*360.0f;
                    if (redHue==360.0f)redHue=0;
                    break;
				case S:
                    greenSat = curz;
                    break;
				case V:
                    blueVal = curz;
                    break;
				case R:
                    redHue = curz;break;
				case G:
                    greenSat = curz;break;
				case B:
                    blueVal = curz;break;
			}

			RefreshImageXY();
}

void W_colorSelectDisplay::RefreshImageXY(){

	int k = 0;
	float red, green, blue;
	GLubyte * image;
	image = quadImage.GetData();
	int i,j;
	for (i=0; i<int(quadImage.GetHeight()); ++i){
		for (j=0; j<int(quadImage.GetWidth()); ++j){
			switch (mode)
			{
				case H:
					HSVtoRGB(redHue,float(j)/ quadImage.GetWidth(),float(i) / quadImage.GetHeight(),&red,&green,&blue);
					break;

				case S:
					HSVtoRGB(float(j)/ quadImage.GetWidth()*360.0f,greenSat,float(i) / quadImage.GetHeight(),&red,&green,&blue);
					break;

				case V:
					HSVtoRGB(float(j)/ quadImage.GetWidth()*360.0f,float(i) / quadImage.GetHeight(),blueVal,&red,&green,&blue);
					break;

				case R:
					red= redHue;
					green= float(j)/ quadImage.GetWidth();
					blue= float(i)/ quadImage.GetHeight();
					break;

				case G:
					red= float(j)/ quadImage.GetWidth();
					green= greenSat;
					blue= float(i)/ quadImage.GetHeight();
					break;

				case B:
					red= float(j)/ quadImage.GetWidth();
					green= float(i)/ quadImage.GetHeight();
					blue= blueVal;
					break;
			}

			image[k++] = char(red * 255);
			image[k++] = char(green * 255);
			image[k++] = char(blue * 255);
		}
	}

	//glBindTexture(GL_TEXTURE_2D, quadImage.texID);
	quadImage.BindTex();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, quadImage.GetWidth(), quadImage.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, quadImage.GetData());

};

void W_colorSelectDisplay::RefreshImageZ(){

	int k = 0;
	float red = redHue;
	float green = greenSat;
	float blue =blueVal;
GLubyte * image;
image = lineImage.GetData();

	for (unsigned int i=0; i<lineImage.GetHeight(); i++){
        switch (mode)
        {
            case H:
            {
                //hue = float(i)/ float(lineImage.height)*360.0f;
                HSVtoRGB(float(i)/ float(lineImage.GetHeight())*360.0f,greenSat,blueVal,&red,&green,&blue);
                break;
            }

            case S:
            {
                //saturation = float(i) / float(lineImage.height);
                HSVtoRGB(redHue,float(i) / float(lineImage.GetHeight()),blueVal,&red,&green,&blue);
                break;
            }

            case V:
            {
                //luminosity = float(i) / float(lineImage.height);

                HSVtoRGB(redHue,greenSat,float(i) / float(lineImage.GetHeight()),&red,&green,&blue);
                break;
            }

            case R:
            {
                red= float(i) / float(lineImage.GetHeight());
                break;
            }

            case G:
            {
                green= float(i) / float(lineImage.GetHeight());
                break;
            }

            case B:
            {
                blue= float(i) / float(lineImage.GetHeight());
                break;
            }
        }

        for (unsigned int j=0; j<lineImage.GetWidth(); j++){
            image[k++] = char(red * 255);
            image[k++] = char(green * 255);
            image[k++] = char(blue * 255);
        }
	}

	lineImage.BindTex();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lineImage.GetWidth(), lineImage.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, lineImage.GetData());
};


void W_colorSelectDisplay::Draw()
{

	glEnable(GL_TEXTURE_2D);

	glTranslated(posx, posy, 0);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	quadImage.BindTex();
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

	lineImage.BindTex();
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

	// draw the border
	glColor4f(1.0f,1.0f,1.0f,0.7f);

	glEnable(GL_TEXTURE_2D);
	textures.slider.BindTex();
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

	glTranslatef(curx*(width-20),cury*height-height,0);
	glBegin(GL_LINE_LOOP);
	glLineWidth(1);

    // xy cursor circle
	for (int i = 0; i <= 360 ;i+=30){
		glVertex2d(sin(DEG2RAD(float(i)))*6, cos(DEG2RAD(float(i)))*6);
	}
	
	glEnd();
	glTranslatef(-curx*(width-20),-(cury*height-height),0);
	
	// z cursor capsule
	glTranslatef(0,curz*height-height,0);
	glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 180 ;i+=30){
		glVertex2d((width-3)+sin(DEG2RAD(float(i)))*4, cos(DEG2RAD(float(i)))*4);
	}
    for (int i = 180; i <= 360 ;i+=30){
		glVertex2d((width-12)+sin(DEG2RAD(float(i)))*4, cos(DEG2RAD(float(i)))*4);
	}
	
    glEnd();
	glTranslatef(0,-(curz*height-height),0);
	glTranslated(-posx,-posy,0);
}

void W_colorSelectDisplay::RefreshAll(){

	switch (mode)
	{
		case H:
			curx = greenSat; cury = blueVal; curz = redHue/360.0f;break;
		case S:
			curx = redHue/360.0f; cury = blueVal; curz = greenSat; break;
		case V:
			curx = redHue/360.0f; cury = greenSat; curz = blueVal; break;
		case R:
			curx = greenSat; cury = blueVal; curz = redHue; break;
		case G:
			curx = redHue; cury = blueVal; curz = greenSat; break;
		case B:
			curx = redHue; cury = greenSat; curz = blueVal; break;
	}
	RefreshImageXY();
	RefreshImageZ();
}

void W_colorSelectDisplay::SetColor(float red, float green, float blue)
{
	if ((mode==H)||(mode==S)||(mode==V))
        RGBtoHSV(red, green, blue,&redHue,&greenSat,&blueVal);
    else
    {
        redHue = red;
        greenSat = green;
        blueVal = blue;
    }
	RefreshAll();
	//SetCursorXY(curx, cury);
	//SetCursorZ(curz);
}

void W_colorSelectDisplay::GetColor(float* red, float* green, float* blue){
    if ((mode==H)||(mode==S)||(mode==V))
        HSVtoRGB(redHue,greenSat,blueVal, red, green, blue);
    else
    {
        *red = redHue;
        *green = greenSat;
        *blue = blueVal;
    }
};

void W_colorSelectDisplay::SetMode(colorSelector mode)
{
	float red = redHue;
	float green = greenSat;
	float blue = blueVal;
	
	if (((this->mode==H)||(this->mode==S)||(this->mode==V))&&((mode==R)||(mode==G)||(mode==B)))
        HSVtoRGB(red, green, blue,&redHue,&greenSat,&blueVal);
	if (((this->mode==R)||(this->mode==G)||(this->mode==B))&&((mode==H)||(mode==S)||(mode==V)))
        RGBtoHSV(red, green, blue,&redHue,&greenSat,&blueVal);
		
	this->mode = mode;
	
	RefreshAll();
}

colorSelector W_colorSelectDisplay::GetMode()
{
	return mode;
}

void W_colorSelectDisplay::OnChange(UI_base * asker, std::function<void(UI_base * asker, W_colorSelectDisplay* caller,float red,float green, float blue)> function)
{
    onChange = function;
	onChangeAsker = asker;
}

UI_base* W_colorSelectDisplay::OnLButtonDown(int x, int y)
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
            if(onChange)
            {
                float r,g,b;
                GetColor(&r,&g,&b);
                onChange(onChangeAsker, this,r,g,b);
            }
            return 0;
		}
		else if (x-posx>width-15)
		{
            curz = 1+float(y-posy)/float(height);
            SetCursorZ(curz);
            xy=false;
            if(onChange)
            {
                float r,g,b;
                GetColor(&r,&g,&b);
                onChange(onChangeAsker, this,r,g,b);
            }
            return 0;
		}
    }
    pInterceptChild = 0;
    return 0;

}

UI_base* W_colorSelectDisplay::OnLButtonUp(int x, int y)
{
    UI_widget::OnLButtonUp(x, y);
	//action = false;
	pInterceptChild = 0;
    return 0;
}

UI_base* W_colorSelectDisplay::OnMouseMove(int x, int y, int prevx, int prevy)
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
        if(onChange)
            {
                float r,g,b;
                GetColor(&r,&g,&b);
                onChange(onChangeAsker, this,r,g,b);
            }
		return this;
	}
    return 0;
}

/*

void W_colorSelectDisplay::LoadXML(TiXmlElement* element)
{

}*/
