#pragma once

#include <fstream>
#include <BuildManager.h>

struct ColHeader
{
	char validator[3];
	char version;
	unsigned int size;
	char modelName[22];
	short modelid;
};

struct ColItems
{
	uint16_t numSpheres;
	uint16_t numBoxes;
	uint16_t numFaces;
	uint8_t numWheels;
	uint8_t padding;
	uint32_t flags;
	uint32_t offSpheres;
	uint32_t offBoxes;
	uint32_t offSuspensionLines;
	uint32_t offVertices;
	uint32_t offFaces;
	uint32_t offTrianglePlanes;

	uint32_t numShadow;
	uint32_t offShadowVert;
	uint32_t offShadowFaces;
};

class ColFile
{
public:
	ColFile(std::ifstream *file);
	~ColFile();
	
	bool Load(BuildManager::ColModel *output);
	
	std::ifstream *handle = NULL;
};
