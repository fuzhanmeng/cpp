/**
 * @file 13.5_tabtenn1.cpp
 * @brief a table tennis base class methods
 * @author fzm
 * @date 2025-12-03
 */
#include <iostream>

#include "13.4_tabtenn1.h"

TableTennisPlayer::TableTennisPlayer(const std::string& fn, const std::string& ln, bool ht)
    : firstName_(fn), lastName_(ln), HasTable_(ht) {}

TableTennisPlayer::~TableTennisPlayer() {}

void TableTennisPlayer::Name() const { std::cout << lastName_ << ", " << firstName_ << std::endl; }

// RatedPlayer methods
RatedPlayer::RatedPlayer(unsigned int r, const std::string& fn, const std::string& ln, bool ht)
    : TableTennisPlayer(fn, ln, ht) {
    rating_ = r;
}

RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer& tp) : TableTennisPlayer(tp), rating_(r) {}

RatedPlayer::~RatedPlayer() {}