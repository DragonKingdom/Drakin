#include "stdafx.h"
#include "FbxModel.h"

FbxModel::FbxModel(LPDIRECT3DDEVICE9 _pDevice) :
m_pDevice(_pDevice),
m_Mode(FbxModel::NORMAL_MODE)
{

}

FbxModel::~FbxModel()
{
	for (unsigned int i = 0; i < m_pFbxModelData.size(); i++)
	{
		if (m_pFbxModelData[i]->Animation.SkinNum != 0)
		{
			for (int n = 0; n < m_pFbxModelData[i]->Animation.SkinNum; n++)
			{
				for (int j = 0; j < m_pFbxModelData[i]->Animation.pSkinData[n].ClusterNum; j++)
				{
					delete[] m_pFbxModelData[i]->Animation.pSkinData[n].pCluster[j].pMat;
				}
				delete[] m_pFbxModelData[i]->Animation.pSkinData[n].pCluster;
			}
			delete[] m_pFbxModelData[i]->Animation.pSkinData;
		}

		for (unsigned int n = 0; n < m_pFbxModelData[i]->pTextureData.size(); n++)
		{
			if (m_pFbxModelData[i]->pTextureData[n]->pTexture == NULL)
			{
				delete m_pFbxModelData[i]->pTextureData[n];
			}
			else
			{
				m_pFbxModelData[i]->pTextureData[n]->pTexture->Release();
				delete m_pFbxModelData[i]->pTextureData[n];
			}
		}

		if (m_pFbxModelData[i]->pVertex != NULL)
		{
			delete[] m_pFbxModelData[i]->pVertex;
		}

		if (m_pFbxModelData[i]->pIndex.IndexAry != NULL)
		{
			delete[] m_pFbxModelData[i]->pIndex.IndexAry;
		}
		delete m_pFbxModelData[i];
	}
}

void FbxModel::Draw()
{
	///@todo fvf‚ÌÝ’è‚Í•ª‚¯‚Æ‚«‚½‚¢‚©‚È
	m_pDevice->SetFVF(USERVERTEX_FVF);

	for (unsigned int i = 0; i < m_pFbxModelData.size(); i++)
	{
		m_pDevice->SetMaterial(&m_pFbxModelData[i]->Material);

		for (unsigned int n = 0; n < m_pFbxModelData[i]->pTextureData.size(); n++)
		{
			m_pDevice->SetTexture(n, m_pFbxModelData[i]->pTextureData[n]->pTexture);
		}

		if (m_Mode == FbxModel::NORMAL_MODE)
		{
			m_pDevice->DrawPrimitiveUP(
				D3DPT_TRIANGLELIST,
				m_pFbxModelData[i]->PrimitiveCount,
				m_pFbxModelData[i]->pVertex,
				sizeof(UserVertex));
		}
	}
}


void FbxModel::NonTextureDraw()
{
	m_pDevice->SetFVF(USERVERTEX_FVF);

	for (unsigned int i = 0; i < m_pFbxModelData.size(); i++)
	{
		m_pDevice->SetMaterial(&m_pFbxModelData[i]->Material);

		m_pDevice->SetTexture(0, NULL);

		if (m_Mode == FbxModel::NORMAL_MODE)
		{
			m_pDevice->DrawPrimitiveUP(
				D3DPT_TRIANGLELIST,
				m_pFbxModelData[i]->PrimitiveCount,
				m_pFbxModelData[i]->pVertex,
				sizeof(UserVertex));
		}
	}
}


