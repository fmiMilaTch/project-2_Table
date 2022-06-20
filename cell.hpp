#pragma once
#include<iostream>
#include<cstring>
#include<fstream>
class Table;
class Cell{
    void del();
    friend class Table;
protected:
    size_t contSize;
    char* cellContents;
public:
    Cell(const char*);
    Cell(const Cell&);
    Cell& operator=(const Cell&);
    virtual Cell* clone()const;
    virtual double getValue() const;
    virtual ~Cell();
    virtual void print() const{
        std::cout<<cellContents<<" "<<contSize<<" ";
    }
    const char* getContents() const{
        return cellContents;
    }
};

double convertToNum(const char* text, int from, int to);
int convertToFullNum(const char* text, int from, int to);
bool isNumber(const char* text, int from, int to);
bool isFullNumber(const char* text, int from, int to);
bool isFormula(const char*);
double convertEquasion(const char*);

const unsigned BUFF_SIZE=1024;
