# Version 0.0.1

# Required soft
Nginx http://nginx.org/

Spawn fcgi http://redmine.lighttpd.net/projects/spawn-fcgi

PostgreSQL http://www.postgresql.org/

# Install fast cgi development kit
http://www.fastcgi.com

# Install libpq for connect to Postgresql from C
sudo apt-get install libpq-dev
gcc -I/usr/include/postgresql/ -L/usr/lib/postgresql/9.3/lib/ -o ./pgtest pgtest.c -lpq

# Compile
gcc -I/usr/local/include/ -I/usr/include/postgresql/ -L/usr/lib/postgresql/9.3/lib/ -o /path/to/source/cblog/bin/cblog /path/to/source/cblog/src/cblog.c /usr/local/lib/libfcgi.a -lpq

# Run
spawn-fcgi -a127.0.0.1 -p9002 -F1 /path/to/source/cblog/bin/cblog

# Problem solving
upd: change to md5
http://www.treshna.com/psql-fatal-ident-authentication-failed-for-user-username-error-and-solution/


# TODO
1. Learn to get POST and GET requests
2. Create Post struct
3. Move database functions to another c-file
4. Move functions for render html to another c-file
5. Implement functional for create and edit posts
