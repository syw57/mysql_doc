#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * headname = "head.html";
char * footname = "footer.html";

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	FILE * fd;

	char tno[32] = "\0";
	char cno[16]="\0";
  char sno[16]="\0";
  char score[16]="\0";
	char ch;

	int status = 0;

	if(!(fd = fopen(headname, "r"))){
		fprintf(cgiOut, "Cannot open file, %s\n", headname);
		return -1;
	}
	ch = fgetc(fd);

	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
	fclose(fd);

	status = cgiFormString("tno",tno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get tno error!\n");
		return 1;
	}

	status = cgiFormString("cno",cno, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}
  status = cgiFormString("sno",sno, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sno error!\n");
		return 1;
	}
  status = cgiFormString("score",score, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get score error!\n");
		return 1;
	}

	//int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	sprintf(sql, "insert into Score values(%d ,%d,'%s',%d)", atoi(sno),atoi(cno),tno,atoi(score));
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "添加学生成绩成功！！！\n");
	mysql_close(db);
	return 0;
}
