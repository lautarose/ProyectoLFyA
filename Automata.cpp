#include "Automata.h"

Automata::Automata() : start(nullptr), end(nullptr) {}

Automata::Automata(Estado* start, Estado* end) : start(start), end(end) {}

Automata Automata::createBasicNFA(char symbol) {
    Estado* start = new Estado();
    Estado* end = new Estado();
    start->transitions[symbol].push_back(end);
    end->isFinal = true;
    return Automata(start, end);
}

Automata Automata::concatenate(const Automata& nfa1, const Automata& nfa2) {
    nfa1.end->isFinal = false;
    nfa1.end->transitions[0].push_back(nfa2.start);
    return Automata(nfa1.start, nfa2.end);
}

Automata Automata::unionNFA(const Automata& nfa1, const Automata& nfa2) {
    Estado* start = new Estado();
    start->transitions[0].push_back(nfa1.start);
    start->transitions[0].push_back(nfa2.start);

    Estado* end = new Estado();
    nfa1.end->isFinal = false;
    nfa2.end->isFinal = false;
    nfa1.end->transitions[0].push_back(end);
    nfa2.end->transitions[0].push_back(end);
    end->isFinal = true;

    return Automata(start, end);
}

Automata Automata::kleeneStar(const Automata& nfa) {
    Estado* start = new Estado();
    Estado* end = new Estado();
    start->transitions[0].push_back(nfa.start);
    start->transitions[0].push_back(end);

    nfa.end->isFinal = false;
    nfa.end->transitions[0].push_back(nfa.start);
    nfa.end->transitions[0].push_back(end);
    end->isFinal = true;

    return Automata(start, end);
}

Automata Automata::postfixToNFA(const std::string& postfix) {
    std::stack<Automata> stack;

    for (char ch : postfix) {
        if (ch == '*') {
            Automata nfa = stack.top();
            stack.pop();
            stack.push(kleeneStar(nfa));
        } else if (ch == '.') {
            Automata nfa2 = stack.top();
            stack.pop();
            Automata nfa1 = stack.top();
            stack.pop();
            stack.push(concatenate(nfa1, nfa2));
        } else if (ch == '+') {
            Automata nfa2 = stack.top();
            stack.pop();
            Automata nfa1 = stack.top();
            stack.pop();
            stack.push(unionNFA(nfa1, nfa2));
        } else {
            stack.push(createBasicNFA(ch));
        }
    }

    return stack.top();
}

void Automata::printNFA() const {
    std::set<Estado*> visited;
    std::stack<Estado*> toVisit;
    toVisit.push(start);

    std::cout << "Initial State: " << start->id << std::endl;

    std::cout << "States and Transitions:\n";
    while (!toVisit.empty()) {
        Estado* state = toVisit.top();
        toVisit.pop();

        if (visited.find(state) != visited.end()) continue;
        visited.insert(state);

        std::cout << "State " << state->id;
        if (state->isFinal) std::cout << " (Final)";
        std::cout << ":\n";

        for (const auto &transition : state->transitions) {
            char symbol = transition.first;
            for (Estado* nextState : transition.second) {
                std::cout << "  --" << (symbol == 0 ? "ε" : std::string(1, symbol)) << "--> " << nextState->id << std::endl;
                if (visited.find(nextState) == visited.end()) {
                    toVisit.push(nextState);
                }
            }
        }
    }

    std::cout << "Final State: " << end->id << std::endl;
}

void Automata::generateDotFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    file << "digraph NFA {\n";
    file << "  rankdir=LR;\n"; // Left to Right orientation
    file << "  node [shape = point]; -1;\n";
    file << "  node [shape = doublecircle]; " << end->id << ";\n";
    file << "  node [shape = circle];\n";

    file << "-1 ->"<< start->id<<";\n";
    std::set<Estado*> visited;
    std::stack<Estado*> toVisit;
    toVisit.push(start);

    while (!toVisit.empty()) {
        Estado* state = toVisit.top();
        toVisit.pop();

        if (visited.find(state) != visited.end()) continue;
        visited.insert(state);

        for (const auto &transition : state->transitions) {
            char symbol = transition.first;
            for (Estado* nextState : transition.second) {
                file << "  " << state->id << " -> " << nextState->id
                     << " [label=\"" << (symbol == 0 ? "ε" : std::string(1, symbol)) << "\"];\n";
                if (visited.find(nextState) == visited.end()) {
                    toVisit.push(nextState);
                }
            }
        }
    }

    file << "}\n";
    file.close();

    std::cout << "DOT file generated: " << filename << std::endl;
}
