#include "stdafx.h"

#include "Model.h"
#include "graphicsDevice.h"

/**
 * コンストラクタ
 * @param _fileName ファイル名        
 * @param _pDevice 描画デバイス
 */
Model::Model(LPCTSTR _fileName) : m_angle(D3DXVECTOR3(0,0,0)) , m_pDevice(GraphicsDevice::getInstance().GetDevice())
{
	// マテリアル情報を格納する領域を宣言
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	
	// ファイル読み込み
	if ( FAILED( D3DXLoadMeshFromX(_fileName, D3DXMESH_MANAGED, m_pDevice, NULL, &pD3DXMtrlBuffer, NULL, &m_NumMaterials, &m_pMesh) ) ) // &がついてるものが必要情報
		throw TEXT("ファイル読み込み失敗");

		   D3DXCreateEffectFromFile(
		   m_pDevice,
		  TEXT("Effect00.fx"),
		  NULL,
		  NULL,
		  D3DXSHADER_DEBUG,
		  NULL,
		  &m_pEffect,
		  NULL
		  );
	// 必要なマテリアル情報を取得
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	m_materials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	// マテリアルとテクスチャ情報を格納する領域を数分生成
	m_pMeshMaterials = new D3DMATERIAL9[m_NumMaterials];
	m_pTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
	// それぞれの情報を格納
	for( DWORD i = 0; i < m_NumMaterials; i++ ){
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		m_pMeshMaterials[i].Diffuse.a = 1.0f;
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;

		m_pTextures[i] = NULL;

		// テクスチャファイル名をUNICODEに対応
		char str[256] = {0};
		// ファイル名が存在していたら一旦キャラ型にコピー
		if( d3dxMaterials[i].pTextureFilename ) strcpy_s( str, d3dxMaterials[i].pTextureFilename);
		TCHAR textureFileName[256] = {0};
		#ifdef UNICODE 
		MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, str, strlen(str), textureFileName, (sizeof(textureFileName)/2 ) );
		#else
		strcpy_s(textureFileName, str);
		#endif	
		D3D_OK;
		HRESULT a;
		//// テクスチャが割り当てられているかチェック
		if( textureFileName && lstrlen(textureFileName) > 0 ){
			// テクスチャ読み込み
			if( FAILED( a =  D3DXCreateTextureFromFileEx( m_pDevice, textureFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &m_pTextures[i]) ) )
				throw TEXT("テクスチャの読み込みに失敗");
		}
	}
	//if( m_pMesh != NULL)
	//{
	//	// バウンディングボックス計算
	//	DWORD VertexCnt = m_pMesh->GetNumVertices(); // 頂点数
	//	DWORD VertexSize = m_pMesh->GetNumBytesPerVertex(); // １つの頂点のサイズ
	//	BYTE *p;
	//	// 頂点バッファをロックし、頂点の先頭アドレス取得
	//	HRESULT hr = m_pMesh->LockVertexBuffer(D3DLOCK_READONLY,(LPVOID*)&p);
	//	if(SUCCEEDED(hr)){
	//		// バウンディングボックスを算出
	//		D3DXComputeBoundingBox( (D3DXVECTOR3*)p,
	//		VertexCnt,
	//		VertexSize,
	//		&m_min,
	//		&m_max);
	//		m_length = m_max - m_min;
	//		// 頂点バッファをアンロック
	//		m_pMesh->UnlockVertexBuffer();
	//	}
	//}

	//一時データを解放
	SAFE_RELEASE( pD3DXMtrlBuffer );
}

/**
 * デストラクタ（モデルの解放）
 */
Model::~Model()
{
	SAFE_RELEASE(m_pMesh);    // メッシュ解放
	for( DWORD i = 0; i < m_NumMaterials; i++ ){  // テクスチャ解放
		SAFE_RELEASE(m_pTextures[i]);
	}
	SAFE_DELETE(m_pTextures);
	SAFE_DELETE(m_pMeshMaterials);   // マテリアル解放
}
void Model::Draw(D3DXVECTOR3 _position)
{
	static float f=0.0f;
	f+=0.025f;
	D3DXMATRIX mat,world;
	D3DXMATRIX rot,View,Proj;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&world);
	m_pDevice->GetTransform(D3DTS_VIEW,&View);
	m_pDevice->GetTransform(D3DTS_PROJECTION,&Proj);
  // D3DXMatrixPerspectiveFovLH( &Proj, D3DXToRadian(45), 640.0f/480.0f, 1.0f, 1000.0f);
       //D3DXMatrixLookAtLH( &View, &D3DXVECTOR3(30*sin(f),20,-30*cos(f)), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,1,0) );
	//mat = world * View;
	//mat = mat * Proj;
	mat = mat * View * Proj;
	m_pEffect->SetMatrix( "matWorldViewProj", &mat );
	// 描画開始
	m_pEffect->SetTechnique( "BasicTec" );
	UINT numPass;
	m_pEffect->Begin( &numPass, 0);
	m_pEffect->BeginPass(0);
	//D3DXMATRIX matWorld, matTrans, matScale, matRotate;

	//D3DXMatrixIdentity(&matRotate);
	//D3DXMatrixRotationYawPitchRoll(&matRotate, D3DXToRadian(m_angle.y), D3DXToRadian(m_angle.x), D3DXToRadian(m_angle.z));

	//D3DXMatrixScaling(&matScale,m_vecScale.x,m_vecScale.y,m_vecScale.z);
	////移動のためのマトリックス
	//D3DXMatrixTranslation(&matTrans, _position.x, _position.y, _position.z);
	//// ワールドマトリックスの設定
	//D3DXMatrixIdentity(&matWorld);
	//matWorld = matScale * matRotate * matTrans;
	//// ワールド行列を登録
	//m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
		// モデルの描画
	for( DWORD i = 0; i < m_NumMaterials; i++ ){
		//m_pMeshMaterials[i].Ambient.a = 1.0f;
		//m_pMeshMaterials[i].Ambient.r =
		//m_pMeshMaterials[i].Ambient.g =
		//m_pMeshMaterials[i].Ambient.b = 1.0f;

		//m_pMeshMaterials[i].Diffuse = m_pMeshMaterials[i].Emissive = 
		//	m_pMeshMaterials[i].Specular = m_pMeshMaterials[i].Ambient;
		//m_pDevice->SetMaterial(&(m_materials[i].MatD3D));
		m_pDevice->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
	m_pEffect->EndPass();
	m_pEffect->End();
}
/**
 * モデルの描画
 * @param _position 表示位置      
 * @param _matrix 回転行列   
 */
void Model::Draw(D3DXVECTOR3 _position,D3DXMATRIX _attitude)
{
	D3DXMATRIX matWorld = _attitude, matTrans, matScale;

	D3DXMatrixScaling(&matScale,m_vecScale.x,m_vecScale.y,m_vecScale.z);
	//移動のためのマトリックス
	D3DXMatrixTranslation(&matTrans, _position.x, _position.y, _position.z);
	// ワールドマトリックスの設定
	D3DXMatrixIdentity(&matWorld);
	matWorld = matScale * _attitude * matTrans;

	// ワールド行列を登録
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// アルファブレンドを有効にする
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ポリゴンの透明度をテクスチャに反映
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// モデルの描画
	for( DWORD i = 0; i < m_NumMaterials; i++ ){
		m_pMeshMaterials[i].Ambient.a = 1.0f;
		m_pMeshMaterials[i].Ambient.r =
		m_pMeshMaterials[i].Ambient.g =
		m_pMeshMaterials[i].Ambient.b = 1.0f;

		m_pMeshMaterials[i].Diffuse = m_pMeshMaterials[i].Emissive = 
			m_pMeshMaterials[i].Specular = m_pMeshMaterials[i].Ambient;
		m_pDevice->SetMaterial(&m_pMeshMaterials[i]);
		m_pDevice->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
}
void Model::SetScale(D3DXVECTOR3 _vecScale)
{
	m_vecScale = _vecScale;
}
void Model::SetPosition(D3DXVECTOR3 _position)
{
	m_position = _position;
}
void Model::SetAngle(D3DXVECTOR3 _angle)
{
	m_angle = _angle;
}
void Model::GetMeshSize(D3DXVECTOR3* _min,D3DXVECTOR3* _max)
{
	*_min = m_min;
	*_max = m_max;
}
void Model::SetColor(float _a,float _r,float _g,float _b)
{
	m_color.a = _a;
	m_color.r = _r;
	m_color.g = _g;
	m_color.b = _b;
}
