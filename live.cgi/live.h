#ifndef _LIVE_H_
#define _LIVE_H_

#include "live_conf.h"

typedef struct
{
    live_conf_t live_conf;
} live_global_t;

int live_init(live_global_t *live_global);

int live_clear(live_global_t *live_global);

#endif // _LIVE_H_
