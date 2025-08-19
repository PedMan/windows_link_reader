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
               
       |                                   LNK Reader is a Robust  

                                    winddos .lnk parser (MS-SHLLINK spec) 

                                 + opener  for Linux/macOS under MIT LIcence
                |                                                                          |               |                                           |               |                                           |                    |                                           |

                          /                      |    v    |                    \
               
                   Easy build command :   gcc lnkReader.c -o open_lnk -Wall -Wextra -O2  |                                |                                          |      |                                |                                          |      |                                |                                          |           |                                |  
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

#OPENING | https://www.youtube.com/watch?v=_85LaeTCtV8 :3

 */ 


#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <sys/stat.h>

#pragma pack(push,1)
typedef struct {
    uint32_t headerSize;    // 0x0000004C
    uint8_t  clsid[16];     // {00021401-0000-0000-C000-000000000046}
    uint32_t linkFlags;
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
} ShellLinkHeader;
#pragma pack(pop)

// LinkFlags
#define HAS_LINK_TARGET_IDLIST 0x00000001
#define HAS_LINK_INFO          0x00000002
#define HAS_NAME               0x00000004
#define HAS_RELATIVE_PATH      0x00000008
#define HAS_WORKING_DIR        0x00000010
#define HAS_ARGUMENTS          0x00000020
#define HAS_ICON_LOCATION      0x00000040
#define IS_UNICODE             0x00000080

/* 
___  ____ ____ ____ ____ ____ ____    ____ _  _ ____ ____ 
|__] |__/ |  | |    |___ [__  [__     |___  \/  |___ |    
|    |  \ |__| |___ |___ ___] ___]    |___ _/\_ |___ |___ 

 */ 

// Spawn a new process without involving a shell
// If path contains '/', use execv (absolute/relative path)
// Otherwise, use execvp (search in PATH)
static int try_spawn(const char *path_or_name, char *const argv[]) {
    pid_t pid = fork();
    if (pid < 0) return 0;
    if (pid == 0) {
        if (strchr(path_or_name, '/')) execv(path_or_name, argv);
        else execvp(path_or_name, argv);
        _exit(127); // If exec fails
    }
    return 1;
}

/*
____ ____ ____ ____ ____    _  _ ____ _  _ ___  _    ____ ____ 
|___ |__/ |__/ |  | |__/    |__| |__| |\ | |  \ |    |___ |__/ 
|___ |  \ |  \ |__| |  \    |  | |  | | \| |__/ |___ |___ |  \ 

                                                               */

// Display error message with desktop notifications if possible
// macOS → osascript notification
// Linux → notify-send, zenity, or kdialog
// Fallback → stderr
static void showError(const char* message) {
    if (!message) message = "Unknown error";

    struct utsname sysinfo;
    if (uname(&sysinfo) == 0) {
        if (strcmp(sysinfo.sysname, "Darwin") == 0) {
            char script[1024];
            snprintf(script, sizeof(script),
                     "display notification \"%s\" with title \"LNK Reader\"", message);
            char *argv[] = { "osascript", "-e", script, NULL };
            if (try_spawn("osascript", argv)) return;
        } else if (strcmp(sysinfo.sysname, "Linux") == 0) {
            char *argv1[] = { "notify-send", "LNK Reader", (char*)message, NULL };
            if (try_spawn("/usr/bin/notify-send", argv1)) return;
            if (try_spawn("notify-send", argv1)) return;

            char *argv2[] = { "zenity", "--error", "--text", (char*)message, NULL };
            if (try_spawn("zenity", argv2)) return;

            char *argv3[] = { "kdialog", "--error", (char*)message, NULL };
            if (try_spawn("kdialog", argv3)) return;
        }
    }

    // Last resort: write to stderr
    fprintf(stderr, "LNK Reader: %s\n", message);
}

/* 
____ ___ ____ _ _  _ ____    ___ ____ ____ _    ____ 
[__   |  |__/ | |\ | | __     |  |  | |  | |    [__  
___]  |  |  \ | | \| |__]     |  |__| |__| |___ ___] 
                                                     
*/

// Convert UTF-16LE string into UTF-8 (limited to BMP characters)
// - Stops at first NUL or max_chars
// - Allocates worst case (3 bytes per UTF-16 char)
// - Handles ASCII, 2-byte and 3-byte ranges only
static char* utf16le_to_utf8(const uint16_t *wstr, size_t max_chars) {
    if (!wstr) return NULL;

    // Count length until NUL or limit
    size_t len = 0; 
    while (len < max_chars && wstr[len] != 0) len++;

    char *out = (char*)malloc(len * 3 + 1); // 3 bytes per char + terminator
    if (!out) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        uint16_t wc = wstr[i];

        if (wc < 0x80) {
            // Plain ASCII (1 byte)
            out[j++] = (char)wc;
        } else if (wc < 0x800) {
            // Extended Latin / Greek / Cyrillic etc. (2 bytes)
            out[j++] = (char)(0xC0 | (wc >> 6));
            out[j++] = (char)(0x80 | (wc & 0x3F));
        } else {
            // Most other BMP characters (3 bytes)
            out[j++] = (char)(0xE0 | (wc >> 12));
            out[j++] = (char)(0x80 | ((wc >> 6) & 0x3F));
            out[j++] = (char)(0x80 | (wc & 0x3F));
        }
    }
    out[j] = 0;
    return out;
}

// Read a counted string from file
// - First 2 bytes = length
// - If unicode=1 → UTF-16LE string
// - If unicode=0 → ANSI string
static char* readStringData(FILE *f, int unicode) {
    uint16_t count = 0;
    if (fread(&count, sizeof(count), 1, f) != 1) return NULL;
    if (count == 0) return strdup("");

    if (unicode) {
        uint16_t *buf = (uint16_t*)malloc((size_t)count * sizeof(uint16_t));
        if (!buf) return NULL;
        if (fread(buf, sizeof(uint16_t), count, f) != count) { free(buf); return NULL; }
        char *out = utf16le_to_utf8(buf, count);
        free(buf);
        return out;
    } else {
        char *buf = (char*)malloc((size_t)count + 1);
        if (!buf) return NULL;
        if (fread(buf, 1, count, f) != count) { free(buf); return NULL; }
        buf[count] = 0;
        return buf;
    }
}

// Read a NUL-terminated ANSI string
// - Reads byte by byte until '\0' or cap
// - Expands buffer if needed
static char* read_c_string(FILE *f, size_t cap) {
    size_t alloc = 256, j = 0;
    char *s = (char*)malloc(alloc);
    if (!s) return NULL;

    int c;
    while ((c = fgetc(f)) != EOF) {
        if (c == 0) break; // stop at NUL
        if (j + 1 >= alloc) {
            size_t newa = alloc * 2; 
            if (newa > cap) newa = cap;
            char *tmp = (char*)realloc(s, newa);
            if (!tmp) { free(s); return NULL; }
            s = tmp; alloc = newa;
        }
        s[j++] = (char)c;
        if (j + 1 >= cap) break;
    }
    s[j] = 0;
    return s;
}

// Read a NUL-terminated UTF-16LE string
// - Reads 16-bit words until 0x0000 or max_chars
// - Expands buffer if needed
// - Converts result to UTF-8
static char* read_w_string(FILE *f, size_t max_chars) {
    size_t alloc = 256, j = 0;
    uint16_t *w = (uint16_t*)malloc(alloc * sizeof(uint16_t));
    if (!w) return NULL;

    uint16_t ch;
    while (fread(&ch, sizeof(ch), 1, f) == 1) {
        if (ch == 0) break; // stop at NUL
        if (j + 1 >= alloc) {
            size_t newa = alloc * 2; 
            if (newa > max_chars) newa = max_chars;
            uint16_t *tmp = (uint16_t*)realloc(w, newa * sizeof(uint16_t));
            if (!tmp) { free(w); return NULL; }
            w = tmp; alloc = newa;
        }
        w[j++] = ch;
        if (j + 1 >= max_chars) break;
    }
    w[j] = 0;

    char *out = utf16le_to_utf8(w, j + 1);
    free(w);
    return out;
}


/* 
___  ____ ___ _  _    _  _ ___ _ _    ____ 
|__] |__|  |  |__|    |  |  |  | |    [__  
|    |  |  |  |  |    |__|  |  | |___ ___] 
                                           
*/

// Check if a path exists on the filesystem
static int path_exists(const char *p) {
    struct stat st; 
    return stat(p, &st) == 0;
}

// Try to convert a Windows path "X:\foo" to a valid Linux mount path
// Skip system mounts like /proc, /dev, /sys...
static char* try_map_windows_drive_to_mounts(const char *winPath) {
    if (!winPath || strlen(winPath) < 3 || winPath[1] != ':' || (winPath[2] != '\\' && winPath[2] != '/'))
        return NULL;

    FILE *m = fopen("/proc/mounts", "r");
    if (!m) return NULL;

    const char *skip[] = { "/proc", "/sys", "/dev", "/run", "/snap", "/var/lib/snapd", NULL };
    char dev[256], mnt[256], rest[512];
    const char *core = winPath + 2;

    // Scan all mounted devices
    while (fscanf(m, "%255s %255s %511s\n", dev, mnt, rest) != EOF) {
        int bad = 0;
        for (int i = 0; skip[i]; ++i) 
            if (strncmp(mnt, skip[i], strlen(skip[i])) == 0) { bad = 1; break; }
        if (bad) continue;

        // Build candidate full path
        char candidate[PATH_MAX];
        snprintf(candidate, sizeof(candidate), "%s%s", mnt, core);

        // Replace Windows backslashes with POSIX slashes
        for (char *p = candidate; *p; ++p) 
            if (*p == '\\') *p = '/';

        // If the candidate path exists, return it
        if (path_exists(candidate)) { 
            fclose(m); 
            return strdup(candidate); 
        }
    }

    fclose(m);
    return NULL;
}

// Replace all backslashes with slashes in a given string
static void normalize_backslashes(char *s) {
    if (!s) return;
    for (char *p = s; *p; ++p) 
        if (*p == '\\') *p = '/';
}

/*
___  ____ ____ _  _ ___ ____ ___     ____ ___  ____ _  _ 
|  \ |___ [__  |_/   |  |  | |__]    |  | |__] |___ |\ | 
|__/ |___ ___] | \_  |  |__| |       |__| |    |___ | \| 
                                                         
*/

// Open a file or directory with the system's default desktop application
// macOS → "open" ; Linux → "xdg-open"
static int open_with_desktop(const char *path) {
    struct utsname u;
    if (uname(&u) == 0 && strcmp(u.sysname, "Darwin") == 0) {
        pid_t pid = fork(); 
        if (pid < 0) return -1;
        if (pid == 0) { execlp("open", "open", path, (char*)NULL); _exit(127); }
        return 0;
    }

    pid_t pid = fork(); 
    if (pid < 0) return -1;
    if (pid == 0) { execlp("xdg-open", "xdg-open", path, (char*)NULL); _exit(127); }
    return 0;
}

/*
_    _ _  _ _  _    _  _ ____ ___  ____ _    
|    | |\ | |_/     |\/| |  | |  \ |___ |    
|___ | | \| | \_    |  | |__| |__/ |___ |___ 
                                             
*/

// Structure holding all important .lnk fields
typedef struct {
    char *localBasePath;      // Base path (ANSI)
    char *localBasePathU;     // Base path (Unicode)
    char *commonPathSuffix;   // Common suffix (ANSI)
    char *commonPathSuffixU;  // Common suffix (Unicode)
    char *nameString;         // Name string
    char *relativePath;       // Relative path
    char *workingDir;         // Working directory
    char *arguments;          // Command-line arguments
    char *iconLocation;       // Icon file location
} LnkInfo;

// Release memory for all strings in a LnkInfo struct
static void freeLnkInfo(LnkInfo *li) {
    if (!li) return;
    free(li->localBasePath);
    free(li->localBasePathU);
    free(li->commonPathSuffix);
    free(li->commonPathSuffixU);
    free(li->nameString);
    free(li->relativePath);
    free(li->workingDir);
    free(li->arguments);
    free(li->iconLocation);
}


/*
_    _  _ _  _    ___  ____ ____ ____ ____ ____ 
|    |\ | |_/     |__] |__| |__/ [__  |___ |__/ 
|___ | \| | \_    |    |  | |  \ ___] |___ |  \ 
                                                
*/

// Parse LNK file: read header, LinkInfo, and strings
static int parse_lnk(FILE *f, LnkInfo *out) {
    memset(out, 0, sizeof(*out));

    //  Header 
    ShellLinkHeader hdr;
    if (fread(&hdr, sizeof(hdr), 1, f) != 1) { showError("Failed to read header"); return 0; }
    if (hdr.headerSize != 0x4C) { showError("Invalid header size"); return 0; }

    // Validate CLSID (GUID identifying ShellLink files)
    static const uint8_t CLSID[16] = {0x01,0x14,0x02,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46};
    if (memcmp(hdr.clsid, CLSID, 16) != 0) { showError("Not a Shell Link file"); return 0; }

    int unicode = (hdr.linkFlags & IS_UNICODE) != 0;

    //  IDList (skip if present) 
    if (hdr.linkFlags & HAS_LINK_TARGET_IDLIST) {
        uint16_t idListSize = 0;
        if (fread(&idListSize, sizeof(idListSize), 1, f) != 1) { showError("Bad IDList size"); return 0; }
        if (fseek(f, idListSize, SEEK_CUR) != 0) { showError("Skip IDList failed"); return 0; }
    }

    //  LinkInfo (base + suffix) 
    if (hdr.linkFlags & HAS_LINK_INFO) {
        long li_start = ftell(f);
        uint32_t liSize = 0;
        if (fread(&liSize, 4, 1, f) != 1 || liSize < 0x1C) { showError("Bad LinkInfo size"); return 0; }

        uint32_t liHeaderSize=0, liFlags=0;
        uint32_t volOff=0, lbpOff=0, cnrlOff=0, cpsOff=0;
        if (fread(&liHeaderSize,4,1,f)!=1) { showError("Bad LinkInfo header"); return 0; }
        if (fread(&liFlags,4,1,f)!=1)      { showError("Bad LinkInfo flags");  return 0; }
        if (fread(&volOff,4,1,f)!=1)       { showError("Bad volume offset");   return 0; }
        if (fread(&lbpOff,4,1,f)!=1)       { showError("Bad base offset");     return 0; }
        if (fread(&cnrlOff,4,1,f)!=1)      { showError("Bad CNRL offset");     return 0; }
        if (fread(&cpsOff,4,1,f)!=1)       { showError("Bad suffix offset");   return 0; }

        // Optional Unicode offsets
        uint32_t lbpOffU = 0, cpsOffU = 0;
        if (liHeaderSize >= 0x24) {
            if (fread(&lbpOffU,4,1,f)!=1)  { showError("Bad baseU offset");    return 0; }
            if (fread(&cpsOffU,4,1,f)!=1)  { showError("Bad suffixU offset");  return 0; }
        }

        // Extract LocalBasePath (Unicode preferred)
        if (lbpOffU && lbpOffU < liSize) { fseek(f, li_start + lbpOffU, SEEK_SET); out->localBasePathU = read_w_string(f, 65535); }
        else if (lbpOff && lbpOff < liSize) { fseek(f, li_start + lbpOff, SEEK_SET); out->localBasePath = read_c_string(f, 1<<20); }

        // Extract CommonPathSuffix (Unicode preferred)
        if (cpsOffU && cpsOffU < liSize) { fseek(f, li_start + cpsOffU, SEEK_SET); out->commonPathSuffixU = read_w_string(f, 65535); }
        else if (cpsOff && cpsOff < liSize) { fseek(f, li_start + cpsOff, SEEK_SET); out->commonPathSuffix = read_c_string(f, 1<<20); }

        fseek(f, li_start + liSize, SEEK_SET); // jump to end of block
    }

    //  Extra Strings 
    if (hdr.linkFlags & HAS_NAME)          out->nameString   = readStringData(f, unicode);
    if (hdr.linkFlags & HAS_RELATIVE_PATH) out->relativePath = readStringData(f, unicode);
    if (hdr.linkFlags & HAS_WORKING_DIR)   out->workingDir   = readStringData(f, unicode);
    if (hdr.linkFlags & HAS_ARGUMENTS)     out->arguments    = readStringData(f, unicode);
    if (hdr.linkFlags & HAS_ICON_LOCATION) out->iconLocation = readStringData(f, unicode);

    return 1;
}

/* 
___ ____ ____ ____ ____ ___    ___  _  _ _ _    ___  
 |  |__| |__/ | __ |___  |     |__] |  | | |    |  \ 
 |  |  | |  \ |__] |___  |     |__] |__| | |___ |__/ 
                                                     
*/

// Build the most reliable target path from available fields
static char* build_best_target(LnkInfo *li) {
    // Prefer Unicode base path if available, else ANSI version
    const char *base = li->localBasePathU ? li->localBasePathU : li->localBasePath;
    if (base && *base) return strdup(base);

    // Combine WorkingDir + RelativePath if both are set
    if (li->workingDir && li->relativePath && *li->workingDir && *li->relativePath) {
        size_t n = strlen(li->workingDir) + 1 + strlen(li->relativePath) + 1;
        char *s = (char*)malloc(n); if (!s) return NULL;
        snprintf(s, n, "%s\\%s", li->workingDir, li->relativePath);
        return s;
    }

    // Otherwise try RelativePath alone
    if (li->relativePath && *li->relativePath) return strdup(li->relativePath);

    // As last resort use CommonPathSuffix (Unicode or ANSI)
    if (li->commonPathSuffixU && *li->commonPathSuffixU) return strdup(li->commonPathSuffixU);
    if (li->commonPathSuffix && *li->commonPathSuffix)   return strdup(li->commonPathSuffix);

    // Nothing usable → return NULL
    return NULL;
}

/*
___  ____ _ _ _ ____ ____    ___  _    ____ _  _ ___
|__] |  | | | | |___ |__/    |__] |    |__| |\ |  |
|    |__| |_|_| |___ |  \    |    |___ |  | | \|  |

*/

int main(int argc, char *argv[]) {
    // Expect exactly one argument: the .lnk file
    if (argc != 2) { showError("Usage: open_lnk <file.lnk>"); return 1; }

    // Open the shortcut file
    FILE *f = fopen(argv[1], "rb");
    if (!f) { showError("Cannot open .lnk file"); return 1; }

    // Parse the LNK structure into info
    LnkInfo info;
    if (!parse_lnk(f, &info)) { fclose(f); return 1; }
    fclose(f);

    // Build best candidate target path
    char *target = build_best_target(&info);
    if (!target) { freeLnkInfo(&info); showError("No target path found"); return 1; }

    // Normalize path separators to Unix style
    normalize_backslashes(target);

    // If path doesn't exist locally but looks like a Windows drive,
    // try mapping to Linux mounts
    if (!path_exists(target) && isalpha((unsigned char)target[0]) && target[1] == ':') {
        char *mapped = try_map_windows_drive_to_mounts(target);
        if (mapped) { free(target); target = mapped; }
    }

    int rc = 0;
    if (path_exists(target)) {
        // Try opening the resolved target
        rc = open_with_desktop(target);
    } else {
        // If target missing, fallback: try parent directory
        char *dup = strdup(target);
        if (dup) {
            char *slash = strrchr(dup, '/');
            if (slash) {
                *slash = 0;
                rc = path_exists(dup) ? open_with_desktop(dup) : -1;
            } else rc = -1;
            free(dup);
        } else rc = -1;
    }

    // Handle failure if desktop open failed
    if (rc != 0) {
        char buf[512];
        snprintf(buf, sizeof(buf), "Failed to open: %s", target);
        showError(buf);
        free(target);
        freeLnkInfo(&info);
        return 1;
    }

    // Cleanup and exit normally
    free(target);
    freeLnkInfo(&info);
    return 0;
}
