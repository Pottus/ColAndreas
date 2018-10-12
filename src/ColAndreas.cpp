//*********************************************************************************************************//
// ColAndreas by [uL]Pottus & [uL]Chris42O & [uL]Slice ****************************************************//
//*********************************************************************************************************//

#include <string>
#include <vector>

using namespace std;

#include <btBulletDynamicsCommon.h>
#include "ColAndreas.h"
#include "DynamicWorld.h"
#include "Natives.h"

bool colInit = false;
bool colDataLoaded = false;
cell nullAddress = NULL;

ColAndreasWorld* collisionWorld;

logprintf_t				logprintf;

extern void *pAMXFunctions;

// Plugin Load
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("*********************");
	logprintf("** Created By:     **");
	logprintf("** [uL]Chris42O    **");
	logprintf("** [uL]Slice       **");
	logprintf("** [uL]Pottus      **");
	logprintf("*********************");

	collisionWorld = new ColAndreasWorld();

	if (collisionWorld->loadCollisionData())
	{
		logprintf("Loaded collision data.");
		colDataLoaded = true;
	}
	else
	{
		logprintf("No collision data found.");
	}

	logprintf("*********************");
	logprintf("  ColAndreas Loaded");
	logprintf("   " CA_VERSION);
	logprintf("*********************");

	return true;
}


// Plugin unload
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
//	delete collisionWorld;

	logprintf("*********************");
	logprintf("*ColAndreas Unloaded*");
	logprintf("*********************");

}

// Function list
AMX_NATIVE_INFO PluginNatives[] =
{
	// Standard Natives
	{ "CA_Init", ColAndreasNatives::CA_Init },
	{ "CA_RayCastLine", ColAndreasNatives::CA_RayCastLine },
	{ "CA_RayCastLineExtraID", ColAndreasNatives::CA_RayCastLineExtraID },
	{ "CA_RayCastLineID", ColAndreasNatives::CA_RayCastLineID },
	{ "CA_RayCastLineAngle", ColAndreasNatives::CA_RayCastLineAngle },
	{ "CA_RayCastMultiLine", ColAndreasNatives::CA_RayCastMultiLine },
	{ "CA_RayCastReflectionVector", ColAndreasNatives::CA_RayCastReflectionVector },
	{ "CA_RayCastLineNormal", ColAndreasNatives::CA_RayCastLineNormal },
	{ "CA_ContactTest", ColAndreasNatives::CA_ContactTest },
	{ "CA_CreateObject", ColAndreasNatives::CA_CreateObject },
	{ "CA_DestroyObject", ColAndreasNatives::CA_DestroyObject },
	{ "CA_IsValidObject", ColAndreasNatives::CA_IsValidObject },
	{ "CA_EulerToQuat", ColAndreasNatives::CA_EulerToQuat },
	{ "CA_QuatToEuler", ColAndreasNatives::CA_QuatToEuler },
	{ "CA_RemoveBuilding", ColAndreasNatives::CA_RemoveBuilding },
	{ "CA_SetObjectPos", ColAndreasNatives::CA_SetObjectPos },
	{ "CA_SetObjectRot", ColAndreasNatives::CA_SetObjectRot },
	{ "CA_GetModelBoundingSphere", ColAndreasNatives::CA_GetModelBoundingSphere },
	{ "CA_GetModelBoundingBox", ColAndreasNatives::CA_GetModelBoundingBox },
	{ "CA_SetObjectExtraID", ColAndreasNatives::CA_SetObjectExtraID },
	{ "CA_GetObjectExtraID", ColAndreasNatives::CA_GetObjectExtraID },

	// Extended Natives
	{ "CA_RayCastLineEx", ColAndreasNatives::CA_RayCastLineEx },
	{ "CA_RayCastLineAngleEx", ColAndreasNatives::CA_RayCastLineAngleEx },
	{ 0, 0 }
};

// Plugin Export
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}


PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
