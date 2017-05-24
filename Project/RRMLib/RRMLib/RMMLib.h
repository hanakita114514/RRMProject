#pragma once

#include <Windows.h>
#include <string>

namespace RRMLib
{
	//構造体
	typedef struct
	{
		int x, y, z;
		int rX, rY, rZ;
		int slider[2];
		unsigned int pov[4];
		unsigned int buttons[32];	//押されたボタンは128

	}DJOYPAD_STATE;

	//使用必須関数---------------------------------------------------------------------

	//RRMLibの初期化
	//使用の際最初に呼ぶ
	//戻り値　-1 エラー　0 成功
	int RRMLib_Init();

	//RRMLibの終了関数
	//戻り値 -1 エラー 0 成功
	int RRMLib_End();

	//ウィンドウのメッセージを取得
	//成功 : 0  エラー又はウィンドウが閉じられた : -1
	int ProcessMessage();
	//-----------------------------------------------------------------------------------

	//画面操作---------------------------------------------------------------------------

	//画面に描画されているものを消す
	void ClearDrawScreen();

	//裏画面切り替え

	int ScreenFlip();

	//ウィンドウサイズの変更
	//この関数を使用すると初期化される
	void SetWindowSize(int width, int height);

	//フルスクリーン化
	void ChangeFullScreenMode(bool fullScreen);

	void SetMainWindowText(std::string windowName);

	//描画系-----------------------------------------------------------------------------
	
	//画像読み込み
	int LoadGraph(std::string filePath);

	//画像の描画
	//左上から描画する
	void DrawGraph(int x, int y, int graphHandle);

	//画像の矩形描画
	void DrawRectGraph(float destX, float destY, int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool trunFlag);

	//画像の拡縮描画
	// lx ly 左上座標
	// rx ry 右下座標
	// handle 画像ハンドル
	void DrawExtendGraph(float lx, float ly, float rx, float ry, int handle);


	//矩形描画
	void DrawBox(float lx, float ly, float rx, float ry, unsigned int color, bool fillFlag);


	//色情報を取得する
	unsigned int GetColor(unsigned char red, unsigned char green, unsigned char blue);

	//------------------------------------------------------------------------------------

	//入力関係の関数----------------------------------------------------------------------

	//ジョイパッド入力
	bool GetJoypadDirectInputState(int inputType, DJOYPAD_STATE* joystate);



	//------------------------------------------------------------------------------------
	//音楽関係の関数----------------------------------------------------------------------

	// 音楽を読み込む
	// 文字リテラルLでパスを指定
	// 読み込めたらハンドルが返ってくる
	// 失敗 -1 成功 それ以外の数値
	int LoadSound(BSTR filePath);

	// 音楽を再生する
	// handle LodaSoundで読み込んだハンドルを指定
	void PlaySoundMem(int handle);

	// 音楽を一時停止させる
	void PauseSound(int handle);

	//音楽を止める
	void StopSound(int handle);

	//音楽のボリュームを変更する
	//0～10000
	void SetSoundVolume(long vol, int handle);

	//音楽のボリュームを取得する
	long GetSoundVolume(int handle);

}