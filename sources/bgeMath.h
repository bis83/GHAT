#ifndef BGEMATH_H
#define BGEMATH_H

#include "math.h"
#include "d3dx9.h"

// 2点間の等速移動速度ベクトルを求める関数
void MathSpeed(D3DXVECTOR3 aVec, D3DXVECTOR3 bVec, int time, LPD3DXVECTOR3 pVec);

// 2点間の距離を返す関数
float MathDirection(D3DXVECTOR3 a, D3DXVECTOR3 b);

// ベクトルの大きさをそのままに方向を変更する関数
D3DXVECTOR3 MathChangeDirection(D3DXVECTOR3 vecVel, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecTar);

#endif
