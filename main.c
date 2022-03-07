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

/* Hamming distance */
int hammingDistance(char str1[], char str2[]){
    int i = 0, count = 0;
  
    while(str1[i]!='\0'){
        if (str1[i] != str2[i])
            count++;
        i++;
    }
    return count;
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

  /* initialize aaray with # and add null terminator to finish the string */
  for (int i = 0; i < argc-1; ++i){
    for(int j=0;j<(int)maximum_tag_length;++j){
      tags_table[i][j] = '_';
    }
    
    //insert string terminating character 
    tags_table[i][(int)maximum_tag_length] = '\0';
  }

  /* change # with the aactual string characters */
  for (int i = 0; i < argc-1; ++i){
    for (int j =0; j <(int)strlen(argv[i+1]);++j){
      tags_table[i][j] = argv[i+1][j];
    }
  }


  for (int i =0; i < argc-1; i++){
    for(int j=0;j<(int)maximum_tag_length;++j){
      printf("%c",tags_table[i][j]);
    }
    printf("\n");
    printf("[%d]: %s\n",i+1,tags_table[i]);
  }

  //initial dif array
  int differences[argc-1][argc-1];
  memset( differences, 0, sizeof(differences));

  for (int i =0; i < argc-1; i++){
    for(int j=i+1;j<argc-1;++j){
      differences[i][j] = hammingDistance(tags_table[i],tags_table[j]);
    }
  }

  /* Fidning minimum value */
  int minVal = 99999;
  int minRow = -1;
  int minCol = -1;

  for (int i =0; i < argc-1; i++){
    for(int j=i+1;j<argc-1;++j){
      if (differences[i][j] < minVal){
        minVal = differences[i][j];
        minRow = i;
        minCol = j;
      }
    }

    
  }
  
  
  
  struct node* s_3 = createParentNode(1);
  insertLeft(s_3,"tagssss");
  insertRight(s_3,"rrrrrr");
  struct node* s_4 = createParentNode(2);
  insertParentRight(s_4,s_3);
  printf("\n%d",s_4->right->id);
  return 0;
}