#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "Estado.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <set>

class Automata {
public:
    Estado* start;
    Estado* end;

    Automata();
    Automata(Estado* start, Estado* end);

    static Automata createBasicNFA(char symbol);
    static Automata concatenate(const Automata& nfa1, const Automata& nfa2);
    static Automata unionNFA(const Automata& nfa1, const Automata& nfa2);
    static Automata kleeneStar(const Automata& nfa);
    static Automata postfixToNFA(const std::string& postfix);

    void printNFA() const;
    void generateDotFile(const std::string& filename) const;
};

#endif // AUTOMATA_H