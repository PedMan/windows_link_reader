#include <stdio.h>
#include <stdint.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1)

typedef struct {
    uint32_t headerSize;
    uint32_t linkCLSID[4];
    uint32_t flags;
    uint32_t fileAttributes;
    uint64_t creationTime;
    uint64_t accessTime;
    uint64_t writeTime;
    uint32_t fileSize;
    uint32_t iconIndex;
    uint32_t showCommand;
    uint16_t hotKey;
    uint16_t reserved1;
    uint32_t reserved2;
    uint32_t reserved3;
} LINK_HEADER;

typedef struct {
    uint32_t length;
    uint16_t firstOffset;
    uint32_t size;
    uint32_t flags;
    uint32_t offsetLocalVolumeTable;
    uint32_t offsetLocalBasePath;
    uint32_t offsetNetworkVolumeTable;
    uint32_t offsetCommonNetworkRelativeLink;
    uint32_t offsetCommonPathSuffix;
} FILE_LOCATION_INFO;

#pragma pack(pop)

void readLinkTarget(FILE *file, const LINK_HEADER *header) {
    if (header->flags & 0x1) { // HasLinkTargetIDList
        uint16_t idListSize;
        fread(&idListSize, sizeof(idListSize), 1, file);
        fseek(file, idListSize, SEEK_CUR); // Skip the IDList
    }

    if (header->flags & 0x2) { // HasLinkInfo
        uint32_t linkInfoSize;
        fread(&linkInfoSize, sizeof(linkInfoSize), 1, file);
        fseek(file, -sizeof(linkInfoSize), SEEK_CUR); // Reposition to read LINKINFO

        char *linkInfo = malloc(linkInfoSize);
        fread(linkInfo, linkInfoSize, 1, file);

        // Decode the LinkInfo structure to extract path
        uint32_t linkInfoHeaderSize;
        memcpy(&linkInfoHeaderSize, linkInfo, sizeof(uint32_t));

        if (linkInfoHeaderSize >= 0x24) { // Minimum size for LinkInfo
            uint32_t localBasePathOffset;
            memcpy(&localBasePathOffset, linkInfo + 0x10, sizeof(uint32_t));

            if (localBasePathOffset > 0) {
                wchar_t *localBasePath = (wchar_t *)(linkInfo + localBasePathOffset);
                wprintf(L"Local Base Path: %ls\n", localBasePath);
            }
        }

        free(linkInfo);
    }
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path_to_lnk_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    LINK_HEADER header;
    fread(&header, sizeof(LINK_HEADER), 1, file);
    
    // Debugging outputs
    printf("LINK_HEADER headerSize: %u\n", header.headerSize);
    printf("LINK_HEADER flags: %u\n", header.flags);


    FILE_LOCATION_INFO locInfo;
    fread(&locInfo, sizeof(FILE_LOCATION_INFO), 1, file);
    printf("FILE_LOCATION_INFO length: %u\n", locInfo.length);
    printf("FILE_LOCATION_INFO firstOffset: %u\n", locInfo.firstOffset);
    printf("FILE_LOCATION_INFO size: %u\n", locInfo.size);
    printf("FILE_LOCATION_INFO flags: %u\n", locInfo.flags);    
    

    readLinkTarget(file, &header);

    fclose(file);
    return 0;
}
