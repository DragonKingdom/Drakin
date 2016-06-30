//�n�ʂƓ��ɋ�̐F�̃t�H�O��K�p����B��̎��͔�

float4x4 WVPP;                //���[���h �~ �r���[ �~ �ˉe
float4 LightDir;              //���s�����̕����x�N�g��
float4 Ambient = 1.0f;       //����
float  CLUTTU;                //���z�̕����x�N�g���Ə�����x�N�g��[0.0f, 1.0f, 0.0f]�Ƃ̓���
float4 FogColor;              //�t�H�O�J���[
float  Param1;                //�t�H�O�̌v�Z���̃p�����[�^�P
float  Param2;                //�t�H�O�̌v�Z���̃p�����[�^�Q

sampler tex1 : register(s1);    //Pass1:���C�g�pCLUT�e�[�u��
sampler tex0 : register(s0);    //Pass1:�f�J�[���}�b�v

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

	//���C�g�̐F���J���[���b�N�A�b�v�e�[�u������擾
	float4 LightColor = tex2D(tex1, float2(CLUTTU, 0.0f));

		//�t�H�O�̎w���v�Z�ɂ��u�d�݁v���v�Z
		float f = pow(1.0f - pow(In.LocalPos.z / In.LocalPos.w, Param1), Param2);

	//�t�H�O��K������
	Out = tex2D(tex0, In.Tex) * In.Col * f + FogColor * (1.0f - f);

	//���C�g�̐F��K������
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
