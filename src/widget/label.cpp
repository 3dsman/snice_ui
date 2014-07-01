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

#include <stdarg.h>

//#include "include/glfw.h"
#include "../snice_UI.h"
//#include "../test_UI.h"
//#include "snice.h"
#include "widget/label.h"

////////////////////////////////////////
// label(int x, int y, bool bw, const char *fmt, ...).
////////////////////////////////////////
W_label::W_label(int x, int y, int w, bool bw, string fmt, ...)
		:UI_widget(x, y, w, 0, 0, 0, 0)
{
	/*posx = x;
	posy = y;
	width = w;*/

	black = bw;

	va_list	ap;											// Pointer To List Of Arguments

	if (fmt.size() == 0)								// If There's No Text
		return;											// Do Nothing

	//strcpy(refName,fmt);
	refName = fmt;
	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt.c_str(), ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text
}

void W_label::Draw()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, font.texture.texID);

	glPushMatrix();

	glTranslated(posx,posy,0);


	int temp = 0;

	if (!black)
	{
		temp = 1;
		glColor4f(r,g,b,0.6f);
	}

    glListBase(font.fontList-32+(128*temp));


	glScalef(1.0f,-1.0f,1.0f);


	char texttemp[256];
	strcpy(texttemp,text);

	if ((width > 0) && ((width/font.charWidth) < (int)strlen(texttemp)) && ((width/font.charWidth) >= 2))
	{
		strcpy(&(texttemp[width/font.charWidth-2]),"..");
	}

	glCallLists(strlen(texttemp),GL_UNSIGNED_BYTE, texttemp);


	//glScalef(1.0f,-1.0f,1.0f);
	//glTranslated(-(posx+7*(int)strlen(text)), -posy,0);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

#ifdef _DEBUG
	{
		//if (strcmp(text,"TEST")) printf("TEST\n");
	}
#endif

}

/*void label::SetPos(int x, int y)
{
	posx = x;	// Store x value
	posy = y;	// Store y value
}*/

void W_label::SetColor(float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;
};

void W_label::SetWidth(int w)
{
	width = w;	// Store w value
}

void W_label::SetText(string t,...)
{
	if (t.size() == 0)				// If There's No Text
		return;										// Do Nothing

	va_list	ap;										// Pointer To List Of Arguments

	va_start(ap, t);								// Parses The String For Variables
		vsprintf(text, t.c_str(), ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);										// Results Are Stored In Text
}

int W_label::GetLength()
{
	return (font.charWidth * strlen(text));
}
