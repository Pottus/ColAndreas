#include "ColAndreasDatabaseReader.h"

CollisionModelstructure* CollisionModels;
ItemPlacementstructure* ModelPlacements;

uint16_t ModelCount = 0;
uint32_t IPLCount = 0;
uint16_t ModelRef[20000];

void DeleteCollisionData()
{

	delete CollisionModels;
	delete ModelPlacements;
}


bool ReadColandreasDatabaseFile(std::string FileLocation)
{
	bool returnValue = false;

	ifstream ColAndreasBinaryfile;

	ColAndreasBinaryfile.open(FileLocation, ios::in | ios::binary);

	if (ColAndreasBinaryfile.is_open()) {
		ColAndreasBinaryfile.seekg(0, ColAndreasBinaryfile.end);
		int length = static_cast<int>(ColAndreasBinaryfile.tellg());

		ColAndreasBinaryfile.seekg(0, ColAndreasBinaryfile.beg);

		char * buffer = new char[length];

		ColAndreasBinaryfile.read(buffer, length);

		uint32_t FileIndex = 0;

		char FileExtension[5];
		GetBytes(buffer, FileExtension, FileIndex, 5);
		
		//If is a ColAndreas binary file.
		if (strcmp(FileExtension, "cadf") == 0)
		{
			GetBytes(buffer, ModelCount, FileIndex, 2);
			GetBytes(buffer, IPLCount, FileIndex, 4);

			if (ModelCount > 0) {
				CollisionModels = new CollisionModelstructure[ModelCount];

				for (uint16_t i = 0; i < ModelCount; i++) {
					GetBytes(buffer, CollisionModels[i].Modelid, FileIndex, 2);
					GetBytes(buffer, CollisionModels[i].SphereCount, FileIndex, 2);
					GetBytes(buffer, CollisionModels[i].BoxCount, FileIndex, 2);
					GetBytes(buffer, CollisionModels[i].FaceCount, FileIndex, 2);

					if (CollisionModels[i].SphereCount > 0) {
						CollisionModels[i].SphereData = new structSphereData[CollisionModels[i].SphereCount];

						for (uint16_t j = 0; j < CollisionModels[i].SphereCount; j++) {
							GetBytes(buffer, CollisionModels[i].SphereData[j].Offset.x, FileIndex, 4);
							GetBytes(buffer, CollisionModels[i].SphereData[j].Offset.y, FileIndex, 4);
							GetBytes(buffer, CollisionModels[i].SphereData[j].Offset.z, FileIndex, 4);

							GetBytes(buffer, CollisionModels[i].SphereData[j].Radius, FileIndex, 4);
						}
					}

					if (CollisionModels[i].BoxCount > 0) {
						CollisionModels[i].BoxData = new structBoxData[CollisionModels[i].BoxCount];

						for (uint16_t j = 0; j < CollisionModels[i].BoxCount; j++) {
							GetBytes(buffer, CollisionModels[i].BoxData[j], FileIndex, 24);
						}
					}

					if (CollisionModels[i].FaceCount > 0)
					{

						CollisionModels[i].FacesData = new structFacesData[CollisionModels[i].FaceCount];

						for (uint16_t j = 0; j < CollisionModels[i].FaceCount; j++) {
							GetBytes(buffer, CollisionModels[i].FacesData[j], FileIndex, 36);
						}
					}
				}
			}

			FileIndex = FileIndex + 8;


			if (IPLCount > 0) {
				ModelPlacements = new ItemPlacementstructure[IPLCount];

				for (uint32_t i = 0; i < IPLCount; i++) {
					GetBytes(buffer, ModelPlacements[i].Modelid, FileIndex, 2);

					GetBytes(buffer, ModelPlacements[i].Position.x, FileIndex, 4);
					GetBytes(buffer, ModelPlacements[i].Position.y, FileIndex, 4);
					GetBytes(buffer, ModelPlacements[i].Position.z, FileIndex, 4);

					GetBytes(buffer, ModelPlacements[i].Rotation.x, FileIndex, 4);
					GetBytes(buffer, ModelPlacements[i].Rotation.y, FileIndex, 4);
					GetBytes(buffer, ModelPlacements[i].Rotation.z, FileIndex, 4);
					GetBytes(buffer, ModelPlacements[i].Rotation.w, FileIndex, 4);
				}
			}

			// Set model ref default values
			for (int i = 0; i < 20000; i++)
			{
				ModelRef[i] = 65535;
			}

			// Initialize model reference
			for (int i = 0; i < ModelCount; i++)
			{
				ModelRef[CollisionModels[i].Modelid] = i;
			}

			returnValue = true;
			delete[] buffer;
		}
	}
	ColAndreasBinaryfile.close();
	return returnValue;
}