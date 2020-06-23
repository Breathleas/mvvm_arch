#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

void display_row() {
	unsigned int field_count;
	field_count = 0;
	while(field_count < mysql_field_count(&my_connection)) {
		printf("%s ", sqlrow[field_count]);
		field_count++;
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	int res;

	mysql_init(&my_connection);
	if(mysql_real_connect(&my_connection, "localhost", "root", "xxx", "db_cd", 0, NULL, 0)) {
		printf("Connection success\n");

		res = mysql_query(&my_connection, "select childno, name, age from children where age > 5");
		if (res) {
			printf("Select error: %s\n", mysql_error(&my_connection));
		} else {
			res_ptr = mysql_use_result(&my_connection);
			if(res_ptr) {
				printf("Retrieved %lu rows\n", (unsigned long)mysql_num_rows(res_ptr));
				while((sqlrow = mysql_fetch_row(res_ptr))) {
					printf("Fetched data...\n");
					display_row();
				}
				if(mysql_errno(&my_connection))
					fprintf(stderr, "Retrive error: %s\n", mysql_error(&my_connection));
				mysql_free_result(res_ptr);
			}
		}

		mysql_close(&my_connection);
	} else {
		fprintf(stderr, "Connection failed\n");
		if (mysql_errno(&my_connection)) {
			fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
		}
	}
	
	return EXIT_SUCCESS;
}
