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
#include <sys/utsname.h>
#include <dirent.h>
#include <unistd.h>


/*
___  ____ _ _ _ ____ ____    ___  _    ____ _  _ ___
|__] |  | | | | |___ |__/    |__] |    |__| |\ |  |
|    |__| |_|_| |___ |  \    |    |___ |  | | \|  |
                

#OPENING | https://www.youtube.com/watch?v=_85LaeTCtV8 :3

*/


#define MAX_DATA_SIZE 4096


// Global variable to hold the notification command
char notifyCmdFormat[256] = {0};

// Convert binary data to ASCII representation
char* binaryToASCII(const unsigned char* data, int length) {
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

// Display an error message using the appropriate method for the current OS
void showError(const char* message) {
    if (!notifyCmdFormat[0]) {
        printf("Unknown OS. Cannot display notification.\n");
        return;
    }

    char cmd[1024];
    sprintf(cmd, notifyCmdFormat, message);
    system(cmd);
}

char* findLongestValidPath(const char* str) {
    regex_t regex;
    regmatch_t matches[2];
    // Regular expression pattern to match file paths
    char pattern[] = "([A-Za-z]:[\\\\/][^ ]+( [^ ]+)*[^ ]*)";
    char* longestPath = NULL;
    int longestPathLen = 0;

    // Compile the regular expression
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        showError("Failed to compile regex.");
        return NULL;
    }

    const char* currentSearch = str;
    // Search for matches repeatedly, aiming to find the longest match
    while (!regexec(&regex, currentSearch, 2, matches, 0)) {
        int start = matches[1].rm_so;
        int end = matches[1].rm_eo;
        int currentMatchLen = end - start;

        // Check if the current match is longer than the previously found path
        if (currentMatchLen > longestPathLen) {
            free(longestPath);
            longestPath = malloc(currentMatchLen + 1);
            strncpy(longestPath, currentSearch + start, currentMatchLen);
            longestPath[currentMatchLen] = '\0';
            longestPathLen = currentMatchLen;
        }
        // Move the search starting point after the current match
        currentSearch += end;
    }

    // Free up the memory used by the regex
    regfree(&regex);
    return longestPath;
}

char* findMountedPath(char* foundPath) {
    // Open the /proc/mounts file which lists all mounted filesystems on Linux
    FILE *mounts = fopen("/proc/mounts", "r");
    if (!mounts) {
        perror("Failed to open /proc/mounts");
        return NULL;
    }

    // Define buffers to hold values from each line in /proc/mounts
    char device[256], mountpoint[256], rest[512];

    // Extract the core part of the path without the drive letter (e.g., skip 'G:')
    char* corePath = foundPath + 2;

    // Loop through each line in /proc/mounts
    while (fscanf(mounts, "%s %s %s\n", device, mountpoint, rest) != EOF) {
        char potentialPath[1024];

        // Create a potential path by appending the corePath to the current mountpoint.
        sprintf(potentialPath, "%s%s", mountpoint, corePath);

        printf("Trying potential path: %s\n", potentialPath);

        // Check if the generated potential path exists in the filesystem
        if (access(potentialPath, F_OK) == 0) {
            printf("Found valid path: %s\n", potentialPath);
            fclose(mounts);
            return strdup(potentialPath);
        }
    }

    fclose(mounts);
    return NULL;
}


/*
___  ____ ____ ____ ____ ____ ____ 
|__] |__/ |  | |    |___ [__  [__  
|    |  \ |__| |___ |___ ___] ___] 

*/

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments are passed to the program
    if (argc != 2) {
        showError("Incorrect number of arguments.");
        return 1;
    }

    // Open the .lnk file for reading in binary mode
    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        showError("Error opening the .lnk file.");
        return 1;
    }

    unsigned char data[MAX_DATA_SIZE];
    
    // Read the contents of the .lnk file into the data buffer
    int bytesRead = fread(data, 1, MAX_DATA_SIZE, file);
    
    // Close the file as it's no longer needed
    fclose(file);

    // Convert the binary data to ASCII representation
    char* asciiData = binaryToASCII(data, bytesRead);

    // Extract the longest valid file path from the ASCII data
    char* foundPath = findLongestValidPath(asciiData);

    // Detect the OS and set up the notification command format if not set already
    if (!notifyCmdFormat[0]) {
        struct utsname sysinfo;
        uname(&sysinfo);
        if (strcmp(sysinfo.sysname, "Linux") == 0) {
            strcpy(notifyCmdFormat, "notify-send 'Error' '%s'");
        } else if (strcmp(sysinfo.sysname, "Darwin") == 0) {
            strcpy(notifyCmdFormat, "osascript -e 'display notification \"%s\" with title \"Error\"'");
        }
    }

    // If a path is found within the .lnk file
    if (foundPath) {
        // Convert any backslashes to forward slashes
        for (int i = 0; foundPath[i]; i++) {
            if (foundPath[i] == '\\') {
                foundPath[i] = '/';
            }
        } 

        // Check if the extracted path exists in the filesystem
        if (access(foundPath, F_OK) != 0) {
            // If not, attempt to find a corresponding mounted path
            char* actualPath = findMountedPath(foundPath);
            if (actualPath) {
                free(foundPath);
                foundPath = actualPath;
            }
        }

        char cmd[1024];
        
        // Determine if the path represents a directory or file based on the presence of an extension
        if (strchr(foundPath, '.') == NULL) {
            sprintf(cmd, "xdg-open '%s/'", foundPath);
        } else {
            sprintf(cmd, "xdg-open '%s'", foundPath);
        }

        // Try to open the extracted path using the OS default program
        if (system(cmd) != 0) {
            char errMsg[512];
            sprintf(errMsg, "Error opening path: %s", foundPath);
            showError(errMsg);
            
            // If there's an error, try opening the parent directory of the path
            char* lastSlash = strrchr(foundPath, '/');
            if (lastSlash) {
                *lastSlash = '\0';
                sprintf(cmd, "xdg-open '%s/'", foundPath);
                system(cmd);
            }
        }

        // Free the memory allocated for the path
        free(foundPath);
    } else {
        showError("Path not found in the provided .lnk file.");
    }

    // Free the memory allocated for the ASCII representation
    free(asciiData);
    return 0;
}
