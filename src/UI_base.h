// UI_base.h: base class for all visible objects (dialogs, widget, nodes).
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
// UI_base.h
// This file is the Colorize node file
// File created by Tricoire Sebastien
// Date of creation : 2004 12 04
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

#ifndef _SNICE_UI_BASE_H_
#define _SNICE_UI_BASE_H_

////////////////////////////////////////
// class UI_base.
// Class for callback and position
////////////////////////////////////////

	/**	\brief Class for callback and position

		UI_base is the base class for all visible objects (dialogs, widget, nodes).
	*/
#include "mylist.h"
//#include "tgafile.h"
#include "UI_image.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

typedef unsigned char GLubyte;
typedef unsigned int GLuint;

using namespace std;

struct Textures{
   UI_image slider;
   UI_image button;
   UI_image buttonPress;
   UI_image specular;
   UI_image progress;
   UI_image shadow;
   UI_image cursor;
};

struct Font{
   UI_image texture;
   GLuint fontList;
   unsigned char charWidth;
};

class UI_widget;

class UI_base
{
private:

protected:
	int posx, posy; /**<		\brief Object's position */

	int parentx, parenty; /**<	\brief Object's parent's position */

	int width, height; /**<		\brief Width & height of the object */
	float r,g,b; /**<			\brief Color of the object */
	bool visible; /**<			\brief true if the object is drawn */

	UI_base* pParentUI_base; /**< \brief Pointer to the parent object */
	UI_base* pInterceptChild; /**< \brief Pointer to the child witch intercept inputs */
	string refName;		/**< \brief Ref name of the object
	the refName of an object is the one we use for save or for, later, call it in script
	*/
	//char refName[256];

    static struct Textures textures; /**< \brief creation of the static structure where textures are stored */
    static struct Font font; /**< \brief creation of the static structure where font is stored */

	List childList; /**< \brief List of childs*/

	void (*onResize)(UI_base * asker, UI_base* caller, int w, int h) = NULL; /**<		\brief resize callback function */
	UI_base * onResizeAsker = NULL;
	void (*onMove)(UI_base * asker, UI_base* caller, int x, int y) = NULL; /**<		\brief move callback function */
	UI_base * onMoveAsker = NULL;
	/**	\brief to check ant treat autokill on the child.*/
	void Autokill(UI_base * child);

public:
	bool killMe;

	/**
		 \param x x position
		 \param y y position
		 \param w width
		 \param h height
		 \param red red color as float [0;1]
		 \param green green color as float [0;1]
		 \param blue blue color as float [0;1]
	*/
	UI_base(int x, int y, int w, int h, float red = 0.3f, float green = 0.3f, float blue = 0.3f);

	virtual ~UI_base();

	/** \brief To set the width of the object.*/
	virtual void SetWidth(int w);

	/**	\brief To set the height of the object.*/
	virtual void SetHeight(int w);

	/**	\brief To set the pos x of the object.*/
	virtual void SetPosX(int x);

	/**	\brief To set the pos y of the object.*/
	virtual void SetPosY(int y);

	/**	\brief To set the pos of the object.*/
	virtual void SetPos(int x, int y);

	/**	\brief To get the pos of the object.*/
	virtual void GetPos(int *x, int *y);

	/**	\brief To set the parentPos of the object.*/
	virtual void SetParentPos(int x, int y);

	/**	\brief To set the color of the object.*/
	virtual void SetColor(float red, float green, float blue);

	/**	\brief To get the refName of the object.*/
	virtual void GetRefName(string name);

	/**	\brief To set the refName of the object.*/
	virtual void SetRefName(string name);

	/**	\brief to add a child to the childlist.*/
	virtual void AddChild(UI_base * child);

	/**	\brief to supress a child to the childlist.*/
	virtual void SupChild(UI_base * child);

	/**	\brief To draw the object.*/
	virtual void Draw();

	/**	\brief To set the visibe attribute of the object.*/
	virtual void SetVisible(bool v);

	/**	\brief This function return true if the (x,y) coordinates are in the object.*/
	virtual bool Hittest(int x, int y);

	/**	\brief Function called when a leftButtonDown event occur on this object.*/
	virtual UI_base* OnLButtonDown(int x, int y);

	/**	\brief Function called when a rightButtonDown event occur on this object.*/
	virtual UI_base* OnRButtonDown(int x, int y);

	/**	\brief Function called when a leftButtonUp event occur on this object.*/
	virtual UI_base* OnLButtonUp(int x, int y);

	/**	\brief Function called when a rightButtonUp event occur on this object.*/
	virtual UI_base* OnRButtonUp(int x, int y);

	/**	\brief Function called when a mouseMove event occur on this object.*/
	virtual UI_base* OnMouseMove(int x, int y, int prevx, int prevy);

	/**	\brief Function called when a keyPressed event occur on this object.*/
	virtual UI_base* OnKeyPressed(int key);

	/**	\brief Function called when a charPressed event occur on this object.*/
	virtual UI_base* OnCharPressed(int character);

	/**	\brief Function called when the object intercept a buttonDown event.*/
//	virtual void OnLButtonDownIntercept(int x, int y);

	/**	\brief Function called when the object intercept a buttonUp event.*/
//	virtual void OnLButtonUpIntercept(int x, int y);

	/**	\brief Function called when the object intercept a mouseMove event.*/
//	virtual void OnMouseMoveIntercept(int x, int y, int prevx, int prevy);

	/**	\brief Function called when the object intercept a keyPressed event.*/
//	virtual void OnKeyPressedIntercept(int key);

	/**	\brief Function called when the object intercept a charPressed event.*/
//	virtual void OnCharPressedIntercept(int character);

	/**	\brief Set the parent object (the node or the dialog for a widget for exemple).*/
	virtual void SetParentUIbase(UI_base * pUI_base);

	/**	\brief This function return the matrix that transform screen coordinates into object coordinates.*/
	virtual bool GetScreenToLocalMatrix(UI_base * object, float *x, float *y, float *zoom);


	/**	\brief This function is called by a child of the object for callback.*/
//	virtual void Callback(UI_base * pCallObject, unsigned char callIndex ) = 0;


	/**	\brief to set value from text (ex: from commandline).*/
	virtual void Set(char* order);


	/**	\brief to set OnResize callback function.*/
	void OnResize(UI_base * asker, void (*function)(UI_base * asker, UI_base* caller, int w, int h));

    /**	\brief to set OnMove callback function.*/
	void OnMove(UI_base * asker, void (*function)(UI_base * asker, UI_base* caller, int x, int y));


	/**< \brief set the texture "texture" with the file "path" */
	static bool SetTexture(UI_image *texture, string path);

	/**< \brief set the font with the file "path" */
    static bool SetFont(string path, int charWidth);

	/** \brief static function to init textures */
	static bool InitTextures();

	/** \brief static function to destroy textures */
	static bool DestroyTextures();

};

#endif //_SNICE_UI_BASE_H_

// End of file UI_base.h
