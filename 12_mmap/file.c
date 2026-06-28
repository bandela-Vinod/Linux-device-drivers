#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>

#define DEVNAME "/dev/mydev"
#define MAP_SIZE 4096

int main(int argc, char *argv[])
{
	int fd;
	char *ptr;

	/* open the device*/

	fd=open(DEVNAME, O_RDWR);

	if(fd<0)
	{
		perror("open");
		return -1;

	}

	/* Map kernal memory into user space*/

	ptr = mmap(NULL,MAP_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		close(fd);
		return -1;
	}

	printf("Memory mapped successfully!\n");
	printf("Mapped Adress: %p \n",ptr);

	/* write to mapped memory if user provides data*/

	if(argc>1)
	{
		strncpy(ptr, argv[1], MAP_SIZE -1);
		ptr[MAP_SIZE -1] = '\0';

		printf("Written to mapped memory: %s\n",argv[1]);
	}

	/* Read from mapped memory*/

	printf("Data from mapped memory : %s \n",ptr);

	/* Unmap memory */

	munmap(ptr, MAP_SIZE);

	close(fd);

	return 0;
}
