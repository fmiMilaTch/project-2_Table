#include"TextCell.hpp"
TextCell::TextCell(const char* contents):Cell(contents){
    if(isNumber(contents,1,contSize-2)){
        numValue=convertToNum(contents,1,contSize-2);
    }
    else{
        numValue=0;
    }
}
Cell* TextCell::clone()const{
    return new TextCell(*this);
}
void TextCell::print() const{
    Cell::print();
    std::cout<<numValue<<std::endl;
}
 TextCell& TextCell::operator=(const TextCell& other){
     if(this!=&other){
        numValue=other.numValue;
        Cell::operator=(other);

     }
     return *this;
 }
 double TextCell::getValue() const{
    return numValue;
}
