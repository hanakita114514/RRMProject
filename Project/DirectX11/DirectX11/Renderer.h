#pragma once

struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilView;

class Renderer
{
private:
	//�����_���[
	ID3D11RenderTargetView* _rtv;

	ID3D11Texture2D* _depthTexture2D;	//�[�x�p�e�N�X�`��
	ID3D11DepthStencilView* _dsv;	//�[�x�r���[

	Renderer();
	Renderer(const Renderer&);
	Renderer& operator = (const Renderer&);

	float _backColor[4];

public:
	~Renderer();

	static Renderer& Instance()
	{
		static Renderer instance;
		return instance;
	}

	bool Init();

	//Z�o�b�t�@�̐ݒ�
	//true �L�� false ����
	void SetZBuffer(bool flag);

	void BackGroundColor(int red, int green, int blue);

	void Clear();

	void DefaultBlend();
	void AlignmentBlend();
	void AddBlend();
	void SubtractBlend();
	void MultipleBlendDesc();

	//pal 0 �` 255�Ŏw��
	void AlphaBlend(int pal);

};

