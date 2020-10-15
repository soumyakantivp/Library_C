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

void initialize(BOOK** b);//initializes pointers with null
int countSize(FILE* fp);//returns number of lines in the file
void printBookList(BOOK* list);//prints book list in console
void updateBookFile(BOOK* list);//copies book list to books.txt
void createBook(BOOK** list);//adds new book from console to list--> uses addBook()
void addBook(BOOK** list,BOOK* newbook);//adds new book with given newbook data
void deleteBook(BOOK** list,int id);//deletes book with id
BOOK* readBooks();//returns pointer to head node of BOOK list generated by reading input file

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
void updateBookFile(BOOK* list){
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
        addBook(list,newbook);
        /*
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
        */
        updateBookFile(*list);
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

//delete with id
void deleteBook(BOOK** list,int id){
        if((*list) == NULL){
                printf("list empty!");
                return;
        }
        if((*list)->id == id){
                
                printf("deleted book: %s id: %d\n",(*list)->name,(*list)->id);
                BOOK* todelete = *list;
                *list = (*list)->next;
                free(todelete);
                todelete = NULL;
        }
        else{
                BOOK* temp = *list;
                int check=0;
                while(temp->next != NULL){
                        if(temp->next->id == id){
                                BOOK* todelete = temp->next; 
                                printf("deleted book: %s id: %d\n",todelete->name,id);
                                temp->next = todelete->next;
                                free(todelete);
                                todelete = NULL;
                                check++;
                                break;
                        }
                        temp = temp->next;
                }
                if(check == 0)
                printf("id: %d not found in BOOK list!\n",id);
        }
        updateBookFile(*list);
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
  deleteBook(&list,11);
  printBookList(list);
  return 0;
}