#include "GraphList.h"
#include <D3DX11.h>
#include <D3D11.h>
#include "DeviceDx11.h"


GraphList::GraphList()
{
}


GraphList::~GraphList()
{
}

void 
GraphList::Add(DrawingStructure& ds)
{
	_drawList.push_back(ds);
}

void 
GraphList::Draw()
{
	DrawingStructure prevDs = {};
	DeviceDx11& dev = DeviceDx11::Instance();

	for (auto d : _drawList)
	{
		if (d.topology != prevDs.topology)
		{
			prevDs.topology = d.topology;
			dev.Context()->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)d.topology);
		}
		if (d.vs != prevDs.vs)
		{
			prevDs.vs = d.vs;
			dev.Context()->VSSetShader(d.vs, nullptr, 0);
		}
		if (d.ps != prevDs.ps)
		{
			prevDs.ps = d.ps;
			dev.Context()->PSSetShader(d.ps, nullptr, 0);
		}
		if (d.layout != prevDs.layout)
		{
			prevDs.layout = d.layout;
			dev.Context()->IASetInputLayout(d.layout);
		}
		if ((d.texture != prevDs.texture) && d.texture != nullptr)
		{
			prevDs.texture = d.texture;
			dev.Context()->PSSetShaderResources(0, d.texSlot, &d.texture);
		}
		if (d.colorBuffer != nullptr)
		{
			dev.Context()->PSSetConstantBuffers(1, 1, &d.colorBuffer);
			d.colorBuffer->Release();
		}

		dev.Context()->IASetVertexBuffers(0, 1, &d.vb, &d.stride, &d.offset);
		dev.Context()->Draw(d.drawNum, 0);
		d.vb->Release();
	}

	_drawList.clear();
}