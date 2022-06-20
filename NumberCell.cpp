#include"NumberCell.hpp"
NumberCell::NumberCell(const char* contents):Cell(contents){
    numValue=convertToNum(contents,0,contSize-1);
}
Cell* NumberCell::clone() const{
    return new NumberCell(*this);
}
void NumberCell::print() const{
    Cell::print();
    std::cout<<numValue<<std::endl;
}
double NumberCell::getValue() const{
    return numValue;
}
NumberCell& NumberCell::operator=(const NumberCell& other){
    if(this!=&other){
        Cell::operator=(other);
        numValue=other.numValue;
    }
    return *this;
}
