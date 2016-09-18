#ifndef SYSTEMMEDIA_H
#define SYSTEMMEDIA_H

#include "GameHolding.h"
#include "MediaObject.h"

#include <Dsound.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")

#include <vector>

using namespace std;

class CSystemMedia : public CSystemBase
{
public:
	// コンストラクタ、デストラクタ
	CSystemMedia(CGameHolding* _holding, HWND hWnd);
	~CSystemMedia();
	// 更新
	void Update();

	// 音声オブジェクトの作成
	void CreateMediaObject(const char* filename, int objectType);
	// 音声オブジェクトの開放
	void DestroyMediaObject(const char* filename);
	void DestroyMediaObject(int id);
	// 音声オブジェクトの全削除
	void ClearMediaObject();

	// BGMの再生
	void PlayBGM(int id, DWORD start = 0);
	// BGMの再開
	void RestartBGM();
	// BGMの停止
	void StopBGM();
	// SEの再生
	void PlaySE(int id);
	// SEの全停止
	void StopSE();
	// 再生ステータスの変更
	void SetPlayStatus(int id, MOSTATUS status, void* pValue);

	// 音声オブジェクトIDの取得
	int GetMediaObjectID(const char* filename);
private:
	// 初期化
	HRESULT InitDSound(HWND hWnd);

	// DirectSoundObject
	LPDIRECTSOUND8 pDSound;

	// メディアオブジェクトリスト
	vector<CMediaObject*> mediaObjectVector;
	// 再生中BGMのID
	int playingMusicID;
};

#endif
