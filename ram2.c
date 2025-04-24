#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define MiB (1024 * 1024)

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <MiB to allocate>\n", argv[0]);
        return 1;
    }

    size_t mib = strtoul(argv[1], NULL, 10);
    size_t bytes = mib * MiB;
    
    // Allocate and lock memory
    char *mem = malloc(bytes);
    if (!mem) { perror("malloc"); return 1; }
    
    memset(mem, 0, bytes);  // Force RAM usage
    
    if (mlock(mem, bytes)) {
        perror("mlock (run as root?)");
    }

    printf("Allocated %zu MiB. Press Enter to free...\n", mib);
    getchar();  // Hold until keypress
    
    free(mem);
    return 0;
}

