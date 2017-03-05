#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define GPIO67_PATH "/sys/class/gpio/gpio67"
#define GPIO69_PATH "/sys/class/gpio/gpio69"
#define GPIO71_PATH "/sys/class/gpio/gpio71"
#define GPIO73_PATH "/sys/class/gpio/gpio73"

enum {
  INPUT_MODE,
  OUTPUT_MODE
};

int
set_gpio_change_mode (char *path, int mode)
{
  int fd = -1;
  int ret = -1;

  fprintf(stderr,"[%s] start...\n",__func__);

  fd = open(path, O_WRONLY|O_TRUNC);
  if (fd < 0)
    {
      fprintf(stderr, "open error. %d, %s\n",fd,path);
      return -1;
    }
  if (mode == OUTPUT_MODE)
    {
      ret = write(fd, "out", 3);
      if (ret < 0)
	fprintf(stderr,"[%s] write error. %s <= out \n",__func__,path);
    }
  else
    {
      ret = write(fd, "in", 2);
      if (ret < 0)
	fprintf(stderr,"[%s] write error. %s <= in \n",__func__,path);
    }
  close(fd);

  return ret;
}

int
set_gpio_value (char *path, int value)
{
  int fd = -1;
  int ret = -1;

  fprintf(stderr,"[%s] start... %s : %d\n",__func__,path,value);

  fd = open(path, O_WRONLY|O_TRUNC);
  if (fd < 0)
    {
      fprintf(stderr, "open error. %d, %s\n",fd,path);
      return -1;
    }

  if (value == 1)
    {
      ret = write(fd, "1", 1);
    }
  else
    {
      ret = write(fd, "0", 1);
    }
  if (ret < 0)
    fprintf(stderr,"[%s] write error. %s <= %d \n",__func__,path,value);

  return 0;
}

int
set_all_gpio_change_mode (int mode)
{
  char gpio_path[64];
  int ret = -1;

  fprintf(stderr,"[%s] start... mode=%d\n",__func__,mode);
  
  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/direction", GPIO67_PATH);
  ret = set_gpio_change_mode(gpio_path, mode);
  if (ret < 0)
    return -1;
  
  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/direction", GPIO69_PATH);
  ret = set_gpio_change_mode(gpio_path, mode);
  if (ret < 0)
    return -1;

  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/direction", GPIO71_PATH);
  ret = set_gpio_change_mode(gpio_path, mode);
  if (ret < 0)
    return -1;

  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/direction", GPIO73_PATH);
  ret = set_gpio_change_mode(gpio_path, mode);
  if (ret < 0)
    return -1;

  return 0;
}

int
car_advance (void)
{
  char gpio_path[64];
  int ret = -1;
  
  fprintf(stderr,"[%s] start...\n",__func__);

  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/value", GPIO67_PATH);
  ret = set_gpio_value(gpio_path, 1);
  if (ret < 0)
    return -1;

  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/value", GPIO71_PATH);
  ret = set_gpio_value(gpio_path, 1);
  if (ret < 0)
    return -1;

  return 0;
}

int
car_turn_left (void)
{
  char gpio_path[64];
  int ret = -1;

  fprintf(stderr,"[%s] start...\n",__func__);

  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/value", GPIO71_PATH);
  ret = set_gpio_value(gpio_path, 1);
  if (ret < 0)
    return -1;

  return 0;
}

int
car_turn_right (void)
{
  char gpio_path[64];
  int ret = -1;

  fprintf(stderr,"[%s] start...\n",__func__);

  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/value", GPIO67_PATH);
  ret = set_gpio_value(gpio_path, 1);
  if (ret < 0)
    return -1;

  return 0;
}

int
reset_gpio_value (void)
{
  char gpio_path[64];
  int ret = -1;
  
  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/value", GPIO67_PATH);
  ret = set_gpio_value(gpio_path, 0);
  if (ret < 0)
    return -1;

  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/value", GPIO69_PATH);
  ret = set_gpio_value(gpio_path, 0);
  if (ret < 0)
    return -1;

  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/value", GPIO71_PATH);
  ret = set_gpio_value(gpio_path, 0);
  if (ret < 0)
    return -1;

  memset(gpio_path, 0, strlen(gpio_path));
  sprintf(gpio_path, "%s/value", GPIO73_PATH);
  ret = set_gpio_value(gpio_path, 0);
  if (ret < 0)
    return -1;

  return 0;
}

int
main(void)
{
  int fd;
  char led_path[64];
  int ret=-1;
  int i;

  fprintf(stderr,"[%s] start...\n",__func__);

  ret = set_all_gpio_change_mode(OUTPUT_MODE);
  if (ret < 0)
    {
      fprintf(stderr,"[%s] gpio output mode error.\n",__func__);
    }

  ret = reset_gpio_value();
  sleep (3);

  ret = car_advance();
  sleep (1);

  ret = reset_gpio_value();
  sleep (3);

  ret = car_turn_left();
  sleep (1);

  ret = reset_gpio_value();
  sleep (3);

  ret = car_turn_right();
  sleep (1);

  ret = reset_gpio_value();
  sleep (3);
  
  ret = set_all_gpio_change_mode(INPUT_MODE);
  if (ret < 0)
    {
      fprintf(stderr,"[%s] gpio input mode error.\n",__func__);
    }
  
  return 0;
}
