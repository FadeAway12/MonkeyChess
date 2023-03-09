#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <vector>

#include "..\Chess\BoardRepresentation.h"
#include "..\Chess\LegalMoves.h"
#include "..\Chess\LegalMoveHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ChessTest
{
	namespace whiteMovement {
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

				vector<string> moves{ "6454", "6444", "6455" };

				arrayToBitBoard(board, listOfBitBoards);



				istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "") };

				string move;

				int num{ 0 };

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
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

				vector<string> moves{ "1404Q", "1404B", "1404N", "1404R" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "") };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
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

				istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "") };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
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

				istringstream is{ wPawnMoves(listOfBoardParamsAndOthers ,"") };

				string move{};
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
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

				istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "") };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
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

				vector<string> moves{ "3423", "3424" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "p1333") };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
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

				vector<string> moves{ "3423", "3424", "3222", "3223" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "p1333") };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(EnPassant3) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ','p',' ','P',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3424" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "p1232") };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(EnPassant4) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ','p','P','p',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3424", "3423" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wPawnMoves(listOfBoardParamsAndOthers, "p1333") };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
		};
		TEST_CLASS(WKnightTest) {
			TEST_METHOD(Knight1) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ','N',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3426", "3415", "3446", "3455", "3453", "3442", "3422", "3413" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wKnightMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(Knight2) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ','B','B','n',' ',' '},  //2
					{' ',' ',' ','B','N','r',' ',' '},  //3
					{' ',' ',' ','B','n','n',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3426", "3415", "3446", "3455", "3453", "3442", "3422", "3413" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wKnightMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(Knight3) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ','N'}, //0
					{' ',' ',' ',' ',' ','b',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ','n',' '},  //2
					{' ',' ',' ',' ',' ',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "0726", "0715" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wKnightMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(Knight4) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ','N',' ',' ',' ',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ','N',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3110", "3112", "3123", "3143", "3152", "3150", "6140", "6142", "6153", "6173" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wKnightMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; }
					}
					Assert::IsTrue(hasMatch);

				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(Knight5) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{'N',' ',' ',' ',' ',' ',' ','N'}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ',' ',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{'N',' ',' ',' ',' ',' ',' ','N'}  //7
				};

				vector<string> moves{ "7051" ,"7062", "0012", "0021", "0715", "0726", "7756", "7765" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wKnightMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; }
					}
					Assert::IsTrue(hasMatch);

				}
				Assert::AreEqual(num, (int)moves.size());
			}
		};
		TEST_CLASS(WRookTest) {
			TEST_METHOD(Rook1) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ','R',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3424", "3414", "3404", "3444", "3454", "3464", "3474",
				"3435", "3436", "3437", "3433", "3432", "3431", "3430" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wRookMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(Rook2) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ','N',' ',' ',' '},  //2
					{' ',' ',' ','n','R',' ',' ','N'},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ','n',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3433", "3435", "3436", "3444", "3454" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wRookMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(Rook3) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ',' ',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{'P','P','P','P','P','P','P','P'}, //6
					{'R','N','B','Q','K','B','N','R'}  //7
				};

				vector<string> moves{ };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wRookMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
		};
		TEST_CLASS(WBishopTest) {
			TEST_METHOD(Bishop1) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ','B',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3425", "3416", "3407", "3423", "3412", "3401",
				"3445", "3456", "3467", "3443", "3452", "3461", "3470" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wBishopMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(Bishop2) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ','N',' ',' '},  //2
					{' ',' ',' ',' ','B',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ','n',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ','q',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3423", "3412", "3401", "3445", "3443", "3452", "3461" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wBishopMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(Bishop3) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ','B'}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ',' ',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "0716", "0725", "0734", "0743", "0752", "0761", "0770" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wBishopMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(Bishop4) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{'B',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ',' ',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "0011", "0022", "0033", "0044", "0055", "0066", "0077" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wBishopMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
		};
		TEST_CLASS(WQueenTest) {
			TEST_METHOD(Queen1) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ','Q',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3424", "3414", "3404", "3444", "3454", "3464", "3474",
				"3435", "3436", "3437", "3433", "3432", "3431", "3430",
				"3425", "3416", "3407", "3423", "3412", "3401",
				"3445", "3456", "3467", "3443", "3452", "3461", "3470" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wQueenMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(Queen2) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ','R',' ',' ',' '}, //1
					{' ',' ',' ','q',' ',' ',' ',' '},  //2
					{' ',' ',' ','N','Q',' ','n',' '},  //3
					{' ',' ',' ',' ','N','N',' ',' '},  //4
					{' ',' ','n',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3424", "3425", "3416", "3407", "3435", "3436", "3443", "3452", "3423" };

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ wQueenMoves(listOfBoardParamsAndOthers) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
		};
		TEST_CLASS(WKingMovementTest) {
			TEST_METHOD(King1) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ','K',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3423", "3424", "3425", "3435", "3445", 
				"3444", "3443", "3433"};

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ getWLegalMoves(listOfBoardParamsAndOthers, "", 0, 0)};

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(King2) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{'K',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ',' ',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "1000", "1001", "1011", "1021", "1020"};

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ getWLegalMoves(listOfBoardParamsAndOthers, "", 0, 0) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
			TEST_METHOD(King3) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ','K'}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ',' ',' ',' ',' '},  //2
					{' ',' ',' ',' ',' ',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "0706", "0716", "0717"};

				arrayToBitBoard(board, listOfBitBoards);

				istringstream is{ getWLegalMoves(listOfBoardParamsAndOthers, "", 0, 0) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
		};
		TEST_CLASS(WKingSafetyTest) {
			TEST_METHOD(KingS1) {
				char board[8][8] = {
					//0   1   2   3   4   5   6   7
					{' ',' ',' ',' ',' ',' ',' ',' '}, //0
					{' ',' ',' ',' ',' ',' ',' ',' '}, //1
					{' ',' ',' ',' ','p',' ',' ',' '},  //2
					{' ',' ',' ',' ','K',' ',' ',' '},  //3
					{' ',' ',' ',' ',' ',' ',' ',' '},  //4
					{' ',' ',' ',' ',' ',' ',' ',' '} , //5
					{' ',' ',' ',' ',' ',' ',' ',' '}, //6
					{' ',' ',' ',' ',' ',' ',' ',' '}  //7
				};

				vector<string> moves{ "3424", "3425", "3445", "3444", "3443", "3423"};

				arrayToBitBoard(board, listOfBitBoards);

				bb* attacked = new bb{ attackedByBlack(listOfBoardParamsAndOthers) };

				istringstream is{ wKingMoves(listOfBoardParamsAndOthers, attacked) };

				string move;
				int num{};

				while (is >> move) {
					num++;
					bool hasMatch{ false };
					for (string m : moves) {
						if (m == move) { hasMatch = true; break; };
					}
					Assert::IsTrue(hasMatch);
				}
				Assert::AreEqual(num, (int)moves.size());
			}
		};
	}
}