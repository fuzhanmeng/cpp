/**
 * @file 13.14_dma
 * @brief inheritance and dynamic memory allocation
 * @author fzm
 * @date 2025-12-15
 */
#ifndef DMA_H
#define DMA_H

#include <ostream>
class baseDMA
{
public:
    baseDMA(const char* l = "null", int r = 0);
    baseDMA(const baseDMA& rs);
    virtual ~baseDMA();
    baseDMA& operator=(const baseDMA& rs);
    friend std::ostream& operator<<(std::ostream& os, const baseDMA& rs);

private:
    char* lable;
    int rating_;
};

class lacksDMA : public baseDMA
{
public:
    lacksDMA(const char* c = "blank", const char* l = "null", int r = 0);
    lacksDMA(const char* c, const baseDMA& rs);

    friend std::ostream& operator<<(std::ostream& os, const lacksDMA& rs);

    virtual ~lacksDMA();

private:
    enum
    {
        COL_LEN = 40
    };
    char color[COL_LEN];
};

class hasDMA : public baseDMA
{
public:
    hasDMA(const char* s = "none", const char* l = "null", int r = 0);
    hasDMA(const char* s, const baseDMA& rs);
    hasDMA(const hasDMA& hs);

    hasDMA& operator=(const hasDMA& rs);
    friend std::ostream& operator<<(std::ostream& os, const hasDMA& rs);

    ~hasDMA();

private:
    char* style;
};

#endif // DMA_H