#ifndef OBJECT_SYNTAX_H
#define OBJECT_SYNTAX_H
#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "analyzer.h"
using namespace std;

enum TypeEl
{
    _Main_program_,
    _Program_,
    _Operator_,
    _Semicolon,
    _Dim,
    _Type,
    _As,
    _Let,
    _For,
    _Each,
    _In,
    _Next,
    _Goto,
    _When,
    _Load,
    _Put,
    _Lable,
    _On,
    _Case,
    _Fail,
    _Comment,
    _Attitide,
    _Sum,
    _Sub,
    _Mult,
    _Div,
    _Mod,
    _Left_bracket,
    _Right_bracket,
    _Comma,
    _Var,
    _Const,
    _Assign,
    _Colon,
    _Do,
    _Expression_,
    _Term_,
    _E_list_,
    _Factor_,
    _T_list_,
    _Test_,
    _Dec_,
    _Dec1_,
    _Declaration_,
    _Declare_,
    _Nont_let_,
    _List_let_,
    _List_let1_,
    _Nont_if_,
    _Nont_load_,
    _Load_list1_,
    _Load_list2_,
    _Nont_R_br_,
    _Nont_put_,
    _Expr_list1_,
    _Nont_comma_,
    _Nont_put1_,
    _E_bracket_,
    _Nont_for_,
    _Bottom_
};

enum TypeStore
{
    _LS,
    _EQ,
    _MR
};

struct classific
{
    TypeEl value;
    bool IsTerminal;
};

class Syntax : public StateM
{
protected:
    list<data_token>::iterator VecIter;
    bool CheckRule(list<TypeEl> &temp, vector<pair<TypeEl, bool>> &Vec);
    typedef void (Syntax::*function_pointer)();
    function_pointer **table1; // ������� ���������� �� ��������� ��������
    enum StateSyntax
    {
        _ACCEPT,
        _ERROR,
        _PROCESSING
    };
    StateSyntax state;

public:
    bool flagSyntax;
    list<TypeEl> store; // �������
    TypeStore reg_table;
    void TestTable();
    void MemoryTable();
    void Initialization(); // ��� ������ ���������� ����������� Error
    void Filling_EQ();     // ���������� ����� ���������� "="
    void Filling_LS();     // ���������� ����� ���������� "<"
    void Filling_MR();     // ���������� ����� ���������� ">"
    void Filling_Bottom(); // ���������� �������� ��������
    void transformation();
    void ClassificationFunction();
    bool CheckTableEq(TypeEl ind1, TypeEl ind2);
    bool CheckTableLs(TypeEl ind1, TypeEl ind2);
    bool CheckTableMr(TypeEl ind1, TypeEl ind2);
    void PrintBeg();
    void PrintBack();
    void PrintCompFirst1();
    void PrintTableClass();
    void PrintElementCl(const TypeEl &el);           // ����������� �������
    void RuleInitialisation();                       // ������������� ������ ����������
    void BeginFunction();                            // ������� ��� ���������� ���
    void BackFunction();                             // ������� ��� ���������� ���
    void CompFirst1Function();                       // ������� ��� ���������� FIRST1*(��� ���)
    bool FindEl(const int &index, const TypeEl &el); // ��� ��� ���
    bool FindEl2(const int &index, const TypeEl &el);
    void ComputBegEl(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule); // ��������� ��� �������
    void ComputEndEl(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule); // ��������� ��� �������
    vector<pair<TypeEl, bool>> ComputFirst1El(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj);
    pair<TypeEl, bool> CallFirst(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule); // ������� ������ ��-� ������
    pair<TypeEl, bool> CallLast(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule);  // ������� ��������� ��-�

    void Ls();
    void Eq();
    void Mr();
    void accept();
    void Error();

    vector<vector<pair<TypeEl, bool>>> BeginList;           // ������ ���
    vector<vector<pair<TypeEl, bool>>> BackList;            // ������ ���
    vector<vector<pair<TypeEl, bool>>> First1List;          // ������ Fist1
    vector<pair<TypeEl, bool>> El;                          // �������� ����������
    vector<pair<TypeEl, vector<pair<TypeEl, bool>>>> rules; //������ ������
    set<pair<TypeEl, bool>> RegRules;

    Syntax()
    {
        state_number = 72;
        class_number = 72;
        transformation();         // ��������������� ������� ������������ �����
        ClassificationFunction(); // ������������� ������� ��� ��������� � �����������, ����������� - 0, ��������� - 1
        RuleInitialisation();     // ������������� ������
        BeginFunction();          // ���������� ���
        BackFunction();           // ���������� ���
        CompFirst1Function();     // ���������� FIRST1
        MemoryTable();            // ��������� ������ ��� �������
        Initialization();         // ��������� ������� Err
        Filling_EQ();             // ���������� ������� EQ
        Filling_LS();             // ���������� ������� LS
        Filling_MR();             // ���������� ������� MR
        Filling_Bottom();
        /*
        PrintBeg();
        PrintBack();
        PrintCompFirst1();
        
    */
    }

    void Init() { store.emplace_front(_Bottom_); }

    void StartSyntax()
    {
        state = _PROCESSING;
        Init();                    
        VecIter = vecToken.begin(); 
        while (state == _PROCESSING)
        {
            if (store.size() <= 2 && store.back() == _Main_program_ && VecIter->CToken == _Bottom_)
                return accept();

            auto it = store.end();
            --it;
            (this->*table1[*it][VecIter->CToken])();
            if (reg_table == _EQ) 
                Transfer();
            else if (reg_table == _LS)
                Transfer();
            else if (reg_table == _MR)
                Convolution();
        }
    }

    void Transfer()
    {
        store.emplace_back(static_cast<TypeEl>(VecIter->CToken));
        ++VecIter;
    }

    void Convolution()
    {

        list<TypeEl> temp; // ��������, ������� ����� �������
        while (reg_table != _LS)
        {
            auto it = store.end();
            --it;
            auto it1 = store.end();
            --it1;
            --it1;

            (this->*table1[*it1][*it])();
            temp.push_front(*it);
            store.pop_back();
        }

        for (size_t i = 0; i < rules.size(); ++i)
        {
            if (CheckRule(temp, rules[i].second))
            {
                store.push_back(rules[i].first);
                return;
            }
        }

        if (store.size() <= 2 && store.back() == _Main_program_ && VecIter->CToken == _Bottom_)
            return accept();

        cout << "there were no rules for convolution" << endl;
        return Error();
    }
};

void Syntax::ClassificationFunction()
{

    El = {
        {{_Main_program_}, {0}},
        {{_Program_}, {0}},
        {{_Operator_}, {0}},
        {{_Semicolon}, {1}},
        {{_Dim}, {1}},
        {{_Type}, {1}},
        {{_As}, {1}},
        {{_Let}, {1}},
        {{_For}, {1}},
        {{_Each}, {1}},
        {{_In}, {1}},
        {{_Next}, {1}},
        {{_Goto}, {1}},
        {{_When}, {1}},
        {{_Load}, {1}},
        {{_Put}, {1}},
        {{_Lable}, {1}},
        {{_On}, {1}},
        {{_Case}, {1}},
        {{_Fail}, {1}},
        {{_Comment}, {1}},
        {{_Attitide}, {1}},
        {{_Sum}, {1}},
        {{_Sub}, {1}},
        {{_Mult}, {1}},
        {{_Div}, {1}},
        {{_Mod}, {1}},
        {{_Left_bracket}, {1}},
        {{_Right_bracket}, {1}},
        {{_Comma}, {1}},
        {{_Var}, {1}},
        {{_Const}, {1}},
        {{_Assign}, {1}},
        {{_Colon}, {1}},
        {{_Do}, {1}},
        {{_Expression_}, {0}},
        {{_Term_}, {0}},
        {{_E_list_}, {0}},
        {{_Factor_}, {0}},
        {{_T_list_}, {0}},
        {{_Test_}, {0}},
        {{_Dec_}, {0}},
        {{_Dec1_}, {0}},
        {{_Declaration_}, {0}},
        {{_Declare_}, {0}},
        {{_Nont_let_}, {0}},
        {{_List_let_}, {0}},
        {{_List_let1_}, {0}},
        {{_Nont_if_}, {0}},
        {{_Nont_load_}, {0}},
        {{_Load_list1_}, {0}},
        {{_Load_list2_}, {0}},
        {{_Nont_R_br_}, {0}},
        {{_Nont_put_}, {0}},
        {{_Expr_list1_}, {0}},
        {{_Nont_comma_}, {0}},
        {{_Nont_put1_}, {0}},
        {{_E_bracket_}, {0}},
        {{_Nont_for_}, {0}},
        {{_Bottom_}, {0}}

    };
}

void Syntax::RuleInitialisation()
{
    rules.resize(56);

    rules[0].first = _Main_program_;
    rules[0].second = {El[_Dec_], El[_Program_]};

    rules[1].first = _Main_program_;
    rules[1].second = {El[_Program_]};

    rules[2].first = _Program_;
    rules[2].second = {El[_Operator_]};

    rules[3].first = _Program_;
    rules[3].second = {El[_Operator_], El[_Program_]};
    // goto
    rules[4].first = _Operator_;
    rules[4].second = {El[_Goto], El[_Semicolon]};

    rules[5].first = _Expression_;
    rules[5].second = {El[_Term_]};

    rules[6].first = _Expression_;
    rules[6].second = {El[_Term_], El[_E_list_]};

    rules[7].first = _E_list_;
    rules[7].second = {El[_Sum], El[_Term_], El[_E_list_]};

    rules[8].first = _E_list_;
    rules[8].second = {El[_Sum], El[_Term_]};

    rules[9].first = _E_list_;
    rules[9].second = {El[_Sub], El[_Term_], El[_E_list_]};

    rules[10].first = _E_list_;
    rules[10].second = {El[_Sub], El[_Term_]};

    rules[11].first = _Term_;
    rules[11].second = {El[_Factor_]};

    rules[12].first = _Term_;
    rules[12].second = {El[_Factor_], El[_T_list_]};

    rules[13].first = _T_list_;
    rules[13].second = {El[_Mult], El[_Factor_], El[_T_list_]};

    rules[14].first = _T_list_;
    rules[14].second = {El[_Mult], El[_Factor_]};

    rules[15].first = _T_list_;
    rules[15].second = {El[_Div], El[_Factor_], El[_T_list_]};

    rules[16].first = _T_list_;
    rules[16].second = {El[_Div], El[_Factor_]};

    rules[17].first = _T_list_;
    rules[17].second = {El[_Mod], El[_Factor_], El[_T_list_]};

    rules[18].first = _T_list_;
    rules[18].second = {El[_Mod], El[_Factor_]};

    rules[19].first = _Factor_;
    rules[19].second = {El[_Left_bracket], El[_Expression_], El[_Right_bracket]};

    rules[20].first = _Factor_;
    rules[20].second = {El[_Const]};

    rules[21].first = _Factor_;
    rules[21].second = {El[_Var]};
    // test
    rules[22].first = _Test_;
    rules[22].second = {El[_Expression_], El[_Attitide], El[_Expression_]};
    // Объявдение
    rules[23].first = _Dec1_;
    rules[23].second = {El[_Declaration_], El[_As], El[_Type], El[_Semicolon]};

    rules[24].first = _Declaration_;
    rules[24].second = {El[_Dim], El[_Var]};

    rules[25].first = _Declaration_;
    rules[25].second = {El[_Declare_], El[_Var]};

    rules[26].first = _Declare_;
    rules[26].second = {El[_Declaration_], El[_Comma]};
    // _Let
    rules[27].first = _Operator_;
    rules[27].second = {El[_Nont_let_], El[_Semicolon]};

    rules[28].first = _Nont_let_;
    rules[28].second = {El[_Let], El[_Var], El[_Assign], El[_List_let_]};

    rules[29].first = _List_let_;
    rules[29].second = {El[_Var], El[_Assign], El[_List_let_]};

    rules[30].first = _List_let_;
    rules[30].second = {El[_List_let1_]};

    rules[31].first = _List_let1_;
    rules[31].second = {El[_Expression_]};
    // _Lable
    rules[32].first = _Operator_;
    rules[32].second = {El[_Lable]};
    // if _Operator
    rules[33].first = _Operator_;
    rules[33].second = {El[_Nont_if_], El[_Semicolon]};

    rules[34].first = _Nont_if_;
    rules[34].second = {El[_Goto], El[_When], El[_Test_]};
    // _Semicolon
    rules[35].first = _Operator_;
    rules[35].second = {El[_Semicolon]};
    // FAIL
    rules[36].first = _Operator_;
    rules[36].second = {El[_Fail], El[_Semicolon]};
    // _Comment
    rules[37].first = _Operator_;
    rules[37].second = {El[_Comment]};
    // _Load
    rules[38].first = _Operator_;
    rules[38].second = {El[_Nont_load_], El[_Semicolon]};

    rules[39].first = _Nont_load_;
    rules[39].second = {El[_Load_list1_], El[_Nont_R_br_]};

    rules[40].first = _Load_list1_;
    rules[40].second = {El[_Load], El[_Var]};

    rules[41].first = _Load_list1_;
    rules[41].second = {El[_Load_list2_], El[_Var]};

    rules[42].first = _Load_list2_;
    rules[42].second = {El[_Load_list1_], El[_Comma]};

    rules[43].first = _Nont_R_br_;
    rules[43].second = {El[_Right_bracket]};
    // _Put
    rules[44].first = _Operator_;
    rules[44].second = {El[_Nont_put_], El[_Semicolon]};

    rules[45].first = _Nont_put_;
    rules[45].second = {El[_Put], El[_Expr_list1_]};

    rules[46].first = _Expr_list1_;
    rules[46].second = {El[_Expression_], El[_Nont_comma_], El[_Expr_list1_]};

    rules[47].first = _Expr_list1_;
    rules[47].second = {El[_Expression_], El[_Nont_comma_], El[_E_bracket_]};

    rules[48].first = _Operator_;
    rules[48].second = {El[_Nont_put1_], El[_Semicolon]};

    rules[49].first = _Nont_put1_;
    rules[49].second = {El[_Put], El[_E_bracket_]};

    rules[50].first = _Nont_comma_;
    rules[50].second = {El[_Comma]};

    rules[51].first = _E_bracket_;
    rules[51].second = {El[_Expression_], El[_Right_bracket]};
    // _For
    rules[52].first = _Operator_;
    rules[52].second = {El[_Nont_for_], El[_Next]};

    rules[53].first = _Nont_for_;
    rules[53].second = {El[_For], El[_Each], El[_Var], El[_In], El[_List_let1_], El[_Do], El[_Program_]};

    rules[54].first = _Dec_;
    rules[54].second = {El[_Dec_], El[_Dec1_]};

    rules[55].first = _Dec_;
    rules[55].second = {El[_Dec1_]};
}

void Syntax::transformation()
{
    for (list<data_token>::iterator el = vecToken.begin(); el != vecToken.end(); ++el)
    {
        switch (el->CToken)
        {
        case SEMICOLON:
            el->CToken = _Semicolon;
            break;
        case DIM:
            el->CToken = _Dim;
            break;
        case TYPE:
            el->CToken = _Type;
            break;
        case AS:
            el->CToken = _As;
            break;
        case LET:
            el->CToken = _Let;
            break;
        case FOR:
            el->CToken = _For;
            break;
        case EACH:
            el->CToken = _Each;
            break;
        case IN:
            el->CToken = _In;
            break;
        case NEXT:
            el->CToken = _Next;
            break;
        case GOTO:
            el->CToken = _Goto;
            break;
        case WHEN:
            el->CToken = _When;
            break;
        case LOAD:
            el->CToken = _Load;
            break;
        case PUT:
            el->CToken = _Put;
            break;
        case LABLE:
            el->CToken = _Lable;
            break;
        case ON:
            el->CToken = _On;
            break;
        case CASE:
            el->CToken = _Case;
            break;
        case FAIL:
            el->CToken = _Fail;
            break;
        case COMMENT:
            el->CToken = _Comment;
            break;
        case BIN_OPERATION:
            switch (*static_cast<TypeOperation *>(el->ptr))
            {
            case BIN_SUM:
                el->CToken = _Sum;
                break;
            case BIN_SUB:
                el->CToken = _Sub;
                break;
            case BIN_MULT:
                el->CToken = _Mult;
                break;
            case BIN_DIV:
                el->CToken = _Div;
                break;
            case BIN_MOD:
                el->CToken = _Mod;
                break;
            }
            break;
        case ATTITUDE:
            el->CToken = _Attitide;
            break;
        case LEFT_BRACKET:
            el->CToken = _Left_bracket;
            break;
        case RIGHT_BRACKET:
            el->CToken = _Right_bracket;
            break;
        case COMMA:
            el->CToken = _Comma;
            break;
        case VARIABLE:
            el->CToken = _Var;
            break;
        case CONSTANT:
            el->CToken = _Const;
            break;
        case ASSIGN:
            el->CToken = _Assign;
            break;
        case COLON:
            el->CToken = _Colon;
            break;
        case DO:
            el->CToken = _Do;
            break;
        case END_MARKER:
            el->CToken = _Bottom_;
            break;
        }
    }
}

void Syntax::Ls() { reg_table = _LS; }

void Syntax::Mr() { reg_table = _MR; }
void Syntax::Eq() { reg_table = _EQ; }

void Syntax::Error()
{
    state = _ERROR;
    flagSyntax = false;
}

void Syntax::accept()
{
    state = _ACCEPT;
    flagSyntax = true;
}

bool Syntax::CheckRule(list<TypeEl> &temp, vector<pair<TypeEl, bool>> &Vec)
{
    if (temp.size() != Vec.size())
        return 0;
    int count = 0;
    for (auto i = temp.begin(); i != temp.end(); ++i)
    {
        if (Vec[count].first != *i)
            return 0;
        ++count;
    }
    return 1;
}

void Syntax::Filling_Bottom()
{
    for (size_t i = 0; i < BeginList[0].size(); ++i)
        table1[_Bottom_][BeginList[0][i].first] = &Syntax::Ls;

    for (size_t i = 0; i < BackList[0].size(); ++i)
        table1[BackList[0][i].first][_Bottom_] = &Syntax::Mr;
}

void Syntax::Filling_MR()
{
    TypeEl temp1, temp2;
    for (size_t i = 0; i < rules.size(); ++i)
    {
        for (size_t j = 0; j < rules[i].second.size() - 1; ++j)
        {
            temp1 = rules[i].second[j].first;
            temp2 = rules[i].second[j + 1].first;
            if (rules[i].second[j].second == 0)
                for (size_t k = 0; k < BackList[temp1].size(); ++k)
                    for (size_t c = 0; c < First1List[temp2].size(); ++c)
                        if (CheckTableMr(BackList[temp1][k].first, First1List[temp2][c].first))
                            table1[BackList[temp1][k].first][First1List[temp2][c].first] = &Syntax::Mr;
        }
    }
}

void Syntax::TestTable()
{
    for (size_t i = 0; i < state_number; ++i)
    {
        for (size_t j = 0; j < state_number; ++j)
        {
            (this->*table1[i][j])();
        }
        cout << '\n';
    }
}

void Syntax::Filling_EQ()
{
    TypeEl temp1, temp2;
    for (size_t i = 0; i < rules.size(); ++i)
    {
        for (size_t j = 0; j < rules[i].second.size() - 1; ++j)
        {
            temp1 = rules[i].second[j].first;
            temp2 = rules[i].second[j + 1].first;
            if (CheckTableEq(temp1, temp2))
                table1[temp1][temp2] = &Syntax::Eq;
        }
    }
}

void Syntax::Filling_LS()
{
    TypeEl temp1, temp2;

    for (size_t i = 0; i < rules.size(); ++i)
    {
        for (size_t j = 0; j < rules[i].second.size() - 1; ++j)
        {
            temp1 = rules[i].second[j].first;
            temp2 = rules[i].second[j + 1].first;
            if (rules[i].second[j + 1].second == 0)
            {
                for (int k = 0; k < BeginList[temp2].size(); ++k)
                    if (CheckTableLs(temp1, BeginList[temp2][k].first))
                        table1[temp1][BeginList[temp2][k].first] = &Syntax::Ls;
            }
        }
    }
}

void Syntax::Initialization()
{
    for (size_t i = 0; i < state_number; ++i)
        for (size_t j = 0; j < state_number; ++j)
            table1[i][j] = &Syntax::Error;
}

bool Syntax::CheckTableEq(TypeEl ind1, TypeEl ind2)
{
    if (table1[ind1][ind2] == &Syntax::Error || table1[ind1][ind2] == &Syntax::Eq)
        return true;
    else
    {
        cout << "������ : ";
        PrintElementCl(ind1);
        cout << '\n';
        cout << "������� : ";
        PrintElementCl(ind2);
        cout << '\n';
        throw "�������� ������� Eq...";
    }
}

bool Syntax::CheckTableLs(TypeEl ind1, TypeEl ind2)
{
    if (table1[ind1][ind2] == &Syntax::Error || table1[ind1][ind2] == &Syntax::Ls)
        return true;
    else
    {
        if (table1[ind1][ind2] == &Syntax::Eq)
            cout << "Eq\n";
        if (table1[ind1][ind2] == &Syntax::Ls)
            cout << "Ls\n";

        cout << "������ : ";
        PrintElementCl(ind1);
        cout << '\n';
        cout << "������� : ";
        PrintElementCl(ind2);
        cout << '\n';
        throw "�������� ������� Ls...";
    }
}

bool Syntax::CheckTableMr(TypeEl ind1, TypeEl ind2)
{
    if (table1[ind1][ind2] == &Syntax::Error || table1[ind1][ind2] == &Syntax::Mr)
        return true;
    else
    {
        if (table1[ind1][ind2] == &Syntax::Eq)
            cout << "Eq\n";
        if (table1[ind1][ind2] == &Syntax::Ls)
            cout << "Ls\n";
        cout << "������ ";
        PrintElementCl(ind1);
        cout << '\n';
        cout << "������� : ";
        PrintElementCl(ind2);
        cout << '\n';
        throw "�������� ������� Mr...";
    }
}

void Syntax::MemoryTable()
{
    table1 = new function_pointer *[state_number];
    for (size_t i = 0; i < state_number; ++i)
        table1[i] = new function_pointer[class_number];
}

void Syntax::PrintTableClass()
{
    for (auto &el : El)
    {
        PrintElementCl(el.first);
        cout << "  : " << el.second << endl;
    }
}

void Syntax::PrintBeg()
{
    cout << "SetSymb.size : " << BeginList.size() << endl;
    int count = 0;
    for (auto el : BeginList)
    {
        cout << count << ") ���(";

        PrintElementCl(static_cast<TypeEl>(count));
        cout << ") = {";
        ++count;
        for (auto el1 : el)
        {
            PrintElementCl(el1.first);
            cout << "  ";
        }
        cout << "}\n";
    }
    cout << '\n';
}

void Syntax::PrintBack()
{
    cout << "SetSymb.size : " << BackList.size() << endl;
    int count = 0;
    for (auto el : BackList)
    {
        cout << count << ") ���(";

        PrintElementCl(static_cast<TypeEl>(count));
        cout << ") = {";
        ++count;
        for (auto el1 : el)
        {
            PrintElementCl(el1.first);
            cout << "  ";
        }
        cout << "}\n";
    }
    cout << '\n';
}

void Syntax::PrintCompFirst1()
{
    cout << "SetSymb.size : " << First1List.size() << endl;
    int count = 0;
    for (auto el : First1List)
    {
        cout << count << ") FIRST1(";

        PrintElementCl(static_cast<TypeEl>(count));
        cout << ") = {";
        ++count;
        for (auto el1 : el)
        {
            PrintElementCl(el1.first);
            cout << "  ";
        }
        cout << "}\n";
    }
    cout << '\n';
}

void Syntax::PrintElementCl(const TypeEl &el) {}

bool Syntax::FindEl(const int &index, const TypeEl &el)
{
    for (auto obj : BeginList[index])
        if (obj.first == el)
            return 1;
    return 0;
}

void Syntax::BeginFunction()
{
    BeginList.resize(El.size());
    for (size_t i = 0; i < rules.size(); ++i) //�������� �� ���� ��������
    {
        ComputBegEl(rules[i]);                                       // ���������� ��� ��� �������� �������
        for (auto it = RegRules.begin(); it != RegRules.end(); ++it) // ������� �������� �� �����
        {
            if (FindEl(rules[i].first, it->first) == 0) // ��� ������������� ��������� � ���������
                BeginList[rules[i].first].push_back(*it);
        }

        if (!RegRules.empty())
            RegRules.clear();
    }
}

void Syntax::ComputBegEl(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule)
{                                                             // ����� �������
    set<pair<TypeEl, bool>> ListSymb = {CallFirst(obj_rule)}; // ������� ������ ��-�
lable1:
    int count = ListSymb.size(); // ��������� ���-�� ��������� ����

    for (auto it = ListSymb.begin(); it != ListSymb.end(); ++it) //������� ��� �������� ���� � ���������
        RegRules.emplace(*it);

    for (auto jt = ListSymb.begin(); jt != ListSymb.end(); ++jt)
        for (size_t i = 0; i < rules.size(); ++i) // ���������� ��� �������
            if (rules[i].first == jt->first)      // ����������� ���������, �� ���������� ������ � ������������ �� �����
            {
                pair<TypeEl, bool> p;
                p = CallFirst(rules[i]);

                ListSymb.emplace(p);
            }

    if (ListSymb.size() == count)
        return;
    else
        goto lable1;
}

pair<TypeEl, bool> Syntax::CallFirst(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule)
{
    return *(obj_rule.second.begin());
}

pair<TypeEl, bool> Syntax::CallLast(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule)
{
    return (obj_rule.second.back());
}

void Syntax::ComputEndEl(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule)
{
    set<pair<TypeEl, bool>> ListSymb = {CallLast(obj_rule)}; // ������� ��������� ��-�
lable2:
    int count = ListSymb.size(); // ��������� ���-�� ��������� ����

    for (auto it = ListSymb.begin(); it != ListSymb.end(); ++it) //������� ��� �������� ���� � ���������
        RegRules.emplace(*it);

    for (auto jt = ListSymb.begin(); jt != ListSymb.end(); ++jt)
        for (size_t i = 0; i < rules.size(); ++i) // ���������� ��� �������
            if (rules[i].first == jt->first)      // ����������� ���������, �� ���������� ������ � ������������ �� �����
            {
                pair<TypeEl, bool> p;
                p = CallLast(rules[i]);

                ListSymb.emplace(p);
            }

    if (ListSymb.size() == count)
        return;
    else
        goto lable2;
}

bool Syntax::FindEl2(const int &index, const TypeEl &el)
{
    for (auto obj : BackList[index])
        if (obj.first == el)
            return 1;
    return 0;
}

void Syntax::BackFunction()
{
    if (!RegRules.empty())
        RegRules.clear();

    BackList.resize(El.size());
    for (size_t i = 0; i < rules.size(); ++i) //�������� �� ���� ��������
    {

        ComputEndEl(rules[i]); // ���������� ��� ��� �������� �������

        for (auto it = RegRules.begin(); it != RegRules.end(); ++it) // ������� �������� �� �����
        {
            if (FindEl2(rules[i].first, it->first) == 0) // ��� ������������� ��������� � ���������
                BackList[rules[i].first].push_back(*it);
        }

        if (!RegRules.empty())
            RegRules.clear();
    }
}

void Syntax::CompFirst1Function()
{
    // ��� -  �����������
    First1List.resize(El.size());

    for (size_t i = 0; i < BeginList.size(); ++i)
        for (size_t j = 0; j < BeginList[i].size(); ++j)
            if (BeginList[i][j].second == 1)
                First1List[i].push_back(BeginList[i][j]);

    for (size_t i = 0; i < El.size(); ++i)
        if (El[i].second == 1)
            First1List[i].push_back(El[i]);
}

/*


int Syntax::accept()
{
    cout << "ACCEPT";
    exit(10);
}

void Syntax::Transfer()
{
    pair<TypeChar, TypeStore> t;
    t.first = static_cast<TypeChar>(VecIter->CToken);
    store.emplace_back(t);
    ++VecIter;
}
/*
void Syntax::Convolution()
{
    list<TypeList> temp; // ��������, ������� ����� ������ � ����������
    list<pair<TypeList, TypeStore>>::iterator it = store.end();
    --it;
    for (; it->second != _LS; --it) // ���� �� ���������� < , ������� �������
        temp.emplace_back(it->first);
    //  cout <<" it :"<< it->first << endl;
    // temp.emplace_back(it->first); // ������ ������� <
    ++it;
    store.erase(it, store.end()); // ������� ��������

    for (size_t i = 0; i < rules.size(); ++i) // ���� ��������, �� ������� ����� ��������
    {
        if (temp == rules[i].second)
        {
            pair<TypeList, TypeStore> t;
            t.first = rules[i].first;
            store.emplace_back(t);
            return;
        }
    }

    throw "��� ������� ��� ������";
}*/

// �������������
/*
void Syntax::Init()
{
    pair<TypeChar, TypeStore> el;
    el.first = _Bottom_;
    store.emplace_front(el);
}

void Syntax::StartSyntax()
{
    Init();
    VecIter = vecToken.begin();
    while (true)
    {
        (this->*table1[store.back().first][VecIter->CToken])();
        if (store.back().second == _EQ)
        {
            Transfer(); // �������
        }
        if (store.back().second == _LS)
        {
            Transfer(); // �������
        }
        /*if (store.back().second == _MR)
        {
            Convolution(); // ������
        
    }
}


void Syntax::Print()
{
    cout << "PRINT\n";
    for (auto &el : vecToken)
        cout << el.CToken << endl;
}*/

#endif