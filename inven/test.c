#include <stdio.h>
#include <stdalign.h>

int main() {
    printf("Alignment of int: %zu\n", alignof(int));    // Typically 4 bytes
    printf("Alignment of double: %zu\n", alignof(double)); // Typically 8 bytes
    printf("Alignment of char: %zu\n", alignof(char));    // Typically 1 byte
    return 0;
}

