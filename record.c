#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/soundcard.h>
#include <termios.h>

#define LENGTH    10  
#define RATE    9600 
#define SIZE    8   
#define CHANNELS 1   
#define RSIZE    8   

struct fhead
{
    unsigned char a[4];
    long int b;        
    unsigned char c[4];
    unsigned char d[4];
    long int e;       
    short int f;       
    short int g;      
    long int h;        
    long int i;        
    short int j;      
    short int k;       
    unsigned char p[4];
    long int q;        
}wavehead;
int main(void)
{
    int fd_r;
    int fd_w;
    int fd_f;
    int i;
    int arg;  
    int status;
    unsigned char buf[RSIZE]; 
   
    wavehead.a[0]='R';
    wavehead.a[1]='I';
    wavehead.a[2]='F';
    wavehead.a[3]='F';
    wavehead.b=LENGTH*RATE*CHANNELS*SIZE/8-8;
    wavehead.c[0]='W';
    wavehead.c[1]='A';
    wavehead.c[2]='V';
    wavehead.c[3]='E';
    wavehead.d[0]='f';
    wavehead.d[1]='m';
    wavehead.d[2]='t';
    wavehead.d[3]=' ';
    wavehead.e=16;
    wavehead.f=1;
    wavehead.g=CHANNELS;
    wavehead.h=RATE;
    wavehead.i=RATE*CHANNELS*SIZE/8;
    wavehead.j=CHANNELS*SIZE/8;
    wavehead.k=SIZE;
    wavehead.p[0]='d';
    wavehead.p[1]='a';
    wavehead.p[2]='t';
    wavehead.p[3]='a';
    wavehead.q=LENGTH*RATE*CHANNELS*SIZE/8;
  
    fd_r= open("/dev/dsp", O_RDONLY,0777);
    if (fd_r < 0)
    {
        printf("cannot open /dev/dsp device");
        return 1;
    }
    arg = SIZE;
    status = ioctl(fd_r, SOUND_PCM_WRITE_BITS, &arg);
    if (status == -1)
    {
        printf("cannot set SOUND_PCM_WRITE_BITS ");
        return 1;
    }
    arg = CHANNELS;
    status = ioctl(fd_r, SOUND_PCM_WRITE_CHANNELS, &arg);
    if (status == -1)
    {
        printf("cannot set SOUND_PCM_WRITE_CHANNELS");
        return 1;
    }
    arg = RATE;
    status = ioctl(fd_r, SOUND_PCM_WRITE_RATE, &arg);
    if (status == -1)
    {
        printf("cannot set SOUND_PCM_WRITE_WRITE");
        return 1;
    }

    fd_w = open("/dev/dsp", O_WRONLY,0777);
    if (fd_w < 0)
    {
        printf("cannot open sound device");
        return 1;
    }
    arg = SIZE;
    status = ioctl(fd_w, SOUND_PCM_WRITE_BITS, &arg);
    if (status == -1)
    {
        printf("cannot set size");
        return 1;
    }
    arg = CHANNELS;
    status = ioctl(fd_w, SOUND_PCM_WRITE_CHANNELS, &arg);
    if (status == -1)
    {
        printf("cannot set channel");
        return 1;
    }
    arg = RATE;
    status = ioctl(fd_w, SOUND_PCM_WRITE_RATE, &arg);
    if (status == -1)
    {
        printf("cannot set rate");
        return 1;
    }
    
    if(( fd_f = open("./sound.wav", O_CREAT|O_RDWR,0777))==-1)

        printf("cannot creat the sound file");

    if((status = write(fd_f, &wavehead, sizeof(wavehead)))==-1)

        printf("cannot write the sound head");

    for(i=0;i<(LENGTH*RATE*SIZE*CHANNELS/8)/RSIZE;i++)
    {

        status = read(fd_r, buf, sizeof(buf));
        if (status != sizeof(buf))
            printf("read wrong ");

        if(write(fd_f, buf, status)==-1)
            printf("write wrong");
    }
    close(fd_r);
    close(fd_f);
    printf("Do you want to play ?    ( y / n )");
    if(getchar()=='y')
    {
        printf("start:\n");
        if(( fd_f = open("./sound.wav", O_RDONLY,0777))==-1)
            printf("cannot creat the sound file");
        
	lseek(fd_f,44,SEEK_SET);
        
	for(i=0;i<(LENGTH*RATE*SIZE*CHANNELS/8)/RSIZE;i++)
        {
            status = read(fd_f, buf, sizeof(buf));
            
		if (status != sizeof(buf))
                printf("write wrong");

            status = write(fd_w, buf, sizeof(buf));
            	if (status != sizeof(buf))
                printf("write file wrong");
        }
        close(fd_f);
        close(fd_w);
        return 0;
    }
    else
    {
        printf("exit");
        return 0;
    }
}
