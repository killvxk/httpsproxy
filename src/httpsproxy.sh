#! /bin/sh

### BEGIN INIT INFO
# Provides:             httpsproxy
# Required-start        No
#short-description:     httpsproxy client
### END INIT INFO

set -e
#/home/eric/httpsproxy/src
test -e /home/eric/httpsproxy/src/makefile || exit 0
cd /home/eric/httpsproxy/src
(make start-client)  || exit 0

