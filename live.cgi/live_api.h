#ifndef _LIVE_API_H_
#define _LIVE_API_H_

#include "json-c/json.h"
#include "mysql/mysql.h"

#include "live_conf.h"

typedef struct
{
    char *req_buf;
} live_req_t;

typedef struct
{
    char *http_headers;
    json_object *josn_rsp;
} live_rsp_t;

int createLiveChannel(live_req_t *req, live_rsp_t *rsp);
int deleteLiveChannel(live_req_t *req, live_rsp_t *rsp);
int startLiveChannel(live_req_t *req, live_rsp_t *rsp);
int stopLiveChannel(live_req_t *req, live_rsp_t *rsp);
int describelLiveChannel(live_req_t *req, live_rsp_t *rsp);
int modifyLiveChannel(live_req_t *req, live_rsp_t *rsp);
int describeLiveChannelList(live_req_t *req, live_rsp_t *rsp);
int describeLiveOnlineUsers(live_req_t *req, live_rsp_t *rsp);

#endif // _LIVE_API_H_
