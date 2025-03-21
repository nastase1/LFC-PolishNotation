﻿#include <iostream>
#include <string>
#include <fstream>
#include <stack>

int prioritate(char op) {
    if (op == '(')
        return 0;
    if (op == '|')
        return 1;
    if (op == '.')
        return 2;
    if (op == '*')
        return 3;
    return -1;
}

bool verificaParanteze(const std::string& expresie) {
    std::stack<char> paranteze;
    for (char c : expresie) {
        if (c == '(') {
            paranteze.push(c);
        }
        else if (c == ')') {
            if (paranteze.empty()) {
                return false; 
            }
            paranteze.pop();
        }
    }
    return paranteze.empty(); 
}

std::string FormaPoloneza(std::string& expresie) {
    std::string fp;
    std::stack<char> operatori;

    if (!verificaParanteze(expresie)) {
        return "Eroare: Parantezele sunt plasate incorect!";
    }

    for (size_t i = 0; i < expresie.size(); ++i) {
        char curent = expresie[i];

        if (isalnum(curent)) {
            fp.push_back(curent);

            if (i + 1 < expresie.size() && (isalnum(expresie[i + 1]) || expresie[i + 1] == '(')) {
                while (!operatori.empty() && prioritate(operatori.top()) >= prioritate('.')) {
                    fp.push_back(operatori.top());
                    operatori.pop();
                }
                operatori.push('.');
            }
        }
        else if (curent == '(') {
            operatori.push(curent);
        }
        else if (curent == ')') {
            while (!operatori.empty() && operatori.top() != '(') {
                fp.push_back(operatori.top());
                operatori.pop();
            }
            if (!operatori.empty())
                operatori.pop();  
        }
        else if (curent == '*' || curent == '|' || curent == '.') {
            while (!operatori.empty() && prioritate(operatori.top()) >= prioritate(curent)) {
                fp.push_back(operatori.top());
                operatori.pop();
            }
            operatori.push(curent);
        }
    }

    while (!operatori.empty()) {
        fp.push_back(operatori.top());
        operatori.pop();
    }
    return fp;
}

int main() {
    std::string expresie;
    std::ifstream f("fisier.in");
    f >> expresie;
    std::cout << "Expresia este: " << expresie << "\n";
    std::string rezultat = FormaPoloneza(expresie);
    std::cout << "Expresia dupa forma normala poloneza: " << rezultat << "\n";
    return 0;
}
