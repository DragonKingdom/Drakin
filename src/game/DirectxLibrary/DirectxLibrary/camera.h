#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
private:
	LPDIRECT3DDEVICE9 m_pDevice;

	D3DXMATRIX m_InitMatView;
	D3DXMATRIX m_InitMatProj;
public:
	Camera();
	~Camera();
	void Look(D3DXVECTOR3 _eyePos, D3DXVECTOR3 _lookAtPos);
};

#endif /* CAMERA_H */
