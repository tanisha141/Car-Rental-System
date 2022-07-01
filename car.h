#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <time.h>
typedef struct User
{
    char userid[20];
    char pwd[20];
    char name[20];
} User;
typedef struct Car
{
    int car_id;
    char car_name[50];
    int capacity;
    int car_count;
    int price;
} Car;
typedef struct Customer_Car_Details
{
    int car_id;
    char cust_name[30];
    char pick[30];
    char drop[30];
    struct tm sd; //start date
    struct tm ed; //end date
} Customer_Car_Details;

void addAdmin();
User* getInput();
int checkUserExist(User, char*);
int adminMenu();
void addEmployee();
void showEmployee();
void addCarDetails();
void showCarDetails();
int deleteEmp();
int deleteCarModel();

int rentCar();
int empMenu();
int selectCarModel();
int isValidDate(struct tm);
int matchWithStartDate(struct tm, struct tm);
void updateCarCount(int);
void bookedCarDetails();
void availCarDetails();
void showCarDetails();
void returnCar();
#endif // CAR_H_INCLUDED
