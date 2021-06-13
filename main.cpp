/*
 *  Mininmal Linuxcnc Interface
 *
 *  Attempt at making a terminal based environment for
 *  Linuxcnc. The hopes of this is to allow for low spec
 *  Computers to be able to run Linuxcnc at a reasonable
 *  clock cycle.
 *
*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE":
 * <satiowadahc> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Chad A. Woitas
 * ----------------------------------------------------------------------------
 *
 */


#include <curses.h>
#include <unistd.h>

// <><><><><><><><><><><><><>
//      Window Variables
// <><><><><><><><><><><><><>
WINDOW *dro;
WINDOW *editor;
WINDOW *messages;
WINDOW *status;

uint16_t mid_top_col, mid_bot_col;
uint16_t mid_left_lines, mid_right_lines;

// Global windows
uint16_t max_h, max_w;

// <><><><><><><><><><><><><>
//      Main Function
//  TODO Abstract all functions in here
// <><><><><><><><><><><><><>
int main() {
  // Initialization
  initscr();
  cbreak();
  noecho();

  getmaxyx(stdscr, max_h, max_w);
  if(max_w < 80 || max_h < 10){
    endwin();
    printf("Terminal must be larger than 80 characters and 10 lines");
    return -1;
  }

  mid_top_col = max_w/2;
  mid_bot_col = max_w/2;
  mid_right_lines = max_h/2;
  mid_left_lines = max_h/2;
  refresh();
  dro = newwin(mid_right_lines,mid_top_col, 0, 0);
  editor = newwin(max_h-mid_right_lines, mid_bot_col, mid_right_lines, 0);
  status = newwin(mid_left_lines, max_w-mid_top_col, 0, mid_top_col);
  messages = newwin(max_h-mid_left_lines, max_w-mid_bot_col, mid_left_lines, mid_bot_col);
  box(dro, 0 , 0);
  box(editor, 0 , 0);
  box(status, 0 , 0);
  box(messages, 0 , 0);
  keypad(dro, true);

  nodelay(dro, true);
  nodelay(editor, true);
  nodelay(status, true);
  nodelay(messages, true);

  waddstr(dro,"X = 0.000\nY = 0.000\nZ = 0.000\n");
  wrefresh(dro);
  waddstr(editor, "Editor\n");
  wrefresh(editor);
  waddstr(status, "Status");
  wrefresh(status);
  waddstr(messages, "messages");
  wrefresh(messages);

  int ch;

// <><><><><><><><><><><><><>
//      Main Loop
// <><><><><><><><><><><><><>
 bool run = true;
  while(run){
    ch = getch();
    if(ch == KEY_ENTER){
      run = false;
    }
    else{
      wprintw(dro, "Pressed Key is: " );
      attron(A_BOLD);
      wprintw(dro, "%c\n", ch);
      attroff(A_BOLD);
    }
    wrefresh(dro);

  }
  // Clean up

  endwin();
  return 0;
}
