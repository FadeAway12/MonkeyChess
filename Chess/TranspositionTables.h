#pragma once

extern int nums[];

extern void initialize();

extern int positionValue(const bb& WP, const bb& WR, const bb& WN, const bb& WB, const bb& WQ, const bb& WK, const bb& BP, const bb& BR, const bb& BN, const bb& BB, const bb& BQ, const bb& BK,
	const std::string& lastMove, const bool& whiteTurn, const bool& WSC, const bool& WLC, const bool& BSC, const bool& BLC);

extern void addEval(const bb& WP, const bb& WR, const bb& WN, const bb& WB, const bb& WQ, const bb& WK, const bb& BP, const bb& BR, const bb& BN, const bb& BB, const bb& BQ, const bb& BK,
	const std::string& lastMove, const bool& whiteTurn, const bool& WSC, const bool& WLC, const bool& BSC, const bool& BLC, int eval);

extern int getHashEval(const bb& WP, const bb& WR, const bb& WN, const bb& WB, const bb& WQ, const bb& WK, const bb& BP, const bb& BR, const bb& BN, const bb& BB, const bb& BQ, const bb& BK,
	const std::string& lastMove, const bool& whiteTurn, const bool& WSC, const bool& WLC, const bool& BSC, const bool& BLC);

bool hasHash(const bb& WP, const bb& WR, const bb& WN, const bb& WB, const bb& WQ, const bb& WK, const bb& BP, const bb& BR, const bb& BN, const bb& BB, const bb& BQ, const bb& BK,
	const std::string& lastMove, const bool& whiteTurn, const bool& WSC, const bool& WLC, const bool& BSC, const bool& BLC);