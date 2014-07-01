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
//#include "prefs.h"

#include "widget/button.h"
#include "include/glfw.h"

W_button::W_button(int x, int y, int w, int h, string l)
		 :UI_widget(x, y, w, h, 0.3f, 0.3f, 0.3f)
{
//	sprintf(refName, "%s", l);
	/*int pos = 0;
	do
	{
	  	if (l[pos] == ' ')
	  	   refName[pos] = '_';
	  	else
 	 		refName[pos] = l[pos];
	++pos;
	}*/
	refName=l;

	//while((l[pos] != 0)&&(pos < 254));
	//refName[pos] = 0;

	text = new W_label(width/2-(l.size()*7)/2-4,8-(height/2), 0, 1, l);
    this->AddChild(text);
	pressed = false;
	active = false;

	onMouseOver=0;
	onMouseOut=0;
	onClick=0;
}

W_button::~W_button()
{
	//delete text;
}

void W_button::SetLabel(string l)
{
	//delete text;
	//text = new W_label(width/2-(strlen(l)*7)/2-4, 8-(height/2), 0, 1, l);
	text->SetPos(width/2-(l.size()*font.charWidth)/2-4, 8-(height/2));
	text->SetWidth(0);
	text->SetText(l);
}

void W_button::SetName(string l)
{
	//sprintf(refName, "%s", l);
	refName = l;
	SetLabel(refName);
}

void W_button::SetWidth(int w)
{
	width = w;
	SetLabel(refName);
}

void W_button::SetPosX(int x)
{
	posx = x;
	SetLabel(refName);
}

void W_button::SetPosY(int y)
{
	posy = y;
	SetLabel(refName);
}

bool W_button::IsPressed()
{
	return pressed;
}

void W_button::SetPressed(bool p)
{
	pressed = p;
}

void W_button::Draw()
{
	glTranslated(posx, posy, 0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	if (pressed)	{ glColor4f(0.6f,0.6f,0.6f,0.7f); if(active) glColor4f(0.75f,0.75f,0.75f,0.7f);}
	else			{ glColor4f(0.95f,0.95f,0.95f,0.7f); if(active) glColor4f(1.0f,1.0f,1.0f,0.9f);}

	// draw the border
	//glColor4f(1.0f,1.0f,1.0f,0.7f);
	//if (pressed) glColor4f(0.8f,0.8f,0.8f,0.7f);

	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textures[9].texID);
	glBindTexture(GL_TEXTURE_2D, textures.button.texID);
	//if (pressed) glBindTexture(GL_TEXTURE_2D, textures[13].texID);
	if (pressed) glBindTexture(GL_TEXTURE_2D, textures.buttonPress.texID);
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

		glTexCoord2f(0.25f,0.75f);
		glVertex2d(8, -8);
		glTexCoord2f(0.75f,0.75f);
		glVertex2d(width-8, -8);
		glTexCoord2f(0.75f,0.25f);
		glVertex2d(width-8, -height+8);
		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -height+8);
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

	glColor4f(0.4f,0.4f,0.4f,0.5f);
	UI_widget::Draw();

}


void W_button::OnMouseOver(void (*function)(W_button* caller))
{
    onMouseOver = function;
}

void W_button::OnMouseOut(void (*function)(W_button* caller))
{
    onMouseOut = function;
}

void W_button::OnClick(void (*function)(W_button* caller))
{
    onClick = function;
}

UI_base* W_button::OnLButtonDown(int x, int y)
{
	if (Hittest(x,y))
	{
        pressed = !pressed;
		pInterceptChild = this;
		return this;
	}
	return NULL;
}

UI_base* W_button::OnLButtonUp(int x, int y)
{
	if (pInterceptChild == this)
	{
        if (Hittest(x,y))
	    {
            if(onClick) onClick(this);
        }
            pressed = !pressed;
    }
    pInterceptChild = 0;
    return 0;
}

UI_base* W_button::OnMouseMove(int x, int y, int prevx, int prevy)
{
    if(Hittest(x,y))
    {
        if(!active)
        {
            active = true;
            if(onMouseOver) onMouseOver(this);
        }
    }else
    {
        if(active)
        {
            active = false;
            if(onMouseOut) onMouseOut(this);
        }
    }
    if (pInterceptChild) return this;
    return 0;
}


void W_button::LoadXML(TiXmlElement* element)
{
	const char * pressedAttribute = element->Attribute("Pressed");
	pressed = false;
	if (pressedAttribute!=NULL){
		if(strncmp(pressedAttribute,"true",4) == 0){pressed = true;};
	}
}

void W_button::SaveXML(TiXmlElement* element)
{
	TiXmlElement NodeButton( refName.c_str() );

	char buf[256];
	if (pressed)
		sprintf( buf, "true");
	else
		sprintf( buf, "false");

	NodeButton.SetAttribute ("Pressed", buf);
	element->InsertEndChild( NodeButton );
}


void W_button::Set(char* order)
{
	//printf("->%s=%s\n", refName, order);
    if (strcmp(order, "true")) {SetPressed(true);}
        else if (strcmp(order, "false")) {SetPressed(false);}
		  	else {SetPressed(atoi(order));}
//	if (pParentUI_base)pParentUI_base->Callback(this,1);
};
