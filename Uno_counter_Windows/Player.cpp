#define _CRT_SECURE_NO_WARNINGS
#include "Player.hpp"
#include "Start.hpp"

int Player::getScore() {
    return m_score;
}

Player::Player() : m_score(0), m_stupid(false), m_index(1), m_name("") {
}

void Player::setScore(int score) {
    m_score += score;
    return;
}

void Player::setName(char Name[20]) {
    strcpy(m_name, Name);
    return;
}

char* Player::getName() {
    return (char*) m_name;
}

void Player::setIndex(int indx) {
    m_index = indx;
    return;
}

int Player::getIndex() {
    return m_index;
}