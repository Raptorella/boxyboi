#pragma once
#include <string>

namespace Helper
{
	char* GetPureColorName(std::string& typeIdColorName)
	{
		char* beginPtr = &typeIdColorName[0];
		char* endPtr = beginPtr + typeIdColorName.length() ;
		std::string word;

		for (char* b = beginPtr + 6; b < endPtr - 4; b++)
		{
			if (b == endPtr - 5)
			{
				word += '\0';
			}
			else
			{
				word += *b;
			}
		}
		
		int size = word.length();
		char* dontGo = new char[size];
		strcpy_s(dontGo, size, word.data());
		return dontGo;
	}
};
