#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>szcacv

void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

struct newContact
{
    int id;
    char name[21];
    struct newConatact *next;
};

struct newContact *head=NULL;
struct newContact *tail=NULL;

struct phoneNumber
{
    int id;
    char number[12];
    struct phoneNumber *next;
};

struct phoneNumber *headPhone = NULL;
struct phoneNumber *tailPhone = NULL;

void appendNewContact(int id, char name[])
{
    _flushall();
    struct newContact *contactTemp;
    contactTemp = (struct newContact*)malloc(sizeof(struct newContact));
    contactTemp->id = id;
    strcpy(contactTemp->name,name);
    if(head == NULL)
    {
        head = tail = contactTemp;
        contactTemp->next = NULL;
    }
    else
    {
        contactTemp->next = NULL;
        tail ->next = contactTemp;
        tail = contactTemp;
    }
}

void appendPhoneNumber(int id, char number[])
{
    _flushall();
    struct phoneNumber* numberTemp;
    numberTemp = (struct phoneNumber*)malloc(sizeof(struct phoneNumber));
    numberTemp ->id = id;
    strcpy(numberTemp->number,number);

    if(headPhone == NULL)
    {
        headPhone = tailPhone = numberTemp;
        numberTemp->next = NULL;
    }
    else
    {
        numberTemp->next = NULL;
        tailPhone->next = numberTemp;
        tailPhone = numberTemp;
    }
}

void appendPhoneBook(int id)
{
    _flushall();
    // variable of name or phone
    char name[21];
    char number[12];
    int timesToadd;

    puts("please enter the name : ");
    gets(name);

    if(strlen(name) >10 && strlen(name) <= 20)
    {
        printf("how many phone number you want to add? ");
        scanf("%i", &timesToadd);
        for(int i = 0; i<timesToadd; i++)
        {
            printf("please enter the phone number : ");
            scanf("%s", &number);
            while(strlen(number ) != 11)
            {
                printf("Oops... The number must be 11 digits! \n");
                printf("please enter the phone number : ");
                scanf("%s", &number);
            }
            if(checkNumberExisting(number)==1)
            {
                printf("SOoory this phone is already Exist...");
                return;
            }
            else
            {
                if(i == 0)
                {
                    appendNewContact(id, name);
                    appendPhoneNumber(id, number);
                }
                else
                    appendPhoneNumber(id, number);
            }
        }
    }
    else
    {
        printf("Oops... The length must be between 10 and 20! \n");
        return appendPhoneBook(id);
    }
}

void displayPhoneNumber(int id)
{
    _flushall();
    struct phoneNumber *temp2 = headPhone;
    while(temp2!= NULL)
    {
        if(temp2->id == id)
        {
            printf("the number is : %s ", temp2->number);
            printf("\n");
        }
        temp2=temp2->next;

    }
}

int checkNumberExisting(char number[])
{
    _flushall();
    struct phoneNumber* temp = headPhone;
    while(temp!= NULL)
    {
        if(strcmp(temp->number, number)==0)
            return 1;

        temp = temp->next;
    }
    return 0;
}

int checkNameExisting(char name[])
{
    _flushall();
    struct newContact* temp = head;
    while(temp!= NULL)
    {
        if(strcmp(temp->name,name)==0)
            return 1;
        temp = temp->next;
    }
    return 0;
}

void displayPhoneBook()
{
    _flushall();
    int id;
    struct newContact *temp= head;
    while(temp!= NULL)
    {
        printf("the name is : %s ", temp->name);
        printf("\n");
        id = temp->id;
        displayPhoneNumber(id);
        printf("******************************************");
        printf("\n");
        temp=temp->next;
    }
}

void searchByName(char name[])
{
    _flushall();
    struct newContact * temp = head;
    while(temp !=NULL)
    {
        if(strcmp(temp->name,name)==0)
        {
            printf("The name is found : %s", temp->name);
            printf("\n");
            displayPhoneNumber(temp->id);
            return;
        }
        temp = temp->next;
    }

    printf("The name is not found");
}
void searchByPhone(char number[])
{
    _flushall();
    struct phoneNumber * temp = headPhone;
    struct newContact * tempName = head;
    //int id;
    while(temp !=NULL)
    {
        if(strcmp(temp->number,number)==0)
        {
            //id=temp->id;
            while(tempName != NULL)
            {
                if(tempName->id == temp->id)
                {
                    printf("The name is  : %s", tempName->name);
                    printf("\n");
                }
                tempName = tempName->next;
            }

            printf("The Phone is found : %s ", temp->number);
            printf("\n");
            return;
        }
        temp = temp->next;
    }

    printf("The name is not found");
}

void editName(char oldName[], char newName[])
{
    _flushall();
    struct newContact *temp = head;
    puts("please enter the old name ");
    gets(oldName);

    puts("please enter the new name ");
    gets(newName);
    while(temp != NULL)
    {
        if(strcmp(temp->name,oldName)==0)
        {
            strcpy(temp->name,newName);
            printf("The name is edited");
            return;
        }
        temp = temp->next;
    }
    printf("the name is not found ");
}
void editNumber(char oldNumber[], char newNumber [])
{
    _flushall();
    //char name1[21];
    struct phoneNumber *temp = headPhone;
    while(temp != NULL)
    {
        if(strcmp(temp->number,oldNumber)==0)
        {
            strcpy(temp->number,newNumber);
            printf("The number is Edited");
            return;
        }
        temp = temp->next;
    }
    printf("the number is not found ");
}

void deletePhone(char number[])
{
    _flushall();
    struct phoneNumber* temp;
    struct phoneNumber* prev;
    temp = headPhone;

    if(temp==NULL)
    {
        printf("The phone book is empty ");
        return;
    }
    else
    {
        while(temp!=NULL)
    {
        if(strcmp(temp->number,number)==0)
        {
            if(headPhone==tailPhone)
            {
                headPhone=tailPhone=NULL;
                printf("The number is deleted");
                free(temp);
                return;
            }
            else if (temp==headPhone)
            {
                headPhone=headPhone->next;
                printf("The number is deleted");
                free(temp);
                return;
            }
            else
            {
                if(temp==tailPhone)
                {
                    tailPhone=prev;
                    prev->next=NULL;
                    printf("The number is deleted");
                    free(temp);
                    return;
                }
                else
                {
                    prev->next=temp->next;
                    printf("The number is deleted");
                    free(temp);
                    return;

                }

            }
        }
        prev=temp;
        temp=temp->next;
    }
    printf("the number you want to delete is not exist");
    }
}

void deleteName(char name[])
{
    _flushall();
    struct newContact* temp;
    struct newContact* prev;
    temp = head;

    if(temp==NULL)
    {
        printf("The phone book is empty ");
        return;
    }
    else
    {
        while(temp!=NULL)
    {
        if(strcmp(temp->name,name)==0)
        {
            if(head==tail)
            {
                head=tail=NULL;
                printf("The name is deleted");
                free(temp);
                return;
            }
            else if (temp==head)
            {
                head=head->next;
                printf("The name is deleted");
                free(temp);
                return;
            }
            else
            {
                if(temp==tail)
                {
                    tail=prev;
                    prev->next=NULL;
                    printf("The name is deleted");
                    free(temp);
                    return;
                }
                else
                {
                    prev->next=temp->next;
                    printf("The name is deleted");
                    free(temp);
                    return;
                }

            }
        }
        prev=temp;
        temp=temp->next;
    }
    printf("the name you want to delete is not exist");
    }
}
/*int getId(char number[])
{
    int id;
    struct phoneNumber * temp = headPhone;
    while(temp!= NULL)
    {
        if(temp->number == number)
        {
            id= temp->id;
            return id;
        }
        temp = temp->next;
    }
}*/

/*struct phoneNumber* searchByID(int id)
{
    struct phoneNumber * temp = headPhone;
    while(temp!= NULL)
    {
        if(temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}*/

