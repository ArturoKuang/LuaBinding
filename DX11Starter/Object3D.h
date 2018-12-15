#pragma once
#include "Entity.h"
#include "Mesh.h"
#include "DirectxMath.h"
#include "SimpleShader.h"

using namespace DirectX;
class Object3D : public Entity
{
private:
	XMFLOAT4X4 worldMatrix;
	XMFLOAT3 position, rotation, scale;
	Mesh* mesh;
	SimplePixelShader* pShader;
	SimpleVertexShader* vShader;
public:
	Object3D(char* n, Mesh* m);
	~Object3D();

	//Getters
	XMFLOAT4X4 getWorldMatrix() { return worldMatrix; }
	XMFLOAT3 getPosition() { return position; }
	XMFLOAT3 getRotation() { return rotation; }
	XMFLOAT3 getScale() { return scale; }
	SimplePixelShader* getPixelShader(){ return pShader; }
	SimpleVertexShader* getVertexShader() { return vShader; }

	//Setters
	void setWorldMatrix(XMMATRIX newMat) { XMStoreFloat4x4(&worldMatrix, newMat); }
	void setPosition(XMFLOAT3 newPos) { position = newPos; }
	void setRotation(XMFLOAT3 newRot) { rotation = newRot; }
	void setScale(XMFLOAT3 newScale) { scale = newScale; }
	void setPixelShader(SimplePixelShader* p) { pShader = p; }
	void setVertexShader(SimpleVertexShader* v) { vShader = v; }

	void OnFrame(float dt) override;
	void OnStart() override;
	void Draw(ID3D11DeviceContext* ctx, XMFLOAT4X4 view, XMFLOAT4X4 projection) override;
	void Move(float x, float y, float z);
};

