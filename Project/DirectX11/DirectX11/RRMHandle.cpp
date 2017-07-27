#include "RRMHandle.h"

void HandleInit(HandleInfo& handleInfo)
{
	handleInfo.asyncLoadResult = true;
	handleInfo.handle = -1;
	handleInfo.deleteFlag = false;
	handleInfo.id = 0;
	handleInfo.list.data = nullptr;
	handleInfo.list.next = nullptr;
	handleInfo.list.prev = nullptr;
	handleInfo.handle = -1;
}