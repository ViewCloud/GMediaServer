#include <stdio.h>
#include <stdlib.h>
#include "live.h"
#include "live_db.h"

void test()
{
    live_global_t live_global;
    live_init(&live_global);
    printf("Hello world!\n");

    live_db_t live_db;
    live_db.live_conf = &(live_global.live_conf);
    char query_str[512] = "INSERT INTO `online_db` (`uuid`, `is_online`, `last_login_time`) VALUES ('455.664.43.34', '1', '2016-04-14 00:00:00')";
    live_db.query_str = query_str;

    printf("1Hello world!\n");
    live_db_process(&live_db);
    printf("2Hello world!\n");
    live_db_result_handler(&live_db);
    printf("3Hello world!\n");
    live_db_clear(&live_db);
    printf("4Hello world!\n");

    live_clear(&live_global);
}

int main()
{
    test();
    printf("Hello world!\n");
    return 0;
}
