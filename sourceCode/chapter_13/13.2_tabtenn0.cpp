/**
 * @file 13.2_tabtenn0.cpp
 * @brief a table tennis base class
 * @author fzm
 * @date 2025-12-02
 */
#include <iostream>
#include <string>

#include "13.1_tabtenn0.h"

TableTennisPlayer::TableTennisPlayer(const std::string& fn, const std::string& ln, bool ht)
    : firstName_(fn), lastName_(ln), hasTable_(ht)
{
}

TableTennisPlayer::~TableTennisPlayer() {}

void TableTennisPlayer::Name() const { std::cout << lastName_ << ", " << firstName_ << "  "; }
