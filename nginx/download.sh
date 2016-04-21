#!/bin/sh -e

nginx=nginx-1.9.15
pcre=pcre-8.38
zlib=zlib-1.2.8
openssl=openssl-1.0.2g

wget http://nginx.org/download/$nginx.tar.gz
tar xzvf $nginx.tar.gz
mv $nginx nginx

wget ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/$pcre.tar.gz
tar xzvf $pcre.tar.gz
mv $pcre pcre

wget http://zlib.net/$zlib.tar.gz
tar xzvf $zlib.tar.gz
mv $zlib zlib

wget https://www.openssl.org/source/$openssl.tar.gz
tar xzvf $openssl.tar.gz
mv $openssl openssl

git clone git://github.com/arut/nginx-rtmp-module.git

