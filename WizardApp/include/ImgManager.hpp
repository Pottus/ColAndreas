#pragma once

#include <fstream>
#include <vector>
#include <cstdint>

struct ImgHeader
{
	char validator[4];
	uint32_t entries;
};

struct ImgEntry
{
	uint32_t offset;
	uint16_t streamingSize;
	uint16_t size;
	char name[24];
};

class ImgFile
{
public:
	ImgFile(std::string path);
	~ImgFile();
	
	bool Load();
		
	std::ifstream *handle = NULL;
	ImgHeader header;
	std::vector<ImgEntry> IPL;
	std::vector<ImgEntry> COL;
};
