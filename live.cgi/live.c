#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "json-c/json.h"

#include "live.h"

int live_init(live_global_t *live_global)
{
    live_conf_init(&live_global->live_conf);
}

int live_clear(live_global_t *live_global)
{
    live_conf_clear(&(live_global->live_conf));
}

