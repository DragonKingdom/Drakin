#include "stdafx.h"

#include "anim3DModel.h"
#include "graphicsDevice.h"

/*-----------------------------------------------------------------------------------------

	スキンメッシュ読み込み

------------------------------------------------------------------------------------------*/

AnimModel::AnimModel(LPCTSTR filename,D3DXVECTOR3 _scale) : pDevice(GraphicsDevice::getInstance().GetDevice()),m_vecScale(_scale),m_curAnimNo(0),m_AnimTime(0) {
	m_color.a = m_color.r = m_color.g = m_color.b = 1.0f;

	if (FAILED(D3DXLoadMeshHierarchyFromX(filename, D3DXMESH_MANAGED, pDevice, &cHierarchy, NULL, &pFrameRoot, &pAnimController))) throw TEXT("Xファイルの読み込みに失敗しました");
	for(DWORD i = 0; i < pAnimController->GetNumAnimationSets(); ++i) {	//アニメーショントラックを得る
		D3DXTRACK_DESC TrackDesc;
		ZeroMemory(&TrackDesc,sizeof(TrackDesc));
		TrackDesc.Weight = 1;
		TrackDesc.Speed = 1;
		TrackDesc.Enable = 1;
		pAnimController->SetTrackDesc(i, &TrackDesc);
		pAnimController->GetAnimationSet(i, &pAnimSet[i]);
//		pAnimController->SetTrackAnimationSet(i, pAnimSet[i]);
	}
	AllocateAllBoneMatrices(pFrameRoot);
}

AnimModel::~AnimModel() {
	FreeAnim(pFrameRoot);
	cHierarchy.DestroyFrame(pFrameRoot);
	SAFE_RELEASE( pAnimController);
}
///// アニメーションメッシュ /////
HRESULT AnimModel::MyHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame) {
    HRESULT hr = S_OK;
    MYFRAME *pFrame;
    *ppNewFrame = NULL;
    pFrame = new MYFRAME;
    if (!pFrame) return E_OUTOFMEMORY;
	pFrame->Name = (LPSTR)(new TCHAR[strlen(Name) + 1]);	
    if (!pFrame->Name) return E_FAIL;
	strcpy_s(pFrame->Name, strlen(Name) + 1, Name);
    D3DXMatrixIdentity(&pFrame->TransformationMatrix);
    D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
    pFrame->pMeshContainer = NULL;
    pFrame->pFrameSibling = NULL;
    pFrame->pFrameFirstChild = NULL;
    *ppNewFrame = pFrame;
    return S_OK;
}

void AnimModel::MyHierarchy::CreateTexture(MYMESHCONTAINER* pMeshContainer, LPDIRECT3DDEVICE9 pDevice, DWORD NumMaterials) {
	for (DWORD iMaterial = 0; iMaterial < NumMaterials; ++iMaterial) {
		if (pMeshContainer->pMaterials[iMaterial].pTextureFilename) {
			// テクスチャファイル名のUnicode対応
			TCHAR strTexturePath[MAX_PATH] = {0};
#ifdef UNICODE
			MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, pMeshContainer->pMaterials[iMaterial].pTextureFilename, strlen(pMeshContainer->pMaterials[iMaterial].pTextureFilename), strTexturePath, (sizeof strTexturePath)/2);
#else
			strcpy_s(strTexturePath, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
#endif
			if(FAILED( D3DXCreateTextureFromFile(pDevice, strTexturePath, &pMeshContainer->ppTextures[iMaterial]))) pMeshContainer->ppTextures[iMaterial] = NULL;
			pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
		}
	}
}

void AnimModel::MyHierarchy::SetDefaultMaterial(MYMESHCONTAINER* pMeshContainer) {
	pMeshContainer->pMaterials[0].pTextureFilename = NULL;
	memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
	pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
}

HRESULT AnimModel::MyHierarchy::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA* pMeshData, CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE* pEffectInstances, DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER *ppMeshContainer) {
    MYMESHCONTAINER *pMeshContainer = NULL;
    INT iFacesAmount;
    LPDIRECT3DDEVICE9 pDevice = NULL;
    LPD3DXMESH pMesh = NULL;
    *ppMeshContainer = NULL;
	DWORD dwBoneAmt=0;
    pMesh = pMeshData->pMesh;
    pMeshContainer = new MYMESHCONTAINER;
    if (!pMeshContainer) return E_OUTOFMEMORY;

    ZeroMemory(pMeshContainer, sizeof(MYMESHCONTAINER));
	pMeshContainer->Name = (LPSTR)(new TCHAR[strlen(Name) + 1]);	
    if (!pMeshContainer->Name) return E_FAIL;
	strcpy_s((char*)pMeshContainer->Name, strlen(Name) + 1, Name);
    pMesh->GetDevice(&pDevice);
    iFacesAmount = pMesh->GetNumFaces();  
	pMeshContainer->MeshData.pMesh = pMesh;
	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
    pMeshContainer->NumMaterials = max(1, NumMaterials);
    pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
    pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
    pMeshContainer->pAdjacency = new DWORD[iFacesAmount*3];
    if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL)) return E_FAIL;
    memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * iFacesAmount*3);
    memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9)*pMeshContainer->NumMaterials);
    if (NumMaterials > 0) {
        memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL)*NumMaterials);
		CreateTexture(pMeshContainer, pDevice, NumMaterials);
    }
    else SetDefaultMaterial(pMeshContainer);
	if (pSkinInfo) {			//当該メッシュがスキン情報を持っている場合（スキンメッシュ固有の処理）
		pMeshContainer->pSkinInfo = pSkinInfo;
        pSkinInfo->AddRef();
		dwBoneAmt = pSkinInfo->GetNumBones();
		pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[dwBoneAmt];
		for (DWORD i = 0; i < dwBoneAmt; ++i) memcpy(&pMeshContainer->pBoneOffsetMatrices[i], pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DMATRIX));
		if(FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(pMesh, NULL, pMeshContainer->pAdjacency, NULL, NULL, NULL, &pMeshContainer->dwWeight, &pMeshContainer->dwBoneAmt, &pMeshContainer->pBoneBuffer, &pMeshContainer->MeshData.pMesh))) return E_FAIL;
	}
	*ppMeshContainer = pMeshContainer;
	SAFE_RELEASE(pDevice);
    return S_OK;
}

HRESULT AnimModel::MyHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	 SAFE_DELETE_ARRAY(pFrameToFree->Name);

	 if( pFrameToFree->pFrameSibling )
	  DestroyFrame( pFrameToFree->pFrameSibling );
	 if( pFrameToFree->pFrameFirstChild )
	  DestroyFrame( pFrameToFree->pFrameFirstChild );
   
	 SAFE_DELETE(pFrameToFree);
	 return S_OK;
}

HRESULT AnimModel::MyHierarchy::DestroyMeshContainer(
	 LPD3DXMESHCONTAINER pMeshContainerBase)
{
	 DWORD material;
	 MYMESHCONTAINER* p = (MYMESHCONTAINER*)pMeshContainerBase;
	 SAFE_DELETE_ARRAY(p->Name);
	 SAFE_RELEASE(p->MeshData.pMesh);
	 SAFE_DELETE_ARRAY(p->pMaterials);
	 SAFE_DELETE_ARRAY(p->pAdjacency);

	 SAFE_RELEASE(p->pSkinInfo);
 
	 SAFE_DELETE_ARRAY(p->ppBoneMatrix);
	 if( p->ppTextures ) {
		for( material = 0; material < p->NumMaterials; material++ ) {
			SAFE_RELEASE(p->ppTextures[material]);
		}
	 }
	 SAFE_DELETE(p->ppTextures);
	 SAFE_RELEASE(p->pBoneBuffer);
	 SAFE_DELETE_ARRAY(p->pBoneOffsetMatrices);
	 SAFE_DELETE_ARRAY(p->ppBoneMatrix);
	 SAFE_DELETE(p);
	 return S_OK;
}



void AnimModel::FreeAnim(LPD3DXFRAME pF) {
	if (pF->pMeshContainer) cHierarchy.DestroyMeshContainer(pF->pMeshContainer);
    if (pF->pFrameSibling) FreeAnim(pF->pFrameSibling);
    if (pF->pFrameFirstChild) FreeAnim(pF->pFrameFirstChild);
}

HRESULT AnimModel::AllocateBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase) {
    MYFRAME *pFrame = NULL;
	DWORD dwBoneAmt = 0;

    MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
    if (!pMeshContainer->pSkinInfo) return S_OK;
	dwBoneAmt = pMeshContainer->pSkinInfo->GetNumBones();
    pMeshContainer->ppBoneMatrix = new D3DXMATRIX*[dwBoneAmt];
    for (DWORD i = 0; i < dwBoneAmt; ++i) {
		pFrame = (MYFRAME*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(i));
		if (!pFrame) return E_FAIL;
		pMeshContainer->ppBoneMatrix[i] = &pFrame->CombinedTransformationMatrix;
	}    
    return S_OK;
}

HRESULT AnimModel::AllocateAllBoneMatrices(LPD3DXFRAME pFrame) {
    if (pFrame->pMeshContainer) if (FAILED(AllocateBoneMatrix(pFrame->pMeshContainer))) return E_FAIL;
    if (pFrame->pFrameSibling) if (FAILED(AllocateAllBoneMatrices(pFrame->pFrameSibling))) return E_FAIL;
    if (pFrame->pFrameFirstChild) if (FAILED(AllocateAllBoneMatrices(pFrame->pFrameFirstChild))) return E_FAIL;
    return S_OK;
}

void AnimModel::RenderMeshContainer( MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame) {
	DWORD i, k, dwBlendMatrixAmt, dwPrevBoneID;
    LPD3DXBONECOMBINATION pBoneCombination;
    UINT iMatrixIndex;
    D3DXMATRIX matStack;

	if (pMeshContainer->pSkinInfo) {		// スキンメッシュの場合
		pBoneCombination = (LPD3DXBONECOMBINATION)pMeshContainer->pBoneBuffer->GetBufferPointer();
		dwPrevBoneID = UINT_MAX;
		for (i = 0; i < pMeshContainer->dwBoneAmt; ++i) {
			dwBlendMatrixAmt = 0;
			for (k = 0; k < pMeshContainer->dwWeight; ++k) if (pBoneCombination[i].BoneId[k] != UINT_MAX) dwBlendMatrixAmt = k;
			pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixAmt);
			for (k = 0; k < pMeshContainer->dwWeight; ++k) {
				iMatrixIndex = pBoneCombination[i].BoneId[k];
				if (iMatrixIndex != UINT_MAX) {
					matStack = pMeshContainer->pBoneOffsetMatrices[iMatrixIndex]*(*pMeshContainer->ppBoneMatrix[iMatrixIndex]);
					pDevice->SetTransform(D3DTS_WORLDMATRIX(k), &matStack);
				}
			}
			SetMaterial(pMeshContainer);
			pDevice->SetMaterial(&pMeshContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D);
			pDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneCombination[i].AttribId]);
			dwPrevBoneID = pBoneCombination[i].AttribId;
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
			pDevice->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
		}
	}
	else {									// 通常メッシュの場合
		pDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
					SetMaterial(pMeshContainer);

		for (i = 0; i < pMeshContainer->NumMaterials; ++i) {
			pDevice->SetMaterial(&pMeshContainer->pMaterials[i].MatD3D);
			pDevice->SetTexture(0, pMeshContainer->ppTextures[i]);
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
}
void AnimModel::DrawFrame(LPD3DXFRAME pFrameBase) {
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
    MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pFrame->pMeshContainer;	
    while (pMeshContainer) {
        RenderMeshContainer(pMeshContainer, pFrame);
        pMeshContainer = (MYMESHCONTAINER*)pMeshContainer->pNextMeshContainer;
    }
    if (pFrame->pFrameSibling) DrawFrame(pFrame->pFrameSibling);
    if (pFrame->pFrameFirstChild) DrawFrame(pFrame->pFrameFirstChild);
}

void AnimModel::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix) {
    MYFRAME *pFrame = (MYFRAME*)pFrameBase;	
    if (pParentMatrix) D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
    else pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
    if (pFrame->pFrameSibling) UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
    if (pFrame->pFrameFirstChild) UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
}
void AnimModel::SetMaterial( MYMESHCONTAINER* pMeshContainer ) {
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = m_color.r;
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = m_color.g;
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = m_color.b;
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.a = m_color.a;
	pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
}
void AnimModel::Draw(D3DXVECTOR3 position, D3DXMATRIX attitude) {
	D3DXMATRIX matTrans;
	D3DXMATRIX matScale;
	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
	D3DXMatrixScaling(&matScale,m_vecScale.x,m_vecScale.y,m_vecScale.z);

	D3DXMATRIX matWorld = attitude;
	matWorld = matWorld * matScale * matTrans;

    pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	UpdateFrameMatrices(pFrameRoot, &matWorld);
	DrawFrame(pFrameRoot);


	// ポリゴンのDiffuse色の透明度をテクスチャに反映させる
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
}
double AnimModel::AdvanceTime(double time) 
{
	pAnimController->AdvanceTime(time, 0);

	m_AnimTime += (time * 60);

	return m_AnimTime;
}
void AnimModel::ChangeMotion(int motion_number)
{
	// 今のアニメーションをトラック1に移行
	D3DXTRACK_DESC TD;
	pAnimController->GetTrackDesc( 0, &TD );
	pAnimController->SetTrackAnimationSet( 1, pAnimSet[ m_curAnimNo ] );
	pAnimController->SetTrackDesc( 1, &TD );
	pAnimController->SetTrackEnable(1, false);
	pAnimController->SetTrackEnable(0, false);

	// 新しいアニメーションをトラック0に移行

	pAnimController->SetTrackAnimationSet( 0, pAnimSet[ motion_number ] );
	
	// アニメーション全体時間確認(デバッグ用)
	//double a = pAnimSet[0]->GetPeriod();

	pAnimController->SetTrackPosition(0,m_animList[motion_number].startTime / 60);
		//アニメーション時間をリセット
	m_AnimTime = m_animList[motion_number].startTime;
	// 現在のアニメーション番号に切り替え
	m_curAnimNo = motion_number;

	pAnimController->SetTrackEnable(0, true);
	pAnimController->SetTrackEnable(1, true);
}
LPD3DXFRAME AnimModel::GetFrameRoot()
{
	return pFrameRoot;
}

void AnimModel::SetScale(D3DXVECTOR3 _vecScale)
{
	m_vecScale = _vecScale;
}
void AnimModel::SetColor(float _a,float _r,float _g,float _b)
{
	m_color.a = _a;
	m_color.r = _r;
	m_color.g = _g;
	m_color.b = _b;
}

void AnimModel::SetAnimList(std::vector<ANIMLIST>* _animList)
{
	m_animList = *_animList;
}