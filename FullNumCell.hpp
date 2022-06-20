#include"cell.hpp"
class FullNumCell : public Cell{
    int numValue;
    friend int convertToFullNum(const char* text, int from, int to);

    friend bool isFullNumber(const char* text, int from, int to);///samo za proverka zasega

public:
    FullNumCell(const char*);
    Cell* clone() const;
    void print() const;
    double getValue() const;
    FullNumCell& operator=(const FullNumCell&);
};
