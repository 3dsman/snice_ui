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

#include "snice.h"
#include "viewports_array.h"
#include "nodes/container.h"

#include "color_conversion.h"

#include "widget/color_select_display.h"
#include "widget/color_display.h"
#include "widget/slider.h"
#include "widget/label.h"

#include "color_picker.h"

//D_ColorPicker::D_ColorPicker(){}

D_ColorPicker::D_ColorPicker(int x, int y,float initRed, float initGreen, float initBlue)
			  :UI_dialog(x, y, 450, 300, "ColorPicker",false, false)
{
	mode = 1;

	r = 0.4f;
	g = 0.4f;
	b = 0.4f;

	pRgbcolor = new W_colorSelectdisplay(10, -35, 255, 255, 256, 256);
	AddChild(pRgbcolor);
	pRgbcolor2 = new W_colorSelectdisplay(270, -35, 35, 255, 4, 256);
	AddChild(pRgbcolor2);

	pBeforecolor = new W_colorDisplay(310, -35, 55, 64, "before");
	AddChild(pBeforecolor);
	pAftercolor = new W_colorDisplay(375, -35, 55, 64, "after");
	AddChild(pAftercolor);

	redColor = initRed;
	greenColor = initGreen;
	blueColor = initBlue;
	pBeforecolor->SetColor(initRed,initGreen,initBlue);

	pSRed = new W_slider(310,-153,120,20,"red", 128.0f, 0.0f, 255.0f, 0, 1.0f, 0.3f, 0.3f);
	AddChild(pSRed);
	pSGreen = new W_slider(310,-175,120,20, "green" , 128.0f, 0.0f, 255.0f, 0 , 0.3f, 1.0f, 0.3f);
	AddChild(pSGreen);
	pSBlue = new W_slider(310,-197,120,20, "blue" , 128.0f, 0.0f, 255.0f, 0,	0.3f, 0.3f, 1.0f);
	AddChild(pSBlue);

	pSHue = new W_slider(310,-226,120,20,  "hue", 0.0f, 0.0f, 360.0f, 0,	0.3f, 0.3f, 0.3f);
	AddChild(pSHue);
	pSSaturation = new W_slider(310,-248,120,20,"Saturation", 0.0f, 0.0f, 100.0f, 0 ,		0.3f, 0.3f, 0.3f);
	AddChild(pSSaturation);
	pSLuminosity = new W_slider(310,-270,120,20, "luminosity", 0.0f, 0.0f, 100.0f, 0,		0.3f, 0.3f, 0.3f);
	AddChild(pSLuminosity);

	SetPicker(initRed,initGreen,initBlue);
	RefreshImage();
	RefreshBand();
	
	RefreshSliders();
	
}



D_ColorPicker::~D_ColorPicker(){}

void D_ColorPicker::Callback(UI_base * pCallObject, unsigned char callIndex )
{
	if (callIndex == 1)
	{
		//if the callback comme from the pRgbcolor or pRgbcolor2
		if ((pCallObject == pRgbcolor)||(pCallObject == pRgbcolor2))
		{
			RefreshSliders();
			RefreshBand();
			RefreshImage();

			if (callbackNode)
			{
				callbackNode->Callback(this,1);
			}else
				if (pParentUI_base) pParentUI_base->Callback(this,1);

			return;
		}

		//if the callback comme from the pBeforecolor
		if (pCallObject == pBeforecolor)
		{
			pBeforecolor->GetColor(&redColor,&greenColor,&blueColor);
			SetPicker(redColor, greenColor, blueColor);
			RefreshSliders();
			RefreshBand();
			RefreshImage();

			if (callbackNode)
			{
				callbackNode->Callback(this,1);
			}else
				if (pParentUI_base) pParentUI_base->Callback(this,1);


			return;
		}


		//if the callback comme from the pSHue
		if (pCallObject == pSHue)		{mode = 0;}

		//if the callback comme from the pSSaturation
		if (pCallObject == pSSaturation){mode = 1;}

		//if the callback comme from the pSLuminosity
		if (pCallObject == pSLuminosity){mode = 2;}

		//if the callback comme from the pSRed
		if (pCallObject == pSRed)		{mode = 3;}

		//if the callback comme from the pSHue
		if (pCallObject == pSGreen)		{mode = 4;}

		//if the callback comme from the pSSaturation
		if (pCallObject == pSBlue)		{mode = 5;}
		
		pAftercolor->GetColor(&redColor,&greenColor,&blueColor);
		SetPicker(redColor, greenColor, blueColor);
		
		RefreshBand();
		RefreshImage();
	}

}


void D_ColorPicker::OnMouseMove(int x, int y, int prevx, int prevy){
	
	
	pRgbcolor->OnMouseMove(x-posx,y-posy, prevx-posx, prevy-posy);
	pRgbcolor2->OnMouseMove(x-posx,y-posy, prevx-posx, prevy-posy);

	OnMouseMoveBase(x, y, prevx, prevy);

	// if the mouse is out of the menu, delete it
	if ((x < posx || x > posx+width || y < posy-height || y > posy) && !(((pRgbcolor->action)||(pRgbcolor2->action))))
	{ pViewports->deletewhendone = this;}
};

	


void D_ColorPicker::RefreshImage(){
	Texture* Image;
	
	Image = &(pRgbcolor->PreviewImage);

	int k = 0;
	float red, green, blue;
	float hue, saturation, luminosity;
	
	float invRgbcolor2Cury = float(255-pRgbcolor2->cury) / 255.0f;
	float hueInvRgbcolor2Cury = invRgbcolor2Cury*360.0f;
	int i,j;
	
	for (i=0; i<int(Image->height); ++i){
		for (j=0; j<int(Image->width); ++j){
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

			Image->imageData[k] = char(red * 255);
			k++;
			Image->imageData[k] = char(green * 255);
			k++;
			Image->imageData[k] = char(blue * 255);
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
	
}

void D_ColorPicker::RefreshBand(){
	Texture* Band;
	Band = &(pRgbcolor2->PreviewImage);
	int k = 0;
	float red, green, blue;
	float hue, saturation, luminosity;
	//float invRgbcolorCury = float(255-pRgbcolor->cury) / 255.0f;
	float pRgbcolorCurx = (float)pRgbcolor->curx;
	float pRgbcolorCury = (float)pRgbcolor->cury;
	float negCury = float(255 - pRgbcolor->cury);
	float negCurx = float(255 - pRgbcolor->curx);
	float invRgbcolorCury =  negCury / 255.0f;
	float invRgbcolorCurx = pRgbcolorCurx / 255.0f;
	float hueCurx = invRgbcolorCurx * 360.0f;
	

	for (int i=0; i<int(Band->height);++i){
		switch (mode)
		{

			//hue
			case 0:
			{
				hue = float(255-i) / 255.0f*360.0f;
				saturation = invRgbcolorCurx;
				luminosity = invRgbcolorCury;
				HSV2RGB(hue,saturation,luminosity,&red,&green,&blue);
				break;
			}

			//saturation
			case 1:
			{
				hue = hueCurx;
				saturation = float(255-i) / 255.0f;
				luminosity = invRgbcolorCury;
				HSV2RGB(hue,saturation,luminosity,&red,&green,&blue);
				break;
			}
			
			//luminosity
			case 2:
			{
				hue = hueCurx;
				saturation = invRgbcolorCury;
				luminosity = float(255-i) / 255.0f;
				HSV2RGB(hue,saturation,luminosity,&red,&green,&blue);
				break;
			}

			//red
			case 3:
			{
				red= float(i);
				green= negCurx;
				blue= pRgbcolorCury;
				break;
			}

			//green
			case 4:
			{
				red= negCurx;
				green= float(i);
				blue= pRgbcolorCury;
				break;
			}
			
			//blue
			case 5:
			{
				red = negCurx;
				green = pRgbcolorCury;
				blue = float(i);
				break;
			}

		}
		
		for (int j=0; j<int(Band->width);++j){
			Band->imageData[k] = char(red * 255);
			k++;
			Band->imageData[k] = char(green * 255);
			k++;
			Band->imageData[k] = char(blue * 255);
			k++;
		}
	}

	//horizontal bar
	k = pRgbcolor2->cury * Band->width*3;
	for (int j= 0; j<int(Band->width)*3;++j){
		Band->imageData[k] = 256 - Band->imageData[k];
		k++;
	};

	pRgbcolor2->RefreshImage();

};
void D_ColorPicker::RefreshSliders(){
	float valRed, valGreen, valBlue;
	float hue, saturation, luminosity;
	switch (mode)
	{

		//hue
		case 0:
		{
			hue = float(255-pRgbcolor2->cury) / 255.0f*360.0f;
			saturation = float(pRgbcolor->curx) / 255.0f;
			luminosity = float(255-pRgbcolor->cury) / 255.0f;
			HSV2RGB(hue,saturation,luminosity,&valRed,&valGreen,&valBlue);
			break;
		}
			//saturation
		case 1:
		{
			hue = float(pRgbcolor->curx) / 255.0f*360.0f;
			saturation = float(255-pRgbcolor2->cury) / 255.0f;
			luminosity = float(255-pRgbcolor->cury) / 255.0f;
			HSV2RGB(hue,saturation,luminosity,&valRed,&valGreen,&valBlue);
			break;
		}
		
		//luminosity
		case 2:
		{
			hue = float(pRgbcolor->curx) / 255.0f*360.0f;
			saturation = float(255-pRgbcolor->cury) / 255.0f;
			luminosity = float(255-pRgbcolor2->cury) / 255.0f;
			HSV2RGB(hue,saturation,luminosity,&valRed,&valGreen,&valBlue);
			break;
		}
		//red
		case 3:
		{
			valRed = float(255-pRgbcolor2->cury) / 255.0f;
			valGreen = float(pRgbcolor->curx) / 255.0f;
			valBlue = float(255-pRgbcolor->cury) / 255.0f;
			RGB2HSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			break;
		}
		//green
		case 4:
		{
			valRed = float(pRgbcolor->curx) / 255.0f;
			valGreen = float(255-pRgbcolor2->cury) / 255.0f;
			valBlue = float(255-pRgbcolor->cury) / 255.0f;
			RGB2HSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			break;
		}
		
		//blue
		case 5:
		{
			valRed = float(pRgbcolor->curx) / 255.0f;
			valGreen = float(255-pRgbcolor->cury) / 255.0f;
			valBlue = float(255-pRgbcolor2->cury) / 255.0f;
			RGB2HSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			break;
		}
	}
	//red->setValue(valRed);
	//green->setValue(valGreen);
	//blue->setValue(valBlue);

	pSRed->SetValue(valRed * 255.0f);
	pSGreen->SetValue(valGreen * 255.0f);
	pSBlue->SetValue(valBlue * 255.0f);
	pSHue->SetValue(hue);
	pSSaturation->SetValue(saturation*100);
	pSLuminosity->SetValue(luminosity*100);

	pAftercolor->SetColor(valRed, valGreen, valBlue);
}


void D_ColorPicker::SetPicker(float valRed,float valGreen,float valBlue){
	switch (mode)
	{

		//hue
		case 0:
		{
			float hue,saturation,luminosity;
			RGB2HSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			pRgbcolor2->cury = int(255 - hue / 360*255);
			pRgbcolor->curx = int(saturation * 255);
			pRgbcolor->cury = int(255 - luminosity * 255);
			break;
		}
			//saturation
		case 1:
		{
			float hue,saturation,luminosity;
			RGB2HSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
			pRgbcolor->curx = int(hue / 360*255);
			pRgbcolor2->cury = int(255 - saturation * 255);
			pRgbcolor->cury = int(255 - luminosity * 255);
			break;
		}
		
		//luminosity
		case 2:
		{
			float hue,saturation,luminosity;
			RGB2HSV(valRed, valGreen, valBlue, &hue, &saturation, &luminosity);
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
	
}

float D_ColorPicker::GetActiveColor(int RGB)
{
		switch (RGB)
		{
		case RED:
			return pSRed->GetValue()/255.0f;
		case GREEN:
			return pSGreen->GetValue()/255.0f;
		case BLUE:
			return pSBlue->GetValue()/255.0f;
		default:
			return 0;
		}
}


///////////////////////////////////////////////////////////////////////////


void D_ColorPicker::CalcOutput(int iOutputNumber, void* Result)
{

}

