//地面と道に空の色のフォグを適用する。青空の時は白

float4x4 m_WVPP;                //ワールド × ビュー × 射影
float4 m_LightDir;              //平行光源の方向ベクトル
float4 m_Ambient = 1.0f;       //環境光
float  m_CLUTTU;                //太陽の方向ベクトルと上方向ベクトル[0.0f, 1.0f, 0.0f]との内積
float4 m_FogColor;              //フォグカラー
float  m_Param1;                //フォグの計算式のパラメータ１
float  m_Param2;                //フォグの計算式のパラメータ２

sampler tex1 : register(s1);    //Pass1:ライト用CLUTテーブル
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

	Out.Pos = mul(Pos, m_WVPP);

	float3 L = -m_LightDir.xyz;
		float3 N = normalize(Normal.xyz);
		Out.Col = max(m_Ambient, dot(N, L));
	Out.Tex = Tex;
	Out.LocalPos = Out.Pos;

	return Out;
}

float4 pixelShader(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	//ライトの色をカラールックアップテーブルから取得
	float4 LightColor = tex2D(tex1, float2(m_CLUTTU, 0.0f));

		//フォグの指数計算により「重み」を計算
		float f = pow(1.0f - pow(In.LocalPos.z / In.LocalPos.w, m_Param1), m_Param2);

	//フォグを適応する
	Out = tex2D(tex0, In.Tex) * In.Col * f + m_FogColor * (1.0f - f);

	//ライトの色を適応する
	Out *= LightColor;

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
