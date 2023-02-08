#ifndef FUNCTIONSM_H
#define FUNCTION_H

#include "StateMachine.h"

void PrintVar(data_token &el);
void PrintConst(data_token &el);

void f1(data_token &el);
void f2(data_token &el);
void f3(data_token &el);
void f4(data_token &el);
void f5(data_token &el);
void f6(data_token &el);
void f7(data_token &el);
void f8(data_token &el);
void f9(data_token &el);
void f10(data_token &el);
void f11(data_token &el);
void f12(data_token &el);
void f13(data_token &el);
void f14(data_token &el);
void f15(data_token &el);
void f16(data_token &el);
void f17(data_token &el);
void f18(data_token &el);
void f19(data_token &el);
void f20(data_token &el);
void f21(data_token &el);
void f22(data_token &el);
void f23(data_token &el);
void f24(data_token &el);
void f26(data_token &el);
void f27(data_token &el);
void f28(data_token &el);
void f29(data_token &el);
void f30(data_token &el);
void f31(data_token &el);
void f32(data_token &el);
void f33(data_token &el);
void f34(data_token &el);
void f35(data_token &el);
void f36(data_token &el);
void f37(data_token &el);
void f38(data_token &el);
//просто обьвялвем состояние
void StateM::CreateConstant()
{
    data_token el;
    el.CToken = CONSTANT;
    el.ptr = new int(reg_const);
    el.PrintElement = PrintConst;
    vecToken.emplace_back(el);
}

void StateM::CreateBinOperation(TypeOperation type, function<void(data_token &)> f)
{
    data_token el;
    el.CToken = BIN_OPERATION;
    el.ptr = new TypeOperation(type);
    el.PrintElement = f;
    vecToken.emplace_back(el);
}

void StateM::CreateToken(TokenClass Tc, function<void(data_token &)> f)
{
    data_token el;
    el.CToken = Tc;
    el.PrintElement = f;
    vecToken.emplace_back(el);
}

void StateM::CreateVariable()
{
    data_token el;
    el.CToken = VARIABLE;
    el.ptr = new string(reg_name);
    el.PrintElement = PrintVar;
    vecToken.emplace_back(el);
}

void StateM::CreateAttitude(TypeAttitude type, function<void(data_token &)> f)
{
    data_token el;
    el.CToken = ATTITUDE;
    el.ptr = new TypeAttitude(type);
    el.PrintElement = f;
    vecToken.emplace_back(el);
}

int StateM::A0a()
{
    CreateToken(DIM, f1);
    return s_A0;
}

int StateM::A0b()
{
    CreateToken(AS, f2);
    return s_A0;
}

int StateM::A0c()
{
    CreateToken(LET, f3);
    return s_A0;
}

int StateM::A0d()
{
    if (vecToken.back().CToken != CONSTANT)
        return Error1();
    data_token el;
    el.CToken = FOR;
    el.ptr = new int(*static_cast<int *>(vecToken.back().ptr));
    el.PrintElement = f4;
    vecToken.pop_back();
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0e()
{
    CreateToken(EACH, f5);
    return s_A0;
}

int StateM::A0f()
{
    CreateToken(IN, f6);
    return s_A0;
}

int StateM::A0h()
{
    CreateToken(WHEN, f7);
    return s_A0;
}

int StateM::A0i()
{
    CreateToken(ON, f8);
    return s_A0;
}

int StateM::A0j()
{
    CreateToken(CASE, f9);
    return s_A0;
}

int StateM::A0k()
{
    CreateToken(DO, f37);
    return s_A0;
}

// пропуск пробелов в начале строки
int StateM::A1()
{
    return s_A1;
}

// semicolon
int StateM::A1a()
{
    CreateToken(SEMICOLON, f10);
    return s_A1;
}

// COLON
int StateM::A1b()
{
    CreateToken(COLON, f11);
    return s_A1;
}

// COMMA
int StateM::A1c()
{
    CreateToken(COMMA, f12);
    return s_A1;
}

int StateM::A1d()
{
    CreateToken(RIGHT_BRACKET, f13);
    return s_A1;
}

int StateM::A1e()
{
    return s_B1;
}

int StateM::A1f()
{
    CreateConstant();
    return s_A1;
}

int StateM::A1g()
{
    CreateConstant();
    return A1h();
}

int StateM::A1h()
{
    if (s.value == '+')
        CreateBinOperation(BIN_SUM, f26);
    else if (s.value == '-')
        CreateBinOperation(BIN_SUB, f27);
    else if (s.value == '*')
        CreateBinOperation(BIN_MULT, f28);
    else if (s.value == '/')
        CreateBinOperation(BIN_DIV, f29);
    else if (s.value == '%')
        CreateBinOperation(BIN_MOD, f30);

    return s_A1;
}

int StateM::A1aa()
{
    CreateVariable();
    return A1h();
}

int StateM::A1ab()
{
    CreateConstant();
    return A1h();
}

int StateM::A1ac()
{
    CreateConstant();
    return A1a();
}

int StateM::A1i()
{
    CreateConstant();
    return A1d();
}

int StateM::A1j()
{
    CreateToken(LEFT_BRACKET, f14);
    return A1e();
}

int StateM::A1l()
{
    CreateVariable();
    return s_A1;
}

int StateM::A1m()
{
    CreateVariable();
    return A1c();
}

int StateM::A1n()
{
    CreateVariable();
    return A1a();
}

int StateM::A1k()
{
    CreateToken(LEFT_BRACKET, f14);
    return A1d();
}

int StateM::A1q()
{
    data_token el;
    el.CToken = NEXT;
    el.ptr = new int(reg_const);
    el.PrintElement = f38;
    vecToken.emplace_back(el);
    return s_A1;
}

int StateM::A1s()
{
    CreateVariable();
    return s_A1;
}

int StateM::A1t()
{
    CreateVariable();
    return A1f();
}

int StateM::A1u()
{
    CreateToken(LEFT_BRACKET, f14);
    return F1();
}

int StateM::A1v()
{
    CreateVariable();
    return A1d();
}

int StateM::A1w()
{
    CreateVariable();
    return A1b();
}

int StateM::A1x()
{
    CreateConstant();
    return A1c();
}

int StateM::A1y()
{
    CreateVariable();
    return A1d();
}

int StateM::A1z()
{
    CreateConstant();
    return A1d();
}

int StateM::A2a()
{
    CreateToken(FAIL, f15);
    return s_A2;
}

// пробел после кл. слова fail
int StateM::A2b()
{
    return s_A1;
}

int StateM::A2c()
{
    data_token el;
    el.CToken = TYPE;
    el.ptr = new TypeVariable(TYPE_UINT);
    el.PrintElement = f16;
    vecToken.emplace_back(el);
    return s_A2;
}

int StateM::A2d()
{
    data_token el;
    el.CToken = TYPE;
    el.ptr = new TypeVariable(TYPE_MATRIX);
    el.PrintElement = f17;
    vecToken.emplace_back(el);
    return s_A2;
}

// (*
int StateM::B1a()
{
    if (s.value != '*')
    {
        CreateToken(TOKEN_ERROR, f18);
        flagAnalyzer = false;
    }
    return s_B2;
}

int StateM::B1b()
{
    CreateToken(LEFT_BRACKET, f14);
    return C1a();
}

// отсальные символы
int StateM::B2a()
{
    return s_B2;
}

// (* ... *
int StateM::B3a()
{
    if (s.value == '*')
        return s_B3;
    else
        return s_B2;
}

// (* ... *)
int StateM::B4a()
{
    CreateToken(COMMENT, f19);
    return s_A1;
}

// апись константы
int StateM::C1a()
{
    reg_const = s.value - '0';
    return s_C1;
}

int StateM::C1b()
{
    reg_const = reg_const * 10 + (s.value - '0');
    return s_C1;
}

int StateM::D1()
{
    if (s.value == '<')
        reg_att = SIGN_LESS;
    else if (s.value == '>')
        reg_att = SIGN_MORE;
    else if (s.value == '!')
        reg_att = SIGN_NOT;
    else if (s.value == '=')
        reg_att = SIGN_EQ;

    return s_D4;
}

int StateM::D1a()
{
    CreateVariable();
    return D1();
}

int StateM::D4()
{
    if (reg_att == SIGN_EQ && s.value == '=')
        CreateAttitude(EQUAL, f35);
    else if (reg_att == SIGN_NOT && s.value == '=')
        CreateAttitude(INEQUAL, f36);
    else if (reg_att == SIGN_LESS && s.value == '=')
        CreateAttitude(LESS_EQUAL, f33);
    else if (reg_att == SIGN_MORE && s.value == '=')
        CreateAttitude(MORE_EQUAL, f34);
    else if (reg_att == SIGN_LESS && s.value == '<')
        return s_E1;
    else
        return Error1();

    return s_A1;
}

int StateM::D4a()
{
    D4b();
    return C1a();
}

int StateM::D4b()
{
    if (reg_att == SIGN_LESS)
        CreateAttitude(LESS, f31);
    else if (reg_att == SIGN_MORE)
        CreateAttitude(MORE, f32);
    else if (reg_att == SIGN_EQ)
        CreateToken(ASSIGN, f20);
    else
        return Error1();
    return s_A1;
}

int StateM::D4c()
{
    CreateConstant();
    return D1();
}

int StateM::D4d()
{
    D4b();
    return C1a();
}

int StateM::D4e()
{
    D4b();
    return A1e();
}

int StateM::D4f()
{
    CreateToken(ASSIGN, f20);
    if (!reg_name.empty())
        reg_name.clear();
    return F2();
}

int StateM::E1()
{
    reg_const = s.value - '0';
    return s_E2;
}

int StateM::E2()
{
    reg_const = reg_const * 10 + (s.value - '0');
    return s_E2;
}

int StateM::E3()
{
    if (s.value != '>')
        return Error1();
    return s_E3;
}

int StateM::E4()
{
    if (s.value != '>')
        return Error1();

    data_token el;
    el.CToken = LABLE;
    el.ptr = new int(reg_const);
    el.PrintElement = f21;
    vecToken.emplace_back(el);
    return s_A1;
}

int StateM::F1()
{
    reg_name = s.value;

    switch (s.value)
    {
    case 'd':
        discovery_register = 0;
        break;
    case 'a':
        discovery_register = 2;
        break;
    case 'l':
        discovery_register = 3;
        break;
    case 'f':
        discovery_register = 5;
        break;
    case 'e':
        discovery_register = 7;
        break;
    case 'i':
        discovery_register = 10;
        break;
    case 'n':
        discovery_register = 11;
        break;
    case 'w':
        discovery_register = 14;
        break;
    case 'o':
        discovery_register = 17;
        break;
    case 'c':
        discovery_register = 18;
        break;
    case 't':
        discovery_register = 23;
        break;
    case 'g':
        discovery_register = 31;
        break;
    case 'p':
        discovery_register = 35;
        break;
    default:
        return s_F2;
    }

    return s_F1;
}

int StateM::F2a()
{
    vecToken.pop_back();
    return F2();
}

int StateM::F2()
{
    reg_name += s.value;
    return s_F2;
}

int StateM::M1()
{
    reg_name += s.value;
    if (discovery_register == 0 && s.value == 'i')
        ++discovery_register;
    else if (discovery_register == 1 && s.value == 'm')
        return A0a();
    else if (discovery_register == 2 && s.value == 's')
        return A0b();
    else if (discovery_register == 3 && s.value == 'e')
        ++discovery_register;
    else if (discovery_register == 4 && s.value == 't')
        return A0c();
    else if (discovery_register == 5 && s.value == 'o')
        ++discovery_register;
    else if (discovery_register == 6 && s.value == 'r')
        return A0d();
    else if (discovery_register == 7 && s.value == 'a')
        ++discovery_register;
    else if (discovery_register == 8 && s.value == 'c')
        ++discovery_register;
    else if (discovery_register == 9 && s.value == 'h')
        return A0e();
    else if (discovery_register == 10 && s.value == 'n')
        return A0f();
    else if (discovery_register == 11 && s.value == 'e')
        ++discovery_register;
    else if (discovery_register == 12 && s.value == 'x')
        ++discovery_register;
    else if (discovery_register == 13 && s.value == 't')
        return R0();
    else if (discovery_register == 14 && s.value == 'h')
        ++discovery_register;
    else if (discovery_register == 15 && s.value == 'e')
        ++discovery_register;
    else if (discovery_register == 16 && s.value == 'n')
        return A0h();
    else if (discovery_register == 17 && s.value == 'n')
        return A0i();
    else if (discovery_register == 18 && s.value == 'a')
        ++discovery_register;
    else if (discovery_register == 19 && s.value == 's')
        ++discovery_register;
    else if (discovery_register == 20 && s.value == 'e')
        return A0j();
    else if (discovery_register == 5 && s.value == 'a')
        discovery_register = 21;
    else if (discovery_register == 21 && s.value == 'i')
        ++discovery_register;
    else if (discovery_register == 22 && s.value == 'l')
        return A2a();
    else if (discovery_register == 23 && s.value == 'y')
        ++discovery_register;
    else if (discovery_register == 24 && s.value == '_')
        ++discovery_register;
    else if (discovery_register == 25 && s.value == 'u')
        ++discovery_register;
    else if (discovery_register == 26 && s.value == 'i')
        ++discovery_register;
    else if (discovery_register == 27 && s.value == 'n')
        ++discovery_register;
    else if (discovery_register == 28 && s.value == 't')
        return A2c();
    else if (discovery_register == 25 && s.value == 'm')
        ++discovery_register;
    else if (discovery_register == 26 && s.value == 'a')
        ++discovery_register;
    else if (discovery_register == 27 && s.value == 't')
        ++discovery_register;
    else if (discovery_register == 28 && s.value == 'r')
        ++discovery_register;
    else if (discovery_register == 29 && s.value == 'i')
        ++discovery_register;
    else if (discovery_register == 30 && s.value == 'x')
        return A2d();
    else if (discovery_register == 31 && s.value == 'o')
        ++discovery_register;
    else if (discovery_register == 32 && s.value == 't')
        ++discovery_register;
    else if (discovery_register == 33 && s.value == 'o')
        return H0();
    else if (discovery_register == 3 && s.value == 'o')
        ++discovery_register;
    else if (discovery_register == 4 && s.value == 'a')
        discovery_register = 34;
    else if (discovery_register == 34 && s.value == 'd')
        return J1a();
    else if (discovery_register == 35 && s.value == 'u')
        ++discovery_register;
    else if (discovery_register == 36 && s.value == 't')
        return J1b();
    else if (discovery_register == 0 && s.value == 'o')
        return A0k();
    else
        return s_F2;

    return s_F1;
}

int StateM::H0()
{
    return s_H0;
}

int StateM::H1()
{
    return s_H1;
}

int StateM::H2a()
{
    reg_const = s.value - '0';
    return s_H2;
}

int StateM::H2b()
{
    reg_const = reg_const * 10 + (s.value - '0');
    return s_H2;
}

int StateM::A1o()
{
    data_token el;
    el.CToken = GOTO;
    el.ptr = new int(reg_const);
    el.PrintElement = f22;
    vecToken.emplace_back(el);
    return s_A1;
}

int StateM::A1p()
{
    A1o();
    return A1c();
}

int StateM::A1r()
{
    A1o();
    return A1a();
}

int StateM::R0()
{
    return s_R0;
}

int StateM::R1()
{
    return s_R1;
}

int StateM::R2a()
{
    reg_const = s.value - '0';
    return s_R2;
}

int StateM::R2b()
{
    reg_const = reg_const * 10 + (s.value - '0');
    return s_R2;
}

int StateM::Error1()
{
    flagAnalyzer = false;
    data_token el;
    el.CToken = TOKEN_ERROR;
    el.PrintElement = f18;
    vecToken.emplace_back(el);
    return s_I1;
}

int StateM::I1()
{
    return s_I1;
}

int StateM::J1a()
{
    CreateToken(LOAD, f23);
    return s_J1;
}

int StateM::J1b()
{
    CreateToken(PUT, f24);
    return s_J1;
}

#endif