// UI_widget.cpp: base for every ui element (button, sliders,...).
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
// UI_widget.cpp
// This file is the UI_widget class file
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


////////////////////////////////////////
// class UI_widget.
// Class for widget definition
////////////////////////////////////////


#include "widget/UI_widget.h"

    //Widget_textures UI_widget::textures;

	UI_widget::UI_widget(int x, int y, int w, int h, float r, float g, float b)
			  :UI_base(x, y, w, h, r, g, b){};

	UI_widget::~UI_widget(){};
	

	void UI_widget::LoadXML(TiXmlElement* element){};

	void UI_widget::SaveXML(TiXmlElement* element){};

	
// End of file UI_widget.cpp
