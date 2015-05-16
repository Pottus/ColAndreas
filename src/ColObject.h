#ifndef _INCL_COLOBJECT
#define _INCL_COLOBJECT

#include <btBulletDynamicsCommon.h>
#include "ColAndreasDatabaseReader.h"
#include "ColAndreas.h"
#include "LodArray.h"

#define MAX_MAP_OBJECTS 50000

struct removeBuildingData
{
	uint16_t r_Model;
	float r_X;
	float r_Y;
	float r_Z;
	float r_Radius;
};


// Collision Objects
class ColAndreasColObject
{
public:
	ColAndreasColObject(uint16_t colindex);
	~ColAndreasColObject();
	btCompoundShape* getCompoundShape();
private:
	// Object Data
	btCompoundShape* colMapObject;

	// Mesh
	btTriangleMesh* trimesh;
	btTriangleMeshShape* meshshape;
	std::vector <btSphereShape*> spheres;
	std::vector <btBoxShape*> boxes;
};

// Map Objects
class ColAndreasMapObject
{
public:
	ColAndreasMapObject(uint16_t modelid, const btQuaternion& objectRot, const btVector3& objectPos, btDynamicsWorld* world);
	~ColAndreasMapObject();
	void setMapObjectPosition(btVector3& position);
	void setMapObjectRotation(btQuaternion& rotation);
private:
	// Object Data
	btRigidBody* colMapRigidBody;
	btDefaultMotionState* colMapObjectPosition;
	uint16_t colindex = 0;
	btDynamicsWorld* collisionWorld;
};


class MapWaterMesh
{
public:
	MapWaterMesh(btDynamicsWorld* world);
	~MapWaterMesh();
private:
	btTriangleMesh* trimesh;
	btBvhTriangleMeshShape* meshshape;
	btDefaultMotionState* meshposition;
	btRigidBody* meshRigidBody;
	btDynamicsWorld* collisionWorld;
};


class ObjectManager
{
public:
	ObjectManager();
	int addObjectManager(ColAndreasMapObject* mapObject);
	int removeObjectManager(const uint16_t index);
	int setObjectPosition(const uint16_t index, btVector3& position);
	int setObjectRotation(const uint16_t index, btQuaternion& rotation);
	int getBoundingSphere(uint16_t modelid, btVector3& center, btScalar& radius);	
private:
	bool slotUsed[MAX_MAP_OBJECTS];
	ColAndreasMapObject* mapObjects[MAX_MAP_OBJECTS];

};


class RemovedBuildingManager
{
public:
	RemovedBuildingManager();
	bool isRemoved(uint16_t model, Vector position);
	void addBuilding(removeBuildingData removeData);
private:
	std::vector <removeBuildingData> removedBuildings;
};

bool LoadCollisionData(btDynamicsWorld* collisionWorld);
void InitCollisionMap(btDynamicsWorld* collisionWorld, RemovedBuildingManager* removeManager);
uint16_t GetModelRef(uint16_t model);

// Pointer reference
extern std::vector <ColAndreasColObject*> colObjects;

typedef struct {
	btVector3 pos;
	btScalar dist;
} btMultiCast;


#endif
