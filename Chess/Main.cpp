#include <chrono>
#include <iostream>

using namespace std::chrono;

#include "BoardRepresentation.h"
#include "LegalMoveHelpers.h"
#include "LegalMoves.h"
#include "MoveExecution.h"
#include "Evaluation.h"
#include "Search.h"
#include "UCI.h"
#include "TranspositionTables.h";

int main() {

	initialize();

	UCICommunication();

}

void functionTime() {

	auto start = high_resolution_clock::now();

	std::cout << positionValue(WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK, lastMove, whiteTurn, whiteShortCastle, whiteLongCastle, blackShortCastle, blackLongCastle) << std::endl;

	auto end = high_resolution_clock::now();

	auto duration = duration_cast<nanoseconds>(end - start);

	std::cout << duration.count() << std::endl;

}