#include <iostream>
#include "BoardRepresentation.h"
#include "Evaluation.h"
#include "LegalMoveHelpers.h"
#include "LegalMoves.h"
#include "MoveExecution.h"
#include "Search.h"
#include "UCI.h"
#include "OpeningBook.h"

using namespace std;

void UCICommunication() {

	while (true) {

		bitboardToArray();


		string s;
		getline(cin, s);

		if (s == "uci") {
			inputUCI();
		}

		else if (s.find("setoption") != string::npos) {
			inputSetOption(s);
		}

		else if (s == "isready") {
			inputIsReady();
		}

		else if (s == "ucinewgame") {
			inputUCINewGame();
		}

		else if (s.find("position") != string::npos) {
			inputPosition(s);
		}

		else if (s.substr(0, 2) == "go") {
			inputGo();
		}
		else if (s == "print") { //below are user implemented commands
			printBoard();
		}
		else if (s == "getMoves") {
			if (whiteTurn) cout << rawToString(getWLegalMoves(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle), board);
			else cout << rawToString(getBLegalMoves(listOfBoardParamsAndOthers, lastMove, blackLongCastle, blackShortCastle), board);
			cout << endl;
		}


	}

}

void inputUCI() {
	cout << "id name MONKEYCHESS\n";
	cout << "id author thanos\n";
	cout << "uciok\n";
}

void inputSetOption(string inputString) {

}

void inputIsReady() {
	cout << "readyok\n";
}

void inputUCINewGame() {
	
	vBlack.repetitions.clear();
	vWhite.repetitions.clear();
	numsTilDraw = 0;
	WP = 0, WN = 0, WR = 0, WQ = 0, WK = 0, WB = 0, BP = 0, BN = 0, BR = 0, BQ = 0, BK = 0, BB = 0;
	bitboardToArray();
	whiteLongCastle = true, whiteShortCastle = true, blackLongCastle = true, blackShortCastle = true;
	whiteTurn = true;
	lastMove = "";
	inOpening = true;
	moveNum = 1;
	cout << "readyok\n";

}

void inputPosition(string input) {
	input = input.substr(9);
	if (input.find("startpos") != string::npos) {

		importFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	}
	else if (input.find("fen") != string::npos) {
		importFEN(input.substr(4));
	}
	if (input.find("moves") != string::npos) {
		
		input = input.substr(input.find("moves") + 6);

		readMoveList(input);

	}
}

void readMoveList(string input) {
	istringstream ist{ input };

	string move;

	while (ist >> move) {

		if (whiteTurn) vWhite.update(getWLegalMoves(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle));
		else vBlack.update(getWLegalMoves(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle));

		move = algebraToMove(move);

		moveNum++;

		if (whiteTurn) { //white
			executeMove(move, "W", listOfBoardParamsAndOthers, whiteLongCastle, whiteShortCastle, blackLongCastle, blackShortCastle);
		}
		else {
			executeMove(move, "B", listOfBoardParamsAndOthers, whiteLongCastle, whiteShortCastle, blackLongCastle, blackShortCastle);
		}
		whiteTurn = !whiteTurn;

		lastMove = move;
	}
}

string algebraToMove(string move) {
	if (move == "O-O" || move == "O-O-O") return move;
	int fromRow = 8 - (move[1] - '0');
	int fromCol = move[0] - 'a';
	int toRow = 8 - (move[3] - '0');
	int toCol = move[2] - 'a';
	if (move.size() == 5) {
		return to_string(fromRow) + to_string(fromCol) + to_string(toRow) + to_string(toCol) + "=" + move[4];
	}
	return to_string(fromRow) + to_string(fromCol) + to_string(toRow) + to_string(toCol);
}

string moveToAlgebra(string move) {
	if (move == "O-O" || move == "O-O-O") return move;
	char fromCol = (move[1] - '0') + 'a';
	int fromRow = 8 - (move[0] - '0');
	char toCol = (move[3] - '0') + 'a';
	int toRow = 8 - (move[2] - '0');

	if (move.size() == 6) {
		return fromCol + to_string(fromRow) + toCol + to_string(toRow) + move[5];
	}
	return fromCol + to_string(fromRow) + toCol + to_string(toRow);
}

void inputGo() {

	string move;

	string op = getOpeningMove();

	string turn;
	if (whiteTurn) turn = "W";
	else turn = "B";

	if (inOpening && isLegal(listOfBoardParamsAndOthers, algebraToMove(op), lastMove, turn, whiteShortCastle,
		whiteLongCastle, blackShortCastle, blackLongCastle)) {
		cout << "bestmove " << op << endl;
		return;
	}

	if (whiteTurn) {
		move = getWhiteMove(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle, blackLongCastle, blackShortCastle, 5);
	}

	else move = getBlackMove(listOfBoardParamsAndOthers, lastMove, whiteLongCastle, whiteShortCastle, blackLongCastle, blackShortCastle, 5);

	

	cout << "bestmove " << moveToAlgebra(move) << endl;

}

void inputPrint() {

}