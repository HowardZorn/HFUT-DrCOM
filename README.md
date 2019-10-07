```
根据GPL协定，我、本项目的作者，不会对您使用这个脚本带来的任何后果负责。
这并非在警告自动登陆校园网是违规使用（其实我并不清楚）。
```

# 合肥工业大学校园网自动登陆指南

## 手动认证方式简介
一般地，操作系统/浏览器会自动检测网络状况并自动跳转到认证页面。此时输入帐号密码即可上网。如果不会跳转，请手动访问172.16.200.11/172.16.200.12/172.16.200.13。
## 自动认证原理
### 新接口（210.45.240.245）
大多数时候，访问172.16.200.11/172.16.200.12/172.16.200.13认证时，会跳转到210.45.240.245进行认证：是跳转到`http://210.45.240.245/switch.php?xxxxx`页面设置一个 session id，然后在登陆页面填写表单 post 到`http://210.45.240.245/post.php`。此时千万要记得将之前的合法session id作为cookie的一部分提交出去。之后即拥有互联网通信权限。

### 老接口（172.16.200.11/172.16.200.12/172.16.200.13）
在部分时候，老接口也可以使用。老接口对于自动化登陆十分方便，没有 session 限制。可以参考 https://github.com/hongrunhui/hfut-autologin 进行登陆。

## TODO
编写自动登陆脚本，隐藏两种接口的不同。后期集成到一个C/C++程序中，方便在路由器上运行。