// ColorPicker.h: ColorPicker dialog box.
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
// ColorPicker.cpp
// This file is the ColorPicker dialog box file
// File created by Tricoire Sebastien
// Date of creation : 2004 06 02
///
// File modified by Lionel Allorge
// Date of modification : 2004 06 02
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

#ifndef _SNICE_COLORPICKER_H_
#define _SNICE_COLORPICKER_H_

#include "UI_dialog.h"
class W_colorSelectdisplay;
class W_slider;
class W_colorDisplay;

class D_ColorPicker : public UI_dialog		// Mix Material Block
{
	
private:
	W_colorSelectdisplay* pRgbcolor;
	W_colorSelectdisplay* pRgbcolor2;
	W_slider* pSRed;
	W_slider* pSGreen;
	W_slider* pSBlue;
	W_slider* pSHue;
	W_slider* pSSaturation;
	W_slider* pSLuminosity;
	W_colorDisplay* pBeforecolor;
	W_colorDisplay* pAftercolor;

	float redColor, greenColor, blueColor;

	int mode; 
	bool active;
public:

	D_ColorPicker(int x, int y,float initRed, float initGreen, float initBlue);

	
	~D_ColorPicker();
		
	void CalcOutput(int iOutputNumber, void* Result);

	void OnMouseMove(int x, int y, int prevx, int prevy);

	void OnKeyPressed(int key){};


	void RefreshImage();

	void RefreshBand();
	void RefreshSliders();


	void SetPicker(float valRed,float valGreen,float valBlue);
	float GetActiveColor(int RGB);

	void Callback(UI_base * pCallObject, unsigned char callIndex );

	void SetSliders();
};

#endif // _SNICE_COLORPICKER_H_
