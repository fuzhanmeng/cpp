/**
 * @file 13.4_tabtenn1.h
 * @brief a table tennis base class
 * @author fzm
 * @date 2025-12-03
 */
#ifndef TABTENNq_H
#define TABTENNq_H

#include <string>

class TableTennisPlayer
{
public:
    TableTennisPlayer(const std::string& fn = "none", const std::string& ln = "none", bool ht = false);
    ~TableTennisPlayer();

    void Name() const;
    bool HasTable() const { return HasTable_; }
    void ResetTable(bool v) { HasTable_ = v; }

private:
    std::string firstName_;
    std::string lastName_;
    bool HasTable_;
};

class RatedPlayer : public TableTennisPlayer
{
public:
    RatedPlayer(unsigned int rat = 0, const std::string& fn = "none", const std::string& ln = "none", bool ht = false);
    RatedPlayer(unsigned int rat, const TableTennisPlayer& tb);
    ~RatedPlayer();

    unsigned int Rating() const { return rating_; }
    void ResetRating(unsigned int rat) { rating_ = rat; }

private:
    unsigned int rating_;
};

#endif // TABTENNq_H