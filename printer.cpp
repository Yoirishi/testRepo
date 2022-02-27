//
// Created by Danil on 27.02.2022.
//

#include "printer.h"


bool test()
{
    std::string testString = "try to print this string";
    std::cout << testString<< std::endl;
    Printer printer;

    printer.print(testString, true);

    char answer;
    std::cout << "are strings above havent diffs?[y/n]" << std::endl;
    do
    {
        std::cin >> answer;
        if (answer != 'y' || answer != 'n')
        {
            std::cout << "incorrect answer" << std::endl;
        }
    }while (answer != 'y' || answer != 'n');
}