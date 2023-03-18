#include "BoardRepresentation.h"
#include "LegalMoveHelpers.h"
#include "LegalMoves.h"
#include "MoveExecution.h"
#include "Evaluation.h"
#include "Search.h"

using namespace std;

void startGame(istream& is);

int main() {
	
	arrayToBitBoard();

	bitboardToArray();

	functionTime();

	startGame(cin);

	printBoard();

	string s = getBLegalMoves(listOfBoardParamsAndOthers, "P6444", true, true);

	cout << "BLACK: " << rawToString(s, board);

	s = getWLegalMoves(listOfBoardParamsAndOthers, "P6444", true, true);

	cout << endl << "WHITE: " << rawToString(s, board);

	cout << endl << "EVAL: " << evaluation(listOfBoardParamsAndOthers);

}

void startGame(istream& is) {

	RepetitionVector vWhite;
	RepetitionVector vBlack;
	
	numsTilDraw = 0;
	int moveNum{};
	string lastMove{};
	
	while (true) {

		string s = getWLegalMoves(listOfBoardParamsAndOthers, "P6444", true, true);
		cout << endl << "WHITE: " << rawToString(s, board) << endl;
		s = getBLegalMoves(listOfBoardParamsAndOthers, "P6444", true, true);
		cout << "BLACK: " << rawToString(s, board) << endl;
		//cout << endl << "EVAL: " << evaluation(listOfBoardParamsAndOthers) << endl;
		cout << endl << "EVAL: " << minimax(listOfBoardParamsAndOthers, lastMove, whiteLongCastle,
			whiteShortCastle, blackLongCastle, blackShortCastle, 6, moveNum % 2 == 0, -INFINITY, +INFINITY);
		cout << endl;

		string move{};
		bitboardToArray();
		printBoardRaw();
		cout << endl;
		printBoard();
		
		if (moveNum % 2 == 0) { //whites turn
			moveNum++;
			while (!isLegal(listOfBoardParamsAndOthers, move, lastMove, "W", whiteShortCastle, whiteLongCastle, blackShortCastle, blackLongCastle)) {
				is >> move;
			}
			lastMove = move;
			if (executeMove(move, "W", listOfBoardParamsAndOthers, whiteLongCastle, whiteShortCastle,
				blackLongCastle, blackShortCastle)) ++numsTilDraw;
			else numsTilDraw = 0;
			if (vWhite.update(getBLegalMoves(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle))) {
				break;
			}
		}
		
		else { //blacks turn
			moveNum++;
			while (!isLegal(listOfBoardParamsAndOthers, move, lastMove, "B", whiteShortCastle, whiteLongCastle, blackShortCastle, blackLongCastle)) {
				is >> move;
			}
			lastMove = move;
			if (executeMove(move, "B", listOfBoardParamsAndOthers, whiteLongCastle, whiteShortCastle,
				blackLongCastle, blackShortCastle)) ++numsTilDraw;
			else numsTilDraw = 0;
			if (vBlack.update(getBLegalMoves(listOfBoardParamsAndOthers, lastMove, blackLongCastle, blackShortCastle))) {
				break;
			}
			
		}
	
		if (numsTilDraw >= 50) break;
	
	}
}