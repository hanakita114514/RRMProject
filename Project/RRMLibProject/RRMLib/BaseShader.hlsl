//�s��p�R���X�^���g�o�b�t�@
cbuffer cbuff : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;
};

//���_���\����
struct Output
{
	float4 pos : SV_POSITION;	//�V�X�e�����W���������Ɉړ�
	//float4 col : COLOR;			//�F�����܂܂���
};

//���_�V�F�[�_
Output BaseVS(float4 pos : POSITION) : SV_POSITION
{
	Output output;

	matrix mat;
	mat = mul(proj, view);
	mat = mul(mat, world);

	output.pos = mul(mat, pos);

	return output;
}

//�s�N�Z���V�F�[�_
float4 BasePS(Output output) : SV_Target
{
	return float4(output.pos.xyz, 1);
}