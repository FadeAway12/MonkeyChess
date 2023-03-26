#include <iostream>
#include "BoardRepresentation.h"
#include "Evaluation.h"
#include "LegalMoveHelpers.h"
#include "LegalMoves.h"
#include "MoveExecution.h"
#include "Search.h"
#include "UCI.h"

using namespace std;

void UCICommunication() {

	while (true) {
		
		string s;
		cin >> s;

		if (s == "uci") {
			inputUCI();
		}

		else if (s.find("setoption")) {
			inputSetOption(s);
		}

		else if (s == "isready") {
			inputIsReady();
		}

		else if (s == "ucinewgame") {
			inputUCINewGame();
		}

		else if (s == "position") {
			inputPosition(s);
		}

		else if (s == "go") {

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

}

void inputPosition(string input) {

}

void inputGo() {

}

void inputPrint() {

}