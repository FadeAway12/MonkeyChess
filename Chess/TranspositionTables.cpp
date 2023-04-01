#include <iostream>
#include <random>
#include <map>
#include <unordered_map>

#include "TranspositionTables.h"
#include "BoardRepresentation.h"

using namespace std;

#define bb std::uint64_t

/** 

0-7 - A8-H8
8-15 - A7-H7
and so on

0-63 WP

64-127 WN

128-191 WB

192-255 WR

256-319 WQ

320-383 WK

384-447 BP

448-511 BB

512-575 BN

576-639 BR

640-703 BQ

704-767 BK

768 - white to move

769 - white short castle

770 - white long castle

771 - black short castle

772 - black long castle

773 - en passant A

774 - en passant B

775 - en passant C

776 - en passant D

777 - en passant E

778 - en passant F

779 - en passant G

780 - en passant H

*/

uint64_t nums[781];

unordered_map<int, moveInfo> transposTable; //first integer is hash of position, second is eval

void initialize() {

	for (int i = 0; i < 64; i++) {
		positions[i] = pow(2, i);
	}
	
	srand((unsigned) time(NULL));
	for (int i = 0; i < 781; i++) {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(1, 18446744073709551615);
		nums[i] = dist(rng);
	}
}

/*
returns hash of position
*/
int positionValue(const bb& WP, const bb& WR, const bb& WN, const bb& WB, const bb& WQ, const bb& WK, const bb& BP, const bb& BR, const bb& BN, const bb& BB, const bb& BQ, const bb& BK,
	const string& lastMove, const bool& whiteTurn, const bool& WSC, const bool& WLC, const bool& BSC, const bool& BLC) {
	
	int value{ 0 };
	
	//positions
	for (int i = 0; i < 64; ++i) {
		if (((WP >> i) & 1) == 1) value ^= nums[i];
		else if (((BP >> i) & 1) == 1) value ^= nums[i + 64 * 6];
		else if (((WN >> i) & 1) == 1) value ^= nums[i + 64 * 1];
		else if (((BN >> i) & 1) == 1) value ^= nums[i + 64 * 8];
		else if (((WB >> i) & 1) == 1) value ^= nums[i + 64 * 2];
		else if (((BB >> i) & 1) == 1) value ^= nums[i + 64 * 7];
		else if (((WR >> i) & 1) == 1) value ^= nums[i + 64 * 3];
		else if (((BR >> i) & 1) == 1) value ^= nums[i + 64 * 9];
		else if (((WQ >> i) & 1) == 1) value ^= nums[i + 64 * 4];
		else if (((BQ >> i) & 1) == 1) value ^= nums[i + 64 * 10];
		else if (((WK >> i) & 1) == 1) value ^= nums[i + 64 * 5]; 
		else if (((BK >> i) & 1) == 1) value ^= nums[i + 64 * 11];
	}

	//white to move
	if (whiteTurn) value ^= nums[768];

	//castling
	if (WSC) value ^= nums[769];
	if (WLC) value ^= nums[770];
	if (BSC) value ^= nums[771];
	if (BLC) value ^= nums[772];

	//en passant
	if (lastMove[0] == 'P' || lastMove[0] == 'p') {
		if (lastMove[0] == 'P' && lastMove[1] - '0' == (lastMove[3] - '0') - 2) value ^= nums[773 + (lastMove[2] - '0')];
		else if (lastMove[0] == 'p' && lastMove[1]-'0' == (lastMove[3]-'0')+2) value ^= nums[773 + (lastMove[2] - '0')];
	}

	return value;
}

void addEval(int hash, int type, int depth, int val) {

	transposTable[hash] = moveInfo(type, depth, val);

}

void addEval(int hash, int type, int depth, int val, string s) {

	transposTable[hash] = moveInfo(type, depth, val, s);

}

moveInfo getHashInfo(int hash) {

	return transposTable.at(hash);

}


bool hasHash (int hash) {

	if (transposTable.count(hash) != 0) return true;

	return false;

}
