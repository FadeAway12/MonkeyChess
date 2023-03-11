#include <vector>

#pragma once

#define moveParams bb& WP, bb& WR, bb& WN, bb& WB, bb& WQ, bb& WK, bb& BP, bb& BR, bb& BN, bb& BB, bb& BQ, bb& BK, bb& emptySquare, bb& black, bb& white

extern std::string pawnPromo(std::string s);

extern std::string pawnPromoB(std::string s);

extern bb attackedByWhite(moveParams);

extern bb attackedByBlack(moveParams);

extern void addCastlingMovesWhite(moveParams, bb* attackedB, std::string& moves, bool SC, bool LC, bool inCheck);

extern void addCastlingMovesBlack(moveParams, bb* attackedW, std::string& moves, bool SC, bool LC, bool inCheck);

extern std::vector<bb> findPinnedPiecesWhite(moveParams, bb* checkers);

extern std::vector<bb> findPinnedPiecesBlack(moveParams, bb* checkers);

extern void functionTime();