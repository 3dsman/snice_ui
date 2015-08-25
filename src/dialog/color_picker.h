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
#include "include/color_conversion.h"
class W_colorSelectDisplay;
class W_slider;
class W_button;
class W_colorDisplay;

class D_ColorPicker : public UI_dialog		// Mix Material Block
{

protected:
	W_colorSelectDisplay* pRgbcolor;
	W_slider* pSRed;
	W_slider* pSGreen;
	W_slider* pSBlue;
	W_slider* pSHue;
	W_slider* pSSaturation;
	W_slider* pSLuminosity;
	
	W_button* pBRed;
	W_button* pBGreen;
	W_button* pBBlue;
	W_button* pBHue;
	W_button* pBSaturation;
	W_button* pBLuminosity;
	
	W_colorDisplay* pBeforecolor;
	W_colorDisplay* pAftercolor;

	float redColor, greenColor, blueColor;
	
	std::function<void(UI_base * asker, D_ColorPicker* caller, float red, float green, float blue)> onColorChange = NULL;
	UI_base * onColorChangeAsker = NULL; 

	int mode;
	bool active;
public:

	D_ColorPicker(int x, int y,float initRed, float initGreen, float initBlue);


	~D_ColorPicker();
	UI_base* OnMouseMove(int x, int y, int prevx, int prevy);


    /**	\brief static function to handle children colorSelectDisplay callbacks .*/
    static void StatChangeColorSelectDisplay(UI_base * asker, W_colorSelectDisplay* caller,float red, float green, float blue);
    /**	\brief the function called by StatChangeColorSelectDisplay to push children callbacks to the good instance of D_ColorPicker.*/
    void ChangeColorSelectDisplay( W_colorSelectDisplay* caller,float red, float green, float blue);
	
    /**	\brief static function to handle children sliders callbacks .*/
	static void StatChangeColorSliders(UI_base * asker, W_slider* caller,float value, bool realtime);
    /**	\brief the function called by StatChangeColorSliders to push children callbacks to the good instance of D_ColorPicker.*/
    void ChangeColorSliders( W_slider* caller,float value, bool realtime);
	
    /**	\brief static function to handle children buttons callbacks .*/
	static void StatChangeMode(UI_base * asker, W_button* caller);
    /**	\brief the function called by StatChangeColorSliders to push children callbacks to the good instance of D_ColorPicker.*/
    void ChangeMode( W_button* caller);

	void RefreshSelect();
	void RefreshSliders();


	void SetPicker(float valRed,float valGreen,float valBlue);
	float GetActiveColor(colorSelector RGB);

	void Callback(UI_base * pCallObject, unsigned char callIndex );

	void SetSliders();
	
    /**	\brief function to set the onColorChange callback function.*/
	void OnColorChange(UI_base * asker, std::function<void(UI_base * asker, D_ColorPicker* caller, float red, float green, float blue)> function);
	
};

#endif // _SNICE_COLORPICKER_H_
