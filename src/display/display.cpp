#include <iostream>
#include <windows.h>

#include <display.h>
#include <colors.h>

void color1() {
	int i = 0;

	while (i < 127)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
		std::wcout << " ";
		i = i + 4;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

void color2() {
	int i = 128;
	int n = 0;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);

	while (n < 4)
	{
		std::wcout << " ";
		n++;
	}

	while (i < 254)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
		std::wcout << " ";
		i = i + 4;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}