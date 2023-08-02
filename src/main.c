#include <stdlib.h>
#include "../lib/libfunc.h"

int main(int argc, char* argv[]) {
    if (argc == 2) {
        int k = atoi(argv[1]);
        if (k == 1) {
            return libfunc(k);
        }
    } else {
        return 1;
    }
}
