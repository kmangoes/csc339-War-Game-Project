/*
  File: main.cpp
  Description: Driver code for the War card game
*/

#include "War.h"
#include <iostream>
#include <random>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    // Enable UTF-8 output on Windows
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto gen = std::default_random_engine{seed};

    auto war = War{gen};

    auto ws = WinState::ongoing;
    int countRounds = 0;
    while (ws == WinState::ongoing) {
        ws = war.playRound();
        ++countRounds;
    }
    std::cout << countRounds << " rounds total." << std::endl;

    return 0;
}