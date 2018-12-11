#pragma once
#include <d3d11.h>
#include "Vertex.h"
#include <fstream>
#include <vector>

using namespace DirectX;
class Mesh
{
private:
    ID3D11Buffer* vertBuffer;
    ID3D11Buffer* indexBuffer;
    int indexBufferCount;
public:
    Mesh();
    Mesh(Vertex* vertices, int vertexCount, unsigned int* indices, int indexCount, ID3D11Device* device);
    Mesh(char* filename, ID3D11Device* device, XMFLOAT4 color);
    ~Mesh();
    ID3D11Buffer* GetVertexBuffer();
    ID3D11Buffer* GetIndexBuffer();
    int GetIndexCount();
};
