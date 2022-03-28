#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------Tree-------------------------------------- */
struct node{
  // tags of the sensor (leaf) and superset tags parent
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

/* Tree insertion functions */
struct node* insertLeft(struct node* root, char *tags) {
  root->left = createNode(tags);
  return root->left;
}

struct node* insertRight(struct node* root, char *tags) {
  root->right = createNode(tags);
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

int search(struct node* node, char *key){
    if (node == NULL)
        return 0;
 
    /* first recur on left child */
    search(node->left,key);
 
    /* then print the data of node */
    //printf("%s \n", node->tags);
    if (!strcmp(node->tags,key)){
      return 1;
    }
 
    /* now recur on right child */
    search(node->right,key);

    return 0;
}

int heightoftree(struct node *root)
{
    int max;
    if (root!=NULL)
    {
        /* Finding the height of left subtree. */
        int leftsubtree = heightoftree(root->left);
        /* Finding the height of right subtree. */
        int rightsubtree = heightoftree(root->right);
        if (leftsubtree > rightsubtree)
        {
            max = leftsubtree + 1;
            return max;
        }
        else
        {
            max = rightsubtree + 1;
            return max;
        }
    }
}
/*
 * Function to print all the nodes left to right of the current level
 */
void currentlevel(struct node *root, int level)
{
    if (root != NULL) 
    {
        if (level == 1)
        {
            printf("%s |", root->tags);
        }
        else if (level > 1) 
        { 
            currentlevel(root->left, level-1); 
            currentlevel(root->right, level-1);
        }			
    }
}


/*--------------------------------List------------------------------------------------------*/

struct list_node{
  int id;
  int has_children_in_tree;
  char *tags;
  struct list_node *next;
};

void insertAtBeginning(struct list_node** head_ref, int id, char *tags,int has_children) {
  // Allocate memory to a node
  struct list_node* new_node = (struct list_node*)malloc(sizeof(struct list_node));

  // insert the data
  new_node->id = id;
  new_node->has_children_in_tree = has_children;
  new_node->tags = strdup(tags);

  new_node->next = (*head_ref);

  // Move head to new node
  (*head_ref) = new_node;
}

void deleteNode(struct list_node** head_ref, int key) {
  struct list_node *temp = *head_ref, *prev;

  if (temp != NULL && temp->id == key) {
    *head_ref = temp->next;
    free(temp);
    return;
  }
  // Find the key to be deleted
  while (temp != NULL && temp->id != key) {
    prev = temp;
    temp = temp->next;
  }

  // If the key is not present
  if (temp == NULL) return;

  // Remove the node
  prev->next = temp->next;

  free(temp);
}

void insertAtEnd(struct list_node** head_ref, int id, char tags[],int has_children) {
  struct list_node* new_node = (struct list_node*)malloc(sizeof(struct list_node));
  struct list_node* last = *head_ref; /* used in step 5*/

  new_node->id = id;
  new_node->has_children_in_tree = has_children;
  new_node->tags = strdup(tags);
  
  new_node->next = NULL;

  if (*head_ref == NULL) {
  *head_ref = new_node;
  return;
  }

  while (last->next != NULL) last = last->next;

  last->next = new_node;
  return;
}

void printList(struct list_node* node) {
  while (node != NULL) {
    printf(" %d: %s\n", node->id,node->tags);
    node = node->next;
  }
}

/*------------------------------------------------------------------------------------------*/

/* Hamming distance */
int hammingDistance(char str1[], char str2[]){
    int i = 0, count = 0;
  
    while(str1[i]!='\0'){
        if (str1[i] != str2[i])
            count++;
        i++;
    }
    count += abs((int)strlen(str1)-(int)strlen(str2));
    return count;
}

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
  final_str[index] = '-';
  index++;
  //printf("%s\n",final_str);
  
  char *token = strtok(str_2,"-");

  while(token != NULL){
    //printf( "%s\n", token );
    int b = strstr(final_str,token) == NULL;
    if (b){
        /*str foung oh my god*/
      for (i=0;i<strlen(token);i++){
        final_str[index] = token[i];
        index++;
      }
      final_str[index] = '-';
      index++;
    }
    //printf( " %d\n", b );
    token = strtok(NULL, "-");
  }

  if(final_str[index-1] == '-'){
    final_str[index-1] = '\0';
    return final_str;
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

void printInorder(struct node* node)
{
    if (node == NULL)
        return;
 
    /* first recur on left child */
    printInorder(node->left);
 
    /* then print the data of node */
    printf("%s | ", node->tags);
 
    /* now recur on right child */
    printInorder(node->right);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

int main(int argc, char **argv) {
  
  struct list_node* head = NULL;
  struct node* tree_head = NULL;

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
    if ( i==0 ){
      insertAtBeginning(&head,i,tags_table[i],0); 
    }else{
      insertAtEnd(&head,i,tags_table[i],0);
    }
  }

  //printList(head);


  // for (int i =0; i < argc-1; i++){
  //   for(int j=0;j<(int)maximum_tag_length;++j){
  //     printf("%c",tags_table[i][j]);
  //   }
  //   printf("\n");
  //   printf("[%d]: %s\n",i+1,tags_table[i]);
  // }

  //initial dif array
  float differences[argc-1][argc-1];
  memset( differences, 0, sizeof(differences));

  for (int i =0; i < argc-1; i++){
    for(int j=i+1;j<argc-1;++j){
      differences[i][j] = hammingDistance(tags_table[i],tags_table[j]);
    }
  }

  /* Fidning minimum value */
  int table_size = argc-1;

  /* Tree root */
  char* first_tag_string;
  char* second_tag_string;
  struct list_node* temp = NULL;

  
  while(table_size != 1){

    temp = head;
    float minVal = 99999;
    int minRow = -1;
    int minCol = -1;

    //find min -> nearest couple
    for (int i =0; i < table_size; i++){
      for(int j=i+1;j<table_size;++j){
        if (differences[i][j] < minVal){
          minVal = differences[i][j];
          minRow = i;
          minCol = j;
        }
      }
    }

    //printf("minclo/row val:%d %d %.f\n",minCol,minRow,minVal);

    /* values to see if a string will have children */
    int first_has_children;
    int second_has_children;

    //copy nearest couple tags
    while(temp != NULL){
      if(temp->id == minRow){
        first_tag_string = strdup(temp->tags);
        first_has_children = temp->has_children_in_tree;
      }
      if(temp->id == minCol){
        second_tag_string = strdup(temp->tags);
        second_has_children = temp->has_children_in_tree;
      }
      temp = temp->next;
    }

                      /* helper prints */
    // printf("i am the first string %s\n",first_tag_string);
    // printf("i am the second string %s\n",second_tag_string);
    char *temp_second_tag_string = strdup(second_tag_string);
    temp_second_tag_string = trim(temp_second_tag_string,'_');

    //combination of the couple tags
    char *aggregated_tags = combination(trim(first_tag_string,'_'),trim(second_tag_string,'_'));
    // printf("i am the second string after comb %s\n",temp_second_string);
    // printf("i am the first string afeter comb %s\n",first_tag_string);

    //na dw ta trees
    struct node* parent_of_childs = createNode(aggregated_tags);

    if(tree_head == NULL){
        insertRight(parent_of_childs,first_tag_string);
        //printf("%s |",parent_of_childs->right->tags);
        insertLeft(parent_of_childs,temp_second_tag_string);
        //printf("%s \n",parent_of_childs->left->tags);
        //printf("i am the second string %s\n",second_tag_string);
        tree_head = parent_of_childs;
    }else if(search(tree_head,first_tag_string)){
      //an to head->id einai == mincol h minrow shmainei oti to ena paidi tou dentrou tha einai to ypodentro alliws tha einai ena kainouyrgio zeugari
      // if(first_has_children && second_has_children){
      //   insertParentLeft(parent_of_childs,)
      //   // insertParentRight(parent_of_childs,tree_head);
      //   // insertLeft(parent_of_childs,second_tag_string);
      //   // tree_head = parent_of_childs; 
      // }else{
        
      // }
      //struct node* parent_of_childs = createNode(aggregated_tags);

      /* An einai to first string anagkastika den einai to deytero opote to dhmiourgoume kai to bazoume aristera enw vazoume to upoloipo dentro dexia */
      insertLeft(parent_of_childs,temp_second_tag_string);
      //printf("%s | ",parent_of_childs->left->tags);
      insertParentRight(parent_of_childs,tree_head);
      //printf("%s \n",parent_of_childs->right->tags);
      tree_head = parent_of_childs;

    }else if(search(tree_head,temp_second_tag_string)){
      
      insertLeft(parent_of_childs,first_tag_string);
      //printf("%s | ",parent_of_childs->left->tags);
      insertParentRight(parent_of_childs,tree_head);
      //printf("%s \n",parent_of_childs->right->tags);
      tree_head = parent_of_childs;
    }else{
      //printf("\n\n Special case \n\n");
      insertLeft(parent_of_childs,temp_second_tag_string);
      //printf("%s |",parent_of_childs->left->tags);
      insertRight(parent_of_childs,first_tag_string);
      //printf("%s \n\n",parent_of_childs->right->tags);
      
      
      struct node* super_parent_of_childs;
      //ftiaxnw to copy epeidh xalaei me to combination kai thelei epanaxrikopoihsh
      char *temp_head_tag_string = strdup(tree_head->tags);
      temp_head_tag_string = trim(temp_head_tag_string,'_');
      
      char *super_aggregated_tags = combination(trim(parent_of_childs->tags,'_'),trim(tree_head->tags,'_'));

      tree_head->tags = temp_head_tag_string;
      super_parent_of_childs = createNode(super_aggregated_tags);
      //printf("\nsuper %s\n",super_parent_of_childs->tags);

      insertParentLeft(super_parent_of_childs,parent_of_childs);
      //printf("%s |",super_parent_of_childs->left->tags);
      insertParentRight(super_parent_of_childs,tree_head);
      //printf("%s \n",super_parent_of_childs->right->tags);
      tree_head = super_parent_of_childs;
    }

    deleteNode(&head, minCol);
    deleteNode(&head, minRow);
    insertAtBeginning(&head,4,aggregated_tags,1);
    //printf("\n agg: %s\n",head->tags);

    temp = head;
    int index = 0;

    //reset ids
    while(temp != NULL){
      temp->id = index;
      index++;
      temp = temp->next;
    }

                      /* helper print */
    // printf("\n list\n");
    // printList(head);
    // printf("\n");

    //re-initialize to zero for the next iteration
    memset( differences, 0, sizeof(differences));

    //loop through the list elements to find new diff array
    temp = head;
    struct list_node* temp_2 = head;
    int i,j;
    i = 0;
    j = 0;


    //printf("\nUpdating distance table iteration %d:\n",table_size);
    while(temp != NULL){
      //printf("\nid:%d tags:%s:\n",temp->id,temp->tags);
      temp_2= temp->next;
      j = i+1;
      while(temp_2 != NULL){
        //printf("\ncompared to -->id:%d tags:%s:\n",temp_2->id,temp_2->tags);
        differences[i][j] = hammingDistance(temp->tags,temp_2->tags);
        //printf("%s   %s\n",temp->tags,temp_2->tags);

        temp_2 = temp_2->next;
        j++;
      }
      
      i++;
      temp = temp->next;
    }


    /* Print distance table */
    // for (i=0;i<table_size-1;i++){
    //   for(j=i;j<table_size-1;j++){
    //     printf("%.2f ",differences[i][j]);
    //   }
    //   printf("\n");
    // }
    
    table_size--;
  }
  //printInorder(tree_head);

  int height = heightoftree(tree_head);
  for(int i = 1; i <= height; i++)      
    {
        printf("%d->",i);
        currentlevel(tree_head,i);
        printf("\n");
    }

  return 0;
}

/* to problima einai oti meta to combinatino xanetai h plhroforia tou second_tag_string opote eipa na kanw ena copy to string kai afou ginei to affrefation na asxoloume me to copy toy 
Den douleuei akoma enw den exw dei th periptwsh toy superparent h opoia den emfanizetai mallon logo twn paradeigmatwn axizei na ereunithei omws

me to level order traversal douleuei isws na einai lathos ta epoxiaka prints poy exw stis periptwseis
akoma 
*/

/* To problima me th mpourda poy kobei ta tags yparxei sto super kai prepei na kanw 2 copy gia ta aggregations gia na to ftiaxw

sto ./a.out TEMP-HUM TEMP-HUM-CO2 RAIN-WEATHER RAIN-WEATHER-SUN SOMETHING-ELSE-IRRELEVANT-YES

*/