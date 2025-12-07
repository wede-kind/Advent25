#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int power(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        result *= base;
        exp--;
    }
    return result;
}

int is_even_digits(int number_digits) {
    if (number_digits % 2 == 0) {
        return 1;
    }
    return 0;
}

int number_digits(unsigned long number) {
    if (number == 0) {
        return 1;
    }
    int counter = 0;
    while (number > 0) {
        counter++;
        number /= 10;
    }
    return counter;
}

unsigned long* input_converter(char *complete_input) {
    int range_counter = 1;
    const int original_complete_length = (int)strlen(complete_input);
    for(int i = 0; i < original_complete_length; i++) {
        if (complete_input[i] == ',') {
            range_counter++;
            complete_input[i] = '\0';
        }
        if (complete_input[i] == '-') {
            complete_input[i] = '\0';
        }
    }
    unsigned long *range_integers = malloc(sizeof(unsigned long) * (1+range_counter*2));
    range_integers[0] = range_counter*2+1;
    int range_int_counter = 2;
    char value[20];
    char *eptr;
    strcpy(value, complete_input);
    range_integers[1] = strtod(value, &eptr);
    for(int i = 0; i < original_complete_length; i++) {
        if (complete_input[i] == '\0') {
            strcpy(value, &complete_input[i+1]);
            range_integers[range_int_counter] = strtod(value, &eptr);
            range_int_counter++;
        }
    }
    return range_integers;
}

unsigned long invalid_finder(char *complete_input){
    unsigned long counter = 0;
    unsigned long *range_integers = input_converter(complete_input);
    for (int i = 1; i < range_integers[0]; i+=2) {
        printf("lower: %lu\n", range_integers[i]);
        printf("upper: %lu\n", range_integers[i+1]);
        for (unsigned long j = range_integers[i]; j <= range_integers[i+1]; j++) {
            int number_of_digits = number_digits(j);
            int factor = power(10, number_of_digits/2);
            if (is_even_digits(number_of_digits)) {
                unsigned long first_half = j/factor;
                unsigned long flattened = first_half * factor;
                unsigned long second_half = j-flattened;
                if (first_half == second_half) {
                    printf("%lu\n", j);
                    counter+= j;
                }
            }
        }
    }
    free(range_integers);
    return counter;
}

int main(int argc, char *argv[]){
    if(argc == 2){
        printf("result: %lu", invalid_finder(argv[1]));
        return 0;
    }
    return 1;
}