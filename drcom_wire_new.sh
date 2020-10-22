#!/usr/bin/bash

username="你的学号"
password="你的密码"

echo 'logging in...'
# visit 172.16.200.11/12/13 to obtain the session giver url.
# http://210.45.240.245/switch.php?xxxxx will give you the correct session id.
url=`curl 172.16.200.13 --silent | sed -n "s/.*'\(.*\)'.*/\1/p"`
# get php session
curl $url --cookie ./cookies --cookie-jar ./cookies --output /dev/null --silent
# login, phpsessid is critical parameter.
curl http://210.45.240.245/post.php  --cookie ./cookies --cookie-jar ./cookies --data-urlencode 'username='$username --data-urlencode 'password='$password --data-urlencode '0MKKey=%B5%C7+%C2%BC' --silent
# test
curl --silent http://detectportal.firefox.com/success.txt
