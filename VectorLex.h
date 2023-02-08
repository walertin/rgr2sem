#ifndef VECTORLEX_H
#define VECTORLEX_H

#include "StateMachine.h"

void PrintList(list<data_token> &obj)
{
    cout << "size Vector: " << obj.size() << endl;
    cout << "Token                           Value\n";
    for (auto &el : obj)
    {
        cout.width(15);
        el.PrintElement(el);
        cout << '\n';
    }
}

void PrintVar(data_token &el)
{
    cout << "VARIABLE";
    cout.width(20);
    cout << *static_cast<string *>(el.ptr);
}

void PrintConst(data_token &el)
{
    cout << "CONSTANT";
    cout.width(20);
    cout << *static_cast<int *>(el.ptr);
}

void f1(data_token &el) { cout << "DIM"; }
void f2(data_token &el) { cout << "AS"; }
void f3(data_token &el) { cout << "LET"; }
void f4(data_token &el)
{
    cout << "FOR";
    cout.width(20);
    cout << *static_cast<int *>(el.ptr);
}
void f5(data_token &el) { cout << "EACH"; }
void f6(data_token &el) { cout << "IN"; }
void f7(data_token &el) { cout << "WHEN"; }
void f8(data_token &el) { cout << "ON"; }
void f9(data_token &el) { cout << "CASE"; }
void f10(data_token &el) { cout << "SEMICOLON"; }
void f11(data_token &el) { cout << "COLON"; }
void f12(data_token &el) { cout << "COMMA"; }
void f13(data_token &el) { cout << "RIGHT_BRACKET"; }
void f14(data_token &el) { cout << "LEFT_BRACKET"; }
void f15(data_token &el) { cout << "FAIL"; }
void f16(data_token &el)
{
    cout << "TYPE";
    cout.width(20);
    cout << "UINT";
}
void f17(data_token &el)
{
    cout << "TYPE";
    cout.width(20);
    cout << "MATRIX";
}
void f18(data_token &el) { cout << "TOKEN_ERROR"; }
void f19(data_token &el) { cout << "COMMENT"; }
void f20(data_token &el) { cout << "ASSIGN"; }
void f21(data_token &el)
{
    cout << "LABLE";
    cout.width(10);
    cout << *static_cast<int *>(el.ptr);
}
void f22(data_token &el)
{
    cout << "GOTO";
    cout.width(20);
    cout << *static_cast<int *>(el.ptr);
}
void f23(data_token &el) { cout << "LOAD"; }
void f24(data_token &el) { cout << "PUT"; }
void f26(data_token &el)
{
    cout << "BIN_OPERATION";
    cout.width(20);
    cout << "SUM";
}

void f27(data_token &el)
{
    cout << "BIN_OPERATION";
    cout.width(20);
    cout << "SUB";
}
void f28(data_token &el)
{
    cout << "BIN_OPERATION";
    cout.width(20);
    cout << "MULT";
}
void f29(data_token &el)
{
    cout << "BIN_OPERATION";
    cout.width(20);
    cout << "DIV";
}
void f30(data_token &el)
{
    cout << "BIN_OPERATION";
    cout.width(20);
    cout << "MOD";
}
void f31(data_token &el)
{
    cout << "ATTITUDE";
    cout.width(20);
    cout << "LESS";
}
void f32(data_token &el)
{
    cout << "ATTITUDE";
    cout.width(20);
    cout << "MORE";
}
void f33(data_token &el)
{
    cout << "ATTITUDE";
    cout.width(20);
    cout << "LESS_EQUAL";
}
void f34(data_token &el)
{
    cout << "ATTITUDE";
    cout.width(20);
    cout << "MORE_EQUAL";
}
void f35(data_token &el)
{
    cout << "ATTITUDE";
    cout.width(20);
    cout << "EQUAL";
}
void f36(data_token &el)
{
    cout << "ATTITUDE";
    cout.width(20);
    cout << "INEQUAL";
}
void f37(data_token &el) { cout << "DO"; }
void f38(data_token &el)
{
    cout << "NEXT";
    cout.width(20);
    cout << *static_cast<int *>(el.ptr);
}

void PrintVariableSet(set<pair<string, bool>> &obj) // ��� ����������
{
    cout << "{ ";
    for (set<pair<string, bool>>::iterator it = obj.begin(); it != obj.end(); ++it)
        cout << it->first << " ";
    cout << "}";
}

void PrintConst(set<long double> &obj)
{
    cout << "{ ";
    for (set<long double>::iterator it = obj.begin(); it != obj.end(); ++it)
        cout << *it << "   ";
    cout << "}";
}

#endif