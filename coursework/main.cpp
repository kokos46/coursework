#include <cstdio>
#include <cstdlib>
#include <locale.h>
#include <string>
#include "functions.h"
#include "queueFunc.h"

int main() {
    setlocale(LC_ALL, "");

    FILE* file = fopen("/Users/konstantin/Desktop/coursework/coursework/testBase1.dat", "rb");
    if (!file) {
        printf("Error with open!\n");
        return 1;
    }

    Record* data = new Record[4000];
    int i = 0;
    while (i < 4000 && fread(&data[i], sizeof(Record), 1, file) == 1) {
        i++;
    }
    fclose(file);
    
    Queue database;
    
    
    delete[] data;
    return 0;
}
