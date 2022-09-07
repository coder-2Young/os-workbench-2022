#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>


#define MAX_CHILDREN 20
#define DTYPE_DIR 4
#define MAX_PATH_LEN 50
#define MAX_PROC_NAME_LEN 50

void dosomething()
{
  return;
}

typedef struct Process
{
  char* _p_id;
  char *_p_name;
  struct Process *_p_children[MAX_CHILDREN];
  int _num_children;
}Process;

Process* init_process(char* pid, char* name)
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
    printf("PID: %s, NAME: %s\n", parent->_p_id,parent->_p_name);
    return;
  }
  for(int i=0; i<parent->_num_children;i++)
  {
    access_children(parent->_p_children[i]);
  }
  printf("PID: %s, NAME: %s\n", parent->_p_id,parent->_p_name);
}

char* cut_proc_name(char *proc_name)
{
  int cut_len = 6;
  char *new_proc_name = (char*)malloc(MAX_PROC_NAME_LEN);
  for(int i=0;i<MAX_PROC_NAME_LEN;i++)
  {
    new_proc_name[i] = proc_name[i+cut_len];
  }
  return new_proc_name;
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
    if(files->d_name[0]<='9' && files->d_name[0]>='0' && files->d_type == DTYPE_DIR) // it is a proc dir
    {
      char* pid = files->d_name;
      // printf("%s\n",pid);
      char status_file_path[MAX_PATH_LEN] = "";
      strcat(strcat(strcat(strcat(status_file_path,proc_path),"/"),pid),"/status");
      // printf("%s\n",status_file_path);
      char process_name[MAX_PROC_NAME_LEN];
      FILE *status = fopen(status_file_path,"r");
      if(status == NULL)
      {
        perror("Error opening file");
        return(-1);
      }
      if(fgets (process_name,MAX_PROC_NAME_LEN, status)!=NULL )
      {
        char* new_process_name=cut_proc_name(process_name);
        //printf("%s",new_process_name);
      }
      
    }
  }
  closedir(dir);


  // Process *p1 = init_process(1,"root");
  // Process *p2 = init_process(2,"file_sys");
  // insert_child(p1,p2);
  // access_children(p1);

  return 0;
}
