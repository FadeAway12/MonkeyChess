#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <chrono>

#include "BoardRepresentation.h"
#include "LegalMoveHelpers.h"
#include "LegalMoves.h"

using namespace std;
using namespace chrono;

bb attackedByWhite(moveParams) {

	//attacked by pawn
	bb attacked = WP >> 7 & ~fileA;
	attacked |= WP >> 9 & ~fileH;
	//attacked by knight
	attacked |= WN >> 6 & ~fileA & ~fileB & ~white;
	attacked |= WN >> 10 & ~fileG & ~fileH & ~white;
	attacked |= WN >> 15 & ~fileA & ~white;
	attacked |= WN >> 17 & ~fileH & ~white;
	attacked |= WN << 6 & ~fileH & ~fileG & ~white;
	attacked |= WN << 10 & ~fileA & ~fileB & ~white;
	attacked |= WN << 15 & ~fileH & ~white;
	attacked |= WN << 17 & ~fileA & ~white;
	//attacked by king
	attacked |= WK >> 7 & ~white & ~fileA;
	attacked |= WK >> 8 & ~white;
	attacked |= WK >> 9 & ~white & ~fileH;
	attacked |= WK >> 1 & ~white & ~fileH;
	attacked |= WK << 1 & ~white & ~fileA;
	attacked |= WK << 7 & ~white & ~fileH;
	attacked |= WK << 8 & ~white;
	attacked |= WK << 9 & ~white & ~fileA;
	//attacked by rook/bishop/queen

	for (int i = 0; i < 64; i++) {
		if (((WR >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb WRU = pos >> 8 & ~white & ~((pos & black) >> 8);

			while (WRU) {

				attacked |= WRU;

				WRU = WRU >> 8 & ~white & ~((WRU & black) >> 8);
			}

			bb WRL = pos >> 1 & ~white & ~fileH & ~((pos & black) >> 1);

			while (WRL) {

				attacked |= WRL;

				WRL = WRL >> 1 & ~white & ~fileH & ~((WRL & black) >> 1);
			}

			bb WRR = pos << 1 & ~white & ~fileA & ~((pos & black) << 1);

			while (WRR) {

				attacked |= WRR;

				WRR = WRR << 1 & ~white & ~fileA & ~((WRR & black) << 1);
			}

			bb WRD = pos << 8 & ~white & ~((pos & black) << 8);

			while (WRD) {

				attacked |= WRD;

				WRD = WRD << 8 & ~white & ~((WRD & black) << 8);
			}

		}
		else if (((WB >> i) & 1) == 1) {
			bb pos = pow(2, i);

			bb WBUR = pos >> 7 & ~fileA & ~white & ~((pos & black) >> 7);

			while (WBUR) {

				attacked |= WBUR;

				WBUR = WBUR >> 7 & ~fileA & ~white & ~((WBUR & black) >> 7);

			}

			bb WBUL = pos >> 9 & ~fileH & ~white & ~((pos & black) >> 9);

			while (WBUL) {

				attacked |= WBUL;

				WBUL = WBUL >> 9 & ~fileH & ~white & ~((WBUL & black) >> 9);

			}

			bb WBDL = pos << 7 & ~fileH & ~white & ~((pos & black) << 7);

			while (WBDL) {


				attacked |= WBDL;

				WBDL = WBDL << 7 & ~fileH & ~white & ~((WBDL & black) << 7);

			}

			bb WBDR = pos << 9 & ~fileA & ~white & ~((pos & black) << 9);

			while (WBDR) {


				attacked |= WBDR;

				WBDR = WBDR << 9 & ~fileA & ~white & ~((WBDR & black) << 9);

			}
		}
		else if (((WQ >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb QU = pos >> 8 & ~white & ~((pos & black) >> 8);

			while (QU) {

				attacked |= QU;

				QU = QU >> 8 & ~white & ~((QU & black) >> 8);
			}



			bb QL = pos >> 1 & ~white & ~fileH & ~((pos & black) >> 1);

			while (QL) {

				attacked |= QL;

				QL = QL >> 1 & ~white & ~fileH & ~((QL & black) >> 1);
			}



			bb QR = pos << 1 & ~white & ~fileA & ~((pos & black) << 1);

			while (QR) {

				attacked |= QR;

				QR = QR << 1 & ~white & ~fileA & ~((QR & black) << 1);
			}

			bb QD = pos << 8 & ~white & ~((pos & black) << 8);



			while (QD) {

				attacked |= QD;

				QD = QD << 8 & ~white & ~((QD & black) << 8);
			}

			bb QUR = pos >> 7 & ~fileA & ~white & ~((pos & black) >> 7);



			while (QUR) {

				attacked |= QUR;

				QUR = QUR >> 7 & ~fileA & ~white & ~((QUR & black) >> 7);

			}



			bb QUL = pos >> 9 & ~fileH & ~white & ~((pos & black) >> 9);

			while (QUL) {

				attacked |= QUL;

				QUL = QUL >> 9 & ~fileH & ~white & ~((QUL & black) >> 9);

			}



			bb QDL = pos << 7 & ~fileH & ~white & ~((pos & black) << 7);

			while (QDL) {

				attacked |= QDL;

				QDL = QDL << 7 & ~fileH & ~white & ~((QDL & black) << 7);

			}



			bb QDR = pos << 9 & ~fileA & ~white & ~((pos & black) << 9);

			while (QDR) {


				attacked |= QDR;

				QDR = QDR << 9 & ~fileA & ~white & ~((QDR & black) << 9);
			}
		}
	}
	return attacked;
}

bb attackedByBlack(moveParams) {

	//attacked by pawn
	bb attacked = BP << 7 & ~fileH;
	attacked |= BP << 9 & ~fileA;
	//attacked by knight
	attacked |= BN >> 6 & ~fileA & ~fileB & ~black;
	attacked |= BN >> 10 & ~fileG & ~fileH & ~black;
	attacked |= BN >> 15 & ~fileA & ~black;
	attacked |= BN >> 17 & ~fileH & ~black;
	attacked |= BN << 6 & ~fileH & ~fileG & ~black;
	attacked |= BN << 10 & ~fileA & ~fileB & ~black;
	attacked |= BN << 15 & ~fileH & ~black;
	attacked |= BN << 17 & ~fileA & ~black;
	//attacked by king
	attacked |= BK >> 7 & ~black & ~fileA;
	attacked |= BK >> 8 & ~black;
	attacked |= BK >> 9 & ~black & ~fileH;
	attacked |= BK >> 1 & ~black & ~fileH;
	attacked |= BK << 1 & ~black & ~fileA;
	attacked |= BK << 7 & ~black & ~fileH;
	attacked |= BK << 8 & ~black;
	attacked |= BK << 9 & ~black & ~fileA;
	//attacked by rook/bishop/queen

	for (int i = 0; i < 64; i++) {
		if (((BR >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb BRU = pos >> 8 & ~black & ~((pos & white) >> 8);

			while (BRU) {

				attacked |= BRU;

				BRU = BRU >> 8 & ~black & ~((BRU & white) >> 8);
			}

			bb BRL = pos >> 1 & ~black & ~fileH & ~((pos & white) >> 1);

			while (BRL) {

				attacked |= BRL;

				BRL = BRL >> 1 & ~black & ~fileH & ~((BRL & white) >> 1);
			}

			bb BRR = pos << 1 & ~black & ~fileA & ~((pos & white) << 1);

			while (BRR) {

				attacked |= BRR;

				BRR = BRR << 1 & ~black & ~fileA & ~((BRR & white) << 1);
			}

			bb BRD = pos << 8 & ~black & ~((pos & white) << 8);

			while (BRD) {

				attacked |= BRD;

				BRD = BRD << 8 & ~black & ~((BRD & white) << 8);
			}

		}
		else if (((BB >> i) & 1) == 1) {
			bb pos = pow(2, i);

			bb BBUR = pos >> 7 & ~fileA & ~black & ~((pos & white) >> 7);

			while (BBUR) {

				attacked |= BBUR;

				BBUR = BBUR >> 7 & ~fileA & ~black & ~((BBUR & white) >> 7);

			}

			bb BBUL = pos >> 9 & ~fileH & ~black & ~((pos & white) >> 9);

			while (BBUL) {

				attacked |= BBUL;

				BBUL = BBUL >> 9 & ~fileH & ~black & ~((BBUL & white) >> 9);

			}

			bb BBDL = pos << 7 & ~fileH & ~black & ~((pos & white) << 7);

			while (BBDL) {


				attacked |= BBDL;

				BBDL = BBDL << 7 & ~fileH & ~black & ~((BBDL & white) << 7);

			}

			bb BBDR = pos << 9 & ~fileA & ~black & ~((pos & white) << 9);

			while (BBDR) {


				attacked |= BBDR;

				BBDR = BBDR << 9 & ~fileA & ~black & ~((BBDR & white) << 9);

			}
		}
		else if (((BQ >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb QU = pos >> 8 & ~black & ~((pos & white) >> 8);

			while (QU) {

				attacked |= QU;

				QU = QU >> 8 & ~black & ~((QU & white) >> 8);
			}



			bb QL = pos >> 1 & ~black & ~fileH & ~((pos & white) >> 1);

			while (QL) {

				attacked |= QL;

				QL = QL >> 1 & ~black & ~fileH & ~((QL & white) >> 1);
			}



			bb QR = pos << 1 & ~black & ~fileA & ~((pos & white) << 1);

			while (QR) {

				attacked |= QR;

				QR = QR << 1 & ~black & ~fileA & ~((QR & white) << 1);
			}

			bb QD = pos << 8 & ~black & ~((pos & white) << 8);



			while (QD) {

				attacked |= QD;

				QD = QD << 8 & ~black & ~((QD & white) << 8);
			}

			bb QUR = pos >> 7 & ~fileA & ~black & ~((pos & white) >> 7);



			while (QUR) {

				attacked |= QUR;

				QUR = QUR >> 7 & ~fileA & ~black & ~((QUR & white) >> 7);

			}



			bb QUL = pos >> 9 & ~fileH & ~black & ~((pos & white) >> 9);

			while (QUL) {

				attacked |= QUL;

				QUL = QUL >> 9 & ~fileH & ~black & ~((QUL & white) >> 9);

			}



			bb QDL = pos << 7 & ~fileH & ~black & ~((pos & white) << 7);

			while (QDL) {

				attacked |= QDL;

				QDL = QDL << 7 & ~fileH & ~black & ~((QDL & white) << 7);

			}



			bb QDR = pos << 9 & ~fileA & ~black & ~((pos & white) << 9);

			while (QDR) {


				attacked |= QDR;

				QDR = QDR << 9 & ~fileA & ~black & ~((QDR & white) << 9);
			}
		}
	}
	return attacked;
}


bb* findCheckerWhite(moveParams) { //finds black piece(s) checking white king
	bb* checkers = new bb[2];
	
	return checkers;
}

void addCastlingMovesWhite(moveParams, bb* attackedB, string& moves, bool SC, bool LC, bool inCheck) {

	constexpr bb kingPos(0b0001000000000000000000000000000000000000000000000000000000000000); //2^60. pow isnt constexpr so cant use
	constexpr bb kingBis(0b0010000000000000000000000000000000000000000000000000000000000000); //2^61
	constexpr bb kingKni(0b0100000000000000000000000000000000000000000000000000000000000000);
	constexpr bb kingRook(0b1000000000000000000000000000000000000000000000000000000000000000);

	constexpr bb queenPos(0b0000100000000000000000000000000000000000000000000000000000000000);
	constexpr bb queenBis(0b0000010000000000000000000000000000000000000000000000000000000000);
	constexpr bb queenKni(0b0000001000000000000000000000000000000000000000000000000000000000);
	constexpr bb queenRook(0b0000000100000000000000000000000000000000000000000000000000000000);

	

	if (inCheck) return;

	if (SC && WK & kingPos && emptySquare & kingBis && emptySquare & kingKni && WR & kingRook) {
		if (!(*attackedB & kingBis || *attackedB & kingKni)) {
			moves += " O-O ";
		}
	}
	if (LC && WK & kingPos && emptySquare & queenPos && emptySquare & queenBis 
		&& emptySquare & queenKni && WR & queenRook) {
		if (!(*attackedB & queenPos || *attackedB & queenBis || *attackedB & queenKni)) {
			moves += " O-O-O ";
		}
	}

}

void addCastlingMovesBlack(moveParams, bb* attackedW, string& moves, bool SC, bool LC, bool inCheck) {

	constexpr bb kingPos{ (int)16 }; //2^59. pow isnt constexpr so cant use
	constexpr bb kingBis{ (int)32}; //2^58
	constexpr bb kingKni{ (int)64};
	constexpr bb kingRook{ (int)128};

	constexpr bb queenPos{ (int)4 };
	constexpr bb queenBis{ (int)2};
	constexpr bb queenKni{ (int)1};
	constexpr bb queenRook(0);

	//50 is natural king position at start of game

	if (inCheck) return;

	if (SC && (BK & kingPos && emptySquare & kingBis && emptySquare & kingKni && BR & kingRook)) {
		if (*attackedW & kingBis || *attackedW & kingKni) {
			moves += " O-O ";
		}
	}
	if (LC && BK & kingPos && emptySquare & queenPos && emptySquare & queenBis
		&& emptySquare & queenKni && BR & queenRook) {
		if (*attackedW & queenPos || *attackedW & queenBis || *attackedW & queenKni) {
			moves += " O-O-O ";
		}
	}

}

string pawnPromo(string s) {
	return " " + s + "Q " + s + "N " + s + "B " + s + "R ";
}

string pawnPromoB(string s) {
	return " " + s + "q " + s + "n " + s + "b " + s + "r ";
}

void functionTime() {

	auto start = high_resolution_clock::now();

	getWLegalMoves(listOfBoardParamsAndOthers, "", 1, 1);

	auto end = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(end - start);

	cout << duration.count() << endl;

}