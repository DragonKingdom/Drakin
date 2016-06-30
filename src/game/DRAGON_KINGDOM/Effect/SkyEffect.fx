float4x4 WVPP;                //���[���h �~ �r���[ �~ �ˉe
float  CLUTTU;                //���z�̕����x�N�g���Ə�����x�N�g��[0.0f, 1.0f, 0.0f]�Ƃ̓���

sampler tex0 : register(s0);    //�_�@�@�@�@�@�@�@�@
sampler tex1 : register(s1);    //��p��CLUT�e�[�u��
//Pass0:��̃����_�����O
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

	//��̐F��CLUT�e�[�u������擾
	Out = tex2D(tex1, float2(CLUTTU, 0.0f));
	//�_�e�N�X�`���[���擾
	float4 Cloud = tex2D(tex0, float2(In.Tex.x, In.Tex.y));
	//���Z����
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
