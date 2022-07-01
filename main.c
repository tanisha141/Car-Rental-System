#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "car.h"
int main()
{
    int i;
    int type, k, choice;
    User *user;
    gotoxy(25,10);
    textcolor(YELLOW);
    printf("WELCOME TO CAR RENTAL SYSTEM");
    gotoxy(21,13);
    textcolor(LIGHTGREEN);
    printf("*RENT A CAR AND GO WHEREVER YOU NEED*");
    getch();
    textcolor(YELLOW);
    addAdmin();
    while(1)
    {
        clrscr();
        gotoxy(30,2);
        textcolor(LIGHTRED);
        printf("CAR RENTAL SYSTEM");
        gotoxy(1,6);
        textcolor(YELLOW);
        for(i=0; i<40; i++)
        {
            printf("**");
        }
        gotoxy(1,18);
        for(i=0; i<80; i++)
        {
            printf("*");
        }
        gotoxy(30,8);
        printf("1.ADMIN");
        gotoxy(30,10);
        printf("2.EMPLOYEE");
        gotoxy(30,12);
        printf("3.QUIT");
        gotoxy(30,14);
        textcolor(WHITE);
        printf("Select your role:");
            scanf("%d", &type);  //admin type or employee type
            k=0;
            if( type == 1)
            {
                while(k==0)
                {
                user = getInput();
                if(user == NULL) //login canceled
                {
                    break;
                }
                else
                {
                    k = checkUserExist(*user, "admin"); //call to validate function
                }
                }
                if(k==-1) //file could not be opened
                    break;
                if(k==1) //found=1
                {
                    gotoxy(1,20);
                    textcolor(WHITE);
                    printf("Press any key to continue");
                    getch();
                    while(1)
                    {
                        clrscr();
                        choice = adminMenu();
                        if(choice == 7)
                        {
                            break;
                        }
                        switch(choice)
                        {
                        case 1:
                            clrscr();
                            addEmployee();
                            break;
                        case 2:
                            clrscr();
                            addCarDetails();
                            break;
                        case 3:
                            clrscr();
                            showEmployee();
                            break;
                        case 4:
                            clrscr();
                            showCarDetails();
                            break;
                        case 5:
                            clrscr();
                            int result=deleteEmp();
                            gotoxy(15,14);
                            if(result==0)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! No employee found for given EMP id.");
                            }
                            else if(result==1)
                            {
                                textcolor(LIGHTGREEN);
                                printf("Record deleted successfully!");
                            }
                            else if(result==2)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! Error in deletion. Try again!");
                            }
                            textcolor(WHITE);
                            printf("\n\nPress any key to go back to the main screen!");
                            getch();
                            break;
                        case 6:
                            clrscr();
                            int res=deleteCarModel();
                            gotoxy(15,14);
                            if(res==0)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! No Car found for given car id.");
                            }
                            else if(res==1)
                            {
                                textcolor(LIGHTGREEN);
                                printf("Record deleted successfully!");
                            }
                            else if(res==2)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! Error in deletion. Try again!");
                            }
                            textcolor(WHITE);
                            printf("\n\nPress any key to go back to the main screen!");
                            getch();
                            break;
                        default:
                            printf("Incorrect choice");
                            getch();
                        }
                    }
                }
            }
            else if( type == 2)
            {
                k=0;
                while(k==0)
                {
                user = getInput(); //user is a pointer of User type
                if(user == NULL)
                {
                    break;
                }
                else
                {
                    k = checkUserExist(*user, "emp"); //call to validate function
                }
                }
                if(k==-1)
                    break;
                if(k==1)
                {
                    gotoxy(1,20);
                    textcolor(WHITE);
                    printf("Press any key to continue");
                    getch();
                    while(1)
                    {
                        clrscr();
                        choice = empMenu();
                        if(choice == 6)
                        {
                            clrscr();
                            break;
                        }
                        switch(choice)
                        {
                        case 1:
                            clrscr();
                            int rentresp = rentCar();
                            if(rentresp == -2)
                            {
                                gotoxy(35,9);
                                textcolor(LIGHTRED);
                                printf("Sorry! All cars booked. Try again later.");
                                getch();
                            }
                            else if(rentresp == 0 )
                            {
                                gotoxy(27,23);
                                textcolor(LIGHTRED);
                                printf("You did not choose any car");
                                getch();
                            }
                            break;
                        case 2:
                            clrscr();
                            bookedCarDetails();
                            break;
                        case 3:
                            clrscr();
                            availCarDetails();
                            break;
                        case 4:
                            clrscr();
                            showCarDetails();
                            break;
                        case 5:
                            clrscr();
                            returnCar();
                            textcolor(WHITE);
                            printf("\n\nPress any key to go back to the main screen!");
                            getch();
                            break;
                        default:
                            printf("Incorrect Choice");
                            getch();
                        }
                    }
                }
            }
            else if( type == 3)
            {
                clrscr();
                textcolor(GREEN);
                gotoxy(25,15);
                printf("Thank you for using our app");
                getch();
                textcolor(WHITE);
                exit(0); //return 0;
            }
            else
            {
                gotoxy(29,21);
                textcolor(RED);
                printf("Invalid User Type");
                getch();
                gotoxy(29,21);
                printf("\t\t\t");
                gotoxy(47,14);
                printf("\t\t");
                textcolor(WHITE);
                gotoxy(47,14);
            }
    }
    return 0;
}
