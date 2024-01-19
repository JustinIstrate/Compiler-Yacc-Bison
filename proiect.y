%{
#include <iostream>
#include <vector>
#include "SymbolTable.h"
#include <cstring>
//#include <variant>
#include <string>
#include <stdio.h>
#include <stack>
#include <queue>
//#include "class.h"
using namespace std;
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);

enum Type
{
    OPERATOR,
    NUMBER,
    IDENTIFIER,
    OTHER
};

struct Expr{
    const char* type;
    const char* name;
    const char* value;
     int intvalue;
    float floatvalue;
    bool boolvalue;
    char charvalue;
    char *strvalue;
};


struct root_data
{
    char op;
    struct Expr *expr_ptr;
    int number;
    char *other;
};
class ASTnode
{
    int exprtype;
    struct root_data *root;
    ASTnode *left;
    ASTnode *right;

    ASTnode *BuildAST(struct root_data *root, ASTnode *left, ASTnode *right, int type)
    {
        ASTnode *newnode = new ASTnode;
        newnode->root = root;
        newnode->exprtype = type;
        newnode->left = left;
        newnode->right = right;
        return newnode;
    }
    int Eval(ASTnode *node)
    {
        if (node->exprtype == Type::NUMBER)
            return node->root->number;
        else if (node->exprtype == Type::IDENTIFIER)
            return node->root->expr_ptr->intvalue;
        else if (node->exprtype == Type::OPERATOR)
        {
            if (node->root->op == '+')
                return Eval(node->left) + Eval(node->right);
            else if (node->root->op == '-')
                return Eval(node->left) - Eval(node->right);
            else if (node->root->op == '*')
                return Eval(node->left) * Eval(node->right);
            else if (node->root->op == '/')
                return Eval(node->left) / Eval(node->right);
            else if (node->root->op == '%')
                return Eval(node->left) % Eval(node->right);
        }
        else if (node->exprtype == Type::OTHER)
            return 0;
    }
    stack<ASTnode*> stiva_noduri;
    void delete_ast(ASTnode *root)
    {
        if (root != NULL)
        {
            if (root->root->other != NULL)
            {
                free(root->root->other);
            } // exprptr nu este dealocat, e pointer la variabila din tabelul de simboluri
            free(root->root);
            delete_ast(root->left);
            delete_ast(root->right);
            delete root;
        }
    }
    void delete_stack()
    {
        while(!stiva_noduri.empty())
        {
            delete_ast(stiva_noduri.top());
            stiva_noduri.pop();
        }
    }
    void build_ast_stack(char oper)
    {
        struct root_data* data=(struct root_data*)calloc(1,sizeof(struct root_data));
        data->op=oper;

        if(stiva_noduri.size()>=2)
        {
            ASTnode* right=stiva_noduri.top();
            stiva_noduri.pop();

            ASTnode* left=stiva_noduri.top();
            stiva_noduri.pop();
            //construieste un nod dou folosind cele doua noduri extrase si operatorul
            ASTnode* root=BuildAST(data,left,right,Type::OPERATOR);
            stiva_noduri.push(root);
        }
        else {
            cout<<"Eror, not enough nodes on the stack for operator "<<oper<<endl;
        }
    }
};

 class SymbolTable listSymbols;
 stack<const char *> scopeStack;
 queue<char *> listTypeParamQueue;
 vector<int> listavalori;

 const char* currentClass;

vector<Expr*> globalParamList;

 %}

%union {
     char* name;
     char* tip_data;

     int Int;
     float Float;
     bool Bool;
     char* String;
     const char* NameClas;
     struct Expr* expr;
}

%token IF ELSE WHILE FOR 
%token CLASS 
%token CONSTANT RETURN
%token EVAL TYPEOF BEGIN_PROGR END_PROGR ASSIGN
%token LOGIC_AND LOGIC_OR LESS LESS_EQ GRT GRT_EQ EQ NOT_EQ NOT 

%token<tip_data>  INT FLOAT CHAR STRING BOOL
%token<String> ID CLASS_ID FUN_ID
%token<String> BOOLEAN
%token<Int>NR_INT
%token<Float>NR_FLOAT



%left LOGIC_OR
%left LOGIC_AND
%left NOT
%left LESS GRT LESS_EQ GRT_EQ EQ NOT_EQ
%left '+' '-'
%left  '*' '/' '%' 


%left '{' '}' '[' ']' '(' ')'


%start progr
%type <tip_data> tip_variabila 

%type <String>object_decl class_header list_param param apel_functie   valoare
%type <String>variable array_decl array_init constant_def variable_decl variable_def
%type <NameClas>obj_id 
%type <expr>call_list list
%type <String>EXPRESII  EXPR_BOOL EXPR_COMP EXPR 
%type <String> array_usage object_usage
%%

// %type <Bool> EXPR_BOOL 
// %type <tip_data> EXPR 
progr: class_list declarations_glob_variable functions_glob_def main_fun {printf("The programme is correct!\n");}
     | declarations_glob_variable functions_glob_def main_fun {printf("The programme is correct!\n");}
     | functions_glob_def main_fun {printf("The programme is correct!\n");}
     | declarations_glob_variable main_fun {printf("The programme is correct!\n");}
     | class_list declarations_glob_variable main_fun {printf("The programme is correct!\n");}
     | class_list functions_glob_def main_fun {printf("The programme is correct!\n");}
     | class_list main_fun {printf("The programme is correct!\n");}
     | main_fun {printf("The programme is correct!\n");}
 
//declaation
declarations_glob_variable :  decl ';'          
	        |  declarations_glob_variable decl ';'   
             ;    
functions_glob_def : function_def ';' 
                   | functions_glob_def function_def ';'
                   ;
class_list: class_def 
           | class_list class_def  
           ;                   
main_fun : begin_progr block end_progr { }
         ;

begin_progr :   BEGIN_PROGR {scopeStack.push("main");}
    ; 
end_progr :END_PROGR{{if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} }}
               ;     
decl      : variable  
          | object_decl
          ;
variable : variable_def
  | variable_decl
  | array_decl
  | array_init
  | constant_def
  ;
array_decl : tip_variabila ID '[' NR_INT ']' {
                        
                         const char* scope ="";
                         if(!scopeStack.empty()){ //ma aflu in scope ul global
                          
                           scope=scopeStack.top(); //clasa/tipul func

                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addArray($1,$2,$4,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addArray($1,$2,$4,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                    
                     } //unidimensional      
           | tip_variabila ID '[' NR_INT ']' '[' NR_INT ']' {
                   const char* scope ="";
                         if(!scopeStack.empty()){ //ma aflu in scope ul clasa
                          
                             scope=scopeStack.top(); //clasa

                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addArray($1,$2,$4,$7,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addArray($1,$2,$4,$7,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                     } //bidimensional
           ;

array_init :  tip_variabila ID '['']' ASSIGN '{' lista_valori '}' { 
          /* Logică inițializare */
              const char* scope ="";

                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           scope=scopeStack.top(); //clasa
                         
                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.initArray(listavalori,$1,$2,listavalori.size(),scope);
               
                                }
                              else{
                                   printf("Error at decl array 1\n"); }
                         }else {
                              if(!listSymbols.existsVar($2,scope)){
                               listSymbols.initArray(listavalori,$1,$2,listavalori.size(),scope);
                                }
                              else{
                                   printf("Error at decl array 2\n"); }
                         }
               listavalori.clear();   // Elimină toate elementele din vector
               listavalori.shrink_to_fit();  // Reduc capacitatea vectorului
          } 
           ;
array_usage : ID '[' dimensiune ']' 
               /*const char* varType = listSymbols.getTypeOfVariable($1);
               if(varType!=nullptr){
                    //var a fost gasita
                    cout<<"Type var : "<<varType<<endl;
                    $$->type=varType;
               }else{
                    cout<<"Eror var dosent def";
               }}*/
            | ID '[' dimensiune ']' '[' dimensiune ']' /*const char* varType = listSymbols.getTypeOfVariable($1);
               if(varType!=nullptr){
                    //var a fost gasita
                    cout<<"Type var : "<<varType<<endl;
                    $$->type=varType;
               }else{
                    cout<<"Eror var dosent def";
               }}*/
            ;

dimensiune : NR_INT
           ;

variable_decl :tip_variabila ID {
                   
                          const char* scope ="";
                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           scope=scopeStack.top(); //clasa/functia/main
                              
                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar($1,$2,scope);
                                }
                              else{
                                   printf("Error at decl var\n%s %s",$1,$2); }
                         }else {
                              if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar($1,$2,scope);
                                }
                              else{
                                   printf("Error at decl var\n%s %s",$1,$2); }
                         }

                         //verific daca nu cumva este data membru;
                       //free($2);
                    }
              ; 
variable_def: tip_variabila ID ASSIGN EXPRESII  {      
                        const char* scope ="";
                         //const char* myCStr="" ;
                          //string exprVal;

                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           scope=scopeStack.top(); //clasa
               
                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar($1,$2,$4,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar($1,$2,$4,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                        printf("Definitia variabilei: %s de tipul %s cu valoarea initiala\n", $2, $1);
                        // Aici, expr ar trebui să fie evaluată și valoarea să fie stocată/atribuită variabilei
                    }
             ;
constant_def : CONSTANT tip_variabila ID ASSIGN EXPRESII {
                    const char* scope ="";
                   //  const char* myCStr ="";
                    // string exprVal="";
         

                                                // Presupunem că $5 este un Expr*
                         if(!scopeStack.empty()){ //ma aflu in scope ul  global
                          
                           scope=scopeStack.top(); //clasa

                                if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar(true,$2,$3,$5,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }else {
                              if(!listSymbols.existsVar($2,scope)){
                              listSymbols.addVar(true,$2,$3,$5,scope);
                                }
                              else{
                                   printf("Error at decl var\n"); }
                         }
                    
                    //trebuie adaugat ca si o constanta,direct cu valoarea ei ,nr
               }
              ;

tip_variabila : INT   {$$=$1;}
              | FLOAT {$$=$1;}
              | CHAR  {$$=$1;}
              | STRING {$$=$1;}
              | BOOL  {$$=$1;}
              ;


//partea de clase:

class_def : class_header class_body '}' ';' { if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} cout<<"de 1"<<endl;}
          //| class_def  class_header class_body '}' ';'{ if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} }
          ;
class_header : CLASS CLASS_ID '{'  { 
             
               scopeStack.push($2);

             if(!listSymbols.existsClass($2)){
                  listSymbols.addClass($2);
             }else{
               printf("Eror,already class exists\n");
             }

             }
             
           ;
//class_id : {if(!scopeStack.empty()){ $$ = (char*)scopeStack.top();}else {printf("Eroar at stack class\n");}}
class_body :   data_members memmber_functions 
           ;

data_members : variable ';'
             | data_members variable ';'
             ;
memmber_functions : function_def_class ';' 
                  | memmber_functions function_def_class ';' 
                  ;

object_decl : CLASS_ID ID {/*cod pentru declararea unui obiect al clasei*/
                     if(listSymbols.addObjInClass($1,$2)){
                       
                    }else { cout<<"Eror decl obj"<<$2<<endl;}
               
               }
            ;
object_usage :  obj_id field_or_method_call {
               currentClass = nullptr; // Setează pointerul la nullptr după eliberarea memoriei
                  /*// Cod pentru utilizarea unui câmp sau apelarea unei metode a obiectului*/}
             ;
obj_id: ID '.'{
               //const char* className=scopeStack.top();          
               //daca apelz obiectul in main,clasa curenta va fi deja scoasa din scope
                 currentClass =listSymbols.gettypeObj($1).c_str();
               
                if(strcmp(currentClass,"")!=0){
                    //exist obiectul
                         $$ = currentClass;
                         cout<<$$<<endl; // Alocăm și setăm numele clasei
                    }else{
                         cout<<"Eror class is not decl"; $$ = nullptr;}

                }

          ;
field_or_method_call : ID { /* Accesare câmp */
                     //const char* className = $<NameClas>-1;// Obțineți numele clasei transmis
                     const char* fieldName = $1;  
                     cout<<currentClass<<" tipul obj: "<<$1<<endl;
                    if(listSymbols.existsVar($1,currentClass)){
                              //l am accesat
                    }else { cout<<"Nu exista acest camp in clasa "<<currentClass<<endl;}
                         }
                    // | FUN_ID '(' call_list ')' { }
                     | apel_functie{for(Expr* expr : globalParamList){
                          delete expr; 
                          expr=nullptr;
                          
                        }
                        cout<<"S-a dealocat globalParamList"<<endl;}
                      // Verificați dacă obiectul $1 are acces la metoda $3 a clasei sale și dacă metoda este apelată corect./* Apel metoda cu argumente */ }
                      // | FUN_ID '(' ')' { /* Apel metoda fără argumente */ }
                     | array_usage {}
                     ;

function_def : function_header function_body '}' { if(!scopeStack.empty()){scopeStack.pop();}else{printf("Eror stack class\n");} }
               ;
function_header : tip_variabila FUN_ID '(' list_param ')' '{' {
                    scopeStack.push($2);
                    //const char* scopeFun=scopeStack.top();
                    const char* scope="";
                  vector<const char *> paramTypes;
                  // Presupunând că $4 este lista de parametri obținută din list_param                     
                    while(!listTypeParamQueue.empty())
                   {
                   const char*  param=listTypeParamQueue.front();
                   listTypeParamQueue.pop();
                   paramTypes.push_back(param);
                   }
                  
                   if(!listSymbols.existsFunc($1,$2,paramTypes,scope)){
                    listSymbols.addFunc($1,$2,paramTypes,scope);
                   }else { cout<<"Eror at func decl: "<<$1<<" "<<$2<<endl ;}
               } 
              ;
function_def_class : function_class_header function_body '}' {}
function_class_header :CLASS_ID tip_variabila FUN_ID '(' list_param ')' '{' {
                    
                    
                    //partea de lista a parametrilor
                    vector<const char*> paramTypes;  
                    while(!listTypeParamQueue.empty())
                    {
                    const char* param=listTypeParamQueue.front();
                    listTypeParamQueue.pop();
                    paramTypes.push_back(param);
                    }
                    const char* classId ="";

                     if(!scopeStack.empty()) //am clase in stiva
                    {
                      classId=scopeStack.top();
                      cout<<classId<<" "<<endl;
                      if(!listSymbols.existsFunc($2,$3,paramTypes,classId)){
                        listSymbols.addFunc($2,$3,paramTypes,classId);
                      }
                      else{
                         cout<<"Eror at func decl: "<<$1<<" "<<$2<<" "<<$3<<endl ;
                      }
                    }else {cout<<"error la stiva";}       
               }
              ;
function_body : block {}
              ;
apel_functie : FUN_ID '(' call_list ')' { 

                    vector<const char*> paramTypes;
                    cout<<"GLobal param types  "<<endl;
                    
                    for(Expr* expr : globalParamList){
                         cout<<expr->type<<" "<<expr->intvalue<<" "<<expr->floatvalue<<"|";
                         paramTypes.push_back(expr->type);
                         // delete expr; 
                         //expr = nullptr;
                         // Dacă este necesar, aici puteți și elibera memoria alocată pentru expr
                    }
                    if(currentClass==nullptr || *currentClass == '\0')
                    {
                   // cout<<"HELLO"<<endl;
                    const char * scope="";
                    
                    string typeFunc = listSymbols.getTypeFunc(scope,$1,paramTypes,scope);  /*scope="" inseamna ca e global*/
                        cout<<typeFunc<<endl;
                        if(typeFunc == ""){
                              cout<<"Eror cant call inexistent fun"<<endl;
                              $$=nullptr;
                        }else{
                         cout<<"Can call fun "<<$1<<endl;
                         const char* returnType = typeFunc.c_str();
                         $$=(char*)returnType;
                        }
                    //$$ trebuie sa prineasca return type ul,pt a puea asigna functia;
                    }else { //apel de metoda
                     //cout<<"HELLO1"<<endl;
                         const char * scope="";
                           string typeFunc = listSymbols.getTypeFunc(scope,$1,paramTypes,currentClass);  /*scope="" inseamna ca e global*/
                        if(typeFunc == ""){
                              cout<<"Eror cant call inexistent fun"<<endl;
                              $$=nullptr;
                        }else{
                         cout<<"Can call fun "<<$1<<" tipul metodei: "<<currentClass<<endl;
                         const char* returnType = typeFunc.c_str();
                         $$=(char*)returnType;
                        }

                    }
                      //if(globalParamList.size()>0)

                     globalParamList.clear(); 
               }
            /* | FUN_ID '('')'{
                     const char * scope="";
                     vector<const char*> paramTypes;

                      string typeFunc = listSymbols.getTypeFunc(scope,$1,paramTypes,scope);
                      if(typeFunc == ""){
                              cout<<"Eror cant call inexistent fun"<<endl;
                              $$=nullptr;
                        }else{
                         cout<<"Can call fun "<<$1<<endl;
                         const char* returnType = typeFunc.c_str();
                         $$=(char*)returnType;
                        }
                    
             }*/
             ;

list_param : param { listTypeParamQueue.push($1); printf("|%s|\n",$1);}
           | list_param ','  param {listTypeParamQueue.push($3); printf("|%s|\n",$3);}
           ;
            
param : tip_variabila ID {$$ = $1; }
      | object_decl
      | array_decl
      | constant_def
      ; 

lista_valori : valoare {}
       | lista_valori ',' valoare{}
       ;

valoare : NR_INT {/*std::string expresie = std::to_string($1); // 
                    const char* plvar_stringm = expresie.c_str();
                    $$=(char*)var_string;*/
                    listavalori.push_back($1);
                    }
        | NR_FLOAT  {/* std::string expresie = std::to_string($1); // 
                    const char* var_string = expresie.c_str();
                    $$=(char*)var_string;*/}
        ;

call_list : list { globalParamList.push_back($1);
                   cout<<"LIST: "<<$1->type<<" "<<$1->floatvalue<<endl;;
                    }
          | call_list ',' list {globalParamList.push_back($3); cout<<"LIST: "<<$3->type<<" "<<$3->floatvalue<<endl;}
          ;
list      :NR_INT {
                Expr* newExpr = new Expr();
                newExpr->type = "int";
                newExpr->intvalue = $1;
                $$ = newExpr;
               
              
          }
          | NR_FLOAT{Expr* newExpr = new Expr();
                newExpr->type = "float";
                newExpr->floatvalue = $1;
                $$ = newExpr;
               
          }
          ;

/*call_list : EXPRESII 
          | object_decl
          | call_list ',' object_decl
          | call_list ',' EXPRESII
          ;
*/
EXPRESII : EXPR {  $$=$1;}
         ;

EXPR      : EXPR '+' EXPR  {
        /*  Expr* expr1= new Expr(); 
          expr1->type= $1->type;
          Expr* expr2= new Expr(); 
          expr2->type = $3->type;
          /*
          Expr* expr1 = $1;
          Expr* expr2 = $3;

          if(strcmp(expr1->type,expr2->type)!=0){
              cout<<"Eror type do not match"; // yyerror("Operand types do not match.");
               $$=nullptr;
          }
          else{
               $$->type=expr1->type;*/
                   // Implementați logica pentru o expresie validă}
        // Setarea $$ la o nouă instanță Expr cu tipul corespunzător
          
          }
          | EXPR '-' EXPR {}
          | EXPR '*' EXPR 
          | EXPR '/' EXPR { 
                //eroare de impartire la 0 printf("Error,devide by 0\n");
          }
          | EXPR '%' EXPR {}
          | '(' EXPR ')' {$$ = $2;}
          | NR_INT { std::string expresie = std::to_string($1); // Convertiți numărul în șir de caractere
                    const char* nr_in_string = expresie.c_str();
                   $$=(char*)nr_in_string;
                   /* $$->type="int";
                    $$->intvalue=$1;
                    cout<<" aaaaaaaa "<<$1;*/
                    }
          //| NR_FLOAT {}
          | ID {
              /* const char* varType = listSymbols.getTypeOfVariable($1);
               if(varType!=nullptr){
                    //var a fost gasita
                    cout<<"Type var : "<<varType<<endl;
                    $$->type=varType;
               }else{
                    cout<<"Eror var dosent def";
               }*/$$=$1;
           }
          | apel_functie {for(Expr* expr : globalParamList){
                          delete expr; 
                          expr=nullptr; }
                        cout<<"S-a dealoc GPL"<<endl;}
          | array_usage 
         // | object_usage
          ;
EXPR_BOOL  : EXPR_BOOL LOGIC_AND EXPR_BOOL
           | EXPR_BOOL LOGIC_OR EXPR_BOOL
           | EXPR_COMP
           | BOOLEAN    
           | '(' EXPR_BOOL ')' {$$ = $2;}
           ;
EXPR_COMP : EXPRESII LESS EXPRESII 
          | EXPRESII LESS_EQ EXPRESII
          | EXPRESII GRT EXPRESII
          | EXPRESII GRT_EQ EXPRESII
          | EXPRESII EQ EXPRESII
          | EXPRESII NOT_EQ EXPRESII 
          ;
RIGHT_VALUE : EXPRESII
            ;
LEFT_VALUE : ID 
               /*const char* varType = listSymbols.getTypeOfVariable($1);
               if(varType!=nullptr){
                    //var a fost gasita
                    cout<<"Type var : "<<varType<<endl;
                    $$->type=varType;
               }else{
                    cout<<"Eror var dosent def";
               }
           */
           | object_usage
           | array_usage
           ;
//Statements
   
block: statement ';' {printf("statement\n");}
     | block statement ';'
     ;

statement: LEFT_VALUE ASSIGN RIGHT_VALUE{
             /*     Expr* leftExpr = $1;
               Expr* rightExpr = $3;
               if (strcmp(leftExpr->type, rightExpr->type) != 0) {
                   yyerror("Type mismatch in assignment.");
               } else {
                   // Continuați procesarea instrucțiunii de atribuire
               }*/
          } 
         | apel_functie { 
          if ($1 == nullptr){cout<<"Eror"<<endl;}
          for(Expr* expr : globalParamList){
                          delete expr; 
                          expr=nullptr;
                          
                        }
                        cout<<"S-a deal GPL STMT"<<endl;
          }//pot apela o functie
         
         | object_usage //pot sa apelez un obict de clasa
         | statement_conditions
         | decl 
         | eval_statement
         | typeof_statement
         ;

statement_conditions : IF '(' EXPR_BOOL ')' '{' block '}'{}
             | IF '(' EXPR_BOOL ')' '{' block '}' ELSE '{' block '}' 
             | WHILE '(' EXPR_BOOL ')' '{' block '}'  { }
             | FOR '(' variable_def ';' EXPR_BOOL ';'  EXPR ';' ')' '{' block '}' { }
             ;
eval_statement : EVAL '(' RIGHT_VALUE ')'
               ;
typeof_statement : TYPEOF '(' RIGHT_VALUE ')'
                 ;
%%

void yyerror(const char * s){
printf("error: %s at line:%d\n",s,yylineno);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
     
     listSymbols.printSymbolTable("out.txt");
    
}