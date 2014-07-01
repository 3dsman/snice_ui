// UI_dialog.h: base for every ui dialog boxes.
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
// UI_dialog.h
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


#ifndef _SNICE_DIALOG_H_
#define _SNICE_DIALOG_H_

#include "UI_window.h"

#include "widget/label.h"
class label;
class Node;

	/**	\brief base class for dialog boxes.

		UI_dialog is the base class for the dialog boxes (color picker, file picker,...).
	*/
class UI_dialog :public UI_window		// Base class for dialogs
{
protected:

	Node * callbackNode; /**< \brief The node we use for callback */
public:
	/**	\brief default constructor.*/
	UI_dialog(int _x, int _y, int _w, int _h, char* _nodeName, bool _minimized = false, bool _minimizeable = false);

	/**	\brief default destructor.*/
	virtual ~UI_dialog();

	/**	\brief To draw the dialog window's widgets.*/
	virtual void DrawInterface();

	/**	\brief To set the callback node (a dialog must return value to a node).*/
	virtual void SetCallbackNode(Node * _node);
};

#endif //_SNICE_DIALOG_H_

// End of file UI_dialog.h
