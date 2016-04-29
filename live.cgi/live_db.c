#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "json-c/json.h"
#include "mysql/mysql.h"

#include "live_db.h"

int live_db_process(live_db_t *live_db)
{
    live_db->conn = NULL;
    live_db->res = NULL;

    live_db->conn = mysql_init(NULL);

    if (live_db->conn == NULL)
    {
        printf("LIVE_DB_ERR_INIT\n");
        return LIVE_DB_ERR_INIT;
    }

    printf("%s\n \
            %s\n \
            %s\n \
            %s\n \
            %d\n \
            %s\n \
            %d\n \
            ",
           live_db->live_conf->host,
           live_db->live_conf->user,
           live_db->live_conf->passwd,
           live_db->live_conf->db,
           live_db->live_conf->port,
           live_db->live_conf->unix_socket,
           live_db->live_conf->client_flag
          );
    if (mysql_real_connect(live_db->conn,
                           live_db->live_conf->host,
                           live_db->live_conf->user,
                           live_db->live_conf->passwd,
                           live_db->live_conf->db,
                           live_db->live_conf->port,
                           live_db->live_conf->unix_socket,
                           live_db->live_conf->client_flag) == NULL)
    {
        printf("LIVE_DB_ERR_CONNECT\n");
        return LIVE_DB_ERR_CONNECT;
    }

    // INSERT INTO `online_db` (`uuid`, `is_online`, `last_login_time`) VALUES ('667.664.34.34', '1', '2016-04-14 00:00:00');

    printf("1111: %s\n", live_db->query_str);
    if (mysql_query(live_db->conn, live_db->query_str))
    {
        printf("LIVE_DB_ERR_QUERY\n");
        return LIVE_DB_ERR_QUERY;
    }

    else
    {
        live_db->res = mysql_store_result(live_db->conn);
        if (live_db->res == NULL)
        {
            printf("LIVE_DB_ERR_NORESULT\n");
            return LIVE_DB_ERR_NORESULT;
        }
    }

    return 0;
}

int live_db_clear(live_db_t *live_db)
{
    if (live_db->res)
    {
        printf("clear 1\n");
        mysql_free_result(live_db->res);
        printf("clear 2\n");
        live_db->res = NULL;
    }
    if (live_db->conn)
    {
        printf("clear 1\n");
        mysql_close(live_db->conn);
        printf("clear 2\n");
        live_db->conn = NULL;
    }
}

int live_db_result_handler(live_db_t *live_db)
{
    printf("0\n");
    MYSQL_RES *result = live_db->res;
    if (result)
    {

        printf("1.1\n");

        int num_fields = mysql_num_fields(result);

        printf("1\n");
        MYSQL_ROW row;
        MYSQL_FIELD *field;
        printf("2\n");
        while ((row = mysql_fetch_row(result)))
        {
            printf("3\n");
            mysql_field_seek(result, 0);
            for(int i = 0; i < num_fields; i++)
            {
                printf("4\n");
                field = mysql_fetch_field(result);
                printf("%s: ", field->name);
                printf("%s  ", row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
        printf("\n");
        mysql_free_result(result);
        live_db->res = NULL;
    }
    return 0;
}

