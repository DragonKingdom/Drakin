#include "Window.h"
#include "textureManager.h"
#include "InputDeviceFacade.h"

const D3DXVECTOR2 Window::PARTS_SIZE = D3DXVECTOR2(135,135);

const Vertex::FRECT Window::UV[Window::TYPE_MAX] = 
{
	//Window.png
	Vertex::FRECT(0,0,135,135),
	Vertex::FRECT(135,0,270,135),
	Vertex::FRECT(0,135,135,270),
	Vertex::FRECT(135,135,270,270),
	Vertex::FRECT(100,100,200,200),
};

Window::Window(D3DXVECTOR2 _windowSize, D3DXVECTOR2 _position, D3DXVECTOR2 _targetPos, StateManager* _pStateManager) :
	m_windowSize(_windowSize),
	m_position(_position),/*�`��ʒu*/
	m_targetPos(_targetPos),/*�ړ���*/
	m_time(LEAVE_LIMIT_TIME),
	m_move(0,0), 
	m_initPos(_position),
	m_pStateManager(_pStateManager)
{	
	m_texture = TextureManager::getInstance().Get(TextureManager::GAME_SCENE_TEX::WINDOW);
	// �E�C���h�E������Ă��܂��ׁA�E�C���h�E�̍ŏ��T�C�Y��菬�����Ȃ�Ȃ��悤�ɂ��Ă���
	if( m_windowSize.x < PARTS_SIZE.x * 2 )
	{
		m_windowSize.x = PARTS_SIZE.x * 2;
	}
	if( m_windowSize.y < PARTS_SIZE.y * 2 )
	{
		m_windowSize.y = PARTS_SIZE.y * 2;
	}
	// �ړ��ʂ����߂�
	if( m_position.x == m_targetPos.x && m_position.y == m_targetPos.y )
	{
		m_state = STATE_WAIT;
		m_direction = DIR_NONE;
		m_move = D3DXVECTOR2(0,0);
	}
	else if (m_position.y == m_targetPos.y)
	{
		m_state = STATE_MOVE;
		m_direction = DIR_HORIZONTAL;
		m_move.x = ( m_targetPos.x - m_position.x) / MOVE_TIME;
	}
	else if(m_position.x == m_targetPos.x )
	{
		m_state = STATE_MOVE;
		m_direction = DIR_VIRTICAL;
		m_move.y = ( m_targetPos.y - m_position.y) / MOVE_TIME;
	}
	else
	{
		m_state = STATE_MOVE;
		m_direction = DIR_VIRTICAL;
		m_move.x = ( m_targetPos.x - m_position.x) / MOVE_TIME;
		m_move.y = ( m_targetPos.y - m_position.y) / MOVE_TIME;
	}
}

Window::~Window()
{
}

bool Window::Control()
{
	// �E�N���b�N���ꂽ��
	if (m_pInputDevice->MouseRightPush())
	{
		// �폜�҂��łȂ���Ԃ̎�
		if (m_state != STATE_DESTROY)
		{
			// �E�C���h�E����ʊO�Ɉړ����閽�߂��o��
			m_state = STATE_LEAVE;
		}
	}

	switch(m_state)
	{
	case STATE_WAIT:
		break;
	case STATE_MOVE:
		m_position += m_move;
		// �ڕW�ʒu�ɒB���Ă��邩���ׂ�
		if( CheckTargetPos(m_position,m_targetPos) )
		{
			m_state = STATE_WAIT;
		}
		break;
	case STATE_LEAVE:
		m_position -= m_move;
		if( CheckTargetPos(m_initPos,m_position) )
		{
			m_state = STATE_DESTROY;
		}
		break;
	}

	if (m_state == STATE_DESTROY)
	{
		return true;
	}
	return false;
}

void Window::Draw()
{
	// �E�C���h�E�l���̕`��
	m_vertex.DrawTextureLT(m_texture,
						   m_position,
						   UV[LEFT_TOP]);
	// �E�㕔��
	m_vertex.DrawTextureLT(m_texture,
						   D3DXVECTOR2(m_position.x + m_windowSize.x - PARTS_SIZE.x,m_position.y),
						   UV[RIGHT_TOP]);
	// ����
	m_vertex.DrawTextureLT(m_texture,
						   D3DXVECTOR2(m_position.x, m_position.y + m_windowSize.y - PARTS_SIZE.y),
						   UV[LEFT_BOTTOM]);
	
	m_vertex.DrawTextureLT(m_texture,
						   D3DXVECTOR2(m_position.x + m_windowSize.x - PARTS_SIZE.x ,m_position.y + m_windowSize.y - PARTS_SIZE.y),
						   UV[RIGHT_BOTTOM]);

	// ���Ԃ𖄂߂�T�C�Y
	int partsSize = 16;
	// �E�C���h�E�̍��E�̃p�[�c�̌��Ԃ𖄂߂�( �T�C�Y - ���E�̃p�[�c��for�����܂킷)
	for(int i = 0; i < m_windowSize.x - PARTS_SIZE.x * 2; )
	{
			// ���Ԃ̕�����partsSize��菬������
		if( m_windowSize.x - PARTS_SIZE.x * 2 - i <= partsSize )
		{
			// �]������߂�
			partsSize = (int)(m_windowSize.x - PARTS_SIZE.x * 2 - i);
		}
		m_vertex.DrawTextureLT(m_texture,
							   D3DXVECTOR2(m_position.x + i + PARTS_SIZE.x,m_position.y),
							   Vertex::FRECT(UV[LEFT_TOP].right,UV[LEFT_TOP].top,UV[LEFT_TOP].right + partsSize,UV[LEFT_TOP].bottom));
		m_vertex.DrawTextureLT(m_texture,
							   D3DXVECTOR2(m_position.x + i + + PARTS_SIZE.x,m_position.y + m_windowSize.y - PARTS_SIZE.y ),
							   Vertex::FRECT(UV[LEFT_BOTTOM].right,UV[LEFT_BOTTOM].top,UV[LEFT_BOTTOM].right + partsSize,UV[LEFT_BOTTOM].bottom));
		i += partsSize;
	}
	
	// �E�C���h�E�̍��E�̃p�[�c�̌��Ԃ𖄂߂�( �T�C�Y - ���E�̃p�[�c��for�����܂킷)
	for(int i = 0; i < m_windowSize.y - PARTS_SIZE.y * 2; )
	{
			// ���Ԃ̕�����partsSize��菬������
		if( m_windowSize.y - PARTS_SIZE.y * 2 - i <= partsSize )
		{
			// �]������߂�
			partsSize = (int)(m_windowSize.y - PARTS_SIZE.y * 2 - i);
		}
		m_vertex.DrawTextureLT(m_texture,
							   D3DXVECTOR2(m_position.x ,m_position.y + i + PARTS_SIZE.y),
							   Vertex::FRECT(UV[LEFT_TOP].left,UV[LEFT_TOP].bottom,UV[LEFT_TOP].right,UV[LEFT_TOP].bottom + partsSize));
		m_vertex.DrawTextureLT(m_texture,
							   D3DXVECTOR2(m_position.x + m_windowSize.x - PARTS_SIZE.x ,m_position.y + i + PARTS_SIZE.y),
							   Vertex::FRECT(UV[RIGHT_TOP].left,UV[RIGHT_TOP].bottom,UV[RIGHT_TOP].right,UV[RIGHT_TOP].bottom + partsSize));
		i += partsSize;
	}

	// ���Ԃ𖄂߂�T�C�Y
	D3DXVECTOR2 size = D3DXVECTOR2(16, 16);
	for (int i = 0; i < m_windowSize.x - PARTS_SIZE.x * 2;)
	{
		// ���Ԃ̕�����partsSize��菬������
		if (m_windowSize.x - PARTS_SIZE.x * 2 - i <= size.x)
		{
			// �]������߂�
			size.x = m_windowSize.x - PARTS_SIZE.x * 2 - i;
		}
		for(int j = 0; j < m_windowSize.y - PARTS_SIZE.y * 2;)
		{
			// ���Ԃ̕�����partsSize��菬������
			if( m_windowSize.y - PARTS_SIZE.y * 2 - j <= size.y )
			{
				// �]������߂�
				size.y = m_windowSize.y - PARTS_SIZE.y * 2 - j;
			}
			m_vertex.DrawTextureLT(m_texture,
								   D3DXVECTOR2(m_position.x + i + PARTS_SIZE.x,m_position.y + j + PARTS_SIZE.y),
								   Vertex::FRECT(UV[CENTER].left,UV[CENTER].top,UV[CENTER].left + size.x,UV[CENTER].top + size.y));
			j += (int)size.y;
		}
		size.y = 16;
		i += (int)size.y;
	}
}

bool Window::CheckTargetPos(D3DXVECTOR2 _position,D3DXVECTOR2 _targetPos)
{
	switch(m_direction)
	{
	case DIR_DIAGONAL:
		if( _position.x <= _targetPos.x && _position.y <= _targetPos.y)
		{
			_position = _targetPos;
			return true;
		}
		break;
	case DIR_HORIZONTAL:
		if( _position.x <= _targetPos.x )
		{
			_position.x = _targetPos.x;
			return true;
		}
		break;
	case DIR_VIRTICAL:
		if( _position.y <= _targetPos.y )
		{
			_position.y = _targetPos.y;
			return true;
		}
		break;
	case DIR_NONE:
		return true;
		break;
	}
	return false;
}