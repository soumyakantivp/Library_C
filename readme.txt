soumya and apurba are working on this project

typedef struct book{
        char name[100];
        int id; [id can not be 0]
        int status;//available or not?
        struct book* next;
}BOOK;

typedef struct student{
        char name[50];
        int roll;
        int status[MAX];//array of book ids issued[must end with 0]
        struct student* next;
}STUDENT;

//remove left trailing spaces from book name
//change student status from char to int!! ................done!
//createSTUDENT...done  & update Student File!