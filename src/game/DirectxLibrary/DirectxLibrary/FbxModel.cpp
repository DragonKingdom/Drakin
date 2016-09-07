#include "stdafx.h"
#include "FbxModel.h"



void Vec3Transform(D3DVECTOR *pOut, D3DVECTOR *pVec, D3DXMATRIX *pMat)
{
	float vx, vy, vz;
	D3DVECTOR vec;
	float *pF1, *pF2, *pF3, *pF4;

	vx = pVec->x;
	vy = pVec->y;
	vz = pVec->z;

	pF1 = pMat->m[0];
	pF2 = pMat->m[1];
	pF3 = pMat->m[2];
	pF4 = pMat->m[3];

	vec.x = vx * (*pF1) + vy * (*pF2) + vz * (*pF3) + (*pF4);
	pF1++;
	pF2++;
	pF3++;
	pF4++;

	vec.y = vx * (*pF1) + vy * (*pF2) + vz * (*pF3) + (*pF4);
	pF1++;
	pF2++;
	pF3++;
	pF4++;

	vec.z = vx * (*pF1) + vy * (*pF2) + vz * (*pF3) + (*pF4);
	pF1++;
	pF2++;
	pF3++;
	pF4++;


	*pOut = vec;
}

FbxModel::FbxModel(LPDIRECT3DDEVICE9 _pDevice) :
m_pDevice(_pDevice),
m_Mode(FbxModel::NORMAL_MODE),
m_FrameCount(0)
{

}

FbxModel::~FbxModel()
{
	if (m_pFbxModelData->Animation.SkinNum != 0)
	{
		for (int n = 0; n < m_pFbxModelData->Animation.SkinNum; n++)
		{
			for (int j = 0; j < m_pFbxModelData->Animation.pSkinData[n].ClusterNum; j++)
			{
				delete[] m_pFbxModelData->Animation.pSkinData[n].pCluster[j].pMat;
			}
			delete[] m_pFbxModelData->Animation.pSkinData[n].pCluster;
		}
		delete[] m_pFbxModelData->Animation.pSkinData;
	}

	for (unsigned int n = 0; n < m_pFbxModelData->pTextureData.size(); n++)
	{
		if (m_pFbxModelData->pTextureData[n]->pTexture == NULL)
		{
			delete m_pFbxModelData->pTextureData[n];
		}
		else
		{
			m_pFbxModelData->pTextureData[n]->pTexture->Release();
			delete m_pFbxModelData->pTextureData[n];
		}
	}

	if (m_pFbxModelData->pVertex != NULL)
	{
		delete[] m_pFbxModelData->pVertex;
	}

	if (m_pFbxModelData->pIndex.IndexAry != NULL)
	{
		delete[] m_pFbxModelData->pIndex.pVertex;
		delete[] m_pFbxModelData->pIndex.IndexAry;
	}
	delete m_pFbxModelData;
}

void FbxModel::GetMaterial(std::vector<D3DMATERIAL9>* pMaterial)
{
	for (unsigned int i = 0; i < m_pFbxModelData->Material.size(); i++)
	{
		pMaterial->push_back(m_pFbxModelData->Material[i]);
	}
}

void FbxModel::Draw()
{
	///@todo fvfの設定は分けときたいかな
	m_pDevice->SetFVF(USERVERTEX_FVF);

	for (unsigned int n = 0; n < m_pFbxModelData->pTextureData.size(); n++)
	{
		m_pDevice->SetTexture(n, m_pFbxModelData->pTextureData[n]->pTexture);
	}

	if (m_Mode == FbxModel::NORMAL_MODE)
	{
		m_pDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLELIST,
			m_pFbxModelData->PrimitiveCount,
			m_pFbxModelData->pVertex,
			sizeof(UserVertex));
	}
	else if (m_Mode == FbxModel::INDEX_MODE)
	{

	}
}


void FbxModel::NonTextureDraw()
{
	m_pDevice->SetFVF(USERVERTEX_FVF);

	m_pDevice->SetTexture(0, NULL);

	if (m_Mode == FbxModel::NORMAL_MODE)
	{
		m_pDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLELIST,
			m_pFbxModelData->PrimitiveCount,
			m_pFbxModelData->pVertex,
			sizeof(UserVertex));
	}
	else if (m_Mode == FbxModel::INDEX_MODE)
	{

	}
}

void FbxModel::InitAnimation()
{
	if (m_pFbxModelData->Animation.SkinNum != 0)
	{
		// アニメーションはインデックス描画じゃないとめんどくさすぎるので変更
		m_Mode = FbxModel::INDEX_MODE;
	
		m_pVertex = new UserVertex[m_pFbxModelData->ControlPointCount];
		m_pTmpVertex = new UserVertex[m_pFbxModelData->ControlPointCount];
		m_pDrawVertex = new UserVertex[m_pFbxModelData->ControlPointCount];

		for (int i = 0; i < m_pFbxModelData->pIndex.IndexCount; i++)
		{
			m_pVertex[m_pFbxModelData->pIndex.IndexAry[i]] = m_pFbxModelData->pVertex[i];
			m_pTmpVertex[m_pFbxModelData->pIndex.IndexAry[i]] = m_pFbxModelData->pVertex[i];
			m_pDrawVertex[m_pFbxModelData->pIndex.IndexAry[i]] = m_pFbxModelData->pVertex[i];
		}

		for (int i = 0; i < m_pFbxModelData->ControlPointCount; i++)
		{
			m_pVertex[i].Vec = m_pFbxModelData->pIndex.pVertex[i];
			m_pTmpVertex[i].Vec = m_pFbxModelData->pIndex.pVertex[i];
			m_pDrawVertex[i].Vec = m_pFbxModelData->pIndex.pVertex[i]; 
		}
	}
}

void FbxModel::ReleaseAnimation()
{
	delete[] m_pDrawVertex;
	delete[] m_pTmpVertex;
	delete[] m_pVertex;
}

void FbxModel::SetAnimationFrame(int _setFrame)
{
	m_FrameCount = _setFrame;
}

void FbxModel::AnimationDraw()
{
	if (m_pFbxModelData->Animation.SkinNum != 0)
	{
		for (unsigned int n = 0; n < m_pFbxModelData->pTextureData.size(); n++)
		{
			m_pDevice->SetTexture(n, m_pFbxModelData->pTextureData[n]->pTexture);
		}

		//-------- アニメーション処理 --------//

		for (int i = 0; i < m_pFbxModelData->ControlPointCount; i++)
		{
			m_pDrawVertex[i].Vec.x = 0.f;
			m_pDrawVertex[i].Vec.y = 0.f;
			m_pDrawVertex[i].Vec.z = 0.f;
		}

		for (int i = 0; i < m_pFbxModelData->Animation.pSkinData[0].ClusterNum; i++)
		{
			D3DXMATRIX InvMat;
			D3DXMatrixInverse(&InvMat, NULL, &m_pFbxModelData->Animation.pSkinData[0].pCluster[i].InitMatrix);

			for (int j = 0; j < m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointNum; j++)
			{
				D3DVECTOR TmpVertex;
				Vec3Transform(
					&TmpVertex,
					&m_pVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec,
					&InvMat
					);

				Vec3Transform(
					&m_pTmpVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec,
					&TmpVertex,
					&(m_pFbxModelData->Animation.pSkinData[0].pCluster[i].pMat[m_FrameCount] * m_pFbxModelData->Animation.pSkinData[0].pCluster[i].WeightAry[j])
					);


				m_pDrawVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.x += m_pTmpVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.x;
				m_pDrawVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.y += m_pTmpVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.y;
				m_pDrawVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.z += m_pTmpVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.z;
			}
		}

		
		if (m_FrameCount == m_pFbxModelData->Animation.pSkinData[0].EndFrame - 1)
		{
			m_FrameCount = 0;
		}
		else
		{
			m_FrameCount++;
		}

		m_pDevice->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			m_pFbxModelData->pIndex.IndexCount,
			m_pFbxModelData->pIndex.IndexCount / 3,
			m_pFbxModelData->pIndex.IndexAry,
			D3DFMT_INDEX16,
			m_pDrawVertex,
			sizeof(UserVertex));
	}
}

void FbxModel::NonTextureAnimationDraw()
{
	if (m_pFbxModelData->Animation.SkinNum != 0)
	{
		m_pDevice->SetTexture(0, NULL);
		m_pDevice->SetTexture(1, NULL);
		m_pDevice->SetTexture(2, NULL);


		//-------- アニメーション処理 --------//

		for (int i = 0; i < m_pFbxModelData->ControlPointCount; i++)
		{
			m_pDrawVertex[i].Vec.x = 0.f;
			m_pDrawVertex[i].Vec.y = 0.f;
			m_pDrawVertex[i].Vec.z = 0.f;
		}

		for (int i = 0; i < m_pFbxModelData->Animation.pSkinData[0].ClusterNum; i++)
		{
			D3DXMATRIX InvMat;
			D3DXMatrixInverse(&InvMat, NULL, &m_pFbxModelData->Animation.pSkinData[0].pCluster[i].InitMatrix);

			for (int j = 0; j < m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointNum; j++)
			{
				D3DVECTOR TmpVertex;
				Vec3Transform(
					&TmpVertex,
					&m_pVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec,
					&InvMat
					);

				Vec3Transform(
					&m_pTmpVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec,
					&TmpVertex,
					&(m_pFbxModelData->Animation.pSkinData[0].pCluster[i].pMat[m_FrameCount] * m_pFbxModelData->Animation.pSkinData[0].pCluster[i].WeightAry[j])
					);


				m_pDrawVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.x += m_pTmpVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.x;
				m_pDrawVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.y += m_pTmpVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.y;
				m_pDrawVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.z += m_pTmpVertex[m_pFbxModelData->Animation.pSkinData[0].pCluster[i].PointAry[j]].Vec.z;
			}
		}


		if (m_FrameCount == m_pFbxModelData->Animation.pSkinData[0].EndFrame - 1)
		{
			m_FrameCount = 0;
		}
		else
		{
			m_FrameCount++;
		}

		m_pDevice->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			m_pFbxModelData->pIndex.IndexCount,
			m_pFbxModelData->pIndex.IndexCount / 3,
			m_pFbxModelData->pIndex.IndexAry,
			D3DFMT_INDEX16,
			m_pDrawVertex,
			sizeof(UserVertex));
	}
}