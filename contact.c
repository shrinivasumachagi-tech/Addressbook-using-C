#include <stdio.h>
#include<string.h>
#include "contact.h"
#include<ctype.h>
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"
#define BOLD_RED    "\033[1;31m"
#define BOLD_GREEN  "\033[1;32m"
#define BOLD_BLUE   "\033[1;34m"
#define BOLD_PURPLE "\033[1;35m"
#define BOLD_CYAN   "\033[1;36m"
#define BOLD    "\033[1m"

/* Function definitions */
// void init_intitalization(AddressBook *addressbook)
// {
// }

int valid_name(char* );
int valid_name(char* name)//validation of name
{
    //1 rule only alphabets
    for(int i=0;name[i]!='\0';i++)
    {
        if(!(islower(name[i])||isupper(name[i])||isspace(name[i])))
        {
            printf(BOLD_RED"Name should contains only alphabet characters! Try again.\n\n"RESET);
            return 0;
        }
    }
    return 1;
}

int valid_phone_number(char* ,AddressBook* );
int valid_phone_number(char* phone_number,AddressBook* addressbook)//validation of phone_number
{   //1 rule frst letter should be >=6 & <=9
    int len=strlen(phone_number);
    if(!(phone_number[0]>='6' && phone_number[0]<='9'))
    {
        printf(BOLD_RED"phone number should be starts with >=6 and <=9.\n\n"RESET);
        return 0;
    }
    //2 rule only numbers
    for(int i=0;i<len;i++)
    {
        if(!(isdigit(phone_number[i])))
        {
            printf(BOLD_RED"Phone number should contains only numbers! Try again\n\n"RESET);
            return 0;
        }
    }
    //3 rule 10 digits
    if(len!=10)
    {
        printf(BOLD_RED"phone number should contains 10 digits.\n\n"RESET);
        return 0;
    }
    //4 rule unique
    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(strcmp(phone_number,addressbook->contact_details[i].Mobile_number)==0)
        {
            printf(BOLD_RED"Phone number should be unique! Try again\n\n"RESET);
            return 0;
        }
    }
    return 1;
}

int valid_email_id(char* ,AddressBook* );
int valid_email_id(char* email_id,AddressBook* addressbook)//validation of email_id
{
    //rule 1 unique email_Id
    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(strcmp(email_id,addressbook->contact_details[i].Mail_ID)==0)
        {
            printf(BOLD_RED"Email_ID should be unique! Try again.\n\n"RESET);
            return 0;
        }
    }
    //rule 2, only 1 @ 
    int len=strlen(email_id);
    int count=0;
    for(int i=0;i<len;i++)
    {
        if(email_id[i]=='@')
        {
            count++;
        }
    }
    if(count!=1)
    {
        printf(BOLD_RED"Mail_id should contain only one @ symbol! Try again.\n\n"RESET);
        return 0;
    }
    //rule 3 only lower case
    for(int i=0;i<len;i++)
    {
        if((email_id[i]>='A' && email_id[i]<='Z'))
        {
            printf(BOLD_RED"In mail_id Only lower case is consider.\n\n"RESET);
            return 0;
        }
    }
    //rule 4 .com should be there
    char substr[6]=".com";
    char* substring=strstr(email_id,substr);
    if(substring == NULL)
    {
        printf(BOLD_RED"Mail_id should conatins @ and .com\n\n"RESET);
        return 0;
    }
    //rule 5 before @ minimum 2 characters should be there
    for(int i=0;i<2;i++)
    {
        if(email_id[i]=='@')
        {
            printf(BOLD_RED"mail_id atleast contains 4 characters before the @ symbol! Try again\n\n"RESET);
            return 0;
        }
    }
    //rule 6 domain name should be after @ symbol
    int k;char ch='@';
    char* str=strstr(email_id,substr);
    char* ptr=strchr(email_id,ch);
    if(str-ptr<2)//str=.com && ptr=@ then .com-@ distance
    {
        printf(BOLD_RED"Domain name should be after the @ symbol! Try again\n\n"RESET);
        return 0;
    }
    //rule 7 no space
    for(int i=0;i<len;i++)
    {
        if(email_id[i]==' ')
        {
            printf(BOLD_RED"In email_id there is no spaces! Try again\n\n"RESET);
            return 0;
        }
    }
    
    //rule 8 only one . should be there after @
    int i,count1=0,alpha_count=0;
    int j=0;
    //rule 9 one alphabet before @ 
    while(email_id[j]!='@')
    {
        if(email_id[j]>='a'&&email_id[j]<='z')
        {
            alpha_count++;
        }
        j++;
    }
    if(alpha_count<1)
    {
        printf(BOLD_RED"Atleast one alphabet should be present before '@'\n\n"RESET);
        return 0;
    }
    //rule 10 before and after @ next index will not be '.' 
    for(i=0;email_id[i]!='\0';i++)
    {
        if(email_id[i]=='@')
        {
            break;
        }
    }
    if(email_id[i-1]=='.'||email_id[i+1]=='.')
    {
        printf(BOLD_RED"Position of the '.' not valid\n\n"RESET);
        return 0;
    }
    for(int j=i;email_id[j]!='\0';j++)
    {
        if(email_id[j]=='.')
        count1++;
    }
    if(count1>1)
    {
        printf(BOLD_RED"after @ only one '.' should be there\n\n"RESET);
        return 0;
    }
    
    //rule 11 last . not there
    if(email_id[len-1]=='.')
    {
        printf(BOLD_RED"In email_id last . should not there!\n\n"RESET);
        return 0;
    }
    return 1;
}
//creating an contact details in structure
int create_contact(AddressBook *addressbook)
{
    int k=1;
    while(k)
    {
        char name[30];
        printf("Enter the Name: ");
        n_m:
        scanf(" %[^\n]",name);
        int valid_n=valid_name(name);
        
        if(valid_n!=0)
        {
            //copyig string to a structure
            strcpy(addressbook->contact_details[addressbook->contact_count].Name,name);
        }
        else{
            printf("Enter name again:");
            goto n_m;
        }

        char phone_number[11];
        printf("Enter phone number: ");
        p_n:
        scanf(" %[^\n]",phone_number);
        int valid_p=valid_phone_number(phone_number,addressbook);

        if(valid_p!=0)
        {
             //copyig string to a structure
            strcpy(addressbook->contact_details[addressbook->contact_count].Mobile_number,phone_number);
        }
        else
        {
            printf("Enter phone number again: ");
            goto p_n;
        }

        char email_id[20];
        printf("Enter email_id: ");
        e_i:
        scanf(" %[^\n]",email_id);
        int valid_e=valid_email_id(email_id,addressbook);

        if(valid_e!=0)
        {
             //copyig string to a structure
            strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID,email_id);
        }
        else
        {
            printf("Enter Email Id again: ");
            goto e_i;
        }
        addressbook->contact_count++;

        printf("Do you want to create contact?\n1.yes\n0.No\n");
        scanf("%d",&k);
    }
    return 0;
}
//list the contact details
void list_contacts(AddressBook *addressbook)
{
    if(addressbook->contact_count==0)
    {
        printf(RED"There are no contact details in the file\n"RESET);
        return;
    }
    printf("Name              Phone_number     email_id\n");
    for(int i=0;i<addressbook->contact_count;i++)
    {   
        printf("-------------------------------------------------------------------------------------------\n");
        printf(BOLD_BLUE "%-16s  %-10s       %s\n" RESET,addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
        //printf("-------------------------------------------------------------------------------------------\n");
    }
    printf("\n");
}
//search the contact details
int search_contacts(AddressBook *addressbook)
{
    if(addressbook->contact_count==0)
    {
        printf(RED"There are no contact details in the file.\n"RESET);
        return -1;
    }
    printf(BLUE"Search Menu\n"RESET"1.search by name\n2.search by mobile numbre\n3.search by email_id\n4.exit\n");
    int option,option1;
    scanf("%d",&option);
    char name[20];
    char Mobile_number[11];
    char email_id[20];
    int count;
    int arr[count];
    int i,j;
    switch(option)
    {
        case 1://search by name
        count=0;
        printf("Enter the name: ");
        scanf(" %[^\n]",name);
        for(i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(addressbook->contact_details[i].Name,name)==0)
            {
                printf(BOLD"%s-%s-%s\n"RESET,addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                arr[count]=i;//storing the index number to array
                count++;
            }
        }
        if(count>1)//if searching name is repeating, search by phone number or email_id in that name
        {
            printf("There are %d contacts with the same name\nSearch the contact details by phone number and email_id\n1.phone number\n2.email_id\n",count);
            scanf("%d",&option1);
            if(option1==1)
            {
                printf("Enter the Mobile number: ");
                scanf(" %[^\n]",Mobile_number);
                for(j=0;j<count;j++)
                {
                    if(strcmp(addressbook->contact_details[arr[j]].Mobile_number,Mobile_number)==0)
                    {  
                        printf("-------------------------------------------------------------------------------------------\n");
                        printf(BOLD"%s-%s-%s\n"RESET,addressbook->contact_details[arr[j]].Name,addressbook->contact_details[arr[j]].Mobile_number,addressbook->contact_details[arr[j]].Mail_ID);
                        printf("-------------------------------------------------------------------------------------------\n");
                        return arr[j];
                    }
                }
                printf("-------------------------------------------------------------------------------------------\n"); 
            }
            if(option1==2)
            {
                 printf("Enter the Email_id: ");
                scanf(" %[^\n]",email_id);
                for(j=0;j<count;j++)
                {
                    if(strcmp(addressbook->contact_details[arr[j]].Mail_ID,email_id)==0)
                    {
                        printf("-------------------------------------------------------------------------------------------\n");
                        printf(BOLD"%s-%s-%s\n"RESET,addressbook->contact_details[arr[j]].Name,addressbook->contact_details[arr[j]].Mobile_number,addressbook->contact_details[arr[j]].Mail_ID);
                        printf("-------------------------------------------------------------------------------------------\n");
                        return arr[j];
                    }
                }
            }
        }
        else if(count==1)
        {
            printf(GREEN"Contact found\n"RESET);
            return arr[0];
        }
        break;

        case 2://search by phone number
        printf("Enter the Mobile number: ");
        scanf(" %[^\n]",Mobile_number);
        for(i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(addressbook->contact_details[i].Mobile_number,Mobile_number)==0)
            {
                printf("-------------------------------------------------------------------------------------------\n");
                printf(BOLD"%s-%s-%s\n"RESET,addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                printf(GREEN"Contact found\n"RESET);
                printf("-------------------------------------------------------------------------------------------\n");
                return i;
                break;
            }
        } 
        break;
        
        case 3://search by email_id
        printf("Enter the email_ID: ");
        scanf(" %[^\n]",email_id);
        for(i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(addressbook->contact_details[i].Mail_ID,email_id)==0)
            {
                printf("-------------------------------------------------------------------------------------------\n");
                printf(BOLD"%s-%s-%s\n"RESET,addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                printf(GREEN"Contact found\n"RESET);
                printf("-------------------------------------------------------------------------------------------\n");
                return i;
                break;
            }
        }
        break;

        case 4:
        printf("Thank you\n");
        break;
    }
    if(option!=4)
    {
    printf(RED"Contact is not found\n"RESET);
    }
}
//editting the details 
int edit_contact(AddressBook *addressbook)
{//for editting frst search that details by name or phone number or email_id if it is present then return the index number
    int search_contacts(AddressBook *);
    int i=search_contacts(addressbook);
    int option;
    char e_name[20];
    char e_phone[11];
    char e_email_id[30];
    if(i>=0 && i<=addressbook->contact_count)
    {
        printf(BLUE"Edit Contact menu : \n"RESET"1.edit the Name \n2.edit the Mobile number\n3.edit the Mail ID\n4.edit all the informations\nEnter the option : ");
        scanf("%d",&option);
        switch(option)
        {
            case 1://edit the name
                e_n:
                printf("Enter the editting name: ");
                scanf(" %[^\n]",e_name);
                int valid_f_e_n=valid_name(e_name);
                if(valid_f_e_n!=0)
                {
                    strcpy(addressbook->contact_details[i].Name,e_name);
                    printf(GREEN"Edit completed.\n\n"RESET);
                }
                else
                {
                    goto e_n;
                }
            break;

            case 2://edit the mobile number
                e_p:
                printf("Enter the editting mobile number: ");
                scanf(" %[^\n]",e_phone);
                int valid_f_e_p=valid_phone_number(e_phone,addressbook);
                if(valid_f_e_p!=0)
                {
                    strcpy(addressbook->contact_details[i].Mobile_number,e_phone);
                    printf(GREEN"Edit completed.\n\n"RESET);
                }
                else
                {
                    goto e_p;
                }
            break;

            case 3://edit the email_id
                f_e_id:
                printf("Enter the editting Email_ID: ");
                scanf(" %[^\n]",e_email_id);
                int valid_f_e_e=valid_email_id(e_email_id,addressbook);
                if(valid_f_e_e!=0)
                {
                    strcpy(addressbook->contact_details[i].Mail_ID,e_email_id);
                    printf(GREEN"Edit completed.\n"RESET);
                }
                else
                {
                    goto f_e_id;
                }
            break;

            case 4://edit all informations
            e_f_n:
            printf("Enter the editting name: ");
            scanf(" %[^\n]",e_name);
            int valid_e_n=valid_name(e_name);
            if(valid_e_n!=0)
            {
                strcpy(addressbook->contact_details[i].Name,e_name);
                //printf(GREEN"Editting name completed.\n\n"RESET);
            }
            else
            {
                goto e_f_n;
            }
            e_f_p:
            printf("Enter the editting phone_number: ");
            scanf(" %[^\n]",e_phone);
            int valid_e_p=valid_phone_number(e_phone,addressbook);
            if(valid_e_p!=0)
            {
                strcpy(addressbook->contact_details[i].Mobile_number,e_phone);
                //printf(GREEN"Editting phone number completed.\n\n"RESET);
            }
            else
            {
                goto e_f_p;
            }
            e_f_e_id:
            printf("Enter the editting email_id: ");
            scanf(" %[^\n]",e_email_id);
            e_e_id:
            int valid_e_e=valid_email_id(e_email_id,addressbook);
            if(valid_e_e!=0)
            {
                strcpy(addressbook->contact_details[i].Mail_ID,e_email_id);
                //printf(GREEN"Editting email_id completed.\n"RESET);
            }
            else
            {
                goto e_f_e_id;
            }
            printf(GREEN"Editting successful\n\n"RESET);
            break;
        }
    }
}

//deleting the contact details
int delete_contact(AddressBook *addressbook)
{
    //for deleting frst search that details by name or phone number or email_id if it is present then return the index number
    int search_contacts(AddressBook *);
    int i=search_contacts(addressbook);
    int option;
    if(i>=0 && i<=addressbook->contact_count)
    {
        printf("Do you really want to delete the details?\n1.yes\n2.No\n");
        scanf("%d",&option);
        if(option==1)
        {
            addressbook->contact_count--;
            for(int j=i;j<addressbook->contact_count;j++)
            {
                addressbook->contact_details[j]=addressbook->contact_details[j+1];
            }
            printf(GREEN"Delete completed\n"RESET);
        }
        return 0;
    }
}
//saving the contact details from structure to file
int save_contacts(AddressBook *addressbook)
{
    //arranging in alphabetical order wise
    FILE* fptr=fopen("data.txt","w");
    if(fptr==NULL)
    {
        printf("File Not found\n");
        return 0;
    }
    Contacts temp;//creating a nested structure for storing the whole details
    for(int i = 0; i < addressbook->contact_count - 1; i++)
    {
        for(int j = 0; j < addressbook->contact_count - i - 1; j++)
        {
            if(strcasecmp(addressbook->contact_details[j].Name,addressbook->contact_details[j + 1].Name) > 0)
            {
                temp = addressbook->contact_details[j];
                addressbook->contact_details[j] = addressbook->contact_details[j + 1];
                addressbook->contact_details[j + 1] = temp;
            }
        }
    }
    //storing to file
    rewind(fptr);
    fprintf(fptr,"#%d\n",addressbook->contact_count);
    for(int i=0;i<addressbook->contact_count;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
    }
    fclose(fptr);
    printf(GREEN"Save Completed\n\n"RESET);
    return 0;
}