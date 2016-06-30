float4x4 WVPP;                //ワールド × ビュー × 射影
float  CLUTTU;                //太陽の方向ベクトルと上方向ベクトル[0.0f, 1.0f, 0.0f]との内積

sampler tex0 : register(s0);    //雲　　　　　　　　
sampler tex1 : register(s1);    //空用のCLUTテーブル
//Pass0:空のレンダリング
struct VS_OUTPUT
{
	float4 Pos    : POSITION;
	float2 Tex    : TEXCOORD0;
};

VS_OUTPUT vertexShader(float4 Pos    : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	Out.Pos = mul(Pos, WVPP);
	Out.Tex = Tex;
	return Out;
}

float4 pixelShader(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	//空の色をCLUTテーブルから取得
	Out = tex2D(tex1, float2(CLUTTU, 0.0f));
	//雲テクスチャーを取得
	float4 Cloud = tex2D(tex0, float2(In.Tex.x, In.Tex.y));
	//加算合成
	Out = Cloud * Cloud.a + Out * 1;

	return Out;
}
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_1_1 vertexShader();
		PixelShader = compile ps_2_0 pixelShader();
	}
}
