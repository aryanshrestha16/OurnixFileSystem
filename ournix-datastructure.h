typedef struct file{
  char *name; /* Name of the file or directory */
  char *type; /* Type i.e file or directory */
  int timestamp; /* Timestamp if the component is a file */
  struct file *parent; /* Parent directory */
  struct file *child; /* Sub directory */
  struct file *next; /* Next element */
} File;
typedef struct{
  File *current; /* Current directory */
  File *root; /* Root directory */
}Ournix;
