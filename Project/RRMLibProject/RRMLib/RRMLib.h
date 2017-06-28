#pragma once

#include <Windows.h>
#include <string>

//---------------------------------------------------------------------------------
// 外部に見せるDefine定義
//---------------------------------------------------------------------------------

//キーボードインプット定義
#define KEY_ESCAPE          0x01
#define KEY_1               0x02
#define KEY_2               0x03
#define KEY_3               0x04
#define KEY_4               0x05
#define KEY_5               0x06
#define KEY_6               0x07
#define KEY_7               0x08
#define KEY_8               0x09
#define KEY_9               0x0A
#define KEY_0               0x0B
#define KEY_MINUS           0x0C
#define KEY_EQUALS          0x0D
#define KEY_BACK            0x0E
#define KEY_TAB             0x0F
#define KEY_Q               0x10
#define KEY_W               0x11
#define KEY_E               0x12
#define KEY_R               0x13
#define KEY_T               0x14
#define KEY_Y               0x15
#define KEY_U               0x16
#define KEY_I               0x17
#define KEY_O               0x18
#define KEY_P               0x19
#define KEY_LBRACKET        0x1A
#define KEY_RBRACKET        0x1B
#define KEY_RETURN          0x1C
#define KEY_LCONTROL        0x1D
#define KEY_A               0x1E
#define KEY_S               0x1F
#define KEY_D               0x20
#define KEY_F               0x21
#define KEY_G               0x22
#define KEY_H               0x23
#define KEY_J               0x24
#define KEY_K               0x25
#define KEY_L               0x26
#define KEY_SEMICOLON       0x27
#define KEY_APOSTROPHE      0x28
#define KEY_GRAVE           0x29
#define KEY_LSHIFT          0x2A
#define KEY_BACKSLASH       0x2B
#define KEY_Z               0x2C
#define KEY_X               0x2D
#define KEY_C               0x2E
#define KEY_V               0x2F
#define KEY_B               0x30
#define KEY_N               0x31
#define KEY_M               0x32
#define KEY_COMMA           0x33
#define KEY_PERIOD          0x34
#define KEY_SLASH           0x35
#define KEY_RSHIFT          0x36
#define KEY_MULTIPLY        0x37
#define KEY_LMENU           0x38
#define KEY_SPACE           0x39
#define KEY_CAPITAL         0x3A
#define KEY_F1              0x3B
#define KEY_F2              0x3C
#define KEY_F3              0x3D
#define KEY_F4              0x3E
#define KEY_F5              0x3F
#define KEY_F6              0x40
#define KEY_F7              0x41
#define KEY_F8              0x42
#define KEY_F9              0x43
#define KEY_F10             0x44
#define KEY_NUMLOCK         0x45
#define KEY_SCROLL          0x46
#define KEY_NUMPAD7         0x47
#define KEY_NUMPAD8         0x48
#define KEY_NUMPAD9         0x49
#define KEY_SUBTRACT        0x4A
#define KEY_NUMPAD4         0x4B
#define KEY_NUMPAD5         0x4C
#define KEY_NUMPAD6         0x4D
#define KEY_ADD             0x4E
#define KEY_NUMPAD1         0x4F
#define KEY_NUMPAD2         0x50
#define KEY_NUMPAD3         0x51
#define KEY_NUMPAD0         0x52
#define KEY_DECIMAL         0x53
#define KEY_OEM_102         0x56
#define KEY_F11             0x57
#define KEY_F12             0x58
#define KEY_F13             0x64
#define KEY_F14             0x65
#define KEY_F15             0x66
#define KEY_KANA            0x70
#define KEY_ABNT_C1         0x73
#define KEY_CONVERT         0x79
#define KEY_NOCONVERT       0x7B
#define KEY_YEN             0x7D
#define KEY_ABNT_C2         0x7E
#define KEY_NUMPADEQUALS    0x8D
#define KEY_PREVTRACK       0x90
#define KEY_AT              0x91
#define KEY_COLON           0x92
#define KEY_UNDERLINE       0x93
#define KEY_KANJI           0x94
#define KEY_STOP            0x95
#define KEY_AX              0x96
#define KEY_UNLABELED       0x97
#define KEY_NEXTTRACK       0x99
#define KEY_NUMPADENTER     0x9C
#define KEY_RCONTROL        0x9D
#define KEY_MUTE            0xA0
#define KEY_CALCULATOR      0xA1
#define KEY_PLAYPAUSE       0xA2
#define KEY_MEDIASTOP       0xA4
#define KEY_VOLUMEDOWN      0xAE
#define KEY_VOLUMEUP        0xB0
#define KEY_WEBHOME         0xB2
#define KEY_NUMPADCOMMA     0xB3
#define KEY_DIVIDE          0xB5
#define KEY_SYSRQ           0xB7
#define KEY_RMENU           0xB8
#define KEY_PAUSE           0xC5
#define KEY_HOME            0xC7
#define KEY_UP              0xC8
#define KEY_PRIOR           0xC9
#define KEY_LEFT            0xCB
#define KEY_RIGHT           0xCD
#define KEY_END             0xCF
#define KEY_DOWN            0xD0
#define KEY_NEXT            0xD1
#define KEY_INSERT          0xD2
#define KEY_DELETE          0xD3
#define KEY_LWIN            0xDB
#define KEY_RWIN            0xDC
#define KEY_APPS            0xDD
#define KEY_POWER           0xDE
#define KEY_SLEEP           0xDF
#define KEY_WAKE            0xE3
#define KEY_WEBSEARCH       0xE5
#define KEY_WEBFAVORITES    0xE6
#define KEY_WEBREFRESH      0xE7
#define KEY_WEBSTOP         0xE8
#define KEY_WEBFORWARD      0xE9
#define KEY_WEBBACK         0xEA
#define KEY_MYCOMPUTER      0xEB
#define KEY_MAIL            0xEC
#define KEY_MEDIASELECT     0xED

//ブレンド定義
#define RRM_BLENDMODE_NONE  0
#define RRM_BLENDMODE_ALPHA  1

//------------------------------------------------------------------------------------------------------------
//関数
//------------------------------------------------------------------------------------------------------------

namespace RRMLib
{
	//構造体
	typedef struct
	{
		int x, y, z;
		int rX, rY, rZ;
		int slider[2];
		unsigned int pov[4];
		unsigned char buttons[32];	//押されたボタンは128

	}DJOYPAD_STATE;

	//------------------------------------------------------------------------------------
	//使用必須関数
	//------------------------------------------------------------------------------------

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
	//画面操作
	//------------------------------------------------------------------------------------

	//画面に描画されているものを消す
	void ClearDrawScreen();

	//裏画面切り替え
	int ScreenFlip();

	//ウィンドウサイズの変更
	//この関数を使用すると初期化される
	void SetWindowSize(int width, int height);

	//フルスクリーン化
	void ChangeFullScreenMode(bool fullScreen);

	//ウィンドウタイトルにテキストを表示
	void SetMainWindowText(std::string windowName);

	//背景の色を変える
	//0 〜 255で指定
	void ChangeBackColor(int red, int green, int blue);

	//メッセージボックスを表示
	void ShowMessageBox(std::string text, std::string title);

	//------------------------------------------------------------------------------------
	//ロード系
	//------------------------------------------------------------------------------------

	//画像読み込み
	int LoadGraph(std::string filePath);

	//画像の分割読み込み
	int LoadDivGraph(std::string filePath, int allNum, int xNum, int yNum, int width, int height, int* handleBuf);

	//画像の削除
	void DeleteGraph(int handle);

	//------------------------------------------------------------------------------------
	//描画系
	//------------------------------------------------------------------------------------
	//画像の描画
	//左上から描画する
	void DrawGraph(float x, float y, int graphHandle);
	//void DrawGraph(int x, int y, DrawingStructure drawData);

	//画像の矩形描画
	void DrawRectGraph(float destX, float destY, int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool trunFlag);

	//画像の拡縮描画
	// lx ly 左上座標
	// rx ry 右下座標
	// handle 画像ハンドル
	void DrawExtendGraph(float lx, float ly, float rx, float ry, int handle);

	//画像の拡縮矩形描画
	void DrawRectExtendGraph(float destLX, float destLY, float destRX, float destRY,
		int srcX, int srcY, int width, int height, int graphHandle, bool transFlag, bool turnFlag);

	//画像の回転描画
	// x, y 中心描画
	void DrawRotaGraph(float x, float y, double angle, int graphHadle, bool transFlag, bool turnFlag);

	//矩形描画
	void DrawBox(float lx, float ly, float rx, float ry, unsigned int color, bool fillFlag);

	//線描画
	void DrawLine(float lx, float ly, float rx, float ry, unsigned int color);

	//点描画
	void DrawPoint(float x, float y, unsigned int color);

	//円描画
	void DrawCircle(float x, float y, float r, unsigned int color, bool fillflag);

	//色情報を取得する
	unsigned int GetColor(unsigned char red, unsigned char green, unsigned char blue);

	//------------------------------------------------------------------------------------
	//ブレンド関数
	//------------------------------------------------------------------------------------

	//RRM_BLENDMODE_で指定
	//pal 0 〜 255で指定
	void SetBlendMode(int mode, int pal);

	//------------------------------------------------------------------------------------
	//入力関係の関数
	//------------------------------------------------------------------------------------

	//ジョイパッド入力
	bool GetJoypadDirectInputState(int inputType, DJOYPAD_STATE* joystate);

	//キーボードの入力を受け取る
	//char[256]のバッファを渡す
	//char[DIK_〜]と指定する
	bool GetKeyboardState(char* keyBuf);

	//------------------------------------------------------------------------------------
	//音楽関係の関数
	//------------------------------------------------------------------------------------

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
	//0〜10000
	void SetSoundVolume(long vol, int handle);

	//音楽のボリュームを取得する
	long GetSoundVolume(int handle);
}