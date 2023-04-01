#pragma once

#include <iostream>

#define moveParams bb& WP, bb& WR, bb& WN, bb& WB, bb& WQ, bb& WK, bb& BP, bb& BR, bb& BN, bb& BB, bb& BQ, bb& BK, bb& emptySquare, bb& black, bb& white

#define bb std::uint64_t

extern bool executeMove(const std::string& move, const std::string& turn, moveParams, bool& WLC, bool& WSC, bool &BLC,
	bool& BSC); //returns true if move is capture

extern void executeMove(const std::string& move, bool whiteTurn);

extern bool isLegal(moveParams, const std::string& move, std::string& lastMove, const std::string& turn, bool SCW, bool LCW, bool SCB, bool LCB);