//
// Created by Danil on 27.02.2022.
//

#ifndef LAB1_PRINTER_H
#define LAB1_PRINTER_H


#include <string>
#include <iostream>

class Printer {
public:
    Printer() = default;
    void print(const std::string& text, bool endline)
    {
        std::cout << text << endline ? "\n" : "";
    }
};


#endif //LAB1_PRINTER_H
