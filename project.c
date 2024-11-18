#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct books{
 int id;
 char bookName[50];
 char authorName[50];
 char date[12];
}b;
struct student{
    int id;
    char sName[50];
    char sClass[50];
    char sRoll[50];
    char bookName[50];
    char date[12];
}s;
FILE *fp;


int main(){
    int ch;


    //main menu
    while(1){

        system("cls");
        system("COLOR 17");
    printf("<====library management system====>\n");
    printf("1.add book\n");
    printf("2.book list\n");
    printf("3.remove book\n");
    printf("4.issue book\n");
    printf("5.issued book list\n");
    printf("0.exit\n\n");
    printf("enter your choice: ");
    scanf("%d",&ch);                        

    switch (ch)
    {
    case 0:
         exit(0);
        break;

    case 1:
     addbook();
     break;

    case 2:
    booklist();
    break;

    case 3:
    del();
    break;

    case 4:
    issue();
    break;

   case 5:
    issued();
    break;

    default:
      printf("invalid choice\n\n");
        break;
    }
    printf("press any key to continue.......");
    getch();
    }
    return 0;
}

// funtion to addbook 
void addbook(){

    //pick system date to the funtion
    char mydate[12];

    time_t t=time(NULL);
    struct tm tm= *localtime(&t);
    sprintf(mydate,"%02d%02d%d",tm.tm_mday, tm.tm_mon+1, tm.tm_year+ 1900);
    strcpy(b.date,mydate);

    fp=fopen("book.txt","ab");

    printf("enter book id: ");
    scanf("%d",&b.id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);

     printf("Enter author name:  ");
     
    fflush(stdin);
    gets(b.authorName);

     printf("added book succesfully\n\n");





    fwrite(&b,sizeof(b),1,fp);
    
    fclose(fp);




}

//funtion to display book list
void booklist(){
    system("cls");
    printf("<==Available books==>\n\n");
    printf("%-10s %-30s %-20s %s","Id","bookname","Author","Date\n\n");

    fp=fopen("book.txt","rb");

    while(fread(&b,sizeof(b),1,fp)==1){
        printf("%-10d %-30s %-20s %s\n",b.id,b.bookName,b.authorName,b.date);
    }
    fclose(fp);
}
// funtion to delete book from booklist 
void del(){
    system("cls");
    int id,f=0;
    printf("<==Remove books\n\n");
    printf("Enter book id to remove: ");
    scanf("%d",&id);

    FILE *ft;

    fp=fopen("book.txt","rb");
    ft=fopen("temp.txt","wb");

    while(fread(&b,sizeof(b),1,fp)==1){
        if(id==b.id){
            f=1;
        }else{fwrite(&b,sizeof(b),1,ft);}
    }
    if(f==1){
        printf("book deleted succesfully\n\n");
    }else("invalid record");


    fclose(fp);
    fclose(ft);

    remove("book.txt");
    rename("temp.txt","book.txt");
    
}
//funtion to issue book 
void issue(){

 //pick system date to function   
    char mydate[12];
    time_t t=time(NULL);
    struct tm tm= *localtime(&t);
    sprintf(mydate,"%02d""%02d""%d",tm.tm_mday, tm.tm_mon+1, tm.tm_year+ 1900);
    strcpy(s.date,mydate);
   


    int f=0;
    system("cls");
    printf("<==Issue books==>\n\n");
    printf("enter book id to issue:  ");
    scanf("%d",&s.id);

    fp=fopen("book.txt","rb");

    while(fread(&b,sizeof(b),1,fp)==1){
        if(b.id==s.id){
            
            strcpy(s.bookName,b.bookName);
            f=1;
            break;
        }
    }
    if(f==0){
        printf("No book found with this id\n");
        printf("please try again later\n\n");
        return;

    }

    fp=fopen("issue.txt","ab");

    printf("Enter student name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter student class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter student roll: ");
    fflush(stdin);
    gets(s.sRoll);

    printf("issued book succesfully\n");

    fwrite(&s,sizeof(s),1,fp);
    fclose(fp);





}

//funtion to display issued book
void issued(){
    system("cls");
    printf("<==Issue book list==>\n\n");
    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n","S.Id","Student name","class","roll no","Book name","Date");

     fp=fopen("issue.txt","rb");

    while(fread(&s,sizeof(s),1,fp)==1){
      printf("%-10d %-30s %-20s %-10s %-30s %d\n\n",s.id,s.sName,s.sClass,s.sRoll,s.bookName,s.date);

    }
    fclose(fp);
}