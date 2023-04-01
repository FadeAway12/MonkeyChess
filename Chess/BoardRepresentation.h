#pragma once

#include <bitset>
#include <iostream>
#include <vector>
#include <sstream>

#define bb std::uint64_t

#define cbb const std::bitset<64>

#define listOfBitBoards WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK

#define listOfBoardParamsAndOthers WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK, emptySquare, black, white

#define listOfMoveParams bb WP, bb WR, bb WN, bb WB, bb WQ, bb WK, bb BP, bb BR, bb BN, bb BB, bb BQ, bb BK

#define listOfMoveParamsRef bb& WP, bb& WR, bb& WN, bb& WB, bb& WQ, bb& WK, bb& BP, bb& BR, bb& BN, bb& BB, bb& BQ, bb& BK

#define constListOfBoardParams const bb& WP, const bb& WR, const bb& WN, const bb& WB, const bb& WQ, const bb& WK, const bb& BP, const bb& BR, const bb& BN, const bb& BB, const bb& BQ, const bb& BK

#define constListOfBoardParamsAndOthers const bb& WP, const bb& WR, const bb& WN, const bb& WB, const bb& WQ, const bb& WK, const bb& BP, const bb& BR, const bb& BN, const bb& BB, const bb& BQ, const bb& BK, bb& emptySquare, bb& black, bb& white

#ifndef RepetitionVecThingy222
#define RepetitionVecThingy222

struct Repetition { //MAKE SURE TO ADD COPY ASSIGNMENT/CONSTRUCTION LATER FOR BEING PASSED THROUGH MINIMAX
	std::string moves;
	int num;
	Repetition(std::string m, int n) : moves(m), num(n) { }
};

struct RepetitionVector { //MAKE SURE TO ADD COPY ASSIGNMENT/CONSTRUCTION LATER FOR BEING PASSED THROUGH MINIMAX

	std::vector<Repetition> repetitions;

	int lastModified{};

	RepetitionVector() {
		
	}

	RepetitionVector(RepetitionVector& v) {
		repetitions = v.repetitions;
	}

	RepetitionVector& operator=(RepetitionVector v) {
		RepetitionVector v2;
		v2.repetitions = v.repetitions;
		return v2;
	}

	bool update(std::string moves) { //returns true if threefold draw repitition is met
		
		lastModified = -1;
		bool found{};
		for (int i = 0; i < repetitions.size(); i++) {
			if (repetitions[i].moves == moves) {
				lastModified = i;
				repetitions[i].num++;
				found = true;
			}
			
			if (repetitions[i].num >= 3) return true;
		}
		if (!found) {
			repetitions.push_back(Repetition(moves, 1));
		}
		return false;
	}

	void undo() {
		if (lastModified == -1) {
			repetitions.pop_back();
		}
		else {
			repetitions[lastModified].num--;
		}
	}

	int maxRep() {
		int max = 0;
		for (int i = 0; i < repetitions.size(); i++) {
			if (repetitions[i].num>max) {
				max = repetitions[i].num;
			}
		}
		return max;
	}

};



#endif

extern bool whiteTurn;

extern bool whiteShortCastle;
extern bool whiteLongCastle;
extern bool blackShortCastle;
extern bool blackLongCastle;

extern int numsTilDraw; //if over 50, game is a draw. increment if executeMove returns true
extern int moveNum;

extern RepetitionVector vWhite;
extern RepetitionVector vBlack;

extern bb positions[64];

extern bb WP;
extern bb WR;
extern bb WN;
extern bb WB;
extern bb WQ;
extern bb WK;

extern bb BP;
extern bb BR;
extern bb BN;
extern bb BB;
extern bb BQ;
extern bb BK;

extern bb black;
extern bb white;
extern bb emptySquare;

extern bb fileA;
extern bb fileB;
extern bb fileC;
extern bb fileD;
extern bb fileE;
extern bb fileF;
extern bb fileG;
extern bb fileH;

extern bb rank8;
extern bb rank7;
extern bb rank6;
extern bb rank5;
extern bb rank4;
extern bb rank3;
extern bb rank2;
extern bb rank1;

extern char board[8][8];

extern std::string lastMove;

extern void arrayToBitBoard(char board[8][8], bb& WP, bb& WR, bb& WN, bb& WB, bb& WQ, bb& WK, bb& BP, bb& BR, bb& BN, bb& BB, bb& BQ, bb& BK);

extern void importFEN(std::string s);

extern void arrayToBitBoard();

extern void bitboardToArray(char board[8][8], cbb WP, cbb WR, cbb WN, cbb WB, cbb WQ, cbb WK, cbb BP, cbb BR, cbb BN, cbb BB, cbb BQ, cbb BK);

extern void bitboardToArray();

extern void setOtherBBs(constListOfBoardParamsAndOthers);

extern void printBoard();

extern void printBoardRaw();

extern std::string rawToString(std::string s, char board[8][8]);
