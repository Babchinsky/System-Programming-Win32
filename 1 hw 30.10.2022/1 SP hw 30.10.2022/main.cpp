#include <iostream>
#include <tchar.h>

using namespace std;

#define SIZE 256

class MyString
{
private:
	_TCHAR sStr[SIZE];
public:
	MyString()
	{
		_tcscpy_s(sStr, L"Hey, man. What is your name?");
	}
	MyString(_TCHAR *t_sStr)
	{
		_tcscpy_s(sStr, t_sStr);
	}

	void Input()
	{
		wcin >> sStr;
	}
	void InputWithSpace()
	{
		wcin.getline(sStr, SIZE);
	}
	void Print()
	{
		wcout << sStr << endl;
	}
	void SpaceToTabInStr()
	{
		for (size_t i = 0; i < _tcslen(sStr); i++)
		{
			if (sStr[i] == ' ')
			{
				sStr[i] = '\t';
			}
		}
	}
	void CountLettersDigitsOthers()
	{
		unsigned int amount_letters(0), ammount_digits(0), amount_spaces(0), amount_others(0);

		for (size_t i = 0; i < _tcslen(sStr); i++)
		{
			if (iswdigit(sStr[i]))
				ammount_digits++;
			
			else if (iswalpha(sStr[i]))
				amount_letters++;

			else if (iswspace(sStr[i]))
				amount_spaces++;

			else amount_others++;
		}
		wcout << "Amount of letters: " << amount_letters << "\n";
		wcout << "Amount of digits: " << ammount_digits << "\n";
		wcout << "Amount of spaces: " << amount_spaces << "\n";
		wcout << "Amount of others: " << amount_others << "\n";
	}
	void CountWords()
	{
		unsigned int amount_words = 0;

		for (size_t i = 0; i < _tcslen(sStr) - 2; i++)
		{
			if (iswalpha(sStr[i]) && iswalpha(sStr[i + 1]))
				if (iswspace(sStr[i + 2])) amount_words++;
				else if (
							sStr[i + 2] == '.' || sStr[i + 2] == L'.' ||
							sStr[i + 2] == ',' || sStr[i + 2] == L',' ||
							sStr[i + 2] == '-' || sStr[i + 2] == L'-' ||
							sStr[i + 2] == '(' || sStr[i + 2] == L'(' ||
							sStr[i + 2] == ')' || sStr[i + 2] == L')' ||
							sStr[i + 2] == '[' || sStr[i + 2] == L'[' ||
							sStr[i + 2] == ']' || sStr[i + 2] == L']' ||
							sStr[i + 2] == '{' || sStr[i + 2] == L'{' ||
							sStr[i + 2] == '}' || sStr[i + 2] == L'}' ||
							sStr[i + 2] == '?' || sStr[i + 2] == L'?' ||
							sStr[i + 2] == '/' || sStr[i + 2] == L'/'
						)
				{
					amount_words++;
				}
				
			
		}
		wcout << amount_words << endl;
	}
	void CountCyrillicVowels()
	{
		unsigned int vowels = 0;

		for (size_t i = 0; i < _tcslen(sStr); i++)
		{
			//à, ÿ, ó, þ, î, å, ¸, ý, è, û
			if (
				sStr[i] == 'à' || sStr[i] == L'à' ||
				sStr[i] == 'ÿ' || sStr[i] == L'ÿ' ||
				sStr[i] == 'ó' || sStr[i] == L'ó' ||
				sStr[i] == 'þ' || sStr[i] == L'þ' ||
				sStr[i] == 'î' || sStr[i] == L'î' ||
				sStr[i] == 'å' || sStr[i] == L'å' ||
				sStr[i] == '¸' || sStr[i] == L'¸' ||
				sStr[i] == 'ý' || sStr[i] == L'ý' ||
				sStr[i] == 'è' || sStr[i] == L'è' ||
				sStr[i] == 'û' || sStr[i] == L'û'
				)
				vowels++;
		}
		wcout << "Amount of vowels: " << vowels << endl;
	}
	void IsPallindrome()
	{
		bool flag = 0;
		size_t length = _tcslen(sStr);
		
		for (size_t i = 0; i < length; i++) 
		{
			if (sStr[i] != sStr[length - i - 1]) 
			{
				flag = 1;
				break;
			}
		}

		if (flag)	wcout << sStr << " is not a palindrome" << endl;
		else		wcout << sStr << " is a palindrome" << endl;
	}
	void RemovePos(unsigned int pos)
	{
		size_t length = _tcsclen(sStr);

		for (int i = pos; i < length - 1; i++)
			sStr[i] = sStr[i + 1];

		sStr[length - 1] = '\0';
	}
	void RemoveChar(_TCHAR ch)
	{
		int j;
		size_t length = _tcsclen(sStr);

		for (int i = j = 0; i < length; i++)
			if (sStr[i] != ch)
				sStr[j++] = sStr[i];

		sStr[j] = '\0';
	}
	void InsertCharInPos(_TCHAR ch, unsigned int pos)
	{
		sStr[pos] = ch;
	}
};



int main()
{
	// turn on cyrillic symbols
	wcout.imbue(locale("rus_rus.866"));
	wcin.imbue(locale("rus_rus.866"));

	_TCHAR str[] = _TEXT("Hey, men., What are your names?");
	MyString obj(str);
	obj.Print();

	//obj.RemoveChar('e');
	//obj.Print();

	obj.RemovePos(3);
	obj.Print();

	//obj.CountLettersDigitsOthers();
	//obj.CountWords();
	//obj.CountCyrillicVowels();
	//obj.IsPallindrome();

	//obj.SpaceToTabInStr();
	//obj.Print();

	//obj.InputWithSpace();
	//obj.Print();

	return 0;
}
