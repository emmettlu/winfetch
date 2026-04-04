#include <iostream>
#include <windows.h>

#include <display.h>
#include <colors.h>

void drawbar(double input)
{
	std::cout << "-=[ ";

	int input1 = input / 5;

	setbarc;

	int i = 0;

	while (i < input1)
	{
		std::cout << "/";
		i++;
	}

	setdflt;

	while (i < 20)
	{
		std::cout << "/";
		i++;
	}

	std::cout << " ]=-";
}

// 优化版本：使用缓存的硬件信息，避免重复查询
void membar(const HardwareInfo& hw_info)
{
	drawbar(static_cast<double>(hw_info.mem_percent));
}

// 优化版本：使用缓存的硬件信息，避免重复查询
void diskbar(const HardwareInfo& hw_info)
{
	if (hw_info.disk_total_gb > 0.0) {
		double used_gb = hw_info.disk_total_gb - hw_info.disk_free_gb;
		double percent = (used_gb / hw_info.disk_total_gb) * 100.0;
		drawbar(percent);
	} else {
		std::wcout << L"Unable to draw disk bar";
	}
}

// 原始版本：保持向后兼容，但会产生额外的系统调用
void membar()
{
	MEMORYSTATUSEX mem{};
	mem.dwLength = sizeof(mem);
	GlobalMemoryStatusEx(&mem);

	double percent = mem.dwMemoryLoad;
	drawbar(percent);
}

// 原始版本：保持向后兼容，但会产生额外的系统调用
void diskbar()
{
	ULARGE_INTEGER FreeBytesAvailableToCaller;
	ULARGE_INTEGER TotalNumberOfBytes;
	ULARGE_INTEGER TotalNumberOfFreeBytes;

	double total{};
	double free{};

	BOOL check = GetDiskFreeSpaceExA("C:\\", &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);

	if (check)
	{
		ULONGLONG totalspace = TotalNumberOfBytes.QuadPart / 1024 / 1024;
		if (totalspace <= INT_MAX) total = static_cast<double>(totalspace);

		ULONGLONG freespace = TotalNumberOfFreeBytes.QuadPart / 1024 / 1024;
		if (freespace <= INT_MAX) free = static_cast<double>(freespace);

		double percent = free / total;
		percent = 1.0 - percent;
		percent = percent * 100;

		drawbar(percent);
	}
	else
	{
		std::wcout << L"Unable to draw disk bar";
	}
}

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