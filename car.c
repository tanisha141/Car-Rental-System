#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "car.h"
#include <string.h>

void addAdmin()
{
    FILE *fp = fopen("admin.bin", "rb");
    User u[2] = {{"admin 1", "test", "Ravi"},{"admin 2", "demo", "Anil"} }; //userid, pwd, name
    if(fp == NULL)
    {
    fp = fopen("admin.bin", "wb");
    fwrite(u, sizeof(u), 1, fp);
    fclose(fp);
    }
    else
    {
        fclose(fp);
    }
}

User* getInput()
{
    int i;
    clrscr();
    gotoxy(32,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0; i<80; i++)
    {
        printf("%c", 247);
    }
    gotoxy(33,5);
    printf("* LOGIN PANEL *");
    textcolor(LIGHTCYAN);
    gotoxy(1,7);
    for(i=0; i<80; i++)
    {
        printf("%c", 247);
    }
    gotoxy(1,15);
    for(i=0; i<80; i++)
    {
        printf("%c", 247);
    }
    gotoxy(54,8);
    textcolor(WHITE);
    printf("Press zero to exit");
    textcolor(LIGHTCYAN);
    gotoxy(26,10);
    printf("Enter user id: ");
    textcolor(WHITE);
    static User u;//(local static) lifetime should be there even after the function ends, scope is not increasing
    fflush(stdin);
    //changes
    //printf("Hello world");
    //char arr[20];
    fgets(u.userid, 20, stdin);

    char *pos = strchr(u.userid, '\n');
    if( pos != NULL)
    {
        *pos = '\0';
    }
    for(i=0; i<20; i++)
    {
        printf("%c", u.userid[i]);
    }
    if(strcmp(u.userid, "0") == 0)
    {
        gotoxy(32,17);
        textcolor(LIGHTRED);
        printf("Login Cancelled"); //Press zero to exit
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    textcolor(LIGHTCYAN);
    gotoxy(26,11);
    printf("Enter password: ");
    fflush(stdin);
    i=0;
    textcolor(WHITE);
    for(;;)
    {
       u.pwd[i] = getch();
       if(u.pwd[i] == 8)
       {
          printf("\b");
          printf(" ");
          printf("\b");
          i--;
       }
       else if(u.pwd[i] == 13)
            break;
       else {
       printf("*");
       i++;}
    }
    u.pwd[i] = '\0';
    //changes
    for(i=0; i<20; i++)
    {
        printf("%c", u.pwd[i]);
    }
    if(strcmp(u.pwd, "0") == 0)
    {
        gotoxy(32,17);
        textcolor(LIGHTRED);
        printf("Login Cancelled"); //Press zero to exit
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    //changes
    printf("\n");
    for(i=0; i<20; i++)
    {
        printf("%c", u.pwd[i]);
    }
    printf("\n");
    for(i=0; i<20; i++)
    {
        printf("%c", u.userid[i]);
    }
    return &u;
}

int checkUserExist(User U, char* ch)
{
    printf("hello world into check user exist");
    if(strlen(U.userid)==0 || strlen(U.pwd)==0)
    {
        //changes
        printf("either userid or pwd is zero");
        gotoxy(27,20);
        textcolor(LIGHTRED);
        printf("Both fields are mandatory. Try again.");
        getch();
        gotoxy(27,20);
        printf("\t\t\t\t\t\t");
        return 0;
    }
    FILE *fp;
    if(strcmp(ch,"admin")==0)
    {
        //changes
        printf("fopen(admin.bin, rb)");
        fp=fopen("admin.bin","rb");
        fseek(fp, 0, SEEK_SET);
    }
    else
    {
        //changes
        printf("fopen(emp.bin, rb)");
        fp=fopen("emp.bin","rb");
        fseek(fp, 0, SEEK_SET);
    }
    if(fp==NULL)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Sorry ! Cannot open the file");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t\t");
        return -1;
    }
    int found=0;
    User user;
    while(fread(&user,sizeof(user),1,fp)==1)
    {
        if(strcmp(U.userid,user.userid)==0 && strcmp(U.pwd,user.pwd)==0)
        {
            found=1;
            //changes
            printf("found=1, matched!");
            break;
        }
    }
    if(found==0)
    {
        //changes
        printf("found=0, not matched!");
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Invalid user id or password. Try again");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t\t");
    }
    else
    {
        gotoxy(28,20);
        textcolor(GREEN);
        printf("Login successful!");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t\t");
    }
    fclose(fp);
    return found;
}

int adminMenu()
{
    textcolor(LIGHTRED);
    int choice, i;
    gotoxy(30,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(34,5);
    printf("ADMIN MENU\n");
    for(i=0; i<80; i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(30,8);
    printf("1. Add Employee");
    gotoxy(30,9);
    printf("2. Add Car Details");
    gotoxy(30,10);
    printf("3. Show Employee");
    gotoxy(30,11);
    printf("4. Show Car Details");
    gotoxy(30,12);
    printf("5. Delete Employee");
    gotoxy(30,13);
    printf("6. Delete Car Details");
    gotoxy(30,14);
    printf("7. Exit");
    gotoxy(30,16);
    printf("Enter choice:");
    textcolor(WHITE);
    scanf("%d", &choice);
    return choice;
}

void addEmployee()
{
    char ch[10];
    char choice = 'Y' ;
    char *pos ;
    User u;
    FILE *fp = fopen("emp.bin", "ab+");
    fseek(fp, 0, SEEK_END);
    long total_rec = ftell(fp)/sizeof(User);
    if(total_rec != 0)
    {
        fseek(fp, -60, SEEK_END);
        fread(ch, sizeof(ch), 1, fp);
        //printf("ch is %s", ch);
        //getch();
        pos = strchr(ch, '-');
        total_rec = atoi(pos+1);
        //printf("\ntotal rec is %ld", total_rec);
        //getch();
    }
    total_rec++;
    sprintf(ch, "EMP-%ld", total_rec);
    strcpy(u.userid, ch);
    fseek(fp, 0, SEEK_END);
    do
    {
        gotoxy(32,2);
        textcolor(LIGHTRED);
        printf("CAR RENTAL APP\n");
        textcolor(LIGHTGREEN);
        for(int i=0; i<80; i++)
        {
            printf("~");
        }
        textcolor(WHITE);
        gotoxy(23,5);
        printf("***** ADD EMPLOYEE DETAILS *****");
        gotoxy(1,8);
        textcolor(YELLOW);
        printf("Enter Employee Name:");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.name, 20, stdin); //enter might have also came if name is <20 characters
        char *pos ;
        pos = strchr(u.name, '\n');
        if(pos != NULL)
        {
            *pos = '\0';
        }
        textcolor(YELLOW);
        printf("Enter Employee Pwd:");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.pwd, 20, stdin);
        pos = strchr(u.pwd, '\n');
        if(pos != NULL)
        {
            *pos = '\0';
        }
        fwrite(&u, sizeof(u), 1, fp);
        gotoxy(28,15);
        textcolor(LIGHTGREEN);
        printf("EMPLOYEE ADDED SUCCESSFULLY");
        printf("\nEMPLOYEE ID is: %s", u.userid);
        getch();
        gotoxy(1,21);
        textcolor(LIGHTRED);
        printf("Do you want to add more employees? (Y/N): ");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c", &choice);
        while(choice!='n' && choice!='N' && choice!='Y' && choice!='y')
        {
            printf("\nIncorrect choice. Try again.");
            getch();
            printf("\r\t\t\t\t");
            gotoxy(1,21);
            textcolor(LIGHTRED);
            printf("Do you want to add more employees? (Y/N):           ");
            printf("\b\b\b\b\b\b\b\b\b\b");
            textcolor(WHITE);
            fflush(stdin);
            scanf("%c", &choice);
        }
        if(choice == 'n' || choice == 'N')
            break;
        else if(choice == 'y' || choice == 'Y')
            clrscr();
        total_rec++;
        sprintf(ch, "EMP-%ld", total_rec);
        strcpy(u.userid, ch);
    }while(1);
    fclose(fp);
}

void addCarDetails()
{
    int carid = 0 ;
    char choice = 'Y' ;
    Car u;
    FILE *fp = fopen("car.bin", "ab+");
    fseek(fp, 0, SEEK_END);
    int total_rec = ftell(fp)/sizeof(Car);
    if(total_rec != 0 )
    {
        fseek(fp, -68, SEEK_END);
        fread(&carid, sizeof(carid), 1, fp);
        //printf("carid is %d", carid);
        //getch();
        total_rec = carid;
        //printf("\ntotal rec is %d", total_rec);
        //getch();
    }
    total_rec++;
    carid = total_rec;
    u.car_id = carid;
    fseek(fp, 0, SEEK_END);
    do
    {
        clrscr();
        gotoxy(32,2);
        textcolor(LIGHTRED);
        printf("CAR RENTAL APP\n");
        textcolor(LIGHTGREEN);
        for(int i=0; i<80; i++)
        {
            printf("~");
        }
        textcolor(WHITE);
        gotoxy(25,5);
        printf("***** ADD CAR DETAILS *****");
        gotoxy(1,8);
        textcolor(YELLOW);
        printf("Enter Car Model:");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.car_name, 20, stdin);
        char *pos ;
        pos = strchr(u.car_name, '\n');
        if(pos != NULL)
        {
            *pos = '\0';
        }
        textcolor(YELLOW);
        printf("Enter Car Capacity:");
        textcolor(WHITE);
        scanf("%d", &u.capacity);
        textcolor(YELLOW);
        printf("Enter Car Count:");
        textcolor(WHITE);
        scanf("%d", &u.car_count);
        textcolor(YELLOW);
        printf("Enter Car Price per day:");
        textcolor(WHITE);
        scanf("%d", &u.price);
        fwrite(&u, sizeof(u), 1, fp);
        gotoxy(28,15);
        textcolor(LIGHTGREEN);
        printf("CAR ADDED SUCCESSFULLY");
        printf("\nCAR ID is: %d", u.car_id);
        getch();
        gotoxy(1,21);
        textcolor(LIGHTRED);
        printf("Do you want to add more cars? (Y/N): ");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c", &choice);
        total_rec++;
        u.car_id = total_rec;
        while(choice!='n' && choice!='N' && choice!='Y' && choice!='y')
        {
            printf("\nIncorrect choice. Try again.");
            getch();
            printf("\r\t\t\t\t");
            gotoxy(1,21);
            textcolor(LIGHTRED);
            printf("Do you want to add more cars? (Y/N):           ");
            printf("\b\b\b\b\b\b\b\b\b\b");
            textcolor(WHITE);
            fflush(stdin);
            scanf("%c", &choice);
        }
        if(choice == 'n' || choice == 'N')
            break;
    }while(choice=='Y' || choice=='y');
    fclose(fp);
}

void showEmployee()
{
    FILE *fp = fopen("emp.bin", "rb");
    User u;
    gotoxy(32, 1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(int i=0; i<80; i++)
    {
        printf("%c", 247);
    }
    gotoxy(30, 5);
    printf("* EMPLOYEE DETAILS *\n\n");
    textcolor(LIGHTGREEN);
    for(int i=0; i<80; i++)
    {
        printf("%c", 247);
    }
    if(fp == NULL)
    {
        gotoxy(31, 9);
        textcolor(LIGHTRED);
        printf("Sorry! No Employee added yet!");
        getch();
        return;
    }
    gotoxy(1, 9);
    for(int i=0; i<80; i++)
    {
        printf("%c", 247);
    }
    gotoxy(1, 8);
    printf("Employee ID\t\t\tName\t\t\tPassword");
    int row = 10;
    textcolor(YELLOW);
    while(fread(&u, sizeof(u), 1, fp)==1)
    {
        gotoxy(2, row);
        printf("%s", u.userid);
        gotoxy(33, row);
        printf("%s", u.name);
        gotoxy(57, row);
        printf("%s", u.pwd);
        row++;
    }
    fclose(fp);
    getch();
}

void showCarDetails()
{
    FILE *fp=fopen("car.bin","rb");
    Car c;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0; i<80; i++)
    {
        printf("%c",247);
    }
    gotoxy(31,5);
    printf("* ALL CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0; i<80; i++)
    {
        printf("%c",247);
    }
    if(fp==NULL)
    {
        gotoxy(31,9);
        textcolor(LIGHTRED);
        printf("Sorry! No cars present!");
        getch();
        return;
    }
    gotoxy(1,8);
    printf(" Car ID\t   Model\t\t Capacity\tAvailable\t  Price/Day");
    gotoxy(1,9);
    for(i=0; i<80; i++)
    {
        printf("%c",247);
    }
    int row=10;
    textcolor(YELLOW);
    while(fread(&c,sizeof(c),1,fp)==1)
    {
        gotoxy(2,row);
        printf("%d",c.car_id);
        gotoxy(12,row);
        printf("%s",c.car_name);
        gotoxy(38,row);
        printf("%d",c.capacity);
        gotoxy(50,row);
        printf("%d",c.car_count);
        gotoxy(68,row);
        printf("%d",c.price);
        row++;
    }
    fclose(fp);
    getch();
}

int deleteEmp()
{
    FILE *fp1=fopen("emp.bin","rb");
    char empid[10];
    int i,result;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0; i<80; i++)
        printf("%c",247);
    gotoxy(27,5);
    textcolor(YELLOW);
    printf("* DELETE EMPLOYEE RECORD *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0; i<80; i++)
        printf("%c",247);
    gotoxy(1,11);
    for(i=0; i<80; i++)
        printf("%c",247);
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo Employee Added Yet!");
        return -1;
    }
    FILE *fp2=fopen("temp.bin","wb+");
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter Employee Id to delete the record:");
    textcolor(WHITE);
    scanf("%s",empid);
    User U;
    int found=0;
    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(strcmp(U.userid,empid)!=0)
        {
            fwrite(&U,sizeof(U),1,fp2);
        }
        else
        {
            found=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp.bin");
    }
    else
    {
        result=remove("emp.bin");
        if(result!=0)
            return 2;
        result=rename("temp.bin","emp.bin");
        if(result!=0)
            return 2;
    }
    return found;
}

int deleteCarModel()
{
    FILE *fp1=fopen("car.bin","rb");
    int carid;
    int i,result;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0; i<80; i++)
        printf("%c",247);
    gotoxy(30,5);
    textcolor(YELLOW);
    printf("* DELETE CAR RECORD *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0; i<80; i++)
        printf("%c",247);
    gotoxy(1,11);
    for(i=0; i<80; i++)
        printf("%c",247);
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo Car Added Yet!");
        return -1;
    }
    FILE *fp2=fopen("temp.bin","wb+");
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter Car Id to delete the record:");
    textcolor(WHITE);
    scanf("%d",&carid);
    Car U;
    int found=0;
    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(U.car_id != carid)
        {
            fwrite(&U,sizeof(U),1,fp2);
        }
        else
        {
            found=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp.bin");
    }
    else
    {
        result=remove("car.bin");
        if(result!=0)
            return 2;
        result=rename("temp.bin","car.bin");
        if(result!=0)
            return 2;
    }
    return found;
}

int empMenu()
{
    int choice,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(34,6);
    printf("EMPLOYEE MENU\n");
    for(i=0; i<80; i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1. Rent A Car");
    gotoxy(32,9);
    printf("2. Booking Details");
    gotoxy(32,10);
    printf("3. Available Car Details");
    gotoxy(32,11);
    printf("4. Show All Car Details");
    gotoxy(32,12);
    printf("5. Return Car");
    gotoxy(32,13);
    printf("6. Exit");
    gotoxy(32,15);
    printf("Enter choice:");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;
}

int selectCarModel()
{
    int flag, choice, row=9;
    FILE *fp = fopen("car.bin", "rb");
    Car c;
    gotoxy(34,row);
    int carcount=0;
    while(fread(&c, sizeof(c), 1, fp)==1)
    {
        if(c.car_count > 0)
        {
            printf("%d. %s",c.car_id, c.car_name);
            gotoxy(34,++row);
            ++carcount;
        }
    }
    if(carcount==0)
    {
        fclose(fp);
        return -2;
    }
    gotoxy(27, row+2);
    printf("Enter your choice(0 to quit): ");
    while(1)
    {
        flag=0;
        textcolor(WHITE);
        scanf("%d", &choice);
        if(choice==0)
        {
            fclose(fp);
            return 0;
        }
        rewind(fp);
        while(fread(&c, sizeof(c), 1, fp)==1)
        {
            if(c.car_id == choice && c.car_count>0)
            {
                flag = 1;
                break;
            }
        }
        if(flag==1)
        {
            fclose(fp);
            return choice;
        }
        gotoxy(35, row+4);
        textcolor(LIGHTRED);
        printf("Wrong Input");
        getch();
        gotoxy(35, row+4);
        printf("\t\t");
        gotoxy(57, row+2);
        printf("\t\t\t");
        gotoxy(57, row+2);
        textcolor(WHITE);
    }
}

int matchWithStartDate(struct tm ed, struct tm sd)
{
    if(ed.tm_year<sd.tm_year)
        return 0;
    if(ed.tm_year==sd.tm_year && ed.tm_mon<sd.tm_mon)
        return 0;
    if(ed.tm_year==sd.tm_year && ed.tm_mon==sd.tm_mon && ed.tm_mday<sd.tm_mday)
        return 0;
    return 1;
}

int isValidDate(struct tm dt)
{
    time_t obj = time(0);
    struct tm * p = localtime(&obj);
    int cur_date = p->tm_mday;
    int cur_mon = p->tm_mon+1;
    int cur_year = p->tm_year+1900;
    if(dt.tm_year>=2021 && dt.tm_year<=2024)
    {
        if( (dt.tm_mon>=1&&dt.tm_mon<=12&&dt.tm_year>cur_year) || (dt.tm_mon>=cur_mon&&dt.tm_mon<=12&&dt.tm_year==cur_year) )
        {
            if( (dt.tm_year>cur_year) || (dt.tm_year==cur_year&&dt.tm_mon>cur_mon) || (dt.tm_year==cur_year&&dt.tm_mon==cur_mon&&dt.tm_mday>=cur_date) )
            {
                if((dt.tm_mday>=1 && dt.tm_mday<=31) && (dt.tm_mon==1 || dt.tm_mon==3 || dt.tm_mon==5 || dt.tm_mon==7 || dt.tm_mon==8 || dt.tm_mon==10 || dt.tm_mon==12))
                    return 1;
                else if((dt.tm_mday>=1 && dt.tm_mday<=30) && (dt.tm_mon==4 || dt.tm_mon==6 || dt.tm_mon==9 || dt.tm_mon==11))
                    return 1;
                else if((dt.tm_mday>=1 && dt.tm_mday<=28) && dt.tm_mon==2 )
                    return 1;
                else if((dt.tm_mday>=1 && dt.tm_mday<=29) && (dt.tm_mon==2) && (dt.tm_year%400 == 0 || (dt.tm_year%4==0 && dt.tm_year%100!=0)) )
                    return 1;
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
    {
        return 0;
    }
}

void updateCarCount(int c_id)
{
    FILE *fp = fopen("car.bin", "rb+");
    if(fp==NULL)
    {
        printf("Sorry! File cannot be opened");
        return;
    }
    Car c;
    while(fread(&c, sizeof(Car),1,fp)==1)
    {
        if(c.car_id == c_id)
        {
            int x = c.car_count;
            x--;
            fseek(fp, -8, SEEK_CUR);
            fwrite(&x, sizeof(int), 1, fp);
            break;
        }
    }
    fclose(fp);
}

char* getCarName(int car_id)
{
    FILE *fp=fopen("car.bin","rb");
    static Car C;
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_id==car_id)
        {
             break;
        }
    }
    fclose(fp);
    return C.car_name;
}

void bookedCarDetails()
{
    clrscr();
    FILE *fp = fopen("customer.bin", "rb+");
    Customer_Car_Details cc;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(int i=0; i<80; i++)
    {
        printf("%c", 247);
    }
    gotoxy(30,5);
    printf("* BOOKED CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(int i=0; i<80; i++)
    {
        printf("%c", 247);
    }
    gotoxy(1,9);
    for(int i=0; i<80; i++)
    {
        printf("%c", 247);
    }
    gotoxy(1,8);
    printf("Model\t    Cust Name\t  Pick Up\t   Drop\t\t S_Date\t     E_Date");
    int row=10;
    textcolor(YELLOW);
    while(fread(&cc,sizeof(Customer_Car_Details),1,fp)==1)
    {
        gotoxy(1,row);
        printf("%s",getCarName(cc.car_id));
        gotoxy(13,row);
        printf("%s",cc.cust_name);
        gotoxy(27,row);
        printf("%s",cc.pick);
        gotoxy(44,row);
        printf("%s",cc.drop);
        gotoxy(58,row);
        printf("%d-%d-%d", cc.sd.tm_mday, cc.sd.tm_mon, cc.sd.tm_year);
        gotoxy(70,row);
        printf("%d-%d-%d",cc.ed.tm_mday, cc.ed.tm_mon, cc.ed.tm_year);
        row++;
    }
    fclose(fp);
    getch();
}

int rentCar()
{
    Customer_Car_Details cc;
    int c,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(34,6);
    printf("EMPLOYEE MENU\n");
    for(i=0; i<80; i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(32,8);
    c = selectCarModel();
    if(c==0 || c==-2)
        return c;
    clrscr();
    cc.car_id = c;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(34,6);
    printf("EMPLOYEE MENU\n");
    for(i=0; i<80; i++)
    {
        printf("*");
    }
    gotoxy(1,17);
    for(i=0; i<80; i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(27,9);
    printf("Enter customer name:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(cc.cust_name, 30, stdin);
    char *pos;
    pos = strchr(cc.cust_name, '\n');
    *pos = '\0';
    gotoxy(27,10);
    textcolor(YELLOW);
    printf("Enter pickup point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(cc.pick, 30, stdin);
    pos = strchr(cc.pick, '\n');
    *pos = '\0';
    gotoxy(27,11);
    textcolor(YELLOW);
    printf("Enter drop point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(cc.drop, 30, stdin);
    pos = strchr(cc.drop, '\n');
    *pos = '\0';
    gotoxy(27,12);
    textcolor(YELLOW);
    printf("Enter start date(dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d", &cc.sd.tm_mday, &cc.sd.tm_mon, &cc.sd.tm_year);
        int datevalid = isValidDate(cc.sd);
        if(datevalid==0)
        {
            gotoxy(27,18);
            textcolor(LIGHTRED);
            printf("Wrong date");
            getch();
            gotoxy(27,18);
            printf("\t\t");
            gotoxy(56,12);
            printf("\t\t\t");
            gotoxy(56,12);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);
    gotoxy(27,13);
    textcolor(YELLOW);
    printf("Enter end date(dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d", &cc.ed.tm_mday, &cc.ed.tm_mon, &cc.ed.tm_year);
        int datevalid = isValidDate(cc.ed);
        int dtvalid = matchWithStartDate(cc.ed, cc.sd);
        if(datevalid==0 || dtvalid==0)
        {
            gotoxy(27,18);
            textcolor(LIGHTRED);
            printf("Wrong date");
            getch();
            gotoxy(27,18);
            printf("\t\t");
            gotoxy(54,13);
            printf("\t\t\t");
            gotoxy(54,13);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);
    FILE *fp;
    fp=fopen("customer.bin","ab");
    if(fp==NULL)
    {
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Sorry ! File cannot be opened");
        getch();
        gotoxy(27,18);
        printf("\t\t");
        return -1;
    }
    fwrite(&cc,sizeof(Customer_Car_Details),1,fp);
    printf("\nBooking Done for car: %d, %s",cc.car_id, getCarName(cc.car_id));
    printf("\nPress any key to continue...");
    getch();
    fclose(fp);
    updateCarCount(c);
    bookedCarDetails();
    return 1;
}

void availCarDetails()
{
    int i;
    Car c;
    FILE *fp = fopen("car.bin", "rb");
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c", 247);
    }
    gotoxy(30,5);
    textcolor(YELLOW);
    printf("* AVAILABLE CAR DETAILS *");
    gotoxy(1,7);
    textcolor(GREEN);
    for(i=0;i<80;i++)
    {
        printf("%c", 247);
    }
    if(fp==NULL)
    {
        gotoxy(32,8);
        textcolor(LIGHTRED);
        printf("Sorry file cannot be opened");
        getch();
        return;
    }
    gotoxy(1,8);
    printf("Car ID\t    Model\t       Capacity\t\tAvailable\t Price/Day ");
    gotoxy(1,9);
    for(i=0;i<80;i++)
    {
        printf("%c", 247);
    }
    textcolor(YELLOW);
    int row=10;
    while(fread(&c, sizeof(c), 1, fp) == 1)
    {
        if(c.car_count > 0)
        {
            gotoxy(2,row);
            printf("%d", c.car_id);
            gotoxy(13,row);
            printf("%s", c.car_name);
            gotoxy(35,row);
            printf("%d", c.capacity);
            gotoxy(50,row);
            printf("%d", c.car_count);
            gotoxy(68,row);
            printf("%d", c.price);
            row++;
        }
    }
    fclose(fp);
    getch();
}

void returnCar()
{
    clrscr();
    int i, result;
    char custname[10];
    char carmodel[10];
    Customer_Car_Details cc;
    Car c;
    FILE *fp1 = fopen("customer.bin", "rb");
    FILE *fp2 = fopen("car.bin", "rb");
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(int i=0; i<80; i++)
    {
        printf("%c", 247);
    }
    gotoxy(34,5);
    printf("* RETURN CAR *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0; i<80; i++)
        printf("%c",247);
    gotoxy(1,12);
    for(i=0; i<80; i++)
        printf("%c",247);
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo Customer Yet!");
    }
    gotoxy(15,9);
    textcolor(YELLOW);
    printf("Enter customer name: ");
    textcolor(WHITE);
    scanf("%s",custname);
    gotoxy(15,10);
    textcolor(YELLOW);
    printf("Enter car model: ");
    textcolor(WHITE);
    scanf("%s",carmodel);
    int found1=0, found2=0;
    int check1=0, check2=0;
    while(fread(&cc,sizeof(cc),1,fp1)==1)
    {
        if(strcmp(cc.cust_name,custname)==0)
        {
            check1 =1;
            break;
        }
    }
    while(fread(&c,sizeof(c),1,fp2)==1)
    {
        if(strcmp(c.car_name,carmodel)==0)
        {
            check2 =1;
            break;
        }
    }
    rewind(fp1);
    rewind(fp2);
    if(check1==1 && check2==1)
    {
        FILE *fp11 = fopen("customer11.bin", "wb+");
        FILE *fp22 = fopen("car22.bin", "wb+");
        while(fread(&cc,sizeof(cc),1,fp1)==1)
        {
        if(strcmp(cc.cust_name,custname)!=0)
        {
            fwrite(&cc,sizeof(cc),1,fp11);
        }
        else
        {
            found1=1;
        }
        }
        while(fread(&c,sizeof(c),1,fp2)==1)
        {
        if(strcmp(c.car_name,carmodel)!=0)
        {
            fwrite(&c,sizeof(c),1,fp22);
        }
        else
        {
            c.car_count++;
            fwrite(&c,sizeof(c),1,fp22);
            found2=1;
        }
        }
            fclose(fp1);
            fclose(fp2);
            fclose(fp11);
            fclose(fp22);
        result=remove("customer.bin");
        if(result!=0)
        {
            textcolor(LIGHTRED);
            printf("Sorry! Error in deletion. Try again!");
            return;
        }
        result=rename("customer11.bin","customer.bin");
        if(result!=0)
        {
            textcolor(LIGHTRED);
            printf("Sorry! Error in deletion. Try again!");
            return;
        }
        result=remove("car.bin");
        if(result!=0)
        {
            textcolor(LIGHTRED);
            printf("\nSorry! Error in deletion. Try again!");
            return;
        }
        result=rename("car22.bin","car.bin");
        if(result!=0)
        {
            textcolor(LIGHTRED);
            printf("\nSorry! Error in deletion. Try again!");
            return;
        }
        if(found1==1 && found2==1)
        {
        textcolor(LIGHTGREEN);
        printf("Car Returned succesfully");
        }
    }
    else
    {
        textcolor(RED);
        printf("No such customer found.");
    }
}






