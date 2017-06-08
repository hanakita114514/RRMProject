#include "SoundManager.h"
#include  <cri_adx2le.h>


CriAtomExAcbHn acbHandle;
CriAtomExVoicePoolHn voicePool;
CriAtomDbasId dbas;
CriAtomExPlayerHn player;


//エラー時のコールバック関数
static void CriErrorCallbackFunction(const CriChar8* errid, CriUint32 p1, CriUint32 p2,
	CriUint32* parray)
{
	const CriChar8* errmsg;

	//デバッグウィンドウにエラーを出力
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	OutputDebugStringA(errmsg);
}

//メモリ確保時のコールバック関数
void* CriAllocatorFunction(void* obj, CriUint32 size)
{
	void* ptr = malloc(size);
	return ptr;
}

//メモリ解放時のコールバック関数
void CriFreeFunc(void* obj, void* ptr)
{
	free(ptr);
}

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void 
SoundManager::Init()
{
	//エラー時のコールバック関数を登録
	criErr_SetCallback(CriErrorCallbackFunction);

	//メモリアロケータの登録
	criAtomEx_SetUserAllocator(CriAllocatorFunction, CriFreeFunc, nullptr);
	
	//ライブラリの初期化
	criAtomEx_Initialize_PC(nullptr, nullptr, 0);

	//ストリーミング用バッファの作成
	dbas = criAtomDbas_Create(nullptr, nullptr, 0);

	//全体設定ファイルの登録
	criAtomEx_RegisterAcfFile(nullptr, "Sound/ADX2_samples.acf", nullptr, 0);

	//DSPバス設定の登録
	criAtomEx_AttachDspBusSetting("DspBusSetting_0", nullptr, 0);

	//ボイスプールの作成
	CriAtomExStandardVoicePoolConfig vpconfig;
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&vpconfig);
	vpconfig.player_config.streaming_flag = CRI_TRUE;
	voicePool = criAtomExVoicePool_AllocateStandardVoicePool(&vpconfig, nullptr, 0);

	//ACBファイルのロード
	acbHandle = criAtomExAcb_LoadAcbFile(nullptr, "Sound/Basic.acb", nullptr, "Sound/Basic.awb",
		nullptr, 0);

	//プレーヤの作成
	player = criAtomExPlayer_Create(nullptr, nullptr, 0);

}

void 
SoundManager::Load()
{

}

void 
SoundManager::Play(int cueId)
{
	criAtomExPlayer_SetCueId(player, acbHandle, cueId);	//キューを選択
	criAtomExPlayer_Start(player); //現在のキューを再生
}

void 
SoundManager::Terminate()
{
	//後始末
	criAtomExPlayer_Destroy(player);
	criAtomExAcb_Release(acbHandle);
	
	criAtomExVoicePool_Free(voicePool);
	criAtomEx_UnregisterAcf();
	criAtomEx_Finalize_PC();
}

void 
SoundManager::Update()
{
	criAtomEx_ExecuteMain();
}
