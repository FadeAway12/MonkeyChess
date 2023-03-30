#pragma once

#include <iostream>

using namespace std;

struct moveInfo {
	int type; //0 - exact eval, 1 - upper bound, 2 - lower bound, 3 - best move
	int depth;
	int value;
	string bestMove;
	moveInfo(int t, int d, int v) : type(t), depth(d), value(v) { }
	moveInfo(int t, int d, int v, string s) : type(t), depth(d), value(v), bestMove(s) { }
	moveInfo() { }
};

#define bb std::uint64_t

extern uint64_t nums[];

extern void initialize();

extern int positionValue(const bb& WP, const bb& WR, const bb& WN, const bb& WB, const bb& WQ, const bb& WK, const bb& BP, const bb& BR, const bb& BN, const bb& BB, const bb& BQ, const bb& BK,
	const std::string& lastMove, const bool& whiteTurn, const bool& WSC, const bool& WLC, const bool& BSC, const bool& BLC);

void addEval(int hash, int type, int depth, int val);

extern bool hasHash(int hash);

extern moveInfo getHashInfo(int hash);

extern void addEval(int hash, int type, int depth, int val, string s);