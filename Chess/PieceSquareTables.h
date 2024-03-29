#pragma once
const double tablePawnW[64] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  4, 4, 4, 4, 4, 4, 4, 4,
  1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5,
  1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,
  1, 1, 1,1.2,1.2,1,1, 1,
  1, 1, 1,1.1,1.1,1,1, 1,
 .9,.9,.9, 1, 1,.9,.9,.9,
  0, 0, 0, 0, 0, 0, 0, 0
};

const double tablePawnB[64] = {
  0, 0, 0, 0, 0, 0, 0, 0,
 .9,.9,.9, 1, 1,.9,.9,.9,
  1, 1, 1,1.1,1.1,1,1, 1,
  1, 1, 1,1.2,1.2,1,1, 1,
  1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2,
  1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5,
  4, 4, 4, 4, 4, 4, 4, 4,
  0, 0, 0, 0, 0, 0, 0, 0
};

const double tableKnight[64] = {
	2.7, 2.8, 2.8, 2.9, 2.9, 2.8, 2.8, 2.8,
	2.7, 2.8, 2.9, 3, 3, 2.9, 2.8, 2.7,
	2.7, 2.8, 2.9, 3, 3, 2.9, 2.8, 2.7,
	2.7, 2.8, 2.9, 3.2, 3.2, 2.9, 2.8, 2.7,
	2.7, 2.8, 2.9, 3.2, 3.2, 2.9, 2.8, 2.7,
	2.7, 2.8, 2.9, 3, 3, 2.9, 2.8, 2.7,
	2.7, 2.8, 2.9, 3, 3, 2.9, 2.8, 2.7,
	2.7, 2.8, 2.8, 2.9, 2.9, 2.8, 2.8, 2.8
};

const double tableBishopW[64] = {
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3,3.2, 3, 3, 3, 3,3.2,3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3.4, 3, 3, 3, 3, 3.4, 3,
	3, 3, 2.9, 3, 3, 2.9, 3, 3
};

const double tableBishopB[64] = {
	3, 3, 2.9, 3, 3, 2.9, 3, 3,
	3, 3.4, 3, 3, 3, 3, 3.4, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3.2, 3, 3, 3, 3, 3.2, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3
};

const double tableRook[64] = {
	4.8, 4.8, 4.8, 5.1, 4.8, 5.1, 4.8, 4.8,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	4.8, 4.8, 4.8, 5.1, 4.8, 5.1, 4.8, 4.8
};

const double tableKingStartB[64] = {
	1000, 1000, 1000.5, 999.5, 999.5, 999.5, 1000.5, 1000,
	999.5, 999.5, 999.5, 999.5, 999.5, 999.5, 999.5, 999.5,
	999, 999, 999, 999, 999, 999, 999, 999,
	998, 998, 998, 998, 998, 998, 998, 998,
	997, 997, 997, 997,	997, 997, 997, 997,
	996, 996, 996, 996, 996, 996, 996, 996,
	995, 995, 995, 995, 995, 995, 995, 995,
	994, 994, 994, 994, 994, 994, 994, 994
};

const double tableKingStartW[64] = {
	994, 994, 994, 994, 994, 994, 994, 994,
	995, 995, 995, 995, 995, 995, 995, 995,
	996, 996, 996, 996, 996, 996, 996, 996,
	997, 997, 997, 997,	997, 997, 997, 997,
	998, 998, 998, 998, 998, 998, 998, 998,
	999, 999, 999, 999, 999, 999, 999, 999,
	999.5, 999.5, 999.5, 999.5, 999.5, 999.5, 999.5, 999.5,
	1000, 1000, 1000.5, 999.5, 999.5, 999.5, 1000.5, 1000
	
};

const double tableQueen[64] = {
	9, 9, 9, 8.8, 9, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9,
	9, 9, 9, 8.8, 9, 9, 9, 9
};

const double centerDistance[64] = {
  6, 5, 4, 3, 3, 4, 5, 6,
  5, 4, 3, 2, 2, 3, 4, 5,
  4, 3, 2, 1, 1, 2, 3, 4,
  3, 2, 1, 0, 0, 1, 2, 3,
  3, 2, 1, 0, 0, 1, 2, 3,
  4, 3, 2, 1, 1, 2, 3, 4,
  5, 4, 3, 2, 2, 3, 4, 5,
  6, 5, 4, 3, 3, 4, 5, 6
};