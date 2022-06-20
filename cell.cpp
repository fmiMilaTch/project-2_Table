#include"cell.hpp"
void Cell::del(){
    delete cellContents;
}
Cell::Cell(const char* contents){
    contSize=strlen(contents);
    cellContents=new char[contSize+1];
    strcpy(cellContents,contents);
}
Cell::Cell(const Cell& other){
    contSize=other.contSize;
    cellContents=new char[contSize+1];
    strcpy(cellContents,other.cellContents);
}
Cell& Cell::operator=(const Cell& other){
    if(this!=&other){
        del();
        contSize=other.contSize;
        cellContents=new char[contSize+1];
        strcpy(cellContents,other.cellContents);
        return *this;
    }
    return *this;
}
Cell* Cell::clone() const{
    return new Cell(*this);
}
double Cell::getValue() const{
    return 0;
}

Cell::~Cell(){
    del();
}
double convertToNum(const char* text, int from, int to){
    if(text!=nullptr){
        double full=0;
        double part=0;
        double ch=0;
        if((text[from]=='-')||(text[from]=='+')){
            for(int i=from+1;i<=to;i++){
                if(text[i]=='.'){
                    for(int k=to;k>i;k--){
                        ch=text[k]-'0';
                        part=(part+ch)/10;

                    }
                    full+=part;
                    if(text[from]=='-'){
                        return full*(-1);
                    }
                    else{
                        return full;
                    }
                }
                ch=text[i]-'0';
                full=full*10+ch;
            }
            if(text[from]=='-'){
                return full*(-1);
            }
            else{
                return full;
            }
        }
        for(int i=from;i<=to;i++){
                if(text[i]=='.'){
                    for(int k=to;k>i;k--){
                        ch=text[k]-'0';
                        part=(part+ch)/10;

                    }
                    full+=part;
                    return full;
                }
                ch=text[i];
                ch-='0';
                full=full*10+ch;
            }
            return full;
    }
    return 0;
}
int convertToFullNum(const char* text, int from, int to){
    if(text!=nullptr){
        double num=0;
        double ch=0;
        if((text[from]=='-')||(text[from]=='+')){
            for(int i=from+1;i<=to;i++){

                ch=text[i]-'0';
                num=num*10+ch;
            }
            if(text[from]=='-'){
                return num*(-1);
            }
            else{
                return num;
            }
        }
        for(int i=from;i<=to;i++){

                ch=text[i];
                ch-='0';
                num=num*10+ch;
            }
            return num;
    }
    return 0;
}
bool isNumber(const char* text, int from, int to){
    if(text!=nullptr){
        int pointCount=0;
        if((text[from]=='-')||(text[from]=='+')||(text[from]>='0'&&text[from]<='9')){
            for(int i=from+1;i<=to;i++){
                if(text[i]=='.'){
                    pointCount++;
                    if(pointCount==2){
                        return false;
                    }
                }
                if(!((text[i]>='0'&&text[i]<='9')||text[i]=='.')){
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    return false;
}
bool isFullNumber(const char* text, int from, int to){
    if(text!=nullptr){
        if((text[from]=='-')||(text[from]=='+')||(text[from]>='0'&&text[from]<='9')){
            for(int i=from+1;i<=to;i++){
                if(!(text[i]>='0'&&text[i]<='9')){
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    return false;
}

bool isFormula(const char* text){
    if(text[0]=='='){
        unsigned textLen=strlen(text);
        for(unsigned i=1;i<textLen;i++){
            if(text[i]=='R'){
                if((i>textLen-4)||((text[i+1]<'1')||(text[i+1]>'9'))){
                    return false;
                }
                i+=2;
                while(text[i]!='C'){
                    if((i>=textLen-2)||((text[i]<'0')||(text[i]>'9'))){
                        return false;
                    }
                    i++;
                }
                i++;
                if((i==textLen)||((text[i]<'1')||(text[i]>'9'))){
                    return false;
                }
                while((i+1<textLen)&&((text[i+1]>='0')&&(text[i+1]<='9'))){
                    i++;
                }
                if((text[i+1]=='R')||(text[i+1]=='.')){
                    return false;
                }
                continue;
            }
            if(text[i]=='.'){
                if(((i==1)||(i==textLen-1))||((text[i-1]<'0')||(text[i-1]>'9'))||((text[i+1]<'0')||(text[i+1]>'9'))){
                    return false;
                }
                continue;
            }
            if((text[i]=='+')||(text[i]=='-')){
                if((i==textLen-1)||(text[i+1]=='*')||(text[i+1]=='/')){
                    return false;
                }
                continue;
            }
            if((text[i]=='*')||(text[i]=='/')){
                if((i==1)||(i==textLen-1)||(text[i+1]=='.')||(text[i+1]=='*')||(text[i+1]=='/')){
                    return false;
                }
                continue;
            }
            if((text[i]<'0')||(text[i]>'9')){
                return false;
            }
        }
        return true;
    }
    return false;
}
double convertEquasion(const char* text){///isFormula razpoznava prepratki kum kletki, no ne i convertEquasion, ako ima prepratki niama da raboti pravilno ;;

    double sum=0;
    double temp1=1;
    double temp2=1;
    int textLen=strlen(text);
    for(int i=1;i<textLen;i++){
        if(text[i]=='-'){
            temp1*=(-1);
            continue;
        }
        if(text[i]=='+'){
            continue;
        }
        if((text[i]>='0')&&(text[i]<='9')){
            int k=i;
            while(((text[k]>='0')&&(text[k]<='9'))||(text[k]=='.')){
                k++;
            }
            temp1*=convertToNum(text,i,k-1);
            if((text[k]=='+')||(text[k]=='-')||(text[k]=='\0')){
                sum+=temp1;
                temp1=1;
                i=k-1;
                continue;
            }
            if((text[k]=='*')||(text[k]=='/')){
                int p=k+1;
                while(((text[p]>='0')&&(text[p]<='9'))||(text[p]=='-')||(text[p]=='+')){
                    if(text[p]=='-'){
                        temp2*=(-1);
                        p++;
                        continue;
                    }
                    if(text[p]=='+'){
                        p++;
                        continue;
                    }
                    if((text[p]>='0')&&(text[p]<='9')){
                        int q=p+1;
                        while(((text[q]>='0')&&(text[q]<='9'))||(text[q]=='.')){
                            q++;
                        }
                        temp2*=convertToNum(text,p,q-1);
                        if(text[k]=='*'){
                            temp1*=temp2;
                            temp2=1;
                        }
                        if(text[k]=='/'){
                            if(temp2==0){
                                return 0;
                            }
                            temp1/=temp2;
                            temp2=1;
                        }
                        if((text[q]!='*')&&(text[q]!='/')){
                            p=q-1;
                            break;
                        }
                        else{
                            k=q;
                            p=k+1;
                            continue;
                        }
                    }
                }
                i=p;
                sum+=temp1;
                temp1=1;
                continue;
            }
        }
    }
    return sum;

}
