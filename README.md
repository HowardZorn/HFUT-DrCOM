```
本项目遵从GPLv2协定，Copyright (C) 2019, Fw[a]rd

根据GPL协定，我、本项目的作者，不会对您使用这个脚本带来的任何后果负责。
这并非在警告自动登陆校园网是违规使用（其实我并不清楚是否存在违规）。
```

# 合肥工业大学校园网自动登陆指南

## 手动认证方式简介
一般地，操作系统/浏览器会自动检测网络状况并自动跳转到认证页面。此时输入帐号密码即可访问网络。如果不会跳转，请手动访问172.16.200.11/172.16.200.12/172.16.200.13。

## 自动认证方法
克隆整个项目，在运行脚本前请打开脚本文件填入自己的用户名和密码。看到success的输出结果即可访问网络。目前仅支持Unix系和msys(2)/Cygwin/MingW。依赖是：bash、curl。

## 自动认证原理
### 新接口（210.45.240.245）
访问校园网外部没有使用加密信道的网页和172.16.200.11/172.16.200.12/172.16.200.13时，会跳转到210.45.240.245进行认证：先是跳转到`http://210.45.240.245/switch.php?×××××`页面设置一个 session id，然后在登陆页面填写表单`POST`到`http://210.45.240.245/post.php`。此时千万要记得将之前的合法session id作为cookie的一部分提交出去。之后即拥有互联网通信权限，这个环境能获得一个IPv4内网地址和IPv6公网地址。

支持脚本文件名为`drcom_wire_new.sh`。

### 老接口（172.16.200.11/172.16.200.12/172.16.200.13）
在部分时候，老接口也可以使用。老接口对于自动化登陆十分方便，没有 session 限制，仅需`POST`。可以参考学长的 https://github.com/hongrunhui/hfut-autologin 进行登陆。这个环境能获得一个IPv4内网地址和IPv6公网地址。

### Wifi 专用接口
在使用SSID名为`HFUT-WiFi`的WLAN连接校园网时，也是需要认证的。这个接口特别之处在于表单提交时密码和用户名是`GET`方法中的一个参数。目前仅有初步支持（在新区图书馆有效，在某些地方似乎无效）。看来学校的网管是真的闲，居然针对同样的问题写了三套不同解决方案。新区图书馆的Wifi下仅有内网的IPv4地址。

支持脚本文件名为`drcom_wireless.sh`。

## TODO
目前已经上传了新接口的脚本。之后会编写自动登陆脚本，隐藏两种接口的不同。后期集成到一个C/C++程序中，方便在路由器上运行。
