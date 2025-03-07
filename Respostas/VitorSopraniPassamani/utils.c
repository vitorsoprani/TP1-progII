#include <stdio.h>

#include "utils.h"

void CleanBuffer() {
    char c = 0;
    while(c != '\n' && c != EOF) {
        c = getchar();
    }
}