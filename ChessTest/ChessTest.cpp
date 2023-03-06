#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <vector>

#include "..\Chess\BoardRepresentation.h"
#include "..\Chess\LegalMoves.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessTest
{
	TEST_CLASS(WPawnTest)
	{
	public:
		
		TEST_METHOD(PawnTest1)
		{

			char board[8][8] = {
				//0    1    2    3    4    5    6    7
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //0
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //1
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //2
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //3
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //4
				{' ', ' ', ' ', ' ', ' ','n', ' ', ' '} , //5
				{' ', ' ', ' ', ' ', 'P', ' ', ' ', ' '}, //6
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}  //7
			}; //6454 6444 6455

			vector<string> moves { "6454", "6444", "6455" };

			arrayToBitBoard(board, listOfBitBoards);

			

			istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "")};

			string move;
		
			int num{ 0 };

			while (is >> move) {
				num++;
				bool hasMatch{ false };
				for (string m : moves) {
					if (m == move) hasMatch = true;
				}
				Assert::IsTrue(hasMatch);
			}
			Assert::AreEqual(num, (int)moves.size());
		}
		TEST_METHOD(PawnTest2) {
			char board[8][8] = {
				//0    1    2    3    4    5    6    7
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //0
				{' ', ' ', ' ', ' ', 'P', ' ', ' ', ' '}, //1
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //2
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //3
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //4
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '} , //5
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //6
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}  //7
			}; 

			vector<string> moves{ "1404Q", "1404B", "1404N", "1404R"};

			arrayToBitBoard(board, listOfBitBoards);

			istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "")};

			string move;
			int num{};
			
			while (is >> move) {
				num++;
				bool hasMatch{ false };
				for (string m : moves) {
					if (m == move) hasMatch = true;
				}
				Assert::IsTrue(hasMatch);
			}
			Assert::AreEqual(num, (int)moves.size());
		}
		TEST_METHOD(PawnTest3) {
			char board[8][8] = {
				//0    1    2    3    4    5    6    7
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //0
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //1
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //2
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //3
				{' ', ' ', ' ', 'N', 'n',' ', ' ', ' '},  //4
				{' ', ' ', ' ', 'P', ' ',' ', ' ', ' '} , //5
				{' ', 'P', ' ', ' ', ' ', ' ', ' ', ' '}, //6
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}  //7
			}; //6151 6141 5344

			vector<string> moves{ "6151", "6141", "5344" };

			arrayToBitBoard(board, listOfBitBoards);

			istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "")};

			string move;
			int num{};

			while (is >> move) {
				num++;
				bool hasMatch{ false };
				for (string m : moves) {
					if (m == move) hasMatch = true;
				}
				Assert::IsTrue(hasMatch);
			}
			Assert::AreEqual(num, (int)moves.size());
		}
		TEST_METHOD(PawnTest4) {
			char board[8][8] = {
				//0    1    2    3    4    5    6    7
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //0
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //1
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //2
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //3
				{' ', ' ', ' ', ' ', ' ',' ', ' ', ' '},  //4
				{'n', ' ', ' ', ' ', ' ',' ', ' ', 'n'} , //5
				{'P', ' ', ' ', ' ', ' ', ' ', ' ', 'P'}, //6
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}  //7
			}; //6151 6141 5344

			vector<string> moves{  };

			arrayToBitBoard(board, listOfBitBoards);

			istringstream is{ wPawnMoves(listOfBoardParamsAndOthers ,"")};

			string move{};
			int num{};

			while (is >> move) {
				num++;
				bool hasMatch{ false };
				for (string m : moves) {
					if (m == move) hasMatch = true;
				}
				Assert::IsTrue(hasMatch);
			}
			Assert::AreEqual(num, (int)moves.size());
		}
		TEST_METHOD(PawnTest5) {
			char board[8][8] = {
				//0   1   2   3   4   5   6   7
				{'q',' ',' ',' ',' ',' ',' ',' '}, //0
				{' ','q',' ','n',' ',' ',' ','P'}, //1
				{' ',' ','P',' ',' ',' ',' ',' '},  //2
				{' ',' ',' ',' ',' ',' ',' ',' '},  //3
				{' ',' ',' ',' ',' ',' ',' ',' '},  //4
				{' ',' ',' ',' ',' ',' ',' ',' '} , //5
				{' ',' ',' ',' ',' ',' ',' ',' '}, //6
				{' ',' ',' ',' ',' ',' ',' ',' '}  //7
			}; //2213 2211 2212 1707Q 1707R 1707N 1707B

			vector<string> moves{ "2213", "2211", "2212", "1707Q", "1707R", "1707N", "1707B" };

			arrayToBitBoard(board, listOfBitBoards);

			istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "")};

			string move;
			int num{};

			while (is >> move) {
				num++;
				bool hasMatch{ false };
				for (string m : moves) {
					if (m == move) hasMatch = true;
				}
				Assert::IsTrue(hasMatch);
			}
			Assert::AreEqual(num, (int)moves.size());
		}
	};
	TEST_CLASS(WEnPassant) {
		TEST_METHOD(EnPassant1) {
			char board[8][8] = {
				//0   1   2   3   4   5   6   7
				{' ',' ',' ',' ',' ',' ',' ',' '}, //0
				{' ',' ',' ',' ',' ',' ',' ',' '}, //1
				{' ',' ',' ',' ',' ',' ',' ',' '},  //2
				{' ',' ',' ','p','P',' ',' ',' '},  //3
				{' ',' ',' ',' ',' ',' ',' ',' '},  //4
				{' ',' ',' ',' ',' ',' ',' ',' '} , //5
				{' ',' ',' ',' ',' ',' ',' ',' '}, //6
				{' ',' ',' ',' ',' ',' ',' ',' '}  //7
			}; 

			vector<string> moves{ "3423", "3424"};

			arrayToBitBoard(board, listOfBitBoards);

			istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "p1333") };

			string move;
			int num{};

			while (is >> move) {
				num++;
				bool hasMatch{ false };
				for (string m : moves) {
					if (m == move) hasMatch = true;
				}
				Assert::IsTrue(hasMatch);
			}
			Assert::AreEqual(num, (int)moves.size());
		}
		TEST_METHOD(EnPassant2) {
			char board[8][8] = {
				//0   1   2   3   4   5   6   7
				{' ',' ',' ',' ',' ',' ',' ',' '}, //0
				{' ',' ',' ',' ',' ',' ',' ',' '}, //1
				{' ',' ',' ',' ',' ',' ',' ',' '},  //2
				{' ',' ','P','p','P',' ',' ',' '},  //3
				{' ',' ',' ',' ',' ',' ',' ',' '},  //4
				{' ',' ',' ',' ',' ',' ',' ',' '} , //5
				{' ',' ',' ',' ',' ',' ',' ',' '}, //6
				{' ',' ',' ',' ',' ',' ',' ',' '}  //7
			};

			vector<string> moves{ "3423", "3424", "3222", "3223"};

			arrayToBitBoard(board, listOfBitBoards);

			istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "p1333") };

			string move;
			int num{};

			while (is >> move) {
				num++;
				bool hasMatch{ false };
				for (string m : moves) {
					if (m == move) hasMatch = true;
				}
				Assert::IsTrue(hasMatch);
			}
			Assert::AreEqual(num, (int)moves.size());
		}
	};
}