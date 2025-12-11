#include <stdio.h>
#include <string.h>

unsigned long power(int base, int exp) {
    unsigned long result = 1;
    while (exp > 0) {
        result *= base;
        exp--;
    }
    return result;
}

unsigned long turn_on_batteries(int bank_count, char* banks[]) {
    unsigned long counter = 0;
    for (int i = 0; i < bank_count; i++) {
       const char* current_bank = banks[i];
        printf("current bank: %s\n", current_bank);
        int max_batteries[12] = {0};
        for (int j = 0; j < strlen(current_bank); j++) {
            const int current_char = current_bank[j] - '0';
            for (int k = 0; k < 12; k++) {
                if (current_char > max_batteries[k] && j <= strlen(current_bank)-(12-k)) {
                    max_batteries[k] = current_char;
                    for (int l = k+1; l < 12; l++) {
                        max_batteries[l] = 0;
                    }
                    break;
                }
            }
        }
        unsigned long current_result = 0;
        for (int j = 0; j < 12; j++) {
            current_result += max_batteries[j]*power(10, 12-j-1);
        }
        printf("current banks result: %lu\n", current_result);
        counter+=current_result;
    }
    return counter;
}

int main (int argc, char* argv[]) {
    printf("result: %lu\n", turn_on_batteries(argc-1, argv+1));
    return 0;
}