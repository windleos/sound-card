#include <sys/soundcard.h>

#include <stdio.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

main()

{

int id,fd,i,j;
int dsp,seq,post,filebuf;

char testbuf[4096];

id=open("/dev/audio",O_RDWR);

fd=open("test.wav",O_RDWR);

if(id<0||fd<0){

printf("error in open the device!\n");

printf("id %d\t dsp%d\t seq%d\n",id,dsp,seq);

exit(-1);

}

post=0;

ioctl(id,SNDCTL_DSP_RESET,(char *)&i);

ioctl(id,SNDCTL_DSP_SYNC,(char *)&i);

i=1;

ioctl(id,SNDCTL_DSP_NONBLOCK,(char *)&i);

i=8000;

ioctl(id,SNDCTL_DSP_SPEED,(char *)&i);

i=1;

ioctl(id,SNDCTL_DSP_CHANNELS,(char *)&i);

i=8;

ioctl(id,SNDCTL_DSP_SETFMT,(char *)&i);

i=3;

ioctl(id,SNDCTL_DSP_SETTRIGGER,(char *)&i);

i=3;

ioctl(id,SNDCTL_DSP_SETFRAGMENT,(char *)&i);

i=1;

ioctl(id,SNDCTL_DSP_PROFILE,(char *)&i);

for(j=0;j<10;){

i=read(id,testbuf,4096);

if(i>0){

write(fd,filebuf,i);

j++;

}

}

close(fd);

close(id);

}
