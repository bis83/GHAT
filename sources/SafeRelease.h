#ifndef SAFERELEASE_H
#define SAFERELEASE_H

#include <d3dx9.h>

//=============================================================
// ���S�ȊJ�����s���}�N��
//=============================================================

#define SAFE_DELETE(p) { if((p) != NULL) { delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p) { delete[] (p); (p) = NULL; } 
#define SAFE_RELEASE(p) { if((p) != NULL) { (p)->Release(); (p) = NULL; } }

#endif
