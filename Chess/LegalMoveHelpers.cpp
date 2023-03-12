#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <chrono>

#include "BoardRepresentation.h"
#include "LegalMoveHelpers.h"
#include "LegalMoves.h"
#include "MoveExecution.h"

using namespace std;
using namespace chrono;

constexpr bb allSpots{ 18'446'744'073'709'551'615 };

//<< means shifted RIGHT AND DOWN visually
//>> means shifted LEFT AND UP visually

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

				WRU = WRU >> 8 & ~white & ~((WRU & black & ~BK) >> 8);
			}

			bb WRL = pos >> 1 & ~white & ~fileH & ~((pos & black & ~BK) >> 1);

			while (WRL) {

				attacked |= WRL;

				WRL = WRL >> 1 & ~white & ~fileH & ~((WRL & black & ~BK) >> 1);
			}

			bb WRR = pos << 1 & ~white & ~fileA & ~((pos & black & ~BK) << 1);

			while (WRR) {

				attacked |= WRR;

				WRR = WRR << 1 & ~white & ~fileA & ~((WRR & black & ~BK) << 1);
			}

			bb WRD = pos << 8 & ~white & ~((pos & black & ~BK) << 8);

			while (WRD) {

				attacked |= WRD;

				WRD = WRD << 8 & ~white & ~((WRD & black & ~BK) << 8);
			}

		}
		else if (((WB >> i) & 1) == 1) {
			bb pos = pow(2, i);

			bb WBUR = pos >> 7 & ~fileA & ~white & ~((pos & black & ~BK) >> 7);

			while (WBUR) {

				attacked |= WBUR;

				WBUR = WBUR >> 7 & ~fileA & ~white & ~((WBUR & black & ~BK) >> 7);

			}

			bb WBUL = pos >> 9 & ~fileH & ~white & ~((pos & black & ~BK) >> 9);

			while (WBUL) {

				attacked |= WBUL;

				WBUL = WBUL >> 9 & ~fileH & ~white & ~((WBUL & black & ~BK) >> 9);

			}

			bb WBDL = pos << 7 & ~fileH & ~white & ~((pos & black & ~BK) << 7);

			while (WBDL) {


				attacked |= WBDL;

				WBDL = WBDL << 7 & ~fileH & ~white & ~((WBDL & black & ~BK) << 7);

			}

			bb WBDR = pos << 9 & ~fileA & ~white & ~((pos & black & ~BK) << 9);

			while (WBDR) {


				attacked |= WBDR;

				WBDR = WBDR << 9 & ~fileA & ~white & ~((WBDR & black & ~BK) << 9);

			}
		}
		else if (((WQ >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb QU = pos >> 8 & ~white & ~((pos & black & ~BK) >> 8);

			while (QU) {

				attacked |= QU;

				QU = QU >> 8 & ~white & ~((QU & black & ~BK) >> 8);
			}



			bb QL = pos >> 1 & ~white & ~fileH & ~((pos & black & ~BK) >> 1);

			while (QL) {

				attacked |= QL;

				QL = QL >> 1 & ~white & ~fileH & ~((QL & black & ~BK) >> 1);
			}



			bb QR = pos << 1 & ~white & ~fileA & ~((pos & black & ~BK) << 1);

			while (QR) {

				attacked |= QR;

				QR = QR << 1 & ~white & ~fileA & ~((QR & black & ~BK) << 1);
			}

			bb QD = pos << 8 & ~white & ~((pos & black & ~BK) << 8);



			while (QD) {

				attacked |= QD;

				QD = QD << 8 & ~white & ~((QD & black & ~BK) << 8);
			}

			bb QUR = pos >> 7 & ~fileA & ~white & ~((pos & black & ~BK) >> 7);



			while (QUR) {

				attacked |= QUR;

				QUR = QUR >> 7 & ~fileA & ~white & ~((QUR & black & ~BK) >> 7);

			}



			bb QUL = pos >> 9 & ~fileH & ~white & ~((pos & black & ~BK) >> 9);

			while (QUL) {

				attacked |= QUL;

				QUL = QUL >> 9 & ~fileH & ~white & ~((QUL & black & ~BK) >> 9);

			}



			bb QDL = pos << 7 & ~fileH & ~white & ~((pos & black & ~BK) << 7);

			while (QDL) {

				attacked |= QDL;

				QDL = QDL << 7 & ~fileH & ~white & ~((QDL & black & ~BK) << 7);

			}



			bb QDR = pos << 9 & ~fileA & ~white & ~((pos & black & ~BK) << 9);

			while (QDR) {


				attacked |= QDR;

				QDR = QDR << 9 & ~fileA & ~white & ~((QDR & black & ~BK) << 9);
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
			bb BRU = pos >> 8 & ~black & ~((pos & white & ~WK) >> 8);

			while (BRU) {

				attacked |= BRU;

				BRU = BRU >> 8 & ~black & ~((BRU & white & ~WK) >> 8);
			}

			bb BRL = pos >> 1 & ~black & ~fileH & ~((pos & white & ~WK) >> 1);

			while (BRL) {

				attacked |= BRL;

				BRL = BRL >> 1 & ~black & ~fileH & ~((BRL & white & ~WK) >> 1);
			}

			bb BRR = pos << 1 & ~black & ~fileA & ~((pos & white & ~WK) << 1);

			while (BRR) {

				attacked |= BRR;

				BRR = BRR << 1 & ~black & ~fileA & ~((BRR & white & ~WK) << 1);
			}

			bb BRD = pos << 8 & ~black & ~((pos & white & ~WK) << 8);

			while (BRD) {

				attacked |= BRD;

				BRD = BRD << 8 & ~black & ~((BRD & white & ~WK) << 8);
			}

		}
		else if (((BB >> i) & 1) == 1) {
			bb pos = pow(2, i);

			bb BBUR = pos >> 7 & ~fileA & ~black & ~((pos & white & ~WK) >> 7);

			while (BBUR) {

				attacked |= BBUR;

				BBUR = BBUR >> 7 & ~fileA & ~black & ~((BBUR & white & ~WK) >> 7);

			}

			bb BBUL = pos >> 9 & ~fileH & ~black & ~((pos & white & ~WK) >> 9);

			while (BBUL) {

				attacked |= BBUL;

				BBUL = BBUL >> 9 & ~fileH & ~black & ~((BBUL & white & ~WK) >> 9);

			}

			bb BBDL = pos << 7 & ~fileH & ~black & ~((pos & white & ~WK) << 7);

			while (BBDL) {


				attacked |= BBDL;

				BBDL = BBDL << 7 & ~fileH & ~black & ~((BBDL & white & ~WK) << 7);

			}

			bb BBDR = pos << 9 & ~fileA & ~black & ~((pos & white & ~WK) << 9);

			while (BBDR) {


				attacked |= BBDR;

				BBDR = BBDR << 9 & ~fileA & ~black & ~((BBDR & white & ~WK) << 9);

			}
		}
		else if (((BQ >> i) & 1) == 1) {
			bb pos = pow(2, i); //creates a bitboard of an individual white rook
			bb QU = pos >> 8 & ~black & ~((pos & white & ~WK) >> 8);

			while (QU) {

				attacked |= QU;

				QU = QU >> 8 & ~black & ~((QU & white & ~WK) >> 8);
			}



			bb QL = pos >> 1 & ~black & ~fileH & ~((pos & white & ~WK) >> 1);

			while (QL) {

				attacked |= QL;

				QL = QL >> 1 & ~black & ~fileH & ~((QL & white & ~WK) >> 1);
			}



			bb QR = pos << 1 & ~black & ~fileA & ~((pos & white & ~WK) << 1);

			while (QR) {

				attacked |= QR;

				QR = QR << 1 & ~black & ~fileA & ~((QR & white & ~WK) << 1);
			}

			bb QD = pos << 8 & ~black & ~((pos & white & ~WK) << 8);



			while (QD) {

				attacked |= QD;

				QD = QD << 8 & ~black & ~((QD & white & ~WK) << 8);
			}

			bb QUR = pos >> 7 & ~fileA & ~black & ~((pos & white & ~WK) >> 7);



			while (QUR) {

				attacked |= QUR;

				QUR = QUR >> 7 & ~fileA & ~black & ~((QUR & white & ~WK) >> 7);

			}



			bb QUL = pos >> 9 & ~fileH & ~black & ~((pos & white & ~WK) >> 9);

			while (QUL) {

				attacked |= QUL;

				QUL = QUL >> 9 & ~fileH & ~black & ~((QUL & white & ~WK) >> 9);

			}



			bb QDL = pos << 7 & ~fileH & ~black & ~((pos & white & ~WK) << 7);

			while (QDL) {

				attacked |= QDL;

				QDL = QDL << 7 & ~fileH & ~black & ~((QDL & white & ~WK) << 7);

			}



			bb QDR = pos << 9 & ~fileA & ~black & ~((pos & white & ~WK) << 9);

			while (QDR) {


				attacked |= QDR;

				QDR = QDR << 9 & ~fileA & ~black & ~((QDR & white & ~WK) << 9);
			}
		}
	}
	return attacked;
}

/*NOTE:
You DO NOT NEED TO NOT THE KING IN THIS METHOD. Remove later
*/

vector<bb> findPinnedPiecesWhite(moveParams, bb* checkers) {
	
	vector<bb> pinned;

	int count{};

	int i{};

	bb U = WK;
	while (U != (U | U >> 8) && count<=1) { //will quit if U is same as U ord with Ushifted up 8. 
		//this is because if they are equal, it is off the board and this prevents an inf loop
		
		if ((U >> 8 & ~U) & white) ++count; //if it hits a white piece, increase the count
		
		U |= U >> 8;
		U = ~WK & U;           //nots the king (needed as pieces check if they can block the king by anding the checker line)
		if (count == 2) break;
		if (U & (BR | BQ)) {
			if (count) pinned.push_back(U);
			else {
				checkers[i] = U;
				++i;
			}
			break;
		}
		else if (U & black & ~(BR | BQ)) break;
	}
	
	count = 0;

	bb R = WK;
	while (R != (R | R << 1) && count <= 1 && (!(R & fileA) || R == WK)) {

		if ((R << 1 & ~R) & white) ++count;

		R |= R << 1;
		R = ~WK & R;        
		if (count == 2) break;
		if (R & (BR | BQ)) {
			if (count) pinned.push_back(R);
			else {
				checkers[i] = R;
				++i;
			}
			break;
		}
		else if (R & black & ~(BR | BQ)) break;
	}

	count = 0;

	bb D = WK;
	while (D != (D | D << 8) && count <= 1) {

		if ((D << 8 & ~D) & white) ++count;

		D |= D << 8;
		D = ~WK & D;
		if (count == 2) break;
		if (D & (BR | BQ)) {
			if (count) pinned.push_back(D);
			else {
				checkers[i] = D;
				++i;
			}
			break;
		}
		else if (D & black & ~(BR | BQ)) break;
	}

	count = 0;

	bb L = WK;
	while (L != (L | L >> 1) && count <= 1 && (!(L & fileH) || L == WK)) {

		if ((L >> 1 & ~L) & white) ++count;

		L |= L >> 1;
		L = ~WK & L;
		if (count == 2) break;
		if (L & (BR | BQ)) {
			if (count) pinned.push_back(L);
			else {
				checkers[i] = L;
				++i;
			}
			break;
		}
		else if (L & black & ~(BR | BQ)) break;
	}

	count = 0;

	bb UR = WK;
	while (UR != (UR | UR >> 7) && count <= 1 && (!(UR & fileA) || UR == WK)) {

		if ((UR >> 7 & ~UR) & white) ++count;

		UR |= UR >> 7;
		UR = ~WK & UR;
		if (count == 2) break;
		if (UR & (BB | BQ)) {
			if (count) pinned.push_back(UR);
			else {
				checkers[i] = UR;
				++i;
			}
			break;
		}
		else if (UR & black & ~(BB | BQ)) break;
	}

	count = 0;

	bb DR = WK;
	while (DR != (DR | DR << 9) && count <= 1 && (!(DR & fileA) || DR == WK)) {

		if ((DR << 9 & ~DR) & white) ++count;

		DR |= DR << 9;
		DR = ~WK & DR;
		if (count == 2) break;
		if (DR & (BB | BQ)) {
			if (count) pinned.push_back(DR);
			else {
				checkers[i] = DR;
				++i;
			}
			break;
		}
		else if (DR & black & ~(BB | BQ)) break;
	}

	count = 0;

	bb DL = WK;
	while (DL != (DL | DL << 7) && count <= 1 && (!(DL & fileH) || DL == WK)) {

		if ((DL << 7 & ~DL) & white) ++count;

		DL |= DL << 7;
		DL = ~WK & DL;
		if (count == 2) break;
		if (DL & (BB | BQ)) {
			if (count) pinned.push_back(DL);
			else {
				checkers[i] = DL;
				++i;
			}
			break;
		}
		else if (DL & black & ~(BB | BQ)) break;
	}

	count = 0;

	bb UL = WK;
	while (UL != (UL | UL >> 9) && count <= 1 && (!(UL & fileH) || UL == WK)) {

		if ((UL >> 9 & ~UL) & white) ++count;

		UL |= UL >> 9;
		UL = ~WK & UL;
		if (count == 2) break;
		if (UL & (BB | BQ)) {
			if (count) pinned.push_back(UL);
			else {
				checkers[i] = UL;
				++i;
			}
			break;
		}
		else if (UL & black & ~(BB | BQ)) break;
	}

	count = 0;

	if (WK >> 9 & BP) { //checks for pawns using a simple if statement
		checkers[i] = WK >> 9;
	}

	if (i == 2) return pinned;

	if (WK >> 7 & BP) {
		checkers[i] = WK >> 7;
	}

	if (i == 2) return pinned;

	//manually checks all possible knight checks



	if (WK >> 6 & BN & ~fileA & ~fileB) checkers[i] = WK >> 6;

	if (i == 2) return pinned;

	if (WK >> 10 & BN & ~fileG & ~fileH) checkers[i] = WK >> 10;

	if (i == 2) return pinned;

	if (WK >> 15 & BN & ~fileA) checkers[i] = WK >> 15;

	if (i == 2) return pinned;

	if (WK >> 17 & BN & ~fileH) checkers[i] = WK >> 17;

	if (i == 2) return pinned;

	if (WK << 6 & BN & ~fileH & ~fileG) checkers[i] = WK << 6;

	if (i == 2) return pinned;

	if (WK << 10 & ~fileA & ~fileB & BN) checkers[i] = WK << 10;

	if (i == 2) return pinned;

	if (WK << 15 & ~fileH & BN) checkers[i] = WK << 15;

	if (i == 2) return pinned;

	if (WK << 17 & ~fileA & BN) checkers[i] = WK << 17;

	if (i == 0) checkers[0] = allSpots;

	return pinned;
}

vector<bb> findPinnedPiecesBlack(moveParams, bb* checkers) {

	vector<bb> pinned;

	int count{};

	int i{};

	bb U = BK;
	while (U != (U | U >> 8) && count <= 1) { //goes through to find a potential checker above the king

		if ((U >> 8 & ~U) & black) ++count;

		U |= U >> 8;
		U = ~BK & U;           //nots the king (needed as pieces check if they can block the king by anding the checker line)
		if (count == 2) break;
		if (U & (WR | WQ)) {
			if (count) pinned.push_back(U);
			else {
				checkers[i] = U;
				++i;
			}
			break;
		}
		else if (U & white & ~(WR | WQ)) break;
	}

	count = 0;

	bb R = BK;
	while (R != (R | R << 1) && count <= 1 && (!(R & fileA) || R == BK)) {

		if ((R << 1 & ~R) & black) ++count;

		R |= R << 1;
		R = ~BK & R;
		if (count == 2) break;
		if (R & (WR | WQ)) {
			if (count) pinned.push_back(R);
			else {
				checkers[i] = R;
				++i;
			}
			break;
		}
		else if (R & white & ~(WR | WQ)) break;
	}

	count = 0;

	bb D = BK;
	while (D != (D | D << 8) && count <= 1) {

		if ((D << 8 & ~D) & black) ++count;

		D |= D << 8;
		D = ~BK & D;
		if (count == 2) break;
		if (D & (WR | WQ)) {
			if (count) pinned.push_back(D);
			else {
				checkers[i] = D;
				++i;
			}
			break;
		}
		else if (D & white & ~(WR | WQ)) break;
	}

	count = 0;

	bb L = BK;
	while (L != (L | L >> 1) && count <= 1 && (!(L & fileH) || L == BK)) {

		if ((L >> 1 & ~L) & black) ++count;

		L |= L >> 1;
		L = ~BK & L;
		if (count == 2) break;
		if (L & (WR | WQ)) {
			if (count) pinned.push_back(L);
			else {
				checkers[i] = L;
				++i;
			}
			break;
		}
		else if (L & white & ~(WR | WQ)) break;
	}

	count = 0;

	bb UR = BK;
	while (UR != (UR | UR >> 7) && count <= 1 && (!(UR & fileA) || UR == BK)) {

		if ((UR >> 7 & ~UR) & black) ++count;

		UR |= UR >> 7;
		UR = ~BK & UR;
		if (count == 2) break;
		if (UR & (WB | WQ)) {
			if (count) pinned.push_back(UR);
			else {
				checkers[i] = UR;
				++i;
			}
			break;
		}
		else if (UR & white & ~(WB | WQ)) break;
	}

	count = 0;

	bb DR = BK;
	while (DR != (DR | DR << 9) && count <= 1 && (!(DR & fileA) || DR == BK)) {

		if ((DR << 9 & ~DR) & black) ++count;

		DR |= DR << 9;
		DR = ~BK & DR;
		if (count == 2) break;
		if (DR & (WB | WQ)) {
			if (count) pinned.push_back(DR);
			else {
				checkers[i] = DR;
				++i;
			}
			break;
		}
		else if (DR & white & ~(WB | WQ)) break;
	}

	count = 0;

	bb DL = BK;
	while (DL != (DL | DL << 7) && count <= 1 && (!(DL & fileH) || DL == BK)) {

		if ((DL << 7 & ~DL) & black) ++count;

		DL |= DL << 7;
		DL = ~BK & DL;
		if (count == 2) break;
		if (DL & (WB | WQ)) {
			if (count) pinned.push_back(DL);
			else {
				checkers[i] = DL;
				++i;
			}
			break;
		}
		else if (DL & white & ~(WB | WQ)) break;
	}

	count = 0;

	bb UL = BK;
	while (UL != (UL | UL >> 9) && count <= 1 && (!(UL & fileH) || UL == BK)) {

		if ((UL >> 9 & ~UL) & black) ++count;

		UL |= UL >> 9;
		UL = ~BK & UL;
		if (count == 2) break;
		if (UL & (WB | WQ)) {
			if (count) pinned.push_back(UL);
			else {
				checkers[i] = UL;
				++i;
			}
			break;
		}
		else if (UL & white & ~(WB | WQ)) break;
	}

	count = 0;

	if (BK << 9 & WP) { //checks for pawns using a simple if statement
		checkers[i] = BK << 9;
	}

	if (i == 2) return pinned;

	if (BK << 7 & WP) {
		checkers[i] = BK << 7;
	}

	if (i == 2) return pinned;

	//manually checks all possible knight checks



	if (BK >> 6 & WN & ~fileA & ~fileB) checkers[i] = BK >> 6;

	if (i == 2) return pinned;

	if (BK >> 10 & WN & ~fileG & ~fileH) checkers[i] = BK >> 10;

	if (i == 2) return pinned;

	if (BK >> 15 & WN & ~fileA) checkers[i] = BK >> 15;

	if (i == 2) return pinned;

	if (BK >> 17 & WN & ~fileH) checkers[i] = BK >> 17;

	if (i == 2) return pinned;

	if (BK << 6 & WN & ~fileH & ~fileG) checkers[i] = BK << 6;

	if (i == 2) return pinned;

	if (BK << 10 & ~fileA & ~fileB & WN) checkers[i] = BK << 10;

	if (i == 2) return pinned;

	if (BK << 15 & ~fileH & WN) checkers[i] = BK << 15;

	if (i == 2) return pinned;

	if (BK << 17 & ~fileA & WN) checkers[i] = BK << 17;

	if (i == 0) checkers[0] = allSpots;

	return pinned;
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
	
	constexpr bb kingPos{  0b0000000000000000000000000000000000000000000000000000000000010000 }; //2^4. pow isnt constexpr so cant use
	constexpr bb kingBis{  0b0000000000000000000000000000000000000000000000000000000000100000 }; //2^3
	constexpr bb kingKni{  0b0000000000000000000000000000000000000000000000000000000001000000 };
	constexpr bb kingRook{ 0b0000000000000000000000000000000000000000000000000000000100000000 };

	constexpr bb queenPos{ 0b0000000000000000000000000000000000000000000000000000000000001000 };
	constexpr bb queenBis{ 0b0000000000000000000000000000000000000000000000000000000000000100 };
	constexpr bb queenKni{ 0b0000000000000000000000000000000000000000000000000000000000000010 };
	constexpr bb queenRook(0b0000000000000000000000000000000000000000000000000000000000000001);

	//50 is natural king position at start of game

	if (inCheck) return;

	if (SC && (BK & kingPos && emptySquare & kingBis && emptySquare & kingKni && BR & kingRook)) {
		if (!(*attackedW & kingBis || *attackedW & kingKni)) {
			moves += " O-O ";
		}
	}

	if (LC && BK & kingPos && emptySquare & queenPos && emptySquare & queenBis
		&& emptySquare & queenKni && BR & queenRook) {
		if (!(*attackedW & queenPos || *attackedW & queenBis || *attackedW & queenKni)) {
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

	//getWLegalMoves(listOfBoardParamsAndOthers, "", 1, 1);

	executeMove("6444", "W", listOfBoardParamsAndOthers, whiteLongCastle, whiteShortCastle,
		blackLongCastle, blackShortCastle);

	auto end = high_resolution_clock::now();

	auto duration = duration_cast<nanoseconds>(end - start);

	cout << duration.count() << endl;

}