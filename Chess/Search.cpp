#include <iostream>

#include "Search.h"

#include "BoardRepresentation.h"
#include "LegalMoveHelpers.h"
#include "LegalMoves.h"
#include "Evaluation.h"

using namespace std;

#define params bb WP, bb WR, bb WN, bb WB, bb WQ, bb WK, bb BP, bb BR, bb BN, bb BB, bb BQ, bb BK, bb emptySquare, bb black, bb white
#define paramsVal WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK, emptySquare, black, white

string search() {
	return "";
}

bool gameOverWhite(params, bool WSC, bool WLC, string lastMove) {
	return 1;
}

double minimax(params, string lastMove, bool WLC, bool WSC, bool BLC, bool BSC,
	int depth, bool maximizingWhite, double alpha, double beta) {

	string moves;

	if (maximizingWhite) moves = getWLegalMoves(paramsVal, lastMove, WLC, WSC);

	else moves = getBLegalMoves(paramsVal, lastMove, BLC, BSC);

	if (depth == 0) return evaluation(paramsVal);

	if (maximizingWhite && moves.size() == 0) {
		bb attack = attackedByBlack(paramsVal);
		if (attack & WK) return -300; //checkmate
		else return 0; //stalemate
	}

	else if (!maximizingWhite && moves.size() == 0) {
		bb attack = attackedByWhite(paramsVal);
		if (attack & BK) return 300;//checkmate
		else return 0; //stalemate
	}

	istringstream is{ moves };

	if (maximizingWhite) {

		double maxEval = -1000;
		string s;

		while (is >> s) {

			bb WP2 = WP; bb WN2 = WN; bb WB2 = WB; bb WK2 = WK; bb WQ2 = WQ; bb WR2 = WR;
			bb BP2 = BP; bb BN2 = BN; bb BB2 = BB; bb BK2 = BK; bb BQ2 = BQ; bb BR2 = BR;
			bb black2 = black; bb white2 = white; bb emptySquare2 = emptySquare;
			string moveLast = lastMove;
			bool WCLC = WLC; bool WCSC = WSC; bool BCLC = BLC; bool BCSC = BSC;

			double eval = minimax(WP2, WR2, WN2, WB2, WQ2, WK2, BP2, BR2, BN2, BB2, BQ2, BK2,
				emptySquare2, black2, white2, moveLast, WCLC, WCSC, BCLC, BCSC, depth - 1, false
			, alpha, beta);

			maxEval = max(eval, maxEval);
			alpha = max(alpha, eval);
			if (beta <= alpha) break;
		}

		return maxEval;

	}
	else {

		double minEval = 1000;
		string s;

		while (is >> s) {
			bb WP2 = WP; bb WN2 = WN; bb WB2 = WB; bb WK2 = WK; bb WQ2 = WQ; bb WR2 = WR;
			bb BP2 = BP; bb BN2 = BN; bb BB2 = BB; bb BK2 = BK; bb BQ2 = BQ; bb BR2 = BR;
			bb black2 = black; bb white2 = white; bb emptySquare2 = emptySquare;
			string moveLast = lastMove;
			bool WCLC = WLC; bool WCSC = WSC; bool BCLC = BLC; bool BCSC = BSC;
			double eval = minimax(WP2, WR2, WN2, WB2, WQ2, WK2, BP2, BR2, BN2, BB2, BQ2, BK2,
				emptySquare2, black2, white2, moveLast, WCLC, WCSC, BCLC, BCSC, depth - 1, false,
				alpha, beta);
			minEval = min(eval, minEval);
			beta = min(beta, eval);
			if (beta <= alpha) break;
		}
		
		return minEval;

	}
}