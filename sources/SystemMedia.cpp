#include "SystemMedia.h"
#include "SafeRelease.h"

CSystemMedia::CSystemMedia(CGameHolding *_holding, HWND hWnd)
: CSystemBase(_holding)
{
	InitDSound(hWnd);

	playingMusicID = 0;
	ClearMediaObject();
}

CSystemMedia::~CSystemMedia()
{
	ClearMediaObject();
	SAFE_RELEASE(pDSound);
}

void CSystemMedia::Update()
{
	if(playingMusicID)
	{
		((CObjectMusic*)mediaObjectVector[playingMusicID-1])->Update();
	}
}

HRESULT CSystemMedia::InitDSound(HWND hWnd)
{
	if(FAILED(DirectSoundCreate8(NULL, &pDSound, NULL)))
	{
		return E_FAIL;
	}
	pDSound->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);

	return S_OK;
}

void CSystemMedia::CreateMediaObject(const char *filename, int objectType)
{
	if(objectType == MOT_MUSIC)
	{
		CObjectMusic* obj = new CObjectMusic();
		obj->Create(filename, pDSound);
		for(int i=0; i<mediaObjectVector.size(); i++)
		{
			if(mediaObjectVector[i] == NULL)
			{
				mediaObjectVector[i] = obj;
				return;
			}
		}
		mediaObjectVector.push_back(obj);
		return;
	}
	if(objectType == MOT_SOUND)
	{
		CObjectSound* obj = new CObjectSound();
		obj->Create(filename, pDSound);
		for(int i=0; i<mediaObjectVector.size(); i++)
		{
			if(mediaObjectVector[i] == NULL)
			{
				mediaObjectVector[i] = obj;
				return;
			}
		}
		mediaObjectVector.push_back(obj);
		return;
	}
}

void CSystemMedia::DestroyMediaObject(const char *filename)
{
	for(int i=0; i<mediaObjectVector.size(); i++)
	{
		if(!strcmp(mediaObjectVector[i]->GetName(), filename))
		{
			mediaObjectVector[i]->Destroy();
			SAFE_DELETE(mediaObjectVector[i]);
			return;
		}
	}
}

void CSystemMedia::DestroyMediaObject(int id)
{
	if((id < 1) || (id > mediaObjectVector.size()))
	{
		return;
	}
	if(mediaObjectVector[id-1] != NULL)
	{
		mediaObjectVector[id-1]->Destroy();
		SAFE_DELETE(mediaObjectVector[id-1]);
	}
}

void CSystemMedia::ClearMediaObject()
{
	for(int i=0; i<mediaObjectVector.size(); i++)
	{
		if(mediaObjectVector[i] != NULL)
		{
			mediaObjectVector[i]->Destroy();
			SAFE_DELETE(mediaObjectVector[i]);
		}
	}
	mediaObjectVector.clear();
}

int CSystemMedia::GetMediaObjectID(const char *filename)
{
	for(int i=0; i<mediaObjectVector.size(); i++)
	{
		if(!strcmp(mediaObjectVector[i]->GetName(), filename))
		{
			return i+1;
		}
	}
}

void CSystemMedia::PlayBGM(int id, DWORD start)
{
	if(playingMusicID != 0)
	{
		StopBGM();
	}
	if((id < 1) || (id > mediaObjectVector.size()))
	{
		return;
	}
	if(mediaObjectVector[id-1]->GetObjectType() != MOT_MUSIC)
	{
		return;
	}
	((CObjectMusic*)mediaObjectVector[id-1])->Play(start);
	playingMusicID = id;
}

void CSystemMedia::RestartBGM()
{
	if(playingMusicID != NULL)
	{
		((CObjectMusic*)mediaObjectVector[playingMusicID-1])->Restart();
	}
}

void CSystemMedia::StopBGM()
{
	if((playingMusicID-1 < 1) || (playingMusicID-1 > mediaObjectVector.size()))
	{
		return;
	}
	if(mediaObjectVector[playingMusicID-1]->GetObjectType() != MOT_MUSIC)
	{
		return;
	}
	((CObjectMusic*)mediaObjectVector[playingMusicID-1])->Stop();
}

void CSystemMedia::PlaySE(int id)
{
	if((id < 1) || (id > mediaObjectVector.size()))
	{
		return;
	}
	if(mediaObjectVector[id-1]->GetObjectType() != MOT_SOUND)
	{
		return;
	}
	((CObjectSound*)mediaObjectVector[id-1])->Play();
}

void CSystemMedia::StopSE()
{
	for(int i=0; i<mediaObjectVector.size(); i++)
	{
		if(mediaObjectVector[i]->GetObjectType() == MOT_SOUND)
		{
			((CObjectSound*)mediaObjectVector[i])->Stop();
		}
	}
}

void CSystemMedia::SetPlayStatus(int id, MOSTATUS status, void* pValue)
{
	if(id < 1 || id > mediaObjectVector.size())
	{
		return;
	}
	if(mediaObjectVector[id-1] == NULL)
	{
		return;
	}
	switch(status)
	{
	case MOS_PAN:
		switch(mediaObjectVector[id-1]->GetObjectType())
		{
		case MOT_MUSIC:
			((CObjectMusic*)mediaObjectVector[id-1])->pDsoundBuffer->SetPan(*((INT*)pValue));
			break;
		case MOT_SOUND:
			((CObjectSound*)mediaObjectVector[id-1])->pDsoundBuffer->SetPan(*((INT*)pValue));
			break;
		}
		break;
	case MOS_FREQUENCY:
		switch(mediaObjectVector[id-1]->GetObjectType())
		{
		case MOT_MUSIC:
			((CObjectMusic*)mediaObjectVector[id-1])->pDsoundBuffer->SetFrequency(*((DWORD*)pValue));
			break;
		case MOT_SOUND:
			((CObjectSound*)mediaObjectVector[id-1])->pDsoundBuffer->SetFrequency(*((DWORD*)pValue));
			break;
		}
		break;
	case MOS_VOLUME:
		switch(mediaObjectVector[id-1]->GetObjectType())
		{
		case MOT_MUSIC:
			((CObjectMusic*)mediaObjectVector[id-1])->pDsoundBuffer->SetVolume( (LONG)((100 - (*((int*)pValue))) * DSBVOLUME_MIN / 100) );
			break;
		case MOT_SOUND:
			((CObjectSound*)mediaObjectVector[id-1])->pDsoundBuffer->SetVolume( (LONG)((100 - (*((int*)pValue))) * DSBVOLUME_MIN / 100));
			break;
		}
		break;
	}
}
