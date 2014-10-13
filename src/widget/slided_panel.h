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


#ifndef _SNICE_slidedPanel_H_
#define _SNICE_slidedPanel_H_

#include "widget/UI_widget.h"
#include "widget/slider.h"

class W_slidedPanel : public UI_widget
{
protected:

	int surfacex;
	int surfacey;


	W_slider * pHorizontalSlider;
	W_slider * pVerticalSlider;

	//virtual void PanelOnLButtonDown(int x, int y, int px, int py)=0;
	//virtual void PanelOnLButtonUp(int x, int y)=0;
	//virtual void PanelOnMouseMove(int x, int y, int prevx, int prevy)=0;
	//virtual void PanelOnKeyPressed(int key)=0;
	//virtual void PanelDraw()=0;

public:

	W_slidedPanel(int x, int y, int w, int h,int sx = 10, int sy = 10, float r = 0.8f, float g = 0.8f, float b = 0.8f);

	virtual ~W_slidedPanel();

	void Draw();
	void SetColor(float red, float green, float blue);

	void GetColor(float * red, float * green, float * blue);

	void SetPanelSurface(int x, int y);

	bool HitPanel(int x, int y);

	/**	\brief left button down function.*/
	virtual UI_base* OnLButtonDown(int x, int y);
	/**	\brief left button up function.*/
	virtual UI_base* OnLButtonUp(int x, int y);
	/**	\brief mouse move function.*/
	virtual UI_base* OnMouseMove(int x, int y, int prevx, int prevy);
	/**	\brief char pressed function.*/
	//virtual UI_base* OnKeyPressed(int key);

	void LoadXML(TiXmlElement* element);

	//void SaveXML(TiXmlElement* element);

};

#endif // _SNICE_slidedPanel_H_
