// ���[���h�r���[�ˉe�ϊ��s��
float4x4 matWorldViewProj;

// ���z�̕����x�N�g���Ə�����x�N�g��[0.0f, 1.0f, 0.0f]�Ƃ̓���
float  DotProduct;

sampler tex0 : register(s0);

struct VS0_OUTPUT
{
	float4 Pos    : POSITION;
	float2 Tex    : TEXCOORD0;
};


// ���_�V�F�[�_
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

// �s�N�Z���V�F�[�_
float4 PSFunc(VS0_OUTPUT In) : COLOR
{
	float4 Out;

	// ��̐F���e�N�X�`������擾����
	Out = tex2D(tex0, float2(DotProduct, 0.0f));

	return Out;
}


technique SkyEffect
{
	pass P0
	{
		//compile vs_2_0��vs_2_0�ŃR���p�C������Ƃ����w��
		VertexShader = compile vs_2_0 VSFunc();
		PixelShader = compile ps_2_0 PSFunc();
	}
}
