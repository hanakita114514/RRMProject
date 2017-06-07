//行列用コンスタントバッファ
cbuffer cbuff : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;
};

//頂点情報構造体
struct Output
{
	float4 pos : SV_POSITION;	//システム座標をこっちに移動
	//float4 col : COLOR;			//色情報を含ませる
};

//頂点シェーダ
Output BaseVS(float4 pos : POSITION) : SV_POSITION
{
	Output output;

	matrix mat;
	mat = mul(proj, view);
	mat = mul(mat, world);

	output.pos = mul(mat, pos);

	return output;
}

//ピクセルシェーダ
float4 BasePS(Output output) : SV_Target
{
	return float4(output.pos.xyz, 1);
}