#pragma once
#include "Entity.h"
#include "DirectxMath.h"

using namespace DirectX;
class Object3D : Entity
{
private:

public:
	Object3D(char* n);
	~Object3D();

	void OnFrame();
};

