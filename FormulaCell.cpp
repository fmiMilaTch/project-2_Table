#include"FormulaCell.hpp"


FormulaCell::FormulaCell(const char* contents):Cell(contents){
        numValue=convertEquasion(contents);
}

FormulaCell& FormulaCell::operator=(const FormulaCell& other){
    if(this!=&other){
        Cell::operator=(other);
        numValue=other.numValue;
    }
    return *this;
}
Cell* FormulaCell::clone() const{
    return new FormulaCell(*this);
}
double FormulaCell::getValue() const{
    return numValue;
}
void FormulaCell::print() const{
    Cell::print();
    std::cout<<numValue<<std::endl;
}
