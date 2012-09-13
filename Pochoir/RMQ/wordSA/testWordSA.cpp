#include "wordSA.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

main(int argc, char *argv[]) {
	if (argc <= 3) {
		cout << "\nUsage: ./testWordSA <preprocessing> <separator list> <text file>" << endl;
		cout << "<preprocessing>:  0,1,2 or 3 for different search methods" << endl;
		cout << "<separator list>: string with word separators, \n" <<
				"                  e.g. $'\\x0a'\" \" in bash for line feeds and spaces" << endl;
		cout << "<text file>:      the input file" << endl << endl;
		exit(-1);
	}

	int preproc = atoi(argv[1]);
    int numSeps = strlen(argv[2]);
    unsigned char* sepList = (unsigned char*) argv[2]; // use $'\x0a' for "\n" in bash
	srand((unsigned) time(NULL));

 	clock_t t1 = clock();
    WordSA wsa(argv[3], sepList, numSeps, preproc);
 	clock_t t2 = clock();
	cout << "preprocessing time: " << "\t" << (double) (t2 - t1) / CLOCKS_PER_SEC << endl;

	//print WSA:
// 	for (int i = 0; i < wsa.k; i++) cout << "|" << i << "\t"; cout << endl;
// 	for (int i = 0; i < wsa.k; i++) cout << "|" << wsa.SA[i] << "\t"; cout << endl;
// 	for (int i = 0; i < 4; i++) {
// 		for (int j = 0; j < wsa.k; j++) cout << "|" << wsa.t[wsa.SA[j]+i] << "\t"; cout << endl;
// 	}

	t1 = clock();
 	// search for 300000 random patterns:
    for (int i = 0; i < 300000; i++) {
        int l = 1+(int) (((float) wsa.n - 1) *rand()/(RAND_MAX+1.0)); // length of pattern
		l = l > 50000 ? 50000 : l;                                    // patterns not too long!
        int p = (int) (((float) wsa.n - l) *rand()/(RAND_MAX+1.0));   // position of pattern
		switch(preproc) {
			case NO:
				wsa.range_naive(&wsa.t[p], l);
				break;
			case BUCKET:
				wsa.range_engineered(&wsa.t[p], l);
				break;
			case LLCP_RLCP:
				wsa.range_improved(&wsa.t[p], l);
				break;
			case LCP_RMQ:
				wsa.range_esa(&wsa.t[p], l);
				break;
		}
	}
 	t2 = clock();
	cout << "searching time for 300,000 patterns: " << "\t" << (double) (t2 - t1) / CLOCKS_PER_SEC << endl;
}
