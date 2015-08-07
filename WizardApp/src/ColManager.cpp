#include <cstring>

#include <ColManager.hpp>

ColFile::ColFile(std::ifstream *file) : handle(file)
{ }

ColFile::~ColFile()
{ }

bool ColFile::Load(BuildManager::ColModel *output)
{
	if(!handle) return false;
	
	std::streamoff beginPos = handle->tellg();
	
	output->num_boxes = 0;
	output->num_faces = 0;
	output->num_spheres = 0;
	
	ColHeader fileHeader;
	handle->read((char*) &fileHeader, sizeof(fileHeader));
	
	if(handle->gcount() == sizeof(fileHeader) && !strncmp(fileHeader.validator, "COL", 3))
	{
		output->name = std::string(fileHeader.modelName);
		output->modelid = fileHeader.modelid;
		
		// Skip bounding objects
		handle->seekg(40, std::ios::cur);
		
		if(fileHeader.version == 'L') // Version 1
		{
			uint32_t itemCount = 0;
			
			// Spheres	
			handle->read((char*) &itemCount, sizeof(itemCount));
			if(handle->gcount() != sizeof(itemCount)) return false;
			
			if(itemCount)
			{
				output->spheres = new BuildManager::ColSphere[itemCount];
				output->num_spheres = itemCount;
				
				for(int i = 0; i < itemCount; ++i)
				{
					handle->read((char*) &(output->spheres[i].radius), sizeof(float));
					handle->read((char*) &(output->spheres[i].center), sizeof(BuildManager::Vertex));
					handle->seekg(4, std::ios::cur); // Skip surface data
				}
			}
			else output->spheres = NULL;
			
			handle->seekg(4, std::ios::cur); // Skip unknown data
			
			// Boxes	
			handle->read((char*) &itemCount, sizeof(itemCount));
			if(handle->gcount() != sizeof(itemCount)) return false;
			
			if(itemCount)
			{
				output->boxes = new BuildManager::ColBox[itemCount];
				output->num_boxes = itemCount;
				
				for(int i = 0; i < itemCount; ++i)
				{
					handle->read((char*) (output->boxes + i), sizeof(BuildManager::ColBox));
					handle->seekg(4, std::ios::cur); // Skip surface data
				}
			}
			else output->boxes = NULL;
			
			// Vertices	
			handle->read((char*) &itemCount, sizeof(itemCount));
			if(handle->gcount() != sizeof(itemCount)) return false;
			
			if(itemCount)
			{
				BuildManager::Vertex *vertices = new BuildManager::Vertex[itemCount];
				handle->read((char*) vertices, sizeof(BuildManager::Vertex) * itemCount);
				
				// Faces	
				handle->read((char*) &itemCount, sizeof(itemCount));
				if(handle->gcount() != sizeof(itemCount)) 
				{
					delete [] vertices;
					return false;
				}
				
				if(itemCount)
				{
					output->faces = new BuildManager::ColFace[itemCount];
					output->num_faces = itemCount;
					
					for(int i = 0; i < itemCount; ++i)
					{
						uint32_t indexes[3];		
						handle->read((char*) &indexes, sizeof(indexes));
						handle->seekg(4, std::ios::cur); // Skip surface data
						
						output->faces[i].a = &(vertices[indexes[0]]);
						output->faces[i].b = &(vertices[indexes[1]]);
						output->faces[i].c = &(vertices[indexes[2]]);
					}
				}
				else 
				{
					delete [] vertices;
					output->faces = NULL;
				}
			}
			else output->faces = NULL;
			
			// Prepare for reading the next collision
			handle->seekg(beginPos + 8 + fileHeader.size);
			
			return true;
		}
		else
		{
			ColItems fileItems;
			handle->read((char*) &fileItems, sizeof(fileItems));
			
			if(handle->gcount() == sizeof(fileItems))
			{
				output->num_boxes = fileItems.numBoxes;
				output->num_spheres = fileItems.numSpheres;
				output->num_faces = fileItems.numFaces;
				
				if(fileItems.numBoxes)
				{
					output->boxes = new BuildManager::ColBox[fileItems.numBoxes];	
					handle->seekg(beginPos + 4 + fileItems.offBoxes);
					
					for(int i = 0; i < fileItems.numBoxes; ++i)
					{
						handle->read((char*) (output->boxes + i), sizeof(BuildManager::ColBox));
						handle->seekg(4, std::ios::cur); // Skip surface data
					}
				}
				else output->boxes = NULL;
				
				if(fileItems.numSpheres)
				{
					output->spheres = new BuildManager::ColSphere[fileItems.numSpheres];	
					handle->seekg(beginPos + 4 + fileItems.offSpheres);
					
					for(int i = 0; i < fileItems.numSpheres; ++i)
					{
						handle->read((char*) (output->spheres + i), sizeof(BuildManager::ColSphere));
						handle->seekg(4, std::ios::cur); // Skip surface data
					}
				}
				else output->spheres = NULL;
				
				if(fileItems.numFaces)
				{
					uint16_t topIndex = 0;
					uint16_t (*faceIndexes)[3] = new uint16_t[fileItems.numFaces][3];
					
					output->faces = new BuildManager::ColFace[fileItems.numFaces];					
					handle->seekg(beginPos + 4 + fileItems.offFaces);
					
					for(int i = 0; i < fileItems.numFaces; ++i)
					{
						handle->read((char*) (faceIndexes + i), sizeof(uint16_t) * 3);
						handle->seekg(2, std::ios::cur); // Skip surface data
						
						if(faceIndexes[i][0] > topIndex) topIndex = faceIndexes[i][0];
						if(faceIndexes[i][1] > topIndex) topIndex = faceIndexes[i][1];
						if(faceIndexes[i][2] > topIndex) topIndex = faceIndexes[i][2];
					}
					
					
					BuildManager::Vertex *vertices = new BuildManager::Vertex[topIndex + 1];
					handle->seekg(beginPos + 4 + fileItems.offVertices);
					
					for(int i = 0; i < topIndex + 1; ++i)
					{
						int16_t vertexData[3];	
						handle->read((char*) &vertexData, sizeof(vertexData));
						
						vertices[i].x = float(vertexData[0]) / 128.0f;
						vertices[i].y = float(vertexData[1]) / 128.0f;
						vertices[i].z = float(vertexData[2]) / 128.0f;
					}
					
					
					for(int i = 0; i < fileItems.numFaces; ++i)
					{
						output->faces[i].a = &(vertices[faceIndexes[i][0]]);
						output->faces[i].b = &(vertices[faceIndexes[i][1]]);
						output->faces[i].c = &(vertices[faceIndexes[i][2]]);
					}
					
					delete [] faceIndexes;
				}
				else output->faces = NULL;
				
				// Prepare for reading the next collision
				handle->seekg(beginPos + 8 + fileHeader.size);
				
				return true;
			}
		}
	}
	
	return false;
}
