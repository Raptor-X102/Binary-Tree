#include <stdio.h>
#include <io.h>

int main() {

    if(_access("Katakuri.png", 00) == -1)
        printf("not Found");

    else
        printf("Found");

}
