#include"FullNumCell.hpp"
FullNumCell::FullNumCell(const char* contents):Cell(contents){
    if(isFullNumber(contents,0,contSize-1)){///samo zasega proverka
        numValue=convertToFullNum(contents,0,contSize-1);
    }
    else{
        numValue=0;
    }
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
