#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>


#define MAX_CHILDREN 20
#define DTYPE_DIR 4

void dosomething()
{
  return;
}

typedef struct Process
{
  int _p_id;
  char *_p_name;
  struct Process *_p_children[MAX_CHILDREN];
  int _num_children;
}Process;

Process* init_process(int pid, char* name)
{
  Process *p = (Process*)malloc(sizeof(Process));
  p->_p_id = pid;
  p->_p_name = name;
  p->_num_children = 0;
  return p;
}

void insert_child(Process *parent, Process *child)
{
  parent->_p_children[parent->_num_children] = child;
  parent->_num_children++;
}

void access_children(Process *parent)
{
  if(parent->_num_children == 0) 
  {
    printf("PID: %d, NAME: %s\n", parent->_p_id,parent->_p_name);
    return;
  }
  for(int i=0; i<parent->_num_children;i++)
  {
    access_children(parent->_p_children[i]);
  }
  printf("PID: %d, NAME: %s\n", parent->_p_id,parent->_p_name);
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

  char *proc_path = "/proc";
  struct dirent *files;
  DIR *dir = opendir(proc_path);
  if (dir == NULL){
    printf("Directory cannot be opened!" );
    return 0;
  }
  while ((files = readdir(dir)) != NULL)
    // printf("%s + %d\n", files->d_name,files->d_type);
  {
    if(files->d_name[0]<='9' && files->d_name>=0 && files->d_type == DTYPE_DIR &&
        strcmp(files->d_name,".") && strcmp(files->d_name,"..")) // it is a proc dir
      printf("%s\n",files->d_name);
  }
  closedir(dir);


  // Process *p1 = init_process(1,"root");
  // Process *p2 = init_process(2,"file_sys");
  // insert_child(p1,p2);
  // access_children(p1);

  return 0;
}
