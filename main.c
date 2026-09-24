#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int ch_to_int(const char c) {
    if (c == '0') {
        return 0;
    }
    else if (c == '1') {
        return 1;
    }
    else if (c == '2') {
        return 2;
    }
    else if (c == '3') {
        return 3;
    }
    else if (c == '4') {
        return 4;
    }
    else if (c == '5') {
        return 5;
    }
    else if (c == '6') {
        return 6;
    }
    else if (c == '7') {
        return 7;
    }
    else if (c == '8') {
        return 8;
    }
    else if (c == '9') {
        return 9;
    }
    return 0;
}


void reverse_str(char *str) {
    char temp;
    for (size_t i=0,j=strlen(str)-1; i < j; ++i,--j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}


char *convert(unsigned int data, const char type) { // assuming that data character is 0-255
    size_t index = 0;
    if (type == 'x') {
        char *result = calloc(2+1,sizeof(char));
        if (result == NULL) {
            fprintf(stderr, "Not enough RAM\n");
            exit(2);
        }
        
        if (data <= 0) {
            result[0] = '0';
            result[1] = '\0';
            return result;
        }

        while (data > 0) {
            if ((data % 16) == 10) {
                result[index] = 'a';
            }
            else if ((data % 16) == 11) {
                result[index] = 'b';
            }
            else if ((data % 16) == 12) {
                result[index] = 'c';
            }
            else if ((data % 16) == 13) {
                result[index] = 'd';
            }
            else if ((data % 16) == 14) {
                result[index] = 'e';
            }
            else if ((data % 16) == 15) {
                result[index] = 'f';
            }
            else {
                result[index] = (data % 16) + '0';
            }
            data = data / 16;
            index++;
        }
        result[index] = '\0';
        reverse_str(result);
        return result;
    }
    else if (type == 'b') {
        char *result = calloc(8+1,sizeof(char));
        if (result == NULL) {
            fprintf(stderr, "Not enough RAM\n");
            exit(2);
        }
        
        if (data <= 0) {
            result[0] = '0';
            result[1] = '\0';
            return result;
        }

        while (data > 0) {
            result[index] = ((data & 1) ? '1' : '0');
            data = data >> 1;
            index++;
        }
        result[index] = '\0';
        reverse_str(result);
        return result;
    }
    else if (type == 'd') {
        char *result = calloc(3+1,sizeof(char));
        if (result == NULL) {
            fprintf(stderr, "Not enough RAM\n");
            exit(2);
        }
        
        if (data <= 0) {
            result[0] = '0';
            result[1] = '\0';
            return result;
        }

        while (data > 0) {
            result[index] = (data % 10) + '0';
            data = data / 10;
            index++;
        }
        result[index] = '\0';
        reverse_str(result);
        return result;
    }
    return NULL;

}

void print_pat(const char *pattern, const unsigned char data) {
    unsigned char fill_char = '0';
    size_t field_width = 0;
    unsigned char type = ' ';
    char *converted = NULL;
    for (size_t i = 0; i < strlen(pattern); ++i) {
        if (pattern[i] == '%') {
            if ((i+1) >= strlen(pattern)) {
                fprintf(stderr, "Incomplete pattern\n");
                exit(1);
            }
            i++;
            if (isalpha(pattern[i])) {
                type = pattern[i];
            }
            else {
                fill_char = pattern[i];
                if ((i+1) < strlen(pattern)) {
                    i++;
                    while (isdigit(pattern[i]) && (i < strlen(pattern))) {
                        field_width = (field_width*10) + ch_to_int(pattern[i]);
                        i++;
                    }
                    if (i < strlen(pattern)) {
                        type=pattern[i];
                    }
                    else {
                        fprintf(stderr, "Incomplete pattern\n");
                        exit(1);   
                    }
                }
                else {
                    fprintf(stderr, "Incomplete pattern\n");
                    exit(1);
                }
            }
            if (type == ' ') {
                fprintf(stderr, "No datatype specified!\n");
                exit(1);
            }
            else if (type == 'x') {
                converted = convert(data, 'x');
                if (converted == NULL) {
                    fprintf(stderr, "Fatal conversion error\n");
                    exit(2);
                }
                
                if (field_width != 0) {
                    for (size_t j = strlen(converted); j < field_width; ++j) {
                        printf("%c", fill_char);
                    }
                }

                printf("%s", converted);
                
                free(converted);
                converted = NULL;
            }
            else if (type == 'X') {
                converted = convert(data, 'x');
                if (converted == NULL) {
                    fprintf(stderr, "Fatal conversion error\n");
                    exit(2);
                }
                
                if (field_width != 0) {
                    for (size_t j = strlen(converted); j < field_width; ++j) {
                        printf("%c", fill_char);
                    }
                }

                for (size_t k = 0; k < strlen(converted); ++k) {
                    printf("%c", toupper(converted[k]));   
                }

                free(converted);
                converted = NULL;
            }
            else if (type == 'b') {
                converted = convert(data, 'b');
                if (converted == NULL) {
                    fprintf(stderr, "Fatal conversion error\n");
                    exit(2);
                }
                
                if (field_width != 0) {
                    for (size_t j = strlen(converted); j < field_width; ++j) {
                        printf("%c", fill_char);
                    }
                }

                printf("%s", converted);
                
                free(converted);
                converted = NULL;
            }
            else if (type == 'd') {
                converted = convert(data, 'd');
                if (converted == NULL) {
                    fprintf(stderr, "Fatal conversion error\n");
                    exit(2);
                }
                
                if (field_width != 0) {
                    for (size_t j = strlen(converted); j < field_width; ++j) {
                        printf("%c", fill_char);
                    }
                }

                printf("%s", converted);

                free(converted);
                converted = NULL;
            }
            else {
                fprintf(stderr, "Invalid datatype specified\n");
                exit(1);
            }

        }
        else if (pattern[i] == '\\') {
            if ((i+1) >= strlen(pattern)) {
                fprintf(stderr, "Incomplete pattern\n");
                exit(1);
            }
            i++;
            if (pattern[i] == 'n') {
                printf("\n");
            }
            else if (pattern[i] == 't') {
                printf("\t");
            }
            else if (pattern[i] == 'v') {
                printf("\v");
            }
            else if (pattern[i] == 'r') {
                printf("\r");
            }
            else if (pattern[i] == 'f') {
                printf("\f");
            }
            else if (pattern[i] == '\\') {
                printf("\\");
            }
            else {
                fprintf(stderr, "Unsupported escape sequence\n");
                exit(1);
            }
        }
        else {
            printf("%c", pattern[i]);
        }
    }
}

void print_usage() {
    puts(
    "Usage: hv <pattern> <filename(optional)>\n"
    "Pattern:\n"
    "printf style pattern\n"
    "Examples:\n"
    "\"\%08b\\n\"\n"
    "\"\%x \"\n"
    );
}

void display(unsigned char sym, const char *pattern) {
    print_pat(pattern, sym);
}

int main(int argc, char *argv[]) {
    if ((argc < 2) || (argc > 3)) {
        print_usage();
        return 1;
    }
    
    char *pattern = argv[1];
    
    if (argc == 2) { // 1 argument
        char data[1];
        size_t readed;
        if (!isatty (STDIN_FILENO)) { // assuming if it is not terminal then it is pipe
            while (true) {
                readed = read(STDIN_FILENO, data, sizeof(data));
                if (readed != sizeof(data)) {
                    break;
                }
                display(data[0], pattern);
            }
        }
        else {
            fprintf(stderr, "Input data not supplied\n");
            return 1;
        }
    }
    else {
        FILE *fs = fopen(argv[2], "r");
        if (fs == NULL) {
            fprintf(stderr, "Cannot open supplied file\n");
        }
        
        fseek(fs, 0, SEEK_END);
        long file_size = ftell(fs);
        fseek(fs, 0, SEEK_SET);

        if (file_size <= 0) {
            fprintf(stderr, "Cannot read empty file\n");
            fclose(fs);
            return 1;
        }

        char temp = fgetc(fs);
        for (long i = 0; i < file_size; ++i) {
            display(temp, pattern);
            temp = fgetc(fs);
        }
        fclose(fs);

    }

    return 0;
}
