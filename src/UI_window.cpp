// UI_window.cpp: base for every windows (nodes, dialogboxes, ...).
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// SNICE : Simple Nodal Image Compositing Environment
// SNICE is a image and video compositing software
// Copyright by Sebastien Tricoire (3dsman@free.fr) and Lionel Allorge (lionel.allorge@lunerouge.org)
///
// based on Crafter (Leaf) Library by Wybren van Keulen (www.funnyfarm.tv)
// based on GLFW Library (www.glfw.org)
//
// UI_window.cpp
// This file is the UI_window class file
// File created by Tricoire Sebastien
// Date of creation : 2005 20 03
///
// File modified by
// Date of modification :
///
// Copyright (C) 2004 Sebastien Tricoire and Lionel Allorge.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 2 as published by the Free Software Foundation;
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//////////////////////////////////////////////////


////////////////////////////////////////
// class UI_window.
// Class for window definition
////////////////////////////////////////


/////////////////////////////////////////////
// Includes
/////////////////////////////////////////////
#include "include/glfw.h"
//#include "viewports_array.h"

#include "widget/label.h"
//#include "nodes/container.h"

//#include "prefs.h"

#include "UI_window.h"
//////////////////////////////////////////////////
// List of functions for io
//////////////////////////////////////////////////
class OnKeyPressed;
unsigned char UI_window::foldSteps = 5;


UI_window::UI_window(int x, int y, int w, int h, string winName, bool closeable, bool foldable, bool dragable, bool folded)
		  :UI_base(x, y, w, h)
{
	dragging = false;
	this->dragable = dragable;
	openclosing = 0;
	this->closeable = closeable;
	this->folded = folded;
	this->foldable = foldable;
	int labelpos = 17;
	if (!foldable) labelpos = 5;
	//onFold = NULL;
	//onUnfold = NULL;
	//if (strlen(winName)<255)
	//{
		refName = winName;//strcpy(refName,winName);
		//MakeUniqueName(refName);
		pTitlelabel = new W_label(labelpos, -4, 0, 0, refName);
	/*}
	else
		pTitlelabel = new W_label(labelpos, -4, 0, 0, "Name Error");
*/
	outlineWidth = 1;
	outlineStripple = false;
	outlineR = 0.0f;
	outlineG = 0.0f;
	outlineB = 0.0f;
}

UI_window::~UI_window(){
	if(pTitlelabel) delete pTitlelabel;
}

bool UI_window::Hittest(int x, int y)
{
	if (folded)
	{
		// if the mouse is in the window header
		if ((x >= posx - 6) &&
		   (x <= posx + width + 6) &&
		   (y >= posy - 26) &&
		   (y <= posy)) return true;
	}
	else
	{
		if ((x >= posx - 6) &&
		   (x <= posx + width + 6) &&
		   (y >= posy - height) &&
		   (y <= posy)) return true;
	}
	return false;
}

int UI_window::GetLeft()
{
	return posx;
}

int UI_window::GetRight()
{
	return posx+width;
}

int UI_window::GetBottom()
{
	if (folded) return posy-24; else return posy-height;
}

int UI_window::GetTop()
{
	return posy;
}

char* UI_window::GetName()
{
	return pTitlelabel->GetText();
}

void UI_window::SetName(char* winName)
{
	pTitlelabel->SetText(winName);
}

/**	\brief function to set the onClose callback function.*/
void UI_window::OnClose(void (*function)(UI_window* caller))
{
    onClose = function;
}
/**	\brief function to set the OnFold callback function.*/
void UI_window::OnFold(void (*function)(UI_window* caller))
{
    onFold = function;
}
/**	\brief function to set the OnUnfold callback function.*/
void UI_window::OnUnfold(void (*function)(UI_window* caller))
{
    onUnfold = function;
}

void UI_window::Draw()
{
	if (!visible) return;

	// move to local system
	glTranslated(posx,posy,0);

	glEnable(GL_POLYGON_SMOOTH);

	int tmpheight = height;

	if (folded)
		tmpheight = 26;
	//////////////////////////////////////

    if (openclosing)
    {
        openclosing--;
        if (folded)
        {
            tmpheight = 26+((height-26)/foldSteps)*(foldSteps-openclosing);
            if (!openclosing)
            {
                tmpheight = height;
        		folded = false;
        		if(onUnfold) onUnfold(this);
            }
        }else
        {
            tmpheight = 26+((height-26)/foldSteps)*openclosing;
            if (!openclosing)
            {
                tmpheight = 26;
        		folded = true;
        		if(onFold) onFold(this);
            }
        }


    }
	///////////////////////////////////


	// shadow
	//if (pPrefs->GetCute())
	//{
		glColor4f(r,g,b,0.2f);

		glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, textures.shadow.GetTexID());
		textures.shadow.BindTex();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		int shadowsize = 6;

		glBegin(GL_QUADS);
			glTexCoord2f(0.66f,0.0f);
			glVertex2d(width-0.5,-10);
			glTexCoord2f(1.0f,0.0f);
			glVertex2d(width+shadowsize-0.5,-10);
			glTexCoord2f(1.0f,0.33f);
			/*
			glVertex2d(width+shadowsize-0.5,-25.5);
			glTexCoord2f(0.66f, 0.33f);
			glVertex2d(width-0.5,-25.5);
	*/

			glVertex2d(width+shadowsize-0.5,-shadowsize-10);
			glTexCoord2f(0.66f, 0.33f);
			glVertex2d(width-0.5,-shadowsize-10);


			glTexCoord2f(0.66f,0.33f);
			glVertex2d(width-0.5, -shadowsize-10);
			glTexCoord2f(1.0f,0.33f);
			glVertex2d(width+shadowsize-0.5,-shadowsize-10);
			glTexCoord2f(1.0f,0.66f);
			glVertex2d(width+shadowsize-0.5, -tmpheight+0.5);
			glTexCoord2f(0.66f,0.66f);
			glVertex2d(width-0.5, -tmpheight+0.5);

			glTexCoord2f(0.66f,0.66f);
			glVertex2d(width-0.5, -tmpheight+0.5);
			glTexCoord2f(1.0f,0.66f);
			glVertex2d(width+shadowsize-0.5, -tmpheight+0.5);
			glTexCoord2f(1.0f,1.0f);
			glVertex2d(width+shadowsize-0.5, -tmpheight-shadowsize+0.5);
			glTexCoord2f(0.66f,1.0f);
			glVertex2d(width-0.5, -tmpheight-shadowsize+0.5);

			glTexCoord2f(0.66f,0.66f);
			glVertex2d(width-0.5, -tmpheight+0.5);
			glTexCoord2f(0.66f,1.0f);
			glVertex2d(width-0.5, -tmpheight-shadowsize+0.5);
			glTexCoord2f(0.33f,1.0f);
			glVertex2d(shadowsize+0.5,-tmpheight-shadowsize+0.5);
			glTexCoord2f(0.33f,0.66f);
			glVertex2d(shadowsize+0.5,-tmpheight+0.5);

			glTexCoord2f(0.33f,0.66f);
			glVertex2d(shadowsize+0.5,-tmpheight+0.5);
			glTexCoord2f(0.33f,1.0f);
			glVertex2d(shadowsize+0.5,-tmpheight-shadowsize+0.5);
			glTexCoord2f(0.0f,1.0f);
			glVertex2d(0.5,-tmpheight-shadowsize+0.5);
			glTexCoord2f(0.0f,0.66f);
			glVertex2d(0.5,-tmpheight+0.5);
		glEnd();

		// fill the last bits
		glBegin(GL_TRIANGLES);
			glTexCoord2f(0.66f,0.66f);
			glVertex2d(width-0.5,-tmpheight+0.5);
			glTexCoord2f(0.70f,0.66f);
			glVertex2d(width-5.5,-tmpheight+0.5);
			glTexCoord2f(0.66f,0.70f);
			glVertex2d(width-0.5,-tmpheight+5.5);
		glEnd();

		glBegin(GL_TRIANGLES);
			glTexCoord2f(0.33f,0.66f);
			glVertex2d(shadowsize+0.5,-tmpheight+0.5);
			glTexCoord2f(0.0f,0.66f);
			glVertex2d(0.5,-tmpheight+0.5);
			glTexCoord2f(0.0f,0.33f);
			glVertex2d(0.5,-tmpheight+5.5);
		glEnd();
	//}

	//glBindTexture(GL_TEXTURE_2D, font.texture.GetTexID());
	font.texture.BindTex();
	glDisable(GL_TEXTURE_2D);

	// Fill
	if((folded)&&(!openclosing))
		glColor4f(r,g,b,1.0f);
	else
		glColor4f(r+0.2f,g+0.2f,b+0.2f,0.8f);

	glBegin(GL_POLYGON);
		glVertex2d(5.5, -0.5);
		glVertex2d(width-5.5, -0.5);
		glVertex2d(width-2.5, -1.5);
		glVertex2d(width-1.5, -2.5);
		glVertex2d(width-0.5, -5.5);
		glVertex2d(width-0.5, -tmpheight+5.5);
		glVertex2d(width-1.5, -tmpheight+2.5);
		glVertex2d(width-2.5, -tmpheight+1.5);
		glVertex2d(width-5.5, -tmpheight+0.5);
		glVertex2d(5.5, -tmpheight+0.5);
		glVertex2d(2.5, -tmpheight+1.5);
		glVertex2d(1.5, -tmpheight+2.5);
		glVertex2d(0.5, -tmpheight+5.5);
		glVertex2d(0.5, -5.5);
		glVertex2d(1.5, -2.5);
		glVertex2d(2.5, -1.5);
		glVertex2d(5.5, -0.5);
	glEnd();
	/////////////////////////////////////////////////


	// white horizontal lines
    if((!folded)||(openclosing))
	{
		//if (pPrefs->GetCute())
		//{
			glLineWidth(2.0f);
			glColor4f(1.0f,1.0f,1.0f,0.05f);
			for (int linenumber = 6; linenumber <= tmpheight/4; ++linenumber)
			{
				glBegin(GL_LINES);
					glVertex2d(0.5, -linenumber*4+0.5);
					glVertex2d(width-0.5, -linenumber*4+0.5);
				glEnd();
			}
			glLineWidth(1.0f);
		//}
		// Header
		glColor4f(r,g,b,1.0f);
		glBegin(GL_POLYGON);
			glVertex2d(5.5, -0.5);
			glVertex2d(width-5.5, -0.5);
			glVertex2d(width-2.5, -1.5);
			glVertex2d(width-1.5, -2.5);
			glVertex2d(width-0.5, -5.5);
			glVertex2d(width-0.5, -24.5);
			glVertex2d(0.5, -24.5);
			glVertex2d(0.5, -5.5);
			glVertex2d(1.5, -2.5);
			glVertex2d(2.5, -1.5);
			glVertex2d(5.5, -0.5);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
			glVertex2d(width-0.5, -24.5);
			glVertex2d(width-5.5, -24.5);
			glVertex2d(width-2.5, -25.5);
			glVertex2d(width-1.5, -26.5);
			glVertex2d(width-0.5, -29.5);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
			glVertex2d(0.5, -24.5);
			glVertex2d(5.5, -24.5);
			glVertex2d(2.5, -25.5);
			glVertex2d(1.5, -26.5);
			glVertex2d(0.5, -29.5);
		glEnd();
	}

	// Black outlining
	//glColor4f(r/2.0, g/2.0, b/2.0, 1.0f); // slightly darker colour
	//glLineWidth(1.0f);
	glColor4f(outlineR,outlineG,outlineB, 1.0f);
	glLineWidth(outlineWidth);
	//glPushAttrib (GL_LINE_BIT);
	if (outlineStripple == true)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(3, 0x5555);
	}

	glBegin(GL_LINE_STRIP);
		glVertex2d(5.5, -0.5);
		glVertex2d(width-5.5, -0.5);
		glVertex2d(width-2.5, -1.5);
		glVertex2d(width-1.5, -2.5);
		glVertex2d(width-0.5, -5.5);
		glVertex2d(width-0.5, -tmpheight+5.5);
		glVertex2d(width-1.5, -tmpheight+2.5);
		glVertex2d(width-2.5, -tmpheight+1.5);
		glVertex2d(width-5.5, -tmpheight+0.5);
		glVertex2d(5.5, -tmpheight+0.5);
		glVertex2d(2.5, -tmpheight+1.5);
		glVertex2d(1.5, -tmpheight+2.5);
		glVertex2d(0.5, -tmpheight+5.5);
		glVertex2d(0.5, -5.5);
		glVertex2d(1.5, -2.5);
		glVertex2d(2.5, -1.5);
		glVertex2d(5.5, -0.5);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glLineStipple(3, 0xFFFF);
	//glPopAttrib ();


	// Draw the resize triangle

	glColor4f(r-0.1f, g-0.1f, b-0.1f, 1.0f); // slightly darker colour

	if (foldable)
	{
		if (folded)
		{
			glBegin(GL_POLYGON);
				glVertex2d(10, -7);
				glVertex2d(19, -12);
				glVertex2d(10, -17);
			glEnd();
		}

		else
		{
			glBegin(GL_POLYGON);
				glVertex2d(8,-8);
				glVertex2d(19,-8);
				glVertex2d(13,-17);
			glEnd();
		}
	}

    if (closeable)
	{
    	// Draw the delete quad
    	glBegin(GL_QUADS);
    		glVertex2d(width-20,-8);
    		glVertex2d(width-11,-8);
    		glVertex2d(width-11,-17);
    		glVertex2d(width-20,-17);
    	glEnd();
    }

	// draw the title
	// return to these values if not anti aliased font is used
	/*if(folded)glColor3f(r-0.2f,g-0.2f,b-0.2f);
	else glColor3f(r+0.3f,g+0.3f,b+0.3f);*/
	if(folded)glColor3f(r-0.4f,g-0.4f,b-0.4f);
	else glColor3f(r+0.4f,g+0.4f,b+0.4f);
	pTitlelabel->Draw();

	// move back to world system
	glTranslated(-posx,-posy,0);
	// glLoadIdentity();

	// move to local system
	glTranslated(posx,posy,0);

	if(openclosing == false)
	{
		// draw the interface
		if (folded == false)
		{
			//DrawInterface();
			if (childList.ToLast())
    		do
    		{
    			((UI_base*)childList.GetCurrentObjectPointer())->Draw();
    		}while(childList.ToPrevious());
		}
	}
	//DrawInterface();

	// move back to world system
			glTranslated(-posx,-posy,0);
}



UI_base* UI_window::OnLButtonDown(int x, int y)
{
    if (pInterceptChild==this)
    {
        // if the mouse is in the window header
    	if((x >= posx) && (x <= (posx+width)) && (y >= (posy-26)) && (y <= posy)&& (dragable))
    	{
    		dragging = true;

    		// minimize button pressed
    		 if(((x >= posx + 8) && (x <= posx + 19) && (y <= posy - 4) && (y >= posy - 17) && (foldable))||
    		// delete
    		((x >= posx + width - 20) && (x <= posx + width - 11) && (y <= posy - 8) && (y >= posy - 17)&& (closeable)))
    			dragging = false;

            pInterceptChild = this;
            return this;
    	}
    	pInterceptChild = 0;
    }

    UI_base::OnLButtonDown(x, y);

    if (!pInterceptChild)
    {
        if(Hittest(x,y)){
            pInterceptChild = this;
        }else{
            return 0;
        }
    }
    return this;

}

UI_base* UI_window::OnLButtonUp(int x, int y)
{
   if (pInterceptChild==this)
   {
    	// check if mouse is still on buttons, then change values, otherwise ingnore the pressing of the button
    	if (dragging)
    	{
    		/*
    		if(pPrefs->GetGridSize())
    		{
    			// align to grid
    			int dev = posx % pPrefs->GetGridSize();
    			if (dev >= pPrefs->GetGridSize()/2) posx += pPrefs->GetGridSize() - dev;
    			else posx -= dev;

    			dev = posy % pPrefs->GetGridSize();
    			if (dev >= pPrefs->GetGridSize()/2) posy += pPrefs->GetGridSize() - dev;
    			else posy -= dev;
    		}
    */
    		dragging = false;
    	}

    	// minimize button pressed
    	if((x >= posx + 8) && (x <= posx + 19) && (y <= posy - 4) && (y >= posy - 17) && (foldable))
    	{
            openclosing = foldSteps;
    	}

    	// delete
    	if ((x >= posx + width - 20) && (x <= posx + width - 11) && (y <= posy - 8) && (y >= posy - 17)&& (closeable))
    	{
    		killMe = true;
    		if(onClose) onClose(this);
    	}

    	pInterceptChild = 0;
    }

    UI_base::OnLButtonUp(x, y);

    if (!pInterceptChild)
    {
        if(Hittest(x,y)){
            pInterceptChild = this;
        }else{
            return 0;
        }
    }
    return this;
}

UI_base* UI_window::OnMouseMove(int x, int y, int prevx, int prevy)
{
    if(pInterceptChild == this)
    {
        if (dragging)
        {
    		SetPos(posx + x - prevx, posy + y - prevy);
    		pInterceptChild = this;
            return this;
        }
        pInterceptChild =0;
    }

    UI_base::OnMouseMove(x, y, prevx, prevy);

    if (!pInterceptChild)
    {
        if(Hittest(x,y)){
            pInterceptChild = this;
        }else{
            return 0;
        }
    }
    return this;

}

UI_base* UI_window::OnKeyPressed(int key)
{
    if (pInterceptChild == this)
    {
        if (dragging) return this;
        pInterceptChild =0;
    }
	UI_base::OnKeyPressed(key);

    if (pInterceptChild)
	   return this;
    return NULL;
}

void UI_window::SetFoldSteps(unsigned char steps)
{
    foldSteps = steps;
}


