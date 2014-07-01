// UI_base.cpp: base for every ui element (button, sliders,...).
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// SNICE : Simple Nodal Image Compositing Environment
// SNICE is a image and video compositing software
// Copyright by Sebastien Tricoire (3dsman@free.fr) and Lionel Allorge (lionel.allorge@lunerouge.org)
//
// based on Crafter (Leaf) Library by Wybren van Keulen (www.funnyfarm.tv)
// based on GLFW Library (www.glfw.org)
//
// UI_base.cpp
// This file is the UI_base class file
// File created by Tricoire Sebastien
// Date of creation : 2004 12 04
//
// File modified by
// Date of modification :
//
// Copyright (C) 2004 Sebastien Tricoire and Lionel Allorge.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 2 as published by the Free Software Foundation;
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//////////////////////////////////////////////////

#include "include/glfw.h"
#include "UI_base.h"
#include <stdlib.h>
//#include "viewports_array.h"
#include <string.h>

Textures UI_base::textures;
Font UI_base::font;

UI_base::UI_base(int x, int y, int w, int h, float red, float green, float blue)
{
	posx = x;
	posy = y;
	parentx = 0;
	parenty = 0;
	width = w;
	height = h;
	pParentUI_base = 0;

	visible = true;

	r = red;
	g = green;
	b = blue;

	killMe = false;
	pInterceptChild = 0;

	onMove = 0;
	onResize = 0;
};

UI_base::~UI_base()
{
	if (childList.ToFirst())
		do
		{
			delete ((UI_base*)childList.GetCurrentObjectPointer());
			childList.RemoveCurrent();
			childList.ToNext();
		}while(childList.GetCurrentObjectPointer());
};

void UI_base::SetWidth(int w)
{
	 width = w;
	if(onResize) onResize(this, width, height);
};

void UI_base::SetHeight(int h)
{
	 height = h;
	if(onResize) onResize(this, width, height);
};

void UI_base::SetPosX(int x)
{
	 SetPos(x, posy);
};

void UI_base::SetPosY(int y)
{
 	 SetPos(posx, y);
};

void UI_base::SetPos(int x, int y)
{
	posx = x;
	posy = y;

	if (childList.ToFirst())
		do
		{
			((UI_base*)childList.GetCurrentObjectPointer())->SetParentPos(parentx + x, parenty + y);
		}while(childList.ToNext());
	if(onMove) onMove(this, x, y);
}

void UI_base::GetPos(int *x, int *y)
{
	*x = posx;
	*y = posy;
}

void UI_base::SetParentPos(int x, int y)
{
	parentx = x;
	parenty = y;

	if (childList.ToFirst())
		do
		{
			((UI_base*)childList.GetCurrentObjectPointer())->SetParentPos(x + posx, y + posy);
		}while(childList.ToNext());
}

void UI_base::SetColor(float red, float green, float blue){
	r = red;
	g = green;
	b = blue;
};

void UI_base::GetRefName(string name)
{
	name = refName;// strcpy(name, refName);
};

void UI_base::SetRefName(string name)
{
	refName = name;
	//strcpy(refName, name);
};

void UI_base::AddChild(UI_base * child)
{
	if (child)
	{
		childList.Add(child);
		child->SetParentPos(posx,posy);
		child->SetParentUIbase(this);
	}
}

void UI_base::SupChild(UI_base * child)
{
	if (child)
	{
		childList.Remove(child);
		child->SetParentPos(0,0);
		child->SetParentUIbase(0);
        if (pInterceptChild == child) {pInterceptChild=0;}
	}
}

void UI_base::Draw()
{
	glTranslated(posx,posy,0);
	if (childList.ToFirst())
			do
			{
				((UI_base*)childList.GetCurrentObjectPointer())->Draw();
			}while(childList.ToNext());
	glTranslated(-posx,-posy,0);
}

void UI_base::Autokill(UI_base * child)
{
	if ((child!=0)&&(child->killMe))
    {
        SupChild(child);
        delete child;
    }
}

void UI_base::SetVisible(bool v)
{
	visible = v;
}

bool UI_base::Hittest(int x, int y){
	if ((x >= posx) && (x <= posx + width) && (y <= posy) && (y >= posy - height) && visible)
		return 1;
	return 0;
};

UI_base* UI_base::OnLButtonDown(int x, int y)
{
    if (pInterceptChild)
    {
        if (pInterceptChild!=this)
        {
            pInterceptChild = (pInterceptChild)->OnLButtonDown(x - posx, y - posy);
            Autokill(pInterceptChild);
        }
        if (pInterceptChild)
            return this;
        else
            return 0;
    };
	if (childList.ToFirst())
		do
		{
			childList.Push();
			pInterceptChild = ((UI_base*)childList.GetCurrentObjectPointer())->OnLButtonDown(x - posx, y - posy);
			childList.Pop();
            Autokill((UI_base*)childList.GetCurrentObjectPointer());
            if (pInterceptChild) {return this;};
		}while(childList.ToNext());
	return 0;
}

UI_base* UI_base::OnRButtonDown(int x, int y)
{
    if (pInterceptChild)
    {
        if (pInterceptChild!=this)
        {
            pInterceptChild = (pInterceptChild)->OnRButtonDown(x - posx, y - posy);
            Autokill(pInterceptChild);
        }
        if (pInterceptChild)
            return this;
        else
            return 0;
    };
	if (childList.ToFirst())
		do
		{
			childList.Push();
			pInterceptChild = ((UI_base*)childList.GetCurrentObjectPointer())->OnRButtonDown(x - posx, y - posy);
			childList.Pop();
            Autokill((UI_base*)childList.GetCurrentObjectPointer());
			if (pInterceptChild) {return this;};
		}while(childList.ToNext());
	return 0;
}

UI_base* UI_base::OnLButtonUp(int x, int y)
{
    if (pInterceptChild)
    {
        if (pInterceptChild!=this)
        {
            pInterceptChild = (pInterceptChild)->OnLButtonUp(x - posx, y - posy);
            Autokill(pInterceptChild);
        }
        if (pInterceptChild)
            return this;
        else
            return 0;
    };

	if (childList.ToFirst())
		do
		{
			childList.Push();
			pInterceptChild = ((UI_base*)childList.GetCurrentObjectPointer())->OnLButtonUp(x - posx, y - posy);
			childList.Pop();
            Autokill((UI_base*)childList.GetCurrentObjectPointer());
			if (pInterceptChild) {return this;};
		}while(childList.ToNext());
	return 0;
}

UI_base* UI_base::OnRButtonUp(int x, int y)
{
    if (pInterceptChild)
    {
        if (pInterceptChild!=this)
        {
            pInterceptChild = (pInterceptChild)->OnRButtonUp(x - posx, y - posy);
            Autokill(pInterceptChild);
        }
        if (pInterceptChild)
            return this;
        else
            return 0;
    };
	if (childList.ToFirst())
		do
		{
			childList.Push();
			pInterceptChild = ((UI_base*)childList.GetCurrentObjectPointer())->OnRButtonUp(x - posx, y - posy);
			childList.Pop();
            Autokill((UI_base*)childList.GetCurrentObjectPointer());
			if (pInterceptChild) {return this;};
		}while(childList.ToNext());
	return 0;
}

UI_base* UI_base::OnMouseMove(int x, int y, int prevx, int prevy)
{
    if (pInterceptChild)
    {
        if (pInterceptChild!=this)
        {
            pInterceptChild = (pInterceptChild)->OnMouseMove(x - posx, y - posy, prevx - posx, prevy - posy);
            Autokill(pInterceptChild);
        }
        if (pInterceptChild)
            return this;
        else
            return 0;
    };
	if (childList.ToFirst())
		do
		{
			childList.Push();
			pInterceptChild = ((UI_base*)childList.GetCurrentObjectPointer())->OnMouseMove(x - posx, y - posy, prevx - posx, prevy - posy);
			childList.Pop();
            Autokill((UI_base*)childList.GetCurrentObjectPointer());
			if (pInterceptChild) {return this;};
		}while(childList.ToNext());
	return 0;
}

UI_base* UI_base::OnKeyPressed(int key)
{
    if (pInterceptChild)
    {
        if (pInterceptChild!=this)
        {
            pInterceptChild = (pInterceptChild)->OnKeyPressed(key);
            Autokill(pInterceptChild);
        }
        if (pInterceptChild)
            return this;
        else
            return 0;
    };
	if (childList.ToFirst())
		do
		{
			childList.Push();
			pInterceptChild = ((UI_base*)childList.GetCurrentObjectPointer())->OnKeyPressed(key);
			childList.Pop();
            Autokill((UI_base*)childList.GetCurrentObjectPointer());
			if (pInterceptChild) {return this;};
		}while(childList.ToNext());
	return 0;
}

UI_base* UI_base::OnCharPressed(int character)
{
    if (pInterceptChild)
    {
        if (pInterceptChild!=this)
        {
            pInterceptChild = (pInterceptChild)->OnCharPressed(character);
            Autokill(pInterceptChild);
        }
        if (pInterceptChild)
            return this;
        else
            return 0;
    };
	if (childList.ToFirst())
		do
		{
			childList.Push();
			pInterceptChild = ((UI_base*)childList.GetCurrentObjectPointer())->OnCharPressed(character);
			childList.Pop();
            Autokill((UI_base*)childList.GetCurrentObjectPointer());
			if (pInterceptChild) {return this;};
		}while(childList.ToNext());
	return 0;
}
/*
void UI_base::OnLButtonDownIntercept(int x, int y){};

void UI_base::OnLButtonUpIntercept(int x, int y){};

void UI_base::OnMouseMoveIntercept(int x, int y, int prevx, int prevy){};

void UI_base::OnKeyPressedIntercept(int key){};

void UI_base::OnCharPressedIntercept(int character){};
*/
void UI_base::SetParentUIbase(UI_base* pUI_base)
{
	pParentUI_base = pUI_base;
}

bool UI_base::GetScreenToLocalMatrix(UI_base * object, float *x, float *y, float *zoom)
{
	if ((pParentUI_base) && (pParentUI_base->GetScreenToLocalMatrix(this, x, y, zoom)))
	{
		if (object != this)
		{
			*x += posx;
			*y += posy;
		}
		return true;
	}

//	printf("pas de pParentUI_base pour %s",refName);
	return false;
}


void UI_base::Set(char* order)
{
//	printf("->%s", refName);
 	char childName[256];

 	for (int i=0; i<256; ++i)
	    childName[i]=0;
	char* separator = strchr(order,'.');
	if (!separator)
	    separator = strchr(order,'=');
	if (separator)
	{
	 	int separatorPos = separator - order ;

	 	strncpy( childName, order,separatorPos);

	 	UI_base* pChild;
	 	char childRefName[256];
		if (childList.ToFirst())
		do
		{
			pChild = (UI_base*)(childList.GetCurrentObjectPointer());
			pChild->GetRefName(childRefName);
			if (strcmp(childRefName, childName) == 0)
			   pChild->Set(order + separatorPos + 1);
		}while (childList.ToNext());
	}
};


void UI_base::OnResize(void (*function)(UI_base* caller, int w, int h))
{
    onResize = function;
}

void UI_base::OnMove(void (*function)(UI_base* caller, int x, int y))
{
    onMove = function;
}

bool UI_base::SetTexture(Texture *texture, char* path)
{
    if (!LoadTGA(texture,path)){return false;}
    glGenTextures(1, &texture->texID);				// Create The Texture
    glBindTexture(GL_TEXTURE_2D, texture->texID);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->imageData);
    if (texture->imageData){ free(texture->imageData);}
    return true;
}

bool UI_base::SetFont( char* path, int charWidth)
{
    font.charWidth = charWidth;
    if (!SetTexture(&font.texture, path))			{return false;}

    font.fontList = glGenLists(256);									// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, font.texture.texID);		// Select Our Font Texture
	for (int loop1=0; loop1<256; ++loop1)					// Loop Through All 256 Lists
	{
		float cx = float(loop1%16)/16.0f;					// X Position Of Current Character
		float cy = float(loop1/16)/16.0f;					// Y Position Of Current Character


		glNewList(font.fontList+loop1,GL_COMPILE);					// Start Building A List
			glBegin(GL_QUADS);								// Use A Quad For Each Character
				glTexCoord2f(cx,1.0f-cy-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2d(0,16);							// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(16,16);							// Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.001f);	// Texture Coord (Top Right)
				glVertex2i(16,0);							// Vertex Coord (Top Right)
				glTexCoord2f(cx,1.0f-cy-0.001f);			// Texture Coord (Top Left)
				glVertex2i(0,0);							// Vertex Coord (Top Left)
			glEnd();										// Done Building Our Quad (Character)
			glTranslated(charWidth,0,0);					// Move To The Right Of The Character
		glEndList();										// Done Building The Display List
	}
	return true;
}

bool UI_base::InitTextures()
{
    if (!SetTexture(&textures.slider,"Data/slider.tga")){return false;} //old index 8
    if (!SetTexture(&textures.button,"Data/buttons.tga")){return false;} //old index 9
	if (!SetTexture(&textures.buttonPress,"Data/butpress.tga")){return false;} //old index 13
	if (!SetTexture(&textures.specular,"Data/specularbig.tga")){return false;} //old index 10
	if (!SetTexture(&textures.progress,"Data/progress.tga")){return false;} //old index 11
	if (!SetTexture(&textures.shadow,"Data/shadow.tga")){return false;} //old index 1
	if (!SetTexture(&textures.cursor,"Data/cursor.tga")){return false;} //old index 12

	if (!SetFont("Data/Fontanti.tga", 7)){return false;} //old index 0
	return true;

}

bool UI_base::DestroyTextures()
{
    glDeleteLists(font.fontList,256);
    return true;
}

// End of file UI_base.cpp
