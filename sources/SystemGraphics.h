#ifndef SYSTEMGRAPHICS_H
#define SYSTEMGRAPHICS_H

#include <windows.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "GameHolding.h"
#include "DrawObject.h"
#include "Light.h"
#include "Camera.h"
#include "RenderingManager.h"

#include <vector>
using namespace std;

//=============================================================
// CSystemGraphics
//-------------------------------------------------------------
// グラフィックスに関する全ての処理を統括するクラス。
// Drawを毎フレーム呼び出して描画イベントキューを処理する。
//=============================================================
class CSystemGraphics : public CSystemBase
{
public:
	// コンストラクタ、デストラクタ
	CSystemGraphics(CGameHolding* _holding, HWND hWnd);
	~CSystemGraphics();
	// 描画
	void Draw();
	// リフレッシュ
	void Reflesh();

	// 描画オブジェクトの作成
	void CreateDrawObject(const char* filename, int objectType);
	// 描画オブジェクトの削除
	void DestroyDrawObject(const char* filename);
	void DestroyDrawObject(int id);
	// 描画オブジェクトの全削除
	void ClearDrawObject();

	// カメラの取得
	CCamera* GetCamera();
	// ライトの取得
	CLight* GetLight();
	// 描画オブジェクトIDの取得
	int GetDrawObjectID(const char* filename);
	// 描画オブジェクトのステータスを設定
	void SetDrawObjectStatus(int id, DOSTATUS status, void* pValue);
	// 描画オブジェクトの描画(シーンのDraw中のみ)
	void DrawObject(int id);

	// 描画中かの判定
	bool Drawing();
private:
	// Direct3Dの初期化
	HRESULT InitD3d(HWND hWnd);

	// Direct3D
	LPDIRECT3D9 pD3d;
	// デバイス
	LPDIRECT3DDEVICE9 pDevice;
	// デバイスパラメータ
	D3DPRESENT_PARAMETERS d3dpp;
	// スプライト
	LPD3DXSPRITE pSprite;

	// レンダリングマネージャー
	CRenderingManager renderMgr;

	// 描画オブジェクトリスト
	vector<CDrawObject*> drawObjectVector;
	// 描画エフェクトリスト(今回は未実装？)
	//vector<int> drawEffectVector;

	// カメラ
	CCamera camera;
	// ライト
	CLight light;

	// シーンの開始中か
	bool scene_f;
};

#endif
