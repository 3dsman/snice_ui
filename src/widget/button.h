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

#ifndef _SNICE_BUTTON_H_
#define _SNICE_BUTTON_H_

#include <functional>
#include "widget/UI_widget.h"
#include "widget/label.h"

class W_button : public UI_widget
{
protected:

	W_label* text;
	//char name[256];

	bool pressed;
	bool active;
	std::function<void(W_button* caller)> onMouseOver = NULL;
	std::function<void(W_button* caller)> onMouseOut = NULL;
	std::function<void(W_button* caller)> onClick = NULL;
	/*void (*onMouseOver)(W_button* caller) = NULL;
	void (*onMouseOut)(W_button* caller) = NULL;
	void (*onClick)(W_button* caller) = NULL;*/

	void SetLabel(string l);

public:

	W_button(int x, int y, int w, int h, string l);

	virtual ~W_button();

    /**	\brief Set the button's label.*/
	void SetName(string l);

    /**	\brief Set the width.*/
	void SetWidth(int w);

    /**	\brief Set the horizontal position of the button.*/
	void SetPosX(int x);

    /**	\brief Set the vertical position of the button.*/
	void SetPosY(int y);

    /**	\brief return true if the button is pressed.*/
	bool IsPressed();

    /**	\brief set the press state of the button.*/
	void SetPressed(bool p);

    /**	\brief function to set the OnMouseOver callback function.*/
	void OnMouseOver(std::function<void(W_button* caller)> function);
    /**	\brief function to set the OnMouseOut callback function.*/
	void OnMouseOut(std::function<void(W_button* caller)> function);
    /**	\brief function to set the OnClick callback function.*/
	void OnClick(std::function<void(W_button* caller)> function);

    /**	\brief draw the button.*/
	void Draw();

	/**	\brief left button down function.*/
	virtual UI_base* OnLButtonDown(int x, int y);
	/**	\brief left button up function.*/
	virtual UI_base* OnLButtonUp(int x, int y);
	/**	\brief mouse move function.*/
	virtual UI_base* OnMouseMove(int x, int y, int prevx, int prevy);

	virtual void LoadXML(TiXmlElement* element);

	virtual void SaveXML(TiXmlElement* element);

	virtual void Set(char* order);
};

#endif //_SNICE_BUTTON_H_

// End of file button.h
