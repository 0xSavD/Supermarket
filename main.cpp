/**
 * @file main.cpp
 * @author Dan 0xSavD
 * @brief Main program for the super market pos system.
 * @version 1.0
 * @date 2024-09-13
 */

#include "inc/pos.h"
#include <cassert>

 int main() {
    Pos newSystem = Pos(1);
    newSystem.scanItem("1983");
    newSystem.scanItem("4900");
    newSystem.scanItem("8873");
    newSystem.scanItem("6732");
    newSystem.scanItem("0923");
    newSystem.scanItem("1983");
    newSystem.scanItem("1983");
    newSystem.scanItem("1983");
    int total = newSystem.getTodaysTotal();
    assert(3037 == total);
 }