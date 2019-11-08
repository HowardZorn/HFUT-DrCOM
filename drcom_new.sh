#!/usr/bin/bash

# Firstly, please visit 172.16.200.11/12/13 to obtain the session giver url.
# http://210.45.240.245/switch.php?xxxxx will give you the correct session id.
echo 'logging in...'
url=`curl 172.16.200.13 --silent | sed -n "s/.*'\(.*\)'.*/\1/p"`
curl $url --cookie ./cookies --cookie-jar ./cookies --output /dev/null --silent

# phpsessid is critical parameter.
curl http://210.45.240.245/post.php  --cookie ./cookies --cookie-jar ./cookies --data-urlencode 'username=学号' --data-urlencode 'password=密码' --data-urlencode '0MKKey=%B5%C7+%C2%BC' --silent

curl --silent http://detectportal.firefox.com/success.txt

