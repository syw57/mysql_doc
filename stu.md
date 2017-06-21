# 学生信息管理系统
## 数据库设计
### 学生信息表Information设计
| 中文名 | 列名 | 字段属性 | 备注 |
|-------|------|--------|-----|
| 学号 | SNO | char(12) |  主键 学号 |
| 学生姓名 | SNAME | char(10) | |
| 居住地 | FPLACE | char(20) | |
| 性别 | SEX | char(2) | |
| 年龄 | AGE | int | |
| 院系 | SCNO | char(2) | 外键 SCNO |
### 院系表School设计
| 中文名 | 列名 | 字段属性  | 备注 |
|-------|------|--------|-----|
| 院系编号 | SCNO | char(2) | 主键 |
| 院系名称 | SCNAME | char(20) | |
| 主任 | DEAN | char(10) | |
### 教师信息表Teacher设计
| 中文名 | 列名 | 字段属性  | 备注 |
|-------|------|--------|-----|
| 教师编号 | TNO | char(3) | 主键 |
| 教师姓名 | TNAME | char(20) | |
| 职称 | TITLE | char(10) | |
| 院系编号 | SCNO | char(2) | 外键 SCNO |
### 课程表Course设计
| 中文名 | 列名 | 字段属性  | 备注 |
|-------|------|--------|-----|
| 课程编号 | CNO | char(3) | 主键 |
| 课程名称 | CNAME | char(15) | |
### 教师授课表TC设计
| 中文名 | 列名 | 字段属性  | 备注 |
|-------|------|--------|-----|
| 教师编号 | TNO | char(3) | 主键 外键 TNO|
| 课程编号 | CNO | char(3) | 主键 外键 CNO |
### 成绩表Score设计
| 中文名 | 列名 | 字段属性 | 备注 |
|-------|------|--------|-----|
| 学号 | SNO | char(12) | 主键 外键 SNO |
| 教师编号 | TNO | char(3) | 主键 外键 TNO |
| 课程编号 | CNO | char(3) | 主键 外键 CNO |
| 成绩 | SCROE | int(11) ||
## CGI程序设计接口
#### 连接数据库接口
```c
//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
```

手册：mysql Documentation
编写：```html #include <mysql/mysql.h>```
编译：```html gcc  test.c  -o test  -lmysqlclient```

```c 
MYSQL *mysql_init(MYSQL *mysql)
```
功能：初始化函数，参数为NULL即可，接收返回值。
     失败，NULL

```c 
MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
```
功能：连接mysql服务器
      失败，NULL

```c 
void mysql_close(MYSQL *mysql)
```
功能：关闭服务器连接

```c 
int mysql_real_query(MYSQL *mysql, const char *stmt_str, unsigned long length)
```
功能：执行sql语句，sql语句不能以“；”结尾
      成功，0
      失败， 非0

```c 
int mysql_query(MYSQL *mysql, const char *stmt_str)
```
功能：执行sql语句，sql语句不能以“；”结尾

```c 
MYSQL_RES *mysql_store_result(MYSQL *mysql)
```
功能：存储 mysql_query()  或者  mysql_read_query() 的数据
     失败， NULL

```c 
MYSQL_RES *mysql_use_result(MYSQL *mysql)
```
功能：接收结果，速度要比mysql_use_result()快。

```c 
void mysql_free_result(MYSQL_RES *result)
```
功能：释放空间

```c 
my_ulonglong mysql_num_rows(MYSQL_RES *result)
```
功能：返回 mysql_store_result 的记录个数

```c 
my_ulonglong mysql_affected_rows(MYSQL *mysql)
```
功能：得到执行sql语句之后改变的记录数

```c 
const char *mysql_error(MYSQL *mysql)
```
功能：返回出错提示

```c 
MYSQL_FIELD *mysql_fetch_field(MYSQL_RES *result)
```
功能：返回集合中列的定义   
MYSQL_FIELD *field;
```c
while((field = mysql_fetch_field(result)))
{
    printf("field name %s\n", field->name);
}
```
```c
MYSQL_FIELD *mysql_fetch_fields(MYSQL_RES *result)
```
功能：返回集合中列的数组
```c
unsigned int num_fields;
unsigned int i;
MYSQL_FIELD *fields;

num_fields = mysql_num_fields(result);
fields = mysql_fetch_fields(result);
for(i = 0; i < num_fields; i++)
{
   printf("Field %u is %s\n", i, fields[i].name);
}

unsigned int mysql_num_fields(MYSQL_RES *result)
```
功能：返回集合中列的个数
```c
my_ulonglong mysql_num_rows(MYSQL_RES *result）
```
功能：返回集合中行的个数
```c
MYSQL_ROW mysql_fetch_row(MYSQL_RES *result)
```
功能：返回集合中的一行， 结束或者错误返回NULL
```c
unsigned long *mysql_fetch_lengths(MYSQL_RES *result)
```
功能：返回当前行中每一个字段值的长度 数组。
