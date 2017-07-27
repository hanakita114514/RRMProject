#pragma once

struct HandleList
{
	int handle;
	void *data;
	HandleList* prev;
	HandleList* next;
};

struct HandleInfo
{
	int id;				//エラーチェック
	int handle;			//データハンドル
	bool deleteFlag;	//削除されたらtrue
	int asyncLoadResult;//非同期読み込みの結果
	HandleList list;	//次と前のポインタ

	HandleInfo() : id(0), handle(-1), deleteFlag(false),
		asyncLoadResult(true)
	{

	}
};

void HandleInit(HandleInfo& handleInfo);