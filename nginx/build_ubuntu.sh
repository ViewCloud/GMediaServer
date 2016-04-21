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
--with-cc-opt='-O3 -fPIC -fdata-sections -ffunction-sections' \
--with-ld-opt='-fPIC -Wl,--gc-sections -Wl,--strip-all' \
--prefix=/usr/share/nginx \
--conf-path=/etc/nginx/nginx.conf \
--http-log-path=/var/log/nginx/access.log \
--error-log-path=/var/log/nginx/error.log \
--lock-path=/var/lock/nginx.lock \
--pid-path=/run/nginx.pid \
--http-client-body-temp-path=/var/lib/nginx/body \
--http-fastcgi-temp-path=/var/lib/nginx/fastcgi \
--http-proxy-temp-path=/var/lib/nginx/proxy \
--http-scgi-temp-path=/var/lib/nginx/scgi \
--http-uwsgi-temp-path=/var/lib/nginx/uwsgi \
--with-debug \
--with-pcre-jit \
--with-ipv6 \
--with-http_ssl_module \
--with-http_stub_status_module \
--with-http_realip_module \
--with-http_auth_request_module \
--with-http_addition_module \
--with-http_dav_module \
--with-http_v2_module \
--with-http_sub_module \
--with-http_geoip_module \
--with-http_gzip_static_module \
--with-http_image_filter_module \
--with-http_xslt_module \
--with-mail \
--with-mail_ssl_module \
--with-http_mp4_module
make 
cd ../
# Totally static build, add: 
# --with-cc-opt="-static -static-libgcc" 
# --with-ld-opt="-static"
 
