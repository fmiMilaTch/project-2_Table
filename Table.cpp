#include"Table.hpp"
#include<iomanip>
void Table::del(){
    for(unsigned i=0;i<rows;i++){
        delete[] cellsTable[i];
    }
}
void Table::copyFrom(const Table& other){
    del();
    capacity=other.capacity;
    rows=other.rows;
    collumns=other.collumns;
    cellsTable=new Cell**[capacity];
    for(unsigned i=0;i<capacity;i++){
        cellsTable[i]=new Cell*[capacity];
        for(unsigned k=0;k<capacity;k++){
            cellsTable[i][k]=nullptr;
        }
    }
    for(unsigned i=0;i<rows;i++){
        for(unsigned k=0;k<collumns;k++){
            if(other.cellsTable[i][k]!=nullptr){
                cellsTable[i][k]=other.cellsTable[i][k]->clone();
            }
        }
    }

}
Table::Table(const Table& other){
    capacity=other.capacity;
    rows=other.rows;
    collumns=other.collumns;
    cellsTable=new Cell**[capacity];
    for(unsigned i=0;i<capacity;i++){
        cellsTable[i]=new Cell*[capacity];
        for(unsigned k=0;k<capacity;k++){
            cellsTable[i][k]=nullptr;
        }
    }
    for(unsigned i=0; i<rows; i++){
        for(unsigned k=0; k<collumns;k++){
            if(other.cellsTable[i][k]!=nullptr){
                cellsTable[i][k]=other.cellsTable[i][k]->clone();
            }
        }
    }
}

Table& Table::operator=(const Table& other){
    if(this!=&other){
        copyFrom(other);
        return *this;
    }
    return *this;
}
Table::~Table(){
    del();
}

Table::Table(const char* filename){
    cellsTable=new Cell**[capacity];
    for(unsigned i=0;i<capacity;i++){
        cellsTable[i]=new Cell* [capacity];
        for(unsigned k=0;k<capacity;k++){
            cellsTable[i][k]=nullptr;
        }
    }
    std::ifstream sourceFile;
    sourceFile.open(filename);
    if(sourceFile.is_open()){
        rows=0;
        collumns=0;
        unsigned collCount;
        char buffer[BUFF_SIZE];
        while(!sourceFile.eof()){
            if(rows==capacity-1){
                resizeTable();
            }
            collCount=0;
            while((sourceFile.peek()!='\n')&&(sourceFile.getline(buffer,BUFF_SIZE,','))){
                if(collCount==capacity-1){
                    rows++;
                    resizeTable();
                    rows--;
                }
                unsigned buffLen=strlen(buffer);
                if(buffLen==0){
                    cellsTable[rows][collCount]=new Cell(buffer);///hmmmm za prazni kletki
                }
                else if((buffer[0]=='"')&&(buffer[buffLen-1]=='"')){
                    cellsTable[rows][collCount]=new TextCell(buffer);
                }
                else if(isFullNumber(buffer,0,buffLen-1)){
                    cellsTable[rows][collCount]=new FullNumCell(buffer);
                }
                else if(isNumber(buffer,0,buffLen-1)){
                    cellsTable[rows][collCount]=new NumberCell(buffer);
                }
                else if(isFormula(buffer)){
                    cellsTable[rows][collCount]=new FormulaCell(buffer);
                }
                else{///tuka e mestence za greshka
                    std::cout<<"Unknown cell type ["<<rows+1<<"]["<<collCount+1<<"]."<<std::endl;
                }
                collCount++;
                if(collCount>collumns){
                    collumns=collCount;
                }
            }
            if(!sourceFile.eof()){
                char ch;
                sourceFile.get(ch);
            }
            rows++;
        }
        sourceFile.close();
        std::cout<<"The file was successfully opened."<<std::endl;
    }
    else{
        std::cout<<"The file could not be opened."<<std::endl;///miasto za greshchica
    }

}

void Table::resizeTable(){
    Cell*** newTable;
    unsigned newCapacaity=capacity*2;
    newTable=new Cell**[newCapacaity];
    for(unsigned i=0;i<newCapacaity;i++){
        newTable[i]=new Cell*[newCapacaity];
        for(unsigned k=0;k<newCapacaity;k++){
            newTable[i][k]=nullptr;
        }
    }
    for(unsigned i=0;i<rows;i++){
        for(unsigned k=0;k<collumns;k++){
            newTable[i][k]=cellsTable[i][k];
        }
    }
    cellsTable=newTable;
    capacity=newCapacaity;
}

void Table::tempPrint() const{
    for(unsigned i=0;i<rows;i++){
        std::cout<<"|";
        for(unsigned k=0;k<collumns;k++){
            if(cellsTable[i][k]!=nullptr){
                std::cout<<std::setw(MIN_CELL_WIDTH)<<cellsTable[i][k]->getContents()<<"|";
            }
            else{
                std::cout<<std::setw(MIN_CELL_WIDTH)<<"";
                std::cout<<"|";
            }
        }
        std::cout<<std::endl;
    }
}
void Table::edit(unsigned row,unsigned col){
    if(row>capacity||col>capacity){
        std::cout<<"Cell does not exist."<<std::endl;
        return;
    }
    if(row-1>=rows){
        rows=row;
    }
    if(col-1>=collumns){
        collumns=col;
    }
    char buffer[BUFF_SIZE];
    std::cout<<"New contents:";
    std::cin>>std::setw(BUFF_SIZE);
    std::cin.getline(buffer,BUFF_SIZE);
    unsigned buffLen=strlen(buffer);
    if(buffLen==0){
        delete cellsTable[row-1][col-1];
        cellsTable[row-1][col-1]=new Cell(buffer);///hmmmm za prazni kletki
    }
    else if((buffer[0]=='"')&&(buffer[buffLen-1]=='"')){
        delete cellsTable[row-1][col-1];
        cellsTable[row-1][col-1]=new TextCell(buffer);
    }
    else if(isFullNumber(buffer,0,buffLen-1)){
        delete cellsTable[row-1][col-1];
        cellsTable[row-1][col-1]=new FullNumCell(buffer);
    }
    else if(isNumber(buffer,0,buffLen-1)){
        delete cellsTable[row-1][col-1];
        cellsTable[row-1][col-1]=new NumberCell(buffer);
    }
    else if(isFormula(buffer)){
        delete cellsTable[row-1][col-1];
        cellsTable[row-1][col-1]=new FormulaCell(buffer);
    }
    else{
        std::cout<<"Unknown cell type. Could not edit cell."<<std::endl;
        std::cin.clear();
        return;
    }
    std::cout<<"Cell successfully edited."<<std::endl;
    std::cin.clear();
}
void Table::saveToFile(const char* fileName) const{
    std::ofstream destFile;
    destFile.open(fileName,std::ios::trunc);
    if(destFile.is_open()){
        for(unsigned i=0;i<rows;i++){
            for(unsigned k=0;k<collumns;k++){
                if(cellsTable[i][k]!=nullptr){
                    destFile<<cellsTable[i][k]->getContents();
                }
                destFile<<',';
            }
            if(i<rows-1){
                destFile<<'\n';
            }
        }
        destFile.close();
        std::cout<<"File successfully saved."<<std::endl;
    }
    else{
        std::cout<<"File could not be opened and saved."<<std::endl;
    }
}
