#include <vector>

#include "TicTacToe.h"

int main(int argc, char** argv) {
  std::vector<char> v = {'x','x','x','-','o','-','-','-','-'};
  TicTacToeBoard board(v.begin(), v.end());
  
  TicTacToeAgent a('x'), b('o');
  
  char c;
  std::cout << board.won(&c) << ' ' << c << std::endl;
  std::cout << a.Utility(board) << ' ' << b.Utility(board) << std::endl;
}
