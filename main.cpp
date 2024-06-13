#include "Automata.h"
#include "Conversion.h"

int main() {
    std::cout << "Ingrese la expresion regular:\n";
    std::string infix, dotfile;
    std::cin >> infix;
    std::cout << "Nombre del archivo DOT:\n";
    std::cin >> dotfile;

    dotfile = dotfile + ".dot";
    std::string postfix = infixToPostfix(infix);
    Automata nfa = Automata::postfixToNFA(postfix);

    std::cout << "NFA creado para la expresión: " << infix << std::endl;
    nfa.printNFA();

    nfa.generateDotFile(dotfile);

    return 0;
}
