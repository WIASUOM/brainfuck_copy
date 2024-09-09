#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void brainfuck_interpreter(const char *code) {
    unsigned char memory[30000] = {0};
    int pointer = 0;
    int code_pointer = 0;
    int brackets[30000];
    int bracket_count = 0;
    char input[256];
    int input_index = 0;

    while (code_pointer < strlen(code)) {
        char command = code[code_pointer];

        if (command == '>') {
            pointer++;
        } else if (command == '<') {
            pointer--;
        } else if (command == '+') {
            memory[pointer] = (memory[pointer] + 1) % 256;
        } else if (command == '-') {
            memory[pointer] = (memory[pointer] - 1) % 256;
        } else if (command == '.') {
            putchar(memory[pointer]);
        } else if (command == ',') {
            if (input_index > 0) {
                memory[pointer] = (unsigned char)input[--input_index];
            } else {
                printf("Inputu: ");
                fgets(input, sizeof(input), stdin);
                memory[pointer] = (unsigned char)input[0];
                input_index = 1; // Reset input index after reading
            }
        } else if (command == '[') {
            if (memory[pointer] == 0) {
                int brackets_open = 1;
                while (brackets_open != 0) {
                    code_pointer++;
                    if (code[code_pointer] == '[') {
                        brackets_open++;
                    } else if (code[code_pointer] == ']') {
                        brackets_open--;
                    }
                }
            } else {
                brackets[bracket_count++] = code_pointer;
            }
        } else if (command == ']') {
            if (memory[pointer] != 0) {
                code_pointer = brackets[bracket_count - 1] - 1;
            } else {
                bracket_count--;
            }
        }

        code_pointer++;
    }
}

int main() {
    char code[256];
    while (1) {
        printf("\nWrite code: ");
        fgets(code, sizeof(code), stdin);
        brainfuck_interpreter(code);
        printf("\n\nPress enter to continue: ");
        getchar();
    }
    return 0;
}
