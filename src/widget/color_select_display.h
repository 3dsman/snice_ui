// crafter interface library
// Funny Farm
// copyright © 2002 Wybren van Keulen
// www.funnyfarm.tv

// colorSelectDisplay.h

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

#ifndef _SNICE_COLORSELECTDISPLAY_H_
#define _SNICE_COLORSELECTDISPLAY_H_

#include "widget/UI_widget.h"

#include "image.h"
//#include "tgafile.h"

enum colorSelector {H, S, V, R, G, B};

class W_colorSelectdisplay : public UI_widget
{

private:

	bool xy;
	float redHue, greenSat, blueVal;
	void RefreshImageXY();
	void RefreshImageZ();
    void SetCursorXY(float curx, float cury);
    void SetCursorZ(float curz);

	void (*onChange)(W_colorSelectdisplay* caller,float red,float green, float blue) = NULL;

public:
	float curx;
	float cury;
	float curz;
	bool action;
	colorSelector mode;

	UI_image quadImage;
	UI_image lineImage;


	W_colorSelectdisplay(int x, int y, int w, int h, colorSelector mode, float red = 0.8f, float green = 0.8f, float blue = 0.8f, int pImageWidth = 256, int pImageHeight = 256);

	~W_colorSelectdisplay();


	void Draw();

	void UpdateColor(int x, int y);

	void GetColor(float* red, float* green, float* blue);

    /**	\brief function to set the onChange callback function.*/
	void OnChange(void (*function)(W_colorSelectdisplay* caller,float red,float green, float blue));

	/**	\brief left button down function.*/
	virtual UI_base* OnLButtonDown(int x, int y);
	/**	\brief left button up function.*/
	virtual UI_base* OnLButtonUp(int x, int y);
	/**	\brief mouse move function.*/
	virtual UI_base* OnMouseMove(int x, int y, int prevx, int prevy);

	void LoadXML(TiXmlElement* element);

	//void SaveXML(TiXmlElement* element);
};

#endif //_SNICE_COLORSELECTDISPLAY_H_

// End of file colorSelectDisplay.h
