#include <stdio.h>

#include "utils.h"

void CleanBuffer() {
    while(getchar() != '\n') {};
}