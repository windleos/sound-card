
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/soundcard.h>

const char *sound_device_names[] = SOUND_DEVICE_NAMES;

int fd;                  
int devmask, stereodevs; 
char *name;

void usage()
{
  int i;

  fprintf(stderr, "usage: %s <device> <left-gain%%> <right-gain%%>\n"
	  "       %s <device> <gain%%>\n\n"
	  "Where <device> is one of:\n", name, name);
  for (i = 0 ; i < SOUND_MIXER_NRDEVICES ; i++)
    if ((1 << i) & devmask)
      fprintf(stderr, "%s ", sound_device_names[i]);
  fprintf(stderr, "\n");
  exit(1);
}

int main(int argc, char *argv[])
{
  int left, right, level;  
  int status;              
  int device;             
  char *dev;               
  int i;

  name = argv[0];

  fd = open("/dev/mixer", O_RDONLY);
  if (fd == -1) {
    perror("unable to open /dev/mixer");
    exit(1);
  }
  
  status = ioctl(fd, SOUND_MIXER_READ_DEVMASK, &devmask);
  if (status == -1)
    perror("SOUND_MIXER_READ_DEVMASK ioctl failed");
  status = ioctl(fd, SOUND_MIXER_READ_STEREODEVS, &stereodevs);
  if (status == -1)
    perror("SOUND_MIXER_READ_STEREODEVS ioctl failed");

  if (argc != 3 && argc != 4)
    usage();

  dev = argv[1];

  for (i = 0 ; i < SOUND_MIXER_NRDEVICES ; i++)
    if (((1 << i) & devmask) && !strcmp(dev, sound_device_names[i]))
      break;
  if (i == SOUND_MIXER_NRDEVICES) { 
    fprintf(stderr, "%s is not a valid mixer device\n", dev);
    usage();
  }

  device = i;

  if (argc == 4) {
    left  = atoi(argv[2]);
    right = atoi(argv[3]);
  } else {
    left  = atoi(argv[2]);
    right = atoi(argv[2]);
  }
  
  if ((left != right) && !((1 << i) & stereodevs)) {
    fprintf(stderr, "warning: %s is not a stereo device\n", dev);
  }
  
  level = (right << 8) + left;
  
  status = ioctl(fd, MIXER_WRITE(device), &level);
  if (status == -1) {
    perror("MIXER_WRITE ioctl failed");
    exit(1);
  }

  left  = level & 0xff;
  right = (level & 0xff00) >> 8;

  fprintf(stderr, "%s gain set to %d%% / %d%%\n", dev, left, right);

  close(fd);
  return 0;
}
