#ifndef MEDIAOBJECT_H
#define MEDIAOBJECT_H

#include "Dsound.h"

#define MOT_MUSIC 1
#define MOT_SOUND 2

typedef enum _MOSTATUS {
	MOS_PAN = 1,
	MOS_FREQUENCY = 2,
	MOS_VOLUME = 3,
} MOSTATUS;

//=============================================================
// CMediaObject
//-------------------------------------------------------------
// メディアオブジェクト。各サウンドの読み込みと再生を行う。
// メディアオブジェクトの基底クラス。
//=============================================================
class CMediaObject
{
public:
	// 生成
	virtual void Create(const char* filename, LPDIRECTSOUND8 pDSound) = 0;
	// 破棄
	virtual void Destroy() = 0;
	// オブジェクトタイプの取得
	int GetObjectType() { return objectType; }
	// 名前の取得
	LPSTR GetName() { return name; }
protected:
	int objectType;
	LPSTR name;
};

//=============================================================
// CObjectMusic
//-------------------------------------------------------------
// BGMのストリーミング再生を行うオブジェクト。
// バッファは最小に抑えて、逐次ファイル読み込みをする。
//=============================================================
class CObjectMusic : public CMediaObject
{
public:
	void Create(const char* filename, LPDIRECTSOUND8 pDSound);
	void Destroy();

	void Play(DWORD start);
	void Restart();
	void Stop();

	BYTE* ReadWavFile(DWORD dwOffset);
	void Update();

	LPDIRECTSOUNDBUFFER pDsoundBuffer;
	//通知区間分だけのWAVデータを読み込む際に使用する
	BYTE* pbWavData;
	// WAVデータのサイズ
	DWORD dwDataSize;
	// DirectSoundバッファのサイズ
	DWORD dwBufferSize;
	// 通知回数
	DWORD dwNumNotify;
	// 通知を発生する間隔のバイトサイズ
	DWORD dwNotifySize;
	//WAVファイルのヘッダー部分を除いた波形データ部分までのオフセット
	DWORD dwDataOffset;

	// バッファ内再生カーソル
	DWORD dwCurPlay;
	// ファイル内読み込みカーソル
	DWORD dwCurRead;
	// DirectSoundバッファー内、次に書き込むオフセット
	DWORD dwNextOffset;
	// WAVデータを最後まで読み込んだときにTRUEになる
	BOOL boEndOfData;

	// リピート
	bool repeat_f;
};

//=============================================================
// CObjectSound
//-------------------------------------------------------------
// SEの再生を行うオブジェクト。
// wavデータは全てメモリ上に移す。
//=============================================================
class CObjectSound : public CMediaObject
{
public:
	void Create(const char* filename, LPDIRECTSOUND8 pDSound);
	void Destroy();

	void Play();
	void Stop();

	LPDIRECTSOUNDBUFFER pDsoundBuffer;
};

#endif
