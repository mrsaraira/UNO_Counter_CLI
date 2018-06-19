#include <stdio.h>
#include "Start.hpp"
#include "Player.hpp"

#define WIDTH 30 
#define HEIGHT 10

int startx = 0;
int starty = 0;

char const *CHOICES[] = {
    "Start Game",
    "Set Payers",
    "Set Max Score",
    "Exit",
};
int n_choices = sizeof (CHOICES) / sizeof (char *);

int main(int argc, char** argv) {
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    int maxscore = 500;
    int maxplayers = 0;
    char uno[] = "Welcome to UNO Game!";
    char *ptr = uno;
    Start *my_game = new Start; // created game obj
    initscr();
    clear();
    noecho();
    cbreak(); /* Line buffering disabled. */
    /* test for color ability of the terminal */
    if (!has_colors()) {
        endwin();
        /* exit Ncurses */
        puts("Terminal cannot do colors");
        getch();
        return (1);
    }
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(1));
    curs_set(0);
    startx = (COLS - WIDTH) / 2;
    starty = (LINES - HEIGHT) / 2;
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    //      show  default scores
    mvprintw(2, COLS - 20, "Max Players=%d", maxplayers);
    mvprintw(3, COLS - 20, "Max score=%d", maxscore);
    mvprintw(0, 1, "Use arrow keys to go up and down, Press enter to select");
    refresh();
    my_game->print_menu(menu_win, highlight, n_choices);
    refresh();
    move(starty - 2, ((COLS - strlen(uno)) / 2));
    while (*ptr) {
        addch(*ptr);
        ptr++;
        refresh();
        napms(120);
    }
    while (true) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                refresh();
                break;
        }
        my_game->print_menu(menu_win, highlight, n_choices);
        if (choice != 0) /* User did a choice  */
            mvprintw(23, 0, "You chose choice %d -> %s\n", choice, CHOICES[choice - 1]);
        clrtoeol();
        mvprintw(0, 1, "Use arrow keys to go up and down, Press enter to select a choice");
        refresh();
        if (choice == 3) {
            my_game->setMaxScore(maxscore);
            choice = 0;
            continue;
        }
        if (choice == 2) {
            my_game->setMaxPlayer(maxplayers);
            choice = 0;
            continue;
        }

        if (choice == 1) {
            my_game->startNewGame(maxplayers, maxscore);
            choice = 0;
            continue;
        }

        if (choice == 4) {
            endwin();
            return 0;
        }

    }
    getch();
    delete menu_win;
    endwin();
    delete my_game;
    return 0;
}