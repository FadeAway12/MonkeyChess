#pragma once

#define moveParams bb& WP, bb& WR, bb& WN, bb& WB, bb& WQ, bb& WK, bb& BP, bb& BR, bb& BN, bb& BB, bb& BQ, bb& BK, bb& emptySquare, bb& black, bb& white

std::string pawnPromo(std::string s);

std::string pawnPromoB(std::string s);

bb attackedByWhite(moveParams);

bb attackedByBlack(moveParams);

void addCastlingMovesWhite(moveParams, bb* attackedB, std::string& moves, bool SC, bool LC, bool inCheck);

void addCastlingMovesBlack(moveParams, bb* attackedW, std::string& moves, bool SC, bool LC, bool inCheck);

void functionTime();