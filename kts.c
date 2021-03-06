/* See LICENSE file for copyright and license details.
 *
 * Knight's tour solver.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MOVEOK(X, Y)	((X) >= 0 && (X) < 8 && (Y) >= 0 && (Y) < 8 && !board[(X)][(Y)])
#define RAND(N)		(rand() / (RAND_MAX / N + 1)) 

/* function declarations */
void nextmove(int *p);
int acc(int x, int y);
void show(void);

/* globals */
int pos[2];
int board[8][8];
int moves[8][2] = {
	/* x,  y */
	{ -2, -1 },
	{  2, -1 },
	{ -1, -2 },
	{  1, -2 },
	{ -2,  1 },
	{  2,  1 },
	{ -1,  2 },
	{  1,  2 }
};

/* function implementations */
int
main(void) {
	int c, x, y, p[2];

	srand((unsigned int)time(NULL));
	x = pos[0] = RAND(8);
	y = pos[1] = RAND(8);
	board[x][y] = -1;
	for(c = 2; c <= 64; ++c) {
		nextmove(p);
		x = pos[0] = p[0];
		y = pos[1] = p[1];
		board[x][y] = c;
	}
	show();
	return 0;
}

void
nextmove(int *p) {
	int i, x, y, a, ma = 9;

	for(i = 0; i < 8; ++i) {
		x = pos[0] + moves[i][0];
		y = pos[1] + moves[i][1];
		if(MOVEOK(x, y) && (a = acc(x, y)) < ma) {
			ma = a;
			p[0] = x;
			p[1] = y;
		}
	}
}

int
acc(int x, int y) {
	int i, a;

	for(a = i = 0; i < 8; ++i)
		if(MOVEOK(x + moves[i][0], y + moves[i][1]))
			++a;
	return a;
}

void
show(void) {
	int x, y;

	printf("%2c", ' ');
	for(x = 0; x < 8; ++x)
		printf("%4c", 'a' + x);
	printf("\n");
	for(x = 0; x < 8; ++x) {
		printf("\n%2d", x);
		for(y = 0; y < 8; ++y) {
			if(board[x][y] == -1)
				printf("%2cS♞", ' ');
			else if(board[x][y])
				if(x == y && x == 7)
					printf("%2cE♞", ' ');
				else
					printf("%4.2d", board[x][y]);
			else
				printf("%4c", '.');
		}
		printf("\n");
	}
}
