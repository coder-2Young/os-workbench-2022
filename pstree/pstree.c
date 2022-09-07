#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  // arg part
  int _numeric_out = 0;
  int _pid_out = 0;
  int _version_out = 0;

  for (int i = 0; i < argc; i++) {
    assert(argv[i]);
    if(argv[i] == "-n"||"--numeric-sort")
      _numeric_out = 1;
    else if(*argv[i] == "-p"||"--show-pids")
      _pid_out = 1;
    else if(*argv[i] == "-V"||"--version")
      _version_out = 1;
    else
    {
      printf("Wrong arg input!\n");
      return 0;
    }
  }
  assert(!argv[argc]);

  char *version_info = 
    "This is my first version of pstree!\n ";
  if(_version_out)
  {
    printf("%s", version_info);
    return 0;
  }


  return 0;
}
