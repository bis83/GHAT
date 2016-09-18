#ifndef VIRTUALCONTROLLER_H
#define VIRTUALCONTROLLER_H

#define KEYNUM 32
#define ANALOG_X KEYNUM
#define ANALOG_Y KEYNUM+1

class CSystemInput;

//=============================================================
// CPlayController
//-------------------------------------------------------------
// コントローラーの情報を保持するクラス。
// 32個のボタンとアナログスティックのX,Yの情報を保持する。
// GetKeyで返されるint型は連続してボタンを押されているフレーム数を返す
// ANALOG_X, ANALOG_Yで方向キーの入力を取得。値は-1000~1000。
//=============================================================
class CPlayController
{
private:
	int key[KEYNUM+2];
	bool pushKey_f[KEYNUM];
	int analog[2];
public:
	// コンストラクタ
	CPlayController()
	{
		for(int i=0; i<KEYNUM; i++)
		{
			key[i] = 0;
			pushKey_f[i] = false;
		}
		key[ANALOG_X] = 0;
		key[ANALOG_Y] = 0;
		analog[0] = 0;
		analog[1] = 0;
	}

	// キーの取得
	int GetKey(int keyNumber)
	{
		return key[keyNumber];
	}

	// キーを押す
	void PushKey(int keyNumber)
	{
		if(keyNumber < KEYNUM)
		{
			pushKey_f[keyNumber] = true;
		}
	}
	// アナログの設定
	void SetAnalogX(int data)
	{
		analog[0] += data;
	}
	void SetAnalogY(int data)
	{
		analog[1] += data;
	}
	// キーの更新
	void Update()
	{
		for(int i=0; i<KEYNUM; i++)
		{
			if(pushKey_f[i])
			{
				key[i]++;
			} else {
				key[i] = 0;
			}
			pushKey_f[i] = false;
		}
		key[ANALOG_X] = analog[0];
		key[ANALOG_Y] = analog[1];
		analog[0] = 0;
		analog[1] = 0;
	}


	// デストラクタ
	~CPlayController() {};
};

#endif
