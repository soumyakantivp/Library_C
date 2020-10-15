#include <stdio.h>
#include <stdlib.h>
#define MAX 10 // total number of books each student can issue

typedef struct book{
        char name[100];
        int id;
        int status;//available or not?
        struct book* next;
}BOOK;

typedef struct student{
        char name[50];
        int roll;
        int status[MAX];//array of book ids issued
        struct student* next;
}STUDENT;
 void initialize(BOOK** b){
         *b = NULL;
 }
int countSize(FILE* fp){
        int count = 0;
        while(!feof(fp)){
                if(fgetc(fp) == '\n')
                count++;
        }
        printf("count: %d\n",count); // test
        return count;
}
void printBookList(BOOK* list){
        printf("BOOK LIST:\n");
        while(list->next != NULL){
                printf("%-3d %-50s %d\n",list->id,list->name,list->status);

                list = list->next;
        }
        printf("%-3d %-50s %d\n",list->id,list->name,list->status);
}
void updateBookList(BOOK* list){
        FILE* fp;
        if((fp = fopen("books.txt","w"))){
        while(list->next != NULL){
                fprintf(fp,"%-3d %-50s %d\n",list->id,list->name,list->status);

                list = list->next;
        }
        fprintf(fp,"%-3d %-50s %d\n",list->id,list->name,list->status);
        }
        else{
                printf("cant open file!");
                return;
        }
}
void createBook(BOOK** list){
        BOOK* temp = *list;
        BOOK* newbook = (BOOK*)malloc(sizeof(BOOK));
        printf("enter book name: ");
        scanf("%[^\n]s",newbook->name);
        printf("\nenter id: ");
        scanf("%d",&newbook->id);
        //validate book id
        while(temp != NULL){
                if(temp->id == newbook->id){
                        printf("id already taken by: %s\n",temp->name);
                        return;
                }
                temp = temp->next;
        }
        
        newbook->status = 1;//available
        newbook->next = NULL;
        if(*list == NULL){
                *list = newbook;
        }
        else{
                temp = *list;
                while(temp->next!=NULL){
                        temp = temp->next;
                }
                temp->next = newbook;
        }
        updateBookList(*list);
}
void addBook(BOOK** list,BOOK* newbook){
        if(*list == NULL){
                *list = newbook;
        }
        else{
                BOOK* temp = *list;
                while(temp->next!=NULL){
                        temp = temp->next;
                }
                temp->next = newbook;
        }
        
}
BOOK* readBooks(){
        FILE* fp;
        if((fp = fopen("books.txt","r"))){
        int i=0,size = countSize(fp);
        BOOK* blist;
        initialize(&blist);
        fseek(fp,0,SEEK_SET);
        while(!feof(fp)){ 
                BOOK* book = (BOOK*)malloc(sizeof(BOOK));
                fscanf(fp,"%d",&book->id);
                if(book->id == 0)
                        break;
                        
                 while(fgetc(fp) == ' ');
                fseek(fp,-1,SEEK_CUR); 

                fscanf(fp,"%22[^\n]s",book->name);
                fscanf(fp,"%d",&book->status);
                book->next = NULL;
                addBook(&blist,book);
                i++;
        }
        return blist;
        fclose(fp);
        }
        else{
                printf("cant open file!");
                return NULL;
        }
}
int main(void) {
  BOOK* list;
  list = readBooks();
  printBookList(list);
  createBook(&list);
  printBookList(list);
  return 0;
}