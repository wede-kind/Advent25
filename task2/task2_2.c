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

int* get_divisors(int number) {
    int counter = 0;
    for (int i = 1; i < number; i++) {
        if (number % i == 0) {
            counter++;
        }
    }
    int *divisors = malloc(sizeof(int) * (counter+1));
    divisors[0] = counter+1;
    counter = 1;
    for (int i = 1; i < number; i++) {
        if (number % i == 0) {
            divisors[counter] = i;
            counter++;
        }
    }
    return divisors;
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
            if (j < 10) {
                continue;
            }
            //printf("current number: %lu\n", j);
            char temp_string[20];
            sprintf(temp_string, "%lu", j);
            const int number_of_digits = number_digits(j);
            int *divisors = get_divisors(number_of_digits);
            //go through every divisor
            for (int k = 0; k < divisors[0]-1; k++) {
                const unsigned long previous_counter = counter;
                const int current_divisor = divisors[k+1];
                //printf("current divisor: %lu\n", current_divisor);
                const int temp_strings_length = number_of_digits/current_divisor;
                char temp_strings[temp_strings_length][20];
                for (int l = 0; l < temp_strings_length; l++) {
                    strncpy(temp_strings[l], temp_string+(l*current_divisor), divisors[k+1]);
                    temp_strings[l][current_divisor] = '\0';
                }
                for (int l = 1; l < temp_strings_length; l++) {
                    if (strcmp(temp_strings[0], temp_strings[l]) != 0) {
                        break;
                    }
                    if (l == temp_strings_length - 1) {
                        printf("%lu\n", j);
                        counter += j;
                    }
                }
                if (previous_counter < counter) {
                    break;
                }
            }
            free(divisors);
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