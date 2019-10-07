#!/usr/bin/bash
# Fw[a]rd, 10.7, 2019.

# Firstly, please visit 172.16.200.11/12/13 to obtain the session giver url.
# http://210.45.240.245/switch.php?xxxxx will give you the correct session id.
url=`curl 172.16.200.13 | sed -n "s/.*'\(.*\)'.*/\1/p"`
curl $url --cookie ./cookies --cookie-jar ./cookies --output /dev/null

# phpsessid is critical parameter.
curl http://210.45.240.245/post.php  --cookie ./cookies --cookie-jar ./cookies --data-urlencode 'username=此处填入用户名' --data-urlencode 'password=此处填入密码' --data-urlencode '0MKKey=%B5%C7+%C2%BC'


