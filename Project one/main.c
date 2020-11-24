#include </usr/include/mysql/my_global.h>
#include </usr/include/mysql/mysql.h>
#include <stdio.h>
#include "functions.c"
#include "report.c"

int main(){
	int option;
	int cont;
	MYSQL * conn = connect_me_to_db();
		do{
			option = main_menu();
			if(option == 1){
				insert_school(conn);
			printf("    Do you want to continue [1/0]  :");
			scanf("%d",&cont);
		 	}else if(option == 2){
				insert_class(conn);
			printf("    Do you want to continue [1/0]  :");
			scanf("%d",&cont);
		 	}else if(option == 3){
				insert_student(conn);
			printf("    Do you want to continue [1/0]  :");
			scanf("%d",&cont);
			}else if(option == 4){
				insert_year(conn);
			printf("    Do you want to continue [1/0]  :");
			scanf("%d",&cont);
			}else if(option == 5){
				system("clear");
				print_result(conn);				
			printf("    Do you want to continue [1/0]  :");
			scanf("%d",&cont);
			}else if(option == 6){
				system("clear");
				printInFile(conn);				
			printf("    Do you want to continue [1/0]  :");
			scanf("%d",&cont);
			}else if(option == 7){
				printf("\n\t\tTHANK YOU FOR USING OUR APP !!!!\n");
			}
			else{
				printf("\n\n\t\tINVARED INPUT !!!!!\n");
				exit(0);
			}
			}while(option != 7);

return 0;
}
