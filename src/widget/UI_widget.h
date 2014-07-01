// UI_widget.h: Widgets base class.
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
// UI_widget.h
// This file is the Colorize node file
// File created by Tricoire Sebastien
// Date of creation : 2004 12 04
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

#ifndef _SNICE_UI_WIDGET_H_
#define _SNICE_UI_WIDGET_H_

#include "UI_base.h"
#include "xml/tinyxml.h"

////////////////////////////////////////
// class UI_widget.
// Class for all widget objects
////////////////////////////////////////
	/**	\brief Class for all widget objects.

		UI_widget is the base class for all widget objects (buttons, sliders, editbox,...).
	*/

        
class UI_widget: public UI_base
{

protected:

public:
    //static struct Widget_textures Textures ;
	/**
		 \param x x position
		 \param y y position
		 \param w width
		 \param h height
		 \param r red color as float [0;1]
		 \param g green color as float [0;1]
		 \param b blue color as float [0;1]
	*/
	UI_widget(int x, int y, int w, int h, float r = 0.3f, float g = 0.3f, float b = 0.3f);

	virtual ~UI_widget();

	/**	\brief This function is called by a child of the object for callback.
	
	this function is'nt defined as a pure virtual because most of the widgets don't need it*/
	virtual void Callback(UI_base * pCallObject, unsigned char callIndex ) {};

	/** \brief To load widget's parameters whith XML */
	virtual void LoadXML(TiXmlElement* element);

	/** \brief To save widget's parameters whith XML */
	virtual void SaveXML(TiXmlElement* element);

};

#endif //_SNICE_UI_WIDGET_H_

// End of file UI_widget.h
