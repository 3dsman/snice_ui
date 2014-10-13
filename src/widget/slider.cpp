// crafter interface library
// Funny Farm
// copyright � 2002 Wybren van Keulen
// www.funnyfarm.tv

// File created by Tricoire Sebastien
// Date of creation : 2004 06 02
///
// File modified by Lionel Allorge
// Date of modification : 2004 06 02

// File modified by Tricoire Sebastien
// Date of modification : 2004 10 15
// ???: creation of barSize
// ???: hiding label when name is empty


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

//#include "snice.h"
//#include "global.h"
//#include "prefs.h"

//#include "viewports_array.h"

#include "widget/slider.h"
#include "../snice_UI.h"

W_slider::W_slider(int x, int y, int w, int h, string l, float v, float f, float t, int p, float bar, float r, float g, float b)
		:UI_widget(x, y, w, h, r, g, b)
{
	Init(x,y,w,h,l,v,f,t,p,bar,r,g,b);
}
/*
W_slider::W_slider(int x, int y, int w, int h, string l, float v, float f, float t, int p, float r, float g, float b)
		:UI_widget(x, y, w, h, r, g, b)
{
	Init(x,y,w,h,l,v,f,t,p,0.0f,r,g,b);

}*/

W_slider::~W_slider()
{
	//delete text;
}

void W_slider::Init(int x, int y, int w, int h, string l, float v, float f, float t, int p, float bar, float red, float green, float blue)
{
/*	posx = x;
	posy = y;
	width = w;
	height = h;
*/
	value = v;
	from = f;
	to = t;
	precision = p;
	barSize = bar;
	mouseOffset = 0;

	refName = l;
	sprintf(name, "%s", l.c_str());
	//text = new W_label(x+width/2-(strlen(l)*7)/2-4, y-2, 0, 1, name);
	text = new W_label(width/2-(l.size()*7)/2-4, 8-(height/2), 0, 1, name);
	this->AddChild(text);
	SetLabel();

	action = false;
/*
	r = red;
	g = green;
	b = blue;
*/
	onSetValue = 0;
}

void W_slider::SetName(char *l)
{
    if (strlen(l)< 256)
	{
	   //delete text;
	   sprintf(name, "%s", l);
	   //text = new W_label(posx+width/2-(strlen(l)*7)/2-4, posy-2, 0, 1, name);
	   SetLabel();
	}
}


void W_slider::SetLabel(char *l)
{
	if (strlen(l)< 256)
	{
		text->SetText(l);
		text->SetPos(width/2-(strlen(l)*7)/2-4, 8-(height/2));
	}
}

void W_slider::SetLabel()
{
	char buttontext[14];
	sprintf(buttontext, "%s: %.*f", name, precision, value);
	SetLabel(&buttontext[0]);
}

void W_slider::SetWidth(int w)
{
	width = w;
	SetLabel();
}

void W_slider::SetPosY(int y)
{
	posy = y;
	SetLabel();
}

void W_slider::SetFrom(float f)
{
	from = f;
	if (value<from)
	{
	   value = from;
	   if(onSetValue) onSetValue(this, value, 0);
    }
	barSize = min(barSize,to-value);
}


void W_slider::SetTo(float t)
{
	to = t;
	if (value>to)
	{
	   value = to;
	   if(onSetValue) onSetValue(this, value, 0);
    }
	barSize = min(barSize,to-value);
}

void W_slider::SetPrecision(int p)
{
	precision = p;
}

void W_slider::SetBarSize(float b)
{
	barSize = min(b,to-value);
}

int W_slider::GetWidth()
{
	return width;
}

float W_slider::GetFrom()
{
	return from;
}


float W_slider::GetTo()
{
	return to;
}

int W_slider::GetPrecision()
{
	return precision;
}

float W_slider::GetBarSize()
{
	return barSize;
}


void W_slider::Draw()
{
	glTranslated(posx, posy, 0);
	// Black outlining
	/*glColor4f(0.3f,0.3f,0.3f,0.5f);
	glBegin(GL_POLYGON);
		glVertex2d(6, 0);
		glVertex2d(width-6, 0);
		glVertex2d(width-2, -1);
		glVertex2d(width-1, -3);
		glVertex2d(width, -6);
		glVertex2d(width, -height+6);
		glVertex2d(width-1, -height+2);
		glVertex2d(width-3, -height+1);
		glVertex2d(width-6, -height);
		glVertex2d(6, -height);
		glVertex2d(2, -height+1);
		glVertex2d(1, -height+3);
		glVertex2d(0, -height+6);
		glVertex2d(0, -6);
		glVertex2d(1, -2);
		glVertex2d(3, -1);
		glVertex2d(6, 0);
	glEnd();*/

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	// Fill
	// glColor4f(1.0f, 1.0f, 1.0f,0.6f);
	// glColor4f(0.64f, 0.59f, 0.53f,1.0f);
	// glColor4f(0.75f, 0.75f, 0.75f,1.0f);
	// glColor4f(1.0f, 1.0f, 1.0f,0.4f);
	glColor4f(1.0f, 1.0f, 1.0f,0.4f);
	glBegin(GL_POLYGON);
		glVertex2d(6, -1);
		glVertex2d(width-6, -1);
		glVertex2d(width-2, -2);
		glVertex2d(width-1, -4);
		glVertex2d(width-1, -6);
		glVertex2d(width-1, -height+6);
		glVertex2d(width-2, -height+2);
		glVertex2d(width-4, -height+1);
		glVertex2d(width-6, -height+1);
		glVertex2d(6, -height+1);
		glVertex2d(2, -height+2);
		glVertex2d(1, -height+4);
		glVertex2d(1, -height+5);
		glVertex2d(1, -7);
		glVertex2d(2, -2);
		glVertex2d(4, -1);
		glVertex2d(6, 0);
	glEnd();

	// draw a stripe in the buttons to indicate the current value
	glBegin(GL_QUADS);
		glColor4f(r,g,b,0.3f);

		glVertex2d((value-from)/(to-from)*width,-1);
		glVertex2d((value-from)/(to-from)*width,-height+1);
		if (barSize){
			glVertex2d((value+barSize-from)/(to-from)*width,-height+1);
			glVertex2d((value+barSize-from)/(to-from)*width, -1);
		}
		else{
			glVertex2d(0,-height+1);
			glVertex2d(0, -1);
		}
	glEnd();



	// draw the border
	glColor4f(1.0f,1.0f,1.0f,0.7f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures.slider.texID);

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

	//if (pPrefs->GetCute())
	//{
		glBindTexture(GL_TEXTURE_2D, textures.specular.texID);
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
	//}

	glDisable(GL_TEXTURE_2D);

	glTranslated(-posx,-posy,0);

	// glColor4f(0.7f,0.7f,0.7f,0.4f);	// for not antialiased font
	glColor4f(0.5f,0.5f,0.5f,0.5f);

	//if (strcmp(name,""))				// Draw text only if there is a name
		//text->Draw();
	   UI_widget::Draw();
}

void W_slider::OnSetValue(void (*function)(W_slider* caller, float value, bool realtime))
{
    onSetValue = function;
}

UI_base* W_slider::OnLButtonDown(int x, int y)
{
	if (Hittest(x,y))
	{
		if (barSize)
		{
			if ((((float)(x-posx)/width)*(to-from)+from)<value)
			{
				tmpValue = max(value - barSize,from);
				//if (pParentUI_base)
				//pParentUI_base->Callback(this,1);
			}
			else if ((((float)(x-posx)/width)*(to-from)+from)>(value + barSize))
			{
				tmpValue = min(value + barSize,to);
				//if (pParentUI_base)
				//	pParentUI_base->Callback(this,1);
			}
			else
			{
				//if (pParentUI_base)
				//	pParentUI_base->Callback(this,1);
				action = true;
			}
		}
		else
		{
			tmpValue = (float)(x-posx)/width*(to-from)+from;
			//if (pParentUI_base)
			//	pParentUI_base->Callback(this,1);
			action = true;
		}
		value = max(min(tmpValue, to - barSize),from);

		SetLabel();

		if(onSetValue) onSetValue(this, value, 1);
		//pViewports->setIntercept(this);
		pInterceptChild = this;
		return this;
	}
	pInterceptChild = 0;
	return 0;
}

UI_base* W_slider::OnLButtonUp(int x, int y)
{
    if ((pInterceptChild == this)&&(onSetValue)) onSetValue(this, value, 0);
	//action = false;
	pInterceptChild = 0;
	return 0;
}

UI_base* W_slider::OnMouseMove(int x, int y, int prevx, int prevy)
{
    if (pInterceptChild == this)
    {
    	//if (action)
    	//{
            tmpValue+=((float)(x-prevx)/width*(to-from));
    		value = max(min(tmpValue,to - barSize),from);
    		SetLabel();
    		if(onSetValue) onSetValue(this, value, 1);
    	//}
        return this;
    }
	return 0;
}

float W_slider::GetValue()
{
	return value;
}

void W_slider::SetValue(float v)
{
	value = v;
	if (value > to) value = to;
	if (value < from) value = from;
	SetLabel();
}

void W_slider::LoadXML(TiXmlElement* element)
{
	double progressValue;
	element->QueryDoubleAttribute("Value",&progressValue);
	SetValue((float)progressValue);

	double red, green, blue;
	if (!(element->QueryDoubleAttribute("Red",&red) == TIXML_NO_ATTRIBUTE)) {r = (float)red;};
	if (!(element->QueryDoubleAttribute("Green",&green) == TIXML_NO_ATTRIBUTE)) {g = (float)green;};
	if (!(element->QueryDoubleAttribute("Blue",&blue) == TIXML_NO_ATTRIBUTE)) {b = (float)blue;};
}

void W_slider::SaveXML(TiXmlElement* element)
{

	//creation of the ColorBand xml flag
	TiXmlElement NodeSlider( refName.c_str() );

	// writing of the slider parameters into the xml hierarchy (as attribute of the argument element)
	char buf[256];

	sprintf( buf, "%f", value );
	NodeSlider.SetAttribute ("Value", buf);

	element->InsertEndChild( NodeSlider );
}


void W_slider::Set(char* order)
{
	printf("->%s=%s\n", refName.c_str(), order);
    SetValue(atof(order));
    //if (pParentUI_base) pParentUI_base->Callback(this,1);
};
