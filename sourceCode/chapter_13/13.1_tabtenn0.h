/**
 * @file 13.1_tabtenn0.h
 * @brief a table tennis base class
 * @author fzm
 * @date 2025-12-02
 */
#ifndef HEADER_NAME_H
#define HEADER_NAME_H

#include <string>

// simple base class
class TableTennisPlayer
{
public:
    TableTennisPlayer();
    TableTennisPlayer(const std::string& fn = "none", const std::string& ln = "none", bool ht = false);
    ~TableTennisPlayer();

    void Name() const;
    bool HasTable() const { return hasTable_; };
    void ResetTable(bool v) { hasTable_ = v; };

private:
    std::string firstName_;
    std::string lastName_;
    bool hasTable_;
};

#endif // HEADER_NAME_H