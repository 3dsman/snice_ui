// array.cpp: Array widget.
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
// array.cpp
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

#include "../snice_UI.h"
#include "widget/array.h"



W_array::W_array(int x, int y, int w, int h, unsigned int sizeX, unsigned int sizeY, unsigned int defWidth, unsigned int defHeight, float r, float g, float b)
		:UI_widget(x, y, w, h, r, g, b)
{
	this->defWidth=defWidth;
	this->defHeight=defHeight;

	Resize(sizeX,sizeY);
		
}

W_array::~W_array(){
}


void W_array::OnClickCell(UI_base * asker, void (*function)(UI_base * asker, W_array* caller, unsigned int x, unsigned int y))
{
    onClickCell = function;
	onClickCellAsker = asker;
}

void W_array::SetWidth(int w)
{
	UI_widget::SetWidth(w);
	
	RefreshContentPos();
}

void W_array::SetHeight(int h)
{
	UI_widget::SetHeight(h);
	
	RefreshContentPos();
}

void W_array::SetContent(unsigned int x, unsigned int y, UI_base* widget, bool snapLeft, bool snapRight, bool snapTop, bool snapBottom)
{
	if ((y>ySizeArray.size())||(x>xSizeArray.size())) return;
    if (array[x][y].content)
    {
        childList.remove(array[x][y].content);
        delete(array[x][y].content);
    }
	array[x][y].content = widget;
	childList.push_front(widget);
	//childList.Add(widget);
	SetContentPos(x, y, snapLeft, snapRight, snapTop, snapBottom);
	
	//refreshContentPos(x, y);
}

UI_base* W_array::GetContent(unsigned int x, unsigned int y)
{
	return array[x][y].content;
}

void W_array::ClearContent()
{
    childList.clear();
    for (unsigned int i = 0; i < xSizeArray.size(); i++) {
        for (unsigned int j = 0; j < ySizeArray.size(); j++) {
            delete(array[i][j].content);
            array[i][j].content= 0;
        }
    }
}

void W_array::SetContentPos(unsigned int x, unsigned int y, bool snapLeft, bool snapRight, bool snapTop, bool snapBottom)
{
	if ((y>=ySizeArray.size())||(x>=xSizeArray.size())) return;
	array[x][y].snapLeft = snapLeft;
	array[x][y].snapRight = snapRight;
	array[x][y].snapTop = snapTop;
	array[x][y].snapBottom = snapBottom;
	
    RefreshContentPos(x, y);
}

void W_array::Resize(unsigned int sizeX, unsigned int sizeY)
{
    unsigned int oldSizeX = xSizeArray.size();
    unsigned int oldSizeY = ySizeArray.size();

    //clear content out of the new size
    for (unsigned int i = 0; i < sizeX; i++) {
        for (unsigned int j = sizeY; j < oldSizeY; j++) {
            childList.remove(array[i][j].content);
            delete(array[i][j].content);

        }
    }

    for (unsigned int i = sizeX; i < oldSizeX; i++) {
        for (unsigned int j = 0; j < oldSizeY; j++) {
            childList.remove(array[i][j].content);
            delete(array[i][j].content);
        }
    }
	
    //resize content array
	array.resize(sizeX);
    for(unsigned int i=0;i<sizeX;i++){ array[i].resize(sizeY);}

    //resize collumn width array
	xSizeArray.resize(sizeX);
    for(unsigned int i=oldSizeX;i<sizeX;i++){ xSizeArray[i] = defWidth;}

    //resize line height array
	ySizeArray.resize(sizeY);
    for(unsigned int i=oldSizeY;i<sizeY;i++){ ySizeArray[i] = defHeight;}

    //recalculate the new size of the widget
	unsigned int tmpPosx = 0;
	unsigned int tmpPosy = 0;
	for(unsigned int i=0;i<sizeX;i++){tmpPosx += xSizeArray[i];}
	for(unsigned int i=0;i<sizeY;i++){tmpPosy += ySizeArray[i];}
	SetSize(tmpPosx + (xSizeArray.size()-1) * marginX + 2*borderX, tmpPosy + (ySizeArray.size()-1) * marginY + 2*borderY);
}

unsigned int W_array::getSizeX()
{
    return xSizeArray.size();
}

unsigned int W_array::getSizeY()
{
    return ySizeArray.size();
}

void W_array::SetLineHeight(unsigned int y, unsigned int lineHeight)
{
	if (y>=ySizeArray.size())return;
	ySizeArray[y] = lineHeight;
	RefreshContentPos();
}

void W_array::SetcollumnWidth(unsigned int x, unsigned int colWidth)
{
	if (x>xSizeArray.size())return;
	xSizeArray[x] = colWidth;
	RefreshContentPos();
}

void W_array::SetCellColor(unsigned int x, unsigned int y, Color color)
{
    if ((x<xSizeArray.size())&&(y<ySizeArray.size()))
    {
        array[x][y].color = color;
    }
}

void W_array::Draw()
{

    glTranslated(posx,posy,0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    float tmpPosx = borderX;
    float tmpPosy = borderY;
    for (unsigned int i = 0; i < xSizeArray.size(); i++) {
        tmpPosy=borderY;
        for (unsigned int j = 0; j < ySizeArray.size(); j++) {
            glColor4f(array[i][j].color.r,array[i][j].color.g,array[i][j].color.b,array[i][j].color.a);

            glBegin(GL_QUADS);
                glVertex2d(tmpPosx, -tmpPosy);
                glVertex2d(tmpPosx, -(tmpPosy+ySizeArray[j]));
                glVertex2d(tmpPosx+xSizeArray[i], -(tmpPosy+ySizeArray[j]));
                glVertex2d(tmpPosx+xSizeArray[i], -tmpPosy);
            glEnd();

            tmpPosy+=ySizeArray[j]+marginY;
        }
        tmpPosx+=xSizeArray[i]+marginX;
    }

    glTranslated(-posx,-posy,0);

    UI_widget::Draw();
}

void W_array::SetMargin(unsigned int marginX, unsigned int marginY, unsigned int borderX, unsigned int borderY)
{
	this->marginX = marginX;
	this->marginY = marginY;
	this->borderX = borderX;
	this->borderY = borderY;}

void W_array::RefreshContentPos()
{

	unsigned int tmpPosx = 0;
	unsigned int tmpPosy = 0;
	for (unsigned int i = 0; i < xSizeArray.size(); i++) {
		tmpPosy=0;
		for (unsigned int j = 0; j < ySizeArray.size(); j++) {
			RefreshContentPos(i, j, tmpPosx, tmpPosy);
			
			tmpPosy+=ySizeArray[j];
		}
		tmpPosx+=xSizeArray[i];
	}
	SetSize(tmpPosx + (xSizeArray.size()-1) * marginX + 2*borderX, tmpPosy + (ySizeArray.size()-1) * marginY+ 2*borderY);
}

void W_array::RefreshContentPos(unsigned int x, unsigned int y)
{
	unsigned int tmpPosx = 0;
	unsigned int tmpPosy = 0;
	for(unsigned int i=0;i<x;i++){tmpPosx += xSizeArray[i];}
	for(unsigned int i=0;i<y;i++){tmpPosy += ySizeArray[i];}
	RefreshContentPos(x, y, tmpPosx, tmpPosy);
}

void W_array::RefreshContentPos(unsigned int x, unsigned int y, unsigned int cellPosx, unsigned int cellPosy)
{
	
	if ((y>ySizeArray.size())||(x>xSizeArray.size())||!(array[x][y].content)) return;
	
	unsigned int contentPosX = cellPosx + x*marginX + borderX;
	unsigned int contentPosY = cellPosy + y*marginY + borderY;
	if (array[x][y].snapRight)
	{
		if (array[x][y].snapLeft)
			array[x][y].content->SetWidth(xSizeArray[x]-marginX);
		else
			contentPosX = contentPosX + xSizeArray[x]-array[x][y].content->GetWidth();
	}else if (!(array[x][y].snapLeft))
	{
		contentPosX = contentPosX + (xSizeArray[x]-array[x][y].content->GetWidth())/2;
	}
	
	if (array[x][y].snapBottom)
	{
		if (array[x][y].snapTop)
			array[x][y].content->SetHeight(ySizeArray[y]-marginY);
		else
			contentPosY = contentPosY + ySizeArray[y]-array[x][y].content->GetHeight();
	}else if (!(array[x][y].snapTop))
	{
		contentPosY = contentPosY + (ySizeArray[y]-array[x][y].content->GetHeight())/2;
	}
	array[x][y].content->SetPos(contentPosX, -contentPosY);
}



UI_base* W_array::OnLButtonUp(int x, int y)
{
    UI_widget::OnLButtonUp(x, y);
    if(!pInterceptChild)
	{
		unsigned int cellX = 0;
		unsigned int cellY = 0;
		int tmpPos = borderX;
		while(cellX<xSizeArray.size())
		{
			if ((tmpPos<x)&&(tmpPos+xSizeArray[cellX]>x))
			{
				tmpPos = borderY;
				while(cellY<ySizeArray.size())
				{
					if ((tmpPos<-y)&&(tmpPos+ySizeArray[cellY]>-y))
					{
						//std::cout<<x<<" "<<y<<"  "<<cellX<<" "<<cellY<<std::endl;
						if(onClickCell) onClickCell(onClickCellAsker, this, cellX, cellY);
						break;
					}
					tmpPos += ySizeArray[cellY]+marginY;
					cellY++;
				}
				break;
			}
			tmpPos += xSizeArray[cellX]+marginX;
			cellX++;
		}
	}
	pInterceptChild = 0;
    return 0;
}


//void W_array::PanelOnLButtonDown(int x, int y, int px, int py){
/*
	int pickedIndex;
	//pickedIndex = (x/colSize)*13 + ((-y-6)/13);
	pickedIndex = (x/colSize)*((surfacey-6)/13) + ((-y-6)/13);
	fileList.ToFirst();
	if ((!(shift))  || (oneFile))
	do{
		((PathElement*)(fileList.GetCurrentObjectPointer()))->Selected(false);

	}while (fileList.ToNext());

	//pickedIndex = (x/colSize)*13 + ((-y-6)/13);

	fileList.ToFirst();
	while (pickedIndex>0)
	{
		fileList.ToNext();
		pickedIndex -=1;

	};

	if (((PathElement*)(fileList.GetCurrentObjectPointer()))->IsDirectory())
	{
		char dirName[256];
		(((PathElement*)(fileList.GetCurrentObjectPointer()))->GetName(dirName));

		if (strcmp(dirName,"..\\")&&strcmp(dirName,"../"))
		{
			((PathElement*)(fileList.GetCurrentObjectPointer()))->GetFullName(dirName);
			SetCurrentDirectory(dirName);
			//listDirectory();
		}
		else
		{
			//directory->getParentDir(dirName);
			directory->GetDirectory(dirName);
			//strcpy(dirName,directory->getPath());
			SetCurrentDirectory(dirName);
			//listDirectory();
			//listDirectory(dirName, this->ext);
		}
		//if (pParentUI_base)
		//		pParentUI_base->Callback(this,1);
	}
	else
	{
		((PathElement*)(fileList.GetCurrentObjectPointer()))->Selected(true);
		//GenDisplayList();
		//if (pParentUI_base)
		//	pParentUI_base->Callback(this,1);
	}
*/
//};
/*

void W_array::PanelOnLButtonUp(int x, int y)
{};
	
void W_array::PanelOnMouseMove(int x, int y, int prevx, int prevy){};

void W_array::PanelOnKeyPressed(int key, int action){
	if ((key == SNICEUI_KEY_LEFT_SHIFT)||(key == SNICEUI_KEY_RIGHT_SHIFT))
		shift = (action == SNICEUI_PRESS);
};
*/
/*
void W_array::GetSelectedList(List * filenames){

};*/
