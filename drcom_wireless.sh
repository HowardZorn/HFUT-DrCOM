#!/usr/bin/bash

username="你的学号"
password="你的密码"

echo 'logging in...'
# detect portal
url=`curl http://detectportal.firefox.com/success.txt --silent | sed -n "s/.*<NextURL>\(.*\)<\/NextURL>.*/\1/p"`
# client ip address
ip=`curl $url --silent | sed -n 's/.*ss5="\([^"]*\)".*/\1/p'`
# login url
url=`printf 'http://210.45.240.105:801/eportal/?c=Portal&a=login&callback=dr1003&login_method=1&user_account=%s&user_password=%s&wlan_user_ip=%s&wlan_user_ipv6=&wlan_user_mac=000000000000&wlan_ac_ip=&wlan_ac_name=HFUT-WS7880&jsVersion=3.3.2&v=5477' $username $password $ip`
# get php session
curl 'http://210.45.240.105:801/eportal/' --cookie ./cookies --cookie-jar ./cookies --silent --output /dev/null
# login
res=`curl $url --cookie ./cookies --cookie-jar ./cookies --silent | sed -n 's/.*(\(.*\)).*/\1/p' | jq`
# test
curl http://detectportal.firefox.com/success.txt --silent --ipv4
