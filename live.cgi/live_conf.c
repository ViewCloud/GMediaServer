#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "json-c/json.h"
#include "mysql/mysql.h"

#include "live_conf.h"

int live_conf_init(live_conf_t *conf)
{
    FILE *fp;
    fp = fopen("./live.conf", "rb");
    if (!fp)
        fp = fopen("/etc/pear/live.conf", "rb");
    if (!fp)
        fp = fopen("/etc/guancloud/live.conf", "rb");
    if (!fp)
        fp = fopen("/etc/live.conf", "rb");
    if (!fp)
    {
        conf->host = (char*)malloc(sizeof("571f3fb81b3da.sh.cdb.myqcloud.com") + 1 );
        strcpy(conf->host, "571f3fb81b3da.sh.cdb.myqcloud.com");
        conf->user = (char*)malloc(sizeof("cdb_outerroot") + 1 );
        strcpy(conf->user, "cdb_outerroot");
        conf->passwd = (char*)malloc(sizeof("its4Alan") + 1 );
        strcpy(conf->passwd, "its4Alan");
        conf->db = (char*)malloc(sizeof("guancloud") + 1 );
        strcpy(conf->db, "guancloud");
        conf->port = 6020;
        conf->unix_socket = NULL;
        conf->client_flag = 0;
    }
    else
    {
        fseek(fp, 0, SEEK_END);
        long fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char *conf_buf = (char*)malloc(fsize + 1);
        fread(conf_buf, fsize, 1, fp);
        conf_buf[fsize] = 0;
        fclose(fp);

        json_object *j_conf, *j_value;
        j_conf = json_tokener_parse(conf_buf);

        json_object_object_get_ex(j_conf, "host", &j_value);
        conf->host = (char*)malloc(json_object_get_string_len(j_value) + 1);
        strcpy(conf->host, json_object_get_string(j_value));

        json_object_object_get_ex(j_conf, "user", &j_value);
        conf->user = (char*)malloc(json_object_get_string_len(j_value) + 1);
        strcpy(conf->user, json_object_get_string(j_value));

        json_object_object_get_ex(j_conf, "passwd", &j_value);
        conf->passwd = (char*)malloc(json_object_get_string_len(j_value) + 1);
        strcpy(conf->passwd, json_object_get_string(j_value));

        json_object_object_get_ex(j_conf, "db", &j_value);
        conf->db = (char*)malloc(json_object_get_string_len(j_value) + 1);
        strcpy(conf->db, json_object_get_string(j_value));

        json_object_object_get_ex(j_conf, "port", &j_value);
        conf->port = json_object_get_int(j_value);

        json_object_object_get_ex(j_conf, "unix_socket", &j_value);
        if (json_object_is_type(j_value, json_type_null))
        {
            conf->unix_socket = NULL;
            printf("unix_socket is null\n");
        }
        else
        {
            conf->unix_socket = (char*)malloc(json_object_get_string_len(j_value) + 1);
            strcpy(conf->unix_socket, json_object_get_string(j_value));
        }
        json_object_object_get_ex(j_conf, "client_flag", &j_value);
        if (json_object_is_type(j_value, json_type_int))
        {
            conf->client_flag = json_object_get_int64(j_value);
        }
        else if (json_object_is_type(j_value, json_type_string) &&
                 strcmp(json_object_get_string(j_value), "CLIENT_MULTI_STATEMENTS") == 0)
        {
            conf->client_flag = CLIENT_MULTI_STATEMENTS;
        }
        else
        {
            conf->client_flag = 0;
        }

        free(conf_buf);
    }
}

int live_conf_clear(live_conf_t *conf)
{
    free(conf->host);
    free(conf->user);
    free(conf->passwd);
    free(conf->db);
    free(conf->unix_socket);
    conf->host        = NULL;
    conf->user        = NULL;
    conf->passwd      = NULL;
    conf->db          = NULL;
    conf->unix_socket = NULL;
    return 0;
}
