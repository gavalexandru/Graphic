#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <winbgim.h>
#include <graphics.h>
using namespace std;
int n=0;
struct node{
node*next;
float info;
char sir[4];
};
struct stiva{
node*head;
int nrelemente;
};
struct coada{
node*primul;
node*ultimul;
int nrelemente;
};
void init(stiva &S, coada &C){
S.head=NULL;
S.nrelemente=0;
C.primul=C.ultimul=NULL;
C.nrelemente=0;
}
void push1(coada &C, float data, char s[]){
if(C.primul==NULL){
    C.primul=new node;
    C.primul->next=NULL;
    if(strcmp("",s)==0) C.primul->info=data;
    strcpy(C.primul->sir,s);
    C.nrelemente++;
    C.ultimul=C.primul;
}
else{
    C.ultimul->next=new node;
    C.ultimul=C.ultimul->next;
    C.ultimul->next=NULL;
    if(strcmp(s,"")==0)C.ultimul->info=data;
    strcpy(C.ultimul->sir,s);
    C.nrelemente++;
}
}
void push2(stiva &S, char s[]){
if(S.head==NULL){
    S.head=new node;
    S.head->next=NULL;
    strcpy(S.head->sir,s);
    S.nrelemente++;
}
else{
    node*aux;
    aux=new node;
    strcpy(aux->sir,s);
    aux->next=S.head;
    S.head=aux;
    S.nrelemente++;
}
}
void popstiva(stiva &S){
if(S.nrelemente>0){
    node*aux;
    aux=S.head;
    S.head=S.head->next;
    delete aux;
    S.nrelemente--;
}
}
void afisare1(coada C){
node*aux;
aux=C.primul;
while(aux!=NULL){
    if(strcmp(aux->sir,"")==0) cout<<aux->info<<' ';
    else cout<<aux->sir<<' ';
    aux=aux->next;
}
cout<<endl;
}
void afisare2(stiva S){
node*aux;
aux=S.head;
while(aux!=NULL){
    cout<<aux->sir<<' ';
    aux=aux->next;
}
cout<<endl;
}
void strtofloat(int i, int j, string s, coada &C, int semn){
string k;
float x;
for(int i1=i;i1<=j;i1++) k+=s[i1];
x=stof(k); //str --> float
if(semn==1) x=x*(-1);
push1(C,x,"");
}
void parcurgere(int &dr, string s){
while(s[dr]>='0' && s[dr]<='9' || s[dr]=='.') dr++;
dr--;
}
int top(stiva S){
if(S.nrelemente>0){
if(strcmp(S.head->sir,"+")==0) return 2;
else if(strcmp(S.head->sir,"-")==0) return 2;
else if(strcmp(S.head->sir,"/")==0) return 3;
else if(strcmp(S.head->sir,"*")==0) return 3;
else if(strcmp(S.head->sir,"^")==0) return 4;
else if(strcmp(S.head->sir,"(")==0) return 1;
else if(strcmp(S.head->sir,")")==0) return -1;
else return 5;
}
else return 0;
}
void evaluator(string &s, coada &C, stiva &S){
int i,dr,ok,j;
for(i=0;i<n;i++){
    dr=i;
    if(s[i]=='-' && s[i+1]=='-'){
        if(i!=0){
        if(s[i-1]!='('){
        dr=i+2;
        parcurgere(dr,s);
        string kk;
        for(j=0;j<=i;j++)kk+=s[j];
        kk+='(';
        for(j=i+1;j<=dr;j++) kk+=s[j];
        kk+=')';
        for(j=dr+1;j<n;j++) kk+=s[j];
        n=n+2;
        s=kk;
        }
        else{
           string kk;
           for(j=0;j<=i-1;j++) kk+=s[j];
           for(j=i+2;j<n;j++) kk+=s[j];
           n=n-2;
           s=kk;
        }
        }
        else if(i==0){ //caz f(x)= -x; (x<0)
            string kk;
            for(j=i+2;j<n;j++) kk+=s[j];
            n=n-2;
            s=kk;
        }
    }
    else if(s[i]=='-' && s[i+1]!='.' && s[i+1]!='/' && s[i+1]!='*' && s[i+1]!='+' && s[i+1]!='-' && s[i+1]!='^' && s[i+1]<'0' && i==0 || s[i]=='-' && s[i+1]!='.' && s[i+1]!='/' && s[i+1]!='*' && s[i+1]!='+' && s[i+1]!='-' && s[i+1]!='^' && s[i+1]>'9' && i==0){
        string kk;
        kk+='(';
        kk+='-';
        kk+='1';
        kk+=')';
        kk+='*';
        for(j=1;j<n;j++) kk+=s[j];
        n=n-1;
        n=n+5;
        s=kk;
    }
    else if(s[i]=='+' && s[i+1]=='-'){
        dr=i+2;
        parcurgere(dr,s);
        string kk;
        for(j=0;j<=i;j++)kk+=s[j];
        kk+='(';
        for(j=i+1;j<=dr;j++) kk+=s[j];
        kk+=')';
        for(j=dr+1;j<n;j++) kk+=s[j];
        n=n+2;
        s=kk;
    }
    else if(s[i]=='*' && s[i+1]=='-'){
        dr=i+2;
        parcurgere(dr,s);
        string kk;
        for(j=0;j<=i;j++)kk+=s[j];
        kk+='(';
        for(j=i+1;j<=dr;j++) kk+=s[j];
        kk+=')';
        for(j=dr+1;j<n;j++) kk+=s[j];
        n=n+2;
        s=kk;
    }
    else if(s[i]=='/' && s[i+1]=='-'){
        dr=i+2;
        parcurgere(dr,s);
        string kk;
        for(j=0;j<=i;j++)kk+=s[j];
        kk+='(';
        for(j=i+1;j<=dr;j++) kk+=s[j];
        kk+=')';
        for(j=dr+1;j<n;j++) kk+=s[j];
        n=n+2;
        s=kk;
    }
    else if(s[i]=='^' && s[i+1]=='-'){
        dr=i+2;
        parcurgere(dr,s);
        string kk;
        for(j=0;j<=i;j++)kk+=s[j];
        kk+='(';
        for(j=i+1;j<=dr;j++) kk+=s[j];
        kk+=')';
        for(j=dr+1;j<n;j++) kk+=s[j];
        n=n+2;
        s=kk;
    }
    if(s[i]=='s' && s[i+1]=='q' && s[i+2]=='r' && s[i+3]=='t'){ //a - sqrt
        i=i+3;
        push2(S,"a");
    }
    else if(s[i]=='l' && s[i+1]=='o' && s[i+2]=='g'){ //b - log
        i=i+2;
        push2(S,"b");
    }
    else if(s[i]=='a' && s[i+1]=='b' && s[i+2]=='s'){ //c - abs
        i=i+2;
        push2(S,"c");
    }
    else if(s[i]=='s' && s[i+1]=='i' && s[i+2]=='n'){ //d - sin
        i=i+2;
        push2(S,"d");
    }
    else if(s[i]=='c' && s[i+1]=='o' && s[i+2]=='s'){ //e - cos
        i=i+2;
        push2(S,"e");
    }
    else if(s[i]=='t' && s[i+1]=='g'){ //f - tg
        i=i+1;
        push2(S,"f");
    }
    else if(s[i]=='c' && s[i+1]=='t' && s[i+2]=='g'){ //g - ctg
        i=i+2;
        push2(S,"g");
    }
    else if(s[i]=='='){
        push2(S,"m");
    }
    else if(s[i]=='!' && s[i+1]=='='){
        i++;
        push2(S,"h");
    }
    else if(s[i]=='<' && s[i+1]!='='){
        push2(S,"i");
    }
    else if(s[i]=='>' && s[i+1]!='='){
        push2(S,"j");
    }
    else if(s[i]=='<' && s[i+1]=='='){
        i++;
        push2(S,"k");
    }
    else if(s[i]=='>' && s[i+1]=='='){
        i++;
        push2(S,"l");
    }
    else if(s[i]<='9' && s[i]>='0'){
        ok=0;
        parcurgere(dr,s);
        strtofloat(i,dr,s,C,ok);
        i=dr;
    }
    else if(s[i]=='-' && s[i+1]<='9' && s[i+1]>='0' && i==0 || s[i]=='-' && s[i+1]<='9' && s[i+1]>='0' && s[i-1]=='('){
                i++;
                ok=1;
                dr=i;
                parcurgere(dr,s);
                strtofloat(i,dr,s,C,ok);
                i=dr;
            }
    else if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='^' || s[i]=='(' || s[i]==')'){
        if(s[i]=='(') push2(S,"(");
        else if(s[i]==')'){
            while(top(S)!=1){
                if(top(S)>1){
                    push1(C,0,S.head->sir);
                }
                popstiva(S);
            }
            popstiva(S);
        }
        else if(s[i]=='+'){
            while(top(S)>=2){
                push1(C,0,S.head->sir);
                popstiva(S);
            }
            push2(S,"+");
        }
        else if(s[i]=='-'){
            while(top(S)>=2){
                push1(C,0,S.head->sir);
                popstiva(S);
            }
            push2(S,"-");
        }
        else if(s[i]=='/'){
            while(top(S)>=3){
                push1(C,0,S.head->sir);
                popstiva(S);
            }
            push2(S,"/");
        }
        else if(s[i]=='*'){
            while(top(S)>=3){
                push1(C,0,S.head->sir);
                popstiva(S);
            }
            push2(S,"*");
        }
        else if(s[i]=='^'){
            push2(S,"^");
        }
    }
}
while(top(S)!=0){
   if(top(S)!=1 && top(S)!=-1) push1(C,0,S.head->sir);
   popstiva(S);
}
}
void ModificaX(string &s, int i, string val){
string k;
int j;
for(j=0;j<i;j++) k+=s[j];
for(j=0;j<val.size();j++) k+=val[j];
for(j=i+1;j<n;j++) k+=s[j];
n=k.size();
s=k;
}
float calcul(coada &C){
while(C.nrelemente!=1){
node*aux;
aux=C.primul;
while(strcmp(aux->sir,"")==0 && aux!=NULL) aux=aux->next;
node*aux1;
aux1=C.primul;
node*aux2;
node*aux3;
if(strcmp(aux->sir,"a")==0){
while(strcmp(aux1->next->sir,"a")!=0) aux1=aux1->next;
       aux1->info=sqrt(aux1->info);
       aux2=aux1->next;
       aux1->next=aux1->next->next;
       delete aux2;
       C.nrelemente--;
}
else if(strcmp(aux->sir,"b")==0){
       while(strcmp(aux1->next->sir,"b")!=0) aux1=aux1->next;
       aux1->info=log(aux1->info);
       aux2=aux1->next;
       aux1->next=aux1->next->next;
       delete aux2;
       C.nrelemente--;
    }
    else if(strcmp(aux->sir,"c")==0){
       while(strcmp(aux1->next->sir,"c")!=0) aux1=aux1->next;
       aux1->info=abs(aux1->info);
       aux2=aux1->next;
       aux1->next=aux1->next->next;
       delete aux2;
       C.nrelemente--;
    }
    else if(strcmp(aux->sir,"d")==0){
       while(strcmp(aux1->next->sir,"d")!=0) aux1=aux1->next;
       aux1->info=sin(aux1->info);
       aux2=aux1->next;
       aux1->next=aux1->next->next;
       delete aux2;
       C.nrelemente--;
    }
    else if(strcmp(aux->sir,"e")==0){
       while(strcmp(aux1->next->sir,"e")!=0) aux1=aux1->next;
       aux1->info=cos(aux1->info);
       aux2=aux1->next;
       aux1->next=aux1->next->next;
       delete aux2;
       C.nrelemente--;
    }
    else if(strcmp(aux->sir,"f")==0){
       while(strcmp(aux1->next->sir,"f")!=0) aux1=aux1->next;
       aux1->info=tan(aux1->info);
       aux2=aux1->next;
       aux1->next=aux1->next->next;
       delete aux2;
       C.nrelemente--;
    }
    else if(strcmp(aux->sir,"g")==0){
       while(strcmp(aux1->next->sir,"g")!=0) aux1=aux1->next;
       aux1->info=1/tan(aux1->info);
       aux2=aux1->next;
       aux1->next=aux1->next->next;
       delete aux2;
       C.nrelemente--;
    }
    else if(strcmp(aux->sir,"h")==0){
        while(strcmp(aux1->next->next->sir,"h")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        if(aux1->info!=aux2->info) aux1->info=1;
        else aux1->info=0;
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
    else if(strcmp(aux->sir,"i")==0){
        while(strcmp(aux1->next->next->sir,"i")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        if(aux1->info<aux2->info) aux1->info=1;
        else aux1->info=0;
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
    else if(strcmp(aux->sir,"j")==0){
        while(strcmp(aux1->next->next->sir,"j")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        if(aux1->info>aux2->info) aux1->info=1;
        else aux1->info=0;
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
    else if(strcmp(aux->sir,"k")==0){
        while(strcmp(aux1->next->next->sir,"k")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        if(aux1->info<=aux2->info) aux1->info=1;
        else aux1->info=0;
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
    else if(strcmp(aux->sir,"l")==0){
        while(strcmp(aux1->next->next->sir,"l")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        if(aux1->info>=aux2->info) aux1->info=1;
        else aux1->info=0;
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
    else if(strcmp(aux->sir,"m")==0){
        while(strcmp(aux1->next->next->sir,"m")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        if(aux1->info==aux2->info) aux1->info=1;
        else aux1->info=0;
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
    else if(strcmp(aux->sir,"+")==0){
        while(strcmp(aux1->next->next->sir,"+")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        aux1->info=aux1->info+aux2->info;
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
    else if(strcmp(aux->sir,"-")==0){
        while(strcmp(aux1->next->next->sir,"-")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        aux1->info=aux1->info-aux2->info;
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
    else if(strcmp(aux->sir,"*")==0){
        while(strcmp(aux1->next->next->sir,"*")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        aux1->info=aux1->info*aux2->info;
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
    else if(strcmp(aux->sir,"/")==0){
        while(strcmp(aux1->next->next->sir,"/")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        aux1->info=aux1->info/aux2->info;
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
    else if(strcmp(aux->sir,"^")==0){
        while(strcmp(aux1->next->next->sir,"^")!=0) aux1=aux1->next;
        aux2=aux1->next;
        aux3=aux1->next->next;
        aux1->info=pow(aux1->info,aux2->info);
        aux1->next=aux1->next->next->next;
        delete aux2;
        delete aux3;
        C.nrelemente=C.nrelemente-2;
    }
}
return C.primul->info;
}
bool esteCaracterValid(char caracter) {
    return std::isdigit(caracter) || std::isspace(caracter) ||
           caracter == '+' || caracter == '-' ||
           caracter == '*' || caracter == '/' ||
           caracter == '^' || caracter == '(' || caracter == ')' || caracter=='.' || std::isalpha(caracter);
}

bool nuSuntOperatoriConsecutivi(const std::string& expresie) {
    for (size_t i = 0; i < expresie.size() - 1; ++i) {
        char caracterCurent = expresie[i];
        char caracterUrmator = expresie[i + 1];

        if ((caracterCurent == '+' || caracterCurent == '-' ||
             caracterCurent == '*' || caracterCurent == '/' || caracterCurent == '^') &&
            (caracterUrmator == '+' || caracterUrmator == '-' ||
             caracterUrmator == '*' || caracterUrmator == '/' || caracterUrmator == '^')) {
            return false;  // Operatori consecutivi
        }
    }
    return true;  // Nu sunt operatori consecutivi
}

bool esteFunctieCorecta(const std::string& expresie) {
    for (char caracter : expresie) {
        if (!esteCaracterValid(caracter)) {
            return false;
        }
    }
    string s;
    s=expresie;
    if(strchr("+-^/*",s[s.size()-1])!=nullptr || strchr("+^/*",s[0])!=nullptr) return 0;
    for(int i=0;i<s.size();i++){
        if(strchr("0123456789+-^/*abcgilnoqrstx().",s[i])!=nullptr){
if(s[i]=='.'){
 if(strchr("0123456789",s[i-1])!=nullptr && strchr("0123456789",s[i+1])==nullptr) return 0;
 else if(strchr("0123456789",s[i-1])==nullptr && strchr("0123456789",s[i+1])!=nullptr) return 0;
 else if(strchr("0123456789",s[i-1])==nullptr && strchr("0123456789",s[i+1])==nullptr) return 0;
}
if(s[i]=='(' && s[i+1]==')') return 0;
if(s[i]=='s' && s[i+1]=='i' && s[i+2]=='n' && s[i+3]!='(') return 0;
else if(s[i]=='c' && s[i+1]=='o' && s[i+2]=='s' && s[i+3]!='(') return 0;
else if(s[i]=='c' && s[i+1]=='t' && s[i+2]=='g' && s[i+3]!='(') return 0;
else if(s[i]=='t' && s[i+1]=='g' && s[i+2]!='(') return 0;
else if(s[i]=='a' && s[i+1]=='b' && s[i+2]=='s' && s[i+3]!='(') return 0;
else if(s[i]=='l' && s[i+1]=='o' && s[i+2]=='g' && s[i+3]!='(') return 0;
else if(s[i]=='s' && s[i+1]=='q' && s[i+2]=='r' && s[i+3]=='t' && s[i+4]!='(') return 0;
if(strchr("abcgilnoqrst",s[i])!=nullptr){
if(s[i]=='s' && s[i+1]=='i' && s[i+2]=='n') i+=2;
else if(s[i]=='c' && s[i+1]=='o' && s[i+2]=='s') i+=2;
else if(s[i]=='c' && s[i+1]=='t' && s[i+2]=='g') i+=2;
else if(s[i]=='t' && s[i+1]=='g') i+=1;
else if(s[i]=='a' && s[i+1]=='b' && s[i+2]=='s') i+=2;
else if(s[i]=='l' && s[i+1]=='o' && s[i+2]=='g') i+=2;
else if(s[i]=='s' && s[i+1]=='q' && s[i+2]=='r' && s[i+3]=='t') i+=3;
else return 0;
}
        }
else return 0;
    }
    // Verificare paranteze
    int countParanteze = 0;
    for (char caracter : expresie) {
        if (caracter == '(') {
            countParanteze++;
        } else if (caracter == ')') {
            countParanteze--;
            if (countParanteze < 0) {
                return false;  // Parantezele nu sunt puse corect
            }
        }
    }

    if (countParanteze != 0) {
        return false;  // Parantezele nu sunt corecte
    }

    // Verificare utilizare corecta a operatorilor și funcțiilor
    size_t pos = 0;
    while ((pos = expresie.find("^", pos)) != std::string::npos) {
        if (pos == 0 || pos == expresie.size() - 1 ||
            !(std::isdigit(expresie[pos - 1]) || std::isalpha(expresie[pos - 1])) ||
            !(std::isdigit(expresie[pos + 1]) || std::isalpha(expresie[pos + 1]))) {
            return false;
        }
        pos++;
    }

    if (!nuSuntOperatoriConsecutivi(expresie)) {
        return false;  // Operatori consecutivi
    }

    return true;
}
void culori(int nr){
if(nr==1) setcolor(RED);
else if(nr==2) setcolor(BLUE);
else if(nr==3) setcolor(YELLOW);
else if(nr==4) setcolor(GREEN);
else if(nr==5) setcolor(CYAN);
else if(nr==6) setcolor(MAGENTA);
else if(nr==7) setcolor(BROWN);
else if(nr==8) setcolor(LIGHTBLUE);
else if(nr==9) setcolor(LIGHTRED);
else if(nr==10) setcolor(LIGHTGREEN);
else if(nr==11) setcolor(LIGHTCYAN);
else if(nr==12) setcolor(LIGHTMAGENTA);
}
struct lista{
string ss1;
float c,d;
int vizibilitate,culoare;
lista*urm;
lista*cap;
};
void graficvizibil(lista L,int &nrgf){
lista*aux;
aux=L.cap;
int i=0;
cout<<endl;
while(aux!=NULL){
    if(aux->vizibilitate==1){
        i++;
        cout<<i<<"."<<' '<<"f:"<<"["<<aux->c<<","<<aux->d<<"]"<<"->R, f(x)="<<aux->ss1<<' '<<"Mod: Vizibil"<<endl,nrgf++;
    }
    aux=aux->urm;
}
}
void graficinvizibil(lista L, int &nrgf){
lista*aux;
aux=L.cap;
int i=0;
cout<<endl;
while(aux!=NULL){
    if(aux->vizibilitate==0){
        i++;
        cout<<i<<"."<<' '<<"f:"<<"["<<aux->c<<","<<aux->d<<"]"<<"->R, f(x)="<<aux->ss1<<' '<<"Mod: Invizibil"<<endl,nrgf++;
    }
    aux=aux->urm;
}
}
void toategraficele(lista L){
lista*aux;
aux=L.cap;
int i=0;
cout<<endl;
while(aux!=NULL){
        i++;
       if(aux->vizibilitate==0) cout<<i<<"."<<' '<<"f:"<<"["<<aux->c<<","<<aux->d<<"]"<<"->R, f(x)="<<aux->ss1<<' '<<"Mod: Invizibil"<<endl;
       else cout<<i<<"."<<' '<<"f:"<<"["<<aux->c<<","<<aux->d<<"]"<<"->R, f(x)="<<aux->ss1<<' '<<"Mod: Vizibil"<<endl;
    aux=aux->urm;
}
}
void gfinviz(lista &L, int nr){
lista*aux;
aux=L.cap;
int i=0;
while(i!=nr){
    if(aux->vizibilitate==1) i++;
    if(i==nr) aux->vizibilitate=0;
    aux=aux->urm;
}
}
void gfviz(lista &L, int nr){
lista*aux;
aux=L.cap;
int i=0;
while(i!=nr){
    if(aux->vizibilitate==0) i++;
    if(i==nr) aux->vizibilitate=1;
    aux=aux->urm;
}
}
void eliminagf(lista &L, int nr, int &nrelemente){
if(nrelemente>1 && nr!=1){
lista*aux;
lista*aux1;
aux=L.cap;
nr--;
while(nr!=1){
    aux=aux->urm;
    nr--;
}
aux1=aux->urm;
aux->urm=aux->urm->urm;
delete aux1;
}
else if(nrelemente==1){
   L.cap=NULL;
}
else{
    L.cap=L.cap->urm;
}
nrelemente--;
}
void toategraficeleculori(lista L){
lista*aux;
aux=L.cap;
int i=0;
cout<<endl;
while(aux!=NULL){
        i++;
       if(aux->vizibilitate==0){
        cout<<i<<"."<<' '<<"f:"<<"["<<aux->c<<","<<aux->d<<"]"<<"->R, f(x)="<<aux->ss1<<' '<<"Mod: Invizibil Culoare: ";
     if(aux->culoare==1) cout<<"Rosu"<<endl;
     else if(aux->culoare==2) cout<<"Albastru"<<endl;
     else if(aux->culoare==3) cout<<"Galben"<<endl;
     else if(aux->culoare==4) cout<<"Verde"<<endl;
     else if(aux->culoare==5) cout<<"Turcoaz"<<endl;
     else if(aux->culoare==6) cout<<"Magenta"<<endl;
     else if(aux->culoare==7) cout<<"Maro"<<endl;
     else if(aux->culoare==8) cout<<"Albastru deschis"<<endl;
     else if(aux->culoare==9) cout<<"Rosu deschis"<<endl;
     else if(aux->culoare==10)cout<<"Verde deschis"<<endl;
     else if(aux->culoare==11)cout<<"Turcoaz deschis"<<endl;
     else if(aux->culoare==12)cout<<"Magenta deschis"<<endl;
       }
       else{
        cout<<i<<"."<<' '<<"f:"<<"["<<aux->c<<","<<aux->d<<"]"<<"->R, f(x)="<<aux->ss1<<' '<<"Mod: Vizibil Culoare: ";
     if(aux->culoare==1) cout<<"Rosu"<<endl;
     else if(aux->culoare==2) cout<<"Albastru"<<endl;
     else if(aux->culoare==3) cout<<"Galben"<<endl;
     else if(aux->culoare==4) cout<<"Verde"<<endl;
     else if(aux->culoare==5) cout<<"Turcoaz"<<endl;
     else if(aux->culoare==6) cout<<"Magenta"<<endl;
     else if(aux->culoare==7) cout<<"Maro"<<endl;
     else if(aux->culoare==8) cout<<"Albastru deschis"<<endl;
     else if(aux->culoare==9) cout<<"Rosu deschis"<<endl;
     else if(aux->culoare==10)cout<<"Verde deschis"<<endl;
     else if(aux->culoare==11)cout<<"Turcoaz deschis"<<endl;
     else if(aux->culoare==12)cout<<"Magenta deschis"<<endl;
       }
    aux=aux->urm;
}
}
void schimbaculoare(lista &L, int nr, int col){
int i;
i=1;
lista*aux;
aux=L.cap;
while(i!=nr){
    aux=aux->urm;
    i++;
}
aux->culoare=col;
}
int main(){
int i,j,ok=1,n1,endd=0,add=1,numar=0,nr_menu,verif1=0,info,nrgf=0,nrelemente=0,scalein=1,scaleout=1,test;
float y,x,OrigineX=400,OrigineY=400,a,b,x1,y1,ok1,unitate=20,x2;
initwindow(800,800);
setbkcolor(WHITE);
cleardevice();
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(400,i,2);
}
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(i,400,2);
}
lista LL;
LL.cap=NULL;
while(endd!=1){
verif1=0;
nrgf=0;
if(add==1){
ok=1;
cout<<"Introduceti intervalul [a,b]: ";
cin>>a>>b;
cout<<endl;
cout<<"Introduceti numarul de ramuri: ";
cin>>n1;
cout<<endl;
cout<<"Selectati culoarea graficului:"<<endl<<endl;
cout<<"1. Rosu"<<endl;
cout<<"2. Albastru"<<endl;
cout<<"3. Galben"<<endl;
cout<<"4. Verde"<<endl;
cout<<"5. Turcoaz"<<endl;
cout<<"6. Magenta"<<endl;
cout<<"7. Maro"<<endl;
cout<<"8. Albastru deschis"<<endl;
cout<<"9. Rosu deschis"<<endl;
cout<<"10. Verde deschis"<<endl;
cout<<"11. Turcoaz deschis"<<endl;
cout<<"12. Magenta deschis"<<endl;
cout<<endl;
cin>>numar;
cout<<endl;
string t;
if(n1==1){
    cout<<"f(x)=";
    cin>>t;
    if(esteFunctieCorecta(t)==0) ok=0;
    else{
        if(LL.cap==NULL){
        LL.cap=new lista;
        LL.cap->urm=NULL;
        LL.cap->c=a;
        LL.cap->d=b;
        LL.cap->ss1=t;
        LL.cap->vizibilitate=1;
        LL.cap->culoare=numar;
        nrelemente++;
      }
      else{
        lista*auxx;
        auxx=LL.cap;
        while(auxx->urm!=NULL) auxx=auxx->urm;
        auxx->urm=new lista;
        auxx=auxx->urm;
        auxx->urm=NULL;
        auxx->c=a;
        auxx->d=b;
        auxx->ss1=t;
        auxx->vizibilitate=1;
        auxx->culoare=numar;
        nrelemente++;
      }
    }
}
else{
    for(i=1;i<=n1;i++){
        cout<<"F(x)=";
        string k;
        cin>>k;
        if(esteFunctieCorecta(k)==0){
            ok=0;
            break;
        }
        cout<<"Daca: ";
        string k1;
        cin>>k1;
        cout<<endl<<endl;
        string k2="()*+";
        t+=k2[0];
        for(j=0;j<k1.size();j++) t+=k1[j];
        t+=k2[1],t+=k2[2],t+=k2[0];
        for(j=0;j<k.size();j++) t+=k[j];
        t+=k2[1];
        if(i!=n1) t+=k2[3];
    }
    if(ok==1){
      if(LL.cap==NULL){
        LL.cap=new lista;
        LL.cap->urm=NULL;
        LL.cap->c=a;
        LL.cap->d=b;
        LL.cap->ss1=t;
        LL.cap->vizibilitate=1;
        LL.cap->culoare=numar;
        nrelemente++;
      }
      else{
        lista*auxx;
        auxx=LL.cap;
        while(auxx->urm!=NULL) auxx=auxx->urm;
        auxx->urm=new lista;
        auxx=auxx->urm;
        auxx->urm=NULL;
        auxx->c=a;
        auxx->d=b;
        auxx->ss1=t;
        auxx->vizibilitate=1;
        auxx->culoare=numar;
        nrelemente++;
      }
    }
}
add=0;
}
if(ok==1){
lista*auxx;
auxx=LL.cap;
while(auxx!=NULL){
if(auxx->vizibilitate==1){
x=auxx->c;
b=auxx->d;
numar=auxx->culoare;
ok1=1;
while(x<=b){
string s;
s=auxx->ss1;
n=auxx->ss1.size();
std::string val=std::to_string(x); // conversie float --> string
for(i=0;i<n;i++){
        if(s[i]=='x'){
        ModificaX(s,i,val),i=0;
        }
    }
stiva S;
coada C;
init(S,C);
evaluator(s,C,S);
y=calcul(C);
y=round(y*1000)/1000;
y=y*(-1);
y=y*unitate;
if(scalein!=1 || scaleout!=1){
    if(scalein==1){
        x2=x/scaleout;
        y=y/scaleout;
    }
    else{
        x2=x*scalein;
        y=y*scalein;
    }
}
y=y+OrigineY;
if(ok1==1 && scalein==1 && scaleout==1) x1=x*unitate+OrigineX,y1=y,ok1=0;
else if(ok1==1) x1=x2*unitate+OrigineX,y1=y,ok1=0;
else{
 culori(numar);
 if(scalein==1 && scaleout==1){
    line(x1,y1,x*unitate+OrigineX,y);
    x1=x*unitate+OrigineX;
    y1=y;
 }
 else{
    line(x1,y1,x2*unitate+OrigineX,y);
    x1=x2*unitate+OrigineX;
    y1=y;
 }
}
x+=0.01;
}
}
auxx=auxx->urm;
}
}
else{
cout<<endl;
cout<<"Functia este scrisa gresit!"<<endl;
}
ok=0;
while(verif1!=1){
cout<<endl;
cout<<endl;
cout<<"Meniu"<<endl;
cout<<endl;
cout<<"1. Adaugarea unui nou grafic"<<endl;
cout<<"2. Grafic - Mod Invizibil"<<endl;
cout<<"3. Grafic - Mod vizibil"<<endl;
cout<<"4. Elimina Grafic"<<endl;
cout<<"5. Schimba culoarea unui grafic"<<endl;
cout<<"6. Zoom In"<<endl;
cout<<"7. Zoom Out"<<endl;
cout<<"8. Inchide Programul"<<endl;
cout<<endl;
cin>>nr_menu;
if(nr_menu>0 && nr_menu<9) verif1=1;
else{
    cout<<endl;
    cout<<"Optiunea selectata nu exista. Afisam inca o data meniul cu optiuni:"<<endl;
}
}
if(nr_menu==1){
    add=1;
    cout<<endl;
}
else if(nr_menu==2){
 ok=1;
 graficvizibil(LL,nrgf);
 cout<<endl;
if(nrgf!=0) cin>>info;
 if(nrgf!=0) gfinviz(LL,info);
 else if(nrelemente!=0) cout<<"Toate graficele sunt invizibile"<<endl;
 else cout<<"Nu exista niciun grafic in lista"<<endl;
 if(nrgf!=0){
cleardevice();
setbkcolor(WHITE);
cleardevice();
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(400,i,2);
}
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(i,400,2);
}
 }
}
else if(nr_menu==3){
ok=1;
graficinvizibil(LL,nrgf);
cout<<endl;
if(nrgf!=0) cin>>info;
if(nrgf!=0) gfviz(LL,info);
else if(nrelemente!=0) cout<<"Toate graficele sunt vizibile"<<endl;
else cout<<"Nu exista niciun grafic in lista"<<endl;
if(nrgf!=0){
cleardevice();
setbkcolor(WHITE);
cleardevice();
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(400,i,2);
}
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(i,400,2);
}
}
}
else if(nr_menu==4){
ok=1;
if(nrelemente>=1){
toategraficele(LL);
cout<<endl;
cin>>info;
eliminagf(LL,info,nrelemente);
cleardevice();
setbkcolor(WHITE);
cleardevice();
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(400,i,2);
}
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(i,400,2);
}
}
else{
cout<<endl;
cout<<"Nu exista niciun grafic in lista"<<endl;
}
}
else if(nr_menu==5){
ok=1;
if(nrelemente>=1){
toategraficeleculori(LL);
cout<<endl;
cin>>info;
cout<<endl;
cout<<"Selectati culoarea graficului:"<<endl<<endl;
cout<<"1. Rosu"<<endl;
cout<<"2. Albastru"<<endl;
cout<<"3. Galben"<<endl;
cout<<"4. Verde"<<endl;
cout<<"5. Turcoaz"<<endl;
cout<<"6. Magenta"<<endl;
cout<<"7. Maro"<<endl;
cout<<"8. Albastru deschis"<<endl;
cout<<"9. Rosu deschis"<<endl;
cout<<"10. Verde deschis"<<endl;
cout<<"11. Turcoaz deschis"<<endl;
cout<<"12. Magenta deschis"<<endl;
cout<<endl;
cin>>numar;
schimbaculoare(LL,info,numar);
cleardevice();
setbkcolor(WHITE);
cleardevice();
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(400,i,2);
}
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(i,400,2);
}
}
else{
cout<<endl;
cout<<"Nu exista niciun grafic in lista"<<endl;
}
}
else if(nr_menu==6){
ok=1;
if(scaleout!=1) scaleout=scaleout/2;
else scalein=scalein*2;
cleardevice();
setbkcolor(WHITE);
cleardevice();
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(400,i,2);
}
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(i,400,2);
}
}
else if(nr_menu==7){
ok=1;
if(scalein!=1) scalein=scalein/2;
else scaleout=scaleout*2;
cleardevice();
setbkcolor(WHITE);
cleardevice();
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(400,i,2);
}
for(i=0;i<=800;i++){
setcolor(BLACK);
circle(i,400,2);
}
}
else if(nr_menu==8){
endd=1;
return 0;
}
}
getch();
closegraph();
return 0;
}
