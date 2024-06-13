#ifndef ESTADO_H
#define ESTADO_H

#include <map>
#include <vector>

class Estado {
public:
    int id;
    std::map<char, std::vector<Estado*>> transitions;
    bool isFinal;

    Estado();
};

#endif // ESTADO_H
