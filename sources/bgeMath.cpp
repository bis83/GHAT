#include "bgeMath.h"

void MathSpeed(D3DXVECTOR3 aVec, D3DXVECTOR3 bVec, int time, LPD3DXVECTOR3 pVec)
{
	pVec->x = (bVec.x - aVec.x) / time;
	pVec->y = (bVec.y - aVec.y) / time;
	pVec->z = (bVec.z - aVec.z) / time;
}

float MathDirection(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	return ((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y)+(b.z-a.z)*(b.z-a.z));
}

D3DXVECTOR3 MathChangeDirection(D3DXVECTOR3 vecVel, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecTar)
{
	float rad = atan2(vecTar.y - vecPos.y, vecTar.x - vecPos.x);
	float len = sqrt(vecVel.x * vecVel.x + vecVel.y * vecVel.y);
	return D3DXVECTOR3(len * cos(rad), len * sin(rad), vecVel.z);
}