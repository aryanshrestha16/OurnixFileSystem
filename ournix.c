/* This File will allow the simulation of files and subdirectories. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ournix.h"

/* Prototypes */
void mkfs(Ournix *const filesystem);
int touch(Ournix *const filesystem, const char name[]);
int mkdir(Ournix *const filesystem, const char name[]);
int cd(Ournix *const filesystem, const char name[]);
int ls(Ournix *const filesystem, const char name[]);
void pwd(Ournix *const filesystem);
void rmfs(Ournix *const filesystem);
int rm(Ournix *const filesystem, const char name[]);
int fwd_slash(const char name[]);
void pwd_recursion(File *curr, File *root, File *last);
void remove_directory(File *curr);
void ls_helper(File *curr);
int contains_file(File *curr, const char name[]);
/* This function will initialize the Ournix parameter. */
void mkfs(Ournix *const filesystem){
  filesystem->root = malloc(sizeof(File));
  filesystem->root->name = malloc(sizeof(char) + 1);
  strcpy(filesystem->root->name,"/");
  filesystem->root->type = malloc(sizeof(char) + 1);
  strcpy(filesystem->root->type,"D"); /* Setting the root as a directory */
  filesystem->root->timestamp = 0;
  filesystem->root->child = NULL;
  filesystem->root->parent = NULL;
  filesystem->current = filesystem->root;
}
/* This function will create a file and if the file exists it will touch it incrementing its timestamp by 1. */
int touch(Ournix *const filesystem, const char name[]){
  File *head = NULL , *curr = NULL, *new_file = NULL;
  if (name != NULL && filesystem != NULL && filesystem->current != NULL){ /* Check whether the paramenters are null */
    if  (name[0] != '\0' && fwd_slash(name) != 0 ){
      if ( strcmp(name,".") != 0 && strcmp(name,"..") != 0 && strcmp(name,"/") != 0){ /* Check whehter the name is valid */
	head = filesystem->current->child;
	while (head != NULL){
	  if (strcmp(head->name,name) == 0){
	    if (strcmp(head->type, "F") == 0 ){
	      head->timestamp = head->timestamp + 1;
	      return 1;
	    }
	    else 
	      return 1;
	  }
	  head = head->next;
	}
	new_file = malloc(sizeof(File));
	new_file->type = malloc(1 + sizeof(char));
	new_file->name = malloc((strlen(name) + 1 )* sizeof(char));
	strcpy(new_file->name, name);
	strcpy(new_file->type, "F");
	new_file->timestamp = 1;
	new_file->child = NULL;
	new_file->parent = filesystem->current;
	curr = filesystem->current->child;
	if (curr == NULL){ /* If the directory is empty */
	  filesystem->current->child = new_file;
	  new_file->next = NULL;
	}
	/* To store the files in an increasing lexicographic order */
	else if (curr != NULL && strcmp(curr->name, new_file->name) > 0){ 
	  filesystem->current->child = new_file;
	  new_file->next = curr;
	}
	else {
	  while(curr != NULL && strcmp(curr->name, new_file->name) < 0){
	    head = curr;
	    curr = curr->next;
	  }
	  if (curr == NULL){
	    head->next = new_file;
	    new_file->next = NULL;
	  }
	  else{
	    head->next = new_file;
	    new_file->next = curr;
	  }
	}
      }    return 1;
    }
    return 0;
  }
  return 0;
}
/* This function is used to create a directory. */
int mkdir(Ournix *const filesystem, const char name[]){
  
  File *head = NULL , *curr = NULL, *new_file = NULL;
  if (name != NULL && filesystem != NULL && filesystem->current != NULL){ /* Check whether the paraments are null */
    if (name[0] != '\0' && strcmp(name,"/") != 0 && strcmp(name,".") != 0 && strcmp(name,"..") != 0 && strchr(name,'/') == NULL){ /* Check whether the name is valid or not. */
      if (contains_file(filesystem->current, name) == 0){
	new_file = malloc(sizeof(File));
	new_file->type = malloc(sizeof(char)+1);
	new_file->name = malloc((strlen(name)+1)*sizeof(char));
	strcpy(new_file->name, name);
	strcpy(new_file->type, "D");
	new_file->child = NULL;
	new_file->parent = filesystem->current;
	curr = filesystem->current->child;
	if (curr == NULL){ /* If the directory is empty. */
	  filesystem->current->child = new_file;
	  new_file->next = NULL;
	}
	/* Storing the directories in an increasing lexicographic order. */
	else if (curr != NULL && strcmp(curr->name, new_file->name) > 0){
	  filesystem->current->child = new_file;
	  new_file->next = curr;
	}
	else{
	  while(curr != NULL && strcmp(curr->name, new_file->name) < 0){
	    head = curr;
	    curr = curr->next;
	  }
	  if (curr == NULL){
	    head->next = new_file;
	    new_file->next = NULL;
	  }
	  else{
	    head->next = new_file;
	    new_file->next = curr;
	  }
	}
	return 1;
      }
    
    } return 0;
  } return 0;
}

/* This functino is will change the current directory of the Ournix variable. */
int cd(Ournix *const filesystem, const char name[]){
  File *curr = NULL;
  if (name != NULL && filesystem != NULL && filesystem->current != NULL){ /* Check whether the parameter are null or not. */
    if (strcmp(name, "/") == 0){
      filesystem->current = filesystem->root;
      return 1;
    }
    if (strcmp(name,".") == 0 || name[0] == '\0')
      return 1;
    else if (strcmp(name, "..") == 0 ){
      if (filesystem->current->parent != NULL){
	filesystem->current = filesystem->current->parent;
	return 1;}
      else
	return 1;}
    else{
      if (filesystem->current->child != NULL){
	curr = filesystem->current->child;
	while(curr != NULL){
	  if (strcmp(curr->name, name) == 0 && strcmp(curr->type, "D") == 0){
	    filesystem->current = curr;
	    return 1;
	  }
	  curr = curr->next;
	}
      }  
    }
  }
  return 0;
}
/* This function will list the files and the directories of the current directory. */
int ls(Ournix *const filesystem, const char name[]){
  File *curr = NULL;
  if (name != NULL && filesystem != NULL && filesystem->current != NULL){
    if (strcmp(name, "/") == 0){
      curr = filesystem->root;
      ls_helper(curr);
      return 1;
    }
    else if (strcmp(name, "..") == 0){
      curr = filesystem->current->parent;
      ls_helper(curr);
      return 1;
    }
    else if (strcmp(name, ".") == 0 || strcmp(name, "") == 0){
      curr = filesystem->current;
      ls_helper(curr);
      return 1;
    }
    if (contains_file(filesystem->current, name) == 1){
      curr = filesystem->current->child;
      while (curr != NULL){
	if (strcmp(curr->name, name) == 0 && strcmp(curr->type, "F") == 0){
	  printf("%s %d\n", curr->name, curr->timestamp);
	  return 1;
	}
	else if (strcmp(curr->name, name) == 0 && strcmp(curr->type, "D") == 0){
	  ls_helper(curr);
	  return 1;
	}
	curr = curr->next;
      }
    }
    else
      return 0;
  }
  return 0;
} 
/* This function will print the the full path from the root to the directory. */
void pwd(Ournix *const filesystem){
  if (filesystem != NULL && filesystem->current != NULL){ 
    if (strcmp(filesystem->current->name, filesystem->root->name) == 0 )
      printf("/");
    else
      pwd_recursion(filesystem->current, filesystem->root, filesystem->current);
    printf("\n");
  }
}
/* This function will dynamicall allocate the entire Ournix variable. */
void rmfs(Ournix *const filesystem){
  if (filesystem != NULL && filesystem->current != NULL){
    remove_directory(filesystem->root->child);
    free(filesystem->root->name); /* Freeing the memory of the root directory */
    free(filesystem->root->type);
    free(filesystem->root);
  }
}
/* This function will remove a file or directory from the current directory. */
int rm(Ournix *const filesystem, const char name[]){
  File *curr = NULL , *prev = NULL;
  if (name != NULL && filesystem != NULL && filesystem->current != NULL){
    if (strcmp(name,".") != 0 && strcmp(name,"..") != 0 && strcmp(name,"/") != 0 && name[0] != '\0' && strchr(name,'/') == NULL){
      curr = filesystem->current->child;
      if(strcmp(curr->name,name) == 0 && strcmp(curr->type,"F") == 0){ /* If the first element of the directory is a file and is to be removed */
	filesystem->current->child = curr->next;
	free(curr->name);
	free(curr->type);
	free(curr);
	return 1;
      }
      else if(strcmp(curr->name,name) == 0 && strcmp(curr->type,"D") == 0){ /* If the first element of the directory is a directory and is to be removed */
	filesystem->current->child = curr->next;
	remove_directory(curr->child);
	free(curr->name);
	free(curr->type);
	free(curr);
	return 1;
      }
      else if(strcmp(curr->name,name) != 0){ /* If the first element of the directory does not match the target. */
	prev = curr;
	curr = prev->next;
	while(curr != NULL){
	  if (strcmp(curr->name,name) == 0 && strcmp(curr->type,"F") == 0){ /* If the element is a file. */
	    prev->next = curr->next;
	    free(curr->name);
	    free(curr->type);
	    free(curr);
	    return 1;
	  }
	  else if(strcmp(curr->name,name) == 0 && strcmp(curr->type,"D") == 0 ){ /* IF the elemnt is a directory. */
	    prev->next = curr->next;
	    remove_directory(curr->child);
	    free(curr->name);
	    free(curr->type);
	    free(curr);
	    return 1;
	  }
	  else{
	    prev = curr;
	    curr = prev->next;
	  }
	}
      }  
    }
  }
  return 0;
}

/* This is a helper function to check if the name is valid. */
int fwd_slash(const char name[]){
  if (strcmp(name,"/") == 0 || strchr(name,'/') == NULL)
    return 1;
  else
    return 0;
}
/* This is a helper function used to print the full path from the root to the directory passed in the function. */
void pwd_recursion(File *curr , File *root, File *last){
  if (strcmp(curr->name,root->name) == 0){
    printf("/");
    return;}
  else
    pwd_recursion(curr->parent, root, last);
  if(strcmp(curr->name,last->name) == 0)
    printf("%s", last->name);
  else
    printf("%s/", curr->name);
     
}
/* This is a helper function which is used to remove directories and its subdirectories. */
void remove_directory(File *curr){
  if (curr == NULL)
    return;
  else {
    if (curr->child != NULL)
      remove_directory(curr->child);
    if (curr->next != NULL)
      remove_directory(curr->next);
  }
  free(curr->name);
  free(curr->type);
  free(curr);
}
/* This is a helper function to print the file or the directory in the given format. */
void ls_helper(File *curr){
  curr = curr->child;
  while(curr != NULL){
    if (strcmp(curr->type, "F") == 0)
      printf("%s\n", curr->name);
    else
      printf("%s/\n",curr->name);
    curr = curr->next;
  }
}
/* This is a helper function that will check if the file given in the arguement is in the directory or not. */
int contains_file(File *head, const char name[]){
  File *current = head->child;
  while (current != NULL){
    if (strcmp(current->name,name) == 0)
      return 1;
    current = current->next;
  }
  return 0;
}
 

