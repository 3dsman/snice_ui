// crafter interface library
// Funny Farm
// copyright © 2002 Wybren van Keulen
// www.funnyfarm.tv

// thanks to nehe stencil buffer tutorial http://nehe.gamedev.net/

// File modified by Tricoire Sebastien
// Date of creation : 2004 10 14
///
// File modified by
// Date of modification :

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
#include "widget/slided_panel.h"


W_slidedPanel::W_slidedPanel(int x, int y, int w, int h,int sx, int sy, float red, float green, float blue)
		    :UI_widget(x, y, w, h, red, green, blue)
{
	surfacex = sx;
	surfacey = sy;

	pHorizontalSlider = new W_slider(0,-height+20,width,20,"", 0.0f, 0.0f, (float)surfacex, 0, (float)width,0.5,0.5,0.5);
	AddChild(pHorizontalSlider);
}

W_slidedPanel::~W_slidedPanel(){}

void W_slidedPanel::Draw()
{
	float winHeight;
	winHeight=height-20.0f;
	glTranslated(posx, posy, 0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	// Fill
	// glColor4f(1.0f, 1.0f, 1.0f,0.6f);
	// glColor4f(0.64f, 0.59f, 0.53f,1.0f);
	glColor4f(r, g, b, 1.0f);			//background color

	/*glBegin(GL_POLYGON);
		glVertex2d(6, -1);
		glVertex2d(width-6, -1);
		glVertex2d(width-2, -2);
		glVertex2d(width-1, -4);
		glVertex2d(width-1, -6);
		glVertex2d(width-1, -winHeight+6);
		glVertex2d(width-2, -winHeight+2);
		glVertex2d(width-4, -winHeight+1);
		glVertex2d(width-6, -winHeight+1);
		glVertex2d(6, -winHeight+1);
		glVertex2d(2, -winHeight+2);
		glVertex2d(1, -winHeight+4);
		glVertex2d(1, -winHeight+5);
		glVertex2d(1, -7);
		glVertex2d(2, -2);
		glVertex2d(4, -1);
		glVertex2d(6, 0);
	glEnd();*/



	glClear(GL_STENCIL_BUFFER_BIT);					// clear the stencil buffer
	glEnable(GL_STENCIL_TEST);						// Enable stencil buffer for "marking" the content of the list selector
	glStencilFunc(GL_ALWAYS, 1, 1);					// Always passes, 1 bit plane, 1 as mask
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);		// We set the stencil buffer to 1 where we draw any polygon
													// Keep if test fails, keep if test passes but buffer test fails replace if test passes
	glBegin(GL_QUADS);
		glVertex2d(1,-1);
		glVertex2d(width-1, -1);					// Draw the backgound to color and stencil buffers.
		glVertex2d(width-1, -winHeight+1);				// We Only Want To Mark It In The Stencil Buffer
		glVertex2d(1, -winHeight+1);					
	glEnd();							

	glStencilFunc(GL_EQUAL, 1, 1);					// We draw only where the stencil is 1
													// (I.E. where the background was drawn)
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);			// Don't change the stencil buffer

	glPushMatrix();									// Push the matrix for the slider translation
	glTranslated(-pHorizontalSlider->GetValue(), 0, 0);							// Slider translation

//**********************************  draw the content of the window  ***********************

	PanelDraw();

//*******************************************************************************************


	glPopMatrix();									// Get the matrix before translation

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
		glVertex2d(width, -winHeight+8);
		glTexCoord2f(0.75f,0.25f);
		glVertex2d(width-8, -winHeight+8);

		glTexCoord2f(0.75f,0.25f);
		glVertex2d(width-8, -winHeight+8);
		glTexCoord2f(1.00f,0.25f);
		glVertex2d(width, -winHeight+8);
		glTexCoord2f(1.00f,0.00f);
		glVertex2d(width, -winHeight);
		glTexCoord2f(0.75f,0.00f);
		glVertex2d(width-8, -winHeight);

		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -winHeight+8);
		glTexCoord2f(0.75f,0.25f);
		glVertex2d(width-8, -winHeight+8);
		glTexCoord2f(0.75,0.00f);
		glVertex2d(width-8, -winHeight);
		glTexCoord2f(0.25f,0.00f);
		glVertex2d(8, -winHeight);

		glTexCoord2f(0.0f,0.25f);
		glVertex2d(0, -winHeight+8);
		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -winHeight+8);
		glTexCoord2f(0.25f,0.00f);
		glVertex2d(8, -winHeight);
		glTexCoord2f(0.0f,0.00f);
		glVertex2d(0, -winHeight);

		glTexCoord2f(0.00f,0.75f);
		glVertex2d(0, -8);
		glTexCoord2f(0.25f,0.75f);
		glVertex2d(8, -8);
		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -winHeight+8);
		glTexCoord2f(0.00f,0.25f);
		glVertex2d(0, -winHeight+8);
	glEnd();

	/*glBindTexture(GL_TEXTURE_2D, textures[10].texID);
	glColor4f(1.0f,1.0f,1.0f,0.6f);	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,1.0f);
		glVertex2d(0, 0);
		glTexCoord2f(1.0f,1.0f);
		glVertex2d(width, 0);
		glTexCoord2f(1.0f,0.0f);
		glVertex2d(width,-winHeight);
		glTexCoord2f(0.0f,0.0f);
		glVertex2d(0, -winHeight);
	glEnd();*/

	glDisable(GL_TEXTURE_2D);
	
	pHorizontalSlider->Draw();
	glTranslated(-posx,-posy,0);
	
}
void W_slidedPanel::SetColor(float red, float green, float blue)
{
	r = red; g = green; b = blue;
}

void W_slidedPanel::GetColor(float * red, float * green, float * blue)
{
	*red = r; *green = g; *blue = b;
}

void W_slidedPanel::SetPanelSurface(int x, int y)
{
	//change the total surface of the panel so set the slider
	surfacex = max(x,width);
	surfacey = max(y,height-20);
	pHorizontalSlider->SetTo((float)surfacex);
	pHorizontalSlider->SetValue(0);
}

bool W_slidedPanel::HitPanel(int x, int y)
{
	if (x<posx || x>posx+width || y>posy || y<posy-height+20)
		return 0;
	else
		return 1;
}

void W_slidedPanel::OnLButtonDown(int x, int y)
{
	if (HitPanel(x,y))
		PanelOnLButtonDown( x - posx + (int)(pHorizontalSlider->GetValue()), y - posy, 0, 0);
	//pHorizontalSlider->onLButtonDown(x-posx,y-posy, posx+scrollx, posy+scrolly);

	pHorizontalSlider->OnLButtonDown(x-posx,y-posy);
}

void W_slidedPanel::OnLButtonUp(int x, int y)
{
	if (HitPanel(x,y))
		PanelOnLButtonUp( x - posx + (int)(pHorizontalSlider->GetValue()), y - posy);
	pHorizontalSlider->OnLButtonUp(x-posx,y-posy);
}

void W_slidedPanel::OnMouseMove(int x, int y, int prevx, int prevy)
{
	if (HitPanel(x,y))
		PanelOnMouseMove( x - posx + (int)(pHorizontalSlider->GetValue()), y - posy, prevx - posx + (int)(pHorizontalSlider->GetValue()), prevy - posy);
	pHorizontalSlider->OnMouseMove(x-posx,y-posy, prevx-posx, prevy-posy);
}

void W_slidedPanel::OnKeyPressed(int key)
{
		PanelOnKeyPressed(key);
}
/*
void W_slidedPanel::panelOnLButtonDown(int x, int y, int px, int py){};
void W_slidedPanel::panelOnLButtonUp(int x, int y){};
void W_slidedPanel::panelOnMouseMove(int x, int y, int prevx, int prevy){};
void W_slidedPanel::panelOnKeyPressed(int key){};

void W_slidedPanel::panelDraw(){};
*/
void W_slidedPanel::LoadXML(TiXmlElement* element)
{
	double red, green, blue;
	element->Attribute("Red",&red);
	element->Attribute("Green",&green);
	element->Attribute("Blue",&blue);
	SetColor((float)red, (float)green, (float)blue);

}
