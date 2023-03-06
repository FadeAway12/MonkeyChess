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

string getWLegalMoves(moveParams, string lastMove) {

	setOtherBBs(listOfBoardParamsAndOthers);

	string moves = wPawnMoves(listOfBoardParamsAndOthers, lastMove) + " " + wKnightMoves(listOfBoardParamsAndOthers) + " " + 
		wKingMoves(listOfBoardParamsAndOthers) + " " + wRookMoves(listOfBoardParamsAndOthers) + " " + 
		wBishopMoves(listOfBoardParamsAndOthers) + " " + wQueenMoves(listOfBoardParamsAndOthers);

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

					enpL = pos << 1 & ~fileH & WP; //1 left and 1 up

					enpR = pos >> 1 & ~fileA & WP; //1 right and 1 up

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

				WRR = WRR << 1 & ~white & ~fileA & ~((WRL & black) << 1);
			}

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

				QR = QR << 1 & ~white & ~fileA & ~((QL & black) << 1);
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