#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>

int main() {
    const char arr[30] = "[15+CX]";
    printf("%d\n", atoi(arr+1));

}

