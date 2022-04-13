### 安装openssl

```shell
#下载openssl源码并解压
https://www.openssl.org/
tar -zxvf xxx.tar.gz
##编译安装
#进入解压后的文件目录
./config shared
#出现Configure for linux-x86_64配置就成功了

make
#出现Makefile:310:recipe for target 'test_cms' failed 和 Makefile:411: recipe for target 'tests' failed，查资料说是bug，不用管

make install(需要root权限)
#出现 POD document had syntax errors at /usr/bin/pod2man line 71.Makefile:594 recipe for target 'install_docs' failed.
#解决方法
mv /usr/bin/pod2man /usr/bin/pod2man_cp

#此时就安装完成了，默认安装在/usr/local/ssl 下

##创建软连接
#先备份原来的openssl
which openssl
mv /usr/bin/openssl /usr/bin/openssl-bak	路径根据上面的命令确定
ln -s /usr/local/ssl/bin/openssl /usr/bin/openssl

#gcc使用openssl库
vi /etc/ld.so.conf
#把/usr/local/openssl/lib	添加到最后一行
ldconfig

#test.cpp 测试openssl的功能
```

