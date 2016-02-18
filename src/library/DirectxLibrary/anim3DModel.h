#ifndef ANIM3DMODEL_H
#define ANIM3DMODEL_H

/**
 * @file anim3DModel.h
 * @author danjo
 */

/**
 * X�t�@�C������Ǎ��񂾃A�j���[�V�������b�V���̊Ǘ�
 */
class AnimModel {
public:
	// �A�j���[�V�������Ԋi�[�p
	typedef struct _ANIMLIST
	{
		double startTime;
		double endTime;
		bool   chancel;
	}ANIMLIST;

private:
	struct MYFRAME: public D3DXFRAME {
		D3DXMATRIX CombinedTransformationMatrix;
	};
	struct MYMESHCONTAINER: public D3DXMESHCONTAINER {
		LPDIRECT3DTEXTURE9*  ppTextures;
		DWORD dwWeight;							// �d�݂̌��i�d�݂Ƃ͒��_�ւ̉e���B�j
		DWORD dwBoneAmt;						// �{�[���̐�
		LPD3DXBUFFER pBoneBuffer;				// �{�[���E�e�[�u��
		D3DXMATRIX** ppBoneMatrix;				// �S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
		D3DXMATRIX* pBoneOffsetMatrices;		// �t���[���Ƃ��Ẵ{�[���̃��[���h�s��̃|�C���^�[
	};
	class MyHierarchy : public ID3DXAllocateHierarchy {
	private:
		void CreateTexture(MYMESHCONTAINER* pMeshContainer, LPDIRECT3DDEVICE9 pDevice, DWORD NumMaterials);
		void SetDefaultMaterial(MYMESHCONTAINER* pMeshContainer);
	public:
		MyHierarchy(){};
		~MyHierarchy(){};
		STDMETHOD(CreateFrame)(THIS_ LPCSTR , LPD3DXFRAME *);
		STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*, CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD*, LPD3DXSKININFO, LPD3DXMESHCONTAINER*);
		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
	};

	LPDIRECT3DDEVICE9			pDevice;										// Direct3D�f�o�C�X�I�u�W�F�N�g
	MyHierarchy					cHierarchy;										// �A���P�[�g�q�G�����L�[�I�u�W�F�N�g
	LPD3DXFRAME					pFrameRoot;										// �t���[��
	LPD3DXANIMATIONCONTROLLER	pAnimController;								// �A�j���[�V�����R���g���[��
	LPD3DXANIMATIONSET			pAnimSet[100];									// �A�j���[�V�����Z�b�g
	int							m_curAnimNo;									// ���݂̃A�j���[�V�����ԍ�

	double						m_AnimTime;										//
	std::vector<ANIMLIST>		m_animList;
	_D3DCOLORVALUE				m_color;									// ���b�V���̐F

public:

	/**
	 * @brief �R���X�g���N�^
	 * @remarks ���[�V�����t����X�t�@�C���̃��[�h �O�ŃX�P�[���������A�R���X�g���N�^�ɃZ�b�g���Ďg�p���Ă��������B
	 * @param filename �摜�t�@�C����
	 * @param pDevice	Direct3D�f�o�C�X�I�u�W�F�N�g
	 */
	AnimModel(LPCTSTR filename, LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 _scale);

	/// �f�X�g���N�^
	~AnimModel(void);

	/**
	 * @brief ���f���̕`��
	 * @remarks ���f���̕`�掞�ɉ�]�s��������ɗ^���Ăق���
	 * @param position �ʒu
	 * @param rotation ��]�s��
	 */
	void Draw(D3DXVECTOR3 position, D3DXMATRIX rotation);

	// �X�P�[�����Z�b�g
	void SetScale(D3DXVECTOR3 _vecScale);

	/**
	 * @brief �A�j���[�V�������Ԃ�i�s
	 * @remarks �K�[�f�B�A���Y�p�ɏ��������Ă����������폜�����̂Ŏg���₷���悤�ɉ��ǂ���K�v�����邩��
	 */
	double AdvanceTime(double time);

	/// ���[�V������؂�ւ���
	void ChangeMotion(int motion_number);

	// �A�j���[�V�����Đ����Ԃ��Z�b�g����
	void SetAnimList(std::vector<ANIMLIST>* _animList);

	// �t���[�����擾
	LPD3DXFRAME GetFrameRoot();

	void SetColor(float _a = 1.0f,float _r = 1.0f,float _g = 1.0f,float _b = 1.0f);	// �}�e���A���̐F���Z�b�g

	void Scalling(D3DXVECTOR3* _size,D3DXVECTOR3 _scale)							// �X�P�[�����Z�b�g
	{
		_size->x = _size->x * _scale.x;
		_size->y = _size->y * _scale.y;
		_size->z = _size->z * _scale.z;
	}
private:
	HRESULT AllocateBoneMatrix(LPD3DXMESHCONTAINER);							// ���b�V���ɍs�������U��
	HRESULT AllocateAllBoneMatrices(LPD3DXFRAME);								// �ċA�R�[�h�F�t���[���K�w��W�J���Ċe���b�V���ɍs�������U��

	D3DXVECTOR3		m_vecScale;
	void UpdateFrameMatrices(LPD3DXFRAME , LPD3DXMATRIX );						// �ċA�R�[�h�F�t���[���̃��[���h�ϊ�
	void RenderMeshContainer(LPDIRECT3DDEVICE9, MYMESHCONTAINER* ,MYFRAME* );	// ���b�V���R���e�i�̃����_�����O
	void DrawFrame(LPDIRECT3DDEVICE9,LPD3DXFRAME );								// �ċA�R�[�h�F�t���[���̃����_�����O
	void FreeAnim(LPD3DXFRAME pF);												// �ċA�R�[�h�F�S�Ẵ��b�V���R���e�i�������[�X
	void SetMaterial(MYMESHCONTAINER* pMeshContainer);
};

#endif /* ANIM3DMODEL_H */
