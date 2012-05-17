/*
  Copyright 2012 Eric A Wollesen

  This program is distributed the terms of the GNU General Public License.
*/

/*
  This file is part of mbp-fn-flip.

  mbp-fn-flip is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  mbp-fn-flip is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with mbp-fn-flip.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define FNMODE_FILE "/sys/module/hid_apple/parameters/fnmode"

void
display_current_setting(void) {
        FILE *f;
        int fnmode;

        f = fopen(FNMODE_FILE, "r");
        if (NULL == f) {
                fprintf(stderr, "Error opening fnmode file.\n");
                exit(EXIT_FAILURE);
        }

        if (0 >= fscanf(f, "%d", &fnmode)) {
                fprintf(stderr, "Failed to read fnmode value.\n");
                exit(EXIT_FAILURE);
        }

        if (0 != fclose(f)) {
                fprintf(stderr, "Error closing fnmode file: %s\n",
                        strerror(errno));
                exit(EXIT_FAILURE);
        }

        fprintf(stdout, "%d\n", fnmode);
}

void
set_value_to(const char value) {
        FILE *f;

        if (0 != setuid(0)) {
                fprintf(stderr, "Error changing user id: %s\n",
                        strerror(errno));
                exit(EXIT_FAILURE);
        }

        f = fopen(FNMODE_FILE, "r+");
        if (NULL == f) {
                fprintf(stderr, "Error opening fnmode file.\n");
                exit(EXIT_FAILURE);
        }

        if (0 >= fprintf(f, "%c", value)) {
                fprintf(stderr, "Failed to write fnmode value.\n");
                exit(EXIT_FAILURE);
        }

        if (0 != fclose(f)) {
                fprintf(stderr, "Error closing fnmode file: %s\n",
                        strerror(errno));
                exit(EXIT_FAILURE);
        }
}

void
usage(const char *bin) {
        fprintf(stderr, "Usage: %s [0|1|2]\n", bin);
}

int
main(int argc, char *argv[]) {
        int opt;

        while ((opt = getopt(argc, argv, "")) != -1) {
                fprintf(stderr, "Usage: %s [0|1|2]\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        if (optind >= argc) {
                display_current_setting();
        } else {
                switch (argv[optind][0]) {
                case '0':
                case '1':
                case '2':
                        set_value_to(argv[optind][0]);
                        display_current_setting();
                        break;
                default:
                        fprintf(stderr, "Usage: %s [0|1|2]\n", argv[0]);
                        exit(EXIT_FAILURE);
                }
        }

        return 0;
}
