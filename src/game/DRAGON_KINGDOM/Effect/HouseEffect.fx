//地面と道に空の色のフォグを適用する。青空の時は白

float4x4 m_WVPP;                //ワールド × ビュー × 射影
float4 m_LightDir;              //平行光源の方向ベクトル
float4 m_Ambient = 1.0f;        //環境光
float  m_CLUTTU;                //太陽の方向ベクトルと上方向ベクトル[0.0f, 1.0f, 0.0f]との内積
float4 m_FogColor;              //フォグカラー
float  m_Param1;                //フォグの計算式のパラメータ１
float  m_Param2;                //フォグの計算式のパラメータ２

sampler ColorTexture : register(s0);    // Pass1:デカールマップ
sampler NormalTexture : register(s1);	// Pass1:ノーマルマップ
sampler LightTexture : register(s2);    // Pass1:ライト用CLUTテーブル


struct VS_INPUT
{
	float4 Pos		: POSITION;
	float4 Normal	: NORMAL;
	float4 Tangent	: TANGENT0;
	float4 Binormal	: BINORMAL0;
	float2 Tex		: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Pos      : POSITION;
	float2 Tex      : TEXCOORD0;
	float4 LocalPos : TEXCOORD1;
	float4 LightDir : TEXCOORD2;	// 接空間に合わせたLightの向き
};

struct PS_INPUT
{
	float2 Tex      : TEXCOORD0;
	float4 LocalPos : TEXCOORD1;
	float4 LightDir : TEXCOORD2;	// 接空間に合わせたLightの向き
};

VS_OUTPUT vertexShader(VS_INPUT In)
{
	VS_OUTPUT Out;

	// 接空間の行列を作成
	float4x4 mat =
	{
		float4(In.Tangent),
		float4(In.Binormal),
		float4(In.Normal),
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};

	float4x4 invTangentMat = transpose(mat);  // 変換のために逆行列にする
	Out.LightDir = mul(float4(-m_LightDir.xyz, 1.0), invTangentMat);	// 逆行列をかけることでライトを接空間に持ってくる

	Out.Pos = mul(In.Pos, m_WVPP);
	Out.Tex = In.Tex;
	Out.LocalPos = Out.Pos;

	return Out;
}

float4 pixelShader(PS_INPUT In) : COLOR0
{
	float4 OutColor;


	// ノーマルマップの色を参照して向きを取得する
	float3 NormalMapColor = tex2D(NormalTexture, In.Tex);
	float3 NormalVec = 2.0f * NormalMapColor - 1.0f;


	// 法線とライトの内積をとって、光にどれくらい当たってるかをとる
	// max関数で最低値を指定するが、その値で陰影をある程度調節できる
	float3 bright = max(0.3f, dot(normalize(In.LightDir), normalize(NormalVec)));
	float4 diffuseColor = tex2D(ColorTexture, In.Tex);		// 普通にカラーテクスチャから色を拾ってくる

	// マテリアルのアンビエントも計算に入れとく
	float4 Col = max(m_Ambient, float4(bright, 1.0f));

	//ライトの色をカラールックアップテーブルから取得
	float4 LightColor = tex2D(LightTexture, float2(m_CLUTTU, 0.0f));

	//フォグの指数計算により「重み」を計算
	float f = pow(1.0f - pow(In.LocalPos.z / In.LocalPos.w, m_Param1), m_Param2);

	//フォグを適応する
	OutColor = float4(bright * diffuseColor.xyz, 1.0f) * Col * f + m_FogColor * (1.0f - f);

	//ライトの色を適応する
	OutColor *= LightColor;

	return OutColor;
}

technique TShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 vertexShader();
		PixelShader = compile ps_2_0 pixelShader();
	}
}
