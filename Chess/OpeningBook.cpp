#include <iostream>
#include "BoardRepresentation.h"
#include "OpeningBook.h"
#include "UCI.h"

using namespace std;

bool inOpening{ true };

int W2, W3, W4, W5, W6, W7, W8, W9, W10; //stores the history of our moves
int B1, B2, B3, B4, B5, B6, B7, B8, B9, B10;

string getOpeningMove() {

	if (whiteTurn) {
		return getOpeningMoveWhite();
	}
	else {
		return getOpeningMoveBlack();
	}

}

string getOpeningMoveWhite() {
	switch (moveNum) {
	case 1:
		return opW1();
	case 3:
		return opW2();
	case 5:
		return opW3();
	default:
		inOpening = false;
		return "!";
	}
}

string getOpeningMoveBlack() {
	switch (moveNum) {
	case 2:
		return opB1();
	case 4:
		return opB2();
	default:
		inOpening = false;
		return "!";
	}
}

string opW1() {
	return "e2e4";
}


string opW2() {
	if (moveToAlgebra(lastMove.substr(1)) == "c7c5") { W2 = 1; return "g1f3"; }
	if (moveToAlgebra(lastMove.substr(1)) == "e7e5") { W2 = 2; return "g1f3"; }
	if (moveToAlgebra(lastMove.substr(1)) == "e7e6") { W2 = 3; return "d2d4"; }
	if (moveToAlgebra(lastMove.substr(1)) == "c7c6") { W2 = 4; return "d2d4"; }
	if (moveToAlgebra(lastMove.substr(1)) == "d7d6") { W2 = 5; return "d2d4"; }
	if (moveToAlgebra(lastMove.substr(1)) == "g7g6") { W2 = 6; return "d2d4"; }
	if (moveToAlgebra(lastMove.substr(1)) == "d7d5") { W2 = 7; return "e4d5"; }
	if (moveToAlgebra(lastMove.substr(1)) == "g8f6") { W2 = 8; return "e4e5"; }
	if (moveToAlgebra(lastMove.substr(1)) == "b8c6") { W2 = 9; return "g1f3"; }
	if (moveToAlgebra(lastMove.substr(1)) == "b7b6") { W2 = 10; return "d2d4"; }
	else inOpening = false;
	return "!";
}

string opW3() {
	
	if (W2 == 1) { //e2 e4
		if (moveToAlgebra(lastMove.substr(1)) == "d7d6") { W3 = 1; return "d2d4"; } //use
		if (moveToAlgebra(lastMove.substr(1)) == "b8c6") { W3 = 2; return "d2d4"; } //use 
		if (moveToAlgebra(lastMove.substr(1)) == "e7e6") { W3 = 3; return "d2d4"; }
		if (moveToAlgebra(lastMove.substr(1)) == "g7g6") { W3 = 4; return "d2d4"; }
	}
	if (W2 == 2) { //e2 c5
		if (moveToAlgebra(lastMove.substr(1)) == "b8c6") { W3 = 5; return "f1b5"; } //use
		if (moveToAlgebra(lastMove.substr(1)) == "g8f6") { W3 = 6; return "f2e5"; }
	}
	if (W2 == 3) {
		if (moveToAlgebra(lastMove.substr(1)) == "b8c6") { W3 = 7; return "f1b5"; } //use
		if (moveToAlgebra(lastMove.substr(1)) == "g8f6") { W3 = 8; return "f2e5"; }
	}
	if (W2 == 4) {
		if (moveToAlgebra(lastMove.substr(1)) == "d2d4") { W3 = 9; return "d7d5"; } //use
		if (moveToAlgebra(lastMove.substr(1)) == "g7g6") { W3 = 9; return "b1c3"; }
	}
	if (W2 == 5) {
		if (moveToAlgebra(lastMove.substr(1)) == "g8f6") { W3 = 9; return "b1c3"; } //use
		if (moveToAlgebra(lastMove.substr(1)) == "g7g6") { W3 = 9; return "b1c3"; }
	}

	else inOpening = false;
	return "!";
}


string opB1() {
	if (moveToAlgebra(lastMove.substr(1)) == "e2e4") { B1 = 1; return "c7c5"; }
	if (moveToAlgebra(lastMove.substr(1)) == "d2d4") { B1 = 2; return "g8f6"; }
	if (moveToAlgebra(lastMove.substr(1)) == "g1f3") { B1 = 3; return "g8f6"; }
	if (moveToAlgebra(lastMove.substr(1)) == "c2c4") { B1 = 4; return "g8f6"; }
	if (moveToAlgebra(lastMove.substr(1)) == "g2g3") { B1 = 5; return "d7d5"; }
	if (moveToAlgebra(lastMove.substr(1)) == "b2b3") { B1 = 6; return "e7e5"; }
	if (moveToAlgebra(lastMove.substr(1)) == "f2f4") { B1 = 7; return "d7d5"; }
	if (moveToAlgebra(lastMove.substr(1)) == "b1c3") { B1 = 8; return "d7d5"; }
	if (moveToAlgebra(lastMove.substr(1)) == "b2b4") { B1 = 9; return "e7e5"; }
	if (moveToAlgebra(lastMove.substr(1)) == "e2e3") { B1 = 10;return "g8f6"; }
	else inOpening = false;
	return "!"; //not in opening anymore
}


string opB2() {

	if (B1 == 1) { //sicilian
		if (moveToAlgebra(lastMove.substr(1)) == "g1f3") { B2 = 1; return "d7d6"; }
		if (moveToAlgebra(lastMove.substr(1)) == "b1c3") { B2 = 2; return "b8c6"; }
		if (moveToAlgebra(lastMove.substr(1)) == "c2c3") { B2 = 3; return "g8f6"; }
	}
	if (B1 == 2) {
		if (moveToAlgebra(lastMove.substr(1)) == "c2c4") { B2 = 4; return "e7e6"; }
		if (moveToAlgebra(lastMove.substr(1)) == "g1f3") { B2 = 5; return "d7d5"; }
		if (moveToAlgebra(lastMove.substr(1)) == "c1g5") { B2 = 6; return "f6e4"; }
	}
	if (B1 == 3) {
		if (moveToAlgebra(lastMove.substr(1)) == "d2d4") { B2 = 7; return "d7d5"; }
		if (moveToAlgebra(lastMove.substr(1)) == "c2c4") { B2 = 8; return "g7g6"; }
		if (moveToAlgebra(lastMove.substr(1)) == "g2g3") { B2 = 9; return "d7d5"; }
	}
	if (B1 == 4) {
		if (moveToAlgebra(lastMove.substr(1)) == "d2d4") { B2 = 10; return "e7e6"; }
		if (moveToAlgebra(lastMove.substr(1)) == "g1f3") { B2 = 11; return "g7g6"; }
		if (moveToAlgebra(lastMove.substr(1)) == "b1c3") { B2 = 12; return "e7e5"; }
		if (moveToAlgebra(lastMove.substr(1)) == "g2g3") { B2 = 13; return "e7e5"; }
	}
	if (B1 == 5) {
		if (moveToAlgebra(lastMove.substr(1)) == "g1f3") { B2 = 14; return "g8f6"; }
		if (moveToAlgebra(lastMove.substr(1)) == "f1g2") { B2 = 15; return "g8f6"; }
	}
	else inOpening = false;
	return "!"; //not in opening anymore
}
