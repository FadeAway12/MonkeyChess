#include <iostream>

#include "Search.h"

#include "BoardRepresentation.h"
#include "LegalMoveHelpers.h"
#include "LegalMoves.h"
#include "Evaluation.h"
#include "MoveExecution.h"
#include "TranspositionTables.h"

using namespace std;

#define params bb WP, bb WR, bb WN, bb WB, bb WQ, bb WK, bb BP, bb BR, bb BN, bb BB, bb BQ, bb BK, bb emptySquare, bb black, bb white
#define paramsVal WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK, emptySquare, black, white

namespace Search {
	int evalScore{};
	int startingDepth;
}

string bestMove{};

string search() {
	return "";
}

struct Move {
	string move;
	int eval;
};

vector<Move> moveList;

string getWhiteMove(params, string lastMove, bool WLC, bool WSC, bool BLC, bool BSC,
	int depth) {
	
	int hash = positionValue(WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK, lastMove, whiteTurn, whiteShortCastle, whiteLongCastle, blackShortCastle, blackLongCastle);
	
	if (hasHash(hash) && getHashInfo(hash).depth >= depth) return getHashInfo(hash).bestMove;

	Search::startingDepth = depth;
	bestMove = "";
	Search::evalScore = minimax(paramsVal, lastMove, WLC, WSC, BLC, BSC, depth, true, true, -3000, +3000);
	
	moveInfo mi = getHashInfo(hash);
	return mi.bestMove;
}

string getBlackMove(params, string lastMove, bool WLC, bool WSC, bool BLC, bool BSC,
	int depth) {

	int hash = positionValue(WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK, lastMove, whiteTurn, whiteShortCastle, whiteLongCastle, blackShortCastle, blackLongCastle);

	if (hasHash(hash) && getHashInfo(hash).depth>=depth) return getHashInfo(hash).bestMove;

	Search::startingDepth = depth;
	bestMove = "";
	Search::evalScore = minimax(paramsVal, lastMove, WLC, WSC, BLC, BSC, depth, true, false, -3000, +3000);
	
	moveInfo mi = getHashInfo(hash);
	return mi.bestMove;
}

bool gameOverWhite(params, bool WSC, bool WLC, string lastMove) {
	return 1;
}

double minimax(params, string lastMove, bool WLC, bool WSC, bool BLC, bool BSC,
	int depth, bool firstCall, bool maximizingWhite, double alpha, double beta) {

	int hash = positionValue(WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK, lastMove, whiteTurn, WSC, WLC, BSC, BLC);
	
	if (hasHash(hash)) {
		
		moveInfo mi = getHashInfo(hash);
		if (mi.depth >= depth) {
			if (mi.type == 0) return mi.value;
			if (mi.type == 1) beta = mi.value;
			if (mi.type == 2) alpha = mi.value;
		}
	}

	string moves;

	if (maximizingWhite) moves = getWLegalMoves(paramsVal, lastMove, WLC, WSC);

	else moves = getBLegalMoves(paramsVal, lastMove, BLC, BSC);

	if (depth == 0) {
		return evaluation(paramsVal);
	}

	istringstream is{ moves };

	if (0 == moves.length()) {

		if (maximizingWhite) {
			bb attack = attackedByBlack(paramsVal);
			if (attack & WK) return -300 - depth; //checkmate
			else return 0; //stalemate
		}

		else if (!maximizingWhite) {
			bb attack = attackedByWhite(paramsVal);
			if (attack & BK) return 300 + depth;//checkmate
			else return 0; //stalemate
		}

	}

	string moveTop;

	if (maximizingWhite) {

		double maxEval = -1000;
		string s;

		while (is >> s) {

			bb WP2 = WP; bb WN2 = WN; bb WB2 = WB; bb WK2 = WK; bb WQ2 = WQ; bb WR2 = WR;
			bb BP2 = BP; bb BN2 = BN; bb BB2 = BB; bb BK2 = BK; bb BQ2 = BQ; bb BR2 = BR;
			bb black2 = black; bb white2 = white; bb emptySquare2 = emptySquare;

			bool WCLC = WLC; bool WCSC = WSC; bool BCLC = BLC; bool BCSC = BSC;

			executeMove(s, "W", WP2, WR2, WN2, WB2, WQ2, WK2, BP2, BR2, BN2, BB2, BQ2, BK2,
				emptySquare2, black2, white2, WCLC, WCSC, BCLC, BCSC);

			double eval = minimax(WP2, WR2, WN2, WB2, WQ2, WK2, BP2, BR2, BN2, BB2, BQ2, BK2,
				emptySquare2, black2, white2, s, WCLC, WCSC, BCLC, BCSC, depth - 1, false, false
				, alpha, beta);

			
			//if ((firstCall && eval > maxEval) || (firstCall && bestMove == "")) bestMove = s;

			if (eval > maxEval) {
				maxEval = eval;
				moveTop = s;
				
			}

			alpha = max(alpha, eval);
			if (beta <= alpha) break;
		}

		if (firstCall) addEval(hash, 0, depth, maxEval, moveTop);

		return maxEval;

	}
	else {

		double minEval = 1000;
		string s;

		while (is >> s) {

			bb WP2 = WP; bb WN2 = WN; bb WB2 = WB; bb WK2 = WK; bb WQ2 = WQ; bb WR2 = WR;
			bb BP2 = BP; bb BN2 = BN; bb BB2 = BB; bb BK2 = BK; bb BQ2 = BQ; bb BR2 = BR;
			bb black2 = black; bb white2 = white; bb emptySquare2 = emptySquare;

			bool WCLC = WLC; bool WCSC = WSC; bool BCLC = BLC; bool BCSC = BSC;

			executeMove(s, "B", WP2, WR2, WN2, WB2, WQ2, WK2, BP2, BR2, BN2, BB2, BQ2, BK2,
				emptySquare2, black2, white2, WCLC, WCSC, BCLC, BCSC);

			double eval = minimax(WP2, WR2, WN2, WB2, WQ2, WK2, BP2, BR2, BN2, BB2, BQ2, BK2,
				emptySquare2, black2, white2, s, WCLC, WCSC, BCLC, BCSC, depth - 1, false, true,
				alpha, beta);

			//if ((firstCall && eval < minEval) || (firstCall && bestMove == "")) bestMove = s;

			if (eval < minEval) {
				minEval = eval;
				moveTop = s;
				
			}

			beta = min(beta, eval);
			if (beta <= alpha) break;

		}

		if (firstCall) addEval(hash, 0, depth, minEval, moveTop);

		return minEval;

	}
}