#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/utsname.h>

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

void showError(const char* message) {
    struct utsname sysinfo;
    uname(&sysinfo);
    char cmd[1024];

    if (strcmp(sysinfo.sysname, "Linux") == 0) {
        sprintf(cmd, "notify-send 'Error' '%s'", message);
    } else if (strcmp(sysinfo.sysname, "Darwin") == 0) {
        sprintf(cmd, "osascript -e 'display notification \"%s\" with title \"Error\"'", message);
    } else if (strstr(sysinfo.sysname, "Win") != NULL) {
        sprintf(cmd, "msg * /v %s", message);
    } else {
        printf("Unknown OS. Cannot display notification.\n");
        return;
    }

    system(cmd);
}

char* findLongestValidPath(const char* str) {
    regex_t regex;
    regmatch_t matches[2];
    char pattern[] = "([A-Za-z]:[\\\\/][^ ]+( [^ ]+)*[^ ]*)";
    char* longestPath = NULL;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        showError("Failed to compile regex.");
        return NULL;
    }

    const char* currentSearch = str;
    while (!regexec(&regex, currentSearch, 2, matches, 0)) {
        int start = matches[1].rm_so;
        int end = matches[1].rm_eo;

        if (!longestPath || (end - start) > strlen(longestPath)) {
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
        showError("Incorrect number of arguments.");
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        showError("Error opening the .lnk file.");
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
        // Assuming if the path doesn't have a file extension, it's a directory
        if (strchr(foundPath, '.') == NULL) {
            sprintf(cmd, "xdg-open '%s/'", foundPath);
        } else {
            sprintf(cmd, "xdg-open '%s'", foundPath);
        }   

        if (system(cmd) != 0) {
            char errMsg[512];
            sprintf(errMsg, "Error opening path: %s", foundPath);
            showError(errMsg);
        }   

        free(foundPath);
    } else {
        char errMsg[512];
        sprintf(errMsg, "Path %s not found in the provided .lnk file.", foundPath);
        showError(errMsg);
    }
    free(asciiData);
    return 0;
}
