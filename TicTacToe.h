#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <climits>
#include <iostream>
#include <random>
#include <set>
#include <time.h>
#include <vector>
#include <algorithm>

#define EMPTYSPOT '_'

char otherchr(char chr) {
	if (chr == 'x') return 'o';
	if (chr == 'o') return 'x';
	std::cout << "Passing " << chr << " to otherchr\n";
	throw std::exception();
}

class TicTacToeBoard;
class TicTacToeAgent;

class TicTacToeBoard {
	std::vector<char> board;
	char latestMove = EMPTYSPOT;
	std::set<int> emptyset;

	public:
	std::string tab;
	friend class TicTacToeAgent;

	// constructors
	// default constructor
	TicTacToeBoard() : board(9, EMPTYSPOT), emptyset({0,1,2,3,4,5,6,7,8}), tab("") {}	
	// range constructor
	template <class It>
	TicTacToeBoard(It begin, It end) : board(begin, end), tab("") {	
		for (int i = 0; i < board.size(); i++) 
			if (board[i] == EMPTYSPOT) emptyset.insert(i);
	}
	// copy constructor
	TicTacToeBoard(const TicTacToeBoard& rb) : board(rb.board), latestMove(rb.latestMove), emptyset(rb.emptyset), tab(rb.tab + " ") {}

	// modify
	void move(char chr, int pos) {
		if (board[pos] != EMPTYSPOT) { 	// trying to move to occupied pos
			std::cout << "Error: " << pos << " is already occupied\n";
			throw std::exception();
		}
		if (chr == latestMove) {	// trying to move twice
			std::cout << "Error: " << chr << " trying to move twice\n";
			throw std::exception();
		}
		board[pos] = chr;
		latestMove = chr;
		emptyset.erase(pos);
	}
	void move(int pos) {
		move(otherchr(latestMove), pos);
	}

	// query
	bool full() const { return emptyset.empty(); }
	bool won() const { char c; return won(&c); }
	bool won(char* c) const {
		if (emptyset.size() > 4) { *c = EMPTYSPOT; return false; }
		// check horizontal
		for (int i : { 0, 3, 6 }) 
			if (board[i] != EMPTYSPOT && board[i] == board[i+1]  && board[i] == board[i+2]) { *c = board[i]; return true; }
		// check vertical
		for (int i : { 0, 1, 2 }) 
			if (board[i] != EMPTYSPOT && board[i] == board[i+3] && board[i] == board[i+6]) { *c = board[i]; return true; }
		// check diagonals
		if (board[0] != EMPTYSPOT && board[0] == board[4] && board[0] == board[8]) { *c = board[0]; return true; }
		if (board[2] != EMPTYSPOT && board[2] == board[4] && board[2] == board[6]) { *c = board[2]; return true; }

		*c = EMPTYSPOT; return false;
	}
	const std::vector<int> getEmptyvec() const { 
		std::vector<int> vec(emptyset.begin(), emptyset.end());
		std::shuffle(vec.begin(), vec.end(), std::default_random_engine(time(NULL)));
		return vec;
	}


	// overload stream operator
	friend std::ostream& operator<<(std::ostream& stream, const TicTacToeBoard& b) {
		stream << b.tab << otherchr(b.latestMove) << "'s turn\n";
		stream << b.tab;
		for (int i = 0; i < b.board.size(); i++) {
			stream << b.board[i] << " ";
			if (i%3==2) stream << std::endl << b.tab;
		}
		return stream;
	}
};

class TicTacToeAgent {
	char chr;
	int winutil, loseutil, drawutil;

	public:
	TicTacToeAgent(char c) : chr(c), winutil(100), loseutil(0), drawutil(50) {}
	TicTacToeAgent(char c, int w, int l, int d) : chr(c), winutil(w), loseutil(l), drawutil(d) {}

	void move(TicTacToeBoard& b) {
		int pos = MinimaxDecision(b);
		b.move(chr, pos);
		std::cout << chr << " moves to " << pos << std::endl << b << std::endl;
	}

	// evaluates current state of board, returns position of best move
	int MinimaxDecision(const TicTacToeBoard& b) {
	}

	// evaluates maximum utility of a state
	int MaxValue(const TicTacToeBoard& b) {
	}

	// evaluates minimum utility of a state
	int MinValue(const TicTacToeBoard& b) {
	}

	// returns true if board is full or has three in a row
	bool TerminalTest(const TicTacToeBoard& b) {
	}

	// should only be called on terminal node. return the utility 
	// of this board to this agent (winutil, loseutil, or drawutil)
	int Utility(const TicTacToeBoard& b) {
		char c;
		if (b.won(&c)) {
			if (c==chr) return winutil;
			else return loseutil;
		}
		else if (b.full()) return drawutil;
		else throw std::exception();
	}

};

#endif
