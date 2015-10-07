// array.h: Array widget.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// SNICE : Simple Nodal Image Compositing Environment
// SNICE is a image and video compositing software
// Copyright by Sebastien Tricoire (3dsman@free.fr)
///
// based on Crafter (Leaf) Library by Wybren van Keulen (www.funnyfarm.tv)
// based on GLFW Library (www.glfw.org)
// 
// array.h
// This file is the array class for grid placement of widgets
///
// Copyright (C) 2004 Sebastien Tricoire.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 2 as published by the Free Software Foundation;
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//////////////////////////////////////////////////



#ifndef _SNICE_array_H_
#define _SNICE_array_H_

#include <vector>

//#define colSize 300

class W_array : public UI_widget
{
private:
	struct cell
    {
        UI_base* content = 0;
		bool snapLeft = true;
		bool snapRight = false;
		bool snapTop = true;
		bool snapBottom = false;
        Color color;
    };
	//unsigned int x, y = 0;
	unsigned int marginX = 2;
	unsigned int marginY = 2;
	unsigned int borderX = 10;
	unsigned int borderY = 10;
	unsigned int defWidth = 200;
	unsigned int defHeight = 20;
	bool shift;
	vector< vector<cell> > array;
	vector<float> xSizeArray;
	vector<float> ySizeArray;
	
	std::function<void(UI_base * asker, W_array* caller, unsigned int x, unsigned int y)> onClickCell = NULL;
	UI_base * onClickCellAsker = NULL;
	
	void RefreshContentPos(unsigned int x, unsigned int y, unsigned int cellPosx, unsigned int cellPosy);
	void RefreshContentPos(unsigned int x, unsigned int y);
	void RefreshContentPos();

public:

	W_array(int x, int y, int w, int h,unsigned int sizeX, unsigned int sizeY,unsigned int defWidth, unsigned int defHeight, float red = defaultR, float green = defaultG, float blue = defaultB);

	~W_array();

	/** \brief To set the width of the object.*/
	virtual void SetWidth(int w);

	/**	\brief To set the height of the object.*/
	virtual void SetHeight(int w);
	
	void SetContent(unsigned int x, unsigned int y, UI_base* widget, bool snapLeft = true, bool snapRight = false, bool snapTop = false, bool snapBottom = false);
	UI_base* GetContent(unsigned int x, unsigned int y);
	void SetContentPos(unsigned int x, unsigned int y, bool snapLeft, bool snapRight, bool snapTop, bool snapBottom);

    void ClearContent();

	void SetLineHeight(unsigned int y, unsigned int lineHeight);
	void SetcollumnWidth(unsigned int x, unsigned int colWidth);

    void SetCellColor(unsigned int x, unsigned int y, Color color);

	void SetMargin(unsigned int marginX, unsigned int marginY, unsigned int borderX, unsigned int borderY);
	void Resize(unsigned int sizeX, unsigned int sizeY);

    unsigned int getSizeX();
    unsigned int getSizeY();
	
	void OnClickCell(UI_base * asker, void (*function)(UI_base * asker, W_array* caller, unsigned int x, unsigned int y));
	
	UI_base* OnLButtonUp(int x, int y);

	void GetSelectedList();

    void Draw();

};

#endif // _SNICE_array_H_
