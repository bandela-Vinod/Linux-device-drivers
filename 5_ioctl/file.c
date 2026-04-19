
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>


#define WR_DATA _IOW('a','a',int32_t*)
#define RD_DATA _IOR('a','b',int32_t*)


int main()
{
        int val=230,res;

        int fd=open("/dev/ioctl",O_WRONLY);

        if(fd<0)
        {
                printf("open not possible!\n");

                return -1;
        }

        ioctl(fd, WR_DATA, &val); //This one first write val=230(this write val to kernal)
        ioctl(fd, RD_DATA, &res); //Hear get res=230(this value read from kernal)

        printf("The result is :%d\n",res);

        close(fd);

        return 0;
}

