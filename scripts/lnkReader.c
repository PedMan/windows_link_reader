/*      \                          |                                |                                               |  |                                          |                    |                                          |                       |                    |  |                                           |                    |        |                    |                              |
               

     |               |                                 |
               
                 |                                                |            |                                   |                               |                           |                               |                           |                               |                                |                               |
          |                                  |                                     |
               
                 |                     |                                                     |                                   |                               |     |                                   |                               |     |                                   |                               |          |                                   |                               |
  |                          |                       |                    |
          |                                    |                                         |     |                    |                                    | |     |                    |                                    | |     |                    |                                    |      |     |                                                        |
     |                        |                                 |      |                                |                       |                    |                |                       |                    |                |                       |                    |                     |                       |                    |
               
                     |                                                |      |                                   |                               |                         |                               |                         |                               |                              |                               |
          |                                   |                               |                   |                                |                       |                    |          |                                |                       |                    |          |                                |                       |                    |               |                                |                                        |
               
                 |                     |
  |                                |                       |                    |            |                                |                       |                    |     |                                |                       |                    |     |                                |                       |                              |                                |
          |                               |                                         |                              |                       |                    |                           |                       |                    |                           |                       |                    |                                |                       |                    |
               
  |         |                                   PRESENTATION                                                |                                |                    |   |                                |                    |   |                                |                    |        |                                |                    |
                                                                                                                              |                               |     |                                   |                               |     |                                   |                               |          |                                   |                               |
               |                             /                 \                          |                                                                              |                               |     |                                   |                               |     |                                   |                               |          |                                   |                               |
               
       |                               LNK Reader is a command-line tool 

                                  designed to read and extract information 

                               from Windows shortcut (.lnk) files. It provides  
                |                                                                          |               |                                           |               |                                           |                    |                                           |

                          /                      |    v    |                    \
               
            insights into the target file or directory paths and supports educational purposes.   |                                |                                          |      |                                |                                          |      |                                |                                          |           |                                |  
     |                  !      |                                   |     |                                |                       |                    |                |                       |                    |                |                       |                    |                    |                                           |
                               |                                   |     |                  
                  |            |                   Anyway          !                        |                                         |                                |                       |                    |                |                       |                    |                |                       |                    |                    |
               
             |                      |                 have                                                 |                        |                                         |                                |                       |                    |                |                       |                    |                |                       |                    |                     |                                           |
               

                |                                  FUN         |                        |                                         |                                |                       |                    |                |                       |                    |                |                       |                    |                    |                                                                      |
               
                                                        =)
               #
                               |                      or                                       |                                                            |                    |                |                       |                    |                |                       |                    |                    |                                           |
               

             |                              |       DIE ! ! !        |                       |                            |                |                       |                    |                |                       |                    |                    |                                           |#     |                        |                                         |                                |
               #
                                                    !                                       |                                |                    |  |                                |                    |  |                                |                    |       |                                |                    |
               
     |               |                                 !
               
                 |                                                |            |                                   |                               |                           |                               |                           |                               |                                |                               |
          |                                  !                                     |
               
                 |                     |                                                     |                                   |                               |     |                                   |                               |     |                                   |                               |          |                                   |                               |
  |                          |                       |                    !
          |                                    |                                         |     |                    |                                    | |     |                    |                                    | |     |                    |                                    |      |     |                    |                                    |
     |                        |                                 |      |                                |                       |                    |                |                       |                    |                |                       |                    |                    |                                           |
               
                     |                                                |      |                                   |                               |                         |                               |                         |                               |                              |                               |
          |                                   |                               |                   |                                |                       |                    |          |                                |                       |                    |          |                                |                       |                    |               |                                                                |
_ _  _ ____ ___ ____ _    _    ____ ___ _ ____ _  _
| |\ | [__   |  |__| |    |    |__|  |  | |  | |\ |
| | \| ___]  |  |  | |___ |___ |  |  |  | |__| | \|
    
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <errno.h>

/*
___  ____ _ _ _ ____ ____    ___  _    ____ _  _ ___
|__] |  | | | | |___ |__/    |__] |    |__| |\ |  |
|    |__| |_|_| |___ |  \    |    |___ |  | | \|  |
                
#OPENING | https://www.youtube.com/watch?v=_85LaeTCtV8 :3
*/

#define MAX_DATA_SIZE 4096

// Global variable to hold the notification command
static char notifyCmdFormat[256] = {0};

// Convert binary data to ASCII representation
static char* binaryToASCII(const unsigned char* data, int length) {
    char* asciiStr = (char*) malloc(length + 1);
    if (!asciiStr) {
        perror("Failed to allocate memory for asciiStr");
        exit(1);
    }
    for (int i = 0; i < length; i++) {
        asciiStr[i] = (data[i] >= 32 && data[i] <= 126) || data[i] == '\n' || data[i] == '\t' ? data[i] : ' ';
    }
    asciiStr[length] = '\0';
    return asciiStr;
}

// Display an error message using the appropriate method for the OS
static void showError(const char* message) {
    if (!notifyCmdFormat[0]) {
        // Fallback if not initialized
        fprintf(stderr, "Error: %s\n", message ? message : "Unknown error");
        return;
    }
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), notifyCmdFormat, message ? message : "Unknown error");
    (void)system(cmd);
}

static char* findLongestValidPath(const char* str) {
    regex_t regex;
    regmatch_t matches[2];
    // Regular expression pattern to match Windows-like file paths
    char pattern[] = "([A-Za-z]:[\\\\/][^ ]+( [^ ]+)*[^ ]*)";
    char* longestPath = NULL;
    int longestPathLen = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        showError("Failed to compile regex.");
        return NULL;
    }

    const char* currentSearch = str;
    while (!regexec(&regex, currentSearch, 2, matches, 0)) {
        int start = matches[1].rm_so;
        int end   = matches[1].rm_eo;
        int currentMatchLen = end - start;

        if (currentMatchLen > longestPathLen) {
            free(longestPath);
            longestPath = (char*)malloc((size_t)currentMatchLen + 1);
            if (!longestPath) {
                regfree(&regex);
                showError("malloc failed for longestPath.");
                return NULL;
            }
            strncpy(longestPath, currentSearch + start, (size_t)currentMatchLen);
            longestPath[currentMatchLen] = '\0';
            longestPathLen = currentMatchLen;
        }
        currentSearch += end;
    }

    regfree(&regex);
    return longestPath;
}

static char* findMountedPath(char* foundPath) {
    FILE *mounts = fopen("/proc/mounts", "r");
    if (!mounts) {
        perror("Failed to open /proc/mounts");
        return NULL;
    }

    char device[256], mountpoint[256], rest[512];

    // Skip the drive letter and colon 
    char* corePath = foundPath + 2;

    while (fscanf(mounts, "%255s %255s %511s\n", device, mountpoint, rest) != EOF) {
        char potentialPath[1024];
        snprintf(potentialPath, sizeof(potentialPath), "%s%s", mountpoint, corePath);

        printf("Trying potential path: %s\n", potentialPath);

        if (access(potentialPath, F_OK) == 0) {
            printf("Found valid path: %s\n", potentialPath);
            fclose(mounts);
            return strdup(potentialPath);
        }
    }

    fclose(mounts);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (!notifyCmdFormat[0]) {
        struct utsname sysinfo;
        if (uname(&sysinfo) == 0) {
            if (strcmp(sysinfo.sysname, "Linux") == 0) {
                // Requires libnotify-bin (notify-send)
                strcpy(notifyCmdFormat, "notify-send 'Error' '%s'");
            } else if (strcmp(sysinfo.sysname, "Darwin") == 0) {
                // macOS notification via AppleScript
                strcpy(notifyCmdFormat, "osascript -e 'display notification \"%s\" with title \"Error\"'");
            }
        }
    }

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
    int bytesRead = (int)fread(data, 1, MAX_DATA_SIZE, file);
    fclose(file);

    char* asciiData = binaryToASCII(data, bytesRead);
    char* foundPath = findLongestValidPath(asciiData);

    if (foundPath) {
        // Normalize backslashes to forward slashes
        for (int i = 0; foundPath[i]; i++) {
            if (foundPath[i] == '\\') foundPath[i] = '/';
        }

        // If path does not exist, try mapping through Linux mount points
        if (access(foundPath, F_OK) != 0) {
            char* actualPath = findMountedPath(foundPath);
            if (actualPath) {
                free(foundPath);
                foundPath = actualPath;
            }
        }

        char cmd[1024];

        // Choose opener per-OS
        #ifdef __APPLE__
            snprintf(cmd, sizeof(cmd), "open '%s'", foundPath);
        #else
            // Linux default
            if (strchr(foundPath, '.') == NULL) {
                // Likely a directory → ensure trailing slash
                snprintf(cmd, sizeof(cmd), "xdg-open '%s/'", foundPath);
            } else {
                snprintf(cmd, sizeof(cmd), "xdg-open '%s'", foundPath);
            }
        #endif

        if (system(cmd) != 0) {
            char errMsg[512];
            snprintf(errMsg, sizeof(errMsg), "Error opening path: %s", foundPath);
            showError(errMsg);

            // Fallback: open parent directory
            char* lastSlash = strrchr(foundPath, '/');
            if (lastSlash) {
                *lastSlash = '\0';
                #ifdef __APPLE__
                    snprintf(cmd, sizeof(cmd), "open '%s/'", foundPath);
                #else
                    snprintf(cmd, sizeof(cmd), "xdg-open '%s/'", foundPath);
                #endif
                (void)system(cmd);
            }
        }

        free(foundPath);
    } else {
        showError("Path not found in the provided .lnk file.");
    }

    free(asciiData);
    return 0;
}
