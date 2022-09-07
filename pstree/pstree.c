#include <stdio.h>
#include <assert.h>
#include <string.h>

void dosomething()
{

}

int main(int argc, char *argv[]) {
  // arg part
  int _numeric_out = 0;
  int _pid_out = 0;
  int _version_out = 0;

  // parse the arg
  for (int i = 1; i < argc; i++) {
    assert(argv[i]);
    if(!strcmp(argv[i], "-n")||!strcmp(argv[i],"--numeric-sort"))
      _numeric_out = 1;
    else if(!strcmp(argv[i], "-p")||!strcmp(argv[i],"--show-pids"))
      _pid_out = 1;
    else if(!strcmp(argv[i], "-V")||!strcmp(argv[i],"--version"))
      _version_out = 1;
    else
    {
      printf("Wrong arg input!\n");
      return 0;
    }
  }
  assert(!argv[argc]);
  
  // print out version info
  char *version_info = 
    "This is my first version of pstree!\n ";
  if(_version_out)
  {
    printf("%s", version_info);
    return 0;
  }

  if(_pid_out) dosomething();
  if(_numeric_out) dosomething();


  return 0;
}
