#include"cell.hpp"
class TextCell : public Cell{
    double numValue;

    friend double convertToNum(const char* text, int from, int to);
    friend bool isNumber(const char* text, int from, int to);
public:
    TextCell(const char*);
    Cell* clone() const;
    TextCell& operator=(const TextCell&);
    void print() const;
    double getValue() const;
};
