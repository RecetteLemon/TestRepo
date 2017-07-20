#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <vector>
using namespace std;

class Util
{
public:
	static int ToInt(string text) { return atoi(text.c_str()); }
	static int ToInt(wstring text) { return _wtoi(text.c_str()); }
	static float ToFloat(string text) { return atof(text.c_str()); }
	static float ToFloat(wstring text) { return _wtof(text.c_str()); }

	static string ToString(int value) { stringstream ss; ss << value; return ss.str(); }
	static string ToString(float value) { stringstream ss; ss << value; return ss.str(); }
	static wstring ToWString(int value) { wstringstream ss; ss << value; return ss.str(); }
	static wstring ToWString(float value) { wstringstream ss; ss << value; return ss.str(); }

	static vector<string> Split(string text, CHAR c)
	{
		vector<string> result;
		int startIndex = 0;

		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] == c)
			{
				result.push_back(text.substr(startIndex, i - startIndex));
				startIndex = i + 1;
			}
		}
		result.push_back(text.substr(startIndex, text.length() - startIndex));
		return result;
	}

	static vector<wstring> Split(wstring text, WCHAR c)
	{
		vector<wstring> result;
		int startIndex = 0;

		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] == c)
			{
				result.push_back(text.substr(startIndex, i - startIndex));
				startIndex = i + 1;
			}
		}
		result.push_back(text.substr(startIndex, text.length() - startIndex));
		return result;
	}
};