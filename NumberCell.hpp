#include"cell.hpp"
class NumberCell : public Cell{
    double numValue;
    friend double convertToNum(const char* text, int from, int to);
public:
    NumberCell(const char*);
    Cell* clone() const;
    void print() const;
    double getValue() const;
    NumberCell& operator=(const NumberCell&);
};
