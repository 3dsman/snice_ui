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

#include "../snice_UI.h"
#include "widget/slided_panel.h"


W_slidedPanel::W_slidedPanel(int x, int y, int w, int h, int sx, int sy, float red, float green, float blue)
		    :UI_widget(x, y, w, h, red, green, blue)
{
	width = w;
	height = h;
	SetPanelSurface(sx,sy);
}

W_slidedPanel::~W_slidedPanel()
{
    if (pHorizontalSlider) delete pHorizontalSlider;
    if (pVerticalSlider) delete pVerticalSlider;
}

void W_slidedPanel::StatChangeSliders(UI_base * asker, W_slider* caller,float value, bool realtime)
{
		(dynamic_cast<W_slidedPanel*> (asker))->ChangeSliders(caller, value, realtime);
}
	
void W_slidedPanel::ChangeSliders( W_slider* caller,float value, bool realtime)
{
	if (caller == pHorizontalSlider)
		xOffset = value;
	if (caller == pVerticalSlider)
	{
		yOffset = (surfacey-windSizeY)-value;
		//std::cout<<surfacey-windSizeY<<" "<<value<<std::endl;
	}
}


void W_slidedPanel::Draw()
{
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
		glVertex2d(windSizeX-1, -1);					// Draw the backgound to color and stencil buffers.
		glVertex2d(windSizeX-1, -windSizeY+1);				// We Only Want To Mark It In The Stencil Buffer
		glVertex2d(1, -windSizeY+1);
	glEnd();

	glStencilFunc(GL_EQUAL, 1, 1);					// We draw only where the stencil is 1
													// (I.E. where the background was drawn)
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);			// Don't change the stencil buffer

	glPushMatrix();									// Push the matrix for the slider translation
	glTranslated(-xOffset, yOffset, 0);
							// Slider translation

//**********************************  draw the content of the window  ***********************

	if (childList.ToFirst())
			do
			{
				((UI_base*)childList.GetCurrentObjectPointer())->Draw();
			}while(childList.ToNext());
	//PanelDraw();

//*******************************************************************************************


	glPopMatrix();									// Get the matrix before translation

	glDisable(GL_STENCIL_TEST);						// We don't need the stencil buffer any more (Disable)


	// draw the border
	glColor4f(1.0f,1.0f,1.0f,0.7f);

	glEnable(GL_TEXTURE_2D);
	textures.slider.BindTex();
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
		glVertex2d(windSizeX-8, 0);
		glTexCoord2f(0.51f,0.75f);
		glVertex2d(windSizeX-8, -8);
		glTexCoord2f(0.49f,0.75f);
		glVertex2d(8, -8);

		glTexCoord2f(0.75f,1.0f);
		glVertex2d(windSizeX-8, 0);
		glTexCoord2f(1.00f,1.0f);
		glVertex2d(windSizeX, 0);
		glTexCoord2f(1.00f,0.75f);
		glVertex2d(windSizeX, -8);
		glTexCoord2f(0.75f,0.75f);
		glVertex2d(windSizeX-8, -8);

		glTexCoord2f(0.75f,0.75f);
		glVertex2d(windSizeX-8, -8);
		glTexCoord2f(1.00f,0.75f);
		glVertex2d(windSizeX, -8);
		glTexCoord2f(1.00f,0.25f);
		glVertex2d(windSizeX, -windSizeY+8);
		glTexCoord2f(0.75f,0.25f);
		glVertex2d(windSizeX-8, -windSizeY+8);

		glTexCoord2f(0.75f,0.25f);
		glVertex2d(windSizeX-8, -windSizeY+8);
		glTexCoord2f(1.00f,0.25f);
		glVertex2d(windSizeX, -windSizeY+8);
		glTexCoord2f(1.00f,0.00f);
		glVertex2d(windSizeX, -windSizeY);
		glTexCoord2f(0.75f,0.00f);
		glVertex2d(windSizeX-8, -windSizeY);

		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -windSizeY+8);
		glTexCoord2f(0.75f,0.25f);
		glVertex2d(windSizeX-8, -windSizeY+8);
		glTexCoord2f(0.75,0.00f);
		glVertex2d(windSizeX-8, -windSizeY);
		glTexCoord2f(0.25f,0.00f);
		glVertex2d(8, -windSizeY);

		glTexCoord2f(0.0f,0.25f);
		glVertex2d(0, -windSizeY+8);
		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -windSizeY+8);
		glTexCoord2f(0.25f,0.00f);
		glVertex2d(8, -windSizeY);
		glTexCoord2f(0.0f,0.00f);
		glVertex2d(0, -windSizeY);

		glTexCoord2f(0.00f,0.75f);
		glVertex2d(0, -8);
		glTexCoord2f(0.25f,0.75f);
		glVertex2d(8, -8);
		glTexCoord2f(0.25f,0.25f);
		glVertex2d(8, -windSizeY+8);
		glTexCoord2f(0.00f,0.25f);
		glVertex2d(0, -windSizeY+8);
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
	
	if (pHorizontalSlider) pHorizontalSlider->Draw();
	if (pVerticalSlider) pVerticalSlider->Draw();
	
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
	windSizeX = width;
	windSizeY = height;
	xOffset = 0;
	yOffset = 0;
	if (width<x) windSizeY = height - 20;
	if (height<y) windSizeX = width - 20;
	surfacex = max(x,windSizeX);
	surfacey = max(y,windSizeY);
		
	if (width<x)
	{
		if (!pHorizontalSlider)
		{
			pHorizontalSlider = new W_slider(0,-windSizeY,windSizeX,20,"", 0.0f, 0.0f, (float)surfacex, 0, (float)windSizeX);
			pHorizontalSlider->OnSetValue(this, W_slidedPanel::StatChangeSliders);
		}else
		{
			//pHorizontalSlider->SetTo((float)surfacex);
			//pHorizontalSlider->SetWidth(windSizeX);
			
			pHorizontalSlider->SetTo((float)surfacex);
			pHorizontalSlider->SetValue((float)surfacex,false);
			pHorizontalSlider->SetBarSize((float)windSizeX);
			pHorizontalSlider->SetWidth(windSizeX);
			pHorizontalSlider->SetPosY(-windSizeY);
		}
	}
	else
		if (pHorizontalSlider)
			{
				delete pHorizontalSlider;
				pHorizontalSlider = nullptr;
			};
		
	if (height<y)
	{
		if (!pVerticalSlider)
		{
			pVerticalSlider = new W_slider(windSizeX,0,20,windSizeY,"", (float)surfacey-(float)windSizeY,  0, (float)surfacey, 0, (float)windSizeY);
	
			pVerticalSlider->OnSetValue(this, W_slidedPanel::StatChangeSliders);
		}else
		{
			pVerticalSlider->SetTo((float)surfacey);
			pVerticalSlider->SetValue((float)surfacey-(float)windSizeY,false);
			pVerticalSlider->SetBarSize((float)windSizeY);
			pVerticalSlider->SetHeight(windSizeY);
			pVerticalSlider->SetPosX(windSizeX);
		}
	}
	else
		if (pVerticalSlider)
			{
				delete pVerticalSlider;
				pVerticalSlider = nullptr;
			}
}

bool W_slidedPanel::HitPanel(int x, int y)
{
	if (x<posx || x>posx+windSizeX || y>posy || y<posy-windSizeY)
		return 0;
	else
		return 1;
}

UI_base* W_slidedPanel::OnLButtonDown(int x, int y)
{
    if (pInterceptChild)
    {
        if ((pInterceptChild==pVerticalSlider)||(pInterceptChild==pHorizontalSlider))
        {
            pInterceptChild = (pInterceptChild)->OnLButtonDown(x - posx , y - posy);
            Autokill(pInterceptChild);
        }else
        if (pInterceptChild!=this)
        {
            pInterceptChild = (pInterceptChild)->OnLButtonDown(x - posx + xOffset, y - posy + yOffset);
            Autokill(pInterceptChild);
        }
        if (pInterceptChild)
            return this;
        else
            return 0;
    };

	if (HitPanel(x,y))
	{
        if (childList.ToFirst())
            do
            {
                childList.Push();
                pInterceptChild = ((UI_base*)childList.GetCurrentObjectPointer())->OnLButtonDown(x - posx + xOffset, y - posy + yOffset);
                childList.Pop();
                Autokill((UI_base*)childList.GetCurrentObjectPointer());
                if (pInterceptChild) {return this;};
            }while(childList.ToNext());
    }else{
		if (pHorizontalSlider)
		{
			pInterceptChild = pHorizontalSlider->OnLButtonDown(x-posx,y-posy);
			if (pInterceptChild) {return this;};
		}
		
		if (pVerticalSlider)
		{
			pInterceptChild = pVerticalSlider->OnLButtonDown(x-posx,y-posy);
			if (pInterceptChild) {return this;};
		}
	}

	return 0;
}

UI_base* W_slidedPanel::OnLButtonUp(int x, int y)
{
    if (pInterceptChild)
    {
        if ((pInterceptChild==pVerticalSlider)||(pInterceptChild==pHorizontalSlider))
        {
            pInterceptChild = (pInterceptChild)->OnLButtonUp(x - posx , y - posy);
            Autokill(pInterceptChild);
        }else
        if (pInterceptChild!=this)
        {
            pInterceptChild = (pInterceptChild)->OnLButtonUp(x - posx + xOffset, y - posy + yOffset);
            Autokill(pInterceptChild);
        }
        if (pInterceptChild)
            return this;
        else
            return 0;
    };

	if (HitPanel(x,y))
	{
        if (childList.ToFirst())
            do
            {
                childList.Push();
                pInterceptChild = ((UI_base*)childList.GetCurrentObjectPointer())->OnLButtonUp(x - posx + xOffset, y - posy + yOffset);
                childList.Pop();
                Autokill((UI_base*)childList.GetCurrentObjectPointer());
                if (pInterceptChild) {return this;};
            }while(childList.ToNext());
    }else{
		if (pHorizontalSlider)
		{
			pInterceptChild = pHorizontalSlider->OnLButtonUp(x-posx,y-posy);
			if (pInterceptChild) {return this;};
		}
		if (pVerticalSlider)
		{
			pInterceptChild = pVerticalSlider->OnLButtonUp(x-posx,y-posy);
			if (pInterceptChild) {return this;};
		}
	}

	return 0;
	//if (HitPanel(x,y))
	//	PanelOnLButtonUp( x - posx + (int)(pHorizontalSlider->GetValue()), y - posy);
	//pHorizontalSlider->OnLButtonUp(x-posx,y-posy);
	//pVerticalSlider->OnLButtonUp(x-posx,y-posy);
}

UI_base* W_slidedPanel::OnMouseMove(int x, int y, int prevx, int prevy)
{
    //int xOffset = (int)(pHorizontalSlider->GetValue());
    //int yOffset = (int)(pVerticalSlider->GetValue());
    if (pInterceptChild)
    {
        if ((pInterceptChild==pVerticalSlider)||(pInterceptChild==pHorizontalSlider))
        {
            pInterceptChild = (pInterceptChild)->OnMouseMove(x-posx,y-posy, prevx-posx, prevy-posy);
            Autokill(pInterceptChild);
        }else
            if (pInterceptChild!=this)
            {
                pInterceptChild = (pInterceptChild)->OnMouseMove( x - posx + xOffset, y - posy + yOffset, prevx - posx + xOffset, prevy - posy + yOffset);
                Autokill(pInterceptChild);
            }
        if (pInterceptChild)
            return this;
        else
            return 0;
    };

	if (HitPanel(x,y))
	{
        if (childList.ToFirst())
            do
            {
                childList.Push();
                pInterceptChild = ((UI_base*)childList.GetCurrentObjectPointer())->OnMouseMove( x - posx + xOffset, y - posy + yOffset, prevx - posx + xOffset, prevy - posy + yOffset);
                childList.Pop();
                Autokill((UI_base*)childList.GetCurrentObjectPointer());
                if (pInterceptChild) {return this;};
            }while(childList.ToNext());
    }else{
		if (pHorizontalSlider)
		{
			pInterceptChild = pHorizontalSlider->OnMouseMove(x-posx,y-posy, prevx-posx, prevy-posy);
			if (pInterceptChild) {return this;};
		}
		if (pVerticalSlider)
		{
			pInterceptChild = pVerticalSlider->OnMouseMove(x-posx,y-posy, prevx-posx, prevy-posy);
			if (pInterceptChild) {return this;};
		}
	}

	return 0;
	//if (HitPanel(x,y))
	//	PanelOnMouseMove( x - posx + (int)(pHorizontalSlider->GetValue()), y - posy, prevx - posx + (int)(pHorizontalSlider->GetValue()), prevy - posy);
	//pHorizontalSlider->OnMouseMove(x-posx,y-posy, prevx-posx, prevy-posy);
	//pVerticalSlider->OnMouseMove(x-posx,y-posy, prevx-posx, prevy-posy);
}
/*
UI_base* W_slidedPanel::OnKeyPressed(int key)
            UI_base::OnKeyPressed(int key)
{
	//	PanelOnKeyPressed(key);
}*/
/*
void W_slidedPanel::panelOnLButtonDown(int x, int y, int px, int py){};
void W_slidedPanel::panelOnLButtonUp(int x, int y){};
void W_slidedPanel::panelOnMouseMove(int x, int y, int prevx, int prevy){};
void W_slidedPanel::panelOnKeyPressed(int key){};

void W_slidedPanel::panelDraw(){};
*/
/*
void W_slidedPanel::LoadXML(TiXmlElement* element)
{
	double red, green, blue;
	element->Attribute("Red",&red);
	element->Attribute("Green",&green);
	element->Attribute("Blue",&blue);
	SetColor((float)red, (float)green, (float)blue);

}*/
