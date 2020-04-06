#define _CRT_SECURE_NO_WARNINGS

#define PROGRAM_VERSION "1.0"
#define ENGLISH_ALPHABET_SIZE 26
#define CASE_DROP_RATE 10

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

struct CPuzzle
{
	CPuzzle(char cLetter, int iRepeat)
	{
		this->cLetter = cLetter;
		this->iRepeat = iRepeat;
	}

	char cLetter;
	int iRepeat, iCurRepeat;
};

std::vector<CPuzzle> g_vPuzzles;

bool AddNewPuzzle(std::string sInput)
{
	if (sInput.find(':') == std::string::npos)
		return false;

	int iRepeat = std::atoi(sInput.substr(sInput.find(':') + 1, sInput.size()).c_str());
	if (iRepeat <= 0)
		return false;

	std::string sWord = sInput.substr(0, sInput.find(':'));

	for (size_t i = 0; i < sWord.size(); i++)
	{
		bool bLetterExists = false;
		for (size_t j = 0; j < g_vPuzzles.size() && !bLetterExists; j++)
			if (sWord.at(i) == g_vPuzzles.at(j).cLetter)
			{
				bLetterExists = true;
				g_vPuzzles.at(j).iRepeat += iRepeat;
			}

		if (!bLetterExists)
			g_vPuzzles.push_back(CPuzzle(sWord.at(i), iRepeat));
	}

	return true;
}

void SetupCurrentRepeat()
{
	for (size_t i = 0; i < g_vPuzzles.size(); i++)
	{
		printf("%c = ", g_vPuzzles.at(i).cLetter);
		do
		{
			scanf("%i", &g_vPuzzles.at(i).iCurRepeat);
			if (g_vPuzzles.at(i).iCurRepeat <= 0)
				printf("[-] Wrong number. Please write the right one.\n");
		} while (g_vPuzzles.at(i).iCurRepeat <= 0);
	}
}

void PrintPuzzleMap()
{
	for (CPuzzle Puzzle : g_vPuzzles)
		printf("Letter %c has %i repeats. Need %i repeats.\n", Puzzle.cLetter, Puzzle.iCurRepeat, Puzzle.iRepeat);
}

void PrintNecessaryLetters()
{
	for (CPuzzle Puzzle : g_vPuzzles)
	{
		printf("%c = ", Puzzle.cLetter);
		int iDelta = Puzzle.iRepeat - Puzzle.iCurRepeat;

		printf("%s\n", iDelta <= 0 ? "full" : std::to_string(iDelta).c_str());
	}
}

void CalculateCasesNum()
{
	int iSumLetters(0);
	for (CPuzzle Puzzle : g_vPuzzles)
	{
		int iDelta = Puzzle.iRepeat - Puzzle.iCurRepeat;
		if (iDelta > 0)
			iSumLetters += iDelta;
	}

	printf("[+] At least %i case(s)\n", iSumLetters);
	printf("[+] Optionaly %i case(s)\n", iSumLetters * ENGLISH_ALPHABET_SIZE);

	int iMinutes = iSumLetters * CASE_DROP_RATE;
	printf("\n[+] Which will take:\n");
	printf("[+] At least %i day(s), %i hour(s) and %i minute(s)\n", iMinutes / 60 / 24, iMinutes / 60 % 24, iMinutes % 60);

	iMinutes *= ENGLISH_ALPHABET_SIZE;
	printf("[+] Optionaly %i day(s), %i hour(s) and %i minute(s)\n", iMinutes / 60 / 24, iMinutes / 60 % 24, iMinutes % 60);
}

int main()
{
	char szBuffer[1024];
	sprintf(szBuffer, "Puzzle calculator v%s", PROGRAM_VERSION);
	SetConsoleTitle(szBuffer);

	printf("[+] Welcome to puzzle calculator v%s!\n", PROGRAM_VERSION);
	printf("[+] Enter new puzzle (wrong syntax or not positive num to exit). Syntax: word:repeat\n");
	do
	{
		printf("> ");
		scanf("%s1024", &szBuffer);
	} while (AddNewPuzzle(szBuffer));

	printf("\n[+] Enter current repeat for each letter:\n");
	SetupCurrentRepeat();

	printf("\n[+] Current puzzle map:\n");
	PrintPuzzleMap();

	printf("\n[+] List of necessary letters for puzzle:\n");
	PrintNecessaryLetters();

	printf("\n[+] You will need:\n");
	CalculateCasesNum();

	system("pause");
	return TRUE;
}