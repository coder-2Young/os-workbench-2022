#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>


#define MAX_CHILDREN 100
#define DTYPE_DIR 4
#define MAX_PATH_LEN 50
#define MAX_PROC_NAME_LEN 50
#define MAX_CHILDREN_LIST 200

void dosomething()
{
  return;
}

typedef struct Process
{
  char* _p_id;
  char *_p_name;
  struct Process *_p_children[MAX_CHILDREN];
  char *_p_children_pid[MAX_CHILDREN];
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

Process* add_children_tree(char* pid)
{
  char root_path[MAX_PATH_LEN];
  strcat(strcat(root_path,"/proc/"),pid);
  
  char status_path[MAX_PATH_LEN];
  strcat(strcat(status_path,root_path),"/status");
  char process_name[MAX_PROC_NAME_LEN];
  FILE *status = fopen(status_path,"r");
  if(status == NULL)
  {
    perror("Error opening file");
    return(NULL);
  }
  fgets(process_name,MAX_PROC_NAME_LEN, status);
  fclose(status);
  char* name = cut_proc_name(process_name);
  Process *root = init_process(pid,name);

  // char* children_path = root_path;
  // strcat(strcat(strcat(children_path,"/task/"),pid),"/children");

  printf("root path: %s",root_path);
  printf("status path: %s",status_path);
  // printf("children path: %s",children_path);


  // travel through children
  // FILE *children = fopen("/proc/1/task/1/children","r");
  // if(children == NULL)
  // {
  //   perror("Error opening file");
  //   return(-1);
  // }
  // char children_list[MAX_CHILDREN_LIST];
  // fgets(children_list,MAX_CHILDREN_LIST,children);
  // fclose(children);
  // char *child_pid = strtok(children_list, " ");
  // while(child_pid != NULL ) {
  //   //printf("%s\n", child_pid ); //printing each token
  //   root->_p_children_pid[root->_num_children] = child_pid;
  //   root->_num_children++;
  //   child_pid = strtok(NULL, " ");
  // }

  return root;
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
  if(_numeric_out) dosomething();// if not -n, out by name sort


  add_children_tree("1");
  // // create root node
  // char *root_path = "/proc/1";
  // char *root_name;
  // char *root_pid = "1";
  // char process_name[MAX_PROC_NAME_LEN];
  // FILE *status = fopen("/proc/1/status","r");
  // if(status == NULL)
  // {
  //   perror("Error opening file");
  //   return(-1);
  // }
  // fgets(process_name,MAX_PROC_NAME_LEN, status);
  // fclose(status);
  // root_name = cut_proc_name(process_name);
  // Process *root = init_process(root_pid,root_name);

  // // travel through children
  // FILE *children = fopen("/proc/1/task/1/children","r");
  // if(children == NULL)
  // {
  //   perror("Error opening file");
  //   return(-1);
  // }
  // char children_list[MAX_CHILDREN_LIST];
  // fgets(children_list,MAX_CHILDREN_LIST,children);
  // fclose(children);
  // char *child_pid = strtok(children_list, " ");
  // while(child_pid != NULL ) {
  //   //printf("%s\n", child_pid ); //printing each token
  //   root->_p_children_pid[root->_num_children] = child_pid;
  //   root->_num_children++;
  //   child_pid = strtok(NULL, " ");
  // }

  // //access_children(root);
  // for(int i=0;i<root->_num_children;i++)
  // {
  //   printf("%s\n",root->_p_children_pid[i]);
  // }



  return 0;
}
