#ifndef BGEMATH_H
#define BGEMATH_H

#include "math.h"
#include "d3dx9.h"

// 2�_�Ԃ̓����ړ����x�x�N�g�������߂�֐�
void MathSpeed(D3DXVECTOR3 aVec, D3DXVECTOR3 bVec, int time, LPD3DXVECTOR3 pVec);

// 2�_�Ԃ̋�����Ԃ��֐�
float MathDirection(D3DXVECTOR3 a, D3DXVECTOR3 b);

// �x�N�g���̑傫�������̂܂܂ɕ�����ύX����֐�
D3DXVECTOR3 MathChangeDirection(D3DXVECTOR3 vecVel, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecTar);

#endif
