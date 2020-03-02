/* Isabella Man
 * 1602153
 * CSE 15
 * 10/19/19
 * Finds all solutions to the n-Queen problem, for 1 <= n <= 15.
 * Uses a recursive function to generate the solutions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBoard(int** B, int n) {
	printf("(");
	for (int ind = 1; ind < n; ind++) {
		printf("%d, ", B[ind][0]);
	}
	printf("%d)\n", B[n][0]);
}

void removeQueen(int** B, int n, int i, int j) {
	B[i][j] = 0;
	B[i][0] = 0;

	int i1 = i + 1;
        int i2 = i + 1;
        int i3 = i + 1;
        int j2 = j + 1;
        int j3 = j - 1;
	while (i1 < n + 1) {
		B[i1][j] += 1;
		i1 = i1+1;
	}
        //while ((i2 >= 1) && (i2 < n + 1) && (j2 >= 1) && (j2 < n + 1)) {
	while ((i2 < n + 1)&& (j2 < n + 1)) {
		B[i2][j2] += 1;
                i2 = i2+1;
                j2 = j2+1;
        }
        while ((i3 >= 1) && (i3 < n + 1) && (j3 >= 1) && (j3 < n + 1)) {
        	B[i3][j3] += 1;
                i3 = i3+1;
                j3 = j3-1;
        }
}

void placeQueen(int** B, int n, int i, int j) { 
	//place a queen on that square
        B[i][j] = 1;
        //attack surrounding squares
        if (B[i][j] == 1) {
		B[i][0] = j;

        	int i1 = i + 1;
                int i2 = i + 1;
                int i3 = i + 1;
                int j2 = j + 1;
                int j3 = j - 1;
                while (i1 < n + 1) {
                	B[i1][j] -= 1;
                        i1 = i1+1;
                }
		while ((i2 >= 1) && (i2 < n + 1) && (j2 >= 1) && (j2 < n + 1)) { 
                        B[i2][j2] -= 1;
			i2 = i2+1;
			j2 = j2+1;
		}
		while ((i3 >= 1) && (i3 < n + 1) && (j3 >= 1) && (j3 < n + 1)) {
                        B[i3][j3] -= 1;
			i3 = i3+1;
			j3 = j3-1;
		}
	}
	/*for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			printf("B[%d][%d] = %d\n", i, j, B[i][j]);
		}
	}*/

}

int findSolutions(int** B, int n, int i, char* mode) {
	static int solutions = 0;
	if (i > n) {
		if (strcmp (mode, "-v") == 0) {
			printBoard(B, n);
		}
		solutions = solutions + 1;
		return solutions;
	}
	
	//for each square on row i (i.e. square j in row i)
	for (int j = 1; j < n + 1; j++) {
		//if that square is safe
		if (B[i][j] == 0) {
			//place a queen on that square
			placeQueen(B, n, i, j);
		
                	//recur on row (i+1), then add returned value
			findSolutions(B, n, i + 1, mode);

			// remove the queen from that square
			removeQueen(B, n, i, j);
		}
	}
        return solutions;
}

int main(int argc, char *argv[]) {
	int n;
	char ch;
	int **B;

//--------------------------------------------------------------------------------------
	if ((argc > 3) || (argc < 2)) {
		printf("Usage: %s [-v] number\n", argv[0]);
		printf("Option: -v   verbose output, print all solutions\n");
		exit(EXIT_FAILURE);
	}
//--------------------------------------------------------------------------------------
	if (argc == 3) {
		//if first arg is -v and second arg is an integer
		if (strcmp(argv[1], "-v") == 0 && sscanf(argv[2], "%d%c", &n, &ch) == 1) {
			n = atoi(argv[2]);
			if (n < 1 || n > 15) {
				exit(EXIT_FAILURE);
			}
			else {
				int i = 1;
				char* vb = "-v";

               			B = calloc(n+2, sizeof(int*));
                		for (int i = 0; i < n + 2; i++) {
                        		B[i] = calloc(n+2, sizeof(int));
                		}
                		for (int i = 0; i < n + 2; i++) {
                        		for (int j = 0; j < n + 2; j++) {
                                		B[i][j] = 0;
                        		}
                		}

				printf("%s-Queens has %d solutions\n", argv[2], findSolutions(B, n, i, vb)); 
                		//printf("%s-Queens has %d solutions\n", argv[2], solutions);
			}
		}
		else {
			printf("Usage: %s [-v] number\n", argv[0]);
			printf("Option: -v   verbose output, print all solutions\n");
			exit(EXIT_FAILURE);
		}
	}

//------------------------------------------------------------------------------------
	if (argc == 2 && sscanf(argv[1], "%d%c", &n, & ch) == 0) {
		printf("Usage: %s [-v] number\n", argv[0]);
		printf("Option: -v   verbose output, print all solutions\n");
		exit(EXIT_FAILURE);
	}

	//if one argument and first argument is digit:
	if (argc == 2 && sscanf(argv[1], "%d%c", &n, & ch) == 1) {
                n = atoi(argv[1]);

                if (n < 1 || n > 15) {
                        exit(EXIT_FAILURE);
                }
		else {
                	B = calloc(n+2, sizeof(int*));
                	for (int i = 0; i < n + 2; i++) {
                        	B[i] = calloc(n+2, sizeof(int));
                	}
                	for (int i = 0; i < n + 2; i++) {
                        	for (int j = 0; j < n + 2; j++) {
                                	B[i][j] = 0;
                        	}
                	}
		}

		int i = 1;
		char* nv = "";
		printf("%s-Queens has %d solutions\n", argv[1], findSolutions(B, n, i, nv));
		//printf("%s-Queens has %d solutions\n", argv[1], solutions);
	}
	/*else {
        	printf("Usage %s [-v] number\n", argv[0]);
		exit(EXIT_FAILURE);
        }*/

//-------------------------------------------------------------------------------
		for (int i = 0; i <= n + 1; i++) {
			free(B[i]);
			B[i] = NULL;
		}	

                free(B);
                B = NULL;

	return EXIT_SUCCESS;
}
