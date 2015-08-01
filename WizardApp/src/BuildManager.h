/*
* This file is part of ColAndreas.
* Copyright(C) <2013>  <christopher michael james>
* computer_customs@hotmail.com
*
* ColAndreas is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ColAndreas is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Special thanks:
*
* [uL]Slice, Writing the original collision reader function
*/
using namespace System::Threading;
#include <Windows.h>
#include <array>
#include <stdio.h>
#include <tchar.h>
#include <fstream> 
#include <iostream>
#include <stdint.h>
#include <algorithm>    // std::find
#include <string>
#include <vector>
//#include"dirent.h"
#include <assert.h>
#include <array>

#include <vcclr.h>

using namespace System;
#define GetBytes(Source, Destination, Index, BytesToCopy) memcpy(&Destination, (Source + Index), BytesToCopy), Index+=BytesToCopy


public class BuildManager
{
private:

	typedef struct
	{
		float x;
		float y;
		float z;
	} Vertex;

	typedef struct
	{
		BuildManager::Vertex center;
		float radius;
	} ColSphere;

	typedef struct
	{
		BuildManager::Vertex   min;
		BuildManager::Vertex   max;
	} ColBox;

	typedef struct
	{
		BuildManager::Vertex*  a;
		BuildManager::Vertex*  b;
		BuildManager::Vertex*  c;
	} ColFace;

	typedef struct
	{
		std::string name;
		uint16_t modelid;

		uint32_t num_spheres;
		uint32_t num_boxes;
		uint32_t num_faces;

		BuildManager::ColSphere* spheres;
		BuildManager::ColBox* boxes;
		BuildManager::ColFace* faces;

	} ColModel;

	typedef struct
	{
		float x;
		float y;
		float z;
		float w;
	} IPLRot;

	typedef struct
	{
		uint16_t modelid;

		BuildManager::Vertex Position;
		BuildManager::IPLRot Rotation;

		std::string Modelname;
	} IPLObject;

	typedef struct
	{
		uint16_t modelid;
		std::string ModelName;
		float DrawDist;
	} Modelid_Modelname_Struct;


	uint8_t ERROR_CODE;//uint8_t
	std::string GTAInstallDirectory;
	std::string OutfileDirectroy;

	std::vector<BuildManager::IPLObject> IPLArray;
	std::vector<BuildManager::ColModel> COLArray;
	std::vector<BuildManager::Modelid_Modelname_Struct> Modelid_Modelname_Vector;

	//These index's are not nescisary, vector has functionality for this already.
	uint32_t Modelid_Modelname_VectorIndex;
	uint32_t IPLArrayVectorIndex;
	uint16_t COLArrayVectorIndex;

	std::tr1::array<std::string, 3> ImageFileNames;
	std::tr1::array<std::string, 2> CollisionFileNames;
	std::tr1::array<std::string, 31> ItemPlacementFileNames;
	std::tr1::array<std::string, 54> ItemDefinitionFileNames;

	gcroot<System::ComponentModel::BackgroundWorker ^>  backgroundWorkerRefrence;

	bool ReadItemDefinitionFile(const char fname[]);
	bool ReadItemPlacmentData(const char fname[]);
	void ReadBinaryItemPlacmentData(char* RawIPLData);
	BuildManager::ColModel ReadColModel(char* data);


	bool ReadColFile(const char fname[]);
	void InitDirectoryNames();

	bool UsingSAMPObjects;
	bool UsingCustomObjects;
public:


	BuildManager(std::string _GTAInstallDirectory, std::string _OutfileDirectroy, System::ComponentModel::BackgroundWorker ^ _backgroundWorkerPointer, bool _UsingSAMPObjects, bool _UsingCustomObjects);


	bool ExtractImageFiles();
	bool ExtractCollisionFiles();
	bool ExtractItemPlacementFiles();
	bool ExtractItemDefinitionFiles();
	void PrepareDatabaseStructures();

	bool WriteBinaryFile(const char fname[]);


};