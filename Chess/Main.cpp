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

	importFEN("8/pp2p3/2p1k2P/4P3/1R2R1P1/8/PPPq1r2/2KN4 w - - 3 34");
	
	while (true) {

		string s = getWLegalMoves(listOfBoardParamsAndOthers, "P6444", whiteLongCastle, whiteShortCastle);
		cout << endl << "WHITE: " << rawToString(s, board) << endl;
		s = getBLegalMoves(listOfBoardParamsAndOthers, "P6444", blackLongCastle, blackShortCastle);
		cout << "BLACK: " << rawToString(s, board) << endl;
		//cout << endl << "EVAL: " << evaluation(listOfBoardParamsAndOthers) << endl;
		//cout << endl << "EVAL: " << minimax(listOfBoardParamsAndOthers, lastMove, whiteLongCastle,
			//whiteShortCastle, blackLongCastle, blackShortCastle, 4,4, moveNum % 2 == 0, -INFINITY, +INFINITY);
		if (whiteTurn)
			cout << endl << "BEST MOVE:" << getWhiteMove(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle, blackLongCastle, blackShortCastle, 5) << endl;
		else 
			cout << endl << "BEST MOVE:" << getBlackMove(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle, blackLongCastle, blackShortCastle, 5) << endl;
		string move{};
		bitboardToArray();
		printBoardRaw();
		cout << endl;
		printBoard();
		
		if (whiteTurn) { //whites turn
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