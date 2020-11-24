#include </usr/include/mysql/my_global.h>
#include </usr/include/mysql/mysql.h>
 #include <my_byteorder.h>

#include<stdio.h>
void validator(MYSQL * connection){
if(connection==NULL){
printf("Failed to create connection!!\n");
exit(0);
}
fprintf(stderr,"%s",mysql_error(connection));
exit(0);
}

void connect_to_server(){

MYSQL *initial_connection=mysql_init(NULL);

initial_connection=mysql_real_connect(initial_connection,"localhost","kwizera","MysqlKwizera@123",NULL,3306,NULL,0);

if(initial_connection==NULL){
validator(initial_connection);
}


int query_result = mysql_query(initial_connection,"create database c_programing_first_db");

/*if(query_result==1){
fprintf(stderr,"%s",mysql_error(initial_connection));
exit(0);
}*/
if(query_result){
validator(initial_connection);
}


}

//FUNCTION TO CREATE CONNECTION TO DATABASE
MYSQL *connect_to_db(){
MYSQL *initial_connection=mysql_init(NULL);
initial_connection=mysql_real_connect(initial_connection,"localhost","kwizera","MysqlKwizera@123","c_programing_first_db",3306,NULL,0);
if(initial_connection==NULL){
validator(initial_connection);
}
}

//FUNCTION FOR CREATING TABLE
void createTable(MYSQL *connection){

int query_result = mysql_query(connection,"CREATE TABLE  first_table(id int primary key auto_increment,name varchar(255) not null,email varchar(255) not null)");
if(query_result)
validator(connection);
}


//FUNCTION FOR INSERTING DATA
void addData(MYSQL *connection){
int query_result = mysql_query(connection,"insert into first_table(name,email) values('MyName','myname@gmail.com')");
int query_result_two = mysql_query(connection,"insert into first_table(name,email) values('Annabelle','anna@gmail.com')");
if(query_result && query_result_two)
validator(connection);
}

//FUNCTION FOR READING DATA
void readDAtaFromTable(MYSQL *connection){
int query_flag = mysql_query(connection,"select * from first_table");
if(query_flag)
validator(connection);

MYSQL_RES *query_result=mysql_store_result(connection);

MYSQL_ROW result_row;

int num_colums=mysql_num_fields(query_result);

while(result_row = mysql_fetch_row(query_result)){
	for(int i=0;i<num_colums;i++){
		printf("%s",result_row[i]);
		printf("\n");
		printf("---------------\n");
	}
}

}






int main(){

///connect_to_server();
MYSQL *db_connection = connect_to_db();
createTable(db_connection);
addData(db_connection);
readDAtaFromTable(db_connection);
return 0;
}


// COMMAN TO COMPILE AND RUN 
// gcc -o database mysql_demo.c -I/usr/include/mysql $(mysql_config --libs)
// ./database
