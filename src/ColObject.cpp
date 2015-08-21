#include "ColObject.h"
#include "WaterArray.h"
#include "ColAndreasDatabaseReader.h"

// SAMP objects only go up 19999
#define WATER_MESH_ID 20000

std::vector <ColAndreasColObject*> colObjects;

ColAndreasColObject::ColAndreasColObject(uint16_t colindex)
{
	colMapObject = new btCompoundShape();

	// Build any spheres
	for (uint16_t i = 0; i < CollisionModels[colindex].SphereCount; i++)
	{
		btSphereShape* sphere = new btSphereShape(CollisionModels[colindex].SphereData[i].Radius);
		colMapObject->addChildShape(btTransform(btQuaternion(0, 0, 0, 1), btVector3(CollisionModels[colindex].SphereData[i].Offset.x, CollisionModels[colindex].SphereData[i].Offset.y, CollisionModels[colindex].SphereData[i].Offset.z)), sphere);
		spheres.push_back(sphere);
	}

	for (uint16_t i = 0; i < CollisionModels[colindex].BoxCount; i++)
	{
		// Create a box shape
		btBoxShape* box = new btBoxShape(btVector3(CollisionModels[colindex].BoxData[i].Size.x, CollisionModels[colindex].BoxData[i].Size.y, CollisionModels[colindex].BoxData[i].Size.z));
		colMapObject->addChildShape(btTransform(btQuaternion(0, 0, 0, 1), btVector3(CollisionModels[colindex].BoxData[i].Center.x, CollisionModels[colindex].BoxData[i].Center.y, CollisionModels[colindex].BoxData[i].Center.z)), box);
		boxes.push_back(box);
	}

	if (CollisionModels[colindex].FaceCount > 0)
	{
		// Create a triangular mesh
		trimesh = new btTriangleMesh();

		for (int i = 0; i < CollisionModels[colindex].FaceCount; i++)
		{
			// Add triangle faces
			trimesh->addTriangle(btVector3(CollisionModels[colindex].FacesData[i].FaceA.x, CollisionModels[colindex].FacesData[i].FaceA.y, CollisionModels[colindex].FacesData[i].FaceA.z),
				btVector3(CollisionModels[colindex].FacesData[i].FaceB.x, CollisionModels[colindex].FacesData[i].FaceB.y, CollisionModels[colindex].FacesData[i].FaceB.z),
				btVector3(CollisionModels[colindex].FacesData[i].FaceC.x, CollisionModels[colindex].FacesData[i].FaceC.y, CollisionModels[colindex].FacesData[i].FaceC.z));
		}
		meshshape = new btBvhTriangleMeshShape(trimesh, true);
		colMapObject->addChildShape(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)), meshshape);
	}
}

ColAndreasColObject::~ColAndreasColObject()
{	
	delete meshshape;
	delete trimesh;
	for (uint16_t i = 0; i < boxes.size(); i++)
	{
		delete boxes[i];
	}
	for (uint16_t i = 0; i < spheres.size(); i++)
	{
		delete spheres[i];
	}
	delete colMapObject;
}


btCompoundShape* ColAndreasColObject::getCompoundShape()
{
	return colMapObject;
}


bool LoadCollisionData(btDynamicsWorld* collisionWorld)
{
	if (ReadColandreasDatabaseFile("scriptfiles/colandreas/ColAndreas.cadb"))
	{
		for (uint16_t i = 0; i < ModelCount; i++)
		{
			if (i % 100 == 0)
			{
				printf("\33Loading: %0.1f\r", ((double)i / ModelCount) * 100);
			}
			ColAndreasColObject* colObject = new ColAndreasColObject(i);
			colObjects.push_back(colObject);
		}
		return true;
	}
	return false;
}


ColAndreasMapObject::ColAndreasMapObject(uint16_t modelid, const btQuaternion& objectRot, const btVector3& objectPos, btDynamicsWorld* world)
{
	colindex = ModelRef[modelid];

	collisionWorld = world;

	// Set the default motion
	colMapObjectPosition = new btDefaultMotionState(btTransform(objectRot, objectPos));

	// Contruction body for the shape
	btRigidBody::btRigidBodyConstructionInfo meshRigidBodyCI(0, colMapObjectPosition, colObjects[colindex]->getCompoundShape(), btVector3(0, 0, 0));

	// Create the rigid body
	colMapRigidBody = new btRigidBody(meshRigidBodyCI);

	// Set the user as the GTA model id for easy look up
	colMapRigidBody->setUserIndex(modelid);

	// Pointer reference to object
	colMapRigidBody->internalSetExtensionPointer(this);

	// Add rigid body to world
	collisionWorld->addRigidBody(colMapRigidBody);
}

ColAndreasMapObject::~ColAndreasMapObject()
{
	collisionWorld->removeRigidBody(colMapRigidBody);
	delete colMapRigidBody;
	delete colMapObjectPosition;
}

void ColAndreasMapObject::setMapObjectPosition(btVector3& position)
{
	colMapRigidBody->setWorldTransform(btTransform(colMapRigidBody->getWorldTransform().getRotation(), position));
	collisionWorld->removeRigidBody(colMapRigidBody);
	collisionWorld->addRigidBody(colMapRigidBody);
}


void ColAndreasMapObject::setMapObjectRotation(btQuaternion& rotation)
{
	colMapRigidBody->setWorldTransform(btTransform(rotation, colMapRigidBody->getWorldTransform().getOrigin()));
	collisionWorld->removeRigidBody(colMapRigidBody);
	collisionWorld->addRigidBody(colMapRigidBody);
}


MapWaterMesh::MapWaterMesh(btDynamicsWorld* world)
{
	collisionWorld = world;

	// Create a triangular mesh
	trimesh = new btTriangleMesh();

	for (uint16_t i = 0; i < 616; i++)
	{
		trimesh->addTriangle(btVector3(btScalar(waterData[i][0]), btScalar(waterData[i][1]), btScalar(waterData[i][2])),
			btVector3(btScalar(waterData[i][3]), btScalar(waterData[i][4]), btScalar(waterData[i][5])),
			btVector3(btScalar(waterData[i][6]), btScalar(waterData[i][7]), btScalar(waterData[i][8])));
	}

	meshshape = new btBvhTriangleMeshShape(trimesh, true);
	meshposition = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	// Contruction body for the shape
	btRigidBody::btRigidBodyConstructionInfo meshRigidBodyCI(0, meshposition, meshshape, btVector3(0, 0, 0));

	// Create the rigid body
	meshRigidBody = new btRigidBody(meshRigidBodyCI);

	// Water mesh is defined as 20000
	meshRigidBody->setUserIndex(WATER_MESH_ID);

	// Add rigid body to world
	collisionWorld->addRigidBody(meshRigidBody);

}

MapWaterMesh::~MapWaterMesh()
{
	delete meshRigidBody;
	delete meshposition;
	delete meshshape;
	delete trimesh;
}



ObjectManager::ObjectManager()
{
	for (int i = 0; i < MAX_MAP_OBJECTS; i++)
	{
		slotUsed[i] = false;
	}
}


int ObjectManager::addObjectManager(ColAndreasMapObject* mapObject)
{
	for (int i = 0; i < MAX_MAP_OBJECTS; i++)
	{
		if (!slotUsed[i])
		{
			slotUsed[i] = true;
			mapObjects[i] = mapObject;
			return i;
		}
	}
	return -1;
}

int ObjectManager::removeObjectManager(const uint16_t index)
{
	if (slotUsed[index])
	{
		slotUsed[index] = false;
		delete mapObjects[index];
		return 1;
	}
	return 0;
}

int ObjectManager::setObjectPosition(const uint16_t index, btVector3& position)
{
	if (slotUsed[index])
	{
		mapObjects[index]->setMapObjectPosition(position);
		return 1;
	}
	return 0;
}

int ObjectManager::setObjectRotation(const uint16_t index, btQuaternion& rotation)
{
	if (slotUsed[index])
	{
		mapObjects[index]->setMapObjectRotation(rotation);
		return 1;
	}
	return 0;
}


int ObjectManager::getBoundingSphere(uint16_t modelid, btVector3& center, btScalar& radius)
{
	uint16_t colindex = ModelRef[modelid];

	// Check for LOD objects
	if (colindex == 65535)
	{
		if (LodReference[modelid] > 0)
			colindex = ModelRef[LodReference[modelid]];
	}


	if (colindex != 65535)
	{
		colObjects[colindex]->getCompoundShape()->getBoundingSphere(center, radius);
		return 1;
	}
	return 0;
}


RemovedBuildingManager::RemovedBuildingManager()
{
}

bool RemovedBuildingManager::isRemoved(uint16_t model, Vector position)
{
	for (uint16_t i = 0; i < removedBuildings.size(); i++)
	{
		if (model == removedBuildings[i].r_Model || model == -1)
		{
			btScalar dist = btDistance(btVector3(btScalar(position.x), btScalar(position.y), btScalar(position.z)),
				btVector3(btScalar(removedBuildings[i].r_X), btScalar(removedBuildings[i].r_Y), btScalar(removedBuildings[i].r_Z)));

			if (dist <= btScalar(removedBuildings[i].r_Radius))
			{
				return 1;
			}
		}
	}
	return 0;
}

void RemovedBuildingManager::addBuilding(removeBuildingData removeData)
{
	removedBuildings.push_back(removeData);
}

void InitCollisionMap(btDynamicsWorld* collisionWorld, RemovedBuildingManager* removedManager)
{
	for (uint16_t i = 0; i < IPLCount; i++)
	{
		if (ModelPlacements[i].Modelid > 19999)
		{
			logprintf("ERROR::InitCollisionMap::Invalid ModelID::%i", ModelPlacements[i].Modelid);
			continue;
		}

		uint16_t index = ModelRef[ModelPlacements[i].Modelid];

		if (i % 100 == 0)
		{
			printf("\33Loading: %0.1f\r", ((double)i / IPLCount) * 100);
		}

		if (!removedManager->isRemoved(ModelPlacements[i].Modelid, ModelPlacements[i].Position))
		{
			// Continue if model has no collision
			if (index == 65535) continue;

			ColAndreasMapObject* tmpObject;
			tmpObject = new ColAndreasMapObject(ModelPlacements[i].Modelid, btQuaternion(ModelPlacements[i].Rotation.x, ModelPlacements[i].Rotation.y, ModelPlacements[i].Rotation.z, ModelPlacements[i].Rotation.w), btVector3(ModelPlacements[i].Position.x, ModelPlacements[i].Position.y, ModelPlacements[i].Position.z), collisionWorld);

		}
	}
}

uint16_t GetModelRef(uint16_t model) 
{
	if (model <= 20000 && ModelRef[model] != 65535)
		return ModelRef[model];
	else
		return 65535;
}
