#pragma once

#include <Windows.h>
#include "WindowControl.h"

//DirectX �v���ƃ^�C�v�錾
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RasterizerState;

class DeviceDx11
{
private:
	HWND _hwnd;
	IDXGISwapChain* _swapchain;
	ID3D11Device* _device;
	ID3D11DeviceContext* _context;

	//�J�����OON/OFF�̂��߂̃��X�^���C�U�[�X�e�[�g
	ID3D11RasterizerState* _cullingOnState;		//���ʔ�`��
	ID3D11RasterizerState* _cullingOffState;	//���ʕ`��

												//�V���O���g���Ȃ̂ŃR���X�g���N�^��private��
	DeviceDx11();
	//�R�s�[�A������֎~
	DeviceDx11(const DeviceDx11&);
	DeviceDx11& operator=(const DeviceDx11&);

public:
	~DeviceDx11();

	//�C���X�^���X��Ԃ�
	static DeviceDx11& Instance()
	{
		static DeviceDx11 instance;

		return instance;
	}

	//DirectX�̏�����
	HRESULT Init(WindowControl& wc);

	//�f�o�C�X�̍Đݒ�
	HRESULT Reset(WindowControl& wc);

	//�f�o�C�X�֘A�̃A�N�Z�T���
	IDXGISwapChain* SwapChain();	//_swapchain��Ԃ�
	ID3D11Device* Device();	//_device��Ԃ�
	ID3D11DeviceContext* Context(); //

	//�I������
	void Terminate();

									//�J�����O��ON/OFF��؂�ւ���
									//flg true�̂Ƃ��J�����OON, false�̂Ƃ��J�����OOFF
	void SetCullingFlg(bool flg);

	HWND WindowHandle();
};

