#pragma once
#define bb std::uint64_t
#define params bb WP, bb WR, bb WN, bb WB, bb WQ, bb WK, bb BP, bb BR, bb BN, bb BB, bb BQ, bb BK, bb emptySquare, bb black, bb white
#define paramsVal WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK, emptySquare, black, white

extern std::string bestMove;

namespace Search {

	extern int evalScore;

}

double minimax(params, std::string lastMove, bool WLC, bool WSC, bool BLC, bool BSC,
	int depth, int dMax, bool maximizingWhite, double alpha, double beta);

std::string getWhiteMove(params, std::string lastMove, bool WLC, bool WSC, bool BLC, bool BSC,
	int depth);

std::string getBlackMove(params, std::string lastMove, bool WLC, bool WSC, bool BLC, bool BSC,
	int depth);