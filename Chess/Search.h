#pragma once
#define bb std::uint64_t
#define params bb WP, bb WR, bb WN, bb WB, bb WQ, bb WK, bb BP, bb BR, bb BN, bb BB, bb BQ, bb BK, bb emptySquare, bb black, bb white
#define paramsVal WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK, emptySquare, black, white

double minimax(params, std::string lastMove, bool WLC, bool WSC, bool BLC, bool BSC,
	int depth, bool maximizingWhite, double alpha, double beta);