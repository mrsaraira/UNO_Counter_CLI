/* 
 * File:   Start.hpp
 * Author: mrsarayra
 *
 * Created on April 23, 2018, 9:12 PM
 */
#include "Player.hpp"
#ifndef START_HPP
#define START_HPP
#define MAX_PLAYERS 10

class Start {
public:
    void setMaxScore(int &maxscore);
    void setMaxPlayer(int &maxplayer);
    void startNewGame(int players_num, int max_score);
    void print_menu(WINDOW *menu_win, int highlight, int &n_choices);
};

#endif /* START_HPP */

