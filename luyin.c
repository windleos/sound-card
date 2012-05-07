//#include < fcntl.h >
#include < stdio.h >
#include < stdlib.h >
#include < string.h >
#include < unistd.h >
#include < sys/ioctl.h >
#include < sys/types.h >
#include < linux/kd.h >

#define DEFAULT_FREQ 440 
#define DEFAULT_LENGTH 200 
#define DEFAULT_REPS 1 
#define DEFAULT_DELAY 100 

typedef struct {
int freq; /* 我们期望输出的频率 */
int length; /* 发声长度*/
int reps; /* 重复的次数*/
int delay; 
} beep_parms_t;

void usage_bail ( const char *executable_name ) {
printf ( "Usage: \n \t%s [-f frequency] [-l length] [-r reps] [-d delay] \n ",
executable_name );
exit(1);
}

void parse_command_line(char **argv, beep_parms_t *result) {
char *arg0 = *(argv++);
while ( *argv ) {
if ( !strcmp( *argv,"-f" )) { /*频率*/
int freq = atoi ( *( ++argv ) );
if ( ( freq <= 0 ) | | ( freq > 10000 ) ) {
fprintf ( stderr, "Bad parameter: frequency must be from 1..10000\n" );
exit (1) ;
} else {
result->freq = freq;
argv++;
}
} else if ( ! strcmp ( *argv, "-l" ) ) { /*时长*/
int length = atoi ( *(++argv ) );
if (length < 0) {
fprintf(stderr, "Bad parameter: length must be >= 0\n");
exit(1);
} else {
result->length = length;
argv++;
}
} else if (!strcmp(*argv, "-r")) { /*重复次数*/
int reps = atoi(*(++argv));
if (reps < 0) {
fprintf(stderr, "Bad parameter: reps must be >= 0\n");
exit(1);
} else {
result->reps = reps;
argv++;
}
} else if (!strcmp(*argv, "-d")) { /* 延时 */
int delay = atoi(*(++argv));
if (delay < 0) {
fprintf(stderr, "Bad parameter: delay must be >= 0\n");
exit(1);
} else {
result->delay = delay;
argv++;
}
} else {
fprintf(stderr, "Bad parameter: %s\n", *argv);
usage_bail(arg0);
}
}
}

int main(int argc, char **argv) {
int console_fd;
int i; 

beep_parms_t parms = {DEFAULT_FREQ, DEFAULT_LENGTH, DEFAULT_REPS,
DEFAULT_DELAY};

parse_command_line(argv, &parms);


if ( ( console_fd = open ( "/dev/console", O_WRONLY ) ) == -1 ) {
fprintf(stderr, "Failed to open console.\n");
perror("open");
exit(1);
}


for (i = 0; i < parms.reps; i++) {

int magical_fairy_number = 1190000/parms.freq;

ioctl(console_fd, KIOCSOUND, magical_fairy_number); /* 开始发声 */
usleep(1000*parms.length); 
ioctl(console_fd, KIOCSOUND, 0); /* 停止发声*/
usleep(1000*parms.delay); 
} /* 重复播放*/
return EXIT_SUCCESS;
}
