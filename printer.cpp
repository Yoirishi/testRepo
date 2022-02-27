//
// Created by Danil on 27.02.2022.
//

#include "printer.h"


bool test()
{
    std::string testString = "try to print this string";
    std::cout << testString<< std::endl;
    Printer printer;

    printer.print(testString, false);
}