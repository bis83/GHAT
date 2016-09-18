#include "DrawEvent.h"

void CDrawEventStack::Create(int max_num_event)
{
	queue = new SDrawEvent[max_num_event+2];
	for(int i=0; i<max_num_event+2; i++)
	{
		ZeroMemory(&queue[i], sizeof(SDrawEvent));
	}
	active = &queue[0];
	active->next = active;
	free = &queue[1];
	free->next = &queue[2];
	for(int i=2; i<max_num_event+1; i++)
	{
		queue[i].next = &queue[i+1];
	}
	queue[max_num_event+2].next = free;
}

void CDrawEventStack::Push(SDrawEvent &ev)
{
	if(free->next != free)
	{
		SDrawEvent* temp = active->next->next;
		active->next = free->next;
		free->next = free->next->next;
		active->next->next = temp;
		*active->next = ev;
	}
}

void CDrawEventStack::Pop()
{
	if(active->next != active)
	{
		SDrawEvent* temp = active->next->next;
		active->next->next = free->next;
		free->next = active->next;
		active->next = temp;
	}
}

void CDrawEventStack::Clear()
{
	while(active->next != active)
	{
		Pop();
	}
}

SDrawEvent* CDrawEventStack::GetFront()
{
	return active->next;
}

INT Compare(const VOID* a, const VOID* b)
{
	SDrawEvent** ppEvA = (SDrawEvent**)a;
	SDrawEvent** ppEvB = (SDrawEvent**)b;
	D3DXMATRIXA16 matA;
	D3DXMATRIXA16 matB;
	D3DXMATRIXA16 matView;
	D3DXMatrixIdentity(&matA);
	D3DXMatrixIdentity(&matB);
	D3DXMatrixIdentity(&matView);

	D3DXMatrixMultiply(&matA, &((*ppEvA)->matWorld), &matView);
	D3DXMatrixMultiply(&matB, &((*ppEvB)->matWorld), &matView);

	if(matA._43 > matB._43)
	{
		return -1;
	} else if(matA._43 < matB._43)
	{
		return 1;
	} else {
		return 0;
	}
}

void CDrawEventStack::Sort()
{
	int size = 0;
	SDrawEvent* temp = active->next;
	// サイズを調べる
	while(temp != active)
	{
		size++;
		temp = temp->next;
	}
	if(size > 0)
	{
		SDrawEvent** a = new SDrawEvent*[size];
		temp = active->next;
		// 配列にイベントへのポインタ配列を作成
		for(int i=0; i<size; i++)
		{
			a[i] = temp;
			temp = temp->next;
		}
		// クイックソートアルゴリズム
		qsort(a, size, sizeof(SDrawEvent*), Compare);
		// ソート順に合わせてアクティブを並び替える
		active->next = a[0];
		for(int i=0; i<size-1; i++)
		{
			a[i]->next = a[i+1];
		}
		a[size-1]->next = active;
	}
}

bool CDrawEventStack::Empty()
{
	return active->next != active ? false : true;
}
