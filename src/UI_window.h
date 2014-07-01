// UI_window.h: base for every windows (nodes, dialogboxes, ...).
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
// UI_window.h
// This file is the UI_window class file
// File created by Tricoire Sebastien
// Date of creation : 2005 20 03
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

#ifndef _SNICE_WINDOWS_H_
#define _SNICE_WINDOWS_H_

#include "UI_base.h"
class W_label;

	/**	\brief base class for windows.

		UI_window is the base class for the windows (dialogs and node class).
	*/
class UI_window :public UI_base		// Base class for windows (dialogs and node class).
{
protected:

	bool folded;		/**<	\brief true if the window is minimized.*/
	bool foldable;	/**<	\brief true if the window is minimizeable.*/
	unsigned char openclosing;	/**<	\brief true during the minimization of the window.*/
	bool closeable;	/**<	\brief true if the window is closeable.*/
	bool dragging;		/**<	\brief true during the drag of the window.*/
	bool dragable;	/**<	\brief true if the window is dragable.*/
	bool onTop;			/**<	\brief true if the window is on top.*/

	int outlineWidth;					/**<	\brief outline width.*/
	bool outlineStripple;				/**<	\brief true if outline is strippled.*/
	float outlineR,outlineG,outlineB; 	/**<	\brief Color of the outline */

	static unsigned char foldSteps;

	W_label* pTitlelabel;	/**<	\brief title of the window (you can get it with GetName()).*/


	void (*onClose)(UI_window* caller);
	void (*onFold)(UI_window* caller);
	void (*onUnfold)(UI_window* caller);

public:

	/**	\brief Default constructor.*/
	//UI_window();
	//UI_window(int x, int y);
	UI_window(int x, int y, int w, int h, string winName, bool closeable = true, bool foldable = true, bool dragable = true, bool folded = false);

	virtual ~UI_window();

	/**	\brief To get the left limit of the window.*/
	int GetLeft();
	/**	\brief To get the right limit of the window.*/
	int GetRight();
	/**	\brief To get the bottom limit of the window.*/
	int GetBottom();
	/**	\brief To get the top limit of the window.*/
	int GetTop();

	/** \brief static function to set the fold steps */
	static void SetFoldSteps(unsigned char steps);

	/**	\brief Get the window's name (writed on the top of the window).*/
	char* GetName();

	/**	\brief Set the window's name (writed on the top of the window).*/
	void SetName(char* winName);


	/**	\brief function to get unique name for node.*/
	//void MakeUniqueName(char* winName);

    /**	\brief function to set the onClose callback function.*/
	void OnClose(void (*function)(UI_window* caller));
    /**	\brief function to set the OnFold callback function.*/
	void OnFold(void (*function)(UI_window* caller));
    /**	\brief function to set the OnUnfold callback function.*/
	void OnUnfold(void (*function)(UI_window* caller));


	/**	\brief Function that draw the window.*/
	virtual void Draw();

	/**	\brief To draw the window's widgets.*/
	virtual void DrawInterface(){};

	/**	\brief left button down function.*/
	virtual UI_base* OnLButtonDown(int x, int y);
	/**	\brief left button up function.*/
	virtual UI_base* OnLButtonUp(int x, int y);
	/**	\brief mouse move function.*/
	virtual UI_base* OnMouseMove(int x, int y, int prevx, int prevy);
	/**	\brief key pressed function.*/
	virtual UI_base* OnKeyPressed(int key);

	/**	\brief Return true if the coordinates are in the window (or only in the header if minimized).*/
	virtual bool Hittest(int x, int y);


};

#endif //_SNICE_WINDOW_H_

// End of file UI_window.h
