void print_result(MYSQL * connection){

// GETT ALL YEARS
	char query[700]= "select * from `years`";
	int v=0;
	if(mysql_query(connection,query))
		validator(connection);
	MYSQL_RES * result_query=mysql_store_result(connection);
	MYSQL_ROW num_row;
	
	char year_id[1000][1000];
	char year_name[1000][1000];
	while(num_row = mysql_fetch_row(result_query)){
		strcpy(year_id[v],num_row[0]);
		strcpy(year_name[v],num_row[1]);
		v++;
	}

// GET ALL SCHOOLS
	strcpy(query, "select * from `schools`");
	int k = 0;
	if(mysql_query(connection,query))
		validator(connection);
	result_query=mysql_store_result(connection);
	char school_id[1000][1000];
	char school_name[1000][1000];
	while(num_row = mysql_fetch_row(result_query)){
		strcpy(school_id[k],num_row[0]);
		strcpy(school_name[k],num_row[1]);
		k++;
	}
	printf("\033[1;32m");
	printf("\n\n\t\tHERE IS THE REPORT FOR SCHOOLS\n\n");
	printf("\033[0m");
	printf("\t\t\t\t\t ACADEMIC YEAR\n");
	printf("\tSCHOOLS\t\t     CLASSES");
	for(int w = 0; w < v;w++){
		printf("\t| %s ",year_name[w]);
	}
	printf("\t| TOTAL");
	
	int sum_sums[1000];
	for(int i = 0; i < k;i++){
		printf("\n\t_____________________________________________________________________________\n\n");
		printf("\t%s\n",school_name[i]);
	strcpy(query, "select * from `classes` where school_id = '");
	strcat(query,school_id[i]);
	strcat(query,"'");
	int z = 0;
	if(mysql_query(connection,query))
		validator(connection);
	result_query=mysql_store_result(connection);
	
	char class_id[1000][1000];
	char class_name[1000][1000];
	while(num_row = mysql_fetch_row(result_query)){
		strcpy(class_id[z],num_row[0]);
		strcpy(class_name[z],num_row[1]);
		z++;
	}
		int array[1000];
		int n = 0;
		for(int j = 0; j < z;j++){
			int sum_class = 0;
			printf("\t\t\t\t %s \t",class_name[j]);
		for(int o = 0; o < v;o++){
               		strcpy(query,"");
                	strcat(query,"SELECT COUNT(*) from classes_students_tbl inner join classes on classes_students_tbl.class_id = classes.id 				inner join students on classes_students_tbl.student_id = students.id WHERE class_id = '");
                	strcat(query,class_id[j]);
	                strcat(query,"' AND classes_students_tbl.year_id = '");
        	        strcat(query,year_id[o]);
        	        strcat(query,"'");
                if(mysql_query(connection,query))
                    validator(connection);
		result_query=mysql_store_result(connection);
		while(num_row = mysql_fetch_row(result_query)){
                printf("| %s\t",num_row[0]);
                sum_class += atoi(num_row[0]);
                array[o] += atoi(num_row[0]);
                sum_sums[o] += atoi(num_row[0]);
		}
		}
		printf("| %d\n",sum_class);
		}
		printf("\n");
		printf("\tTOTAL FOR %s\t\t\t",school_name[i]);
		for(int b=0;b<v;b++){
			printf("| %d\t",array[b]);
			n += array[b];
			//sumOfSums += n;
			array[b]=0;
		}
		printf("| %d\t",n);
		
	}
		printf("\n\t_____________________________________________________________________________\n");
		printf("\t TOTAL FOR ALL\t\t\t");
		int tots=0;
			for(int s=0;s<v;s++){
				printf("| %d\t",sum_sums[s]);
				tots+=sum_sums[s];
				sum_sums[s]=0;
			}
		printf("| %d\t",tots);
	printf("\n\t*****************************************************************************\n\n");
}

void printInFile(MYSQL * connection){
        FILE * schoolFile;
	schoolFile = fopen("schools.csv","w");char query[700]= "select * from `years`";
	int v=0;
	if(mysql_query(connection,query))
		validator(connection);
	MYSQL_RES * result_query=mysql_store_result(connection);
	MYSQL_ROW num_row;
	
	char year_id[1000][1000];
	char year_name[1000][1000];
	while(num_row = mysql_fetch_row(result_query)){
		strcpy(year_id[v],num_row[0]);
		strcpy(year_name[v],num_row[1]);
		v++;
	}
	strcpy(query, "select * from `schools`");
	int k = 0;
	if(mysql_query(connection,query))
		validator(connection);
	result_query=mysql_store_result(connection);
	char school_id[1000][1000];
	char school_name[1000][1000];
	while(num_row = mysql_fetch_row(result_query)){
		strcpy(school_id[k],num_row[0]);
		strcpy(school_name[k],num_row[1]);
		k++;
	}
	//fprintf(schoolFile,"\n\n,,HERE IS THE REPORT FOR SCHOOLS\n\n");
	fprintf(schoolFile,",,,,, ACADEMIC YEAR\n");
	fprintf(schoolFile,"SCHOOLS,,CLASSES");
	for(int w = 0; w < v;w++){
		fprintf(schoolFile,",%s",year_name[w]);
	}
	fprintf(schoolFile,",TOTAL\n");
	int sum_sums[1000];
	for(int i = 0; i < k;i++){
		fprintf(schoolFile,"%s\n",school_name[i]);
	strcpy(query, "select * from `classes` where school_id = '");
	strcat(query,school_id[i]);
	strcat(query,"'");
	int z = 0;
	if(mysql_query(connection,query))
		validator(connection);
	result_query=mysql_store_result(connection);
	
	char class_id[1000][1000];
	char class_name[1000][1000];
	while(num_row = mysql_fetch_row(result_query)){
		strcpy(class_id[z],num_row[0]);
		strcpy(class_name[z],num_row[1]);
		z++;
	}
	        int array[1000];
		int n = 0;
		for(int j = 0; j < z;j++){
			int sum_class = 0;
			fprintf(schoolFile,",, %s ,",class_name[j]);
			for(int o = 0; o < v;o++){
               		strcpy(query,"");
                	strcat(query,"SELECT COUNT(*) from classes_students_tbl inner join classes on classes_students_tbl.class_id = classes.id 				inner join students on classes_students_tbl.student_id = students.id WHERE class_id = '");
                	strcat(query,class_id[j]);
	                strcat(query,"' AND classes_students_tbl.year_id = '");
        	        strcat(query,year_id[o]);
        	        strcat(query,"'");
                if(mysql_query(connection,query))
                    validator(connection);
		result_query=mysql_store_result(connection);
		while(num_row = mysql_fetch_row(result_query)){
                fprintf(schoolFile,"%s\t",num_row[0]);
                sum_class += atoi(num_row[0]);
                array[o] += atoi(num_row[0]);
                sum_sums[o] += atoi(num_row[0]);
		}
		}
		fprintf(schoolFile,"%d\n",sum_class);
		}
		fprintf(schoolFile,"\n");
		fprintf(schoolFile,"TOTAL FOR %s,,,",school_name[i]);
		for(int b=0;b<v;b++){
			fprintf(schoolFile,"%d,",array[b]);
			n += array[b];
			//sumOfSums += n;
			array[b]=0;
		}
		fprintf(schoolFile," %d,\n",n);
		}
		fprintf(schoolFile,"TOTAL FOR ALL,,,");
		int tots=0;
			for(int s=0;s<v;s++){
				fprintf(schoolFile,"%d\t",sum_sums[s]);
				tots+=sum_sums[s];
				sum_sums[s]=0;
			}
		fprintf(schoolFile,"%d,",tots);
	fclose(schoolFile);
}


