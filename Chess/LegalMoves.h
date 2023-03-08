#pragma once

#include "BoardRepresentation.h"

#define moveParams bb& WP, bb& WR, bb& WN, bb& WB, bb& WQ, bb& WK, bb& BP, bb& BR, bb& BN, bb& BB, bb& BQ, bb& BK, bb& emptySquare, bb& black, bb& white

extern std::string getWLegalMoves(moveParams, std::string lastMove, bool canLC, bool canSC);

extern std::string getBLegalMoves(moveParams, std::string lastMove, bool canLC, bool canSC);

extern std::string pawnPromo(std::string s);

extern std::string wPawnMoves(moveParams, std::string lastMove);

extern std::string wKnightMoves(moveParams);

extern std::string wKingMoves(moveParams);

extern std::string wRookMoves(moveParams);

extern std::string wBishopMoves(moveParams);

extern std::string wQueenMoves(moveParams);

extern std::string bPawnMoves(moveParams, std::string lastMove);

extern std::string bKnightMoves(moveParams);

extern std::string bKingMoves(moveParams);

extern std::string bRookMoves(moveParams);

extern std::string bBishopMoves(moveParams);

extern std::string bQueenMoves(moveParams);