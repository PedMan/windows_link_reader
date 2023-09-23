#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#define MAX_DATA_SIZE 4096

char* bytesToHexString(const unsigned char* bytes, int length) {
    char* hexStr = malloc(2 * length + 1);
    for (int i = 0; i < length; ++i) {
        sprintf(hexStr + 2 * i, "%02X", bytes[i]);
    }
    hexStr[2 * length] = '\0';
    return hexStr;
}

char* hexToASCII(const char* hexStr) {
    int length = strlen(hexStr) / 2;
    char* asciiStr = malloc(length + 1);
    for (int i = 0; i < length; i++) {
        sscanf(hexStr + 2 * i, "%2hhx", &asciiStr[i]);
    }
    asciiStr[length] = '\0';
    return asciiStr;
}

char* findPathInHexString(const char* hexStr) {
    const char* potentialDrives = "4142434445464748494A4B4C4D4E4F505152535455565758595A"; // ABCDEFGHIJKLMNOPQRSTUVWXYZ in hex
    for (int i = 0; i < strlen(potentialDrives); i += 2) {
        char pattern[5];
        strncpy(pattern, potentialDrives + i, 2);
        pattern[2] = '3'; // This is for ":"
        pattern[3] = 'A'; // This is for "\"
        pattern[4] = '\0';

        char* startOfPath = strstr(hexStr, pattern);
        if (startOfPath) {
            char* endOfPath = strstr(startOfPath, "2000"); // This is for space
            if (endOfPath) {
                int pathLength = endOfPath - startOfPath;
                char* path = malloc(pathLength + 1);
                strncpy(path, startOfPath, pathLength);
                path[pathLength] = '\0';
                char* asciiPath = hexToASCII(path);
                free(path);
                return asciiPath;
            }
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    if (argc != 2) {
        printf("Usage: %s <path_to_lnk_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    unsigned char data[MAX_DATA_SIZE];
    int bytesRead = fread(data, 1, MAX_DATA_SIZE, file);
    fclose(file);

    char* hexStr = bytesToHexString(data, bytesRead);
    char* foundPath = findPathInHexString(hexStr);
    if (foundPath) {
        printf("Chemin trouvé: %s\n", foundPath);   

        // Remplacer les backslashes par des slashes pour la compatibilité avec Linux.
        for (int i = 0; foundPath[i]; i++) {
            if (foundPath[i] == '\\') {
                foundPath[i] = '/';
            }
        }   

        char cmd[1024];
        sprintf(cmd, "xdg-open \"%s\"", foundPath);
        system(cmd);
        free(foundPath);
    } else {
        printf("Chemin non trouvé.\n");
    }   

    free(hexStr);
    return 0;
}
