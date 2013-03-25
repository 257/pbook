#include <time.h> /* for rand(), should use /dev/urandom though */
#define frand() ((double) rand() / (RAND_MAX+1.0))
