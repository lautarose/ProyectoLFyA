#include <iostream>
#include <unordered_set>

int main() {
    // Declarar un unordered_set de enteros
    std::unordered_set<int> mySet;

    // Insertar elementos
    mySet.insert(1);
    mySet.insert(2);
    mySet.insert(3);

    // Intentar insertar un elemento duplicado (no se añadirá)
    mySet.insert(2);

    // Imprimir los elementos del unordered_set
    for (int elem : mySet) {
        std::cout << elem << " " << std::endl;
    }

    return 0;
}
