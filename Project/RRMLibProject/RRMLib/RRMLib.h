#pragma once

#include <Windows.h>
#include <string>

#define RRM_BLENDMODE_NONE  0
#define RRM_BLENDMODE_ALPHA  1

namespace RRMLib
{
	//�\����
	typedef struct
	{
		int x, y, z;
		int rX, rY, rZ;
		int slider[2];
		unsigned int pov[4];
		unsigned char buttons[32];	//�����ꂽ�{�^����128

	}DJOYPAD_STATE;

	//------------------------------------------------------------------------------------
	//�g�p�K�{�֐�
	//------------------------------------------------------------------------------------

	//RRMLib�̏�����
	//�g�p�̍ۍŏ��ɌĂ�
	//�߂�l�@-1 �G���[�@0 ����
	int RRMLib_Init();

	//RRMLib�̏I���֐�
	//�߂�l -1 �G���[ 0 ����
	int RRMLib_End();

	//�E�B���h�E�̃��b�Z�[�W���擾
	//���� : 0  �G���[���̓E�B���h�E������ꂽ : -1
	int ProcessMessage();

	//-----------------------------------------------------------------------------------
	//��ʑ���
	//------------------------------------------------------------------------------------

	//��ʂɕ`�悳��Ă�����̂�����
	void ClearDrawScreen();

	//����ʐ؂�ւ�
	int ScreenFlip();

	//�E�B���h�E�T�C�Y�̕ύX
	//���̊֐����g�p����Ə����������
	void SetWindowSize(int width, int height);

	//�t���X�N���[����
	void ChangeFullScreenMode(bool fullScreen);

	//�E�B���h�E�^�C�g���Ƀe�L�X�g��\��
	void SetMainWindowText(std::string windowName);

	//�w�i�̐F��ς���
	//0 �` 255�Ŏw��
	void ChangeBackColor(int red, int green, int blue);

	//------------------------------------------------------------------------------------
	//���[�h�n
	//------------------------------------------------------------------------------------

	//�摜�ǂݍ���
	int LoadGraph(std::string filePath);

	//------------------------------------------------------------------------------------
	//�`��n
	//------------------------------------------------------------------------------------
	//�摜�̕`��
	//���ォ��`�悷��
	void DrawGraph(int x, int y, int graphHandle);

	//�摜�̋�`�`��
	void DrawRectGraph(float destX, float destY, int srcX, int srcY,
		int width, int height, int graphHandle, bool transFlag, bool trunFlag);

	//�摜�̊g�k�`��
	// lx ly ������W
	// rx ry �E�����W
	// handle �摜�n���h��
	void DrawExtendGraph(float lx, float ly, float rx, float ry, int handle);

	//�摜�̊g�k��`�`��
	void DrawRectExtendGraph(float destLX, float destLY, float destRX, float destRY,
		int srcX, int srcY, int width, int height, int graphHandle, bool transFlag, bool turnFlag);

	//��`�`��
	void DrawBox(float lx, float ly, float rx, float ry, unsigned int color, bool fillFlag);

	//���`��
	void DrawLine(float lx, float ly, float rx, float ry, unsigned int color);

	//�_�`��
	void DrawPoint(float x, float y, unsigned int color);

	//�~�`��
	void DrawCircle(float x, float y, float r, unsigned int color, bool fillflag);

	//�F�����擾����
	unsigned int GetColor(unsigned char red, unsigned char green, unsigned char blue);

	//------------------------------------------------------------------------------------
	//�u�����h�֐�
	//------------------------------------------------------------------------------------

	//RRM_BLENDMODE_�Ŏw��
	//pal 0 �` 255�Ŏw��
	void SetBlendMode(int mode, int pal);

	//------------------------------------------------------------------------------------
	//���͊֌W�̊֐�
	//------------------------------------------------------------------------------------

	//�W���C�p�b�h����
	bool GetJoypadDirectInputState(int inputType, DJOYPAD_STATE* joystate);

	//------------------------------------------------------------------------------------
	//���y�֌W�̊֐�
	//------------------------------------------------------------------------------------

	// ���y��ǂݍ���
	// �������e����L�Ńp�X���w��
	// �ǂݍ��߂���n���h�����Ԃ��Ă���
	// ���s -1 ���� ����ȊO�̐��l
	int LoadSound(BSTR filePath);

	// ���y���Đ�����
	// handle LodaSound�œǂݍ��񂾃n���h�����w��
	void PlaySoundMem(int handle);

	// ���y���ꎞ��~������
	void PauseSound(int handle);

	//���y���~�߂�
	void StopSound(int handle);

	//���y�̃{�����[����ύX����
	//0�`10000
	void SetSoundVolume(long vol, int handle);

	//���y�̃{�����[�����擾����
	long GetSoundVolume(int handle);
}