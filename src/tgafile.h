// tgafile.h
// This file is for TGA image format related functions.
//
// File created by Lionel Allorge
// Date of creation : 2004 06 02
// Date of modification : 

// Other copyrights :
// part copyright 2002-2003 Wybren van Keulen
// www.funnyfarm.tv
// I used the OpenGL framework by Jeff Molofee 2000
// his site rocks, visit it at nehe.gamedev.net
// updated by tricoire sebastien
// 3dsman@free.fr


/* ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version. The Blender
 * Foundation also sells licenses for use in proprietary software under
 * the Blender License.  See http://www.blender.org/BL/ for information
 * about this.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2002-2003 by Funny Farm.
 * www.funnyfarm.tv
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#ifndef _SNICE_TGAFILE_H_
#define _SNICE_TGAFILE_H_

#include "stdio.h"
//#include "include/glfw.h"
typedef unsigned char GLubyte;
typedef unsigned int GLuint;


typedef struct
{
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
} Texture;

void gentex(Texture tex);

typedef struct
{
	GLubyte Header[12];									// TGA File Header
} TGAHeader;

typedef struct
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;	
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} TGA;

static TGAHeader tgaheader;									// TGA header
static TGA tga;												// TGA image data

static GLubyte uTGAcompare[12] = {0,0,2, 0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
static GLubyte cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};	// Compressed TGA Header

bool LoadTGA(Texture * texture, char * filename);		// Load a TGA file
bool LoadUncompressedTGA(Texture * texture, char * filename, FILE * fTGA);	// Load an Uncompressed file
bool LoadCompressedTGA(Texture * texture, char * filename, FILE * fTGA);		// Load a Compressed file

#endif // _SNICE_TGAFILE_H_

// End of tgafile.h
