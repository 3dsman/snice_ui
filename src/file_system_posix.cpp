// fileSystemPosix.cpp: Function for file managment (input/output, browse).
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
// fileSystemWin.cpp
// This file contains function for file managment (input/output, browse).
// File created by Tricoire Sebastien
// Date of creation : 2004 25 10
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

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <cstring>

#include "mylist.h"
#include "file_system.h"

using namespace std;
/*
bool isDirectory(string name){
	return name.find('/');//(name[strlen(name)-1] == '/');
};*/

bool directoryExist(string name){ return true;};
bool fileExist(string name){return true;};

void rootsNames(std::list<string> rootsList){
	/*char* plinuxRoot = new char[2];  // Allocate memory for the array
  	strcpy(plinuxRoot, "/");
	rootsList->Add(plinuxRoot);*/
	rootsList.push_back("/");
};

PathElement::PathElement(const string name){

	Path = name;
	select = false;

};

PathElement::~PathElement(){};

string PathElement::GetName(){
	return Path.substr(Path.find_last_of('/', Path.length()-2)+1);
};

string PathElement::GetFullName(){
	return Path;
}

string PathElement::GetDirectory()
{
		return Path.substr(0, Path.find_last_of('/'));
}

string PathElement::GetClipingName(unsigned int size)
{
	// Get the cliping name and verify if it is too long
	// if it is copy the ".." char at the size position

	string name = GetName();
	if (name.size() > size)
	{
		name = name.substr(0, size-2);
		return name+"..";
	}
	return name;
};

bool PathElement::IsSelected()
{
	return select;
};

void PathElement::Selected(bool selected)
{
	select = selected;
};

bool PathElement::IsDirectory()
{	
	return Path.find('/');
};


//**********************************************************
//********************    FILE INFO    *********************
//**********************************************************

FileInfo::FileInfo(const string fileName)
		 :PathElement( fileName)
{
	file = true;
};

FileInfo::~FileInfo(){};

void FileInfo::GetExtension(const string fileName, char * ext){};

bool FileInfo::FileExist(const string name){return true;};

//**********************************************************
//*********************    DIR INFO    *********************
//**********************************************************

DirInfo::DirInfo(const string dirName)
		:PathElement(dirName)
{
	file = false;
};

DirInfo::~DirInfo(){};

std::list<PathElement> DirInfo::BrowseDirectory(const char * exts)
{   
	std::list<PathElement> fileList;
	struct dirent **namelist;
	struct stat infos;
	string catNamePath = Path;

    int n = scandir(catNamePath.c_str(), &namelist, 0, alphasort);
    if (n < 0)
        perror("scandir error");
    else {
    	int file = 0;
        while(file < n) {
			catNamePath = Path + namelist[file]->d_name;
        	//strcpy(catNamePath,Path);
        	//strcat(catNamePath,namelist[file]->d_name);
        	if ( 0 > lstat(catNamePath.c_str(), &infos) )
        	{
            	printf("%s %s\n", "file stat problem : " , namelist[file]->d_name);
        	}else
	            if((S_ISDIR(infos.st_mode))&&(strcmp(namelist[file]->d_name,".")))
	            {
					catNamePath = Path + namelist[file]->d_name + "/";
	            	//strcpy(catNamePath,Path);
					//strcat(catNamePath,namelist[file]->d_name);
					//strcat(catNamePath,"/");
					DirInfo* dir = new DirInfo(catNamePath);
	            	fileList.push_back((PathElement)*dir);
	            	//printf("%s %s\n", "repertoire: " , catNamePath.c_str());
	            }
	        file++;
        }
        file = 0;
        while(file < n) {
			catNamePath = Path + namelist[file]->d_name;
        	//strcpy(catNamePath,Path);
        	//strcat(catNamePath,namelist[file]->d_name);
        	if ( 0 > lstat(catNamePath.c_str(), &infos) )
        	{
            	printf("%s %s\n", "file stat problem : " , namelist[file]->d_name);
        	}else
        	if(S_ISREG(infos.st_mode)){
	        		
	        	// List Files
				char ext[EXTMAXLENGTH];
				char extsc[EXTMAXLENGTH];
				
				strcpy(extsc,exts);
	
				char * curPos= extsc;
				char * separator;
				if(strlen( extsc))
				do{
					// Find the next "|" character in the string
					separator = strchr(curPos,'|');
					
					// if there is one
					if (separator)
					{
						// copy to and add a null char at the end
						strncpy(ext,curPos,separator - curPos);
						ext[separator - curPos] = 0;
	
						//change the current position
						curPos = separator + 1;
					}else
					{
						//else just copy the string
						strcpy( ext, curPos);
					}
					
					if((strstr(namelist[file]->d_name,ext))||!(strcmp(ext,".*")))
					{
						catNamePath = Path + namelist[file]->d_name;
						FileInfo* file = new FileInfo(catNamePath);
						file->size = infos.st_size;
						file->cDate = infos.st_ctime;
						file->wDate = infos.st_mtime;
						file->aDate = infos.st_atime;
						fileList.push_back(*file);
						separator = 0;
					}
					
					
					
				}while( separator);
        	}
	        file++;
        }
            /*
            if (S_ISREG(infos.st_mode))printf("%s %s\n", "regular: " , namelist[n]->d_name);
			if (S_ISDIR(infos.st_mode))printf("%s %s\n", "dir: " , namelist[n]->d_name);
			if (S_ISCHR(infos.st_mode))printf("%s %s\n", "chardev: " , namelist[n]->d_name);
            if (S_ISBLK(infos.st_mode))printf("%s %s\n", "block: " , namelist[n]->d_name);
			if (S_ISFIFO(infos.st_mode))printf("%s %s\n", "fifo: " , namelist[n]->d_name);
			if (S_ISLNK(infos.st_mode))printf("%s %s\n", "link: " , namelist[n]->d_name);
			if (S_ISSOCK(infos.st_mode))printf("%s %s\n", "sock: " , namelist[n]->d_name);
			*/
		file = n;
        while(file--) {
       		free(namelist[file]);
        }
        
        free(namelist);
    }
	return fileList;
};

