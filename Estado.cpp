#include "Estado.h"

int stateIdCounter = 0;

Estado::Estado() : isFinal(false) {
    id = stateIdCounter++;
}
