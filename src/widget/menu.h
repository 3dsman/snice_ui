// crafter interface library
// Funny Farm
// copyright © 2002 Wybren van Keulen
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

#ifndef _SNICE_MENU_H_
#define _SNICE_MENU_H_

#include "widget/UI_widget.h"
#include "widget/button.h"
#include "mylist.h"


class W_subMenu;

class W_menu  : public W_button
{
private:
	W_subMenu* childMenu;
	W_label* label;

public:

	W_menu(int x, int y, int w, int h, string l, float r = 0.3f, float g = 0.3f, float b = 0.3f);

	virtual ~W_menu();

	void pickOption(W_subMenu* caller, unsigned char option);

	void SetLabel(string l);

	void AddOption(string l, W_subMenu * optionsubMenu = 0);

	UI_base* OnLButtonDown(int x, int y);

	UI_base* OnLButtonUp(int x, int y);

	UI_base* OnMouseMove(int x, int y, int prevx, int prevy);

	void Callback(UI_base * pCallObject, unsigned char callIndex );

	string GetString();

	int GetOption();

	void SetOption(int v);

	void SetOption(char * text);

	void Flush(); // delete all options

    /**	\brief function to set the OnPickOption callback function.*/
	void OnPickOption(void (*function)(W_subMenu* caller, unsigned char option));

	void LoadXML(TiXmlElement* element);

	void SaveXML(TiXmlElement* element);

	virtual void Set(string order);
};

#endif //_SNICE_MENU_H_

// End of file menu.h
