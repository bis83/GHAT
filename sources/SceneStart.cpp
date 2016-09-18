#include "SceneStart.h"
#include "SceneDemo.h"
#include "SafeRelease.h"
#include "bgeString.h"

#include "Config.h"

CSceneStart::CSceneStart()
: CSceneBase()
{
	wait = 0;
}

CSceneStart::~CSceneStart()
{
}

void CSceneStart::Init(CSystemScene *_system)
{
	CSceneBase::Init(_system);
	// �ǂݍ��݃��X�g�̃e�L�X�g
	ifstream fin("Data/Text/DataList.txt");
	if(!fin)
	{
		MessageBox(NULL, "DataList�����݂��܂���", NULL, MB_OK);
		return;
	}
	char* token = NULL;
	token = new char[64];
	fin >> token;
	while(!fin.eof())
	{
		file.push_back(token);
		token = NULL;
		token = new char[64];
		fin >> token;
	}
	file.push_back(token);

	// �t�@�C���ǂݍ��݊m�F�p
	/*for(int i=0; i<file.size(); i++)
	{
		MessageBox(NULL, file[i], NULL, MB_OK);
	}*/

	index = 0;
}

void CSceneStart::UnInit()
{
	for(int i=0; i<file.size(); i++)
	{
		SAFE_DELETE_ARRAY(file[i]);
	}
	file.clear();
}

void CSceneStart::Update()
{
	// ���t���[�����Ƃ�1�t�@�C�����ǂݍ���ł���
	if(index < file.size())
	{
		if(!strcmp(file[index], "Mesh"))
		{
			index++;
			GetGraphics()->CreateDrawObject(file[index], DOT_MESH);
		} else if(!strcmp(file[index], "Sprite")) {
			index++;
			GetGraphics()->CreateDrawObject(file[index], DOT_SPRITE);
			int id = GetGraphics()->GetDrawObjectID(file[index]);
			int s[] = {GetIntForStr(file[index+1]), GetIntForStr(file[index+2])};
			GetGraphics()->SetDrawObjectStatus(id, DOS_SIZE, &s);
			index += 2;
		} else if(!strcmp(file[index], "Font")) {
			index++;
			GetGraphics()->CreateDrawObject(file[index], DOT_FONT);
			int id = GetGraphics()->GetDrawObjectID(file[index]);
			int s[] = {GetIntForStr(file[index+1]), GetIntForStr(file[index+2])};
			GetGraphics()->SetDrawObjectStatus(id, DOS_SIZE, &s);
			index += 2;
		} else if(!strcmp(file[index], "Music")) {
			index++;
			GetMedia()->CreateMediaObject(file[index], MOT_MUSIC);
		} else if(!strcmp(file[index], "Sound")) {
			index++;
			GetMedia()->CreateMediaObject(file[index], MOT_SOUND);
		}
		index++;
	} else {
		if(wait < 60)
		{
			wait++;
			return;
		}
		// �S�Ă̓ǂݍ��݂��I�������玟�̃V�[��(�f��)
		MoveScene(new CSceneDemo());
	}
}

void CSceneStart::Draw()
{
	// �ǂݍ��ݒ��̓v���[�Y�E�F�C�g�摜��\�����Ă���
	int id = GetGraphics()->GetDrawObjectID("Data/Texture/pleaseWait.png");
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, 1160, 680, 0);
	if(GetInput(0, e_Config.key_ok))
	{
		D3DCOLOR color = D3DCOLOR_ARGB(128, 255, 255, 255);
		GetGraphics()->SetDrawObjectStatus(id, DOS_COLOR, &color);
	}
	GetGraphics()->SetDrawObjectStatus(id, DOS_MATRIX, &mat);
	GetGraphics()->DrawObject(id);

	id = GetGraphics()->GetDrawObjectID("Data/Texture/title.png");
	D3DXMatrixTranslation(&mat, 640, 360, 0);
	GetGraphics()->SetDrawObjectStatus(id, DOS_MATRIX, &mat);
	GetGraphics()->DrawObject(id);
}
