#include "BoardRepresentation.h"
#include "LegalMoves.h"
#include "PieceSquareTables.h"

using namespace std;

double evaluation(moveParams) {
	double scoreW{};
	double scoreB{};
	int kingPosW{};
	int kingPosB{};
	//Material evaluation
	for (int i = 0; i < 64; i++) {
		
		if (((WP >> i) & 1) == 1) scoreW += tablePawnW[i];
		else if (((WN >> i) & 1) == 1) scoreW += tableKnight[i];
		else if (((WB >> i) & 1) == 1) scoreW += tableBishopW[i];
		else if (((WR >> i) & 1) == 1) scoreW += tableRook[i];
		else if (((WQ >> i) & 1) == 1) scoreW += tableQueen[i];
		else if (((WK >> i) & 1) == 1) kingPosW = i;

		else if (((BP >> i) & 1) == 1) scoreB += tablePawnB[i];
		else if (((BN >> i) & 1) == 1) scoreB += tableKnight[i];
		else if (((BB >> i) & 1) == 1) scoreB += tableBishopB[i];
		else if (((BR >> i) & 1) == 1) scoreB += tableRook[i];
		else if (((BQ >> i) & 1) == 1) scoreB += tableQueen[i];
		else if (((BK >> i) & 1) == 1) kingPosB = i;

	}

	double scoreSum{ scoreW + scoreB };
	if (scoreSum == 0) return 0;
	else if (scoreSum <= 13) scoreW += 1000 + (6 - centerDistance[kingPosW]) / 10,
		scoreB += 1000 + (6 - centerDistance[kingPosB]) / 10;
	else scoreW += 1000 + tableKingStartW[kingPosW], scoreB += 1000 + tableKingStartB[kingPosB];
	return scoreW-scoreB; //sometimes it acts weird if score equals 0
}