#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include <list>
#include <set>
#include <functional>

using namespace std;

// ���������� �������
enum SymbolToken
{
    LEX_DIGIT,
    LEX_CHARACTER,
    LEX_AR_OPERATION,
    LEX_ATTITUDE,
    LEX_L_BRACKET,
    LEX_R_BRACKET,
    LEX_SPACE,
    LEX_LF,
    LEX_COMMA,
    LEX_SEMICOLON,
    LEX_ERR_SYMB,
    LEX_COLON
};
//перечисление всех видов токенов(посимвольно)
// ������� ��� ��������� ������
enum TokenClass
{
    SEMICOLON,
    DIM,
    TYPE,
    AS,
    LET,
    FOR,
    EACH,
    IN,
    NEXT,
    GOTO,
    WHEN,
    LOAD,
    PUT,
    LABLE,
    ON,
    CASE,
    FAIL,
    COMMENT,
    BIN_OPERATION,
    ATTITUDE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    VARIABLE,
    CONSTANT,
    ASSIGN,
    COLON,
    DO,
    TOKEN_ERROR,
    END_MARKER
};
//определяем класс токена (само слово или его обьяснения)
enum TypeOperation
{
    BIN_SUM,
    BIN_SUB,
    BIN_MULT,
    BIN_DIV,
    BIN_MOD
};

enum TypeAttitude
{
    LESS,
    MORE,
    LESS_EQUAL,
    MORE_EQUAL,
    EQUAL,
    INEQUAL
};

enum TypeVariable
{
    TYPE_UINT,
    TYPE_MATRIX
};

enum States
{
    s_A0,
    s_A1,
    s_A2,
    s_B1,
    s_B2,
    s_B3,
    s_C1,
    s_D2,
    s_D3,
    s_D4,
    s_E1,
    s_E2,
    s_E3,
    s_F1,
    s_F2,
    s_M1,
    s_H0,
    s_H1,
    s_H2,
    s_R0,
    s_R1,
    s_R2,
    s_I1,
    s_J1,
    s_Error,
    s_Stop
};

enum SignAtt
{
    SIGN_LESS,
    SIGN_MORE,
    SIGN_EQ,
    SIGN_NOT
};

struct PairToken
{
    SymbolToken SToken;
    char value;
};

struct data_token
{
    int CToken;
    void *ptr;
    function<void(data_token &)> PrintElement;
    data_token() { ptr = nullptr; }
};

list<data_token> vecToken;
set<pair<string, bool>> SetVar;

void f25(data_token &el) { cout << "END_MARKER"; }

class StateM
{
protected:
    PairToken s;
    int discovery_register;
    int reg_const;
    string reg_name;
    int reg_num_str;
    SignAtt reg_att;
    int cur_state;

    int state_number;
    int class_number;
    typedef int (StateM::*function_pointer)();
    function_pointer **table;

    int A0a();
    int A0b();
    int A0c();
    int A0d();
    int A0e();
    int A0f();
    int A0h();
    int A0i();
    int A0j();
    int A0k();

    int A1();
    int A1a();
    int A1b();
    int A1c();
    int A1d();
    int A1e();
    int A1f();
    int A1g();
    int A1h();
    int A1i();
    int A1j();
    int A1k();
    int A1l();
    int A1m();
    int A1n();
    int A1o();
    int A1p();
    int A1q();
    int A1r();
    int A1s();
    int A1t();
    int A1u();
    int A1v();
    int A1w();
    int A1x();
    int A1y();
    int A1z();
    int A1aa();
    int A1ab();
    int A1ac();

    int A2a();
    int A2b();
    int A2c();
    int A2d();

    int B1a();
    int B1b();
    int B2a();
    int B3a();
    int B4a();

    int C1a();
    int C1b();

    int D1();
    int D1a();
    int D4();
    int D4a();
    int D4b();
    int D4c();
    int D4d();
    int D4e();
    int D4f();

    int E1();
    int E2();
    int E3();
    int E4();

    int F1();
    int F1a();

    int F2();
    int F2a();

    int M1();

    int H0();
    int H1();
    int H2a();
    int H2b();

    int R0();
    int R1();
    int R2a();
    int R2b();

    int I1();

    int J1a();
    int J1b();

    void MemoryTable();

    int Error1();
    void CreateBinOperation(TypeOperation type, function<void(data_token &)> f);
    void CreateToken(TokenClass Tc, function<void(data_token &)> f);
    void CreateConstant();
    void CreateAttitude(TypeAttitude type, function<void(data_token &)> f);
    void CreateVariable();

public:
    bool flagAnalyzer;
    set<int> SetConst;

    void transliterator(char ch);
    void StartDKA(const char *NameFile);
    void LineProcessing(const string &RegisterStr);
    friend void PrintVec(list<data_token> &obj);
    friend void PrintLableList(set<int> &obj);
    friend void PrintConst(set<int> &obj);
    StateM()
    {
        cur_state = s_A1;
        state_number = 27;
        class_number = 14;
        reg_num_str = 0;
        MemoryTable();

        for (int i = 0; i < state_number; ++i)
            for (int j = 0; j < class_number; ++j)
                table[i][j] = &StateM::Error1;

        table[s_A0][LEX_SPACE] = &StateM::A1;
        table[s_A0][LEX_DIGIT] = &StateM::F2a;
        table[s_A0][LEX_CHARACTER] = &StateM::F2a;

        table[s_A1][LEX_SPACE] = &StateM::A1;
        table[s_A1][LEX_LF] = &StateM::A1;
        table[s_A1][LEX_SEMICOLON] = &StateM::A1a;
        table[s_A1][LEX_COLON] = &StateM::A1b;
        table[s_A1][LEX_COMMA] = &StateM::A1c;
        table[s_A1][LEX_R_BRACKET] = &StateM::A1d;
        table[s_A1][LEX_L_BRACKET] = &StateM::A1e;
        table[s_A1][LEX_DIGIT] = &StateM::C1a;
        table[s_A1][LEX_AR_OPERATION] = &StateM::A1h;
        table[s_A1][LEX_ATTITUDE] = &StateM::D1;
        table[s_A1][LEX_CHARACTER] = &StateM::F1;

        table[s_A2][LEX_SEMICOLON] = &StateM::A1a;
        table[s_A2][LEX_SPACE] = &StateM::A2b;

        table[s_B1][LEX_AR_OPERATION] = &StateM::B1a;
        table[s_B1][LEX_DIGIT] = &StateM::B1b;
        table[s_B1][LEX_L_BRACKET] = &StateM::A1j;
        table[s_B1][LEX_R_BRACKET] = &StateM::A1k;
        table[s_B1][LEX_CHARACTER] = &StateM::A1u;

        table[s_B2][LEX_DIGIT] = &StateM::B2a;
        table[s_B2][LEX_CHARACTER] = &StateM::B2a;
        table[s_B2][LEX_AR_OPERATION] = &StateM::B3a;
        table[s_B2][LEX_ATTITUDE] = &StateM::B2a;
        table[s_B2][LEX_L_BRACKET] = &StateM::B2a;
        table[s_B2][LEX_R_BRACKET] = &StateM::B2a;
        table[s_B2][LEX_SPACE] = &StateM::B2a;
        table[s_B2][LEX_LF] = &StateM::B2a;
        table[s_B2][LEX_COMMA] = &StateM::B2a;
        table[s_B2][LEX_SEMICOLON] = &StateM::B2a;
        table[s_B2][LEX_ERR_SYMB] = &StateM::B2a;
        table[s_B2][LEX_COLON] = &StateM::B2a;

        table[s_B3][LEX_DIGIT] = &StateM::B2a;
        table[s_B3][LEX_CHARACTER] = &StateM::B2a;
        table[s_B3][LEX_AR_OPERATION] = &StateM::B3a;
        table[s_B3][LEX_ATTITUDE] = &StateM::B2a;
        table[s_B3][LEX_L_BRACKET] = &StateM::B2a;
        table[s_B3][LEX_R_BRACKET] = &StateM::B4a;
        table[s_B3][LEX_SPACE] = &StateM::B2a;
        table[s_B3][LEX_LF] = &StateM::B2a;
        table[s_B3][LEX_COMMA] = &StateM::B2a;
        table[s_B3][LEX_SEMICOLON] = &StateM::B2a;
        table[s_B3][LEX_ERR_SYMB] = &StateM::B2a;
        table[s_B3][LEX_COLON] = &StateM::B2a;

        table[s_C1][LEX_DIGIT] = &StateM::C1b;
        table[s_C1][LEX_SPACE] = &StateM::A1f;
        table[s_C1][LEX_LF] = &StateM::A1f;
        table[s_C1][LEX_AR_OPERATION] = &StateM::A1g;
        table[s_C1][LEX_R_BRACKET] = &StateM::A1i;
        table[s_C1][LEX_ATTITUDE] = &StateM::D4c;
        table[s_C1][LEX_COMMA] = &StateM::A1x;
        table[s_C1][LEX_R_BRACKET] = &StateM::A1z;
        table[s_C1][LEX_COLON] = &StateM::A1ab;
        table[s_C1][LEX_SEMICOLON] = &StateM::A1ac;

        table[s_D4][LEX_ATTITUDE] = &StateM::D4;
        table[s_D4][LEX_DIGIT] = &StateM::D4a;
        table[s_D4][LEX_SPACE] = &StateM::D4b;
        table[s_D4][LEX_DIGIT] = &StateM::D4d;
        table[s_D4][LEX_L_BRACKET] = &StateM::D4e;
        table[s_D4][LEX_CHARACTER] = &StateM::D4f;

        table[s_E1][LEX_DIGIT] = &StateM::E1;

        table[s_E2][LEX_DIGIT] = &StateM::E2;
        table[s_E2][LEX_ATTITUDE] = &StateM::E3;

        table[s_E3][LEX_ATTITUDE] = &StateM::E4;

        table[s_F1][LEX_CHARACTER] = &StateM::M1;
        table[s_F1][LEX_DIGIT] = &StateM::F2;
        table[s_F1][LEX_SPACE] = &StateM::A1s;
        table[s_F1][LEX_LF] = &StateM::A1s;
        table[s_F1][LEX_AR_OPERATION] = &StateM::A1aa;
        table[s_F1][LEX_R_BRACKET] = &StateM::A1v;
        table[s_F1][LEX_SEMICOLON] = &StateM::A1n;
        table[s_F1][LEX_R_BRACKET] = &StateM::A1y;

        table[s_F2][LEX_CHARACTER] = &StateM::F2;
        table[s_F2][LEX_DIGIT] = &StateM::F2;
        table[s_F2][LEX_SPACE] = &StateM::A1l;
        table[s_F2][LEX_COMMA] = &StateM::A1m;
        table[s_F2][LEX_SEMICOLON] = &StateM::A1n;
        table[s_F2][LEX_ATTITUDE] = &StateM::D1a;
        table[s_F2][LEX_AR_OPERATION] = &StateM::A1aa;
        table[s_F2][LEX_COLON] = &StateM::A1w;
        table[s_F2][LEX_R_BRACKET] = &StateM::A1y;

        table[s_H0][LEX_SPACE] = &StateM::H1;
        table[s_H0][LEX_CHARACTER] = &StateM::F2a;
        table[s_H0][LEX_DIGIT] = &StateM::F2a;

        table[s_H1][LEX_SPACE] = &StateM::H1;
        table[s_H1][LEX_DIGIT] = &StateM::H2a;

        table[s_H2][LEX_DIGIT] = &StateM::H2b;
        table[s_H2][LEX_SPACE] = &StateM::A1o;
        table[s_H2][LEX_COMMA] = &StateM::A1p;
        table[s_H2][LEX_SEMICOLON] = &StateM::A1r;

        table[s_R0][LEX_SPACE] = &StateM::R1;
        table[s_R0][LEX_CHARACTER] = &StateM::F2a;
        table[s_R0][LEX_DIGIT] = &StateM::F2a;

        table[s_R1][LEX_SPACE] = &StateM::R1;
        table[s_R1][LEX_DIGIT] = &StateM::R2a;

        table[s_R2][LEX_DIGIT] = &StateM::R2b;
        table[s_R2][LEX_SPACE] = &StateM::A1q;
        table[s_R2][LEX_LF] = &StateM::A1q;

        table[s_J1][LEX_DIGIT] = &StateM::F2a;
        table[s_J1][LEX_CHARACTER] = &StateM::F2a;
        table[s_J1][LEX_L_BRACKET] = &StateM::A1;

        table[s_I1][LEX_DIGIT] = &StateM::I1;
        table[s_I1][LEX_CHARACTER] = &StateM::I1;
        table[s_I1][LEX_AR_OPERATION] = &StateM::I1;
        table[s_I1][LEX_ATTITUDE] = &StateM::I1;
        table[s_I1][LEX_L_BRACKET] = &StateM::I1;
        table[s_I1][LEX_R_BRACKET] = &StateM::I1;
        table[s_I1][LEX_SPACE] = &StateM::I1;
        table[s_I1][LEX_LF] = &StateM::A1;
        table[s_I1][LEX_COMMA] = &StateM::I1;
        table[s_I1][LEX_SEMICOLON] = &StateM::I1;
        table[s_I1][LEX_ERR_SYMB] = &StateM::I1;
        table[s_I1][LEX_COLON] = &StateM::I1;
    }

    ~StateM()
    {
        if (!reg_name.empty())
            reg_name.clear();
    }
};

void StateM::StartDKA(const char *NameFile)
{
    flagAnalyzer = true;
    fstream buff(NameFile);

    if (!buff.is_open())
    {
        cout << "failed to open file: " << NameFile << endl;
        return;
    }

    string RegisterStr;
    while (!buff.eof())
    {
        if (!RegisterStr.empty())
            RegisterStr.clear();

        getline(buff, RegisterStr);
        RegisterStr += '\n';
        LineProcessing(RegisterStr);
    }
    data_token k;
    k.CToken = END_MARKER;
    k.PrintElement = f25;
    vecToken.emplace_back(k);
    buff.close();
}

void StateM::LineProcessing(const string &RegisterStr)
{
    for (int i = 0; i < RegisterStr.size(); ++i)
    {
        transliterator(RegisterStr[i]);
        cur_state = (this->*table[cur_state][s.SToken])();
    }
}

void StateM::MemoryTable()
{
    table = new function_pointer *[state_number];
    for (size_t i = 0; i < state_number; ++i)
        table[i] = new function_pointer[class_number];
}

#endif