#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define FNMODE_FILE "/sys/module/hid_apple/parameters/fnmode"

int
main() {
        FILE *f;
        int fnmode;
        int ret;

        if (0 != setuid(0)) {
                fprintf(stderr, "Error changing user id: %s\n",
                        strerror(errno));
                return 1;
        }

        f = fopen(FNMODE_FILE, "r+");
        if (NULL == f) {
                fprintf(stderr, "Error opening fnmode file.\n");
                return 1;
        }

        if (0 >= fscanf(f, "%d", &fnmode)) {
                fprintf(stderr, "Failed to read fnmode value.\n");
                return 1;
        }

        rewind(f);

        if (0 >= fprintf(f, "%d", fnmode == 2 ? 1 : 2)) {
                fprintf(stderr, "Failed to write fnmode value.\n");
                return 1;
        }

        if (0 != fclose(f)) {
                fprintf(stderr, "Error closing fnmode file: %s\n",
                        strerror(errno));
                return 1;
        }

        return 0;
}
