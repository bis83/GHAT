#ifndef HANDLESYSTEM_H
#define HANDLESYSTEM_H

#include "SystemGraphics.h"
#include "SystemMedia.h"

//=============================================================
// ChandleGraphics
//-------------------------------------------------------------
// グラフィックスにシーンからアクセスする際に使用するハンドルクラス
//=============================================================
class CHandleGraphics
{
private:
	CSystemGraphics *graphics;
public:
	// コンストラクタ
	CHandleGraphics(CSystemGraphics *_graphics)
	{
		graphics = _graphics;
	}
	// 描画オブジェクトの作成
	void CreateDrawObject(const char* filename, int objectType)
	{
		graphics->CreateDrawObject(filename, objectType);
	}
	// 描画オブジェクトの削除
	void DestroyDrawObject(const char* filename)
	{
		graphics->DestroyDrawObject(filename);
	}
	void DestroyDrawObject(int id)
	{
		graphics->DestroyDrawObject(id);
	}
	// 描画オブジェクトの全削除
	void ClearDrawObject()
	{
		graphics->ClearDrawObject();
	}

	// カメラの取得
	CCamera* GetCamera()
	{
		return graphics->GetCamera();
	}
	// ライトの取得
	CLight* GetLight()
	{
		return graphics->GetLight();
	}
	// 描画オブジェクトIDの取得
	int GetDrawObjectID(const char* filename)
	{
		return graphics->GetDrawObjectID(filename);
	}
	// 描画オブジェクトのステータスを設定
	void SetDrawObjectStatus(int id, DOSTATUS status, void* pValue)
	{
		graphics->SetDrawObjectStatus(id, status, pValue);
	}
	// 描画オブジェクトの描画(シーンのDraw中のみ)
	void DrawObject(int id)
	{
		graphics->DrawObject(id);
	}
};

//=============================================================
// ChandleMedia
//-------------------------------------------------------------
// メディアにシーンからアクセスする際に使用するハンドルクラス
//=============================================================
class CHandleMedia
{
private:
	CSystemMedia *media;
public:
	CHandleMedia(CSystemMedia *_media)
	{
		media = _media;
	}
	// 音声オブジェクトの作成
	void CreateMediaObject(const char* filename, int objectType)
	{
		media->CreateMediaObject(filename, objectType);
	}
	// 音声オブジェクトの開放
	void DestroyMediaObject(const char* filename)
	{
		media->DestroyMediaObject(filename);
	}
	void DestroyMediaObject(int id)
	{
		media->DestroyMediaObject(id);
	}
	// 音声オブジェクトの全削除
	void ClearMediaObject()
	{
		media->ClearMediaObject();
	}

	// BGMの再生
	void PlayBGM(int id, DWORD start = 0)
	{
		media->PlayBGM(id, start);
	}
	void RestartBGM()
	{
		media->RestartBGM();
	}
	// BGMの停止
	void StopBGM()
	{
		media->StopBGM();
	}
	// SEの再生
	void PlaySE(int id)
	{
		media->PlaySE(id);
	}
	// SEの全停止
	void StopSE()
	{
		media->StopSE();
	}
	// 再生ステータスの変更
	void SetPlayStatus(int id, MOSTATUS status, void* pValue)
	{
		media->SetPlayStatus(id, status, pValue);
	}

	// 音声オブジェクトIDの取得
	int GetMediaObjectID(const char* filename)
	{
		return media->GetMediaObjectID(filename);
	}
};

#endif