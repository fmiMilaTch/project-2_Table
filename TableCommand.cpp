#include"TableCommand.hpp"
#include<iomanip>
TableCommand::TableCommand(){
    openedFile=false;
    unsavedChanges=false;
}
TableCommand::~TableCommand(){
    std::cout<<"Exited program."<<std::endl;
    delete currentFile;
    delete table;

}
void TableCommand::open(){
    char buffer[BUFF_SIZE];
    std::cout<<"Please input the file name/path:";
    std::cin>>std::ws>>std::setw(BUFF_SIZE);
    std::cin.getline(buffer,BUFF_SIZE);
    std::cin.clear();
    table=new Table(buffer);
    openedFile=true;
    currentFileLen=strlen(buffer);
    currentFile=new char [currentFileLen+1];
    strcpy(currentFile,buffer);

}
void TableCommand::close(){
    if(openedFile){
        delete currentFile;
        currentFileLen=0;
        delete table;
        openedFile=false;
        unsavedChanges=false;
        std::cout<<"The file was successfully closed."<<std::endl;
    }
    else{
        std::cout<<"There is no currently opened file to be closed."<<std::endl;
    }
}
void TableCommand::save(){
    if(openedFile){
        table->saveToFile(currentFile);
        unsavedChanges=false;
        std::cout<<"The file was saved successfully."<<std::endl;
    }
    else{
        std::cout<<"There is no currently opened file to be saved."<<std::endl;
    }
}
void TableCommand::saveAs(){
    if(openedFile){
        char buffer[BUFF_SIZE];
        std::cout<<"Please input the file name/path:";
        std::cin>>std::ws>>std::setw(BUFF_SIZE);
        std::cin.getline(buffer,BUFF_SIZE);
        std::cin.clear();

        delete currentFile;
        currentFileLen=strlen(buffer);
        currentFile=new char[currentFileLen+1];
        strcpy(currentFile,buffer);
        table->saveToFile(currentFile);
        unsavedChanges=false;
        std::cout<<"The file was saved successfully."<<std::endl;
    }
    else{
        std::cout<<"Currently there is not an opened file to be saved."<<std::endl;
    }
}
void TableCommand::help()const{
    std::cout<<"\"open\" - open a file;"<<std::endl<<"\"close\" - close currently opened file;"<<std::endl<<"\"save\" - save currently opened file;"<<std::endl;
    std::cout<<"\"saveAs\" - save currently opened file as different file;"<<std::endl<<"\"print\" - print contents of currently opened file;"<<std::endl;
    std::cout<<"\"edit\" - edit a cell of the currently opened file;"<<std::endl<<"\"help\" - view list of commands;"<<std::endl<<"\"exit\" - exit the program;"<<std::endl;
}
void TableCommand::print() const{
    if(openedFile){
        table->print();
    }
    else{
        std::cout<<"Currently there is not an opened file to print."<<std::endl;
    }
}
void TableCommand::edit(){
    if(openedFile){
        unsigned row,col;
        std::cout<<"Cell row:";
        std::cin>>std::ws>>row;
        std::cin.clear();
        std::cout<<"Cell collumn:";
        std::cin>>std::ws>>col;
        char c;
        std::cin.get(c);
        table->edit(row,col);
        unsavedChanges=true;///ne e sigurno...moge da promenia tipa na edit, no shte e tupichko :/
    }
    else{
        std::cout<<"Currently there is not an opened file to edit."<<std::endl;
    }
}
void TableCommand::start(){
    char buffer[BUFF_SIZE];
    std::cout<<"Welcome. Type \"help\" for list of existing commands."<<std::endl;
    while(1){
        std::cout<<'>';
        std::cin>>std::ws>>std::setw(BUFF_SIZE);
        std::cin.getline(buffer,BUFF_SIZE);
        std::cin.clear();
        if(strcmp(buffer,"open")==0){
            if(unsavedChanges){
                std::cout<<"There are unsaved changes to the current file. Please select \"close\" or \"save\" first."<<std::endl;
                std::cout<<'>';
                std::cin>>std::ws>>std::setw(BUFF_SIZE);
                std::cin.getline(buffer,BUFF_SIZE);
                std::cin.clear();
                if(strcmp(buffer,"save")==0){
                    save();
                    close();
                }
                else if(strcmp(buffer,"close")==0){
                    close();
                }
            }
            if(openedFile){
                close();
            }
            open();
        }
        else if(strcmp(buffer,"close")==0){
            close();
        }
        else if(strcmp(buffer,"save")==0){
            save();
        }
        else if(strcmp(buffer,"saveAs")==0){
            saveAs();
        }
        else if(strcmp(buffer,"help")==0){
            help();
        }
        else if(strcmp(buffer,"print")==0){
            print();
        }
        else if(strcmp(buffer,"edit")==0){
            edit();
        }
        else if(strcmp(buffer,"exit")==0){
            if(unsavedChanges){
                std::cout<<"There are unsaved changes to the current file. Please select \"close\" or \"save\" first."<<std::endl;
                std::cout<<'>';
                std::cin>>std::ws>>std::setw(BUFF_SIZE);
                std::cin.getline(buffer,BUFF_SIZE);
                std::cin.clear();
                if(strcmp(buffer,"save")==0){
                    save();
                    close();
                }
                else if(strcmp(buffer,"close")==0){
                    close();
                }
                std::cout<<"Exiting program..."<<std::endl;
                return;
            }
            else{
                std::cout<<"Exiting program..."<<std::endl;
                return;
            }
        }
        else{
            std::cout<<"Not an existing command. Type \"help\" for list of existing commands."<<std::endl;
        }
    }
}
