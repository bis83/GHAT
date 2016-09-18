#include "MediaObject.h"
#include "SystemMedia.h"
#include "SafeRelease.h"

// �~���[�W�b�N�I�u�W�F�N�g
void CObjectMusic::Create(const char *filename, LPDIRECTSOUND8 pDSound)
{
	// ���O�ƃI�u�W�F�N�g�ԍ��̐ݒ�
	objectType = MOT_MUSIC;
	name = new TCHAR[strlen(filename)+1];
	strcpy(name, filename);

	// wav�t�@�C�����J���Ă���
	HMMIO hMmio = NULL;
	DWORD dwWavSize = 0;
	WAVEFORMATEX* pwfex;
	MMCKINFO ckInfo;
	MMCKINFO riffckInfo;
	PCMWAVEFORMAT pcmWaveFormat;

	hMmio = mmioOpen(name, NULL, MMIO_ALLOCBUF | MMIO_READ);

	if(MMSYSERR_NOERROR !=mmioDescend(hMmio, &riffckInfo, NULL, NULL))
	{
		MessageBox(NULL, "�ŏ��̃`�����N�ɐi���ł��܂���B", name, MB_OK);
		return;
	}
	if( (riffckInfo.ckid != mmioFOURCC('R', 'I', 'F', 'F')) || (riffckInfo.fccType != mmioFOURCC('W', 'A', 'V', 'E') ) )
	{
		MessageBox(NULL, "�����WAV�t�@�C���ł͂���܂���", name, MB_OK);
		return;
	}
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if(MMSYSERR_NOERROR != mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK))
	{
		MessageBox(NULL, "fmt�`�����N��������܂���B", name, MB_OK);
		return;
	}
	mmioRead(hMmio, (HPSTR)&pcmWaveFormat, sizeof(pcmWaveFormat));
	/*{
		MessageBox(NULL, "SoundObject�̐����Ɏ��s", name, MB_OK);
		return;
	}*/
	if( pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM )
    {
        pwfex = (WAVEFORMATEX*)new CHAR[ sizeof(WAVEFORMATEX) ];
        if( NULL == pwfex )
		{
			MessageBox(NULL, "���s", NULL, MB_OK);
			return;
		}  
        memcpy( pwfex, &pcmWaveFormat, sizeof(pcmWaveFormat) );
        pwfex->cbSize = 0;
    }
    else
	{
		MessageBox(0,"�{�T���v���͕W���̃��j�APCM�t�H�[�}�b�g��z�肵�Ă��܂�","",MB_OK);
		return;
	}
	if(MMSYSERR_NOERROR != mmioAscend(hMmio, &ckInfo, NULL))
	{
		MessageBox(NULL, "���s", NULL, MB_OK);
		return;
	}
	// wave�t�@�C�����̉��f�[�^��ǂݍ���
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
	dwWavSize = ckInfo.cksize;
	// �ʒm�T�C�Y�y�ђʒm�񐔂�ݒ肷��
	DWORD nBlockAlign = (DWORD)pcmWaveFormat.wf.nBlockAlign;
	INT nSamplesPerSec = pcmWaveFormat.wf.nSamplesPerSec;
	dwNumNotify = 4;
	dwNotifySize = nSamplesPerSec * 4 * nBlockAlign / dwNumNotify;		// 1�b����
	dwNotifySize -= dwNotifySize % nBlockAlign;
	// �T�E���h�o�b�t�@�[���쐬����
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
	dsbd.dwBufferBytes = dwNotifySize * dwNumNotify;
	dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
	dsbd.lpwfxFormat = pwfex;
	if(FAILED(pDSound->CreateSoundBuffer(&dsbd, &pDsoundBuffer, NULL)))
	{
		delete pwfex;
		MessageBox(NULL, "�T�E���h�o�b�t�@�[�̍쐬�Ɏ��s", name, MB_OK);
		return;
	}
	delete pwfex;

	// �o�b�t�@�𖳉��ɂ��ăo�b�t�@�̃T�C�Y���擾����
	VOID* pBuffer;
	pDsoundBuffer->Lock(0, dsbd.dwBufferBytes, &pBuffer, &dwBufferSize, NULL, NULL, 0);
	memset(pBuffer, 0, dwBufferSize);
	pDsoundBuffer->Unlock(pBuffer, dwBufferSize, NULL, NULL);

	// �e��Đ��p�f�[�^������������
	pbWavData = new BYTE[dwNotifySize];
	dwDataSize = dwWavSize;
	dwCurPlay = 0;
	dwCurRead = 0;
	dwNextOffset = 0;
	boEndOfData = FALSE;
	dwDataOffset = riffckInfo.dwDataOffset + sizeof(FOURCC);

	// �e��t���O������������
	repeat_f = true;
}

void CObjectMusic::Destroy()
{
	SAFE_DELETE_ARRAY(pbWavData);
	SAFE_RELEASE(pDsoundBuffer);
}

void CObjectMusic::Play(DWORD start)
{
	// Wav�t�@�C���̓ǂݍ��݃J�[�\�����Đ��X�^�[�g�ʒu�ɃZ�b�g
	// (�ʒm�Ԋu�ɍ��킹�邽�߂ɒ[��؂�)
	dwCurRead = (start / dwNotifySize) * dwNotifySize;
	dwCurPlay = 0;
	dwNextOffset = 0;
	boEndOfData = FALSE;

	// ����̃o�b�t�@����ǂݍ���
	VOID* pBuffer;
	DWORD dwSize;

	pDsoundBuffer->Lock(0, dwBufferSize, &pBuffer, &dwSize, NULL, NULL, 0);

	FILE* fp = fopen(name, "rb");
	if(fp == NULL)
	{
		MessageBox(NULL, "�X�g���[���Đ��p�t�@�C�������݂��܂���", name, MB_OK);
	}
	fseek(fp, dwDataOffset+dwCurRead, SEEK_SET);
	BYTE* pData = new BYTE[dwBufferSize];
	fread(pData, 1, dwBufferSize, fp);
	for(DWORD i=0; i<dwBufferSize; i++)
	{
		*((BYTE*)pBuffer+i) = *((BYTE*) pData+i); 
	}
	fclose(fp);

	pDsoundBuffer->Unlock(pBuffer, dwSize, NULL, NULL);
	delete pData;

	// �ǂݍ��݃J�[�\�����o�b�t�@���i�߂�
	dwCurRead += dwSize;

	// �Đ����J�n����
	pDsoundBuffer->SetCurrentPosition(0);
	pDsoundBuffer->Play(NULL, 0, DSBPLAY_LOOPING);
}

void CObjectMusic::Restart()
{
	// �Đ����J�n����
	pDsoundBuffer->Play(NULL, 0, DSBPLAY_LOOPING);
}

void CObjectMusic::Stop()
{
	pDsoundBuffer->Stop();
}

// �t�@�C���ǂݍ��݊֐�
BYTE* CObjectMusic::ReadWavFile(DWORD dwCur)
{
	FILE* fp=fopen(name, "rb");
	fseek(fp, dwDataOffset+dwCur, SEEK_SET);
	fread(pbWavData, 1, dwNotifySize, fp);
	fclose(fp);
	return pbWavData;
}

void CObjectMusic::Update()
{
	// �Đ��J�[�\���̈ʒu���擾
	pDsoundBuffer->GetCurrentPosition(&dwCurPlay, NULL);

	// �Đ��J�[�\�����ʒm�n�_���z�����Ƃ�
	if((dwCurPlay > dwNextOffset+dwNotifySize)
		|| ((dwCurPlay < dwNotifySize) && (dwNextOffset != 0)))
	{
		VOID* pv;
		DWORD dwSize;

		// ���̓ǂݍ��݂ŏI�[�ɓ��B����ꍇ
		if(dwCurRead + dwNotifySize >= dwDataSize)
		{
			if(repeat_f)
			{
				pDsoundBuffer->Lock(dwNextOffset, dwNotifySize, &pv, &dwSize, NULL, NULL, 0);
				// �o�b�t�@��wav�f�[�^���R�s�[����
				memcpy(pv, ReadWavFile(dwCurRead), dwDataSize-dwCurRead);
				memset(((BYTE*)pv+(dwDataSize-dwCurRead)), 0, dwCurRead+dwNotifySize-dwDataSize);
				pDsoundBuffer->Unlock(pv, dwSize, NULL, NULL);
				dwNextOffset += dwNotifySize;
				dwNextOffset %= dwBufferSize;
				// �ǂݍ��݃J�[�\���������ʒu�ɖ߂�
				dwCurRead = 0;
				return;
			} else {
				// �I���n�_�t���O�����Ă�
				boEndOfData = TRUE;

				pDsoundBuffer->Lock(dwNextOffset, dwNotifySize, &pv, &dwSize, NULL, NULL, 0);
				memset(pv, 0, dwSize);
				pDsoundBuffer->Unlock(pv, dwSize, NULL, NULL);
				dwNextOffset += dwSize;
				dwNextOffset %= dwBufferSize;
				return;
			}
		}

		pDsoundBuffer->Lock(dwNextOffset, dwNotifySize, &pv, &dwSize, NULL, NULL, 0);
		// �o�b�t�@��wav�f�[�^���R�s�[����
		memcpy(pv, ReadWavFile(dwCurRead), dwSize);
		pDsoundBuffer->Unlock(pv, dwSize, NULL, NULL);
		dwNextOffset += dwSize;
		dwNextOffset %= dwBufferSize;
		// �ǂݍ��݃J�[�\����i�߂�
		dwCurRead += dwSize;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

// �T�E���h�I�u�W�F�N�g

void CObjectSound::Create(const char *filename, LPDIRECTSOUND8 pDSound)
{
	// ���O�ƃI�u�W�F�N�g�ԍ��̐ݒ�
	objectType = MOT_SOUND;
	name = new TCHAR[strlen(filename)+1];
	strcpy(name, filename);

	// wav�t�@�C�����J���Ă���
	HMMIO hMmio = NULL;
	DWORD dwWavSize = 0;
	WAVEFORMATEX* pwfex;
	MMCKINFO ckInfo;
	MMCKINFO riffckInfo;
	PCMWAVEFORMAT pcmWaveFormat;
	hMmio = mmioOpen(name, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if(MMSYSERR_NOERROR !=mmioDescend(hMmio, &riffckInfo, NULL, NULL))
	{
		MessageBox(NULL, "SoundObject�̐����Ɏ��s", name, MB_OK);
		return;
	}
	if( (riffckInfo.ckid != mmioFOURCC('R', 'I', 'F', 'F')) || (riffckInfo.fccType != mmioFOURCC('W', 'A', 'V', 'E') ) )
	{
		MessageBox(NULL, "�����WAV�t�@�C���ł͂���܂���", name, MB_OK);
		return;
	}
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if(MMSYSERR_NOERROR != mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK))
	{
		MessageBox(NULL, "SoundObject�̐����Ɏ��s", name, MB_OK);
		return;
	}
	mmioRead(hMmio, (HPSTR) &pcmWaveFormat, sizeof(pcmWaveFormat));
	/*{
		MessageBox(NULL, "mmio�ǂݍ��ݎ��s", NULL, MB_OK);
		return;
	}*/
	//���j�APCM�ŁA���A�}���`�`�����l��WAV�͑z��O
    if( pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM )
    {
        pwfex = (WAVEFORMATEX*)new CHAR[ sizeof(WAVEFORMATEX) ];
        if( NULL == pwfex )
		{
			MessageBox(NULL, "���s", NULL, MB_OK);
			return;
		}
        memcpy( pwfex, &pcmWaveFormat, sizeof(pcmWaveFormat) );
        pwfex->cbSize = 0;
    }
    else
	{
		MessageBox(0,"�{�T���v���͕W���̃��j�APCM�t�H�[�}�b�g��z�肵�Ă��܂�","",MB_OK);
		return;
	}
	if(MMSYSERR_NOERROR !=mmioAscend(hMmio, &ckInfo, NULL))
	{
		delete pwfex;
		MessageBox(NULL, "���s", NULL, MB_OK);
		return;
	}
	// wave�t�@�C�����̉��f�[�^��ǂݍ���
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if(MMSYSERR_NOERROR != mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK))
	{
		delete pwfex;
		MessageBox(NULL, "mmio�ǂݍ��ݎ��s", NULL, MB_OK);
		return;
	}
	dwWavSize = ckInfo.cksize;
	// �T�E���h�o�b�t�@�[�̍쐬
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
	dsbd.dwBufferBytes = dwWavSize;
	dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
	dsbd.lpwfxFormat = pwfex;
	if(FAILED(pDSound->CreateSoundBuffer(&dsbd, &pDsoundBuffer, NULL)))
	{
		delete pwfex;
		MessageBox(NULL, "�T�E���h�o�b�t�@�[�̍쐬�Ɏ��s", name, MB_OK);
		return;
	}
	delete pwfex;
	// �g�`�f�[�^���������ނ��߂Ƀo�b�t�@�����b�N����
	VOID* pBuffer = NULL;
	DWORD dwBufferSize = 0;
	pDsoundBuffer->Lock(0, dwWavSize, &pBuffer, &dwBufferSize, NULL, NULL, 0);
	// �o�b�t�@�ɔg�`�f�[�^����������
	FILE* fp=fopen(name, "rb");
	if(fp == NULL)
	{
		MessageBox(NULL, "�t�@�C�������݂��܂���", name, MB_OK);
	}
	fseek(fp, riffckInfo.dwDataOffset+sizeof(FOURCC), SEEK_SET);
	BYTE* pWavData = new BYTE[dwBufferSize];
	fread(pWavData, 1, dwBufferSize, fp);
	for(DWORD i = 0; i<dwBufferSize; i++)
	{
		*((BYTE*)pBuffer+i) = *((BYTE*)pWavData+i);
	}
	fclose(fp);
	delete pWavData;
	// �������݂��I�����ăo�b�t�@���A�����b�N����
	pDsoundBuffer->Unlock(pBuffer, dwBufferSize, NULL, 0);
}

void CObjectSound::Destroy()
{
	SAFE_RELEASE(pDsoundBuffer);
}
void CObjectSound::Play()
{
	pDsoundBuffer->SetCurrentPosition(0);
	pDsoundBuffer->Play(NULL, 0, NULL);
}
void CObjectSound::Stop()
{
	pDsoundBuffer->Stop();
}