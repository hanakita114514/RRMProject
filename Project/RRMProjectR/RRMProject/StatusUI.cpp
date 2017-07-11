#include "StatusUI.h"
#include <RRMLib.h>
#include "GraphicLoad.h"
#include "common.h"

static const float IMG_HEIGHT = 112.f;
static const float FILTER_H = 75.0f;

StatusUI::StatusUI()
{
	_handle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/Ui.png");
	_filterHandle[0] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/filter1.png");
	_filterHandle[1] = GraphicLoad::Instance().LoadGraph("Resource/img/UI/filter2.png");
}


StatusUI::~StatusUI()
{
}

void
StatusUI::Draw()
{
	int posX = WINDOW_WIDTH / 2;

	RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, 128);
	for (int i = 0; i < 2; ++i)
	{
		RRMLib::DrawExtendGraph(posX * i, 0, posX * i + WINDOW_WIDTH / 2, 0 + FILTER_H, _filterHandle[i]);
	}
	RRMLib::SetBlendMode(RRM_BLENDMODE_NONE, 0);


	//RRMLib::DrawExtendGraph(0, WINDOW_HEIGHT - IMG_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT,_handle);
}
