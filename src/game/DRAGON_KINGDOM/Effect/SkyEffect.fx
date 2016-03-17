// ワールドビュー射影変換行列
float4x4 matWorldViewProj;

// 太陽の方向ベクトルと上方向ベクトル[0.0f, 1.0f, 0.0f]との内積
float  DotProduct;

sampler tex0 : register(s0);

struct VS0_OUTPUT
{
	float4 Pos    : POSITION;
	float2 Tex    : TEXCOORD0;
};


// 頂点シェーダ
VS0_OUTPUT VSFunc(
	float4 Pos    : POSITION,
	float4 Normal : NORMAL,
	float2 Tex	  : TEXCOORD)
{
	VS0_OUTPUT Out;

	Out.Pos = mul(Pos, matWorldViewProj);
	Out.Tex = Tex;

	return Out;
}

// ピクセルシェーダ
float4 PSFunc(VS0_OUTPUT In) : COLOR
{
	float4 Out;

	// 空の色をテクスチャから取得する
	Out = tex2D(tex0, float2(DotProduct, 0.0f));

	return Out;
}


technique SkyEffect
{
	pass P0
	{
		//compile vs_2_0はvs_2_0でコンパイルするという指定
		VertexShader = compile vs_2_0 VSFunc();
		PixelShader = compile ps_2_0 PSFunc();
	}
}
