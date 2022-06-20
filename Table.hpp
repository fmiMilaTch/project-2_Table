#pragma once
#include"TextCell.hpp"
#include"NumberCell.hpp"
#include"FullNumCell.hpp"
#include"FormulaCell.hpp"
class Table{
    Cell*** cellsTable;
    unsigned rows;
    unsigned collumns;
    unsigned capacity=5;

    void del();
    void copyFrom(const Table&);
    void resizeTable();
public:
    Table(const char* filename);
    Table(const Table&);
    Table& operator=(const Table&);
    void tempPrint() const;
    void edit(unsigned row,unsigned col);
    void saveToFile(const char*) const;
    ~Table();
};

const unsigned MIN_CELL_WIDTH=15;
