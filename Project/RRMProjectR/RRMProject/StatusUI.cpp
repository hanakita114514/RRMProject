#include "StatusUI.h"
#include <RRMLib.h>
#include "GraphicLoad.h"
#include "common.h"

const int IMG_HEIGHT = 112;

StatusUI::StatusUI()
{
	_handle = GraphicLoad::Instance().LoadGraph("Resource/img/UI/Ui.png");
}


StatusUI::~StatusUI()
{
}

void
StatusUI::Draw()
{
	RRMLib::DrawExtendGraph(0, WINDOW_HEIGHT - IMG_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT,_handle);
}
