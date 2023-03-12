#include "BoardRepresentation.h"

#include "LegalMoves.h"

#include "LegalMoveHelpers.h"

#include <iostream>

#include <vector>

#include <string>

//<< means shifted RIGHT AND DOWN visually
//>> means shifted LEFT AND UP visually

constexpr bb allSpots{ 18'446'744'073'709'551'615 };

using namespace std;

string lastMove; //formatted as piece, rowF, colF, rowT, colT

#define ts std::to_string

//moveParams - list of bitboards
//lastMove - used for en passant
//canLC - checks if queenside rook or king has moved already.
//canSC - checks if kingside rook or king has moved already
string getWLegalMoves(moveParams, string lastMove, bool canLC, bool canSC) {

	setOtherBBs(listOfBoardParamsAndOthers);

	bb* blackAttack = new bb{ attackedByBlack(listOfBoardParamsAndOthers) }; //initliaze to black attack

	bool inCheck(*blackAttack & WK);

	bb* check = new bb[2]{ 0, 0 };

	vector<bb> pinned = findPinnedPiecesWhite(listOfBoardParamsAndOthers, check); //also looks for what piece is chekcing king

	if (inCheck) {
		
		if (check[1] != 0) { //in a double check, only the king can move, so we only search possible king moves
			return wKingMoves(listOfBoardParamsAndOthers, blackAttack, check, pinned);
		}

	}

	string moves = 
		wPawnMoves(listOfBoardParamsAndOthers, lastMove, check, pinned) + " " + 
		wKnightMoves(listOfBoardParamsAndOthers, check, pinned) + " " +
		wKingMoves(listOfBoardParamsAndOthers, blackAttack, check, pinned) + " " + 
		wRookMoves(listOfBoardParamsAndOthers, check, pinned) + " " +
		wBishopMoves(listOfBoardParamsAndOthers, check, pinned) + " " + 
		wQueenMoves(listOfBoardParamsAndOthers, check, pinned);

	addCastlingMovesWhite(listOfBoardParamsAndOthers, blackAttack, moves, canSC, canLC, inCheck);

	delete[] check, blackAttack;

	return moves;
}

string getBLegalMoves(moveParams, string lastMove, bool canLC, bool canSC) {
	
	setOtherBBs(listOfBoardParamsAndOthers);

	bb* whiteAttack = new bb{attackedByWhite(listOfBoardParamsAndOthers) };

	bool inCheck(*whiteAttack & BK);

	bb* check = new bb[2]{ 0, 0 };

	vector<bb> pinned = findPinnedPiecesBlack(listOfBoardParamsAndOthers, check);

	if (inCheck) {

		if (check[1] != 0) { //in a double check, only the king can move, so we only search possible king moves
			return bKingMoves(listOfBoardParamsAndOthers, whiteAttack, check, pinned);
		}

	}
	
	string moves = 
		bPawnMoves(listOfBoardParamsAndOthers, lastMove, check, pinned) + " " +
		bKnightMoves(listOfBoardParamsAndOthers, check, pinned) + " " +
		bKingMoves(listOfBoardParamsAndOthers, whiteAttack, check, pinned) + " " +
		bRookMoves(listOfBoardParamsAndOthers, check, pinned) + " " +
		bBishopMoves(listOfBoardParamsAndOthers, check, pinned) + " " +
		bQueenMoves(listOfBoardParamsAndOthers, check, pinned);

	addCastlingMovesBlack(listOfBoardParamsAndOthers, whiteAttack, moves, canSC, canLC, inCheck);

	delete[] check, whiteAttack;

	return moves;
}

//helper methods

string wPawnMoves(moveParams, string lastMove, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb check = *checkers;

	bb pinnedLine{ allSpots }; //pinnedline by default is set to occupy all locations on the bitboard because if
	//it is not pinned, we and it with the move to see where it can move to. if there is a pinned line, it will make sure
	//it can only move to a place where the pin is maintained.

	for (int i = 0; i < pinned.size(); i++) {
		if (WP & pinned[i]) pinnedLine = pinned[i] | WK;
	}

	bb pawnUR { (WP >> 7) & check & black & ~rank8 & ~fileA }; //capturing to the right

	bb pawnUL { (WP >> 9) & check & black & ~rank8 & ~fileH }; //capturing to the left

	bb pawnU  { (WP >> 8) & check & ~rank8 & emptySquare };

	bb pawnDJ { ((WP >> 16) & check & rank4 & emptySquare) & ((WP >> 8) & ~rank8 & emptySquare) >> 8 }; //going up 2 squares

	bb pawnPCR{ (WP >> 7) & check & rank8 & black }; //promo cap right

	bb pawnPCL{ (WP >> 9) & check & rank8 & black }; //promo cap left

	bb pawnPU{ (WP >> 8) & check & rank8 & emptySquare }; //straight up promo

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

					enpL = pos << 1 & check & ~fileA & WP; //1 left and 1 up

					enpR = pos >> 1 & check & ~fileH & WP; //1 right and 1 up

				}

			}
			catch (...) {
				cerr << "Invalid last move.";
			}
		}
	} //gathering en passant moves

	for (int i = 0; i < 64; i++) {

		bb move{};

		bool pin{ false };
		
		if (pinnedLine != allSpots) {
			move = pow(2, i);

			pin = true;
		}

		//(WP & ~(move << 7) & move)

		if (((pawnUR >> i) & 1) == 1 && ((WP & pinnedLine & ~move << 7 | move) || !pin)) moves += " " + ts(i / 8 + 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

		if (((pawnUL >> i) & 1) == 1 && ((WP & pinnedLine & ~move << 9 | move) || !pin)) moves += " " + ts(i / 8 + 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((pawnU >> i) & 1) == 1 && ((WP & pinnedLine & ~move << 8 | move) || !pin)) moves += " " + ts(i / 8 + 1) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((pawnDJ >> i) & 1) == 1 && ((WP & pinnedLine & ~move << 16 | move) || !pin)) moves += " " + ts(i / 8 + 2) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((pawnPCR >> i) & 1) == 1 && ((WP & pinnedLine & ~move << 7 | move) || !pin)) moves+= pawnPromo(ts(i / 8 + 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8));

		if (((pawnPCL >> i) & 1) == 1 && ((WP & pinnedLine & ~move << 9 | move) || !pin)) moves+= pawnPromo(ts(i / 8 + 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8));

		if (((pawnPU >> i) & 1) == 1 && ((WP & pinnedLine & ~move << 8 | move) || !pin)) moves+= pawnPromo(ts(i / 8 + 1) + ts(i % 8) + ts(i / 8) + ts(i % 8));

		if (((enpL >> i) & 1) == 1 && ((WP & pinnedLine & ~move << 9 | move) || !pin)) moves += " " + (ts(i / 8) + ts(i % 8) + ts(i / 8 - 1) + ts(i % 8 - 1));

		if (((enpR >> i) & 1) == 1 && ((WP & pinnedLine & ~move << 7 | move) || !pin)) moves += " " + (ts(i / 8) + ts(i % 8) + ts(i / 8 - 1) + ts(i % 8 + 1));

	} //goes through and adds moves//goes through and add moves

	return moves;

}

string wKnightMoves(moveParams, bb* checkers, vector<bb> pinned) {
	string moves{};

	bb check = *checkers;

	bb pinnedLine{ 0 };

	for (int i = 0; i < pinned.size(); i++) {
		if (WN & pinned[i]) pinnedLine = pinned[i] | WK;
	}

	bb knightMovesRU{ (WN & ~pinnedLine) >> 6 & check & ~fileA & ~fileB & ~white}; //2 right, 1 up

	bb knightMovesLU{ (WN & ~pinnedLine) >> 10 & check & ~fileG & ~fileH & ~white };

	bb knightMovesUR{ (WN & ~pinnedLine) >> 15 & check & ~fileA & ~white };
	
	bb knightMovesUL{ (WN & ~pinnedLine) >> 17 & check & ~fileH & ~white };

	bb knightMovesLD{ (WN & ~pinnedLine) << 6 & check & ~fileH & ~fileG & ~white };

	bb knightMovesRD{ (WN & ~pinnedLine) << 10 & check & ~fileA & ~fileB & ~white };

	bb knightMovesDL{ (WN & ~pinnedLine) << 15 & check & ~fileH & ~white };

	bb knightMovesDR{ (WN & ~pinnedLine) << 17 & check & ~fileA & ~white };

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

string wKingMoves(moveParams, bb* unsafe, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb kingUR{ WK >> 7 & ~white & ~fileA & ~*unsafe};

	bb kingU { WK >> 8 & ~white & ~*unsafe };

	bb kingUL{ WK >> 9 & ~white & ~fileH & ~*unsafe };

	bb kingL { WK >> 1 & ~white & ~fileH & ~*unsafe };

	bb kingR { WK << 1 & ~white & ~fileA & ~*unsafe };

	bb kingDL{ WK << 7 & ~white & ~fileH & ~*unsafe };

	bb kingD { WK << 8 & ~white & ~*unsafe };

	bb kingDR{ WK << 9 & ~white & ~fileA & ~*unsafe };

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

string wRookMoves(moveParams, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb check = *checkers;

	bb pinnedLine{ allSpots };

	for (int i = 0; i < pinned.size(); i++) {
		if (WR & pinned[i]) pinnedLine = pinned[i] | WK;
	}

	for (int i = 0; i < 64; i++) {
		if (((WR >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb WRU = pos >> 8 & ~white & ~((pos & black) >> 8);
			int count{ 0 };
			while (WRU) {

				count++;

				if (!(WR >> 8 * count & pinnedLine)) break;

				if (check & WRU & ~(WRU << 8)) moves = moves + ts(i / 8) + ts(i % 8) + ts (i/8 - count) + ts(i%8) + " ";

				WRU = WRU >> 8 & ~white & ~((WRU & black) >> 8);
			}

			count = 0;

			bb WRL = pos >> 1 & ~white & ~fileH & ~((pos & black) >> 1);

			while (WRL) {

				count++;

				if (!(WR >> 1 * count & pinnedLine)) break;

				if (check & WRL & ~(WRL << 1)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 - count) + " ";

				WRL = WRL >> 1 & ~white & ~fileH & ~((WRL & black) >> 1);
			}

			count = 0;

			bb WRR = pos << 1 & ~white & ~fileA & ~((pos & black) << 1);

			while (WRR) {

				count++;

				if (!(WR << 1 * count & pinnedLine)) break;

				if (check & WRR & ~(WRR >> 1)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 + count) + " ";

				WRR = WRR << 1 & ~white & ~fileA & ~((WRR & black) << 1);
			}

			bb WRD = pos << 8 & ~white & ~((pos & black) << 8);

			count = 0;

			while (WRD) {

				count++;

				if (!(WR << 8 * count & pinnedLine)) break;

				if (check & WRD & ~(WRD >> 8)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8) + " ";

				WRD = WRD << 8 & ~white & ~((WRD & black) << 8);
			}

		}
	}

	return moves;

}

string wBishopMoves(moveParams, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb pinnedLine{ allSpots };

	bb check = *checkers;

	for (int i = 0; i < pinned.size(); i++) {
		if (WB & pinned[i]) pinnedLine = pinned[i] | WK;
	}

	for (int i = 0; i < 64; i++) {

		if (((WB >> i) & 1) == 1) {

			// top right

			bb pos = pow(2, i);

			bb WBUR = pos >> 7 & ~fileA & ~white & ~((pos & black) >> 7);

			int count{};

			while (WBUR) {

				count++;

				if (!(WB >> 7 * count & pinnedLine)) break;

				if (check & WBUR & ~(WBUR << 7)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 + count) + " ";

				WBUR = WBUR >> 7 & ~fileA & ~white & ~((WBUR & black) >> 7);

			}

			count = 0;

			bb WBUL = pos >> 9 & ~fileH & ~white & ~((pos & black) >> 9);

			while (WBUL) {

				count++;

				if (!(WB >> 9 * count & pinnedLine)) break;

				if (check & WBUL & ~(WBUL << 9)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 - count) + " ";

				WBUL = WBUL >> 9 & ~fileH & ~white & ~((WBUL & black) >> 9);

			}

			count = 0;

			bb WBDL = pos << 7 & ~fileH & ~white & ~((pos & black) << 7);

			while (WBDL) {

				count++;

				if (!(WB << 7 * count & pinnedLine)) break;

				if (check & WBDL & ~(WBDL >> 7)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 - count) + " ";

				WBDL = WBDL << 7 & ~fileH & ~white & ~((WBDL & black) << 7);

			}

			count = 0;

			bb WBDR = pos << 9 & ~fileA & ~white & ~((pos & black) << 9);

			while (WBDR) {

				count++;

				if (!(WB << 9 * count & pinnedLine)) break;

				if (check & WBDR & ~(WBDR >> 9)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 + count) + " ";

				WBDR = WBDR << 9 & ~fileA & ~white & ~((WBDR & black) << 9);

			}

		}

	}

	return moves;

}

string wQueenMoves(moveParams, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb pinnedLine{ allSpots };
	
	bb check = *checkers;

	for (int i = 0; i < pinned.size(); i++) {
		if (WQ & pinned[i]) pinnedLine = pinned[i] | WK;
	}

	for (int i = 0; i < 64; i++) {
		if (((WQ >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb QU = pos >> 8 & ~white & ~((pos & black) >> 8);
			int count{ 0 };
			while (QU) {

				count++;

				if (!(WQ >> 8 * count & pinnedLine)) break;

				if (check & QU & ~(QU << 8)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8) + " ";

				QU = QU >> 8 & ~white & ~((QU & black) >> 8);
			}

			count = 0;

			bb QL = pos >> 1 & ~white & ~fileH & ~((pos & black) >> 1);

			while (QL) {

				count++;

				if (!(WQ >> 1 * count & pinnedLine)) break;

				if (check & QL & ~(QL << 1)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 - count) + " ";

				QL = QL >> 1 & ~white & ~fileH & ~((QL & black) >> 1);
			}

			count = 0;

			bb QR = pos << 1 & ~white & ~fileA & ~((pos & black) << 1);

			while (QR) {

				count++;

				if (!(WQ << 1 * count & pinnedLine)) break;

				if (check & QR & ~(QR >> 1)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 + count) + " ";

				QR = QR << 1 & ~white & ~fileA & ~((QR & black) << 1);
			}

			bb QD = pos << 8 & ~white & ~((pos & black) << 8);

			count = 0;

			while (QD) {

				count++;

				if (!(WQ << 8 * count & pinnedLine)) break;

				if (check & QD & ~(QD >> 8)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8) + " ";

				QD = QD << 8 & ~white & ~((QD & black) << 8);
			}

			bb QUR = pos >> 7 & ~fileA & ~white & ~((pos & black) >> 7);

			count = 0;

			while (QUR) {

				count++;

				if (!(WQ >> 7 * count & pinnedLine)) break;

				if (check & QUR & ~(QUR << 7)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 + count) + " ";

				QUR = QUR >> 7 & ~fileA & ~white & ~((QUR & black) >> 7);

			}

			count = 0;

			bb QUL = pos >> 9 & ~fileH & ~white & ~((pos & black) >> 9);

			while (QUL) {

				count++;

				if (!(WQ >> 9 * count & pinnedLine)) break;

				if (check & QUL & ~(QUL << 9)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 - count) + " ";

				QUL = QUL >> 9 & ~fileH & ~white & ~((QUL & black) >> 9);

			}

			count = 0;

			bb QDL = pos << 7 & ~fileH & ~white & ~((pos & black) << 7);

			while (QDL) {

				count++;

				if (!(WQ << 7 * count & pinnedLine)) break;

				if (check & QDL & ~(QDL >> 7)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 - count) + " ";

				QDL = QDL << 7 & ~fileH & ~white & ~((QDL & black) << 7);

			}

			count = 0;

			bb QDR = pos << 9 & ~fileA & ~white & ~((pos & black) << 9);

			while (QDR) {

				count++;

				if (!(WQ << 9 * count & pinnedLine)) break;

				if (check & QDR & ~(QDR >> 9)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 + count) + " ";

				QDR = QDR << 9 & ~fileA & ~white & ~((QDR & black) << 9);
			}
		}
	}


	return moves;

}

string bPawnMoves(moveParams, string lastMove, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb check = *checkers;

	bb pinnedLine{ allSpots };

	for (int i = 0; i < pinned.size(); i++) {
		if (BP & pinned[i]) pinnedLine = pinned[i] | BK;
	}

	bb pawnDR{ (BP << 9) & check & white & ~rank8 & ~fileA }; //capturing to the right down

	bb pawnDL{ (BP << 7) & check & white & ~rank8 & ~fileH }; //capturing to the left down

	bb pawnD{ (BP << 8) & check & ~rank1 & emptySquare }; //straight down

	bb pawnDJ{ ((BP << 16) & check & rank5 & emptySquare) & ((BP << 8) & ~rank1 & emptySquare) << 8 }; //going up 2 squares

	bb pawnPDR{ (BP << 7) & check & rank1 & white }; //promo cap right

	bb pawnPDL{ (BP << 9) & check & rank1 & white }; //promo cap left

	bb pawnPD{ (BP << 8) & check & rank1 & emptySquare }; //straight up promo

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

					enpL = pos << 1 & check & ~fileA & BP; //1 right and 1 down

					enpR = pos >> 1 & check & ~fileH & BP; //1 left and 1 down

				}

			}
			catch (...) {
				cerr << "Invalid last move.";
			}
		}
	} //gathering en passant moves

	for (int i = 0; i < 64; i++) {

		bb move{};

		bool pin{ false };

		if (pinnedLine != allSpots) {
			move = pow(2, i);

			pin = true;
		}

		if (((pawnDR >> i) & 1) == 1 && ((BP & pinnedLine & ~move >> 9 | move) || !pin)) moves += " " + ts(i / 8 - 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8);

		if (((pawnDL >> i) & 1) == 1 && ((BP & pinnedLine & ~move >> 7 | move) || !pin)) moves += " " + ts(i / 8 - 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8);

		if (((pawnD >> i) & 1) == 1 && ((BP & pinnedLine & ~move >> 8 | move) || !pin)) moves += " " + ts(i / 8 - 1) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((pawnDJ >> i) & 1) == 1 && ((BP & pinnedLine & ~move >> 16 | move) || !pin)) moves += " " + ts(i / 8 - 2) + ts(i % 8) + ts(i / 8) + ts(i % 8);

		if (((pawnPDR >> i) & 1) == 1 && ((BP & pinnedLine & ~move >> 7 | move) || !pin)) moves += pawnPromoB(ts(i / 8 - 1) + ts(i % 8 - 1) + ts(i / 8) + ts(i % 8));

		if (((pawnPDL >> i) & 1) == 1 && ((BP & pinnedLine & ~move >> 9 | move) || !pin)) moves += pawnPromoB(ts(i / 8 - 1) + ts(i % 8 + 1) + ts(i / 8) + ts(i % 8));

		if (((pawnPD >> i) & 1) == 1 && ((BP & pinnedLine & ~move >> 8 | move) || !pin)) moves += pawnPromoB(ts(i / 8 - 1) + ts(i % 8) + ts(i / 8) + ts(i % 8));

		if (((enpL >> i) & 1) == 1 && ((BP & pinnedLine & ~move >> 7 | move) || !pin)) moves += " " + (ts(i / 8) + ts(i % 8) + ts(i / 8 + 1) + ts(i % 8 - 1));

		if (((enpR >> i) & 1) == 1 && ((BP & pinnedLine & ~move >> 9 | move) || !pin)) moves += " " + (ts(i / 8) + ts(i % 8) + ts(i / 8 + 1) + ts(i % 8 + 1));

	}

	return moves;
	
}

string bKnightMoves(moveParams, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb check = *checkers;

	bb pinnedLine{ 0 };

	for (int i = 0; i < pinned.size(); i++) {
		if (BN & pinned[i]) pinnedLine = pinned[i] | BK;
	}

	bb knightMovesRU{ (BN & ~pinnedLine) >> 6 & check >> 6 & ~fileA & ~fileB & ~black }; //2 right, 1 up

	bb knightMovesLU{ (BN & ~pinnedLine) >> 10 & check & ~fileG & ~fileH & ~black };

	bb knightMovesUR{ (BN & ~pinnedLine) >> 15 & check & ~fileA & ~black };

	bb knightMovesUL{ (BN & ~pinnedLine) >> 17 & check & ~fileH & ~black };

	bb knightMovesLD{ (BN & ~pinnedLine) << 6 & check & ~fileH & ~fileG & ~black };

	bb knightMovesRD{ (BN & ~pinnedLine) << 10 & check & ~fileA & ~fileB & ~black };

	bb knightMovesDL{ (BN & ~pinnedLine) << 15 & check & ~fileH & ~black };

	bb knightMovesDR{ (BN & ~pinnedLine) << 17 & check & ~fileA & ~black };

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

string bKingMoves(moveParams, bb* unsafe, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb kingUR{ BK >> 7 & ~black & ~fileA & ~*unsafe};

	bb kingU{ BK >> 8 & ~black & ~*unsafe };

	bb kingUL{ BK >> 9 & ~black & ~fileH & ~*unsafe };

	bb kingL{ BK >> 1 & ~black & ~fileH & ~*unsafe };

	bb kingR{ BK << 1 & ~black & ~fileA & ~*unsafe };

	bb kingDL{ BK << 7 & ~black & ~fileH & ~*unsafe };

	bb kingD{ BK << 8 & ~black & ~*unsafe };

	bb kingDR{ BK << 9 & ~black & ~fileA & ~*unsafe };

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

string bRookMoves(moveParams, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb check = *checkers;

	bb pinnedLine{ allSpots };

	for (int i = 0; i < pinned.size(); i++) {
		if (BR & pinned[i]) pinnedLine = pinned[i] | BK;
	}

	for (int i = 0; i < 64; i++) {
		if (((BR >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb BRU = pos >> 8 & ~black & ~((pos & white) >> 8);
			int count{ 0 };
			while (BRU) {

				count++;

				if (!(BR >> 8 * count & pinnedLine)) break;

				if (check & BRU & ~(BRU << 8)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8) + " ";

				BRU = BRU >> 8 & ~black & ~((BRU & white) >> 8);
			}

			count = 0;

			bb BRL = pos >> 1 & ~black & ~fileH & ~((pos & white) >> 1);

			while (BRL) {

				count++;

				if (!(BR >> 1 * count & pinnedLine)) break;

				if (check & BRL & ~(BRL << 1)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 - count) + " ";

				BRL = BRL >> 1 & ~black & ~fileH & ~((BRL & white) >> 1);
			}

			count = 0;

			bb BRR = pos << 1 & ~black & ~fileA & ~((pos & white) << 1);

			while (BRR) {

				count++;

				if (!(BR << 1 * count & pinnedLine)) break;

				if (check & BRR & ~(BRR >> 1)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 + count) + " ";

				BRR = BRR << 1 & ~black & ~fileA & ~((BRR & white) << 1);
			}

			bb BRD = pos << 8 & ~black & ~((pos & white) << 8);

			count = 0;

			while (BRD) {

				count++;

				if (!(BR << 8 * count & pinnedLine)) break;

				if (check & BRD & ~(BRD >> 8)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8) + " ";

				BRD = BRD << 8 & ~black & ~((BRD & white) << 8);
			}

		}
	}

	return moves;

}

string bBishopMoves(moveParams, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb pinnedLine{ allSpots };

	bb check = *checkers;

	for (int i = 0; i < pinned.size(); i++) {
		if (BB & pinned[i]) pinnedLine = pinned[i] | BK;
	}

	for (int i = 0; i < 64; i++) {

		if (((BB >> i) & 1) == 1) {

			// top right

			bb pos = pow(2, i);

			bb BBUR = pos >> 7 & ~fileA & ~black & ~((pos & white) >> 7);

			int count{};

			while (BBUR) {

				count++;

				if (!(BB >> 7 * count & pinnedLine)) break;

				if (check & BBUR & ~(BBUR << 7)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 + count) + " ";

				BBUR = BBUR >> 7 & ~fileA & ~black & ~((BBUR & white) >> 7);

			}

			count = 0;

			bb BBUL = pos >> 9 & ~fileH & ~black & ~((pos & white) >> 9);

			while (BBUL) {

				count++;

				if (!(BB >> 9 * count & pinnedLine)) break;

				if (check & BBUL & ~(BBUL << 9)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 - count) + " ";

				BBUL = BBUL >> 9 & ~fileH & ~black & ~((BBUL & white) >> 9);

			}

			count = 0;

			bb BBDL = pos << 7 & ~fileH & ~black & ~((pos & white) << 7);

			while (BBDL) {


				count++;

				if (!(BB << 7 * count & pinnedLine)) break;

				if (check & BBDL & ~(BBDL >> 7)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 - count) + " ";

				BBDL = BBDL << 7 & ~fileH & ~black & ~((BBDL & white) << 7);

			}

			count = 0;

			bb BBDR = pos << 9 & ~fileA & ~black & ~((pos & white) << 9);

			while (BBDR) {


				count++;

				if (!(BB << 9 * count & pinnedLine)) break;

				if (check & BBDR & ~(BBDR >> 9)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 + count) + " ";

				BBDR = BBDR << 9 & ~fileA & ~black & ~((BBDR & white) << 9);

			}

		}

	}

	return moves;

}

string bQueenMoves(moveParams, bb* checkers, vector<bb> pinned) {

	string moves{};

	bb pinnedLine{ allSpots };

	bb check = *checkers;

	for (int i = 0; i < pinned.size(); i++) {
		if (BQ & pinned[i]) pinnedLine = pinned[i] | BK;
	}

	for (int i = 0; i < 64; i++) {
		if (((BQ >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb QU = pos >> 8 & ~black & ~((pos & white) >> 8);
			int count{ 0 };
			while (QU) {

				count++;

				if (!(BQ >> 8 * count & pinnedLine)) break;

				if (check & QU & ~(QU << 8)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8) + " ";

				QU = QU >> 8 & ~black & ~((QU & white) >> 8);
			}

			count = 0;

			bb QL = pos >> 1 & ~black & ~fileH & ~((pos & white) >> 1);

			while (QL) {

				count++;

				if (!(BQ >> 1 * count & pinnedLine)) break;

				if (check & QL & ~(QL << 1)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 - count) + " ";

				QL = QL >> 1 & ~black & ~fileH & ~((QL & white) >> 1);
			}

			count = 0;

			bb QR = pos << 1 & ~black & ~fileA & ~((pos & white) << 1);

			while (QR) {

				count++;

				if (!(BQ << 1 * count & pinnedLine)) break;

				if (check & QR & ~(QR >> 1)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8) + ts(i % 8 + count) + " ";

				QR = QR << 1 & ~black & ~fileA & ~((QR & white) << 1);
			}

			bb QD = pos << 8 & ~black & ~((pos & white) << 8);

			count = 0;

			while (QD) {

				count++;

				if (!(BQ << 8 * count & pinnedLine)) break;

				if (check & QD & ~(QD >> 8)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8) + " ";

				QD = QD << 8 & ~black & ~((QD & white) << 8);
			}

			bb QUR = pos >> 7 & ~fileA & ~black & ~((pos & white) >> 7);

			count = 0;

			while (QUR) {

				count++;

				if (!(BQ >> 7 * count & pinnedLine)) break;

				if (check & QUR & ~(QUR << 7)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 + count) + " ";

				QUR = QUR >> 7 & ~fileA & ~black & ~((QUR & white) >> 7);

			}

			count = 0;

			bb QUL = pos >> 9 & ~fileH & ~black & ~((pos & white) >> 9);

			while (QUL) {

				count++;

				if (!(BQ >> 9 * count & pinnedLine)) break;

				if (check & QUL & ~(QUL << 9)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 - count) + ts(i % 8 - count) + " ";

				QUL = QUL >> 9 & ~fileH & ~black & ~((QUL & white) >> 9);

			}

			count = 0;

			bb QDL = pos << 7 & ~fileH & ~black & ~((pos & white) << 7);

			while (QDL) {


				count++;

				if (!(BQ << 7 * count & pinnedLine)) break;

				if (check & QDL & ~(QDL >> 7)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 - count) + " ";

				QDL = QDL << 7 & ~fileH & ~black & ~((QDL & white) << 7);

			}

			count = 0;

			bb QDR = pos << 9 & ~fileA & ~black & ~((pos & white) << 9);

			while (QDR) {


				count++;

				if (!(BQ << 9 * count & pinnedLine)) break;

				if (check & QDR & ~(QDR >> 9)) moves = moves + ts(i / 8) + ts(i % 8) + ts(i / 8 + count) + ts(i % 8 + count) + " ";

				QDR = QDR << 9 & ~fileA & ~black & ~((QDR & white) << 9);
			}
		}
	}


	return moves;

}