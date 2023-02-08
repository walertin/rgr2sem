#include "analyzer.h"
#include "Syntax.h"
int main(int argc, char *argv[])
{

    setlocale(LC_ALL, "Russian");

    if (argc != 2)
    {
        cout << "Format: ./executable_name(.exe) input_file_name(.txt)" << endl;
        return 1;
    }
//расписываем как будет работать программа при чтение файла
    StateM programm1;
    programm1.StartDKA(argv[1]);
    PrintList(vecToken);
    if (programm1.flagAnalyzer == true)
        cout << "ANALYZER: accept" << endl;
    else
    {
        cout << "ANALYZER: error" << endl;
        return -1;
    }

    Syntax programm2;
    programm2.StartSyntax();
    if (programm2.flagSyntax == true)
        cout << "SYNTAX: accept" << endl;
    else
    {
        cout << "SYNTAX: error" << endl;
        return -2;
    }

    return 0;
}
