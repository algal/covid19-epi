#include <stdlib.h>

#if defined(USE_GETRANDOM)
#include <linux/random.h>
#include <errno.h>
#else
#include <time.h>
#endif

#include "common.h"

int use_fixed_seed = 0;

/* wrap the random function so we can easily change the selected random generator */

void COV_init_rand() {
#if defined(USE_GETRANDOM)
    unsigned short sv[3];
    int ret;
#endif

    if (use_fixed_seed) {
        srand48(555L);
    } else {
#if defined(USE_GETRANDOM)
        ret = getrandom(((void *)sv, sizeof(sv), 0);
        while (ret != sizeof(sv) && (errno == EAGAIN || errno == EINTR)) {
            ret = getrandom(((void *)sv, sizeof(sv), 0);
        }
        seed48(sv);
#else
        srand48(time(NULL));
#endif
    }
}

/* Must produce a values in the [0, 1) range */
double COV_rand() {
    double ret;
    ret =  drand48();
    return ret;
}
