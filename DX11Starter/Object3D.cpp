#include "Object3D.h"

Object3D::Object3D(char* n, Mesh* m) : Entity(n)
{
	mesh = m;
	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity());
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

Object3D::~Object3D()
{
	delete mesh;
}

void Object3D::OnFrame(float dt)
{
}

void Object3D::Draw(ID3D11DeviceContext * ctx, XMFLOAT4X4 view, XMFLOAT4X4 projection)
{
	vShader->SetMatrix4x4("world", worldMatrix);
	vShader->SetMatrix4x4("view", view);
	vShader->SetMatrix4x4("projection", projection);
	vShader->SetShader();
	pShader->SetShader();
	vShader->CopyAllBufferData();
	pShader->CopyAllBufferData();
	
	ID3D11Buffer* meshVertexBuffer = mesh->GetVertexBuffer();
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	ctx->IASetVertexBuffers(0, 1, &meshVertexBuffer, &stride, &offset);
	ctx->IASetIndexBuffer(mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	ctx->DrawIndexed(
		mesh->GetIndexCount(),
		0,
		0
	);
}

void Object3D::Move(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
	XMMATRIX newWorld = XMMatrixTranslation(position.x, position.y, position.z);
	XMStoreFloat4x4(&worldMatrix, newWorld);
}
