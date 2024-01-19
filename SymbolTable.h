#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<cstring>
#include <fstream>
#include <variant>
//#include <variant>
using namespace std;

struct VarInfo {
    string type;      // Tipul variabilei (ex: int, float, bool, etc.)
    string name;      // Numele variabilei
    string value;     // Valoarea variabilei sub formă de șir de caractere
    //string scope;     // Numele funcției sau clasei în care variabila este definită
    int dimensions[2]={0,0};// Dimensiuni pentru array-uri, cu -1 în cazul variabilelor simple
    string className; //or function name
    bool isConstant;
    vector<int> value_from_array;
};

struct FuncInfo {
    string name;
    string returnType;
    vector<const char *> paramTypes; // Tipurile parametrilor
    // Alte informații necesare
    string className; //sau globale


};
struct ClassId {
    string className;
    vector<const char*> objects;
};
class SymbolTable {
    vector<VarInfo> vars;
    vector<FuncInfo> funcs; // Informații despre funcții
    vector<ClassId> Clas;
   // map<string,ClassInfo> clases;
    public:

    bool existsVar(const char* name,const char* className);
    void addVar(const char* type, const char*name , const char* className);
    void addVar(const char* type, const char*name,const char* value,const char* className);
    void addVar(bool isConstant ,const char* type, const char*name,const char* value,const char* className);   
    void addArray(const char* type, const char*name,int capacity1,const char* className);
    void addArray(const char* type, const char*name,int capacity1,int capacity2,const char* className);
    void initArray(const vector<int> values,const char* type, const char*name,int capacity1,const char* className);
    const char* getTypeOfVariable(const char* varName);   
    //fun
    void addFunc(const char* returnType, const char* name, const vector<const char *>& paramTypes,const char* className);
    bool existsFunc(const char* returnType, const char* name, const vector<const char *>& paramTypes,const char* className);
    string getTypeFunc(const char* returnType, const char* name, const vector<const char *>& paramTypes,const char* className);
    //class
    void addClass(const char* className);
    bool existsClass(const char* className);
    bool addObjInClass(const char* className,const char* numeObiect);
    string gettypeObj(const char* numeObiect);   

    void printSymbolTable(const string& filename);
    ~SymbolTable();
};
