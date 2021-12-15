#pragma once
#include <string>
#include <memory>

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
	char* ConcatenateWithDash(char* first, char* second)
	{
		char* firstBegin = &first[0];
		char* secondBegin = &second[0];

		int sizeFirst = strlen(first);
		int sizeSecond = strlen(second);

		char* firstEnd = firstBegin + sizeFirst;
		char* secondEnd = secondBegin + sizeSecond;

		char* combination = new char[sizeFirst + sizeSecond + 2];
		char* combBegin = &combination[0];
		char* combEnd = combBegin + (sizeFirst + sizeSecond + 2);
			//std::make_unique<char>(new char[sizeFirst + sizeSecond + 2]); //one for null one for dash

		char* cb = combBegin;
		for (char* b = firstBegin; b <= firstEnd; b++, cb++)
		{
			if (b == firstEnd)
			{
				*cb = '-';
				cb++;
				for (char* sb = secondBegin; cb <= combEnd; sb++, cb++)
				{
					if (cb == combEnd)
					{
						*cb = '\0';
					}
					else
					{
						*cb = *sb;
					}
				}
			}
			else
			{
				*cb = *b;
			}
		}
			return combination;
	}
};
