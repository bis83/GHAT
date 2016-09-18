#ifndef VIRTUALCONTROLLER_H
#define VIRTUALCONTROLLER_H

#define KEYNUM 32
#define ANALOG_X KEYNUM
#define ANALOG_Y KEYNUM+1

class CSystemInput;

//=============================================================
// CPlayController
//-------------------------------------------------------------
// �R���g���[���[�̏���ێ�����N���X�B
// 32�̃{�^���ƃA�i���O�X�e�B�b�N��X,Y�̏���ێ�����B
// GetKey�ŕԂ����int�^�͘A�����ă{�^����������Ă���t���[������Ԃ�
// ANALOG_X, ANALOG_Y�ŕ����L�[�̓��͂��擾�B�l��-1000~1000�B
//=============================================================
class CPlayController
{
private:
	int key[KEYNUM+2];
	bool pushKey_f[KEYNUM];
	int analog[2];
public:
	// �R���X�g���N�^
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

	// �L�[�̎擾
	int GetKey(int keyNumber)
	{
		return key[keyNumber];
	}

	// �L�[������
	void PushKey(int keyNumber)
	{
		if(keyNumber < KEYNUM)
		{
			pushKey_f[keyNumber] = true;
		}
	}
	// �A�i���O�̐ݒ�
	void SetAnalogX(int data)
	{
		analog[0] += data;
	}
	void SetAnalogY(int data)
	{
		analog[1] += data;
	}
	// �L�[�̍X�V
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


	// �f�X�g���N�^
	~CPlayController() {};
};

#endif
