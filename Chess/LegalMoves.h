#pragma once

#include "BoardRepresentation.h"
#include <vector>

#define moveParams bb& WP, bb& WR, bb& WN, bb& WB, bb& WQ, bb& WK, bb& BP, bb& BR, bb& BN, bb& BB, bb& BQ, bb& BK, bb& emptySquare, bb& black, bb& white

extern std::string getWLegalMoves(moveParams, std::string lastMove, bool canLC, bool canSC);

extern std::string getBLegalMoves(moveParams, std::string lastMove, bool canLC, bool canSC);

extern std::string pawnPromo(std::string s);

extern std::string wPawnMoves(moveParams, std::string lastMove, bb* checkers, std::vector<bb> pinned);

extern std::string wKnightMoves(moveParams, bb* checkers, std::vector<bb> pinned);

extern std::string wKingMoves(moveParams, bb* unsafe, bb* checkers, std::vector<bb> pinned);

extern std::string wRookMoves(moveParams, bb* checkers, std::vector<bb> pinned);

extern std::string wBishopMoves(moveParams, bb* checkers, std::vector<bb> pinned);

extern std::string wQueenMoves(moveParams, bb* checkers, std::vector<bb> pinned);

extern std::string bPawnMoves(moveParams, std::string lastMove, bb* checkers, std::vector<bb> pinned);

extern std::string bKnightMoves(moveParams, bb* checkers, std::vector<bb> pinned);

extern std::string bKingMoves(moveParams, bb*, bb* checkers, std::vector<bb> pinned);

extern std::string bRookMoves(moveParams, bb* checkers, std::vector<bb> pinned);

extern std::string bBishopMoves(moveParams, bb* checkers, std::vector<bb> pinned);

extern std::string bQueenMoves(moveParams, bb* checkers, std::vector<bb> pinned);