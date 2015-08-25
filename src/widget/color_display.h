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


#ifndef _SNICE_COLORDISPLAY_H_
#define _SNICE_COLORDISPLAY_H_

#include "widget/UI_widget.h"

//class D_ColorPicker;

typedef bool (*pt2Function)();

class W_colorDisplay : public UI_widget
{
private:
	int posx;
	int posy;

	int width;
	int height;

	//D_ColorPicker* pColorPicker;

	//void (*onClick)(W_colorDisplay* caller) = NULL;
	std::function<void(UI_base * asker, W_colorDisplay* caller)> onClick = NULL;
	UI_base * onClickAsker = NULL;
	//void (*onChange)(W_colorDisplay* caller,float red,float green, float blue) = NULL;
	std::function<void(UI_base * asker, W_colorDisplay* caller,float red,float green, float blue)> onChange = NULL;
	UI_base * onChangeAsker = NULL;
public:

	W_colorDisplay(int x, int y, int w, int h, string name, float r = 0.8f, float g = 0.8f, float b = 0.8f);

	~W_colorDisplay();


	void Draw();
	void SetColor(float r, float g, float b);

	void GetColor(float * r, float * g, float * b);

    /**	\brief function to set the onClic callback function.*/
	void OnClick(UI_base * asker, void (*function)(UI_base * asker, W_colorDisplay* caller));

    /**	\brief function to set the onChange callback function.*/
	void OnChange(UI_base * asker, void (*function)(UI_base * asker, W_colorDisplay* caller,float red,float green, float blue));

	float GetColor(int RGB);

	UI_base* OnLButtonDown(int x, int y);

	UI_base* OnLButtonUp(int x, int y);

	//void Callback(UI_base * pCallObject, unsigned char callIndex );

	void SetOnDrawFunction(pt2Function onDrawFunction);

	virtual void OnDraw();

	//void LoadXML(TiXmlElement* element);

	//void SaveXML(TiXmlElement* element);

	virtual void Set(char* order);
};

#endif // _SNICE_COLORDISPLAY_H_
