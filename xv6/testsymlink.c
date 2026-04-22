#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void) {
  printf(1, "Testing symlinks...\n");
  
  int fd = open("testfile", O_CREATE | O_RDWR);
  write(fd, "hello\n", 6);
  close(fd);

  symlink("testfile", "link1");
  symlink("link1", "link2");

  fd = open("link2", O_RDONLY);
  if(fd < 0){
    printf(1, "Failed to open link2\n");
  } else {
    char buf[10];
    read(fd, buf, 6);
    buf[6] = '\0';
    printf(1, "Read from link2: %s", buf);
    close(fd);
  }

  symlink("cycle1", "cycle2");
  symlink("cycle2", "cycle1");
  
  if(open("cycle1", O_RDONLY) < 0){
    printf(1, "Cycle detection successful\n");
  } else {
    printf(1, "Failed to detect cycle\n");
  }

  exit();
}

