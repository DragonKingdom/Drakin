/**
 * @file   Button2D.h
 * @brief  2D�̃{�^���N���X�w�b�_
 *
 * @author matsumura
 */

#ifndef BUTTON2D_H
#define BUTTON2D_H

/// ��_���
enum RefPoint
{
	kTopLeft,
	kCenter
};

/// 2D�̃{�^���N���X
/**
 * ���g���N���b�N���ꂽ���Ƃ�}�E�X�I�[�o�[���擾�ł���B
 * UI���i���A2D�̃{�^���I�u�W�F�N�g�͖{�N���X���p������ƕ֗��Ȃ͂��B
 */
class InputDeviceFacade;

class Button2D
{
public:
	/// �R���X�g���N�^
	/**
	 * ��_�͍���ƒ��S�̂����ꂩ���w��ł���
	 *
	 * @param _refPoint ��_���
	 * @param _position ����W
	 */
	Button2D(RefPoint _refPoint, D3DXVECTOR2 _position);
	virtual ~Button2D();

	Vertex::FRECT GetRect(){ return m_rect; }  //�Q/�Q�U�ǉ�

protected:
	bool IsMouseOver();
	bool IsLeftClicked();
	void SetRect(float _width, float _height);

	D3DXVECTOR2 m_position;
	RefPoint m_refPoint;
	Vertex::FRECT m_rect;
	InputDeviceFacade* m_pIdf;

private:
	// �B��
	Button2D();
	DISALLOW_COPY_AND_ASSIGN(Button2D);
};

#endif // BUTTON2D_H
