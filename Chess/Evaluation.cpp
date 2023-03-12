#include "BoardRepresentation.h"
#include "LegalMoves.h"

double evaluation(moveParams) {
	double score{};
	for (int i = 0; i < 64; i++) {
		
		if (((WP >> i) & 1) == 1) ++score;
		if (((WN >> i) & 1) == 1) score+=3;
		if (((WB >> i) & 1) == 1) score+= 3.2;
		if (((WR >> i) & 1) == 1) score+=5;
		if (((WQ >> i) & 1) == 1) score+=9;
		if (((WK >> i) & 1) == 1) score+=1000;

		if (((BP >> i) & 1) == 1) --score;
		if (((BN >> i) & 1) == 1) score-=3;
		if (((BB >> i) & 1) == 1) score-=3.2;
		if (((BR >> i) & 1) == 1) score-=5;
		if (((BQ >> i) & 1) == 1) score-=9;
		if (((BK >> i) & 1) == 1) score-=1000;

	}
	return score;
}