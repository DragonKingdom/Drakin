float4x4 m_WVPP;                //���[���h �~ �r���[ �~ �ˉe
static float4 m_LightDir;              //���s�����̕����x�N�g��
float4 m_Ambient = 1.0f;       //����
float  m_CLUTTU;                //���z�̕����x�N�g���Ə�����x�N�g��[0.0f, 1.0f, 0.0f]�Ƃ̓���
float4 m_FogColor;              //�t�H�O�J���[
float  m_Param1;                //�t�H�O�̌v�Z���̃p�����[�^�P
float  m_Param2;                //�t�H�O�̌v�Z���̃p�����[�^�Q
sampler tex0 : register(s0);    //Pass0:�_�@�@�@�@�@�@�@�@�@Pass1:�f�J�[���}�b�v
sampler tex1 : register(s1);    //Pass0:��p��CLUT�e�[�u���@Pass1:���C�g�pCLUT�e�[�u��
sampler tex2 : register(s2);    //Pass0:��

//Pass0:��̃����_�����O
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

	//��̐F��CLUT�e�[�u������擾
	Out = tex2D(tex1, float2(m_CLUTTU, 0.0f));
	//Out *= tex2D(tex1, In.Tex);
	//�_�e�N�X�`���[���擾
	float4 Cloud = tex2D(tex0, float2(In.Tex.x, In.Tex.y));
	//���Z����
	Out = Cloud * Cloud.a + Out * 1;
	
	//Out = Cloud * Cloud.a + Out * 1;
	////���e�N�X�`���[���擾
	//float4 Star = tex2D(tex2, In.Tex);
	//
	////�_�A�܂��͐�����ɓK������
	////���Ԃ͉_���A��͉_�ɂ��������Ă��Ȃ������ɐ��������_�����O���銴��
	//Out += lerp(max(0.0f, Cloud), Cloud, Out.a);
	//Out += lerp(max(0.0f, Star - Cloud), Cloud, Out.a);

	return Out;
}

//Pass1:��ȊO�̃I�u�W�F�N�g�̃����_�����O
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

	//���C�g�̐F���J���[���b�N�A�b�v�e�[�u������擾
	float4 LightColor = tex2D(tex1, float2(m_CLUTTU, 0.0f));

	//�t�H�O�̎w���v�Z�ɂ��u�d�݁v���v�Z
	float f = pow(1.0f - pow(In.LocalPos.z / In.LocalPos.w, m_Param1), m_Param2);
	float4 tex = tex2D(tex0, In.Tex);
	//�t�H�O��K������
	Out = tex * In.Col * f + m_FogColor * (1.0f - f);

	//���C�g�̐F��K������
	Out *= LightColor;

	return Out;
}

technique TShader
{
	//��ȊO�̃I�u�W�F�N�g�̃����_�����O
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
