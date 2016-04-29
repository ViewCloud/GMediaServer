#ifndef _LIVE_DB_H_
#define _LIVE_DB_H_

#include "mysql/mysql.h"

#include "live_conf.h"

typedef struct
{
    live_conf_t *live_conf;
    MYSQL *conn;
    MYSQL_RES *res;
    char *query_str;
} live_db_t;

typedef enum{
    LIVE_DB_ERR_INIT     = -5,
    LIVE_DB_ERR_CONNECT  = -4,
    LIVE_DB_ERR_QUERY    = -3,
    LIVE_DB_ERR_NORESULT = -2,
    LIVE_DB_ERR_OTHER    = -1
} live_db_err_t;

int live_db_process(live_db_t *live_db);

int live_db_clear(live_db_t *live_db);

int live_db_result_handler(live_db_t *live_db);

#endif // _LIVE_DB_H_
