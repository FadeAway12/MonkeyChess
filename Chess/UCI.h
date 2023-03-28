#pragma once

#include <iostream>

extern std::string algebraToMove(std::string move);

extern std::string moveToAlgebra(std::string move);

extern void UCICommunication();

extern void inputUCI();

extern void inputSetOption(std::string inputString);

extern void inputIsReady();

extern void inputUCINewGame();

extern void inputPosition(std::string input);

extern void inputGo();

extern void inputPrint();

extern void readMoveList(std::string input);