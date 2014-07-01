// viewport.h: window base class.
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
// viewport.h
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

#ifndef _SNICE_Viewport_H_
#define _SNICE_Viewport_H_

#include "UI_base.h"


class UI_widget;

class Viewport : public UI_base
{
	
protected:
	float scrollx; /**< \brief  Horizontal scroll position*/
	float scrolly; /**< \brief  Vertical scroll position*/
	float viewZoom; /**< \brief  Zoom factor (not used for now)*/
	/** \brief funtion to draw the content of the viewport*/
	
	void (*onDraw)(UI_base* caller);
	//virtual void DrawOn(){};
public:
	//Viewport();
	Viewport(int x, int y,int w, int h);

	virtual ~Viewport();

	virtual UI_base* OnMouseMove(int x, int y, int prevx, int prevy);

	//virtual UI_base* OnKeyPressed(int key);

	//virtual UI_base* OnCharPressed(int character);
	
	virtual bool GetScreenToLocalMatrix(UI_base * object, float *x, float *y, float *zoom);
	
	void Callback(UI_base * pCallObject, unsigned char callIndex );

	/**	\brief Function called when we resize the viewport .*/
	virtual void Resize(int x, int y,int w, int h);
	
	
	void setOnDraw(void (*function)(UI_base* caller));

	void Draw();
};

#endif //_SNICE_Viewport_H_

// End of file window.h
