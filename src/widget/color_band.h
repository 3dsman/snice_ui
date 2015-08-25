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

#ifndef _SNICE_COLORBAND_H_
#define _SNICE_COLORBAND_H_

#include "widget/UI_widget.h"
/*
class colorbandItem
{
public:
	float pos;
	float r,g,b,a;

	colorbandItem(float position, float red, float green, float blue, float alpha);
};*/


class W_colorBand: public UI_widget
{

private:


	struct 	colorbandItem
	{
		float pos;
		float r,g,b,a;
	};

	colorbandItem* NewColorbandItem(float position, float red, float green, float blue, float alpha);

	double LinearInterpolate1D(double a, double b, double x);
	double CosineInterpolate1D(double a, double b, double x);

	char interpolation;

	List listofcolorbandItems;

	colorbandItem* pActiveColorBandItem;
	bool draggingcolorbandItem;

	void SortList();

public:

	W_colorBand(int x, int y, int w, int h, string name);

	~W_colorBand();

	void RemoveActiveColorNode();

	void FlushColorNode();

	void AddColorNode(float Pos, float Red, float Green, float Blue, float Alpha);

	void SetActiveColor(float Red,float Green,float Blue,float Alpha);

	void GetActiveColor(float* Red,float* Green,float* Blue,float* Alpha);

	float GetActiveColor(int RGBA);

	void GetColorAt(float* Red,float* Green,float* Blue,float* Alpha, float pos);

	void SetInterpolation(char i);

	void GetInterpolation(char i);

	void SetHeight(int h);

	void SetWidth(int w);

	void SetPosX(int x);

	void SetPosY(int y);

	void Draw();

	/**	\brief left button down function.*/
	virtual UI_base* OnLButtonDown(int x, int y);
	/**	\brief left button up function.*/
	virtual UI_base* OnLButtonUp(int x, int y);
	/**	\brief mouse move function.*/
	virtual UI_base* OnMouseMove(int x, int y, int prevx, int prevy);
/*
	void LoadXML(TiXmlElement* element);

	void SaveXML(TiXmlElement* element);
*/
	virtual void Set(char* order);
};

#endif //_SNICE_COLORBAND_H_

// End of file coulourBand.h
