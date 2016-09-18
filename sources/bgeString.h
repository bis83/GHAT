#ifndef BGESTRING_H
#define BGESTRING_H

#include <string>
using namespace std;

// 文字列の長さを取得する
int GetStringSize(const char* str);

// 数字だけの文字列から整数値を取得する
int GetIntForStr(const char* str);

// 数字だけの文字列から浮動小数点値を取得する
float GetFloatForStr(const char *str);

#endif
