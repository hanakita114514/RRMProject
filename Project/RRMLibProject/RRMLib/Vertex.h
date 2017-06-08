#pragma once

#include <D3DX11.h>
#include <xnamath.h>

struct Vertex2D
{
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};

struct Vertex3D
{
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 uv;
};