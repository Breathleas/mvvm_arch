#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME 	"/tmp/my_fifo"
#define BUFFER_SIZE	PIPE_BUF

int main(int argc, char *argv[])
{
	int pipe_fd;
	int res;
	int open_mode = O_RDONLY;
	char buffer[BUFFER_SIZE + 1];
	int bytes_read = 0;
	
	memset(buffer, '\0', sizeof(buffer));
	if(access(FIFO_NAME, F_OK) == -1) {
		res = mkfifo(FIFO_NAME, 0777);
		if(res != 0){
			fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}

	printf("Process %d opening FIFO O_WRONLY\n", getpid());
	pipe_fd = open(FIFO_NAME, open_mode);
	printf("Process %d result %d\n", getpid(), pipe_fd);
	
	if(pipe_fd != -1) {
		do{
			res = read(pipe_fd, buffer, BUFFER_SIZE);
			bytes_read += res;
		} while(res > 0);
		(void)close(res);
	} else {
		exit(EXIT_FAILURE);
	}
	printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
	exit(EXIT_SUCCESS);
}
