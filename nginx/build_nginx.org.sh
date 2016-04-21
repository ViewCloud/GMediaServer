#!/usr/bin/env bash
# This one is mainly in compliance with the official Ubuntu one. 
# Under some circumstances, you might want the official Nginx one: 
# http://nginx.org/en/linux_packages.html#arguments 

nginx_rtmp_module=$(pwd)/nginx-rtmp-module
pcre=$(pwd)/pcre
zlib=$(pwd)/zlib
openssl=$(pwd)/openssl

export CFLAGS="-O3 -fPIC -fdata-sections -ffunction-sections"
export CXXFLAGS="-O3 -fPIC -fdata-sections -ffunction-sections"
export LDFLAGS="-fPIC -Wl,--gc-sections -Wl,--strip-all"

cd $zlib
make clean
./configure
make
cd ..

cd $pcre
make clean
./configure
make
cd ..

cd $openssl
make clean
./config
make
cd ..

cd nginx
make clean
./configure \
--add-module=$nginx_rtmp_module \
--with-pcre=$pcre \
--with-zlib=$zlib \
--with-openssl=$openssl \
--with-cc-opt='-static -static-libgcc -O3 -fPIC -fdata-sections -ffunction-sections' \
--with-ld-opt='-static -fPIC -Wl,--gc-sections -Wl,--strip-all' \
--prefix=/etc/nginx \
`#--sbin-path=/usr/sbin/nginx                               `\
`#--conf-path=/etc/nginx/nginx.conf                         `\
`#--error-log-path=/var/log/nginx/error.log                 `\
`#--http-log-path=/var/log/nginx/access.log                 `\
`#--pid-path=/var/run/nginx.pid                             `\
`#--lock-path=/var/run/nginx.lock                           `\
`#--http-client-body-temp-path=/var/cache/nginx/client_temp `\
`#--http-proxy-temp-path=/var/cache/nginx/proxy_temp        `\
`#--http-fastcgi-temp-path=/var/cache/nginx/fastcgi_temp    `\
`#--http-uwsgi-temp-path=/var/cache/nginx/uwsgi_temp        `\
`#--http-scgi-temp-path=/var/cache/nginx/scgi_temp          `\
--user=nginx \
--group=nginx \
--with-http_ssl_module \
--with-http_realip_module \
--with-http_addition_module \
--with-http_sub_module \
--with-http_dav_module \
--with-http_flv_module \
--with-http_mp4_module \
--with-http_gunzip_module \
--with-http_gzip_static_module \
--with-http_random_index_module \
--with-http_secure_link_module \
--with-http_stub_status_module \
--with-http_auth_request_module \
--with-mail \
--with-mail_ssl_module \
--with-file-aio \
--with-http_v2_module \
--with-ipv6 \
--with-threads \
--with-stream \
--with-stream_ssl_module \
--with-http_slice_module
make
cd ../
