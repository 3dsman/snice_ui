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

#ifndef _SNICE_SLIDER_H_
#define _SNICE_SLIDER_H_

#include "widget/UI_widget.h"
#include "widget/label.h"

class W_slider : public UI_widget
{
private:
	W_label* text;
	char name[512];

	float value;
	float tmpValue;
	float from;
	float to;
	float barSize;
	float mouseOffset;
	int precision;

	bool action;

	void (*onSetValue)(W_slider* caller, float value, bool realtime);

	void Init(int x, int y, int w, int h, string l, float v, float f, float t, int p, float bar, float r, float g, float b);

public:

	W_slider(int x, int y, int w, int h, string l, float v, float f, float t, int p, float bar, float r, float g, float b);
	W_slider(int x, int y, int w, int h, string l, float v, float f, float t, int p, float r = 0.3f, float g = 0.3f, float b = 0.3f);

	virtual ~W_slider();

	void SetName(char *l);

	void SetLabel(char *l);

	void SetLabel();

	void SetWidth(int w);

	void SetPosY(int y);

	void SetFrom(float f);

	void SetTo(float t);

	void SetPrecision(int p);

	void SetBarSize(float b);

	int GetWidth();

	float GetFrom();

	float GetTo();

	int GetPrecision();

	float GetBarSize();

	void Draw();

	    /**	\brief function to set the OnValue callback function.*/
	void OnSetValue(void (*function)(W_slider* caller, float value, bool realtime));

	virtual UI_base* OnLButtonDown(int x, int y);

	virtual UI_base* OnLButtonUp(int x, int y);

	virtual UI_base* OnMouseMove(int x, int y, int prevx, int prevy);

	float GetValue();

	void SetValue(float v);

	void LoadXML(TiXmlElement* element);

	void SaveXML(TiXmlElement* element);

	virtual void Set(char* order);

};

#endif //_SNICE_SLIDER_H_


// End of file slider.h
