#include "RoadManager.h"
#include "CrossingManager.h"
#include "BuildAreaManager.h"
#include <math.h>

#define ROAD_ROUND_OFF 35.f

namespace
{
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		D3DCOLOR color;
	};
}

RoadManager::RoadManager(CrossingManager* _cross, BuildAreaManager* _build) :
	m_pDevice(GraphicsDevice::getInstance().GetDevice()),
	m_pCrossingManager(_cross),
	m_pBuildAreaManager(_build),
	m_prevMousePos(D3DXVECTOR3(0,0,0))
{
	m_setStartPos = false;
	m_controlFlag = false;

	SetPos(0,0);
	//SetControlPos(-500,500);
	SetPos(0,1000);

	SetPos(0,1000);
	SetPos(1000,1000);

	SetPos(0,1000);
	SetPos(-1000,1000);
	//SetPos(-100,2000);
	//SetControlPos(-500,500);
	//SetPos(-1000,2000);

	//SetPos(-100,0);
	//SetControlPos(-500,500);
	//SetPos(-1000,0);

}

RoadManager::~RoadManager()
{

}

void RoadManager::Draw()
{
	for( DWORD i = 0 ; i < m_Road.size() ; i++ )
	{
		m_Road[i].Draw();
	}
	if( m_setStartPos )
	{
		PreviewDraw();
	}
}

void RoadManager::SetPos(float x, float y)
{
	if( m_setStartPos == false )
	{
		int loop = m_pCrossingManager->GetpCrossing()->size();
		for( int i = 0 ; i < loop ; i++ )
		{
			D3DXVECTOR3 crossPos = m_pCrossingManager->GetpCrossing()[0][i].pos;
			if( fabs( crossPos.x - x ) < ROAD_ROUND_OFF )
			{
				if( fabs( crossPos.z - y ) < ROAD_ROUND_OFF )
				{
					x = crossPos.x;
					y = crossPos.z;
					break;
				}
			}
		}
		
		m_startPos = D3DXVECTOR2(x,y);
		m_setStartPos = true;
	}
	else
	{
		int loop = m_pCrossingManager->GetpCrossing()->size();
		for( int i = 0 ; i < loop ; i++ )
		{
			D3DXVECTOR3 crossPos = m_pCrossingManager->GetpCrossing()[0][i].pos;
			if( fabs( crossPos.x - x ) < ROAD_ROUND_OFF )
			{
				if( fabs( crossPos.z - y ) < ROAD_ROUND_OFF )
				{
					x = crossPos.x;
					y = crossPos.z;
					break;
				}
			}
		}
		m_endPos = D3DXVECTOR2(x,y);
		float x,y;
		x =fabs( m_startPos.x-m_endPos.x );
		y = fabs( m_startPos.y-m_endPos.y );
		if( x + y > MIN_ROAD_LENGTH)
		{
			SetRoad();	
		}
		m_setStartPos = false;
		m_controlFlag = false;
	}
}

// スタート値とエンド値とコントロール値（あれば）をもとに、
// Roadクラスにデータを分割してほりこんでいく
void RoadManager::SetRoad()
{
	// 線の長さを出す
	float length = 0.f;
	if( m_controlFlag )
	{
		// ベジェ曲線の長さを求める 処理が重いようならコメントアウト部分を用い、大まかな長さを出すように変更
		float t2 = 1;
		float t1 = 0;
		float x1 = m_startPos.x, y1 = m_startPos.y;
		float x2 = m_controlPos.x, y2 = m_controlPos.y;
		float x3 = m_endPos.x, y3 = m_endPos.y;
		float xa = 2*(x1-2*x2+x3), xb = -2*x1+2*x2, ya = 2*(y1-2*y2+y3), yb = -2*y1+2*y2;
		float a = xa*xa+ya*ya, b = 2*(xa*xb+ya*yb), c = xb*xb+yb*yb, D = b*b-4*a*c;
		if (D) 
		{
			float s1 = 2 * sqrt(a*(t1*(a*t1 + b) + c)) + 2 * a*t1 + b;
			float s2 = 2 * sqrt(a*(t2*(a*t2 + b) + c)) + 2 * a*t2 + b;
			length = (s2*s2 - s1*s1 - D*(4 * log(s2 / s1) + D*(1 / (s2*s2) - 1 / (s1*s1)))) / (32 * a*sqrt(a));
		} 
		else if (a) 
		{
			length = (abs(2*a*t2+b)*(2*a*t2+b)-abs(2*a*t1+b)*(2*a*t1+b))/(8*a*sqrt(a));
		} 
		else 
		{
			length = sqrt(c)*(t2-t1);
		}

		/*length += sqrt( (m_startPos.x - m_controlPos.x ) * (m_startPos.x - m_controlPos.x ) ) +
				sqrt( (m_startPos.y - m_controlPos.y ) * (m_startPos.y - m_controlPos.y ) );

		length += sqrt( (m_endPos.x - m_controlPos.x ) * (m_endPos.x - m_controlPos.x ) ) +
				sqrt( (m_endPos.y - m_controlPos.y ) * (m_endPos.y - m_controlPos.y ) );*/
	}
	else
	{
		length += sqrt( (m_startPos.x - m_endPos.x ) * (m_startPos.x - m_endPos.x )  +
					    (m_startPos.y - m_endPos.y ) * (m_startPos.y - m_endPos.y ) );

		m_controlPos = m_endPos;
	}

	// 長さがわかったらいくつに分解するか決める
	int roadNum = (int)length / MAXROADLENGTH + 1;
	int centerPosNum = (int)length / ROADLINESPACE + 1;

	// 頂点データを作る
	D3DXVECTOR3* centerLinePos;
	centerLinePos = new D3DXVECTOR3[centerPosNum];

	for( int i = 0 ; i < centerPosNum ; i++ )
	{
		centerLinePos[i] = QuadraticBezPoint(m_startPos,m_controlPos,m_endPos,i*1.f/(float)(centerPosNum-1));
	}
	
	// 頂点データと角度データができたのでセット
	// セットする用のベクターを生成
	Road road;
	Road* tmp_road;
	m_Road.push_back(road);
	m_pCurrentRoad = tmp_road = &m_Road.back();
	
	int loopNum;
	int TmpCrossing1;
	int TmpCrossing2;
	for( int i = 0 ; i < roadNum ; i++ )
	{
		loopNum = centerPosNum / roadNum + 1;
		if (i == roadNum - 1)
		{
			loopNum = centerPosNum % loopNum;
		}

		for( int j = 0 ; j < loopNum ; j++ )
		{
			m_pCurrentRoad->SetPos(centerLinePos[i*(centerPosNum / roadNum + 1)+j]);
		}
		// データがそろったらRoadクラスでデータを定義
		m_pCurrentRoad->SetSideRoad();
		if( i == 0 )
		{
			TmpCrossing1 = m_pCrossingManager->AddCrossing(&centerLinePos[0], m_pCurrentRoad, m_Road.size() - 1, length);
		}
		// 最終ループなら抜ける
		if( i == roadNum - 1 ) 
		{
			int size = m_pCurrentRoad->GetCenterLinePos().size();
			TmpCrossing2 = m_pCrossingManager->AddCrossing(&m_pCurrentRoad->GetCenterLinePos()[size-1],m_pCurrentRoad,m_Road.size()-1,length);
			m_pCrossingManager->GetpCrossing()[0][TmpCrossing1].m_connectCrossingID.push_back(TmpCrossing2);
			m_pCrossingManager->GetpCrossing()[0][TmpCrossing2].m_connectCrossingID.push_back(TmpCrossing1);
			break;
		}

		// 違うなら次の道とのつなぎを作る
		// 生成
		Road road;
		m_Road.push_back(road);
		
		m_pCurrentRoad = &m_Road.back();
		// 一個前の点を取得して新しいRoadの先頭につっこむ
		m_pCurrentRoad->SetPos(centerLinePos[(i+1)*(centerPosNum / roadNum + 1)-1]);
	}

	// コントロールフラグがないなら交差を調べるのは1度でいい
	if( m_controlFlag )
	{

	}
	else
	{
		//float bx1,bx2,by1,by2;

		//for( int i = 0 ; i < m_Road.size() ; i++ )
		//{
		//	std::vector<D3DXVECTOR3> road = m_Road[i].GetCenterLinePos();
		//	// 交差チェックの幅で道の点の数を割って回数を減らす
		//	for( int j = 0 ; j < road.size() / CROSSCHECKSPACE - 1 ; j++ )
		//	{
		//		
		//		bx1 = road[j*CROSSCHECKSPACE].x;
		//		bx2 = road[(j+1)*CROSSCHECKSPACE].x;
		//		by1 = road[j*CROSSCHECKSPACE].y;
		//		by2 = road[(j+1)*CROSSCHECKSPACE].y;

		//		// 交差しているかを確認する式
		//		if(	(m_startPos.y-m_endPos.y)*(bx1-m_startPos.x)-(m_startPos.x-m_endPos.x)*(by1-m_startPos.y)*
		//			(m_startPos.y-m_endPos.y)*(bx2-m_startPos.x)-(m_startPos.x-m_endPos.x)*(by2-m_startPos.y) < 0 )
		//		{
		//			if( (by1-by2)*(m_startPos.x-bx1)-(bx1-bx2)*(m_startPos.y-by1)*
		//				(by1-by2)*(m_endPos.x-bx1)-(bx1-bx2)*(m_endPos.y-by1) < 0 )
		//			{
		//				// 交差しているから交差点をつくる処理
		//				if( j == 0 )
		//				{
		//					// もともと最初の点が交差してるなら頂点増やさなくていい
		//				}
		//				else
		//				{
		//					// 制御点をいっこふやす
		//					std::vector<Road>::iterator itr;
		//					itr = m_Road.begin();
		//					itr += i+1;
		//					m_Road.insert(itr,m_Road[i].MakeInsertRoad(j*CROSSCHECKSPACE));
		//					m_Road[i].ShortenRoad(road.size() - j*CROSSCHECKSPACE - 1);

		//					i++;
		//					break;
		//				}
		//			}
		//		}
		//	}
		//}	
	}
	if( !m_controlFlag )
	{
		float angle = atan2( m_endPos.y - m_startPos.y,
							m_endPos.x - m_startPos.x);
		int buildNum = (int)(length / BUILD_SIZE);
		for( int i = 0 ; i < buildNum ; i++ )
		{
			D3DXVECTOR3 buildPos;
			// 道のりに進める
			float buildSetLineLength = BUILD_SIZE / 2 + BUILD_SIZE * i;

			buildPos.x = m_startPos.x + ( buildSetLineLength ) * cos(angle);
			buildPos.y = 0.5f;
			buildPos.z = m_startPos.y + ( buildSetLineLength ) * sin(angle);
			
			// 家のサイズの半分だけ道の横にずらす
			buildPos.x += ( 230.f / 2) * sin(angle);
			buildPos.z += ( 230.f / 2) * -cos(angle);
			// 建築地点データを追加
			m_pBuildAreaManager->AddBuildArea(buildPos,angle);

			// 道の両サイドに作るため道の反対側に移動
			buildPos.x -= ( 230.f ) * sin(angle);
			buildPos.z -= ( 230.f ) * -cos(angle);
			// 建築地点データを追加
			//angle  += D3DX_PI;
			m_pBuildAreaManager->AddBuildArea(buildPos,angle);
		}
	}
	delete[] centerLinePos;
	centerLinePos = NULL;
	
}

void RoadManager::CleanSetPos()
{
	m_setStartPos = false;
	m_controlFlag = false;
}

void RoadManager::SetControlPos(float x, float y)
{
	m_controlFlag = true;
	m_controlPos = D3DXVECTOR2(x,y);
}

void RoadManager::PreviewRoadControl(D3DXVECTOR3 _mousePos)
{
	if( m_prevMousePos != _mousePos )
	{
		m_prevMousePos = _mousePos;
		PreviewSet();
	}
}

void RoadManager::PreviewSet()
{
	D3DXVECTOR2 endPoint = D3DXVECTOR2(m_prevMousePos.x,m_prevMousePos.z);
	D3DXVECTOR2 controlPoint = endPoint;
	if( m_controlFlag == true )
	{
		controlPoint = m_controlPos;
	}
	for( int i = 0 ; i < PREVIEWROADSIZE ; i++ )
	{
		m_previewRoad[i] = QuadraticBezPoint(m_startPos,controlPoint,endPoint,i*1.f/(float)(PREVIEWROADSIZE-1));
	}
	for( int i = 0 ; i < PREVIEWROADSIZE - 1 ; i++ )
	{
		m_previewRoadAngle[i] = atan2( m_previewRoad[i+1].z - m_previewRoad[i].z,
									   m_previewRoad[i+1].x - m_previewRoad[i].x);
	}
	m_previewRoadAngle[PREVIEWROADSIZE-1] = atan2( m_previewRoad[PREVIEWROADSIZE-1].z - m_previewRoad[PREVIEWROADSIZE-2].z,
												   m_previewRoad[PREVIEWROADSIZE-1].x - m_previewRoad[PREVIEWROADSIZE-2].x);

	for( unsigned int i = 0 ; i < PREVIEWROADSIZE ; i ++ )
	{
		D3DXVECTOR3 p;
		p.x = m_previewRoad[i].x + ROAD_WIDTH * sin(m_previewRoadAngle[i]);
		p.y = 0.5f;
		p.z = m_previewRoad[i].z + ROAD_WIDTH * -cos(m_previewRoadAngle[i]);
		
		m_previewLeft[i] = p;

		p.x = m_previewRoad[i].x + -ROAD_WIDTH * sin(m_previewRoadAngle[i]);
		p.z = m_previewRoad[i].z + -ROAD_WIDTH * -cos(m_previewRoadAngle[i]);
		m_previewRight[i] = p;
	}
}

void RoadManager::PreviewDraw()
{
	m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	//matWorld = matScale * _attitude * matTrans;

	// ワールド行列を登録
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	CUSTOMVERTEX* vertex = new CUSTOMVERTEX[PREVIEWROADSIZE * 2];
	for( int i = 0 ; i < PREVIEWROADSIZE ; i++ )
	{
		vertex[i*2].pos = m_previewLeft[i];
		vertex[i*2+1].pos = m_previewRight[i];
	}
	for( int i = 0 ; i < PREVIEWROADSIZE*2 ; i++ )
	{
		vertex[i].color = D3DCOLOR_ARGB(255,255,255,255);
	}
	m_pDevice->SetTexture(0,NULL);
	m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );

	m_pDevice->DrawPrimitiveUP(
					D3DPT_TRIANGLESTRIP,
					PREVIEWROADSIZE*2 - 2,
					vertex,
					sizeof(CUSTOMVERTEX)
					);
	delete[] vertex;
	vertex = NULL;
}