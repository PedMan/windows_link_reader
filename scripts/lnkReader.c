#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_DATA_SIZE 4096

char* binaryToASCII(const unsigned char* data, int length) {
    char* asciiStr = malloc(length + 1);
    for (int i = 0; i < length; i++) {
        if ((data[i] >= 32 && data[i] <= 126) || data[i] == '\n' || data[i] == '\t') {
            asciiStr[i] = data[i];
        } else {
            asciiStr[i] = ' ';
        }
    }
    asciiStr[length] = '\0';
    return asciiStr;
}

char* findLongestValidPath(const char* str) {
    regex_t regex;
    regmatch_t matches[2];
    char pattern[] = "([A-Za-z]:[\\\\/][^ ]+?[\\\\/][^ ]+)";
    char* longestPath = NULL;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        system("zenity --error --text='Failed to compile regex.'");
        return NULL;
    }

    const char* currentSearch = str;
    while (!regexec(&regex, currentSearch, 2, matches, 0)) {
        int start = matches[1].rm_so;
        int end = matches[1].rm_eo;
        
        if(!longestPath || (end - start) > strlen(longestPath)) {
            free(longestPath);
            longestPath = malloc(end - start + 1);
            strncpy(longestPath, currentSearch + start, end - start);
            longestPath[end - start] = '\0';
        }
        currentSearch += end;
    }

    regfree(&regex);
    return longestPath;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        system("zenity --error --text='Incorrect number of arguments.'");
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        system("zenity --error --text='Error opening the .lnk file.'");
        return 1;
    }

    unsigned char data[MAX_DATA_SIZE];
    int bytesRead = fread(data, 1, MAX_DATA_SIZE, file);
    fclose(file);

    char* asciiData = binaryToASCII(data, bytesRead);
    char* foundPath = findLongestValidPath(asciiData);

    if (foundPath) {
        for (int i = 0; foundPath[i]; i++) {
            if (foundPath[i] == '\\') {
                foundPath[i] = '/';
            }
        }

        char cmd[1024];
        sprintf(cmd, "xdg-open '%s'", foundPath);
        if (system(cmd) != 0) {
            char errMsg[512];
            sprintf(errMsg, "zenity --error --text='Error opening path: %s'", foundPath);
            system(errMsg);
        }

        free(foundPath);
    } else {
        system("zenity --error --text='Path not found in the provided .lnk file.'");
    }

    free(asciiData);
    return 0;
}
