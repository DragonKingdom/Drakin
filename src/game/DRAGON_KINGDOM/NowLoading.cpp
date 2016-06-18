#include "NowLoading.h"
#include "graphicsDevice.h"

bool NowLoading::m_ThreadDestroyFlag;

NowLoading::NowLoading()
{
	m_ThreadFlag = false;
	m_ThreadDestroyFlag = false;
	m_ThreadHandle = NULL;
}

NowLoading::~NowLoading()
{
}

bool NowLoading::ThreadCreate(Texture* _pTexture)
{
	if (m_ThreadFlag == true)
	{
		// �X���b�h�����łɗ��Ă��Ă����珈����Ԃ�
		return false;
	}


	// �X���b�h���Ă�
	m_ThreadHandle = CreateThread(NULL, 0, this->NowLoadingThread, (LPVOID)_pTexture, 0, &m_ThreadId);
	if (m_ThreadHandle == NULL)
	{
		// �X���b�h�𗧂Ă�̂Ɏ��s���Ă��珈����Ԃ�
		return false;
	}

	
	m_ThreadFlag = true;

	return true;
}

bool NowLoading::ThreadDestroy()
{
	// �X���b�h���Ȃ���Ώ�����Ԃ�
	if (m_ThreadFlag == false)
	{
		return false;
	}

	// �X���b�h�̏I���t���O�𗧂Ă�
	m_ThreadDestroyFlag = true;

	// �X���b�h���I������܂őҋ@
	WaitForSingleObject(m_ThreadHandle, INFINITE);

	// �X���b�h�����
	CloseHandle(m_ThreadHandle);

	// ���㏈��
	m_ThreadFlag = false;
	m_ThreadDestroyFlag = false;
	m_ThreadHandle = NULL;


	return true;
}

void NowLoading::Control(NowLoadingThreadData* pData)
{
	// �Ƃ肠�����摜�X�N���[���ł�����ۂ��̂�����Ă�
	for (int i = 0; i < 4; i++)
	{
		pData->tu[i] -= SCROOL_SPEED;
	}
}

void NowLoading::Draw(NowLoadingThreadData* pData)
{
	// �`��O����
	GraphicsDevice::getInstance().GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.f, 0);
	GraphicsDevice::getInstance().GetDevice()->BeginScene();

	// �`�揈��
	pData->vertex.DrawTexture(
		*pData->pTexture,
		pData->Vec,
		pData->tu,
		pData->tv,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		0);

	// �`��㏈��
	GraphicsDevice::getInstance().GetDevice()->EndScene();
	GraphicsDevice::getInstance().GetDevice()->Present(NULL, NULL, NULL, NULL);
}

DWORD WINAPI NowLoading::NowLoadingThread(LPVOID _pTexture)
{
	// ����������
	NowLoadingThreadData ThreadData;

	// �e�N�X�`���|�C���^�󂯎��
	ThreadData.pTexture = reinterpret_cast<Texture*> (_pTexture);

	// ���_���W������
	// ���݂͌��߂���
	ThreadData.Vec[0].x = CLIENT_WIDTH - 390.f;
	ThreadData.Vec[1].x = CLIENT_WIDTH - 20.f;
	ThreadData.Vec[2].x = CLIENT_WIDTH - 20.f;
	ThreadData.Vec[3].x = CLIENT_WIDTH - 390.f;

	ThreadData.Vec[0].y = CLIENT_HEIGHT - 160.f;
	ThreadData.Vec[1].y = CLIENT_HEIGHT - 160.f;
	ThreadData.Vec[2].y = CLIENT_HEIGHT - 80.f;
	ThreadData.Vec[3].y = CLIENT_HEIGHT - 80.f;

	ThreadData.Vec[0].z = 0.5f;
	ThreadData.Vec[1].z = 0.5f;
	ThreadData.Vec[2].z = 0.5f;
	ThreadData.Vec[3].z = 0.5f;

	// �e�N�X�`�����W������
	ThreadData.tu[0] = 0.0f;
	ThreadData.tu[1] = 1.0f;
	ThreadData.tu[2] = 1.0f;
	ThreadData.tu[3] = 0.0f;

	ThreadData.tv[0] = 0.0f;
	ThreadData.tv[1] = 0.0f;
	ThreadData.tv[2] = 1.0f;
	ThreadData.tv[3] = 1.0f;


	// ���[�v����
	DWORD NowTime = timeGetTime();
	DWORD OldTime = timeGetTime();
	while (m_ThreadDestroyFlag == false)
	{
		NowTime = timeGetTime();
		if (NowTime - OldTime >= (1000 / 60))
		{
			Control(&ThreadData);
			Draw(&ThreadData);

			OldTime = timeGetTime();
		}
	}
	return 0;
}
