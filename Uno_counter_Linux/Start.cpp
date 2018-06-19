/*
 *  This app is CLI Uno score counter 
    Copyright (C) 2018-2019 Mr.Sarayra

    This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

 */

#include "Start.hpp"
#include <form.h>
#include <cstdlib>

extern char const *CHOICES[]; //global var in main.cpp

void Start::setMaxPlayer(int &maxplayer) {
    scr_dump("temp_screen.out");
    clear();
    refresh();
    int x_, y_, max(-1);
    getmaxyx(stdscr, y_, x_);
    const char msgg [] = "Please set max players number:  ";
    mvprintw((y_ / 2), (x_ / 2 - strlen(msgg)), msgg);
    refresh();
    echo();
    curs_set(1);
    while (max > 10 || max < 0)
        scanw("%d", &max);
    maxplayer = max;
    clear();
    noecho();
    curs_set(0);
    refresh();
    scr_restore("temp_screen.out");
    move(2, 131 - 20);
    clrtoeol();
    mvprintw(2, 131 - 20, "Max Players=%d", maxplayer);
    refresh();
    return;
}

void Start::setMaxScore(int &maxscore) {
    scr_dump("temp_screen2.out");
    clear();
    refresh();
    int x_, y_, max(-1);
    getmaxyx(stdscr, y_, x_);
    const char msgg [] = "Please set max score (default is 500):  ";
    mvprintw((y_ / 2), (x_ / 2 - strlen(msgg)), msgg);
    refresh();
    echo();
    curs_set(1);
    while (max < 0)
        scanw("%d", &max);
    maxscore = max;
    clear();
    noecho();
    curs_set(0);
    refresh();
    scr_restore("temp_screen2.out");
    move(3, 131 - 20);
    clrtoeol();
    mvprintw(3, 131 - 20, "Max score=%d", maxscore);
    refresh();
    return;

}

void Start::startNewGame(int players_num, int max_score) {
    if (players_num == 0)
        return;
    scr_dump("temp_screen3.out");
    clear();
    int i(0), temp_index(0);
    char temp_name[20];
    Player *players = new Player [players_num];
    curs_set(1);
    echo();
    refresh();
    while (i < players_num) {
        mvprintw((LINES / 2), (COLS - 40) / 2, "Please enter player's \"%d\" name:  ", i + 1);
        refresh();
        scanw("%s", &temp_name);
        players[i].setName(temp_name);
        players[i].setIndex(i + 1);
        clear();
        ++i;
    }
    i = 0;
    keypad(stdscr, TRUE);
    /* Initialize the fields */
    FIELD * field [players_num], *save_field(NULL);
    FORM *my_form;
    int ch(0);
    bool win_trigger(false);
    char *buffer(NULL);
    char winner [20];
    int starty_(4), winner_score(0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    for (int x = 0; x < players_num; ++x) {
        field[x] = new_field(1, 10, starty_, 5 + COLS / 2, 1, 0);
        set_field_back(field[x], A_UNDERLINE);
        field_opts_off(field[x], O_AUTOSKIP);
        field_opts_off(field[x], O_NULLOK);
        starty_ += 2;
    }
    field[players_num] = NULL;
    my_form = new_form(field);
    post_form(my_form);
    starty_ = 4;
    for (int i = 0; i < players_num; ++i) {
        mvprintw(starty_, COLS / 3, "Player: %s -- %d --", players[i].getName(), players[i].getScore());
        starty_ += 2;
    }
    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, " Press F1 to exit. ");
    attroff(A_REVERSE);
    mvprintw(1, 0, "Enter the score then press 'ENTER'. To rest the score press 'DELETE'. ");
    mvprintw(0, 0, "Use arrow keys to move up and down to switch between fields");
    pos_form_cursor(my_form);
    refresh();

    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {

            case KEY_DOWN:
                /* Go to next field */
                form_driver(my_form, REQ_NEXT_FIELD);
                form_driver(my_form, REQ_END_FIELD);
                /* Go to the end of the present buffer */
                /* Leaves nicely at the last character */
                break;

            case KEY_UP:
                /* Go to previous field */
                form_driver(my_form, REQ_PREV_FIELD);
                form_driver(my_form, REQ_END_FIELD);
                break;

            case KEY_BACKSPACE:
                form_driver(my_form, REQ_DEL_PREV);
                break;

            case '\n':
                save_field = current_field(my_form);
                for (int y = 0; y < players_num; y++) {
                    set_current_field(my_form, field[y]);
                    buffer = field_buffer(field[y], 0);
                    i = atoi(buffer);
                    players[y].setScore(i);
                    form_driver(my_form, REQ_CLR_FIELD);
                    i = 0;
                    buffer = 0;

                    if (players[y].getScore() >= max_score) {
                        win_trigger = true;
                        strcpy(winner, players[y].getName());
                        winner_score = players[y].getScore();
                        ungetch(KEY_F(1));
                    }

                }
                for (int u = 0, starty_ = 4; u < players_num; ++u) {
                    mvprintw(starty_, COLS / 3, "Player: %s -- %d --", players[u].getName(), players[u].getScore());
                    starty_ += 2;
                }
                refresh();
                set_current_field(my_form, save_field);
                pos_form_cursor(my_form);
                break;

            case KEY_DC:
                save_field = current_field(my_form);
                temp_index = save_field->index;
                players[temp_index].setScore(-(players[temp_index].getScore()));
                for (int u = 0, starty_ = 4; u < players_num; ++u) {
                    mvprintw(starty_, COLS / 3, "Player: %s -- %d --", players[u].getName(), players[u].getScore());
                    starty_ += 2;
                }
                refresh();
                break;

            default:
                /* If this is a normal character, it gets */
                /* Printed
                 */
                form_driver(my_form, ch);
                break;
        }
        form_driver(my_form, REQ_VALIDATION);
    }
    unpost_form(my_form);
    free_form(my_form);
    for (int i = 0; i < players_num; ++i)
        free_field(field[i]);
    delete [] players;
    clear();
    if (win_trigger) {
        mvprintw(LINES / 2, (COLS - strlen(winner) - 45) / 2, "The winner is %s with >>%d<< score. CONGRATULATIONS!!!!!", winner, winner_score);
        refresh();
        getch();
        if (!getenv("windir")) { //check if env not WINDOWS :)
            def_prog_mode();
            endwin();
            system("./firework 3");
            reset_prog_mode();
        }
    }
    clear();
    curs_set(0);
    noecho();
    keypad(stdscr, FALSE);
    refresh();
    scr_restore("temp_screen3.out");
    refresh();
    return;
}

void Start::print_menu(WINDOW *menu_win, int highlight, int &n_choices) {
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) /* High light the present choice */ {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", CHOICES[i]);
            wattroff(menu_win, A_REVERSE);
        } else
            mvwprintw(menu_win, y, x, "%s", CHOICES[i]);
        ++y;
    }
    wrefresh(menu_win);
}
