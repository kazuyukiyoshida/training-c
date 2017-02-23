#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define LED_PATH "/sys/class/leds/LED"

int
set_brightness (int fd, char *value)
{
  int ret=-1;
  char current[2];

  ret = read(fd, current, 1);

  if (ret < 0)
    {
      fprintf(stderr,"[%s] read error. ret=%d, fd=%d, value=%d\n",__func__,ret,fd,value);
    }
  else
    {
      if(strcmp(current, value) != 0)
	{
	  ret = write (fd, value, 1);
	  if (ret < 0)
	    {
	      fprintf(stderr,"[%s] write error. ret=%d, fd=%d, value=%d\n",__func__,ret,fd,value);
	    }
	}
    }

  return ret;
}

int main(void)
{
  int fd;
  char led_path[64];
  int ret=-1;
  int i;

  for (i=1; i<=4; i++)
    {
      memset(led_path, 0, strlen(led_path));
      sprintf(led_path, "%s%d/brightness", LED_PATH, i);
      
      fd = open(led_path, O_RDWR);
      if (fd < 0)
	{
	  fprintf(stderr, "open error. %d, %s\n",fd,led_path);
	  return -1;
	}
      
      ret = set_brightness(fd, "1");
      if (ret < 0)
	{
	  fprintf(stderr, "set_brightness error. %d, %s\n",fd,led_path);
	  close(fd);
	  return -1;
	}

      close(fd);
      sleep(5);
    }

  for (i=1; i<=4; i++)
    {
      memset(led_path, 0, strlen(led_path));
      sprintf(led_path, "%s%d/brightness", LED_PATH, i);
      
      fd = open(led_path, O_RDWR);
      if (fd < 0)
	{
	  fprintf(stderr, "open error. %d, %s\n",fd,led_path);
	  return -1;
	}
      
      ret = set_brightness(fd, "0");
      if (ret < 0)
	{
	  fprintf(stderr, "set_brightness error. %d, %s\n",fd,led_path);
	  close(fd);
	  return -1;
	}

      close(fd);
      sleep(5);
    }

  return 0;
}
