#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_paper_positions(int row_count, char* rows[]) {
    int counter = 0;
    int prev_counter = 0;
    do {
        prev_counter = counter;
        for (int i = 0; i < row_count; i++) {
            char* current_top_row;
            char* current_row;
            char* current_bottom_row;
            if (i == 0) {
                current_top_row = malloc(sizeof(char)*(strlen(rows[0])+1));
                for (int j = 0; j < strlen(rows[0]); j++) {
                    current_top_row[j] = '.';
                }
                current_top_row[strlen(rows[0])] = '\0';
            }else {
                current_top_row = rows[i-1];
            }
            current_row = rows[i];
            if (i == row_count-1) {
                current_bottom_row = malloc(sizeof(char)*(strlen(rows[0])+1));
                for (int j = 0; j < strlen(rows[0]); j++) {
                    current_bottom_row[j] = '.';
                }
                current_bottom_row[strlen(rows[0])] = '\0';
            }else {
                current_bottom_row = rows[i+1];
            }
            char* to_change_row = malloc(sizeof(char)*(strlen(rows[0])+1));
            strcpy(to_change_row, current_row);
            char* prev_changed_row;
            int current_counter = 0;
            for (int j = 0; j < strlen(rows[0]); j++) {
                printf("%c", current_row[j]);
                if (current_row[j] == '@') {
                    if (j == 0 || current_top_row[j-1] == '.') {
                        current_counter++;
                    }
                    if (current_top_row[j] == '.') {
                        current_counter++;
                    }
                    if (j == row_count-1 || current_top_row[j+1] == '.') {
                        current_counter++;
                    }
                    if (j == 0 || current_row[j-1] == '.') {
                        current_counter++;
                    }
                    if (j == row_count-1 || current_row[j+1] == '.') {
                        current_counter++;
                    }
                    if (j == 0 || current_bottom_row[j-1] == '.') {
                        current_counter++;
                    }
                    if (current_bottom_row[j] == '.') {
                        current_counter++;
                    }
                    if (j == row_count-1 || current_bottom_row[j+1] == '.') {
                        current_counter++;
                    }
                    if (current_counter >= 5) {
                        printf("X");
                        to_change_row[j] = '.';
                        counter++;
                    }
                    current_counter = 0;
                }
            }
            printf("\n");

            if (i >= 1) {
                strcpy(rows[i-1], prev_changed_row);
            }

            if (i<row_count) {
                prev_changed_row = to_change_row;
            }



            if (i==0) {
                free(current_top_row);
            }
            if (i==row_count-1) {
                rows[i] = to_change_row;
                free(current_bottom_row);
            }
        }
    for (int i = 0; i < row_count; i++) {
        printf("%s\n", rows[i]);
    }

    }while (counter != prev_counter);

    return counter;
}

int main(int argc, char* argv[]) {
    printf("result: %d\n", find_paper_positions(argc-1, argv+1));
    return 0;
}