#include "backend.h"
#include "frontend.h"
#include <ncurses.h>

int main() {
  
  initscr();

  cbreak();
  noecho();
  keypad(stdscr, TRUE); // make keys work
  curs_set(0); // hide cursor
  timeout(100);

  int xmax;
  int ymax;
  getmaxyx(stdscr, ymax, xmax);
  enum Direction dir = RIGHT;

  Board* board = createBoard(createSnake(), NULL, xmax, ymax);
  int i;
  for (i = 0; i < 6; i++) {
    addFood(board);
  }

  while(true) {
    clear();
    display(board->snake, '@');
    display(board->foods, ACS_DIAMOND);
    refresh();
    dir = getMove(dir);
    enum Status status = moveSnake(board, dir);
    if (status == FAILURE) break;
  }
  endwin();

  return 0;
}


 