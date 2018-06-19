/*
 *  This is Uno game score counter  with interactive CLI
    Copyright (C) 2018-2019 Mr.Sarayra

    This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

 */

/* 
 * File:   Player.hpp
 * Author: mrsarayra
 *
 * Created on April 23, 2018, 10:45 AM
 */
#include <string.h>
#include <curses.h>
#ifndef PLAYER_HPP
#define PLAYER_HPP
#define CHAR_SIZE 20

class Player {
    char m_name[20];
    int m_index;
    int m_score;
    bool m_stupid;
public:
    Player();
    void setName(char Name[20]);
    void setScore(int score);
    void setIndex(int indx);
    char* getName();
    int getScore();
    int getIndex();
};

#endif /* PLAYER_HPP */

