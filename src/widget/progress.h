// crafter interface library
// Funny Farm
// copyright © 2002 Wybren van Keulen
// www.funnyfarm.tv

// File modified by Tricoire Sebastien
// Date of creation : 2004 06 02
///
// File modified by Lionel Allorge
// Date of modification : 2004 06 02

// progress.h

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


#ifndef _SNICE_PROGRESS_H_
#define _SNICE_PROGRESS_H_

#include "widget/UI_widget.h"
#include "widget/label.h"

class W_progress : public UI_widget
{
private:

	W_label* text;
	string name;

	float value;
	float speed;

	bool action;


public:

	W_progress(int x, int y, int w, int h, string l, float r = 0.3f, float g = 0.3f, float b = 0.3f);

	virtual ~W_progress();

	void SetName(string l);

	void SetLabel(string l);

	void SetLabel();

	void SetWidth(int w);

	void SetPosY(int y);

	void Draw();

	float GetValue();

	void SetValue(float v);

	float GetAction();

	void SetAction(bool a);

    float GetSpeed();

    void SetSpeed(float s);

	void LoadXML(TiXmlElement* element);

	//void SaveXML(TiXmlElement* element);

};

#endif // _SNICE_PROGRESS_H_

// End of file progress.h
