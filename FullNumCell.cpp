#include"FullNumCell.hpp"
FullNumCell::FullNumCell(const char* contents):Cell(contents){
        numValue=convertToFullNum(contents,0,contSize-1);
}
Cell* FullNumCell::clone() const{
    return new FullNumCell(*this);
}
void FullNumCell::print() const{
    Cell::print();
    std::cout<<numValue<<std::endl;
}
double FullNumCell::getValue() const{
    return numValue;
}
FullNumCell& FullNumCell::operator=(const FullNumCell& other){
    if(this!=&other){
        Cell::operator=(other);
        numValue=other.numValue;
    }
    return *this;
}
