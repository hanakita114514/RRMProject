#pragma once

#include "Vertex.h"
#include "RRMCommon.h"

class GeometryGraph
{
private:
	ID3D11VertexShader* _vs2d;		//���_�V�F�[�_
	ID3D11VertexShader* _vs3d;		//���_�V�F�[�_
	ID3D11PixelShader* _ps;			//�s�N�Z���V�F�[�_
	ID3D11InputLayout* _layout;		//���C�A�E�g

	GeometryGraph();
	GeometryGraph(const GeometryGraph&);
	GeometryGraph& operator=(const GeometryGraph&);

	bool CreateShader(ID3D11VertexShader*& vs2d, ID3D11VertexShader*& vs3d, ID3D11InputLayout*& layout, ID3D11PixelShader*& ps);

public:
	~GeometryGraph();
	static GeometryGraph& Instance()
	{
		static GeometryGraph instance;

		return instance;
	}

	//���`��
	DrawingStructure DrawBox(float lx, float ly, float rx, float ry, unsigned int color, bool fillFlag);
	//���`��
	DrawingStructure DrawLine(float lx, float ly, float rx, float ry, unsigned int color);
	//�_�`��
	DrawingStructure DrawPoint(float x, float y, unsigned int color);
	//�~�`��
	DrawingStructure DrawCircle(float x, float y, float r, unsigned int color, bool fillFlag);
};

