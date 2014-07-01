// label class
// Funny Farm
// copyright © 2002 Wybren van Keulen
// www.funnyfarm.tv

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

#ifndef _SNICE_LABEL_H_
#define _SNICE_LABEL_H_

#include "widget/UI_widget.h"

class W_label : public UI_widget
{
private:
	char text[256];
	bool black;

public:
	W_label(int x, int y, int w, bool bw, string fmt, ...);
	virtual ~W_label(){}
	void SetText(string t,...);
	void SetColor(float red, float green, float blue);
	void SetWidth(int w);
	int GetLength();

	char* GetText(){return text;}
	void Draw();

};

#endif //_SNICE_LABEL_H_

// End of file label.h
