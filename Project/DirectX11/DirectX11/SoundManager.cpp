#include "SoundManager.h"
#include  <cri_adx2le.h>


CriAtomExAcbHn acbHandle;
CriAtomExVoicePoolHn voicePool;
CriAtomDbasId dbas;
CriAtomExPlayerHn player;


//�G���[���̃R�[���o�b�N�֐�
static void CriErrorCallbackFunction(const CriChar8* errid, CriUint32 p1, CriUint32 p2,
	CriUint32* parray)
{
	const CriChar8* errmsg;

	//�f�o�b�O�E�B���h�E�ɃG���[���o��
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	OutputDebugStringA(errmsg);
}

//�������m�ێ��̃R�[���o�b�N�֐�
void* CriAllocatorFunction(void* obj, CriUint32 size)
{
	void* ptr = malloc(size);
	return ptr;
}

//������������̃R�[���o�b�N�֐�
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
	//�G���[���̃R�[���o�b�N�֐���o�^
	criErr_SetCallback(CriErrorCallbackFunction);

	//�������A���P�[�^�̓o�^
	criAtomEx_SetUserAllocator(CriAllocatorFunction, CriFreeFunc, nullptr);
	
	//���C�u�����̏�����
	criAtomEx_Initialize_PC(nullptr, nullptr, 0);

	//�X�g���[�~���O�p�o�b�t�@�̍쐬
	dbas = criAtomDbas_Create(nullptr, nullptr, 0);

	//�S�̐ݒ�t�@�C���̓o�^
	criAtomEx_RegisterAcfFile(nullptr, "Sound/ADX2_samples.acf", nullptr, 0);

	//DSP�o�X�ݒ�̓o�^
	criAtomEx_AttachDspBusSetting("DspBusSetting_0", nullptr, 0);

	//�{�C�X�v�[���̍쐬
	CriAtomExStandardVoicePoolConfig vpconfig;
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&vpconfig);
	vpconfig.player_config.streaming_flag = CRI_TRUE;
	voicePool = criAtomExVoicePool_AllocateStandardVoicePool(&vpconfig, nullptr, 0);

	//ACB�t�@�C���̃��[�h
	acbHandle = criAtomExAcb_LoadAcbFile(nullptr, "Sound/Basic.acb", nullptr, "Sound/Basic.awb",
		nullptr, 0);

	//�v���[���̍쐬
	player = criAtomExPlayer_Create(nullptr, nullptr, 0);

}

void 
SoundManager::Load()
{

}

void 
SoundManager::Play(int cueId)
{
	criAtomExPlayer_SetCueId(player, acbHandle, cueId);	//�L���[��I��
	criAtomExPlayer_Start(player); //���݂̃L���[���Đ�
}

void 
SoundManager::Terminate()
{
	//��n��
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
