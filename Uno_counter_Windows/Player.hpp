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

