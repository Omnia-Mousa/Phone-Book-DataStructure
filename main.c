#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define up 'H'
#define down 'P'
#define Home 'G'
#define end 'O'
#define Name 'n'
#define phone 'p'
int index ;

void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

}

int main()
{
    int id=1;
    char name[21];
    char number[12];

    char Menu[9][20] = {"New Contact", "Display All Contact","Search By Name",
                        "Search By Phone","Edit Contact","Delete By Name","Delete By Phone","Exit"
                       }, ch;
    int i, current=0, ExetFlag=0 ;

    do
    {
        system("cls");
        for(i=0; i<9; i++)
        {
            gotoxy(50,9+3*i);
            if(i==current)
                textattr(0x70);
            _cprintf("%s", Menu[i]);
            textattr(0x07);
        }
        ch= getch();
        switch(ch)
        {
        case -32:
            ch=getch();
            switch(ch)
            {
            case up :
                current--;
                if(current<0)
                    current=7;
                break;

            case down:
                current++;
                if(current>7)
                    current=0;
                break;

            case Home:
                current=0;
                break;

            case end:
                current=7;
                break;
            }
            break;

        case 13:
            switch(current)
            {
            case 0: //NEW Contact
                system("cls");
                appendPhoneBook(id);
                id++;
                _flushall();
                getch();
                break;

            case 1:   // Display All
                system("cls");
                displayPhoneBook();
                getch();
                break;

            case 2: // Search By Name
                system("cls");
                printf("please enter the name \n");
                gets(name);
                //_flushall();
                searchByName(name);
                getch();
                break;

            case 3:  //Search By Phone
                system("cls");
                printf("please enter the Phone Number \n");
                gets(number);
                searchByPhone(number);
                getch();
                break;

            case 4:   //Edit Contact
                system("cls");
                printf("Please choose from the following options \n");
                printf("1- if you want to edit any name press n \n");
                printf("2- if you want to edit any number press p \n");
                scanf("%c", &ch);
                {
                    switch(ch)
                    {
                    case Name: // n
                        system("cls");
                        char oldName [21];
                        char newName [21];
                        editName(oldName,newName);
                        getch();
                        break;

                    case phone://P
                        system("cls");
                        char newnumber[12];
                        printf("please enter the old number \n");
                        scanf("%s",number);
                        printf("please enter the new number ");
                        scanf("%s",newnumber);
                        editNumber(number,newnumber);
                        getch();
                        break;
                    }
                }
                getch();
                break;

            case 5://Delete By Name
                system("cls");
                char deletedname[21];
                puts("please enter the name you want to delete");
                gets(deletedname);
                _flushall();
                deleteName(deletedname);
                getch();
                break;

            case 6: //Delete By Phone
                system("cls");
                char deletenum[12];
                printf("please enter the number you want to delete \n");
                scanf("%s", deletenum);
                deletePhone(deletenum);
                getch();
                break;

            case 7: //Exit
                ExetFlag = 1;
                break;
            }
            break;

        }

    }
    while(!ExetFlag);
    return 0;
}
