#include "BoardRepresentation.h"
#include "LegalMoveHelpers.h"
#include "LegalMoves.h"
#include "MoveExecution.h"
#include "Evaluation.h"
#include "Search.h"
#include "UCI.h"

using namespace std;

void startGame(istream& is);

int main() {

	UCICommunication();
	
	arrayToBitBoard();

	bitboardToArray();

	functionTime();

	startGame(cin);

	printBoard();

	string s = getBLegalMoves(listOfBoardParamsAndOthers, lastMove, true, true);

	cout << "BLACK: " << rawToString(s, board);

	s = getWLegalMoves(listOfBoardParamsAndOthers, lastMove, true, true);

	cout << endl << "WHITE: " << rawToString(s, board);

	cout << endl << "EVAL: " << evaluation(listOfBoardParamsAndOthers);

}

void startGame(istream& is) {

	//importFEN("3rr1k1/p4ppp/2p5/8/1p4n1/4N1P1/PP3q1P/5K2 w - - 1 28");
	
	while (true) {
		
		string s = getWLegalMoves(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle);
		
		cout << endl << "WHITE: " << rawToString(s, board) << endl;
		
		s = getBLegalMoves(listOfBoardParamsAndOthers, lastMove, blackLongCastle, blackShortCastle);
		
		cout << "BLACK: " << rawToString(s, board) << endl;
		
		//cout << endl << "EVAL: " << evaluation(listOfBoardParamsAndOthers) << endl;
		//cout << endl << "EVAL: " << minimax(listOfBoardParamsAndOthers, lastMove, whiteLongCastle,
			//whiteShortCastle, blackLongCastle, blackShortCastle, 4,4, moveNum % 2 == 0, -INFINITY, +INFINITY);
		
		if (whiteTurn) {
			string best{ getWhiteMove(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle, blackLongCastle, blackShortCastle, 5) };
			cout << endl << "BEST MOVE:" << best << " OR " << rawToString(best, board) << endl;
		}

		else {
			string best{ getBlackMove(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle, blackLongCastle, blackShortCastle, 5) };
			cout << endl << "BEST MOVE:" << best << " OR " << rawToString(best, board) << endl;
		}

		if (abs(Search::evalScore)>300) {
			int mate = abs(Search::evalScore) - 299;

			cout << "Mate in " << mate << endl;
		}
		else cout << "EVAL: " << Search::evalScore << endl;

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
		whiteTurn = !whiteTurn;
		if (numsTilDraw >= 50) break;
	}
}