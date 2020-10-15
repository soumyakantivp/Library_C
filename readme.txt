soumya and apurba are working on this project

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

//remove left trailing spaces from book name