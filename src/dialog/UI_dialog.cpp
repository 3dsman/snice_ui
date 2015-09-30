// UI_dialog.cpp: base for every ui dialog boxes.
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
// UI_dialog.cpp
// This file is the UI_dialog class file
// File created by Tricoire Sebastien
// Date of creation : 2005 05 01
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


////////////////////////////////////////
// class UI_dialog.
// Class for dialog definition
////////////////////////////////////////

//#include "nodes/node.h"
//#include "include/color_conversion.h"
#include "UI_dialog.h"

UI_dialog::UI_dialog(int _x, int _y, int _w, int _h, string _nodeName, bool _minimized, bool _minimizeable)
		  :UI_window(_x, _y, _w, _h, _nodeName, _minimized, _minimizeable)
{
	callbackNode = 0;
}

UI_dialog::~UI_dialog(){}

void UI_dialog::DrawInterface()
{
	if((openclosing == false)&&(folded == false))
		
		for(std::list<UI_base*>::iterator iter = childList.begin(); iter != childList.end(); iter ++)
		{
			(*iter)->Draw();
		}
		/*if (childList.ToLast())
			do
			{
				((UI_base*)childList.GetCurrentObjectPointer())->Draw();
			}while(childList.ToPrevious());*/
}

void UI_dialog::SetCallbackNode(Node * _node)
{
	callbackNode = _node;
}
