#include "Resource.h"


Resource::Resource()
{
}


Resource::~Resource()
{
}

//A usefull bit to avoid searching for uneeded bits thus saving some performance. :P
bool Resource::hasSpawnPoint()
{
	return spawnpoints.empty();
}

bool Resource::hasMap()
{
	return maps.empty();
}

bool Resource::hasMesh()
{
	return meshs.empty();
}

bool Resource::hasTexture()
{
	return textures.empty();
}

bool Resource::hasScript()
{
	return scripts.empty();
}

void Resource::addSpawnPoint(vector3d<s32> point)
{
	spawnpoints.push_back(point);
}

void Resource::addMap(path file)
{
	maps.push_back(file);
}

void Resource::addMesh(path file)
{
	meshs.push_back(file);
}

void Resource::addTexture(path file)
{
	textures.push_back(file);
}

void Resource::addScript(path file)
{
	scripts.push_back(file);
}