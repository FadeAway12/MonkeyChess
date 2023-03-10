#include <vector>

#pragma once

#define moveParams bb& WP, bb& WR, bb& WN, bb& WB, bb& WQ, bb& WK, bb& BP, bb& BR, bb& BN, bb& BB, bb& BQ, bb& BK, bb& emptySquare, bb& black, bb& white

extern std::string pawnPromo(std::string s);

extern std::string pawnPromoB(std::string s);

extern bb attackedByWhite(moveParams);

extern bb attackedByBlack(moveParams);

extern void addCastlingMovesWhite(moveParams, bb* attackedB, std::string& moves, bool SC, bool LC, bool inCheck);

extern void addCastlingMovesBlack(moveParams, bb* attackedW, std::string& moves, bool SC, bool LC, bool inCheck);

extern bb* findCheckerWhite(moveParams);

extern std::vector<bb> findPinnedPiecesWhite(moveParams);

extern void functionTime();