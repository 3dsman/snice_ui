// snice.h: Main file for the Snice program.
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
// snice.h
// This file is the main file for the Snice program
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

#ifndef _SNICE_SNICE_H_
#define _SNICE_SNICE_H_

#include <GLFW/glfw3.h>

/*
class UI_base;
class UI_window;
class Node;
class curve;
class N_Container;
class UI_widget;
//class ViewportsArray;
class Viewport;
class Prefs;
*/
// General variables
/*
extern bool Cutting; // ????

extern int iPrevMousePosx; // ????
extern int iPrevMousePosy; // ????

extern int iMousePosx; // ????
extern int iMousePosy; // ????

extern int WindowSizex; // ????
extern int WindowSizey; // ????

extern float interceptx;
extern float intercepty;
extern float zoom;
*/
//extern Prefs* pPrefs;
/*
extern N_Container* pRootContainer;
extern N_Container* pCurContainer;
*/
//extern Viewport* pViewport;
/*
extern NodalViewport* pNodalView;

extern UI_base* pMouseMoveIntercept;
extern UI_base* pLButtonDownIntercept;
extern UI_base* pLButtonUpIntercept;
extern UI_base* pKeyPressedIntercept;
extern UI_base* pCharPressedIntercept;
*/
/*
extern bool active;		// Window Active Flag Set To TRUE By Default
extern bool fullscreen;	// Fullscreen Flag Set To Not Fullscreen Mode By Default
extern int running;	// Is the application running

extern Texture textures[20];	// Storage For Textures
extern GLuint base;				// Base Display List For The Font
extern bool keys[320];			// Array Used For The Keyboard Routine
*/
//extern double MinimizeSpeed;	// Delay for the node to minimize

// General Functions

bool DrawGLScene();
void create_interface();

void ProcessKey(GLFWwindow* wind, int key, int scancode, int action, int mods);
void ProcessChar(GLFWwindow* wind, int character, int action);
void ProcessReshape(GLFWwindow* wind, int width, int height);
void ProcessMouseButton(GLFWwindow* wind, int button, int action);
void ProcessMousePos(GLFWwindow* wind,  double x, double y );

#endif // _SNICE_SNICE_H_

// end of snice.h
