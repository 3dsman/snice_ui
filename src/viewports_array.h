// viewports_array.h: viewports_array class.
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
// viewports_array.h
// This file is the file of the imageViewport class
// File created by Tricoire Sebastien
// Date of creation : 2008 19 03
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

#ifndef _SNICE_VIEWPORTSARRAY_H_
#define _SNICE_VIEWPORTSARRAY_H_

#include "include/glfw.h"
#include "viewport.h"
#include "UI_window.h"

#include <vector>



class UI_base;

class ViewportsArray : public UI_base
{

protected:

private:
int iPrevMousePosx; // Horizontal mouse previous position
int iPrevMousePosy; // Vertical mouse previous position

int iMousePosx; // Horizontal mouse position
int iMousePosy; // Vertical mouse position

int WindowSizex; // Horizontal window position
int WindowSizey; // Vertical window position

std::vector<Viewport> Viewports;


UI_base* pMouseMoveIntercept;
UI_base* pLButtonDownIntercept;
UI_base* pLButtonUpIntercept;
UI_base* pKeyPressedIntercept;
UI_base* pCharPressedIntercept;

public:
float interceptx;
float intercepty;
float zoom;

	UI_base * deletewhendone;	/**<	\brief true if the viewports must be deleted*/

	Viewport* pView1;	/**<	\brief pointer to the viewport 1*/
	Viewport* pView2;	/**<	\brief pointer to the viewport 2*/

	UI_window* modalWindow;		/**<	\brief pointer to the modal window (dialog boxes)*/

	ViewportsArray(int x, int y,int w, int h);

	~ViewportsArray();

	UI_window* GetModalWindow(); 										/**<	\brief function that return pointer to the modalWindow*/
	UI_window* SetModalWindow(UI_window* window, UI_base* callback);	/**<	\brief function to set the modalWindow*/
	void DelModalWindow();												/**<	\brief function to destroy the modalWindow*/


	UI_base* OnLButtonDown(int x, int y);
	UI_base* OnRButtonDown(int x, int y);
	UI_base* OnLButtonUp(int x, int y);
	UI_base* OnRButtonUp(int x, int y);
	UI_base* OnMouseMove(int x, int y, int prevx, int prevy);
	UI_base* OnKeyPressed(int key);
	UI_base* OnCharPressed(int character);


	void Callback(UI_base * pCallObject, unsigned char callIndex );

	void setIntercept( UI_base * object );

	/**	\brief Funtion called to resize the viewport*/
	void Resize(int x, int y,int w, int h);

	void Draw();
};

#endif //_SNICE_VIEWPORTSARRAY_H_

// End of file viewports_array.h
