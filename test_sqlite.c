#include <stdio.h>
#include "sqlite3.h"
#include<string.h>
#include<stdlib.h>

#define DBNAME "test.db"
static int exec_sql(char*);

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

void test_sql(){

        char *sql_create_customer =  "DROP TABLE IF EXISTS Customer;" \
                                     "CREATE TABLE Customer (" \
                                     "cust_id INT PRIMARY KEY," \
                                     "fname VARCHAR(50), " \
                                     "lname VARCHAR(50) );";
        char *sql_create_account = "DROP TABLE IF EXISTS Account;" \
                                    "CREATE TABLE Account (" \
                                    "account_id INT PRIMARY KEY," \
                                    "product_cd VARCHAR(50), " \
                                    "cust_id INT," \
                                    "balance INT," \
                                    "FOREIGN KEY(cust_id) REFERENCES Customer(cust_id));" ;

        char *sql_create_product = "DROP TABLE IF EXISTS Product;" \
                                    "CREATE TABLE Product(" \
                                    "product_cd VARCHAR(50) PRIMARY KEY," \
                                    "name       VARCHAR(50) );";

        char *sql_create_transaction = "DROP TABLE IF EXISTS aTransaction;" \
                                        "CREATE TABLE aTransaction(" \
                                        "txn_id INT PRIMARY KEY," \
                                        "txn_type_cd VARCHAR(50)," \
                                        "account_id INT," \
                                        "amount INT," \
                                        "txn_date date);";
        exec_sql(sql_create_customer);
        exec_sql(sql_create_account);
        exec_sql(sql_create_product);
        exec_sql(sql_create_transaction);

}

void createdb_for_ospdemo(){

        char* sql_s;
        char *sql_create_file = "CREATE TABLE IF NOT EXISTS File(" \
                                 "sha1 CHAR(41) PRIMARY KEY);";  /*41??*/

        /*用于登录的用户名应该是唯一的，这个用户名 *可以是邮箱之类的注册号*/
        char *sql_create_user = "CREATE TABLE IF NOT EXISTS User(" \
                                 "name VARCHAR(200) PRIMARY KEY," \
                                 "password VARCHAR(50)," \
                                 "level INT);";

        char *sql_create_userfile = "CREATE TABLE IF NOT EXISTS UserFile(" \
                                     "username VARCHAR(200)," \
                                     "filesha1 CHAR(41)," \
                                     "filename VARCHAR(200)," \
                                     "FOREIGN KEY(username) REFERENCES User(name)," \
                                     "FOREIGN KEY(filesha1) REFERENCES File(sha1)," \
                                     "PRIMARY KEY(username,filesha1));";
        sql_s = malloc(strlen(sql_create_file)+strlen(sql_create_user)+strlen(sql_create_userfile)+1);
        sql_s[0] = '\0';
        strcat(sql_s,sql_create_file);
        strcat(sql_s,sql_create_user);
        strcat(sql_s,sql_create_userfile);

        exec_sql(sql_s);
        free(sql_s);
}

/**********************************************************************
 * *sqlite 执行sql函数，包含连接，执行和关闭
 **********************************************************************
 *return:0 success
 *param:sql语句
***********************************************************************/
static int exec_sql(char *sql_s){

  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open(DBNAME, &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  rc = sqlite3_exec(db, sql_s,0, 0, &zErrMsg);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
 
}
static void test_sqlite(){

        
}

int main(int argc, char **argv){

//        test_sql();
        createdb_for_ospdemo();

        return 0;
}
