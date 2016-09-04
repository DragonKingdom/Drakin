float4x4 WVPP;                //ワールド × ビュー × 射影
float4 LightDir;              //平行光源の方向ベクトル
float4 Ambient = 1.0f;       //環境光
float  CLUTTU;                //太陽の方向ベクトルと上方向ベクトル[0.0f, 1.0f, 0.0f]との内積
float4 FogColor;              //フォグカラー
float  Param1;                //フォグの計算式のパラメータ１
float  Param2;                //フォグの計算式のパラメータ２

sampler tex1 : register(s2);    //Pass1:ライト用CLUTテーブル
sampler tex0 : register(s0);    //Pass1:デカールマップ

struct VS_OUTPUT
{
	float4 Pos      : POSITION;
	float4 Col      : COLOR0;
	float2 Tex      : TEXCOORD0;
	float4 LocalPos : TEXCOORD1;
};

VS_OUTPUT vertexShader(float4 Pos    : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	Out.Pos = mul(Pos, WVPP);

	float3 L = -LightDir.xyz;
	float3 N = normalize(Normal.xyz);
	Out.Col = max(Ambient, dot(N, L));
	Out.Tex = Tex;
	Out.LocalPos = Out.Pos;

	return Out;
}

float4 pixelShader(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	float4 LightColor = tex2D(tex1, float2(CLUTTU, 0.0f));

	float f = pow(1.0f - pow(In.LocalPos.z / In.LocalPos.w, Param1), Param2);

	Out = tex2D(tex0, In.Tex) * In.Col * f + FogColor * (1.0f - f);

	Out *= LightColor;

	return Out;
}

technique HumanEffect
{
	pass P0
	{
		VertexShader = compile vs_1_1 vertexShader();
		PixelShader = compile ps_2_0 pixelShader();
	}
}
