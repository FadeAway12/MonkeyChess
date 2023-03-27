#include "BoardRepresentation.h"
#include "LegalMoves.h"

#include <iostream>

using namespace std;

constexpr bb shortRookW(9.22337204E18);

constexpr bb longRookW(0b0000000100000000000000000000000000000000000000000000000000000000);

constexpr bb shortRookB(128);

constexpr bb longRookB(1);

//turn is whether white or black is executing the move
bool executeMove(const string& move, const string& turn, moveParams, bool& WLC,
	bool& WSC, bool& BLC, bool& BSC) { //returns true if capture or pawn move
	
	bool cap{ false };

	if (turn == "W" && move == "O-O") {
		WR = (WR & ~shortRookW) | WK << 1;
		WK = WK << 2;
	}

	if (turn == "W" && move == "O-O-O") {
		WR = (WR & ~longRookW) | WK >> 1;
		WK = WK >> 2;
	}

	if (turn == "B" && move == "O-O") {
		BR = (BR & ~shortRookB) | BK << 1;
		BK = BK << 2;
	}

	if (turn == "B" && move == "O-O-O") {
		BR = (BR & ~longRookB) | BK >> 1;
		BK = BK >> 2;
	}

	if (move.size() == 5) { //its a promotion
		
		cap = true;

		char piece = move[4];
		int rowF = move[0] - '0';
		int colF = move[1] - '0';
		int rowT = move[2] - '0';
		int colT = move[3] - '0';

		bb from = pow(2, rowF * 8 + colF);
		bb to = pow(2, rowT * 8 + colT);

		if (turn == "W") {

			WP &= ~from;
			switch (piece) {
			case 'Q': WQ |= to; break;
			case 'B': WB |= to; break;
			case 'R': WR |= to; break;
			case 'N': WN |= to; break;
			}
			//if ((black & ~to) != black) cap = true;
			BP &= ~to, BN &= ~to, BB &= ~to, BR &= ~to, BK &= ~to, BQ &= ~to;
			return cap;

		}

		if (turn == "B") {

			BP &= ~from;

			switch (piece) {
			case 'Q': BQ |= to; break;
			case 'B': BB |= to; break;
			case 'R': BR |= to; break;
			case 'N': BN |= to; break;
			}
			//if ((white & ~to) != white) cap = true;
			WP &= ~to, WN &= ~to, WB &= ~to, WR &= ~to, WK &= ~to, WQ &= ~to;
			return cap;
		}
		//throw error here
	}
	
	int rowF = move[0] - '0';
	int colF = move[1] - '0';
	int rowT = move[2] - '0';
	int colT = move[3] - '0';
	
	bb from = pow(2, rowF * 8 + colF);
	bb to = pow(2, rowT * 8 + colT);

	if (turn == "W") {
		if (from & WP) {
			cap = true; 
			//en passant
			if (colF != colT) {
				BP = BP & ~(to << 8);
			}
			WP = (WP | to) & ~from;
		}
		else if (from & WN) {
			WN = (WN | to) & ~from;
		}
		else if (from & WQ) {
			WQ = (WQ | to) & ~from;
		}
		else if (from & WB) {
			WB = (WB | to) & ~from;
		}
		else if (from & WR) {
			WR = (WR | to) & ~from;
			if (!WSC & from & shortRookW) WSC = false;
			if (!WLC & from & longRookW) WLC = false;
		}
		else if (from & WK) {
			WK = (WK | to) & ~from;
			WSC = false;
			WLC = false;
		}
		else {
			//error
		}
		if ((black & ~to) != black) cap = true;
		BP &= ~to, BN &= ~to, BB &= ~to, BR &= ~to, BK &= ~to, BQ &= ~to;
		return cap;
	}
	if (turn == "B") {
		if (from & BP) {
			cap = true;
			if (colF != colT) {
				WP = WP & ~(to >> 8);
			}
			BP = (BP | to) & ~from;
		}
		else if (from & BN) {
			BN = (BN | to) & ~from;
		}
		else if (from & BQ) {
			BQ = (BQ | to) & ~from;
		}
		else if (from & BB) {
			BB = (BB | to) & ~from;
		}
		else if (from & BR) {
			BR = (BR | to) & ~from;
			if (!BSC & from & shortRookB) BSC = false;
			if (!BLC & from & longRookB) BLC = false;
		}
		else if (from & BK) {
			BK = (BK | to) & ~from;
		}
		else {
			//error
		}
		if ((white & ~to) != white) cap = true;
		WP &= ~to, WN &= ~to, WB &= ~to, WR &= ~to, WK &= ~to, WQ &= ~to;
		return cap;
	}
	return cap; //error
}

bool isLegal(moveParams, const string& move, string& lastMove, const string& turn, bool SCW, bool LCW, bool SCB, bool LCB) {
	if (move.size() == 0) return false;
	if (turn == "W") {
		string s = getWLegalMoves(listOfBoardParamsAndOthers, lastMove, LCW, SCW);
		istringstream is{ s };
		while (is) {
			string m;
			is >> m;
			if (move == m) return true;
		}
		return false;
	}
	if (turn == "B") {
		string s = getBLegalMoves(listOfBoardParamsAndOthers, lastMove, LCB, SCB);
		istringstream is{ s };
		while (is) {
			string m;
			is >> m;
			if (move == m) return true;
		}
		return false;
	}
	return false;
}