
// image.h
// This file is for image load.
//
// File created by tricoire sebastien
// Date of creation : 2015 03 31
// Date of modification :


/* ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
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
 * ***** END GPL LICENSE BLOCK *****
 */

#ifndef _SNICE_IMAGE_H_
#define _SNICE_IMAGE_H_

//#include <fstream>
#include <iostream>
//#include <sstream>
#include <string.h>
#include "stdio.h"

using namespace std;

class UI_image
{
private:
	string filename;

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

    //void gentex(Texture tex);

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

    Texture tex;

public:
    UI_image();

	UI_image(string filename);

	virtual ~UI_image();
    bool LoadImage(string filename);		// Load a TGA file

    TGAHeader tgaheader;									// TGA header
    TGA tga;												// TGA image data

    GLubyte uTGAcompare[12];	// Uncompressed TGA Header
    GLubyte cTGAcompare[12];	// Compressed TGA Header

    int MessageBox(int empty, string message, string title, int flag);
    void gentex();
    bool LoadTGA(Texture * texture, string filename);		// Load a TGA file
    bool LoadUncompressedTGA(Texture * texture, FILE * fTGA);	// Load an Uncompressed file
    bool LoadCompressedTGA(Texture * texture, FILE * fTGA);		// Load a Compressed file
    GLuint	GetWidth();
    GLuint	GetHeight();
    GLubyte * GetData();
    bool SetWidth(GLuint width);
    bool SetHeight(GLuint height);
    bool SetBpp(GLuint bpp);
    bool SetData(GLubyte * data);

    bool BindTex();

};




#endif // _SNICE_IMAGE_H_

// End of image.h
