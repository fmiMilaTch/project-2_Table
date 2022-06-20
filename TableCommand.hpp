#include"Table.hpp"
class TableCommand{
    char* currentFile;
    unsigned currentFileLen;
    bool openedFile;
    bool unsavedChanges;
    Table* table;

    TableCommand(const TableCommand&)=delete;
    TableCommand& operator=(const TableCommand&)=delete;

    void open();
    void save();
    void saveAs();
    void close();
    void print()const;
    void edit();
    void help()const;
public:
    void start();

    TableCommand();
    ~TableCommand();


};
