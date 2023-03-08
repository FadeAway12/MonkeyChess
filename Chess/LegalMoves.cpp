#include "BoardRepresentation.h"

#include "LegalMoves.h"

#include <iostream>

#include <vector>

#include <string>

//<< means shifted RIGHT AND DOWN visually
//>> means shifted LEFT AND UP visually

using namespace std;

string lastMove; //formatted as piece, rowF, colF, rowT, colT

#define ts std::to_string

//moveParams - list of bitboards
//lastMove - used for en passant
//canLC - checks if queenside rook or king has moved already.
//canSC - checks if kingside rook or king has moved already
string getWLegalMoves(moveParams, string lastMove, bool canLC, bool canSC) {

	setOtherBBs(listOfBoardParamsAndOthers);

	string moves = wPawnMoves(listOfBoardParamsAndOthers, lastMove) + " " + wKnightMoves(listOfBoardParamsAndOthers) + " " + 
		wKingMoves(listOfBoardParamsAndOthers) + " " + wRookMoves(listOfBoardParamsAndOthers) + " " + 
		wBishopMoves(listOfBoardParamsAndOthers) + " " + wQueenMoves(listOfBoardParamsAndOthers);

	return moves;
}

string getBLegalMoves(moveParams, string lastMove, bool canLC, bool canSC) {
	
	string moves = bPawnMoves(listOfBoardParamsAndOthers, lastMove) + " " + bKnightMoves(listOfBoardParamsAndOthers) + " " +
		bKingMoves(listOfBoardParamsAndOthers) + " " + bRookMoves(listOfBoardParamsAndOthers) + " " +
		bBishopMoves(listOfBoardParamsAndOthers) + " " + bQueenMoves(listOfBoardParamsAndOthers);

	return moves;
}

string wPawnMoves(moveParams, string lastMove) {

	string moves{};
	
	bb pawnUR { (WP >> 7) & black & ~rank8 & ~fileA }; //capturing to the right

	bb pawnUL { (WP >> 9) & black & ~rank8 & ~fileH }; //capturing to the left

	bb pawnU  { (WP >> 8) & ~rank8 & emptySquare };

	bb pawnDJ { ((WP >> 16) & rank4 & emptySquare) & ((WP >> 8) & ~rank8 & emptySquare) >> 8 }; //going up 2 squares

	bb pawnPCR{ (WP >> 7) & rank8 & black }; //promo cap right

	bb pawnPCL{ (WP >> 9) & rank8 & black }; //promo cap left

	bb pawnPU{ (WP >> 8) & rank8 & emptySquare }; //straight up promo

	//EN PASSANT:

	bb enpL{ 0 };

	bb enpR{ 0 };

	if (lastMove.size()) {
		if (lastMove[0] == 'p') {
			try {
				int rowF = lastMove[1] - '0';
				int colF = lastMove[2] - '0';
				int rowT = lastMove[3] - '0';
				int colT = lastMove[4] - '0';

				if (rowF == 1 && rowT == 3) {

					bb pos = pow(2, 24 + colT); //24 is rowT*8

					enpL = pos << 1 & ~fileA & WP; //1 left and 1 up

					enpR = pos >> 1 & ~fileH & WP; //1 right and 1 up

				}

			}
			catch (...) {
				cerr << "Invalid last move.";
			}
		}
	} //gathering en passant moves

	for (int i = 0; i < 64; i++) {
		
		if (((pawnUR >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

		if (((pawnUL >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((pawnU >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((pawnDJ >> i) & 1) == 1) moves += " " + ts(i / 8 + 2) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((pawnPCR >> i) & 1) == 1) moves+= pawnPromo(ts(i / 8 + 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8));

		if (((pawnPCL >> i) & 1) == 1) moves+= pawnPromo(ts(i / 8 + 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8));

		if (((pawnPU >> i) & 1) == 1) moves+= pawnPromo(ts(i / 8 + 1) + ts(i % 8) + ts(i / 8) + ts(i % 8));

		if (((enpL >> i) & 1) == 1) moves += " " + (ts(i / 8) + ts(i % 8) + ts(i / 8 - 1) + ts(i % 8 - 1));

		if (((enpR >> i) & 1) == 1) moves += " " + (ts(i / 8) + ts(i % 8) + ts(i / 8 - 1) + ts(i % 8 + 1));

	} //goes through and adds moves//goes through and add moves

	return moves;

}

string pawnPromo(string s) {
	return " " + s + "Q " + s + "N " + s + "B " + s + "R ";
}

string pawnPromoB(string s) {
	return " " + s + "q " + s + "n " + s + "b " + s + "r ";
}

string wKnightMoves(moveParams) {

#define ts std::to_string

	string moves{};

	bb knightMovesRU{ WN >> 6 & ~fileA & ~fileB & ~white }; //2 right, 1 up

	bb knightMovesLU{ WN >> 10 & ~fileG & ~fileH & ~white };

	bb knightMovesUR{ WN >> 15 & ~fileA & ~white };
	
	bb knightMovesUL{ WN >> 17 & ~fileH & ~white };

	bb knightMovesLD{ WN << 6 & ~fileH & ~fileG & ~white };

	bb knightMovesRD{ WN << 10 & ~fileA & ~fileB & ~white };

	bb knightMovesDL{ WN << 15 & ~fileH & ~white };

	bb knightMovesDR{ WN << 17 & ~fileA & ~white };

	for (int i = 0; i < 64; i++) {

		if (((knightMovesRU >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8 - 2) + ts(i / 8) + ts(i % 8);

		if (((knightMovesLU >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8 + 2) + ts(i / 8) + ts(i % 8);

		if (((knightMovesUR >> i) & 1) == 1) moves += " " + ts(i / 8 + 2) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

		if (((knightMovesUL >> i) & 1) == 1) moves += " " + ts(i / 8 + 2) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((knightMovesLD >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8 + 2) + ts(i / 8) + ts(i % 8);

		if (((knightMovesRD >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8 - 2) + ts(i / 8) + ts(i % 8);

		if (((knightMovesDL >> i) & 1) == 1) moves += " " + ts(i / 8 - 2) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((knightMovesDR >> i) & 1) == 1) moves += " " + ts(i / 8 - 2) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

	}

	return moves;
}

string wKingMoves(moveParams) {

	string moves{};

	bb kingUR{ WK >> 7 & ~white & ~fileA };

	bb kingU { WK >> 8 & ~white };

	bb kingUL{ WK >> 9 & ~white & ~fileH };

	bb kingL { WK >> 1 & ~white & ~fileH };

	bb kingR { WK << 1 & ~white & ~fileA };

	bb kingDL{ WK << 7 & ~white & ~fileH };

	bb kingD { WK << 8 & ~white };

	bb kingDR{ WK << 9 & ~white & ~fileA };

	for (int i = 0; i < 64; i++) {

		if (((kingUR >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

		if (((kingU >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((kingUL >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((kingL >> i) & 1) == 1) moves += " " + ts(i / 8) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((kingR >> i) & 1) == 1) moves += " " + ts(i / 8) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

		if (((kingDL >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((kingD >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((kingDR >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

	}

	return moves;

}

string wRookMoves(moveParams) {

	string moves{};

	for (int i = 0; i < 64; i++) {
		if (((WR >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb WRU = pos >> 8 & ~white & ~((pos & black) >> 8);
			int count{ 0 };
			while (WRU) {
				
				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts (i/8 - count) + ts(i%8) + " ";

				WRU = WRU >> 8 & ~white & ~((WRU & black) >> 8);
			}

			count = 0;

			bb WRL = pos >> 1 & ~white & ~fileH & ~((pos & black) >> 1);

			while (WRL) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 - count) + " ";

				WRL = WRL >> 1 & ~white & ~fileH & ~((WRL & black) >> 1);
			}

			count = 0;

			bb WRR = pos << 1 & ~white & ~fileA & ~((pos & black) << 1);

			while (WRR) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 + count) + " ";

				WRR = WRR << 1 & ~white & ~fileA & ~((WRR & black) << 1);
			}

			cout << count << endl;

			bb WRD = pos << 8 & ~white & ~((pos & black) << 8);

			count = 0;

			while (WRD) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8) + " ";

				WRD = WRD << 8 & ~white & ~((WRD & black) << 8);
			}

		}
	}

	return moves;

}

string wBishopMoves(moveParams) {

	string moves{};

	for (int i = 0; i < 64; i++) {

		if (((WB >> i) & 1) == 1) {

			// top right

			bb pos = pow(2, i);

			bb WBUR = pos >> 7 & ~fileA & ~white & ~((pos & black) >> 7);

			int count{};

			while (WBUR) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 + count) + " ";

				WBUR = WBUR >> 7 & ~fileA & ~white & ~((WBUR & black) >> 7);

			}

			count = 0;

			bb WBUL = pos >> 9 & ~fileH & ~white & ~((pos & black) >> 9);

			while (WBUL) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 - count) + " ";

				WBUL = WBUL >> 9 & ~fileH & ~white & ~((WBUL & black) >> 9);

			}

			count = 0;

			bb WBDL = pos << 7 & ~fileH & ~white & ~((pos & black) << 7);

			while (WBDL) {


				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 - count) + " ";

				WBDL = WBDL << 7 & ~fileH & ~white & ~((WBDL & black) << 7);

			}

			count = 0;

			bb WBDR = pos << 9 & ~fileA & ~white & ~((pos & black) << 9);

			while (WBDR) {


				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 + count) + " ";

				WBDR = WBDR << 9 & ~fileA & ~white & ~((WBDR & black) << 9);

			}

		}

	}

	return moves;

}

string wQueenMoves(moveParams) {

	string moves{};
	for (int i = 0; i < 64; i++) {
		if (((WQ >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb QU = pos >> 8 & ~white & ~((pos & black) >> 8);
			int count{ 0 };
			while (QU) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8) + " ";

				QU = QU >> 8 & ~white & ~((QU & black) >> 8);
			}

			count = 0;

			bb QL = pos >> 1 & ~white & ~fileH & ~((pos & black) >> 1);

			while (QL) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 - count) + " ";

				QL = QL >> 1 & ~white & ~fileH & ~((QL & black) >> 1);
			}

			count = 0;

			bb QR = pos << 1 & ~white & ~fileA & ~((pos & black) << 1);

			while (QR) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 + count) + " ";

				QR = QR << 1 & ~white & ~fileA & ~((QR & black) << 1);
			}

			bb QD = pos << 8 & ~white & ~((pos & black) << 8);

			count = 0;

			while (QD) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8) + " ";

				QD = QD << 8 & ~white & ~((QD & black) << 8);
			}

			bb QUR = pos >> 7 & ~fileA & ~white & ~((pos & black) >> 7);

			count = 0;

			while (QUR) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 + count) + " ";

				QUR = QUR >> 7 & ~fileA & ~white & ~((QUR & black) >> 7);

			}

			count = 0;

			bb QUL = pos >> 9 & ~fileH & ~white & ~((pos & black) >> 9);

			while (QUL) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 - count) + " ";

				QUL = QUL >> 9 & ~fileH & ~white & ~((QUL & black) >> 9);

			}

			count = 0;

			bb QDL = pos << 7 & ~fileH & ~white & ~((pos & black) << 7);

			while (QDL) {


				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 - count) + " ";

				QDL = QDL << 7 & ~fileH & ~white & ~((QDL & black) << 7);

			}

			count = 0;

			bb QDR = pos << 9 & ~fileA & ~white & ~((pos & black) << 9);

			while (QDR) {


				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 + count) + " ";

				QDR = QDR << 9 & ~fileA & ~white & ~((QDR & black) << 9);
			}
		}
	}


	return moves;

}

string bPawnMoves(moveParams, string lastMove) {

	string moves{};

	bb pawnDR{ (BP << 9) & white & ~rank8 & ~fileA }; //capturing to the right down

	bb pawnDL{ (BP << 7) & white & ~rank8 & ~fileH }; //capturing to the left down

	bb pawnD{ (BP << 8) & ~rank1 & emptySquare }; //straight down

	bb pawnDJ{ ((BP << 16) & rank4 & emptySquare) & ((BP << 8) & ~rank1 & emptySquare) << 8 }; //going up 2 squares

	bb pawnPDR{ (BP << 7) & rank1 & white }; //promo cap right

	bb pawnPDL{ (BP << 9) & rank1 & white }; //promo cap left

	bb pawnPD{ (BP << 8) & rank1 & emptySquare }; //straight up promo

	//EN PASSANT:

	bb enpL{ 0 };

	bb enpR{ 0 };

	if (lastMove.size()) {
		if (lastMove[0] == 'P') {
			try {
				int rowF = lastMove[1] - '0';
				int colF = lastMove[2] - '0';
				int rowT = lastMove[3] - '0';
				int colT = lastMove[4] - '0';

				if (rowF == 6 && rowT == 4) {

					bb pos = pow(2, 32 + colT); //32 is rowT*8

					enpL = pos << 1 & ~fileA & BP; //1 right and 1 down

					enpR = pos >> 1 & ~fileH & BP; //1 left and 1 down

				}

			}
			catch (...) {
				cerr << "Invalid last move.";
			}
		}
	} //gathering en passant moves

	for (int i = 0; i < 64; i++) {

		if (((pawnDR >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

		if (((pawnDL >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((pawnD >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((pawnDJ >> i) & 1) == 1) moves += " " + ts(i / 8 - 2) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((pawnPDR >> i) & 1) == 1) moves += pawnPromoB(ts(i / 8 - 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8));

		if (((pawnPDL >> i) & 1) == 1) moves += pawnPromoB(ts(i / 8 - 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8));

		if (((pawnPD >> i) & 1) == 1) moves += pawnPromoB(ts(i / 8 - 1) + ts(i % 8) + ts(i / 8) + ts(i % 8));

		if (((enpL >> i) & 1) == 1) moves += " " + (ts(i / 8) + ts(i % 8) + ts(i / 8 + 1) + ts(i % 8 - 1));

		if (((enpR >> i) & 1) == 1) moves += " " + (ts(i / 8) + ts(i % 8) + ts(i / 8 + 1) + ts(i % 8 + 1));

	}

	return moves;
	
}

string bKnightMoves(moveParams) {

	string moves{};

	bb knightMovesRU{ WN >> 6 & ~fileA & ~fileB & ~white }; //2 right, 1 up

	bb knightMovesLU{ WN >> 10 & ~fileG & ~fileH & ~white };

	bb knightMovesUR{ WN >> 15 & ~fileA & ~white };

	bb knightMovesUL{ WN >> 17 & ~fileH & ~white };

	bb knightMovesLD{ WN << 6 & ~fileH & ~fileG & ~white };

	bb knightMovesRD{ WN << 10 & ~fileA & ~fileB & ~white };

	bb knightMovesDL{ WN << 15 & ~fileH & ~white };

	bb knightMovesDR{ WN << 17 & ~fileA & ~white };

	for (int i = 0; i < 64; i++) {

		if (((knightMovesRU >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8 - 2) + ts(i / 8) + ts(i % 8);

		if (((knightMovesLU >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8 + 2) + ts(i / 8) + ts(i % 8);

		if (((knightMovesUR >> i) & 1) == 1) moves += " " + ts(i / 8 + 2) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

		if (((knightMovesUL >> i) & 1) == 1) moves += " " + ts(i / 8 + 2) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((knightMovesLD >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8 + 2) + ts(i / 8) + ts(i % 8);

		if (((knightMovesRD >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8 - 2) + ts(i / 8) + ts(i % 8);

		if (((knightMovesDL >> i) & 1) == 1) moves += " " + ts(i / 8 - 2) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((knightMovesDR >> i) & 1) == 1) moves += " " + ts(i / 8 - 2) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

	}

	return moves;
}

string bKingMoves(moveParams) {

	string moves{};

	bb kingUR{ BK >> 7 & ~black & ~fileA };

	bb kingU{ BK >> 8 & ~black };

	bb kingUL{ BK >> 9 & ~black & ~fileH };

	bb kingL{ BK >> 1 & ~black & ~fileH };

	bb kingR{ BK << 1 & ~black & ~fileA };

	bb kingDL{ BK << 7 & ~black & ~fileH };

	bb kingD{ BK << 8 & ~black };

	bb kingDR{ BK << 9 & ~black & ~fileA };

	for (int i = 0; i < 64; i++) {

		if (((kingUR >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

		if (((kingU >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((kingUL >> i) & 1) == 1) moves += " " + ts(i / 8 + 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((kingL >> i) & 1) == 1) moves += " " + ts(i / 8) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((kingR >> i) & 1) == 1) moves += " " + ts(i / 8) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

		if (((kingDL >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((kingD >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((kingDR >> i) & 1) == 1) moves += " " + ts(i / 8 - 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

	}

	return moves;

}

string bRookMoves(moveParams) {

	string moves{};

	for (int i = 0; i < 64; i++) {
		if (((BR >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb BRU = pos >> 8 & ~black & ~((pos & white) >> 8);
			int count{ 0 };
			while (BRU) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8) + " ";

				BRU = BRU >> 8 & ~black & ~((BRU & white) >> 8);
			}

			count = 0;

			bb BRL = pos >> 1 & ~black & ~fileH & ~((pos & white) >> 1);

			while (BRL) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 - count) + " ";

				BRL = BRL >> 1 & ~black & ~fileH & ~((BRL & white) >> 1);
			}

			count = 0;

			bb BRR = pos << 1 & ~black & ~fileA & ~((pos & white) << 1);

			while (BRR) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 + count) + " ";

				BRR = BRR << 1 & ~black & ~fileA & ~((BRR & white) << 1);
			}

			bb BRD = pos << 8 & ~black & ~((pos & white) << 8);

			count = 0;

			while (BRD) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8) + " ";

				BRD = BRD << 8 & ~black & ~((BRD & white) << 8);
			}

		}
	}

	return moves;

}

string bBishopMoves(moveParams) {

	string moves{};

	for (int i = 0; i < 64; i++) {

		if (((BB >> i) & 1) == 1) {

			// top right

			bb pos = pow(2, i);

			bb BBUR = pos >> 7 & ~fileA & ~black & ~((pos & white) >> 7);

			int count{};

			while (BBUR) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 + count) + " ";

				BBUR = BBUR >> 7 & ~fileA & ~black & ~((BBUR & white) >> 7);

			}

			count = 0;

			bb BBUL = pos >> 9 & ~fileH & ~black & ~((pos & white) >> 9);

			while (BBUL) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 - count) + " ";

				BBUL = BBUL >> 9 & ~fileH & ~black & ~((BBUL & white) >> 9);

			}

			count = 0;

			bb BBDL = pos << 7 & ~fileH & ~black & ~((pos & white) << 7);

			while (BBDL) {


				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 - count) + " ";

				BBDL = BBDL << 7 & ~fileH & ~black & ~((BBDL & white) << 7);

			}

			count = 0;

			bb BBDR = pos << 9 & ~fileA & ~black & ~((pos & white) << 9);

			while (BBDR) {


				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 + count) + " ";

				BBDR = BBDR << 9 & ~fileA & ~black & ~((BBDR & white) << 9);

			}

		}

	}

	return moves;

}

string bQueenMoves(moveParams) {

	string moves{};
	for (int i = 0; i < 64; i++) {
		if (((BQ >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb QU = pos >> 8 & ~black & ~((pos & white) >> 8);
			int count{ 0 };
			while (QU) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8) + " ";

				QU = QU >> 8 & ~black & ~((QU & white) >> 8);
			}

			count = 0;

			bb QL = pos >> 1 & ~black & ~fileH & ~((pos & white) >> 1);

			while (QL) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 - count) + " ";

				QL = QL >> 1 & ~black & ~fileH & ~((QL & white) >> 1);
			}

			count = 0;

			bb QR = pos << 1 & ~black & ~fileA & ~((pos & white) << 1);

			while (QR) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 + count) + " ";

				QR = QR << 1 & ~black & ~fileA & ~((QR & white) << 1);
			}

			bb QD = pos << 8 & ~black & ~((pos & white) << 8);

			count = 0;

			while (QD) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8) + " ";

				QD = QD << 8 & ~black & ~((QD & white) << 8);
			}

			bb QUR = pos >> 7 & ~fileA & ~black & ~((pos & white) >> 7);

			count = 0;

			while (QUR) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 + count) + " ";

				QUR = QUR >> 7 & ~fileA & ~black & ~((QUR & white) >> 7);

			}

			count = 0;

			bb QUL = pos >> 9 & ~fileH & ~black & ~((pos & white) >> 9);

			while (QUL) {

				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 - count) + " ";

				QUL = QUL >> 9 & ~fileH & ~black & ~((QUL & white) >> 9);

			}

			count = 0;

			bb QDL = pos << 7 & ~fileH & ~black & ~((pos & white) << 7);

			while (QDL) {


				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 - count) + " ";

				QDL = QDL << 7 & ~fileH & ~black & ~((QDL & white) << 7);

			}

			count = 0;

			bb QDR = pos << 9 & ~fileA & ~black & ~((pos & white) << 9);

			while (QDR) {


				count++;

				moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 + count) + " ";

				QDR = QDR << 9 & ~fileA & ~black & ~((QDR & white) << 9);
			}
		}
	}


	return moves;

}