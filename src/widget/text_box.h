// crafter interface library
// Funny Farm
// copyright � 2002 Wybren van Keulen
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

#ifndef _SNICE_TEXTBOX_H_
#define _SNICE_TEXTBOX_H_

#include "widget/UI_widget.h"
#include "widget/label.h"
#include <functional>

class W_textbox : public UI_widget
{
private:

	unsigned short initialWidth;

	W_label* text;
	string prompt;

	string contents;
	unsigned char key[256];
	unsigned short curPos;
	bool number;
    bool integ;
	bool decimal;
	bool action;
	bool drawContour;

    //void (*onSetContent)(W_textbox* caller, string content) = NULL;
	std::function<void(W_textbox* caller, string content)> onSetContent = NULL;


	void SetLabel(string l);

	void SetLabel();

public:

	W_textbox(int x, int y, int w, int h, string l, string c, bool num = false, bool integer = true, bool deci = false, bool contour = true, float r = 0.3f, float g = 0.3f, float b = 0.3f);

	virtual ~W_textbox();


	char* GetContent();

	void SetContent(const string c);

	void Draw();

	/** \brief To set the width of the object.*/
	virtual void SetWidth(int w);
/*
	void OnLButtonDown(int x, int y);

	void OnLButtonUp(int x, int y);

	virtual void OnLButtonUpIntercept(int x, int y);

	void OnMouseMove(int x, int y, int prevx, int prevy);

	void OnKeyPressed(int key);

	void OnCharPressedIntercept(int character);

	virtual void OnKeyPressedIntercept(int key);
*/

    /**	\brief function to set the OnSetContent callback function.*/
	void OnSetContent(void (*function)(W_textbox* caller, string content));

	/**	\brief left button down function.*/
	virtual UI_base* OnLButtonDown(int x, int y);
	/**	\brief left button up function.*/
	virtual UI_base* OnLButtonUp(int x, int y);
	/**	\brief mouse move function.*/
	virtual UI_base* OnMouseMove(int x, int y, int prevx, int prevy);
	/**	\brief char pressed function.*/
	virtual UI_base* OnKeyPressed(int key);
	/**	\brief char pressed function.*/
	virtual UI_base* OnCharPressed(int character);

	void LoadXML(TiXmlElement* element);

	void SaveXML(TiXmlElement* element);

	virtual void Set(char* order);
};

#endif // _SNICE_TEXTBOX_H_

// End of file textBox.h
