#include "BoardRepresentation.h"
#include "LegalMoves.h"

using namespace std;

double evaluation(moveParams) {
	double score{};

	for (int i = 0; i < 64; i++) {
		
		if (((WP >> i) & 1) == 1) ++score;
		else if (((WN >> i) & 1) == 1) score+=3;
		else if (((WB >> i) & 1) == 1) score+=3.2;
		else if (((WR >> i) & 1) == 1) score+=5;
		else if (((WQ >> i) & 1) == 1) score+=9;
		else if (((WK >> i) & 1) == 1) score+=1000;

		else if (((BP >> i) & 1) == 1) --score;
		else if (((BN >> i) & 1) == 1) score-=3;
		else if (((BB >> i) & 1) == 1) score-=3.2;
		else if (((BR >> i) & 1) == 1) score-=5;
		else if (((BQ >> i) & 1) == 1) score-=9;
		else if (((BK >> i) & 1) == 1) score-=1000;

	}
	
	return (score<10000) ? 0 : score; //sometimes it acts weird if score equals 0
}