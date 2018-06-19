/*
 *  This is Uno game score counter  with interactive CLI
    Copyright (C) 2018-2019 Mr.Sarayra

    This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

 */

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

