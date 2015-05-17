#ifndef _INCL_DYNWORLD
#define _INCL_DYNWORLD

#include <btBulletDynamicsCommon.h>
#include "ColObject.h"
#include "ColAndreas.h"


class ColAndreasWorld
{
public:
	// Initialize ColAndreas
	ColAndreasWorld();

	// ColAndreas closed
	~ColAndreasWorld();

	RemovedBuildingManager* removedManager;
	ObjectManager* objectManager;

	// Converts GTA rotations to quaternion
	btScalar getDist3D(const btVector3& p1, const btVector3& p2);
	void EulerToQuat(btVector3& rotation, btQuaternion& result);
	void QuatToEuler(btQuaternion& rotation, btVector3& result);
	int performRayTest(const btVector3& Start, const btVector3& End, btVector3& Result, uint16_t& model);
	int performRayTestEx(const btVector3& Start, const btVector3& End, btVector3& Result, btQuaternion& Rotation, btVector3& Position, uint16_t& model);
	int performRayTestAngle(const btVector3& Start, const btVector3& End, btVector3& Result, btScalar& RX, btScalar& RY, btScalar& RZ, uint16_t& model);
	int performRayTestAngleEx(const btVector3& Start, const btVector3& End, btVector3& Result, btScalar& RX, btScalar& RY, btScalar& RZ, btQuaternion& Rotation, btVector3& Position, uint16_t& model);
	int performRayTestAll(const btVector3& Start, const btVector3& End, btAlignedObjectArray < btVector3 >& Result, int ModelIDs[], int size);
	int performRayTestReflection(const btVector3& Start, const btVector3& End, btVector3& Position, btVector3& Result, uint16_t& model);
	int performRayTestNormal(const btVector3& Start, const btVector3& End, btVector3& Result, btVector3& Normal, uint16_t& model);


	uint16_t createColAndreasMapObject(uint16_t addtomanager, uint16_t modelid, const btQuaternion& objectRot, const btVector3& objectPos);
	uint16_t getModelRef(uint16_t model);
	void colandreasInitMap();
	bool loadCollisionData();

private:
	MapWaterMesh* mapWaterMesh;
	btDynamicsWorld* dynamicsWorld;
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	const btScalar DEG_TO_RAD = btScalar(0.0174532925);
	const btScalar RADIAN_TO_DEG = btScalar(57.29577951);
};

extern ColAndreasWorld* collisionWorld;

#endif
