1、平台：WIN10;

2、软件：VS2019、MySQL开发包mysql-8.0.24;

3、如果VS报错，显示找不到libmysql.dll？

​       需要在VS2019中在项目属性页的“配置属性”-“调试”-“环境” 中编辑，把环境设置为数据库的bin文件夹即可，注意末尾分号要用半角的。参考[【VS2019/C++/报错】由于找不到libmysql.dll/由于找不到libssl-1_1-x64.dll，无法继续执行代码_Amanda1m的博客-CSDN博客](https://blog.csdn.net/m0_37764065/article/details/107376783)

```cpp
PATH=...\mysql-8.0.24-winx64\bin;
```

4、MySQL中创建数据库mysql，在mysql中创建表person(name,age,sex)
