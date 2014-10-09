// crafter interface library
// Funny Farm
// copyright � 2002 Wybren van Keulen
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


#include "../snice_UI.h"
#include "widget/progress.h"

W_progress::W_progress(int x, int y, int w, int h, string l, float red, float green, float blue)
		:UI_widget(x, y, w, h, r, g, b)
{
	posx = x;
	posy = y;
	width = w;
	height = h;

	name = l;
	text = new W_label(x+width/2-(l.size()*7)/2-4,y-2, 0, 1, name);
	// setLabel();

	action = false;

	r = red;
	g = green;
	b = blue;

	value = 0.0f;
	speed = 0.03f;
}

W_progress::~W_progress()
{
	delete text;
}

void W_progress::SetName(string l)
{
	delete text;
	name = l;
	text = new W_label(posx+width/2-(l.size()*7)/2-4, posy-2, 0, 1, name);
	SetLabel();
}

void W_progress::SetLabel(string l)
{
	delete text;
	text = new W_label(posx+width/2-(l.size()*7)/2-4, posy-2, 0, 1, l);
}

void W_progress::SetLabel()
{
	string buttontext;
	//TODO decommenter ligne suivante
	//buttontext = name+": "+ value;

	SetLabel(buttontext);
}

void W_progress::SetWidth(int w)
{
	width = w;
	SetLabel();
}

void W_progress::SetPosY(int y)
{
	posy = y;
	SetLabel();
}
void W_progress::Draw()
{
	if (action)
		value = value + speed; if(value > 2*height) value = 0.0f;

	glTranslated(posx, posy, 0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	// Fill
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

	// glScissor(parentx+posx+scrollx,parenty+posy+scrolly-20,width,height);
	// glEnable(GL_SCISSOR_TEST);


	glEnable(GL_TEXTURE_2D);
	glColor4f(r,g,b,1.0f);
	//glBindTexture(GL_TEXTURE_2D, textures[11].texID);
	glBindTexture(GL_TEXTURE_2D, textures.progress.texID);

	glBegin(GL_QUADS);
		glTexCoord2f(value/height*2, 1.0f);
		glVertex2d(0,-1);
		glTexCoord2f(value/height*2+width/25, 1.0f);
		glVertex2d(width,-1);
		glTexCoord2f(value/height*2+width/25, 0.0f);
		glVertex2d(width,-height+1);
		glTexCoord2f(value/height*2,0.0f);
		glVertex2d(0,-height+1);
	glEnd();



	// draw the border
	glColor4f(1.0f,1.0f,1.0f,0.7f);

	//glBindTexture(GL_TEXTURE_2D, textures[8].texID);
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

	//glBindTexture(GL_TEXTURE_2D, textures[10].texID);
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

	glDisable(GL_TEXTURE_2D);

	glTranslated(-posx,-posy,0);

	// glColor4f(0.5f,0.5f,0.5f,0.5f);
	// text->Draw();
}

float W_progress::GetValue()
{
	return value;
}

void W_progress::SetValue(float v)
{
	// value = v;
	SetLabel();
}

float W_progress::GetAction()
{
	return action;
}

void W_progress::SetAction(bool a)
{
	action = a;
}

float W_progress::GetSpeed()
{
	return speed;
}

void W_progress::SetSpeed(float s)
{
	speed = s;
}

void W_progress::LoadXML(TiXmlElement* element)
{
	double progressValue;
	element->Attribute("Value",&progressValue);
	SetValue((float)progressValue);
}
