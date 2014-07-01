// viewports_array.cpp: viewports_array class.
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
// viewports_array.cpp
// This file is the file of the imageViewport class
// File created by Tricoire Sebastien
// Date of creation : 2008 18 03
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

/////////////////////////////////////////////
// Includes
/////////////////////////////////////////////


#include "viewports_array.h"


ViewportsArray::ViewportsArray(int x, int y,int w, int h)
			  :UI_base(x, y, w, h),
pMouseMoveIntercept(NULL),
pLButtonDownIntercept(NULL),
pLButtonUpIntercept(NULL),
pKeyPressedIntercept(NULL),
pCharPressedIntercept(NULL)
{

	deletewhendone = false;

	interceptx = 0;
	intercepty = 0;
	zoom = 1;

	modalWindow = 0;

	r = 0;
	g = 0;
	b = 0;
	pView1 = new Viewport(0,0,100,50);
	pView2 = new Viewport(0,50,100,50);
	Viewports.push_back( Viewport(0,0,100,50));
	Viewports.push_back( Viewport(0,50,100,50));

};

ViewportsArray::~ViewportsArray()
{/*
    for ( size_t i = 0, size = Viewports.size(); i < size; ++i )
    {
        delete Viewports[ i ];
    }*/
	if (pView1)
	{
		delete pView1;
		pView1 = NULL;
	}

	if (pView1)
	{
		delete pView1;
		pView1 = NULL;
	}
};

UI_window* ViewportsArray::GetModalWindow()
{
	return modalWindow;
}

UI_window * ViewportsArray::SetModalWindow(UI_window* window, UI_base * callback)
{
	if (!modalWindow)
	{
		modalWindow = window;
		modalWindow->SetParentUIbase(callback);
		modalWindow->SetPos(iMousePosx-10,iMousePosy+10);
		return modalWindow;
	}
	return 0;
}

void ViewportsArray::DelModalWindow(){
	delete modalWindow;
	modalWindow = 0;
}

UI_base* ViewportsArray::OnLButtonDown(int x, int y)
{
	if (pLButtonDownIntercept)
		pLButtonDownIntercept->OnLButtonDownIntercept((int)(iMousePosx * zoom - interceptx),(int)(iMousePosy * zoom - intercepty));
	else if (GetModalWindow())
		((UI_window*)GetModalWindow())->OnLButtonDown(iMousePosx, iMousePosy);
	else
	    for ( size_t i = 0, size = Viewports.size(); i < size; ++i )
        {
            if ((Viewports[i]).Hittest(iMousePosx,iMousePosy))
                (Viewports[i]).OnLButtonDown(iMousePosx,iMousePosy);
        }
        /*
	else if (pView1->Hittest(iMousePosx,iMousePosy))
		pView2->OnLButtonDown(iMousePosx,iMousePosy);
	else if (pView2->Hittest(iMousePosx,iMousePosy))
		pView2->OnLButtonDown(iMousePosx,iMousePosy);
		*/
};



UI_base* ViewportsArray::OnRButtonDown(int x, int y)
{
	if (!GetModalWindow())
	{
        for ( size_t i = 0, size = Viewports.size(); i < size; ++i )
        {
            if ((Viewports[i]).Hittest(iMousePosx,iMousePosy))
                (Viewports[i]).OnRButtonDown(iMousePosx,iMousePosy);
        }
        /*
		if (pView1->Hittest(iMousePosx,iMousePosy))
			pView2->OnRButtonDown(iMousePosx,iMousePosy);
		else if (pView1->Hittest(iMousePosx,iMousePosy))
			pView2->OnRButtonDown(iMousePosx,iMousePosy);
			*/
	}

}

UI_base* ViewportsArray::OnLButtonUp(int x, int y)
{
	if (pLButtonUpIntercept)
		pLButtonUpIntercept->OnLButtonUpIntercept((int)(iMousePosx * zoom - interceptx),(int)(iMousePosy * zoom - intercepty));
	else if (GetModalWindow())
	{
		((UI_window*)GetModalWindow())->OnLButtonUp(iMousePosx,iMousePosy);
		if (deletewhendone)
		{
			DelModalWindow();
			deletewhendone = 0;
		}

		return;
	}
	else
	    for ( size_t i = 0, size = Viewports.size(); i < size; ++i )
        {
            if ((Viewports[i]).Hittest(iMousePosx,iMousePosy))
                (Viewports[i]).OnLButtonUp(iMousePosx,iMousePosy);
        }
        /*
	else if (pView1->Hittest(iMousePosx,iMousePosy))
		pView1->OnLButtonUp(iMousePosx,iMousePosy);
	else if (pView2->Hittest(iMousePosx,iMousePosy))
		pView2->OnLButtonUp(iMousePosx,iMousePosy);
		*/
};

UI_base* ViewportsArray::OnRButtonUp(int x, int y)
{
	if (!GetModalWindow())
	{
        for ( size_t i = 0, size = Viewports.size(); i < size; ++i )
        {
            if ((Viewports[i]).Hittest(iMousePosx,iMousePosy))
                (Viewports[i]).OnRButtonUp(iMousePosx,iMousePosy);
        }
        /*
		if (pView1->Hittest(iMousePosx,iMousePosy))
			pView1->OnRButtonUp(iMousePosx,iMousePosy);
		else if (pView2->Hittest(iMousePosx,iMousePosy))
			pView2->OnRButtonUp(iMousePosx,iMousePosy);
			*/
	}
}


UI_base* ViewportsArray::OnMouseMove(int x, int y, int prevx, int prevy)
{
	iMousePosx = x;
	iMousePosy =  height - y;

	if (pMouseMoveIntercept)
	{
		pMouseMoveIntercept->OnMouseMoveIntercept((int)(iMousePosx*zoom-interceptx),(int)(iMousePosy*zoom-intercepty), (int)(iPrevMousePosx*zoom-interceptx),(int)(iPrevMousePosy*zoom-intercepty));
	}
	else
		if (GetModalWindow())
		{
			((UI_window*)GetModalWindow())->OnMouseMove(iMousePosx, iMousePosy, iPrevMousePosx, iPrevMousePosy);
			if (deletewhendone)
			{
				DelModalWindow();
				deletewhendone = 0;
			}
		}
		else
		{
            for ( size_t i = 0, size = Viewports.size(); i < size; ++i )
            {
                (Viewports[i]).OnMouseMove(iMousePosx,iMousePosy,iPrevMousePosx,iPrevMousePosy);
            }
            /*
			pView1->OnMouseMove(iMousePosx,iMousePosy,iPrevMousePosx,iPrevMousePosy);
			pView2->OnMouseMove(iMousePosx,iMousePosy,iPrevMousePosx,iPrevMousePosy);
			*/
		}
	iPrevMousePosx = iMousePosx;
	iPrevMousePosy = iMousePosy;
};


UI_base* ViewportsArray::OnKeyPressed(int key)
{
	if (pKeyPressedIntercept)
		pKeyPressedIntercept->OnKeyPressedIntercept(key);
	else
		if (GetModalWindow())
			((UI_window*)GetModalWindow())->OnKeyPressed(key);
		else
		    for ( size_t i = 0, size = Viewports.size(); i < size; ++i )
            {
                if ((Viewports[i]).Hittest(iMousePosx,iMousePosy))
                    (Viewports[i]).OnKeyPressed(key);
            }
            /*
			if (pView1->Hittest(iMousePosx,iMousePosy))
				pView1->OnKeyPressed(key);
			else
				if (pView2->Hittest(iMousePosx,iMousePosy))
					pView2->OnKeyPressed(key);
					*/
};


UI_base* ViewportsArray::OnCharPressed(int character)
{
		if (pCharPressedIntercept)
			pCharPressedIntercept->OnCharPressedIntercept(character);
		else
			if (GetModalWindow())
				((UI_window*)GetModalWindow())->OnCharPressed(character);
			else
				for ( size_t i = 0, size = Viewports.size(); i < size; ++i )
                {
                    if ((Viewports[i]).Hittest(iMousePosx,iMousePosy))
                        (Viewports[i]).OnCharPressed(character);
                }
                /*
			if (pView1->Hittest(iMousePosx,iMousePosy))
				pView1->OnCharPressed(character);
			else
				if (pView2->Hittest(iMousePosx,iMousePosy))
					pView2->OnCharPressed(character);
					*/
}


void ViewportsArray::Callback(UI_base * pCallObject, unsigned char callIndex ){};


void ViewportsArray::setIntercept( UI_base * object )
{
	pMouseMoveIntercept = object;
	pLButtonDownIntercept = object;
	pLButtonUpIntercept = object;
	pKeyPressedIntercept = object;
	pCharPressedIntercept = object;

	interceptx = 0;
	intercepty = 0;
	zoom = 1;
	if (object)
		object->GetScreenToLocalMatrix(object, &interceptx, &intercepty, &zoom);
}

void ViewportsArray::Resize(int x, int y,int w, int h)
{
	posx = x;
	posy = y;
	width = w;
	height = h;
	for ( size_t i = 0, size = Viewports.size(); i < size; ++i )
    {
        if ((Viewports[i]).Hittest(iMousePosx,iMousePosy))
            (Viewports[i]).OnCharPressed(character);
    }
	pView1->Resize(x,y,w, h/2-5);
	pView2->Resize(x,h/2+5+y,w, h/2-5);
	//pView1->Resize(x,y,w, h);
	//pView2->Resize(x,h,w, 1);
};

void ViewportsArray::Draw()
{
	pView1->Draw();
	pView2->Draw();

	glViewport( posx, posy, width, height );			// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();
	glOrtho(posx,posx+width,posy,posy+height,-1,1);				// Set Up An Ortho Screen

	if (GetModalWindow())
	{
		((UI_window*)GetModalWindow())->Draw();
	}
};

