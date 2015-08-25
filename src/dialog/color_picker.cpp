// color_picker.cpp: ColorPicker dialog box.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// SNICE : Simple Nodal Image Compositing Environment
// SNICE is a image and video compositing software
// Copyright by Sebastien Tricoire (3dsman@free.fr) and Lionel Allorge (lionel.allorge@lunered.org)
///
// based on Crafter (Leaf) Library by Wybren van Keulen (www.funnyfarm.tv)
// based on GLFW Library (www.glfw.org)
//
// color_picker.cpp
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

//#include "snice.h"
//#include "viewports_array.h"
//#include "nodes/container.h"

//#include "color_conversion.h"

#include "widget/color_select_display.h"
#include "widget/color_display.h"
#include "widget/slider.h"
#include "widget/label.h"

#include "color_picker.h"
#include "UI_image.h"

D_ColorPicker::D_ColorPicker(int x, int y,float initRed, float initGreen, float initBlue)
			  :UI_dialog(x, y, 450, 300, "ColorPicker",false, false)
{
	mode = 1;

	r = 0.4f;
	g = 0.4f;
	b = 0.4f;

	pRgbcolor = new W_colorSelectDisplay(10, -35, 255, 255,H,initRed, initGreen, initBlue);
	pRgbcolor->OnChange(this, D_ColorPicker::StatChangeColorSelectDisplay);
	AddChild(pRgbcolor);

	pBeforecolor = new W_colorDisplay(310, -35, 55, 64, "before");
	AddChild(pBeforecolor);
	pAftercolor = new W_colorDisplay(375, -35, 55, 64, "after");
	AddChild(pAftercolor);

	redColor = initRed;
	greenColor = initGreen;
	blueColor = initBlue;
	pBeforecolor->SetColor(initRed,initGreen,initBlue);

	pSRed = new W_slider(310,-153,120,20,"red", 128.0f, 0.0f, 255.0f, 0, 0, 1.0f, 0.3f, 0.3f);
	AddChild(pSRed);
	pSRed->OnSetValue(this, D_ColorPicker::StatChangeColorSliders);
	pSGreen = new W_slider(310,-175,120,20, "green" , 128.0f, 0.0f, 255.0f, 0, 0, 0.3f, 1.0f, 0.3f);
	AddChild(pSGreen);
	pSGreen->OnSetValue(this, D_ColorPicker::StatChangeColorSliders);
	pSBlue = new W_slider(310,-197,120,20, "blue" , 128.0f, 0.0f, 255.0f, 0, 0, 0.3f, 0.3f, 1.0f);
	AddChild(pSBlue);
	pSBlue->OnSetValue(this, D_ColorPicker::StatChangeColorSliders);

	pSHue = new W_slider(310,-226,120,20,  "hue", 0.0f, 0.0f, 360.0f, 0, 0, 0.3f, 0.3f, 0.3f);
	AddChild(pSHue);
	pSHue->OnSetValue(this, D_ColorPicker::StatChangeColorSliders);
	pSSaturation = new W_slider(310,-248,120,20,"Saturation", 0.0f, 0.0f, 100.0f, 0 , 0, 0.3f, 0.3f, 0.3f);
	AddChild(pSSaturation);
	pSSaturation->OnSetValue(this, D_ColorPicker::StatChangeColorSliders);
	pSLuminosity = new W_slider(310,-270,120,20, "luminosity", 0.0f, 0.0f, 100.0f, 0, 0, 0.3f, 0.3f, 0.3f);
	AddChild(pSLuminosity);
	pSLuminosity->OnSetValue(this, D_ColorPicker::StatChangeColorSliders);

	RefreshSliders();

}



D_ColorPicker::~D_ColorPicker(){}

UI_base* D_ColorPicker::OnMouseMove(int x, int y, int prevx, int prevy)
{
	if (!Hittest(x, y))
		{
			killMe = true;
    		if(onClose) onClose(onCloseAsker, this);
			return nullptr;
		}
	return UI_window::OnMouseMove(x, y, prevx, prevy);
};


void D_ColorPicker::StatChangeColorSelectDisplay(UI_base * asker, W_colorSelectDisplay* caller,float red, float green, float blue)
{
		(dynamic_cast<D_ColorPicker*> (asker))->ChangeColorSelectDisplay(caller, red,  green,  blue);
};

void D_ColorPicker::ChangeColorSelectDisplay(W_colorSelectDisplay* caller,float red, float green, float blue)
{
	
    redColor = red;
    greenColor = green;
	blueColor = blue;
	RefreshSliders();
	
	if(onColorChange)
		onColorChange(onColorChangeAsker, this,redColor, greenColor, blueColor);
}

void D_ColorPicker::StatChangeColorSliders(UI_base * asker, W_slider* caller,float value, bool realtime)
{
		(dynamic_cast<D_ColorPicker*> (asker))->ChangeColorSliders(caller, value, realtime);
};

void D_ColorPicker::ChangeColorSliders(W_slider* caller,float value, bool realtime)
{
		float hue, saturation, luminosity;
		
		if ((caller == pSRed)||(caller == pSGreen)||(caller == pSBlue))
		{
			//red
			if (caller == pSRed)
				redColor = value/255.0f;

			//green
			if (caller == pSGreen)
				greenColor = value/255.0f;

			//blue
			if (caller == pSBlue)
				blueColor = value/255.0f;
			
			// set the hsv sliders
			RGBtoHSV(redColor, greenColor, blueColor, &hue, &saturation, &luminosity);
			pSHue->SetValue(hue, false);
			pSSaturation->SetValue(saturation*100, false);
			pSLuminosity->SetValue(luminosity*100, false);
		}else{
			
			RGBtoHSV(redColor, greenColor, blueColor, &hue, &saturation, &luminosity);
			
			//hue
			if (caller == pSHue)
			{
				hue = value;
			}else
			//saturation
			if (caller == pSSaturation)
			{
				saturation = value/100.0f;
			}else
			//luminosity
			if (caller == pSLuminosity)
			{
				luminosity = value/100.0f;
			}
			
			HSVtoRGB(hue,saturation,luminosity,&redColor,&greenColor,&blueColor);
			pSRed->SetValue(redColor*255.0f, false);
			pSGreen->SetValue(greenColor*255.0f, false);
			pSBlue->SetValue(blueColor*255.0f, false);
			
		}
	pRgbcolor->SetColor(redColor, greenColor, blueColor);
	pAftercolor->SetColor(redColor, greenColor, blueColor);
	
	if(onColorChange)
		onColorChange(onColorChangeAsker, this,redColor, greenColor, blueColor);
}

void D_ColorPicker::RefreshSelect(){
/*
	UI_image* Image;

	//Image.SetData(&(pRgbcolor->PreviewImage);

	int k = 0;
	float red, green, blue;
	float hue, saturation, luminosity;

	float invRgbcolor2Cury = float(255-pRgbcolor2->cury) / 255.0f;
	float hueInvRgbcolor2Cury = invRgbcolor2Cury*360.0f;
	int i,j;

	for (i=0; i<int(Image.GetHeight()); ++i){
		for (j=0; j<int(Image.GetWidth()); ++j){
			switch (mode)
			{

				//hue
				case 0:
				{
					hue = hueInvRgbcolor2Cury;
					saturation = float(255-j)/ 255.0f;
					luminosity = float(255-i) / 255.0f ;

					HSV2RGB(hue,saturation,luminosity,&red,&green,&blue);
					break;
				}

				//saturation
				case 1:
				{
					hue = float(255-j)/ 255.0f*360.0f;
					saturation = invRgbcolor2Cury;
					luminosity = float(255-i) / 255.0f ;

					HSV2RGB(hue,saturation,luminosity,&red,&green,&blue);
					break;
				}

				//luminosity
				case 2:
				{
					hue = float(255-j)/ 255.0f*360.0f;
					saturation = float(255-i) / 255.0f ;
					luminosity = invRgbcolor2Cury;

					HSV2RGB(hue,saturation,luminosity,&red,&green,&blue);
					break;
				}
				//red
				case 3:
				{
					red= float(pRgbcolor2->cury);
					green= float(j);
					blue= float(i);
					break;
				}

				//green
				case 4:
				{
					red= float(j);
					green= float(pRgbcolor2->cury);
					blue= float(i);
					break;
				}

				//blue
				case 5:
				{
					red= float(j);
					green= float(i);
					blue= float(pRgbcolor2->cury);
					break;
				}
			}

			Image[k] = char(red * 255);
			k++;
			Image[k] = char(green * 255);
			k++;
			Image[k] = char(blue * 255);
			k++;
		}
	}


	// horizontal bar
	for (j= (pRgbcolor->cury ) * Image->width * 3; j < int(pRgbcolor->cury * Image->width +(Image->width-1)) * 3;++j){
		Image->imageData[j] = 1 - (Image->imageData[j]);
	}

	// vertical bar
	i = (255 - pRgbcolor->curx) * 3;
	for (j = 0; j < int(Image->height) ;++j){
		Image->imageData[i] = 1 - (Image->imageData[i]);
		Image->imageData[i+1] = 1 - (Image->imageData[i+1]);
		Image->imageData[i+2] = 1 - (Image->imageData[i+2]);
		i += Image->width*3;
	}

	pRgbcolor->RefreshImage();
*/
}

void D_ColorPicker::RefreshSliders(){
//	float valRed, valGreen, valBlue;
	float hue, saturation, luminosity;

/*

	switch (mode)
	{

		//hue
		case 0:
		{
			hue = float(255-pRgbcolor2->cury) / 255.0f*360.0f;
			saturation = float(pRgbcolor->curx) / 255.0f;
			luminosity = float(255-pRgbcolor->cury) / 255.0f;
			HSVtoRGB(hue,saturation,luminosity,&valRed,&valGreen,&valBlue);
			break;
		}
			//saturation
		case 1:
		{
			hue = float(pRgbcolor->curx) / 255.0f*360.0f;
			saturation = float(255-pRgbcolor2->cury) / 255.0f;
			luminosity = float(255-pRgbcolor->cury) / 255.0f;
			HSVtoRGB(hue,saturation,luminosity,&valRed,&valGreen,&valBlue);
			break;
		}

		//luminosity
		case 2:
		{
			hue = float(pRgbcolor->curx) / 255.0f*360.0f;
			saturation = float(255-pRgbcolor->cury) / 255.0f;
			luminosity = float(255-pRgbcolor2->cury) / 255.0f;
			HSVtoRGB(hue,saturation,luminosity,&valRed,&valGreen,&valBlue);
			break;
		}
		//red
		case 3:
		{
			valRed = float(255-pRgbcolor2->cury) / 255.0f;
			valGreen = float(pRgbcolor->curx) / 255.0f;
			valBlue = float(255-pRgbcolor->cury) / 255.0f;
			RGBtoHSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			break;
		}
		//green
		case 4:
		{
			valRed = float(pRgbcolor->curx) / 255.0f;
			valGreen = float(255-pRgbcolor2->cury) / 255.0f;
			valBlue = float(255-pRgbcolor->cury) / 255.0f;
			RGBtoHSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			break;
		}

		//blue
		case 5:
		{
			valRed = float(pRgbcolor->curx) / 255.0f;
			valGreen = float(255-pRgbcolor->cury) / 255.0f;
			valBlue = float(255-pRgbcolor2->cury) / 255.0f;
			RGBtoHSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			break;
		}
	}*/
	//red->setValue(valRed);
	//green->setValue(valGreen);
	//blue->setValue(valBlue);
    //pRgbcolor->GetColor(&valRed,&valGreen,&valBlue);
    RGBtoHSV(redColor, greenColor, blueColor, &hue, &saturation, &luminosity);


    pSRed->SetValue(redColor*255, false);
	pSGreen->SetValue(greenColor*255, false);
	pSBlue->SetValue(blueColor*255, false);
	if (!((redColor==greenColor)&&(redColor==blueColor))) pSHue->SetValue(hue, false);
	pSSaturation->SetValue(saturation*100, false);
	pSLuminosity->SetValue(luminosity*100, false);

	pAftercolor->SetColor(redColor, greenColor, blueColor);
}


void D_ColorPicker::SetPicker(float valRed,float valGreen,float valBlue){
    /*
	switch (mode)
	{

		//hue
		case 0:
		{
			float hue,saturation,luminosity;
			RGBtoHSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			pRgbcolor2->cury = int(255 - hue / 360*255);
			pRgbcolor->curx = int(saturation * 255);
			pRgbcolor->cury = int(255 - luminosity * 255);
			break;
		}
			//saturation
		case 1:
		{
			float hue,saturation,luminosity;
			RGBtoHSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			pRgbcolor->curx = int(hue / 360*255);
			pRgbcolor2->cury = int(255 - saturation * 255);
			pRgbcolor->cury = int(255 - luminosity * 255);
			break;
		}

		//luminosity
		case 2:
		{
			float hue,saturation,luminosity;
			RGBtoHSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			pRgbcolor->curx = int(hue / 360*255);
			pRgbcolor->cury = int(255 - saturation * 255);
			pRgbcolor2->cury = int(255 - luminosity * 255);
			break;
		}
		//red
		case 3:
		{
			pRgbcolor2->cury = int(255 - valRed *255);
			pRgbcolor->curx = int(valGreen * 255);
			pRgbcolor->cury = int(255 - valBlue * 255);
			break;
		}
		//green
		case 4:
		{
			pRgbcolor->curx = int(valRed *255);
			pRgbcolor2->cury = int(255 - valGreen * 255);
			pRgbcolor->cury = int(255 - valBlue * 255);
			break;
		}

		//blue
		case 5:
		{
			pRgbcolor->curx = int(valRed *255);
			pRgbcolor->cury = int(255 - valGreen * 255);
			pRgbcolor2->cury = int(255 - valBlue * 255);
			break;
		}

	}
*/
}

float D_ColorPicker::GetActiveColor(colorSelector RGB)
{
		switch (RGB)
		{
		case R:
			return pSRed->GetValue()/255.0f;
		case G:
			return pSGreen->GetValue()/255.0f;
		case B:
			return pSBlue->GetValue()/255.0f;
		default:
			return 0;
		}
}

void D_ColorPicker::OnColorChange(UI_base * asker, std::function<void(UI_base * asker, D_ColorPicker* caller, float red, float green, float blue)> function)
{
    onColorChange = function;
	onColorChangeAsker = asker;
}