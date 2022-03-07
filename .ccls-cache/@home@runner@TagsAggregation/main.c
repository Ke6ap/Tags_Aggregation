#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tree struct */
struct node{
  // id is only for the parent nodes to map them in the 2d array 
  int id;
  // tags of the sensor (leaf)
  char *tags;
  struct node *left;
  struct node *right;
};

/* Create leaf node with its tags and irelevant id */
struct node* createLeafNode(char *tags) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->id = -1;
  newNode->tags = tags;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

/* Create parent node with no tags and its id which maps it to the superset array */
struct node* createParentNode(int id) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->id = id;
  newNode->tags = NULL;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

/* Tree insertion functions */

struct node* insertLeft(struct node* root, char *tags) {
  root->left = createLeafNode(tags);
  return root->left;
}

struct node* insertRight(struct node* root, char *tags) {
  root->right =  createLeafNode(tags);
  return root->right;
}

struct node* insertParentRight(struct node* root,struct node* subParent){
  root->right = subParent;
  return root->right;
}

struct node* insertParentLeft(struct node* root,struct node* subParent){
  root->left = subParent;
  return root->left;
}

/*fdsfsdfsd*/
void tags_alignment(int argc, int max, char tags[argc][max]){

  for(int i =0; i<argc; i++){
    int tag_length = strlen(tags[i]);
    if(tag_length < max){
      for (int j = (max - tag_length) + 1; j < max; ++j){
        tags[i][j] = '#';
        }
    }
  }

  return;
    // printf("%s iter: %d\n",tags_table[i-1],i);
}

int main(int argc, char **argv) {

  int maximum_tag_length = -1;
  /* Ta arguments einai oi etiketes */
  for (int i = 1; i < argc; ++i){
    /* Thelei typcast giati to strlen tou argv einai unsigned long int */
    if ((int)strlen(argv[i]) > maximum_tag_length){
      maximum_tag_length = strlen(argv[i]);
    }
  }

  /* filling the tags table and align them 
     maximum_tag_length + 1 because we will add '\0' to declare end of the string   
  */
  char tags_table[argc-1][(int)maximum_tag_length+1];
  
  for (int i = 0; i < argc-1; ++i){
    for(int j=0;j<(int)maximum_tag_length;++j){
      tags_table[i][j] = '_';
    }
    tags_table[i][(int)maximum_tag_length] = '\0';
  }
  
  for (int i = 0; i < argc-1; ++i){
    //strcpy(tags_table[i],argv[i+1]);
    for (int j =0; j <(int)strlen(argv[i+1]);++j){
      tags_table[i][j] = argv[i+1][j];
    }
  }

  /* Array print
  for (int i =0; i < argc-1; i++){
    for(int j=0;j<(int)maximum_tag_length;++j){
      printf("%c",tags_table[i][j]);
    }
    printf("\n");
    printf("[%d]: %s\n",i+1,tags_table[i]);
  }
  */
  
  
  
  struct node* s_3 = createParentNode(1);
  insertLeft(s_3,"tagssss");
  insertRight(s_3,"rrrrrr");
  struct node* s_4 = createParentNode(2);
  insertParentRight(s_4,s_3);
  printf("%d",s_4->right->id);
  return 0;
}