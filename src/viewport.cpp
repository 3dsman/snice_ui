// viewport.cpp: window base class.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// SNICE : Simple Nodal Image Compositing Environment
// SNICE is a image and video compositing software
// Copyright by Sebastien Tricoire (3dsman@free.fr) and Lionel Allorge (lionel.allorge@lunerouge.org)
///
// based on Crafter (Leaf) Library by Wybren van Keulen (www.funnyfarm.tv)
// based on GLFW Library (www.glfw.org)
// 
// viewport.cpp
// This file is the file of the window class
// File created by Tricoire Sebastien
// Date of creation : 2005 16 02
///
// File modified by 
// Date of modification :
///
// Copyright (C) 2004 Sebastien Tricoire and Lionel Allorge.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 2 as published by the Free Software Foundation;
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//////////////////////////////////////////////////

/////////////////////////////////////////////
// Includes
/////////////////////////////////////////////

//#include "include/glfw.h"
#include "snice_UI.h"
#include "viewport.h"
#include <stdio.h>

Viewport::Viewport(int x, int y,int w, int h)
		 :UI_base(x, y, w, h){
scrollx = 0;
scrolly = 0;
viewZoom = 1;

}

Viewport::~Viewport(){};

		
UI_base* Viewport::OnMouseMove(int x, int y, int prevx, int prevy)
{
    //if (!pParentUI_base) y = height-y;
    return UI_base::OnMouseMove(x, y, prevx, prevy);
};

//UI_base* Viewport::OnKeyPressed(int key){return 0;};

//UI_base* Viewport::OnCharPressed(int character){return 0;};

void Viewport::Resize(int x, int y,int w, int h)
{
	posx = x;
	posy = y;
	width = w;
	height = h;
	if(onResize) onResize(onResizeAsker, this, w, h);
};

void Viewport::setOnDraw(void (*function)(UI_base* caller))
{
    onDraw = function;
}

void Viewport::Draw()
{
	glViewport( posx, posy, width, height );			// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);					// Select The Projection Matrix
	glLoadIdentity();						// Reset The Projection Matrix

	glColor3f(r,g,b) ;
	glBegin(GL_QUADS) ;
	glVertex2f(-1,-1) ;
	glVertex2f(-1,1) ;
	glVertex2f(1,1) ;
	glVertex2f(1,-1) ;
	glEnd() ;
	glOrtho(0,width,0,height,-1,1);					// Set Up An Ortho Screen

	glMatrixMode(GL_MODELVIEW);					// Select The Modelview Matrix
	glLoadIdentity();						// Reset The Modelview Matrix
	if (childList.ToLast())
		do
		{
			((UI_base*)childList.GetCurrentObjectPointer())->Draw();
		}while(childList.ToPrevious());
	glLoadIdentity();
	
	if(onDraw) onDraw(this);
	//DrawOn();

};


bool Viewport::GetScreenToLocalMatrix(UI_base * object, float *x, float *y, float *zoom)
{
	//check if the object is not one of the childs of the viewport
	childList.Push();
	if (childList.ToFirst())
	do
	{
	
		if((UI_base*)childList.GetCurrentObjectPointer() == object)
		{
			*x += posx; 
			*y += posy;
			return true;
		}			
	}while(childList.ToNext());
	childList.Pop();

	*x += (posx + scrollx); 
	*y += (posy + scrolly);
	*zoom *= viewZoom;

	return true;
}

//void Viewport::Callback(UI_base * pCallObject, unsigned char callIndex ){};
