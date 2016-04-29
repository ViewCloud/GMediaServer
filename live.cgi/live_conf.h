#ifndef _LIVE_CONF_H_
#define _LIVE_CONF_H_

typedef struct
{
    char *host;
    char *user;
    char *passwd;
    char *db;
    int  port;
    char *unix_socket;
    unsigned long client_flag;
} live_conf_t;

int live_conf_init(live_conf_t *conf);

int live_conf_clear(live_conf_t *conf);

#endif // _LIVE_CONF_H_
