#include</usr/include/mysql/mysql.h>
#include<stdio.h>

int main(){

printf("My server is: %s\n",mysql_get_client_info());

return 0;
}
