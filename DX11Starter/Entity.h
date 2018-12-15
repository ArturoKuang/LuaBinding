#pragma once
#include "DirectXMath.h"
#include "DXCore.h"

using namespace DirectX;
class Entity
{
protected:
	Entity* parent;
	char* name;
public:
	Entity(char* n) { name = n; }
	virtual void OnStart() = 0;
	virtual void OnFrame(float dt) = 0;
	virtual void Draw(ID3D11DeviceContext* ctx, XMFLOAT4X4 view, XMFLOAT4X4 projection) = 0;
	char* GetName() { return name; }
	void SetName(char* n) { name = n; }
	Entity* GetParent() { return parent; }
	void SetParent(Entity* p) { parent = p; }
};