#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tree struct */
struct node{
  // tags of the sensor (leaf)
  char *tags;
  struct node *left;
  struct node *right;
};

/* Create leaf node with its tags and irelevant id */
struct node* createNode(char *tags) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->tags = tags;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

// /* Create parent node with no tags and its id which maps it to the superset array */
// struct node* createParentNode(int id) {
//   struct node* newNode = malloc(sizeof(struct node));
//   newNode->id = id;
//   newNode->tags = NULL;
//   newNode->left = NULL;
//   newNode->right = NULL;

//   return newNode;
// }

/* Tree insertion functions */

struct node* insertLeft(struct node* root, char *tags) {
  root->left = createNode(tags);
  return root->left;
}

struct node* insertRight(struct node* root, char *tags) {
  root->right =  createNode(tags);
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

/* tags union */
char *findUnion(char str1[], char str2[]) {

    int f, p = 0;
    int i, j;

    //char *str3;
   char *str3 = (char*) malloc(12*sizeof(char));
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    while (str1[p] != '\0') {
        str3[p] = str1[p];
        p++;
    }

    int start = 0;

    for (i = 0; i < len2; i++) {
        f = 0;

        for (j = 0; j < len1; j++) {
             if (str2[i] == str1[j]) {
                f = 1;
            } 
        }
        if (f == 0) {
            str3[p] = str2[i];
            p++;
        }
    }
    str3[p] = '\0';
    //printf("Union of two strings:%s", str3);
    return str3;
}


/*string union*/
char *combination(char *str_1, char *str_2){
  char *final_str;
  final_str = (char*)malloc ((strlen(str_1)+strlen(str_2)+1) * sizeof (char));
  
  int i,j;
  for(i=0;i<strlen(str_1);i++){
    final_str[i] = str_1[i];
  }
  
  int index = i;
  int k=0;
  int prev=0;

  char word[2000];
  final_str[index] = ' ';
  index++;
  printf("%s\n",final_str);
  
  char *token = strtok(str_2," ");

  while(token != NULL){
    //printf( "%s\n", token );
    int b = strstr(final_str,token) == NULL;
    if (b){
        /*str foung oh my god*/
      for (i=0;i<strlen(token);i++){
        final_str[index] = token[i];
        index++;
      }
      final_str[index] = ' ';
      index++;
    }
    //printf( " %d\n", b );
    token = strtok(NULL, " ");
  }

  final_str[index] = '\0';
  //printf("\nfinal_str: %s",final_str);
  return final_str;
}

/* character triming */
char *trim(char *str,char ch){
  int len = strlen(str);
  int i,j;
  	   	
    for(i = 0; i < len; i++){
  		if(str[i] == ch)
  		{
  			for(j = i; j < len; j++)
  			{
  				str[j] = str[j + 1];
  			}
  			len--;
  			i--;	
  		} 
  	}	

  return str;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

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
  int table_size = argc-1;

  /* Tree root */
  struct node* root = createNode("");

  while(table_size != 1){
    
    for (int i =0; i < argc-1; i++){
      for(int j=i+1;j<argc-1;++j){
        if (differences[i][j] < minVal){
          minVal = differences[i][j];
          minRow = i;
          minCol = j;
        }
      }
    }

    char* first_tag_string = strdup(tags_table[minCol]);
    char* second_tag_string = strdup(tags_table[minRow]);

    char *aggregated_tags = trim(findUnion(first_tag_string,second_tag_string),'_');

    /*
      edw tha ftiaxw ta nodes me ta tags tous
    */

  //printf("----%s----\n",aggregated_tags);

    

    
    table_size--;
  }
  
  
  
  // struct node* s_3 = createParentNode(1);
  // insertLeft(s_3,"tagssss");
  // insertRight(s_3,"rrrrrr");
  // struct node* s_4 = createParentNode(2);
  // insertParentRight(s_4,s_3);
  // printf("\n%d",s_4->right->id);
  return 0;
}