#include "MediaObject.h"
#include "SystemMedia.h"
#include "SafeRelease.h"

// ミュージックオブジェクト
void CObjectMusic::Create(const char *filename, LPDIRECTSOUND8 pDSound)
{
	// 名前とオブジェクト番号の設定
	objectType = MOT_MUSIC;
	name = new TCHAR[strlen(filename)+1];
	strcpy(name, filename);

	// wavファイルを開いていく
	HMMIO hMmio = NULL;
	DWORD dwWavSize = 0;
	WAVEFORMATEX* pwfex;
	MMCKINFO ckInfo;
	MMCKINFO riffckInfo;
	PCMWAVEFORMAT pcmWaveFormat;

	hMmio = mmioOpen(name, NULL, MMIO_ALLOCBUF | MMIO_READ);

	if(MMSYSERR_NOERROR !=mmioDescend(hMmio, &riffckInfo, NULL, NULL))
	{
		MessageBox(NULL, "最初のチャンクに進入できません。", name, MB_OK);
		return;
	}
	if( (riffckInfo.ckid != mmioFOURCC('R', 'I', 'F', 'F')) || (riffckInfo.fccType != mmioFOURCC('W', 'A', 'V', 'E') ) )
	{
		MessageBox(NULL, "これはWAVファイルではありません", name, MB_OK);
		return;
	}
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if(MMSYSERR_NOERROR != mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK))
	{
		MessageBox(NULL, "fmtチャンクが見つかりません。", name, MB_OK);
		return;
	}
	mmioRead(hMmio, (HPSTR)&pcmWaveFormat, sizeof(pcmWaveFormat));
	/*{
		MessageBox(NULL, "SoundObjectの生成に失敗", name, MB_OK);
		return;
	}*/
	if( pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM )
    {
        pwfex = (WAVEFORMATEX*)new CHAR[ sizeof(WAVEFORMATEX) ];
        if( NULL == pwfex )
		{
			MessageBox(NULL, "失敗", NULL, MB_OK);
			return;
		}  
        memcpy( pwfex, &pcmWaveFormat, sizeof(pcmWaveFormat) );
        pwfex->cbSize = 0;
    }
    else
	{
		MessageBox(0,"本サンプルは標準のリニアPCMフォーマットを想定しています","",MB_OK);
		return;
	}
	if(MMSYSERR_NOERROR != mmioAscend(hMmio, &ckInfo, NULL))
	{
		MessageBox(NULL, "失敗", NULL, MB_OK);
		return;
	}
	// waveファイル内の音データを読み込む
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
	dwWavSize = ckInfo.cksize;
	// 通知サイズ及び通知回数を設定する
	DWORD nBlockAlign = (DWORD)pcmWaveFormat.wf.nBlockAlign;
	INT nSamplesPerSec = pcmWaveFormat.wf.nSamplesPerSec;
	dwNumNotify = 4;
	dwNotifySize = nSamplesPerSec * 4 * nBlockAlign / dwNumNotify;		// 1秒ごと
	dwNotifySize -= dwNotifySize % nBlockAlign;
	// サウンドバッファーを作成する
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
		MessageBox(NULL, "サウンドバッファーの作成に失敗", name, MB_OK);
		return;
	}
	delete pwfex;

	// バッファを無音にしてバッファのサイズを取得する
	VOID* pBuffer;
	pDsoundBuffer->Lock(0, dsbd.dwBufferBytes, &pBuffer, &dwBufferSize, NULL, NULL, 0);
	memset(pBuffer, 0, dwBufferSize);
	pDsoundBuffer->Unlock(pBuffer, dwBufferSize, NULL, NULL);

	// 各種再生用データを初期化する
	pbWavData = new BYTE[dwNotifySize];
	dwDataSize = dwWavSize;
	dwCurPlay = 0;
	dwCurRead = 0;
	dwNextOffset = 0;
	boEndOfData = FALSE;
	dwDataOffset = riffckInfo.dwDataOffset + sizeof(FOURCC);

	// 各種フラグを初期化する
	repeat_f = true;
}

void CObjectMusic::Destroy()
{
	SAFE_DELETE_ARRAY(pbWavData);
	SAFE_RELEASE(pDsoundBuffer);
}

void CObjectMusic::Play(DWORD start)
{
	// Wavファイルの読み込みカーソルを再生スタート位置にセット
	// (通知間隔に合わせるために端を切る)
	dwCurRead = (start / dwNotifySize) * dwNotifySize;
	dwCurPlay = 0;
	dwNextOffset = 0;
	boEndOfData = FALSE;

	// 初回のバッファ分を読み込む
	VOID* pBuffer;
	DWORD dwSize;

	pDsoundBuffer->Lock(0, dwBufferSize, &pBuffer, &dwSize, NULL, NULL, 0);

	FILE* fp = fopen(name, "rb");
	if(fp == NULL)
	{
		MessageBox(NULL, "ストリーム再生用ファイルが存在しません", name, MB_OK);
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

	// 読み込みカーソルをバッファ分進める
	dwCurRead += dwSize;

	// 再生を開始する
	pDsoundBuffer->SetCurrentPosition(0);
	pDsoundBuffer->Play(NULL, 0, DSBPLAY_LOOPING);
}

void CObjectMusic::Restart()
{
	// 再生を開始する
	pDsoundBuffer->Play(NULL, 0, DSBPLAY_LOOPING);
}

void CObjectMusic::Stop()
{
	pDsoundBuffer->Stop();
}

// ファイル読み込み関数
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
	// 再生カーソルの位置を取得
	pDsoundBuffer->GetCurrentPosition(&dwCurPlay, NULL);

	// 再生カーソルが通知地点を越えたとき
	if((dwCurPlay > dwNextOffset+dwNotifySize)
		|| ((dwCurPlay < dwNotifySize) && (dwNextOffset != 0)))
	{
		VOID* pv;
		DWORD dwSize;

		// 次の読み込みで終端に到達する場合
		if(dwCurRead + dwNotifySize >= dwDataSize)
		{
			if(repeat_f)
			{
				pDsoundBuffer->Lock(dwNextOffset, dwNotifySize, &pv, &dwSize, NULL, NULL, 0);
				// バッファにwavデータをコピーする
				memcpy(pv, ReadWavFile(dwCurRead), dwDataSize-dwCurRead);
				memset(((BYTE*)pv+(dwDataSize-dwCurRead)), 0, dwCurRead+dwNotifySize-dwDataSize);
				pDsoundBuffer->Unlock(pv, dwSize, NULL, NULL);
				dwNextOffset += dwNotifySize;
				dwNextOffset %= dwBufferSize;
				// 読み込みカーソルを初期位置に戻す
				dwCurRead = 0;
				return;
			} else {
				// 終了地点フラグをたてる
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
		// バッファにwavデータをコピーする
		memcpy(pv, ReadWavFile(dwCurRead), dwSize);
		pDsoundBuffer->Unlock(pv, dwSize, NULL, NULL);
		dwNextOffset += dwSize;
		dwNextOffset %= dwBufferSize;
		// 読み込みカーソルを進める
		dwCurRead += dwSize;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

// サウンドオブジェクト

void CObjectSound::Create(const char *filename, LPDIRECTSOUND8 pDSound)
{
	// 名前とオブジェクト番号の設定
	objectType = MOT_SOUND;
	name = new TCHAR[strlen(filename)+1];
	strcpy(name, filename);

	// wavファイルを開いていく
	HMMIO hMmio = NULL;
	DWORD dwWavSize = 0;
	WAVEFORMATEX* pwfex;
	MMCKINFO ckInfo;
	MMCKINFO riffckInfo;
	PCMWAVEFORMAT pcmWaveFormat;
	hMmio = mmioOpen(name, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if(MMSYSERR_NOERROR !=mmioDescend(hMmio, &riffckInfo, NULL, NULL))
	{
		MessageBox(NULL, "SoundObjectの生成に失敗", name, MB_OK);
		return;
	}
	if( (riffckInfo.ckid != mmioFOURCC('R', 'I', 'F', 'F')) || (riffckInfo.fccType != mmioFOURCC('W', 'A', 'V', 'E') ) )
	{
		MessageBox(NULL, "これはWAVファイルではありません", name, MB_OK);
		return;
	}
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if(MMSYSERR_NOERROR != mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK))
	{
		MessageBox(NULL, "SoundObjectの生成に失敗", name, MB_OK);
		return;
	}
	mmioRead(hMmio, (HPSTR) &pcmWaveFormat, sizeof(pcmWaveFormat));
	/*{
		MessageBox(NULL, "mmio読み込み失敗", NULL, MB_OK);
		return;
	}*/
	//リニアPCMで、かつ、マルチチャンネルWAVは想定外
    if( pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM )
    {
        pwfex = (WAVEFORMATEX*)new CHAR[ sizeof(WAVEFORMATEX) ];
        if( NULL == pwfex )
		{
			MessageBox(NULL, "失敗", NULL, MB_OK);
			return;
		}
        memcpy( pwfex, &pcmWaveFormat, sizeof(pcmWaveFormat) );
        pwfex->cbSize = 0;
    }
    else
	{
		MessageBox(0,"本サンプルは標準のリニアPCMフォーマットを想定しています","",MB_OK);
		return;
	}
	if(MMSYSERR_NOERROR !=mmioAscend(hMmio, &ckInfo, NULL))
	{
		delete pwfex;
		MessageBox(NULL, "失敗", NULL, MB_OK);
		return;
	}
	// waveファイル内の音データを読み込む
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if(MMSYSERR_NOERROR != mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK))
	{
		delete pwfex;
		MessageBox(NULL, "mmio読み込み失敗", NULL, MB_OK);
		return;
	}
	dwWavSize = ckInfo.cksize;
	// サウンドバッファーの作成
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
		MessageBox(NULL, "サウンドバッファーの作成に失敗", name, MB_OK);
		return;
	}
	delete pwfex;
	// 波形データを書き込むためにバッファをロックする
	VOID* pBuffer = NULL;
	DWORD dwBufferSize = 0;
	pDsoundBuffer->Lock(0, dwWavSize, &pBuffer, &dwBufferSize, NULL, NULL, 0);
	// バッファに波形データを書き込む
	FILE* fp=fopen(name, "rb");
	if(fp == NULL)
	{
		MessageBox(NULL, "ファイルが存在しません", name, MB_OK);
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
	// 書き込みを終了してバッファをアンロックする
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