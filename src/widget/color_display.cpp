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

#include "snice.h"

#include "viewports_array.h"
#include "dialog/color_picker.h"

#include "widget/color_display.h"

W_colorDisplay::W_colorDisplay(int x, int y, int w, int h, char* name, float r, float g, float b)
			 :UI_widget(x, y, w, h, r, g, b)
{
	posx = x;
	posy = y;
	width = w;
	height = h;

	strcpy(refName, name);

	r = r;
	g = g;
	b = b;
}

W_colorDisplay::~W_colorDisplay()
{
}

void W_colorDisplay::Draw()
{
	glTranslated(posx, posy, 0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	// Fill
	// glColor4f(1.0f, 1.0f, 1.0f,0.6f);
	// glColor4f(0.64f, 0.59f, 0.53f,1.0f);
	glColor4f(r, g, b, 1.0f);
	/*glBegin(GL_POLYGON);
		glVertex2d(6, -1);
		glVertex2d(width-6, -1);
		glVertex2d(width-2, -2);
		glVertex2d(width-1, -4);
		glVertex2d(width-1, -6);
		glVertex2d(width-1, -height+6);
		glVertex2d(width-2, -height+2);
		glVertex2d(width-4, -height+1);
		glVertex2d(width-6, -height+1);
		glVertex2d(6, -height+1);
		glVertex2d(2, -height+2);
		glVertex2d(1, -height+4);
		glVertex2d(1, -height+5);
		glVertex2d(1, -7);
		glVertex2d(2, -2);
		glVertex2d(4, -1);
		glVertex2d(6, 0);
	glEnd();*/

	/*glBegin(GL_QUADS);
		glVertex2d(1,-1);
		glVertex2d(width-1, -1);
		glVertex2d(width-1, -height+1);
		glVertex2d(1, -height+1);
	glEnd();*/


		glClear(GL_STENCIL_BUFFER_BIT);					// clear the stencil buffer
		glEnable(GL_STENCIL_TEST);						// Enable stencil buffer for "marking" the content of the list selector
		glStencilFunc(GL_ALWAYS, 1, 1);					// Always passes, 1 bit plane, 1 as mask
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);		// We set the stencil buffer to 1 where we draw any polygon
														// Keep if test fails, keep if test passes but buffer test fails replace if test passes
		glBegin(GL_QUADS);
			glVertex2d(1,-1);
			glVertex2d(width-1, -1);					// Draw the backgound to color and stencil buffers.
			glVertex2d(width-1, -height+1);				// We Only Want To Mark It In The Stencil Buffer
			glVertex2d(1, -height+1);					
		glEnd();							

		glStencilFunc(GL_EQUAL, 1, 1);					// We draw only where the stencil is 1
														// (I.E. where the background was drawn)
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);			// Don't change the stencil buffer

		glPushMatrix();									// Push the matrix 

		OnDraw();								// draw the content of the window

		glPopMatrix();									// Get the matrix

		glDisable(GL_STENCIL_TEST);						// We don't need the stencil buffer any more (Disable)

	
	// draw the border
	glColor4f(1.0f,1.0f,1.0f,0.7f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[8].texID);				// Select Our Font Texture
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,1.0f);
		glVertex2d(0, 0);
		glTexCoord2f(0.25f,1.0f);
		glVertex2d(8, 0);
		glTexCoord2f(0.25,0.75f);
		glVertex2d(8, -8);
		glTexCoord2f(0.0f,0.75f);
		glVertex2d(0, -8);
		
		glTexCoord2f(0.49f,1.0f);
		glVertex2d(8, 0);
		glTexCoord2f(0.51f,1.0f);
		glVertex2d(width-8, 0);
		glTexCoord2f(0.51f,0.75f);
		glVertex2d(width-8, -8);
		glTexCoord2f(0.49f,0.75f);
		glVertex2d(8, -8);

		glTexCoord2f(0.75f,1.0f);
		glVertex2d(width-8, 0);
		glTexCoord2f(1.00f,1.0f);
		glVertex2d(width, 0);
		glTexCoord2f(1.00f,0.75f);
		glVertex2d(width, -8);
		glTexCoord2f(0.75f,0.75f);
		glVertex2d(width-8, -8);

		glTexCoord2f(0.75f,0.75f);
		glVertex2d(width-8, -8);
		glTexCoord2f(1.00f,0.75f);
		glVertex2d(width, -8);
		glTexCoord2f(1.00f,0.25f);
		glVertex2d(width, -height+8);
		glTexCoord2f(0.75f,0.25f);
		glVertex2d(width-8, -height+8);

		glTexCoord2f(0.75f,0.25f);
		glVertex2d(width-8, -height+8);
		glTexCoord2f(1.00f,0.25f);
		glVertex2d(width, -height+8);
		glTexCoord2f(1.00f,0.00f);
		glVertex2d(width, -height);
		glTexCoord2f(0.75f,0.00f);
		glVertex2d(width-8, -height);

		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -height+8);
		glTexCoord2f(0.75f,0.25f);
		glVertex2d(width-8, -height+8);
		glTexCoord2f(0.75,0.00f);
		glVertex2d(width-8, -height);
		glTexCoord2f(0.25f,0.00f);
		glVertex2d(8, -height);

		glTexCoord2f(0.0f,0.25f);
		glVertex2d(0, -height+8);
		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -height+8);
		glTexCoord2f(0.25f,0.00f);
		glVertex2d(8, -height);
		glTexCoord2f(0.0f,0.00f);
		glVertex2d(0, -height);

		glTexCoord2f(0.00f,0.75f);
		glVertex2d(0, -8);
		glTexCoord2f(0.25f,0.75f);
		glVertex2d(8, -8);
		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -height+8);
		glTexCoord2f(0.00f,0.25f);
		glVertex2d(0, -height+8);
	glEnd();

	/*glBindTexture(GL_TEXTURE_2D, textures[10].texID);
	glColor4f(1.0f,1.0f,1.0f,0.6f);	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,1.0f);
		glVertex2d(0, 0);
		glTexCoord2f(1.0f,1.0f);
		glVertex2d(width, 0);
		glTexCoord2f(1.0f,0.0f);
		glVertex2d(width,-height);
		glTexCoord2f(0.0f,0.0f);
		glVertex2d(0, -height);
	glEnd();*/

	glDisable(GL_TEXTURE_2D);
	
	glTranslated(-posx,-posy,0);
}
void W_colorDisplay::SetColor(float red, float green, float blue)
{
	r = red; g = green; b = blue;
}

void W_colorDisplay::GetColor(float * red, float * green, float * blue)
{
	*red = r; *green = g; *blue = b;
}

float W_colorDisplay::GetColor(int RGB)
{
		switch (RGB)
		{
		case RED:
			return r;
		case GREEN:
			return g;
		case BLUE:
			return b;
		default:
			return 0;
		}
}

void W_colorDisplay::OnLButtonUp(int x, int y)
{
	if (Hittest(x,y))
		if (pParentUI_base) pParentUI_base->Callback(this,1);	
}


void W_colorDisplay::Callback(UI_base * pCallObject, unsigned char callIndex ){};




void W_colorDisplay::OnDraw(){};

void W_colorDisplay::SaveXML(TiXmlElement* element)
{
	
	char buf[256];
	float red, green, blue;
	GetColor(&red, &green, &blue);

	//creation of the ColorBand xml flag
	TiXmlElement NodeColorDisplay( refName );

	sprintf( buf, "%f", red );
	NodeColorDisplay.SetAttribute( "Red", buf );
	sprintf( buf, "%f", green );
	NodeColorDisplay.SetAttribute( "Green", buf );
	sprintf( buf, "%f", blue );
	NodeColorDisplay.SetAttribute( "Blue", buf );

	element->InsertEndChild( NodeColorDisplay );
}

void W_colorDisplay::LoadXML(TiXmlElement* element)
{
	double red, green, blue;
	element->Attribute("Red",&red);
	element->Attribute("Green",&green);
	element->Attribute("Blue",&blue);
	SetColor((float)red, (float)green, (float)blue);

}


void W_colorDisplay::Set(char* order)
{
 	printf("->%s", refName);
 	char value[256];
	int i=0;
 	for (i=0; i<256; ++i)
	    value[i]=0;
    float r=g=b=0;
    char* separator = strchr(order,',');
	 if (separator)
	 {
		 strncpy( value, order,separator - order);
		 value[separator-order] = 0;
		 r = atof(value);
		 order = separator+1;
     };
     separator = strchr(separator+1,',');
	 if (separator)
	 {
		 strncpy( value, order,separator - order);
		 g = atof(value);
		 b = atof(separator+1);
     }
     
   	 SetColor(r/255.0f,g/255.0f,b/255.0f);
//   	 if (pParentUI_base) pParentUI_base->Callback(this,1);
};
