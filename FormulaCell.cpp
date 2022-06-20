#include"FormulaCell.hpp"
void FormulaCell::del(){
    for(unsigned i=0;i<refrencesNumber;i++){
        delete[] references[i];
    }
}
void FormulaCell::copyFrom(const FormulaCell& other){
    references=new unsigned*[other.refCapacity];
    refCapacity=other.refCapacity;
    refrencesNumber=other.refrencesNumber;
    for(unsigned i=0;i<refrencesNumber;i++){
        references[i]=new unsigned[2];
        references[i][0]=other.references[i][0];
        references[i][1]=other.references[i][1];
    }
    numValue=other.numValue;
}
FormulaCell::FormulaCell(const char* contents):Cell(contents){
    if(isFormula(contents)){
        for(unsigned i=0; i<contSize;i++){
            if(contents[i]=='R'){
                refrencesNumber++;
            }
        }
        if(refrencesNumber>refCapacity){
            refCapacity*=refrencesNumber/refCapacity+1;
        }
        references=new unsigned*[refCapacity];
        for(unsigned i=0;i<refrencesNumber;i++){// zasega placeholder nuli, convertequasion ne poddurzha prepratki <:{
            references[i]=new unsigned[2];
            references[i][0]=0;
            references[i][1]=0;
        }
        numValue=convertEquasion(contents);
    }
}
FormulaCell::FormulaCell(const FormulaCell& other):Cell(other){
    refCapacity=other.refCapacity;
    references=new unsigned*[refCapacity];
    refrencesNumber=other.refrencesNumber;
    for(unsigned i=0; i<refrencesNumber;i++){
        references[i]=new unsigned[2];
        references[i][0]=other.references[i][0];
        references[i][1]=other.references[i][1];
    }
    numValue=other.numValue;
}
FormulaCell& FormulaCell::operator=(const FormulaCell& other){
    if(this!=&other){
        if(other.refCapacity>refCapacity){
            del();
            Cell::operator=(other);
            copyFrom(other);
            return *this;
        }
        else{
            Cell::operator=(other);
            refrencesNumber=other.refrencesNumber;
            numValue=other.numValue;
            for(unsigned i=0;i<refrencesNumber;i++){
                references[i][0]=other.references[i][0];
                references[i][1]=other.references[i][1];
            }
            return *this;
        }

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
FormulaCell::~FormulaCell(){
    del();
}
