#include"cell.hpp"
class FormulaCell : public Cell{
    double numValue;

    friend int convertToFullNum(const char* text, int from, int to);
    friend bool isFormula(const char*);
    friend double convertEquasion(const char*);
public:
    FormulaCell(const char*);
    FormulaCell& operator=(const FormulaCell&);
    Cell* clone() const;
    double getValue() const;
    void print() const;

};
