struct Output
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};

//�s��p�R���X�^���g�o�b�t�@
cbuffer cbuff : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;
};

//�F�p�R���X�^���g�o�b�t�@
cbuffer cbuff : register(b1)
{
	unsigned int col;	//r, g, b, a
}

Texture2D tex : register(t0);
SamplerState sample;


//2D���_�V�F�[�_
Output VertexShader2D(float4 pos : SV_POSITION, float2 uv : TEXCOORD)
{
	Output output;

	output.pos = pos;

	output.uv = uv;

	return output;
}

//3D���_�V�F�[�_
Output VertexShader3D(float4 pos : SV_POSITION, float2 uv : TEXCOORD)
{
	Output output;

	output.pos = mul(world, pos);

	output.uv = uv;

	return output;
}

//�s�N�Z���V�F�[�_
float4 PicturePS(Output output) : SV_Target
{
	float4 color = tex.Sample(sample, output.uv);

	if (color.a == 0)
	{
		//discard;
	}

	return float4(color.r, color.g, color.b, color.a);
}

//�}�`�p
float4 GeometryPS(Output output) : SV_Target
{
	float4 color;
color.r = (col & 0xff000000) / 255;
color.g = (col & 0x00ff0000) / 255;
color.b = (col & 0x0000ff00) / 255;
color.a = (col & 0x000000ff) / 255;

return float4(color.r, color.g, color.b, 1);
}