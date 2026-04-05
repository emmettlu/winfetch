#include <debug.h>
#include <iostream>
#include <locale>
#include <windows.h>

void neofetch();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_ALL, "en_US.UTF-8");

    neofetch();

    return 0;
}
