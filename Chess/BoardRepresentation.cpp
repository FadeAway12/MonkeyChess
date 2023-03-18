#include <iostream>
#include <vector>
#include <stdlib.h>

#include "BoardRepresentation.h"
#include "LegalMoves.h"
#include "LegalMoveHelpers.h"
#include "MoveExecution.h"

using namespace std;

/*

//DEFINES:

bb - bitboard (std::bitset<64>)

cbb - const bitboard (const std::bitset<64>)

listOfBitBoards - WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK

listOfBoardParamsAndOthers - WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK, emptySquare, black, white

listOfMoveParams - bb WP, bb WR, bb WN, bb WB, bb WQ, bb WK, bb BP, bb BR, bb BN, bb BB, bb BQ, bb BK

listOfMoveParamsRef - bb& WP, bb& WR, bb& WN, bb& WB, bb& WQ, bb& WK, bb& BP, bb& BR, bb& BN, bb& BB, bb& BQ, bb& BK

constListOfBoardParams - const bb& WP, const bb& WR, const bb& WN, const bb& WB, const bb& WQ, const bb& WK, const bb& BP, const bb& BR, const bb& BN, const bb& BB, const bb& BQ, const bb& BK

constListOfBoardParamsAndOthers const bb& WP, const bb& WR, const bb& WN, const bb& WB, const bb& WQ, const bb& WK, const bb& BP, const bb& BR, const bb& BN, const bb& BB, const bb& BQ, const bb& BK, bb& emptySquare, bb& black, bb& white

*/



bool whiteShortCastle{ true }; //checks if white king or kingside rook has moved
bool whiteLongCastle{ true }; //checks if white king or queenside rook has moved
bool blackShortCastle{ true }; //checks if black king or kingside rook move
bool blackLongCastle{ true }; //checks if black king or queenside rook moved

//making bitboards for each piece that'll represent the current state of the board

int numsTilDraw;

bb WP;
bb WR;
bb WN;
bb WB;
bb WQ;
bb WK;

bb BP;
bb BR;
bb BN;
bb BB;
bb BQ;
bb BK;

//self-explanatory. used for convenience in legal move generation

bb black;
bb white;
bb emptySquare;

//used in legal move generation

bb fileA{ 0b00000001'00000001'00000001'00000001'00000001'00000001'00000001'00000001 };
bb fileB{ fileA << 1 };
bb fileC{ fileB << 1 };
bb fileD{ fileC << 1 };
bb fileE{ fileD << 1 };
bb fileF{ fileE << 1 };
bb fileG{ fileF << 1 };
bb fileH{ fileG << 1 };

bb rank8{ 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'11111111 };
bb rank7{ rank8 << 8 };
bb rank6{ rank7 << 8 };
bb rank5{ rank6 << 8 };
bb rank4{ rank5 << 8 };
bb rank3{ rank4 << 8 };
bb rank2{ rank3 << 8 };
bb rank1{ rank2 << 8 };

bb* positions = new bb[64];

void meth() {
	positions[0] = 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000001;
	bb* x = &positions[0];
	for (int i = 0; i < 64; i++) {
		bb k = *x;
		k << i;
		++x;
	}
}

//Real board

/*
char board[8][8] = { //used for convenient viewing of the board's representation
	//0    1    2    3    4    5    6    7
	{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, //0
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, //1
	{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //2
	{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //3
	{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //4
	{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '} , //5
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, //6
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}  //7
	
};*/


//Test board


char board[8][8] = {
	//0   1   2   3   4   5   6   7
	{' ',' ',' ',' ',' ',' ',' ',' '}, //0
	{' ',' ',' ',' ',' ',' ',' ',' '}, //1
	{' ',' ',' ',' ',' ',' ',' ',' '},  //2
	{' ',' ',' ',' ',' ',' ',' ',' '},  //3
	{' ',' ',' ',' ',' ',' ',' ',' '},  //4
	{' ','K',' ',' ',' ',' ',' ',' '} , //5
	{' ',' ',' ',' ','R',' ',' ',' '}, //6
	{' ','k',' ',' ',' ',' ',' ',' '}  //7
};



void arrayToBitBoard(char board[8][8], bb& WP, bb& WR, bb& WN, bb& WB, bb& WQ, bb& WK, bb& BP, bb& BR, bb& BN, bb& BB, bb& BQ, bb& BK) {
	
	bb mask{ 0b1 };

	BP = 0; BR = 0; BN = 0; BB = 0; BQ = 0; BK = 0; WP = 0; WR = 0; WN = 0; WB = 0; WQ = 0; WK = 0;

	for (int i = 0; i < 64; i++) {

		switch (board[i/8][i-(i/8)*8]) {

		case 'p': BP |= mask; break;
		case 'r': BR |= mask; break;
		case 'n': BN |= mask; break;
		case 'b': BB |= mask; break;
		case 'q': BQ |= mask; break;
		case 'k': BK |= mask; break;

		case 'P': WP |= mask; break;
		case 'R': WR |= mask; break;
		case 'N': WN |= mask; break;
		case 'B': WB |= mask; break;
		case 'Q': WQ |= mask; break;
		case 'K': WK |= mask; break;

		}

		mask *= 0b10; //multiplying by two in binary will move the bit left one space.

	}

	setOtherBBs(listOfBoardParamsAndOthers); //sets the black, white and empty bitboards

}

void arrayToBitBoard() {

	arrayToBitBoard(board, WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK);

}

void bitboardToArray(char board[8][8], cbb WP, cbb WR, cbb WN, cbb WB, cbb WQ, cbb WK, cbb BP, cbb BR, cbb BN, cbb BB, cbb BQ, cbb BK) {

	for (int i = 0; i < 64; i++) { //goes through each bitboard and sees if it has a piece in a position
		
		char& c = board[i / 8][i - (i / 8) * 8];

		if (WP.test(i)) { c = 'P'; continue; }
		else if (WK.test(i)) { c = 'K'; continue; }
		else if (WN.test(i)) { c = 'N'; continue; }
		else if (WQ.test(i)) { c = 'Q'; continue; }
		else if (WR.test(i)) { c = 'R'; continue; }
		else if (WB.test(i)) { c = 'B'; continue; }

		else if (BP.test(i)) { c = 'p'; continue; }
		else if (BK.test(i)) { c = 'k'; continue; }
		else if (BN.test(i)) { c = 'n'; continue; }
		else if (BQ.test(i)) { c = 'q'; continue; }
		else if (BR.test(i)) { c = 'r'; continue; }
		else if (BB.test(i)) { c = 'b'; continue; }
		else c = ' ';

	}

}

void bitboardToArray() {

	bitboardToArray(board, WP, WR, WN, WB, WQ, WK, BP, BR, BN, BB, BQ, BK);

}


void printBoard() {
	cout << "  A B C D E F G H" << endl;
	for (int i = 0; i < 8; i++) {
		cout << 8-i;
		cout << " ";
		for (int j = 0; j < 8; j++) {
			std::cout <<board[i][j] << " ";
		}
		std::cout << endl;
	}
}


void printBoardRaw() {
	cout << "  0 1 2 3 4 5 6 7" << endl;
	for (int i = 0; i < 8; i++) {
		cout << i;
		cout << " ";
		for (int j = 0; j < 8; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << endl;
	}
}

void setOtherBBs(constListOfBoardParamsAndOthers) { //sets empty, black and white based off bitboards
	emptySquare = ~(WP | WR | WN | WB | WQ | WK | BP | BR | BN | BB | BQ | BK);
	black = BP | BR | BN | BB | BQ | BK;
	white = WP | WR | WN | WB | WQ | WK;
}

string rawToString(string s, char board[8][8]) { //converts raw notation (like 2346) to normal notation
	
	istringstream is{ s };

	string alph2{ "abcdefgh" };

	string final{};

	while (is) {
		
		string move;
		is >> move;
		
		if (move == "O-O" || move == "O-O-O") { final += " " + move; continue; }

		if (move.size() < 4) continue;
		
		int rowF = move[0];
		char colF = move[1];
		
		int rowT = 8-(move[2]-'0');
		char colT = move[3];

		char piece = board[rowF-'0'][colF-'0'];

		if (piece == 'P' or piece == 'p') final = final + alph2[(int)colT - '0'] + to_string(rowT) + " ";
		else final = final + piece + alph2[colT - '0'] + to_string(rowT) + " ";
		 
		
	}
	return final;

}
