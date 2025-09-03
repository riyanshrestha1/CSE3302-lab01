//Name: Riyan Shrestha
//ID: 1002223799
//Language Version: C (GCC 13.3.0)
//OS: Ubuntu 24.04
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

long long calculate_size(const char *path) {
    // Open the directory
    DIR *dp = opendir(path);
    if (dp == NULL) {
        // If we cannot open the directory, return 0
        return 0;
    }

    struct dirent *de;  //Directory entry structure
    struct stat st;     //File status structure to get file information
    long long bytes_total = 0;
    char joined[1024];

    while ((de = readdir(dp)) != NULL) {
        // Skip the current (.) and parent (..) directory entries
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            continue;
        }

        // Build full path
        snprintf(joined, sizeof(joined), "%s/%s", path, de->d_name);

        // Get information about the directory entry
        if (stat(joined, &st) != 0) {
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            // Recurse into subdirectory and add its size
            bytes_total += calculate_size(joined);
        } else if (S_ISREG(st.st_mode)) {
            // Regular file: add its size in bytes_total
            bytes_total += st.st_size;
        }
    }

    closedir(dp);
    return bytes_total;
}

int main(int argc, char *argv[]) {
    // Use command line argument for the starting directory or use the current directory if not provided 
    const char *start = (argc > 1) ? argv[1] : ".";
    long long size = calculate_size(start);
    printf("%lld\n", size);
    return 0;
}
