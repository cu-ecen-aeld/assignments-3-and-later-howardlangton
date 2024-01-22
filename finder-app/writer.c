#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[])
{
 // Open syslog
  openlog(NULL, 0, LOG_USER);

 // Check argument count is 2 
  if (argc != 3)
  {	
     printf("Expected 2 arguments\n Usage: writer  writefile writestr\n");
     printf("You provided %d arguments\n", argc-1);
     return 1;
  } 

 // Open the file
  int fd;
  char *my_writefile = argv[1];
  char *my_writestr = argv[2];
  fd = open(my_writefile, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU | S_IRGRP | S_IROTH);
  int err = errno;
  if (fd == -1)
    {
      printf("Error creating file: %s\n", strerror(err));
      syslog(LOG_ERR, "Error creating file: %s\n", strerror(err));
      return 1;
    }

  ssize_t nr;
  size_t count = strlen(my_writestr);
  nr = write(fd, my_writestr, count);
  err = errno;
  if ( nr == -1 )
    {
      printf("Error writing %s to %s, error is %s\n", my_writestr, my_writefile, strerror(err));
      perror("write");
      syslog(LOG_ERR,"Error writing %s to %s, error is %s\n", my_writestr, my_writefile, strerror(err));
      return 1;
    } 
  else
    {
      syslog(LOG_DEBUG,"Writing %s to %s", my_writestr, my_writefile);
      printf("Writing %s to %s\n", my_writestr, my_writefile);
    }
}

