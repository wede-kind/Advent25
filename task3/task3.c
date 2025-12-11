#include <stdio.h>
#include <string.h>

int turn_on_batteries(int bank_count, char* banks[]) {
    int counter = 0;
    for (int i = 0; i < bank_count; i++) {
        int max1 = 0;
        int max2 = 0;
        for (int j = 0; j < strlen(banks[i]); j++) {
            const int current_char = banks[i][j] - '0';
            if (current_char > max1 && j < strlen(banks[i])-1) {
                max1 = current_char;
                max2 = 0;
            }else if (current_char > max2) {
                max2 = current_char;
            }
        }
        counter+= max1*10 + max2;
    }
    return counter;
}

int main (int argc, char* argv[]) {
    printf("result: %d\n", turn_on_batteries(argc-1, argv+1));
    return 0;
}