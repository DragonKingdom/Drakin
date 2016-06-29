//�n�ʂƓ��ɋ�̐F�̃t�H�O��K�p����B��̎��͔�

float4x4 m_WVPP;                //���[���h �~ �r���[ �~ �ˉe
float4 m_LightDir;              //���s�����̕����x�N�g��
float4 m_Ambient = 1.0f;        //����
float  m_CLUTTU;                //���z�̕����x�N�g���Ə�����x�N�g��[0.0f, 1.0f, 0.0f]�Ƃ̓���
float4 m_FogColor;              //�t�H�O�J���[
float  m_Param1;                //�t�H�O�̌v�Z���̃p�����[�^�P
float  m_Param2;                //�t�H�O�̌v�Z���̃p�����[�^�Q

sampler ColorTexture : register(s0);    // Pass1:�f�J�[���}�b�v
sampler NormalTexture : register(s1);	// Pass1:�m�[�}���}�b�v
sampler LightTexture : register(s2);    // Pass1:���C�g�pCLUT�e�[�u��


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
	float4 LightDir : TEXCOORD2;	// �ڋ�Ԃɍ��킹��Light�̌���
};

struct PS_INPUT
{
	float2 Tex      : TEXCOORD0;
	float4 LocalPos : TEXCOORD1;
	float4 LightDir : TEXCOORD2;	// �ڋ�Ԃɍ��킹��Light�̌���
};

VS_OUTPUT vertexShader(VS_INPUT In)
{
	VS_OUTPUT Out;

	// �ڋ�Ԃ̍s����쐬
	float4x4 mat =
	{
		float4(In.Tangent),
		float4(In.Binormal),
		float4(In.Normal),
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};

	float4x4 invTangentMat = transpose(mat);  // �ϊ��̂��߂ɋt�s��ɂ���
	Out.LightDir = mul(float4(-m_LightDir.xyz, 1.0), invTangentMat);	// �t�s��������邱�ƂŃ��C�g��ڋ�ԂɎ����Ă���

	Out.Pos = mul(In.Pos, m_WVPP);
	Out.Tex = In.Tex;
	Out.LocalPos = Out.Pos;

	return Out;
}

float4 pixelShader(PS_INPUT In) : COLOR0
{
	float4 OutColor;


	// �m�[�}���}�b�v�̐F���Q�Ƃ��Č������擾����
	float3 NormalMapColor = tex2D(NormalTexture, In.Tex);
	float3 NormalVec = 2.0f * NormalMapColor - 1.0f;


	// �@���ƃ��C�g�̓��ς��Ƃ��āA���ɂǂꂭ�炢�������Ă邩���Ƃ�
	// max�֐��ōŒ�l���w�肷�邪�A���̒l�ŉA�e��������x���߂ł���
	float3 bright = max(0.3f, dot(normalize(In.LightDir), normalize(NormalVec)));
	float4 diffuseColor = tex2D(ColorTexture, In.Tex);		// ���ʂɃJ���[�e�N�X�`������F���E���Ă���

	// �}�e���A���̃A���r�G���g���v�Z�ɓ���Ƃ�
	float4 Col = max(m_Ambient, float4(bright, 1.0f));

	//���C�g�̐F���J���[���b�N�A�b�v�e�[�u������擾
	float4 LightColor = tex2D(LightTexture, float2(m_CLUTTU, 0.0f));

	//�t�H�O�̎w���v�Z�ɂ��u�d�݁v���v�Z
	float f = pow(1.0f - pow(In.LocalPos.z / In.LocalPos.w, m_Param1), m_Param2);

	//�t�H�O��K������
	OutColor = float4(bright * diffuseColor.xyz, 1.0f) * Col * f + m_FogColor * (1.0f - f);

	//���C�g�̐F��K������
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
