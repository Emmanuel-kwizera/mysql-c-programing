#include </usr/include/mysql/my_global.h>
#include </usr/include/mysql/mysql.h>
#include <stdio.h>

//FUNCION TO VALIDATE THE CONNECTION
int validator(MYSQL* connection){
	if(connection==NULL){
		printf("Failed to create connection!!\n");
		exit(0);
	}
	fprintf(stderr,"%s",mysql_error(connection));
	exit(0);
}

// FUNCTION TO CONNECT TO DATABASE
MYSQL* connect_me_to_db(){
	MYSQL *primary_Connection=mysql_init(NULL);
	if(mysql_real_connect(primary_Connection,"localhost","kwizera","MysqlKwizera@123","C_programing_project_one",3306,NULL,0)==NULL)
		validator(primary_Connection);
	return primary_Connection;
}

// FUNCTION TO INSERT A SCHOOL
int insert_school(MYSQL * connection){
	char school_name[100] = "";
	char query[500]= "";
	printf("ENTER SCHOOL NAME HERE  :");
	scanf("%s",school_name);
// USING STRING CONCAT TO INSERT INTO TABLE IN DATABASE
	strcat(query,"INSERT INTO `schools` VALUES(NULL,'");
	strcat(query, school_name);
	strcat(query,"')");
	if(mysql_query(connection,query))
		validator(connection);
	else{
		printf("\n\t_________________________________________________\n\n");
		printf("\t\tSCHOOL  SUCCESSFULLY REGISTERED \n");
		printf("\n\t**************************************************\n\n");
	}
}

// FUNCTION TO GET SCHOOL ID
char * get_school_id(MYSQL * connection){
	int choice;
	char query[1000] = "SELECT * FROM `schools`";
	if(mysql_query(connection,query))
		validator(connection);

	MYSQL_RES *result_query=mysql_store_result(connection);
	int nums = mysql_num_fields(result_query);
	MYSQL_ROW num_row;
	int i = 0;
	char * school_id[300];
	printf("\t\tTHIS IS THE AVAILABLE SCHOOLS\n");
	printf("\n\t_________________________________________________\n\n");
	while(num_row = mysql_fetch_row(result_query)){
		school_id[i] = num_row[0];
		printf("\t   %d  %s \n",i+1,num_row[1]);
		i++;
	}
	printf("\n\t_________________________________________________\n\n");
	printf("\t\t\t ENTER YOUR CHOISE     : ");
	scanf("%d",&choice);
	if(choice < 1 || choice > i){
		printf("\n\n INVALIED INPUT\n");
		exit(0);
	}
	return school_id[choice-1];
}

// FUNCTION TO GET CLASSS ID 
char * get_class_id(MYSQL * connection,char * school_id){
	int choice;
	char query[900] = "";
	strcat(query,"SELECT * FROM `classes` WHERE `school_id`='");
	strcat(query,school_id);
	strcat(query,"'");
	if(mysql_query(connection,query))
		validator(connection);

	MYSQL_RES *result_query=mysql_store_result(connection);
	int nums = mysql_num_fields(result_query);
	MYSQL_ROW num_row;
	int i = 0;
	char * class_id[300];
	printf("\t\tTHIS IS THE AVAILABLE CLASSES\n");
	printf("\n\t_________________________________________________\n\n");
	while(num_row = mysql_fetch_row(result_query)){
		class_id[i] = num_row[0];
		printf("\t\t\t   %d  %s \n",i+1,num_row[1]);
		i++;
	}
	printf("\n\t_________________________________________________\n\n");
	printf("\t\t\t ENTER YOUR CHOICE    : ");
	scanf("%d",&choice);
	if(choice < 1 || choice > i){
		printf("\n\n INVALIED INPUT\n");
		exit(0);
	}
	return class_id[choice-1];
}

// FUNCTION TO INSERET A CLASS
void insert_class(MYSQL * connection){
	char class_name[100] = " ";
	char *school_id = get_school_id(connection);
	char query[500]= "";
	printf("ENTER CLASS NAME HERE  :");
	scanf("%s",class_name);
	strcat(query,"INSERT INTO `classes` VALUES(NULL,'");
	strcat(query, class_name);
	strcat(query,"','");
	strcat(query, school_id);
	strcat(query,"')");
	if(mysql_query(connection,query))
		validator(connection);
	else{
		printf("\n\t_________________________________________________\n\n");
		printf("\t    CLASS  SUCCESSFULLY REGISTERED \n");
		printf("\n\t**************************************************\n\n");
	}
}

//FUNCTION TO GET YEAR ID
char * get_year_id(MYSQL * connection){
	int choice;
	char class_name[100] = "";
	char query[1000] = "SELECT * FROM `years`";
	if(mysql_query(connection,query))
		validator(connection);
	
	MYSQL_RES *result_query=mysql_store_result(connection);
	int nums = mysql_num_fields(result_query);
	MYSQL_ROW num_row;
	int i = 0;
	char * year_id[300];
	printf("\n\t_________________________________________________\n\n");
	while(num_row = mysql_fetch_row(result_query)){
		year_id[i] = num_row[0];
		printf("\t\t\t   %d  %s \n",i+1,num_row[1]);
		i++;
	}
	printf("\n\t_________________________________________________\n\n");
	printf("\t\t\t ENTER YOUR CHOICE    : ");
	scanf("%d",&choice);
	if(choice < 1 || choice > i){
		printf("\n\n INVALIED INPUT\n");
		exit(0);
	}
	return year_id[choice-1];
}

// FUNCTION TO GET STUDENT ID	
char * get_student_id(MYSQL * connection,char * year_id,char * student_name){
	//int choice;
	char query[1000] = "SELECT * FROM `students` WHERE `year_id` = '";
	strcat(query,year_id);
	strcat(query,"' AND `name` = '");
	strcat(query,student_name);
	strcat(query,"'");
	if(mysql_query(connection,query))
		validator(connection);
	
	MYSQL_RES * result_query=mysql_store_result(connection);
	MYSQL_ROW num_row;
	char * student_id;
	while(num_row = mysql_fetch_row(result_query)){
		student_id = num_row[0];
	}
	return student_id;
}

// FUNCTION TO INSERT A STUDENT
void insert_student(MYSQL * connection){
	char student_name[600] = "";
	char * school_id = get_school_id(connection);
	char * class_id = get_class_id(connection,school_id);
	char year_id[100] = "";
	strcpy(year_id,get_year_id(connection));
	printf("\nENTER STUDENT NAME   :");
	scanf("%s",student_name);

	char query[1000] = "";
	strcat(query,"INSERT INTO `students` VALUES(NULL,'");
	strcat(query,student_name);
	strcat(query,"','");
	strcat(query,year_id);
	strcat(query,"')");
	if(mysql_query(connection,query))
		validator(connection);
	else{
		char student_id[100];
		strcpy(student_id,get_student_id(connection,year_id,student_name));
		char sql[150] = "";
		strcat(sql,"INSERT INTO `classes_students_tbl` VALUES('");
		strcat(sql,class_id);
		strcat(sql,"','");
		strcat(sql,student_id);
		strcat(sql,"','");
		strcat(sql,year_id);
		strcat(sql,"')");
		if(mysql_query(connection,sql))
			validator(connection);
		else{
			printf("\n\t_________________________________________________\n\n");
			printf("\t    STUDENT SUCCESSFULLY REGISTERED \n");
			printf("\n\t**************************************************\n\n");
		}
	}	
}

// FUNCTION TO INSERT A YAER 
void insert_year(MYSQL * connection){
	int year_num;
	char year_name[100];
	char query[500]= "";
	printf("ENTER A YEAR :");
	scanf("%d",&year_num);
	sprintf(year_name,"%d",year_num);
	strcat(query,"INSERT INTO `years` VALUES(NULL,'");
	strcat(query, year_name);
	strcat(query,"')");
	if(mysql_query(connection,query))
		validator(connection);
	else{
		printf("\n\t_______________________________________________________\n\n");
		printf("\t    YEAR  SUCCESSFULLY REGISTERED \n");
		printf("\n\t*******************************************************\n\n");
	}
}

// FUNCTION GENERATE THE MAIN MENU
int main_menu(){
	int choice;
	printf("\t       Welcome to our services here is our menu \n"); 
	printf("\t_______________________________________________________\n\n\n");
	printf("\t     1. Insert a new school \n");
	printf("\t     2. Insert a new class\n");
	printf("\t     3. Insert a new student \n");
	printf("\t     4. Insert a new year \n");
	printf("\t     5. Print  a result \n");
	printf("\t     6. Print  a result in file\n");
	printf("\t     7. Exit \n");
	printf("\n\n\t_______________________________________________________\n\n");
	printf("\t\t\t ENTER YOUR CHOISE     : ");
	scanf("%d",&choice);
	return choice;
}



