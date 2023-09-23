#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_DATA_SIZE 4096

// Convert binary data to ASCII representation
char* binaryToASCII(const unsigned char* data, int length) {
    // Allocate memory for the resulting ASCII string
    char* asciiStr = malloc(length + 1);

    // Process each byte in the binary data
    for (int i = 0; i < length; i++) {
        // Check if the current byte represents a printable ASCII character or a newline/tab
        if ((data[i] >= 32 && data[i] <= 126) || data[i] == '\n' || data[i] == '\t') {
            asciiStr[i] = data[i];
        } else {
            // Replace non-printable characters with a space
            asciiStr[i] = ' ';
        }
    }
    // Null-terminate the resulting ASCII string
    asciiStr[length] = '\0';
    return asciiStr;
}

// Display an error message using the appropriate method for the current OS
void showError(const char* message) {
    struct utsname sysinfo;
    // Get OS info
    uname(&sysinfo);
    char cmd[1024];

    // Check if the OS is Linux
    if (strcmp(sysinfo.sysname, "Linux") == 0) {
        sprintf(cmd, "notify-send 'Error' '%s'", message);
    // Check if the OS is MacOS (Darwin)
    } else if (strcmp(sysinfo.sysname, "Darwin") == 0) {
        sprintf(cmd, "osascript -e 'display notification \"%s\" with title \"Error\"'", message);
    } else {
        // Handle unknown OS cases
        printf("Unknown OS. Cannot display notification.\n");
        return;
    }

    // Execute the constructed command
    system(cmd);
}

// Extract the longest valid file path from a string
char* findLongestValidPath(const char* str) {
    regex_t regex;
    regmatch_t matches[2];
    // Regular expression pattern to match file paths
    char pattern[] = "([A-Za-z]:[\\\\/][^ ]+( [^ ]+)*[^ ]*)";
    char* longestPath = NULL;

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

        // Check if the current match is longer than the previously found path
        if (!longestPath || (end - start) > strlen(longestPath)) {
            // Allocate memory for the new path and copy it
            free(longestPath);
            longestPath = malloc(end - start + 1);
            strncpy(longestPath, currentSearch + start, end - start);
            longestPath[end - start] = '\0';
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
        perror("Failed to open /proc/mounts");  // Output any system error message
        return NULL;
    }

    // Define buffers to hold values from each line in /proc/mounts
    char device[256], mountpoint[256], rest[512];

    // Loop through each line in /proc/mounts
    while (fscanf(mounts, "%s %s %s\n", device, mountpoint, rest) != EOF) {
        char potentialPath[1024];

        // Create a potential path by appending the foundPath (after skipping the Windows drive letter e.g., 'G:')
        // to the current mountpoint. This checks if the found path corresponds to any Linux mountpoint.
        sprintf(potentialPath, "%s%s", mountpoint, foundPath + 2);  // skip the 'G:'

        printf("Trying potential path: %s\n", potentialPath); // DEBUG: Log the path being checked

        // Check if the generated potential path exists in the filesystem
        if (access(potentialPath, F_OK) == 0) {
            printf("Found valid path: %s\n", potentialPath); // DEBUG: Log the successful path discovery
            fclose(mounts);  // Close the /proc/mounts file
            // Return a duplicate of the potential path, so it won't be affected by local variable going out of scope
            return strdup(potentialPath);
        }
    }

    fclose(mounts);  // Close the /proc/mounts file if no valid path was found
    return NULL;  // Return NULL if no valid path was found after checking all mount points
}



int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 2) {
        showError("Incorrect number of arguments.");
        return 1;
    }

    // Try to open the provided .lnk file
    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        showError("Error opening the .lnk file.");
        return 1;
    }

    // Read data from the .lnk file
    unsigned char data[MAX_DATA_SIZE];
    int bytesRead = fread(data, 1, MAX_DATA_SIZE, file);
    fclose(file);

    // Convert the binary data to ASCII
    char* asciiData = binaryToASCII(data, bytesRead);
    // Extract the path using regular expressions
    char* foundPath = findLongestValidPath(asciiData);

    if (foundPath) {
        // Convert backslashes to forward slashes
        for (int i = 0; foundPath[i]; i++) {
            if (foundPath[i] == '\\') {
                foundPath[i] = '/';
            }
        } 

        // Check if the path can be accessed directly
        if (access(foundPath, F_OK) != 0) {
            // If not, look for the appropriate mount point
            char* actualPath = findMountedPath(foundPath);
            if (actualPath) {
                free(foundPath);
                foundPath = actualPath;
            }
        }

        char cmd[1024];

        // Build the command to open the path
        if (strchr(foundPath, '.') == NULL) {
            sprintf(cmd, "xdg-open '%s/'", foundPath);
        } else {
            sprintf(cmd, "xdg-open '%s'", foundPath);
        }

        // Try to execute the command to open the path
        if (system(cmd) != 0) {
            char errMsg[512];
            sprintf(errMsg, "Error opening path: %s", foundPath);
            showError(errMsg);
            // If the file can't be opened, try opening the parent directory
            char* lastSlash = strrchr(foundPath, '/');
            if (lastSlash) {
                *lastSlash = '\0';
                sprintf(cmd, "xdg-open '%s/'", foundPath);
                system(cmd);
            }
        }

        free(foundPath);
    } else {
        showError("Path not found in the provided .lnk file.");
    }

    free(asciiData);
    return 0;
}

