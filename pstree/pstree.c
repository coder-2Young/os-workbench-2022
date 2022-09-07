#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  // arg part
  int _numeric_out = 0;
  int _pid_out = 0;
  int _version_out = 0;

  for (int i = 0; i < argc; i++) {
    assert(argv[i]);
    printf("argv[%d] = %s\n", i, argv[i]);
  }

  assert(!argv[argc]);

  char *words = "It is a string";
  printf("%s",words);
  return 0;
}
