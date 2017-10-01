// author: levitan

#include <iostream>

#include "TicTacToe.h"

int main(int argc, char** argv) {
	TicTacToeBoard board;
	TicTacToeAgent a('o'), b('x');

	bool aturn = true;
	while (!board.won() && !board.full()) {
		if (aturn) a.move(board);
		else b.move(board);
		aturn = !aturn;
	}

	char wonres;
	if (!board.won(&wonres)) std::cout << "Draw\n";
	else std::cout << wonres << " is the winner\n";
}
