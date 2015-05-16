////////////////////////////////////////////////////////////////////////////////
// ColAndreas Plugin Include ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
Native Functions:
Add any remove building first before initializing the map
native CA_RemoveBuilding(modelid, Float:x, Float:y, Float:z, Float:radius)

Initialize the static map (used after CA_RemoveBuilding() )
native CA_Init();

Cast a line from p1 to p2 and return the point of collision
native CA_RayCastLine(Float:StartX, Float:StartY, Float:StartZ, Float:EndX, Float:EndY, Float:EndZ, &Float:x, &Float:y, &Float:z)

Converts SAMP rx,ry,rz rotations to quaternion used by ColAndreas
native CA_EulerToQuat(Float:rx, Float:ry, Float:rz, &Float:x, &Float:y, &Float:z, &Float:w)

Create a collision object
native CA_CreateObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, bool:add = false)

Destroy a collision object
native CA_DestroyObject(index)

Stock functions:
Create a dynamic object (Streamer) with collision in ColAndreas static
stock CA_CreateDynamicObject_SC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, vw = -1, interior = -1, playerid = -1, Float:streamdist = 300.0, Float:drawdist = 300.0)
stock CA_CreateDynamicObjectEx_SC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:drawdistance = 0.0, Float:streamdistance = 200.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)

Create a object with collision in ColAndreas static
CA_CreateObject_SC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:drawdistance = 300.0)

Create a dynamic object (Streamer) with collision in ColAndreas dynamic
CA_CreateDynamicObject_DC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, vw = -1, interior = -1, playerid = -1, Float:streamdist = 300.0, Float:drawdist = 300.0)
stock CreateDynamicObjectEx_DC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:drawdistance = 0.0, Float:streamdistance = 200.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)

Create a object with collision in ColAndreas dynamic
CA_CreateObject_DC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:drawdistance = 300.0)

Destroy a object with collision in ColAndreas
CA_DestroyObject_DC(index)

Destoys all objects streamer/regular
CA_DestroyAllObjects_DC()

MapAndreas replacement function
CA_FindZ_For2DCoord(Float:x, Float:y, &Float:z)

Notes:

Recommended loading order
- RemoveBuildings
- Init static map
- Add static objects

There is currently no support for virtual worlds / interior or per player with streamer objects

*/


// Natives
native CA_Init();
/*
native CA_RemoveBuilding(modelid, Float:x, Float:y, Float:z, Float:radius);
native CA_RayCastLine(Float:StartX, Float:StartY, Float:StartZ, Float:EndX, Float:EndY, Float:EndZ, &Float:x, &Float:y, &Float:z);
native CA_RayCastMultiLine(handle, Float:StartX, Float:StartY, Float:StartZ, Float:EndX, Float:EndY, Float:EndZ);
native CA_RayCastLineAngle(Float:StartX, Float:StartY, Float:StartZ, Float:EndX, Float:EndY, Float:EndZ, &Float:x, &Float:y, &Float:z, &Float:rx, &Float:ry, &Float:rz);
native CA_EulerToQuat(Float:rx, Float:ry, Float:rz, &Float:x, &Float:y, &Float:z, &Float:w);

// Used internally
native CA_CreateObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, bool:add = false);
native CA_DestroyObject(index);
native CA_SetObjectPos(index, Float:x, Float:y, Float:z);
native CA_SetObjectRot(index, Float:rx, Float:ry, Float:rz);
*/
// Callbacks
forward CA_OnRayCastMultiLine(handle, Float:ResultsX[], Float:ResultsY[], Float:ResultsZ[], ResultSize);

// ColAndreas currently supports 50000 user collision objects (Lower to acommodate muliple scripts)
#define         MAX_CA_OBJECTS          10000

// Water object ID
#define         WATER_OBJECT            19999

#define         OBJECT_TYPE_OBJECT      0
#define         OBJECT_TYPE_DYNAMIC     1


#if defined _Y_ITERATE_LOCAL_VERSION
	static stock Iterator:CA_Objects<MAX_CA_OBJECTS>;
#endif

enum CAOBJECTINFO
{
	ColdAndreadsID,
	ObjectID,
	ObjectType,

	#if !defined _Y_ITERATE_LOCAL_VERSION
		bool:ObjectUsed,
	#endif
}

static stock CA_ObjectList[MAX_CA_OBJECTS][CAOBJECTINFO];


// Static collision object functions (The index is not returned these can not be deleted!)
stock CA_CreateDynamicObjectEx_SC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:drawdistance = 0.0, Float:streamdistance = 200.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
{
    new id = CreateDynamicObjectEx(modelid, x, y, z, rx, ry, rz, drawdistance, streamdistance, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
	CA_CreateObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
	return id;
}

stock CA_CreateDynamicObject_SC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, vw = -1, interior = -1, playerid = -1, Float:streamdist = 300.0, Float:drawdist = 300.0)
{
    new id = CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, vw, interior, playerid, streamdist, drawdist);
	CA_CreateObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
	return id;
}

stock CA_CreateObject_SC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:drawdistance = 300.0)
{
	new id = CreateObject(modelid, x, y, z, rx, ry, rz, drawdistance);
	CA_CreateObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
	return id;
}

// Dynamic collision object functions (Removable)
stock CA_CreateDynamicObjectEx_DC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:drawdistance = 0.0, Float:streamdistance = 200.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
{
	new index = -1;
   	#if defined _Y_ITERATE_LOCAL_VERSION
		index = Iter_Free(CA_Objects);
	#else
		for(new i = 0; i < MAX_CA_OBJECTS; i++)
		{
		    if(CA_ObjectList[i][ObjectUsed] == false)
		    {
		        index = i;
		        break;
		    }
		}
	#endif

	if(index > -1)
	{
		#if defined _Y_ITERATE_LOCAL_VERSION
			Iter_Add(CA_Objects, index);
		#else
		    CA_ObjectList[index][ObjectUsed] = true;
		#endif
	    CA_ObjectList[index][ObjectID] = CreateDynamicObjectEx(modelid, x, y, z, rx, ry, rz, drawdistance, streamdistance, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		CA_ObjectList[index][ColdAndreadsID] = CA_CreateObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, true);
		CA_ObjectList[index][ObjectType] = OBJECT_TYPE_DYNAMIC;
	}
	return index;
}


stock CA_CreateDynamicObject_DC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, vw = -1, interior = -1, playerid = -1, Float:streamdist = 300.0, Float:drawdist = 300.0)
{
	new index = -1;
   	#if defined _Y_ITERATE_LOCAL_VERSION
		index = Iter_Free(CA_Objects);
	#else
		for(new i = 0; i < MAX_CA_OBJECTS; i++)
		{
		    if(CA_ObjectList[i][ObjectUsed] == false)
		    {
		        index = i;
		        break;
		    }
		}
	#endif

	if(index > -1)
	{
		#if defined _Y_ITERATE_LOCAL_VERSION
			Iter_Add(CA_Objects, index);
		#else
		    CA_ObjectList[index][ObjectUsed] = true;
		#endif
	    CA_ObjectList[index][ObjectID] = CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, vw, interior, playerid, streamdist, drawdist);
		CA_ObjectList[index][ColdAndreadsID] = index = CA_CreateObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, true);
		CA_ObjectList[index][ObjectType] = OBJECT_TYPE_DYNAMIC;
	}
	return index;
}

stock CA_CreateObject_DC(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:drawdistance = 300.0)
{
	new index = -1;
   	#if defined _Y_ITERATE_LOCAL_VERSION
		index = Iter_Free(CA_Objects);
	#else
		for(new i = 0; i < MAX_CA_OBJECTS; i++)
		{
		    if(CA_ObjectList[i][ObjectUsed] == false)
		    {
		        index = i;
		        break;
		    }
		}
	#endif

	if(index > -1)
	{
		#if defined _Y_ITERATE_LOCAL_VERSION
			Iter_Add(CA_Objects, index);
		#else
		    CA_ObjectList[index][ObjectUsed] = true;
		#endif
	    CA_ObjectList[index][ObjectID] = CreateObject(modelid, x, y, z, rx, ry, rz, drawdistance);
		CA_ObjectList[index][ColdAndreadsID] = index = CA_CreateObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, true);
		CA_ObjectList[index][ObjectType] = OBJECT_TYPE_OBJECT;
	}
	return index;
}


stock CA_DestroyObject_DC(index)
{
	// Out of bounds
	if(index < 0 || index >= MAX_CA_OBJECTS) return -1;
   	#if defined _Y_ITERATE_LOCAL_VERSION
		if(Iter_Contains(CA_Objects, index))
		{
			new next;
		    Iter_SafeRemove(CA_Objects, index, next);
   			if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_OBJECT) DestroyObject(CA_ObjectList[index][ObjectID]);
   			#if defined STREAMER_TYPE_OBJECT
		    	else if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_DYNAMIC) DestroyDynamicObject(CA_ObjectList[index][ObjectID]);
			#endif
		    CA_DestroyObject(CA_ObjectList[index][ColdAndreadsID]);
		    return next;
		}
	#else
        if(CA_ObjectList[index][ObjectUsed])
        {
   			if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_OBJECT) DestroyObject(CA_ObjectList[index][ObjectID]);
			#if defined STREAMER_TYPE_OBJECT
		    	else if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_DYNAMIC) DestroyDynamicObject(CA_ObjectList[index][ObjectID]);
			#endif
            CA_ObjectList[index][ObjectUsed] = false;
            CA_DestroyObject(CA_ObjectList[index][ColdAndreadsID]);
			return 1;
        }
   #endif
   return -1;
}

stock CA_SetObjectPos_DC(index, Float:x, Float:y, Float:z)
{
	// Out of bounds
	if(index < 0 || index >= MAX_CA_OBJECTS) return -1;
   	#if defined _Y_ITERATE_LOCAL_VERSION
		if(Iter_Contains(CA_Objects, index))
		{
			if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_OBJECT) SetObjectPos(CA_ObjectList[index][ObjectID], x, y, z);
			#if defined STREAMER_TYPE_OBJECT
			    else if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_DYNAMIC) SetDynamicObjectPos(CA_ObjectList[index][ObjectID], x, y, z);
			#endif
		    CA_SetObjectPos(CA_ObjectList[index][ColdAndreadsID], x, y, z);
		}
	#else
        if(CA_ObjectList[index][ObjectUsed])
        {
			if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_OBJECT) SetObjectPos(CA_ObjectList[index][ObjectID], x, y, z);
			#if defined STREAMER_TYPE_OBJECT
		    	else if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_DYNAMIC) SetDynamicObjectPos(CA_ObjectList[index][ObjectID], x, y, z);
			#endif
		    SetObjectPos(CA_ObjectList[index][ObjectID], x, y, z);
		    CA_SetObjectPos(CA_ObjectList[index][ColdAndreadsID], x, y, z);
			return 1;
        }
   #endif
   return -1;
}

stock CA_SetObjectRot_DC(index, Float:rx, Float:ry, Float:rz)
{
	// Out of bounds
	if(index < 0 || index >= MAX_CA_OBJECTS) return -1;
   	#if defined _Y_ITERATE_LOCAL_VERSION
		if(Iter_Contains(CA_Objects, index))
		{
		    if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_OBJECT) SetObjectRot(CA_ObjectList[index][ObjectID], rx, ry, rz);
			#if defined STREAMER_TYPE_OBJECT
				else if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_DYNAMIC) SetDynamicObjectRot(CA_ObjectList[index][ObjectID], rx, ry, rz);
			#endif
		    CA_SetObjectRot(CA_ObjectList[index][ColdAndreadsID], rx, ry, rz);
		}
	#else
        if(CA_ObjectList[index][ObjectUsed])
        {
		    if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_OBJECT) SetObjectRot(CA_ObjectList[index][ObjectID], rx, ry, rz);
			#if defined STREAMER_TYPE_OBJECT
				else if(CA_ObjectList[index][ObjectType] == OBJECT_TYPE_DYNAMIC) SetDynamicObjectRot(CA_ObjectList[index][ObjectID], rx, ry, rz);
			#endif
		    CA_SetObjectRot(CA_ObjectList[index][ColdAndreadsID], rx, ry, rz);
			return 1;
        }
   #endif
   return -1;
}

// Destroy all objects
CA_DestroyAllObjects_DC()
{
   	#if defined _Y_ITERATE_LOCAL_VERSION
		foreach(new i : CA_Objects)
		{
			if(CA_ObjectList[i][ObjectType] == OBJECT_TYPE_OBJECT) i = CA_DestroyObject_DC(i);
		}
	#else
		for(new i = 0; i < MAX_CA_OBJECTS; i++)
		{
		    if(CA_ObjectList[i][ObjectUsed])
		    {
				if(CA_ObjectList[i][ObjectType] == OBJECT_TYPE_OBJECT) CA_DestroyObject_DC(i);
	       }
		}

	#endif
}

// MapAndreas simulation
stock CA_FindZ_For2DCoord(Float:x, Float:y, &Float:z)
{
	if(CA_RayCastLine(x, y, 700.0, x, y, -1000.0, x, y, z)) return 1;
	return 0;
}


// Hooked functions
public OnFilterScriptExit()
{
//	CA_DestroyAllObjects_DC();
	if (funcidx("CA_OnFilterScriptExit") != -1)
  	{
    	return CallLocalFunction("CA_OnFilterScriptExit", "");
  	}
  	return 1;
 }

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit CA_OnFilterScriptExit

forward CA_OnFilterScriptExit();


public OnGameModeExit()
{
//	CA_DestroyAllObjects_DC();
	if (funcidx("CA_OnGameModeExit") != -1)
  	{
    	return CallLocalFunction("CA_OnGameModeExit", "");
  	}
  	return 1;
 }

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit CA_OnGameModeExit

forward CA_OnGameModeExit();
