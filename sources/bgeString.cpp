#include "bgeString.h"

int GetStringSize(const char str[])
{
	int i = 0;
	while(str[i] != '\0') i++;
	return i;
}

int GetIntForStr(const char *str)
{
	int size = GetStringSize(str);
	int figure = GetStringSize(str)-1;
	int result = 0;
	int temp = 0;
	bool f = false;
	int i=0;
	if(str[0] == '-')
	{
			f = true;
			figure--;
			i++;
	}
	for(; i<size; i++)
	{
		temp = str[i] - 0x30;
		for(int j=0; j<figure; j++)
		{
			temp *= 10;
		}
		result += temp;
		figure--;
	}
	return f ? -result : result;
}

float GetFloatForStr(const char *str)
{
	int size = GetStringSize(str);
	int figure = -1;
	for(int i=0; i<size; i++)
	{
		if(str[i] == '.')
		{
			break;
		}
		figure++;
	}
	float result = 0.0f;
	float temp = 0.0f;
	bool f = false;
	int i=0;
	if(str[0] == '-')
	{
			f = true;
			figure--;
			i++;
	}
	for(; i<size; i++)
	{
		if(str[i] == 'f')
		{
			break;
		}
		if(str[i] == '.')
		{
			continue;
		}
		temp = (str[i] - 0x30) * 1.0f;
		if(figure > 0)
		{
			for(int j=0; j<figure; j++)
			{
				temp *= 10.0f;
			}
		} else {
			for(int j=figure; j<0; j++)
			{
				temp *= 0.1f;
			}
		}
		result += temp;
		figure--;
	}
	return f ? -result : result;
}