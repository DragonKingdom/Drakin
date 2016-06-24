float4x4 m_WVPP;                //ワールド × ビュー × 射影
static float4 m_LightDir;              //平行光源の方向ベクトル
float4 m_Ambient = 1.0f;       //環境光
float  m_CLUTTU;                //太陽の方向ベクトルと上方向ベクトル[0.0f, 1.0f, 0.0f]との内積
float4 m_FogColor;              //フォグカラー
float  m_Param1;                //フォグの計算式のパラメータ１
float  m_Param2;                //フォグの計算式のパラメータ２
sampler tex0 : register(s0);    //Pass0:雲　　　　　　　　　Pass1:デカールマップ
sampler tex1 : register(s1);    //Pass0:空用のCLUTテーブル　Pass1:ライト用CLUTテーブル
sampler tex2 : register(s2);    //Pass0:星

//Pass0:空のレンダリング
struct VS0_OUTPUT
{
	float4 Pos    : POSITION;
	float2 Tex    : TEXCOORD0;
};

VS0_OUTPUT VS0(float4 Pos    : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS0_OUTPUT Out;

	Out.Pos = mul(Pos, m_WVPP);
	Out.Tex = Tex;
	return Out;
}

float4 PS0(VS0_OUTPUT In) : COLOR
{
	float4 Out;

	//空の色をCLUTテーブルから取得
	Out = tex2D(tex1, float2(m_CLUTTU, 0.0f));
	//Out *= tex2D(tex1, In.Tex);
	//雲テクスチャーを取得
	float4 Cloud = tex2D(tex0, float2(In.Tex.x, In.Tex.y));
	//加算合成
	Out = Cloud * Cloud.a + Out * 1;
	
	//Out = Cloud * Cloud.a + Out * 1;
	////星テクスチャーを取得
	//float4 Star = tex2D(tex2, In.Tex);
	//
	////雲、または星を空に適応する
	////昼間は雲を、夜は雲にさえぎられていない部分に星をレンダリングする感じ
	//Out += lerp(max(0.0f, Cloud), Cloud, Out.a);
	//Out += lerp(max(0.0f, Star - Cloud), Cloud, Out.a);

	return Out;
}

//Pass1:空以外のオブジェクトのレンダリング
struct VS1_OUTPUT
{
	float4 Pos      : POSITION;
	float4 Col      : COLOR0;
	float2 Tex      : TEXCOORD0;
	float4 LocalPos : TEXCOORD1;
};

VS1_OUTPUT VS1(float4 Pos    : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS1_OUTPUT Out;

	Out.Pos = mul(Pos, m_WVPP);

	float3 L = -m_LightDir.xyz;
	float3 N = normalize(Normal.xyz);
	Out.Col = max(m_Ambient, dot(N, L));
	Out.Tex = Tex;
	Out.LocalPos = Out.Pos;

	return Out;
}

float4 PS1(VS1_OUTPUT In) : COLOR0
{
	float4 Out;

	//ライトの色をカラールックアップテーブルから取得
	float4 LightColor = tex2D(tex1, float2(m_CLUTTU, 0.0f));

	//フォグの指数計算により「重み」を計算
	float f = pow(1.0f - pow(In.LocalPos.z / In.LocalPos.w, m_Param1), m_Param2);
	float4 tex = tex2D(tex0, In.Tex);
	//フォグを適応する
	Out = tex * In.Col * f + m_FogColor * (1.0f - f);

	//ライトの色を適応する
	Out *= LightColor;

	return Out;
}

technique TShader
{
	//空以外のオブジェクトのレンダリング
	pass P0
	{
		VertexShader = compile vs_1_1 VS0();
		PixelShader = compile ps_2_0 PS0();
	}

	pass P1
	{
		VertexShader = compile vs_1_1 VS1();
		PixelShader = compile ps_2_0 PS1();
	}
}
