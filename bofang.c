#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<linux/soundcard.h>
#include<sys/ioctl.h>

#define Dsp_Device "/dev/dsp"
#define Sample_Size 16
#define Sample_Rate 15000

int play_sound(char *filename)
{
        struct stat stat_buf;
        unsigned char *buf=NULL;
        int handler,fd;
        int result;
        int arg,status;
        fd=open(filename,O_RDONLY);
        if(fd<0)
                return -1;
        if(fstat(fd,&stat_buf))
        {
                close(fd);
                return -1;
        }
        if(!stat_buf.st_size)
        {
                close(fd);
                return -1;
        }
        buf=malloc(stat_buf.st_size);
        if(!buf)
        {
                close(fd);
                return -1;
        }
        if(read(fd,buf,stat_buf.st_size)<0)
        {
                free(buf);
                close(fd);
                return -1;
        }
        handler=open(Dsp_Device,O_WRONLY);
        if(handler==-1)
        {
                printf("open Dsp_Device failed");
                return -1;
        }
        arg=Sample_Rate;
        status=ioctl(handler,SOUND_PCM_WRITE_RATE,&arg);
        if(status==-1)
        {
                printf("error from Sample_Rate");
                return -1;
        }
        arg=Sample_Size;
        status=ioctl(handler,SOUND_PCM_WRITE_BITS,&arg);
        if(status==-1)
        {
                printf("error from Sample_Size");
                return -1;
        }
        result=write(handler,buf,stat_buf.st_size);
        if(result==-1)
        {
                printf("Fail to play the sound");
                return -1;
        }
        free(buf);
        close(fd);
        return result;
}

int main()
{
        play_sound("/home/administrator/桌面/login.wav");
}
