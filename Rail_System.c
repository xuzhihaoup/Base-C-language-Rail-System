#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include "Rail_System.h"


//初始化各模块
Data_List Open_Rail_data(Data_List Rail_data);
void printAllTrains(Data_List Rail_data,int state);
Data_List addTrain(Data_List Rail_data);
Data_List stopTrain(Data_List Rail_data);
void searchTrain(Data_List Rail_data);
Data_List modifyTrain(Data_List Rail_data);

Data_Passenger_List Open_Passenger_data(Data_Passenger_List Passenger_data);
Data_Passenger_List addPassenger(Data_Passenger_List Passenger_data);
void printAllPassengers(Data_Passenger_List Passenger_data);
void searchPassenger(Data_Passenger_List Passenger_data);
Data_Passenger_List modifyPassenger(Data_Passenger_List Passenger_data);
Data_Passenger_List deletePassenger(Data_Passenger_List Passenger_data);

Data_Order_List Open_Order_data(Data_Order_List Order_data);
Data_Order_List reserveTicket(Data_Order_List Order_data,Data_List Rail_data);
void printAllOrders(Data_Order_List Order_data);
void Order_data_print(Data_Order_List Order_data, int i);
void printOrderInfo_num(Data_Order_List Order_data);
int generateRandomNumber(int min, int max);
void searchOrder(Data_Order_List Order_data);
void checkRemainingSeats(Data_Order_List Order_data, Data_List Rail_data);
Data_Order_List deleteOrder(Data_Order_List Order_data);
void OrdershowMenu();
void RailshowMenu();
void ALLshowMenu();
void PassengershowMenu();
void RailSYSTEM(Data_List Rail_data);
void PassengerSYSTEM(Data_Passenger_List  Passenger_data);
void OrderSYSTEM(Data_Order_List Order_data);
int main()
{  
    Data_List Rail_data;
    Data_Passenger_List  Passenger_data;
    Data_Order_List Order_data;
    char result[20];
    //初始化数据结构
    Init_List(&Rail_data);
    Init_List(&Passenger_data);
    Init_List(&Order_data);
    //加载数据
    Passenger_data = Open_Passenger_data(Passenger_data);
    Order_data     = Open_Order_data(Order_data);
    Rail_data      = Open_Rail_data(Rail_data);

    int choice;
    do {
        ALLshowMenu();
        printf("请选择操作： ");
        scanf_s("%d", &choice);
       
        switch (choice) {
        case 1:
            PassengerSYSTEM(Passenger_data);
            break;
        case 2:
            RailSYSTEM(Rail_data);
            break;
        case 3:
            OrderSYSTEM(Order_data);
            break;
        case 0:
            printf("感谢使用高铁订票系统！\n");
            break;
        default:
            printf("无效的选择，请重新输入。\n");
        }
    } while (choice != 0);
     return 0;
}






















