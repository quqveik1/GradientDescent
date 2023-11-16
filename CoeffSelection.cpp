// CoeffSelection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include "CoorEngine.cpp"
#include <iostream>

// sin(5x + 7)
int main()
{
    Vector screenSize = { 1000, 800 };

    CoorEngine* coorEngine = new CoorEngine();
    coorEngine->startApp();

    delete coorEngine;
}
