#include "BoardRepresentation.h"
#include "LegalMoveHelpers.h"
#include "LegalMoves.h"
#include "MoveExecution.h"
#include "Evaluation.h"

using namespace std;

void startGame(istream& is);

int main() {
	
	arrayToBitBoard();

	bitboardToArray();

	startGame(cin);

	printBoard();

	string s = getBLegalMoves(listOfBoardParamsAndOthers, "P6444", true, true);

	cout << "BLACK: " << rawToString(s, board);

	s = getWLegalMoves(listOfBoardParamsAndOthers, "P6444", true, true);

	cout << endl << "WHITE: " << rawToString(s, board);

	cout << endl << "EVAL: " << evaluation(listOfBoardParamsAndOthers);

}

void startGame(istream& is) {
	numsTilDraw = 0;
	int moveNum{0};
	string lastMove{};
	while (true) {
		string move{};
		bitboardToArray();
		printBoardRaw();
		if (moveNum % 2 == 0) { //whites turn
			moveNum++;
			while (!isLegal(listOfBoardParamsAndOthers, move, lastMove, "W", whiteShortCastle, whiteLongCastle, blackShortCastle, blackLongCastle)) {
				is >> move;
			}
			lastMove = move;
			if (executeMove(move, "W", listOfBoardParamsAndOthers, whiteLongCastle, whiteShortCastle,
				blackLongCastle, blackShortCastle)) ++numsTilDraw;
		}
		else { //blacks turn
			moveNum++;
			while (!isLegal(listOfBoardParamsAndOthers, move, lastMove, "B", whiteShortCastle, whiteLongCastle, blackShortCastle, blackLongCastle)) {
				is >> move;
			}
			lastMove = move;
			if (executeMove(move, "B", listOfBoardParamsAndOthers, whiteLongCastle, whiteShortCastle,
				blackLongCastle, blackShortCastle)) ++numsTilDraw;
		}
	}
}