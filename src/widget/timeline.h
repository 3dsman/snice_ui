// crafter interface library
// copyright © 2004 Tricoire Sebastien

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

#ifndef _SNICE_TIMELINE_H_
#define _SNICE_TIMELINE_H_

#include "widget/UI_widget.h"

class W_textbox;
class W_slider;

class W_timeline : public UI_widget
{
private:

	W_textbox* pStartFrame;
	W_textbox* pEndFrame;

	W_slider* pSliderTimeline;

	bool action;

public:

	W_timeline(int x, int y, int w, int h, char *l, float v, float f, float t, int p, float r = 0.3f, float g = 0.3f, float b = 0.3f);

	~W_timeline();

	void SetName(char *l);

	void SetLabel(char *l);

	void SetLabel();

	void SetWidth(int w);

	void SetFrom(float f);

	void SetTo(float t);

	float GetFrom();

	float GetTo();

	void SetPrecision(int p);

	float GetValue();

	void SetValue(float v);

	void Draw();
/*
	void onLButtonDown(int x, int y);

	void onLButtonUp(int x, int y);

	void onMouseMove(int x, int y, int prevx, int prevy);
*/
	void Callback(UI_base * pCallObject, unsigned char callIndex );

	void LoadXML(TiXmlElement* element);

	void SaveXML(TiXmlElement* element);

	virtual void Set(char* order);
};

#endif // _SNICE_TIMELINE_H_

// End of file timeline.h
