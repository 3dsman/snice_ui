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

//void W_colorSelectdisplay::RefreshImage(){
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, quadImage.width, quadImage.height, GL_RGB, GL_UNSIGNED_BYTE, quadImage.imageData);

void W_colorSelectdisplay::RefreshImage(){
//	Texture* Image;

	//Image = &(pRgbcolor->quadImage);

	int k = 0;
	float red, green, blue;
	float hue, saturation, luminosity;
	float h, s, v;
    RGBtoHSV(r,g,b,&h,&s,&v);

	int i,j;
	for (i=0; i<int(quadImage.height); ++i){
		for (j=0; j<int(quadImage.width); ++j){
			switch (mode)
			{
				case HUE:
				{
					hue = h;
					saturation = float(j)/ quadImage.width;
					luminosity = float(i) / quadImage.height ;

					HSVtoRGB(hue,saturation,luminosity,&red,&green,&blue);
					break;
				}

				case SAT:
				{
					hue = float(j)/ quadImage.width*360.0f;
					saturation = s;
					luminosity = float(i) / quadImage.height ;

					HSVtoRGB(hue,saturation,luminosity,&red,&green,&blue);
					break;
				}

				case VAL:
				{
					hue = float(j)/ quadImage.width*360.0f;
					saturation = float(i) / quadImage.height ;
					luminosity = v;

					HSVtoRGB(hue,saturation,luminosity,&red,&green,&blue);
					break;
				}

				case RED:
				{
					red= r;
					green= float(j)/ quadImage.width;
					blue= float(i)/ quadImage.height;
					break;
				}

				case GREEN:
				{
					red= float(j)/ quadImage.width;
					green= g;
					blue= float(i)/ quadImage.height;
					break;
				}

				case BLUE:
				{
					red= float(j)/ quadImage.width;
					green= float(i)/ quadImage.height;
					blue= b;
					break;
				}
			}

			quadImage.imageData[k++] = char(red * 255);
			quadImage.imageData[k++] = char(green * 255);
			quadImage.imageData[k++] = char(blue * 255);
		}
	}

    k=0;
	for (i=0; i<lineImage.height; i++){
        switch (mode)
        {
            case HUE:
            {
                hue = float(i)/ lineImage.height*360.0f;
                saturation = s;
                luminosity = v ;

                HSVtoRGB(hue,saturation,luminosity,&red,&green,&blue);
                break;
            }

            case SAT:
            {
                hue = h;
                saturation = float(i) / float(lineImage.height);
                luminosity = v ;

                HSVtoRGB(hue,saturation,luminosity,&red,&green,&blue);
                break;
            }

            case VAL:
            {
                hue = h;
                saturation = s;
                luminosity = float(i) / float(lineImage.height);

                HSVtoRGB(hue,saturation,luminosity,&red,&green,&blue);
                break;
            }

            case RED:
            {
                red= float(i) / float(lineImage.height);
                green= g;
                blue= b;
                break;
            }

            case GREEN:
            {
                red= r;
                green= float(i) / float(lineImage.height);
                blue= b;
                break;
            }

            case BLUE:
            {
                red= r;
                green= g;
                blue= float(i) / float(lineImage.height);
                break;
            }
        }

        for (j=0; j<lineImage.width; j++){
            lineImage.imageData[k++] = char(red * 255);
            lineImage.imageData[k++] = char(green * 255);
            lineImage.imageData[k++] = char(blue * 255);
        }
	}

	// horizontal bar
	i=int(cury * quadImage.height)*quadImage.width * 3;
	for (j= 0; j < quadImage.width * 3;j++){
		quadImage.imageData[i] = 1 - (quadImage.imageData[i]);
		i++;
	}

	// vertical bar
	i = curx*quadImage.width * 3;
	for (j = 0; j < int(quadImage.height) ;++j){
		quadImage.imageData[i] = 1 - (quadImage.imageData[i]);i++;
		quadImage.imageData[i] = 1 - (quadImage.imageData[i]);i++;
		quadImage.imageData[i] = 1 - (quadImage.imageData[i]);i++;
		i += (quadImage.width-1)*3;
	}

	glBindTexture(GL_TEXTURE_2D, lineImage.texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lineImage.width, lineImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, lineImage.imageData);

	glBindTexture(GL_TEXTURE_2D, quadImage.texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, quadImage.width, quadImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, quadImage.imageData);

	refresh = true;
};

W_colorSelectdisplay::W_colorSelectdisplay(int x, int y, int w, int h, colorSelector selectorType, float red, float green, float blue, int pImageWidth, int pImageHeight)
		:UI_widget(x, y, w, h, red, green, blue)
{
	posx = x;
	posy = y;
	width = w;
	height = h;

	//curx = 0;
	//cury = 0;
	r = red;
	g = green;
	b = blue;

	mode=selectorType;

    float hue, sat, val;
    RGBtoHSV(r,g,b,&hue,&sat,&val);

	switch (mode)
			{
				case HUE:
                    curx = sat;cury = val;break;
				case SAT:
                    curx = hue/360.0f; cury = val; break;
				case VAL:
                    curx = hue/360.0f; cury = sat; break;
				case RED:
                    curx = g; cury = b; break;
				case GREEN:
                    curx = r; cury = b; break;
				case BLUE:
                    curx = r; cury = g; break;
			}

	refresh = true;

    //gentex(lineImage);
	lineImage.width  = 4;
	lineImage.height = pImageHeight;
	lineImage.bpp	= 24;
	lineImage.imageData	= (GLubyte *)malloc(lineImage.width*lineImage.height*3);
	glGenTextures(1, &lineImage.texID);

	quadImage.width  = pImageWidth;
	quadImage.height = pImageHeight;
	quadImage.bpp	= 24;
	quadImage.imageData	= (GLubyte *)malloc(pImageWidth*pImageHeight*3);
	glGenTextures(1, &quadImage.texID);

    RefreshImage();

	glBindTexture(GL_TEXTURE_2D, quadImage.texID);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR  );
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR  );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, quadImage.width, quadImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, quadImage.imageData);

	glBindTexture(GL_TEXTURE_2D, lineImage.texID);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR  );
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR  );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lineImage.width, lineImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, lineImage.imageData);
    //gentex(lineImage);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lineImage.width, lineImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, lineImage.imageData);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, quadImage.width, quadImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, quadImage.imageData);

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


void W_colorSelectdisplay::Draw()
{

	glEnable(GL_TEXTURE_2D);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	if (refresh){

//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, quadImage.width, quadImage.height, GL_RGB, GL_UNSIGNED_BYTE, quadImage.imageData);
		//refresh=false;
	}
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

if (refresh){refresh =false;};

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

	glTranslated(-posx,-posy,0);
}

void W_colorSelectdisplay::UpdateColor(int x, int y){

	r = float(x)/float(width);
	g = -(float(y)/float(height));
	b = 0;
}

void W_colorSelectdisplay::GetColor(float* red, float* green, float* blue){
	*red = r;
	*green = g;
	*blue = b;

};

UI_base* W_colorSelectdisplay::OnLButtonDown(int x, int y)
{
	if (Hittest(x,y))
	{
        UpdateColor(x-posx,y-posy);
		curx = x-posx;
		cury = posy-y;
		pInterceptChild = this;
	}
    else
    {
        pInterceptChild = 0;
    }
	/*if (!(x<posx || x>posx+width || y>posy || y<posy-height)){
		//action = true;
		UpdateColor(x-posx,y-posy);
		curx = x-posx;
		cury = posy-y;

		pInterceptChild = this;
		return this;
	}*/
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
	//if (action == true)
	if(pInterceptChild == this)
	{

		curx = x-posx;
		cury = posy-y;
		if (curx<0 ){
			curx = 0;
		}
		if (curx>width ){
			curx = width;
		}
		if (cury<0 ){
			cury = 0;
		}
		if (cury>height ){
			cury = height;
		}

        //pInterceptChild = this;
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
