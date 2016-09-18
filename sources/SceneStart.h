#ifndef SCENESTART_H
#define SCENESTART_H

#include "SystemScene.h"
#include "SceneBase.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//=============================================================
// CSceneStart
//-------------------------------------------------------------
// スタートシーン。
// というかファイルの読み込み用。
//=============================================================
class CSceneStart : public CSceneBase
{
public:
	CSceneStart();
	~CSceneStart();

	void Update();
	void Draw();
	void Init(CSystemScene *_system);
	void UnInit();
private:
	vector<char*> file;
	int index;

	// プリーズウェイトID
	int waitID;
	// ウェイト
	int wait;
};

#endif
