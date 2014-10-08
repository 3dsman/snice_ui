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
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, PreviewImage.width, PreviewImage.height, GL_RGB, GL_UNSIGNED_BYTE, PreviewImage.imageData);

void W_colorSelectdisplay::RefreshImage(){
//	Texture* Image;

	//Image = &(pRgbcolor->PreviewImage);

	int k = 0;
	float red, green, blue;
	float hue, saturation, luminosity;
	float h, s, v;
    RGBtoHSV(r,g,b,&h,&s,&v);

	int i,j;
	for (i=0; i<int(PreviewImage.height); ++i){
		for (j=0; j<int(PreviewImage.width); ++j){
			switch (mode)
			{
				case HUE:
				{
					hue = h;
					saturation = float(j)/ 255.0f;
					luminosity = float(i) / 255.0f ;

					HSVtoRGB(hue,saturation,luminosity,&red,&green,&blue);
					break;
				}

				case SAT:
				{
					hue = float(j)/ 255.0f*360.0f;
					saturation = s;
					luminosity = float(i) / 255.0f ;

					HSVtoRGB(hue,saturation,luminosity,&red,&green,&blue);
					break;
				}

				case VAL:
				{
					hue = float(j)/ 255.0f*360.0f;
					saturation = float(i) / 255.0f ;
					luminosity = v;

					HSVtoRGB(hue,saturation,luminosity,&red,&green,&blue);
					break;
				}

				case RED:
				{
					red= r;
					green= float(j);
					blue= float(i);
					break;
				}

				case GREEN:
				{
					red= float(j);
					green= g;
					blue= float(i);
					break;
				}

				case BLUE:
				{
					red= float(j);
					green= float(i);
					blue= b;
					break;
				}
			}

			PreviewImage.imageData[k++] = char(red * 255);
			PreviewImage.imageData[k++] = char(green * 255);
			PreviewImage.imageData[k++] = char(blue * 255);
		}
	}


	// horizontal bar
	i=int(cury * PreviewImage.height)*PreviewImage.width * 3;
	for (j= 0; j < PreviewImage.width * 3;j++){
		PreviewImage.imageData[i] = 1 - (PreviewImage.imageData[i]);
		i++;
	}

	// vertical bar
	i = curx*PreviewImage.width * 3;
	for (j = 0; j < int(PreviewImage.height) ;++j){
		PreviewImage.imageData[i] = 1 - (PreviewImage.imageData[i]);i++;
		PreviewImage.imageData[i] = 1 - (PreviewImage.imageData[i]);i++;
		PreviewImage.imageData[i] = 1 - (PreviewImage.imageData[i]);i++;
		i += (PreviewImage.width-1)*3;
	}

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
	//action=false;
	printf("%03f %03f", curx, cury);

    gentex(PreviewImage);
	PreviewImage.width  = pImageWidth;
	PreviewImage.height = pImageHeight;
	PreviewImage.bpp	= 24;
	PreviewImage.imageData	= (GLubyte *)malloc(pImageWidth*pImageHeight*24);

	glGenTextures(1, &PreviewImage.texID);
	glBindTexture(GL_TEXTURE_2D, PreviewImage.texID);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR  );
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR  );

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, PreviewImage.width, PreviewImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, PreviewImage.imageData);
	RefreshImage();

}

W_colorSelectdisplay::~W_colorSelectdisplay()
{
	if (PreviewImage.imageData)
    {
        free(PreviewImage.imageData);
    }
}


void W_colorSelectdisplay::Draw()
{

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, PreviewImage.texID);

	if (refresh){
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, PreviewImage.width, PreviewImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, PreviewImage.imageData);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, PreviewImage.width, PreviewImage.height, GL_RGB, GL_UNSIGNED_BYTE, PreviewImage.imageData);
		refresh=false;
	}
	glTranslated(posx, posy, 0);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2d(1,-1);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2d(width-1, -1);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2d(width-1, -height+1);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2d(1, -height+1);
	glEnd();

	glDisable(GL_TEXTURE_2D);


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
