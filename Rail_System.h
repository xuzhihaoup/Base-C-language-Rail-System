#ifndef  _Rail_System_
#define  _Rail_System_
#define _CRT_SECURE_NO_WARNINGS
#define MaxSize        100//存储最大长度
//状态代码
#define   TRUE           1
#define   FALSE          0
#define   OK             1
#define   ERROR          0
#define   INFEASIBLE    -1
#define   OVERFLOW      -2

int      allraildataNum = 0;


typedef struct {
	char  trainNumber[20];         // 车次
	char  startingStation[50];     // 始发站
	char  destinationStation[50];  // 终到站
	int   alldistance;         // 总里程（单位公里）
	char  isServiceAvailable[50];  // 运行情况（是否停运）
	char  departureTime[10];   // 发车时间
	char  arriveTime[10];      // 达到时间
	int   allstationNumber;         //停靠站数
	int   principalSeat; //特等座
	int   firSeat; //1等座
	int   secSeat; //2等座
	// 停靠车站的信息
	struct {
		char stationName[50];  // 车站名
		char arrivalTime[10];   // 进站时间
		char departureTime[10]; // 出站时间
		int distance;         // 里程（单位公里）
	       }stops[20];  // 最多存储10个停靠车站的信息
}Data_Type; //列车数据类型定义
typedef struct {
    char passengerName[50];
    char idType[20];  // 证件类别
    char idNumber[20];  // 证件号
    char phoneNumber[20];//联系电话
    char emergencyContact[50];  // 紧急联系人
    char emergencyContactPhone[20];// 紧急联系人联系电话
} Passenger;//乘客数据类型定义
typedef struct {
    char orderNumber[20]; // 订单号
    char travelDate[20]; // 乘车日期
    char trainNumber[20]; // 车次
    char startingStation[50]; // 始发站
    char destinationStation[50]; // 终到站
    char idType[20]; // 证件类别
    char idNumber[20]; // 证件号
    char passengerName[50]; // 乘客姓名
    char departureTime[10]; // 开车时间
    char arriveTime[10]; // 到达时间
    char seatClass[20]; // 座位等级 特等座	一等座	二等座
    char seatNumber[10]; // 座位号
    float ticketPrice; // 票价
} Order; // 订单数据类型定义




typedef struct {
	Data_Type  *Rail_Data;  //存储空间基地址
	int         Length; //当前表长
}Data_List; //定义列车线性表数据类型
typedef struct {
    Passenger  * Passenger_Data;  //存储空间基地址
    int         Length; //当前表长
}Data_Passenger_List; //定义列车线性表数据类型
typedef struct {
    Order *Order_Data; // 存储空间基地址
    int Length; // 当前表长
} Data_Order_List; // 定义订单线性表数据类型




//初始化线性表
int Init_List(Data_List* list)
{//初始化顺序表
	list->Rail_Data = (Data_Type*)malloc(sizeof(Data_Type) * MaxSize);//为顺序内存分配
	if (!list->Rail_Data)
	{
		return  OVERFLOW;             //分配失败
	}
	list->Length = 0;                                            //初始化表长
	return OK;                                                   //初始化成功
}
//加载火车数据从TXT
Data_List Open_Rail_data(Data_List Rail_data) {
    int count = 0;
    FILE* file;
    char line[1024];
    int result = 0;
    long int read_rail_data_index = 0, index_num = 0;
    errno_t err = fopen_s(&file, "C:\\Rail_system\\Rail_System\\train.txt", "r");
    if (err == 0) {

        printf("列车数据加载成功\n");
        while (fgets(line, sizeof(line), file) != NULL)
        {
            result = sscanf_s(line, "%s %s %s %d %s %s %s %d %d %d %d%n",
                Rail_data.Rail_Data[count].trainNumber, sizeof(Rail_data.Rail_Data[count].trainNumber),
                Rail_data.Rail_Data[count].startingStation, sizeof(Rail_data.Rail_Data[count].startingStation),
                Rail_data.Rail_Data[count].destinationStation, sizeof(Rail_data.Rail_Data[count].destinationStation),
                &Rail_data.Rail_Data[count].alldistance,
                Rail_data.Rail_Data[count].isServiceAvailable, sizeof(Rail_data.Rail_Data[count].isServiceAvailable),
                Rail_data.Rail_Data[count].departureTime, sizeof(Rail_data.Rail_Data[count].departureTime),
                Rail_data.Rail_Data[count].arriveTime, sizeof(Rail_data.Rail_Data[count].arriveTime),
                &Rail_data.Rail_Data[count].allstationNumber,
                &Rail_data.Rail_Data[count].principalSeat,
                &Rail_data.Rail_Data[count].firSeat,
                &Rail_data.Rail_Data[count].secSeat,
                &read_rail_data_index
            );
            //停靠站载入
            for (int i = 0; i < Rail_data.Rail_Data[count].allstationNumber; i++) {
                result = sscanf_s(line + read_rail_data_index, "%s %s %s %d %n",
                    Rail_data.Rail_Data[count].stops[i].stationName, sizeof(Rail_data.Rail_Data[count].stops[i].stationName),
                    Rail_data.Rail_Data[count].stops[i].arrivalTime, sizeof(Rail_data.Rail_Data[count].stops[i].arrivalTime),
                    Rail_data.Rail_Data[count].stops[i].departureTime, sizeof(Rail_data.Rail_Data[count].stops[i].departureTime),
                    &Rail_data.Rail_Data[count].stops[i].distance,
                    &index_num
                );
                read_rail_data_index = read_rail_data_index + index_num;
                index_num = 0;
            }
            count++;
            read_rail_data_index = 0;
        }
        Rail_data.Length = count;
    }
    else {
        fprintf(stderr, "Unable to open file.\n");
    }
    fclose(file);
    return Rail_data;
}
//加载乘客数据从TXT
Data_Passenger_List Open_Passenger_data(Data_Passenger_List Passenger_data) {
    int count = 0;
    FILE* file;
    char line[1024];
    int result = 0;
    long int read_rail_data_index = 0, index_num = 0;
    errno_t err = fopen_s(&file, "C:\\Rail_system\\Rail_System\\passenger.txt", "r");
    if (err == 0) {

        printf("乘客数据加载成功\n");
        while (fgets(line, sizeof(line), file) != NULL)
        {
            result = sscanf_s(line, "%s %s %s %s %s %s",
                Passenger_data.Passenger_Data[count].idNumber, sizeof(Passenger_data.Passenger_Data[count].idNumber),
                Passenger_data.Passenger_Data[count].passengerName, sizeof(Passenger_data.Passenger_Data[count].passengerName),
                Passenger_data.Passenger_Data[count].idType, sizeof(Passenger_data.Passenger_Data[count].idType),
                Passenger_data.Passenger_Data[count].phoneNumber, sizeof(Passenger_data.Passenger_Data[count].phoneNumber),
                Passenger_data.Passenger_Data[count].emergencyContact, sizeof(Passenger_data.Passenger_Data[count].emergencyContact),
                Passenger_data.Passenger_Data[count].emergencyContactPhone, sizeof(Passenger_data.Passenger_Data[count].emergencyContactPhone)
                );
            count++;
        }
        Passenger_data.Length = count;
    }
    else {
        fprintf(stderr, "Unable to open file.\n");
    }
    fclose(file);
    return Passenger_data;
}
//加载订单数据从TXT
Data_Order_List Open_Order_data(Data_Order_List Order_data) {
    int count = 0;
    FILE* file;
    char line[1024];
    int result = 0;
    long int read_order_data_index = 0, index_num = 0;
    errno_t err = fopen_s(&file, "C:\\Rail_system\\Rail_System\\booking.txt", "r");
    if (err == 0) {
        printf("订单数据加载成功\n");
        while (fgets(line, sizeof(line), file) != NULL)
        {
            result = sscanf_s(line, "%s %s %s %s %s %s %s %s %s %s %s %s %f",
                Order_data.Order_Data[count].orderNumber, sizeof(Order_data.Order_Data[count].orderNumber),
                Order_data.Order_Data[count].travelDate, sizeof(Order_data.Order_Data[count].travelDate),
                Order_data.Order_Data[count].trainNumber, sizeof(Order_data.Order_Data[count].trainNumber),
                Order_data.Order_Data[count].startingStation, sizeof(Order_data.Order_Data[count].startingStation),
                Order_data.Order_Data[count].destinationStation, sizeof(Order_data.Order_Data[count].destinationStation),
                Order_data.Order_Data[count].idType, sizeof(Order_data.Order_Data[count].idType),
                Order_data.Order_Data[count].idNumber, sizeof(Order_data.Order_Data[count].idNumber),
                Order_data.Order_Data[count].passengerName, sizeof(Order_data.Order_Data[count].passengerName),
                Order_data.Order_Data[count].departureTime, sizeof(Order_data.Order_Data[count].departureTime),
                Order_data.Order_Data[count].arriveTime, sizeof(Order_data.Order_Data[count].arriveTime),
                Order_data.Order_Data[count].seatClass, sizeof(Order_data.Order_Data[count].seatClass),
                Order_data.Order_Data[count].seatNumber, sizeof(Order_data.Order_Data[count].seatNumber),
                &Order_data.Order_Data[count].ticketPrice
            );
            count++;
        }
        Order_data.Length = count;
    }
    else {
        fprintf(stderr, "Unable to open file.\n");
    }
    fclose(file);
    return Order_data;
}
//增开列车
Data_List addTrain(Data_List Rail_data){
        // 读取新列车的信息
        printf("当前共有%d个车次信息\n", Rail_data.Length);
        printf("请输入新列车的信息：\n");
        printf("车次：");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].trainNumber, sizeof(Rail_data.Rail_Data[Rail_data.Length].trainNumber));
        printf("始发站：");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].startingStation, sizeof(Rail_data.Rail_Data[Rail_data.Length].startingStation));
        printf("终点站：");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].destinationStation, sizeof(Rail_data.Rail_Data[Rail_data.Length].destinationStation));
        printf("总里程(单位公里)：");
        scanf_s("%d", &Rail_data.Rail_Data[Rail_data.Length].alldistance);
        printf("运行情况(是否停运)：");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].isServiceAvailable, sizeof(Rail_data.Rail_Data[Rail_data.Length].isServiceAvailable));
        printf("发车时间：");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].departureTime, sizeof(Rail_data.Rail_Data[Rail_data.Length].departureTime));
        printf("到达时间：");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].arriveTime, sizeof(Rail_data.Rail_Data[Rail_data.Length].arriveTime));
        printf("停靠站数：");
        scanf_s("%d", &Rail_data.Rail_Data[Rail_data.Length].allstationNumber);
        printf("特等座数量：");
        scanf_s("%d", &Rail_data.Rail_Data[Rail_data.Length].principalSeat);
        printf("一等座数量：");
        scanf_s("%d", &Rail_data.Rail_Data[Rail_data.Length].firSeat);
        printf("二等座数量：");
        scanf_s("%d", &Rail_data.Rail_Data[Rail_data.Length].secSeat);
        // 增加停靠站信息数目
        for (int i = 0; i < Rail_data.Rail_Data[Rail_data.Length].allstationNumber; i++) {
            printf("请输入第%d站信息(站名 进站时间 出站时间 里程)：",i+1);
            scanf_s("%s %s %s %d", Rail_data.Rail_Data[Rail_data.Length].stops[i].stationName,sizeof(Rail_data.Rail_Data[Rail_data.Length].stops[i].stationName),
                                   Rail_data.Rail_Data[Rail_data.Length].stops[i].arrivalTime, sizeof(Rail_data.Rail_Data[Rail_data.Length].stops[i].arrivalTime),
                                   Rail_data.Rail_Data[Rail_data.Length].stops[i].departureTime, sizeof(Rail_data.Rail_Data[Rail_data.Length].stops[i].departureTime),
                                   &Rail_data.Rail_Data[Rail_data.Length].stops[i].distance
                 );       
        }
        Rail_data.Length++;
        printf("列车添加成功！\n");
        printf("当前共有%d个车次信息\n", Rail_data.Length);
        return Rail_data;
}
// 添加一个乘客（插入）
Data_Passenger_List addPassenger(Data_Passenger_List Passenger_data) {
        // 读取新乘客的信息
        printf("请输入新乘客的信息：\n");
        printf("姓名：");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].passengerName,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].passengerName));
        printf("证件类别：");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].idType,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].idType));
        printf("证件号：");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].idNumber,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].idNumber));
        printf("手机号：");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].phoneNumber,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].phoneNumber));
        printf("紧急联系人：");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].emergencyContact,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].emergencyContact));
        printf("紧急联系人电话：");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].emergencyContactPhone,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].emergencyContactPhone));

        printf("乘客添加成功！\n");
        Passenger_data.Length++;
        return Passenger_data;
}
//订票（插入）
Data_Order_List reserveTicket(Data_Order_List Order_data, Data_List Rail_data) {
    Data_Order_List old_Order_data;
    old_Order_data = Order_data;
    Order_data.Length = Order_data.Length + 1;

    int distance = 0;
   // 获取系统当前时间
    time_t currentTime;
    time(&currentTime);
    struct tm tmInfo;
    localtime_s(&tmInfo, &currentTime);
    // 使用 strftime 格式化输出
    char buffer[80];  // 足够大以容纳格式化后的字符串
    if (strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tmInfo) != 0) {
        printf("当前时间：%s仅限订购两个月以内的车票\n", buffer);
    }
    else {
        printf("日期获取失败！\n");
    }


    // 填写新订单的相关信息
    printf("请输入订票时间：\n");
    printf("乘车日期(格式：20230101)：");
    scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].travelDate, sizeof(Order_data.Order_Data[Order_data.Length].orderNumber));
    Order_data.Order_Data[Order_data.Length].ticketPrice = 0.0;
    // 计算两个月后的时间
    struct tm twoMonthsLater;
    if (localtime_s(&twoMonthsLater, &currentTime) == 0) {
        twoMonthsLater.tm_mon += 2;
        time_t twoMonthsLaterTime = mktime(&twoMonthsLater);
        // 将用户输入的日期字符串转换为结构体
        int year, month, day;
        sscanf_s(Order_data.Order_Data[Order_data.Length-1].travelDate, "%4d%2d%2d", &year, &month, &day);
        // 构造结构体
        struct tm inputDate = { 0 };
        inputDate.tm_year = year - 1900;  // 年份减去1900
        inputDate.tm_mon = month - 1;  // 月份从0开始
        inputDate.tm_mday = day;
        time_t inputDateTime = mktime(&inputDate);
        // 检查是否在两个月内
        if (difftime(inputDateTime, twoMonthsLaterTime) > 0) {
            printf("只能预定两个月内的车票，预定失败！\n");
            
        }
        else {
            printf("请输入相关订票信息\n");
            printf("始发站：");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].startingStation, sizeof(Order_data.Order_Data[Order_data.Length].startingStation));
            printf("终到站：");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].destinationStation, sizeof(Order_data.Order_Data[Order_data.Length].destinationStation));
            printf("证件类别(身份证 护照)：");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].idType, sizeof(Order_data.Order_Data[Order_data.Length].idType));
            printf("证件号：");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].idNumber, sizeof(Order_data.Order_Data[Order_data.Length].idNumber));
            printf("乘客姓名：");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].passengerName, sizeof(Order_data.Order_Data[Order_data.Length].passengerName));
            printf("座位等级(特等座	一等座	二等座)：");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].seatClass, sizeof(Order_data.Order_Data[Order_data.Length].seatClass));
            for (int count = 0; count < Rail_data.Length; count++) {
                if (strcmp(Rail_data.Rail_Data[count].isServiceAvailable, "正常") != 0) {
                    continue;  // 如果列车状态不是正常，跳过该列车
                }
                // 遍历该列车的停靠站信息
                for (int i = 0; i < Rail_data.Rail_Data[count].allstationNumber; i++) {
                    // 检查是否符合用户输入的始发站
                    if (strcmp(Order_data.Order_Data[Order_data.Length-1].startingStation, Rail_data.Rail_Data[count].stops[i].stationName) == 0) {
                        // 继续检查终点站
                        for (int j = i + 1; j < Rail_data.Rail_Data[count].allstationNumber; j++) {
                            if (strcmp(Order_data.Order_Data[Order_data.Length-1].destinationStation, Rail_data.Rail_Data[count].stops[j].stationName) == 0) {
                                // 打印符合条件的列车信息
                                printf("符合条件的车次：%s\n", Rail_data.Rail_Data[count].trainNumber);
                                printf("始发站时间：%s\n", Rail_data.Rail_Data[count].stops[i].arrivalTime);
                                printf("终点站时间：%s\n", Rail_data.Rail_Data[count].stops[j].departureTime);
                                printf("终点站距离：%d\n", Rail_data.Rail_Data[count].stops[j].distance - Rail_data.Rail_Data[count].stops[i].distance);
                                printf("\n");
                                break;  // 找到符合条件的列车后，跳出内层循环
                            }
                        }
                    }
                }
            }
            printf("请从以上列车选择车次：");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].trainNumber, sizeof(Order_data.Order_Data[Order_data.Length].trainNumber));
            for (int i = 0; i < Rail_data.Length-1; i++) {
                if (strcmp(Rail_data.Rail_Data[i].trainNumber, Order_data.Order_Data[Order_data.Length-1].trainNumber) == 0){
                    for (int j = 0; j < Rail_data.Rail_Data[i].allstationNumber; j++) {
                        // 检查是否符合用户输入的始发站
                        if (strcmp(Order_data.Order_Data[Order_data.Length-1].startingStation, Rail_data.Rail_Data[i].stops[j].stationName) == 0) {
                            // 继续检查终点站
                            for (int u = j + 1; u < Rail_data.Rail_Data[i].allstationNumber; u++) {
                                if (strcmp(Order_data.Order_Data[Order_data.Length-1].destinationStation, Rail_data.Rail_Data[i].stops[u].stationName) == 0) {
                                    // 打印符合条件的列车信息
                                    printf("您购买的车次：%s将于%4d年%2d月%2d日发车\n", Rail_data.Rail_Data[i].trainNumber,year,month,day);
                                    printf("始发站时间：%s\n", Rail_data.Rail_Data[i].stops[j].arrivalTime);
                                    strcpy_s(Order_data.Order_Data[Order_data.Length-1].departureTime, sizeof(Order_data.Order_Data[Order_data.Length].departureTime), Rail_data.Rail_Data[i].stops[j].arrivalTime);
                                    printf("终点站时间：%s\n", Rail_data.Rail_Data[i].stops[u].departureTime);
                                    strcpy_s(Order_data.Order_Data[Order_data.Length-1].arriveTime, sizeof(Order_data.Order_Data[Order_data.Length].arriveTime), Rail_data.Rail_Data[i].stops[u].departureTime);
                                    printf("终点站距离：%d\n", Rail_data.Rail_Data[i].stops[u].distance - Rail_data.Rail_Data[i].stops[j].distance);
                                    distance = Rail_data.Rail_Data[i].stops[u].distance - Rail_data.Rail_Data[i].stops[j].distance;                                    
                                    if (strcmp(Order_data.Order_Data[Order_data.Length-1].seatClass, "特等座") == 0) {
                                        Order_data.Order_Data[Order_data.Length].ticketPrice = (double)distance * 1.2;
                                        printf("票价：%.2f\n", Order_data.Order_Data[Order_data.Length-1].ticketPrice);
                                    }
                                    else if (strcmp(Order_data.Order_Data[Order_data.Length-1].seatClass, "一等座") == 0) {
                                        Order_data.Order_Data[Order_data.Length-1].ticketPrice = (double)distance * 0.6;

                                        printf("票价：%.2f\n", Order_data.Order_Data[Order_data.Length-1].ticketPrice);
                                    }
                                    else if (strcmp(Order_data.Order_Data[Order_data.Length-1].seatClass, "二等座") == 0) {
                                        Order_data.Order_Data[Order_data.Length-1].ticketPrice = (double)distance * 0.46;
                                        printf("第%d\n", Order_data.Length-1);
                                        printf("票价：%.2f\n", Order_data.Order_Data[Order_data.Length-1].ticketPrice);
                                    }
                                    printf("票价：%.2f\n", Order_data.Order_Data[Order_data.Length - 1].ticketPrice);
                                     strcpy_s(Order_data.Order_Data[Order_data.Length-1].orderNumber, sizeof(Order_data.Order_Data[Order_data.Length-1].orderNumber), "20240107-0069-001");
                                     strcpy_s(Order_data.Order_Data[Order_data.Length-1].seatNumber, sizeof(Order_data.Order_Data[Order_data.Length - 1].seatNumber), "1");
                                     return Order_data;
                                }
                            }
                        }
                    }

                }
            }
            
            
        }
    }    
    return old_Order_data;
}
//打印当前所有车次
void printAllTrains(Data_List Rail_data, int state){
    printf("当前共有%d个车次信息\n", Rail_data.Length);
    printf("车次    出发站   终点站   总距离   运行情况  发车时间  到达时间\n");
    for (int i = 0; i < Rail_data.Length; i++) {
        printf("%3s  %8s  %8s  %6d  %8s  %8s  %8s\n",
            Rail_data.Rail_Data[i].trainNumber,
            Rail_data.Rail_Data[i].startingStation,
            Rail_data.Rail_Data[i].destinationStation,
            Rail_data.Rail_Data[i].alldistance,
            Rail_data.Rail_Data[i].isServiceAvailable,
            Rail_data.Rail_Data[i].departureTime,
            Rail_data.Rail_Data[i].arriveTime);
               //Rail_data.Rail_Data[i].allstationNumber,
               //Rail_data.Rail_Data[i].principalSeat,
               //Rail_data.Rail_Data[i].firSeat,
               //Rail_data.Rail_Data[i].secSeat); %d %d %d %d
        if (state)
        {
            for (int j = 0; j < Rail_data.Rail_Data[i].allstationNumber; j++) {
                printf("%s %s %s %d ",
                    Rail_data.Rail_Data[i].stops[j].stationName,
                    Rail_data.Rail_Data[i].stops[j].arrivalTime,
                    Rail_data.Rail_Data[i].stops[j].departureTime,
                    Rail_data.Rail_Data[i].stops[j].distance
                );
            }
        }
           
           printf("\n");
    }
}
// 输出一个列车上所有乘客的信息
void printAllPassengers(Data_Passenger_List Passenger_data) {
    printf("证件号              乘客姓名       证件类别     联系电话      紧急联系人   紧急联系人电话\n");
    for (int i = 0; i < Passenger_data.Length; i++) {
        printf("%-20s    %-6s    %-6s    %-12s    %-10s    %-12s\n",
            Passenger_data.Passenger_Data[i].idNumber,
            Passenger_data.Passenger_Data[i].passengerName,
            Passenger_data.Passenger_Data[i].idType,
            Passenger_data.Passenger_Data[i].phoneNumber,
            Passenger_data.Passenger_Data[i].emergencyContact,
            Passenger_data.Passenger_Data[i].emergencyContactPhone
            );
    }
    return;
}
//打印所有车票信息
void printAllOrders(Data_Order_List Order_data) {
    printf("所有订单信息如下：\n");
    printf("     订单号       乘车日期    车次     始发站       终到站     证件类别     证件号        乘客姓名  开车时间  到达时间 座位等级 座位号   票价\n");

    for (int i = 0; i < Order_data.Length; i++) {
        printf("%-15s %-8s    %-8s %-12s %-12s %-6s %-18s %-10s %-8s %-8s %-10s %-3s %-8.2f\n",
            Order_data.Order_Data[i].orderNumber,
            Order_data.Order_Data[i].travelDate,
            Order_data.Order_Data[i].trainNumber,
            Order_data.Order_Data[i].startingStation,
            Order_data.Order_Data[i].destinationStation,
            Order_data.Order_Data[i].idType,
            Order_data.Order_Data[i].idNumber,
            Order_data.Order_Data[i].passengerName,
            Order_data.Order_Data[i].departureTime,
            Order_data.Order_Data[i].arriveTime,
            Order_data.Order_Data[i].seatClass,
            Order_data.Order_Data[i].seatNumber,
            Order_data.Order_Data[i].ticketPrice
        );
    }
}
//停开列车
Data_List stopTrain(Data_List Rail_data) {
    // 假设用户输入要停运的列车的车次
    char trainToStop[20];
    printf("请输入要停运的列车的车次： ");
    scanf_s("%s", trainToStop, sizeof(trainToStop));
    // 遍历列车数组查找要停运的列车
    for (int i = 0; i < Rail_data.Length; i++) {
        if (strcmp(Rail_data.Rail_Data[i].trainNumber, trainToStop) == 0) {
            // 找到匹配的列车，将其运行情况标记为停运
            strcpy_s(Rail_data.Rail_Data[i].isServiceAvailable, sizeof(Rail_data.Rail_Data[i].isServiceAvailable),"停运");
            printf("列车 %s 已停运。\n", Rail_data.Rail_Data[i].trainNumber);
            return  Rail_data; // 停运列车后直接返回
        }
    }
    // 若未找到匹配的列车
    printf("未找到车次为 %s 的列车。\n", trainToStop);
}
// 删除一个乘客
Data_Passenger_List deletePassenger(Data_Passenger_List Passenger_data) {
    char idNumberToDelete[20];
    int found = 0;

    printf("请输入要删除的乘客证件号： ");
    scanf_s("%s", idNumberToDelete, sizeof(idNumberToDelete));

    for (int i = 0; i < Passenger_data.Length; i++) {
        if (strcmp(Passenger_data.Passenger_Data[i].idNumber, idNumberToDelete) == 0) {
            found = 1;

            printf("\n删除乘客信息：\n");
            printf("证件号              乘客姓名       证件类别     联系电话      紧急联系人   紧急联系人电话\n");
            printf("%-20s %-8s %-6s %-12s %-10s %-12s\n",
                Passenger_data.Passenger_Data[i].idNumber,
                Passenger_data.Passenger_Data[i].passengerName,
                Passenger_data.Passenger_Data[i].idType,
                Passenger_data.Passenger_Data[i].phoneNumber,
                Passenger_data.Passenger_Data[i].emergencyContact,
                Passenger_data.Passenger_Data[i].emergencyContactPhone);

            // 将删除的乘客信息用后面的乘客信息覆盖
            for (int j = i; j < Passenger_data.Length - 1; j++) {
                Passenger_data.Passenger_Data[j] = Passenger_data.Passenger_Data[j + 1];
            }

            // 减少乘客数目
            Passenger_data.Length--;

            printf("乘客信息删除成功！\n");

            break; // 找到匹配的乘客后结束循环
        }
    }

    if (!found) {
        printf("未找到证件号为 %s 的乘客信息。\n", idNumberToDelete);
    }

    return Passenger_data;
}
//退票
Data_Order_List deleteOrder(Data_Order_List Order_data) {
    char idNumberToDelete[20];
    int found = 0;

    printf("请输入要退票的证件号： ");
    scanf_s("%s", idNumberToDelete, sizeof(idNumberToDelete));

    for (int i = 0; i < Order_data.Length; i++) {
        if (strcmp(Order_data.Order_Data[i].idNumber, idNumberToDelete) == 0) {
            found = 1;

            printf("\n订单信息：\n");
            printf("     订单号       乘车日期    车次     始发站       终到站     证件类别     证件号        乘客姓名  开车时间  到达时间 座位等级 座位号   票价\n");
            printf("%-15s %-8s    %-8s %-12s %-12s %-6s %-18s %-10s %-8s %-8s %-10s %-3s %-8.2f\n",
                Order_data.Order_Data[i].orderNumber,
                Order_data.Order_Data[i].travelDate,
                Order_data.Order_Data[i].trainNumber,
                Order_data.Order_Data[i].startingStation,
                Order_data.Order_Data[i].destinationStation,
                Order_data.Order_Data[i].idType,
                Order_data.Order_Data[i].idNumber,
                Order_data.Order_Data[i].passengerName,
                Order_data.Order_Data[i].departureTime,
                Order_data.Order_Data[i].arriveTime,
                Order_data.Order_Data[i].seatClass,
                Order_data.Order_Data[i].seatNumber,
                Order_data.Order_Data[i].ticketPrice
            );
            // 将删除的乘客信息用后面的乘客信息覆盖
            for (int j = i; j < Order_data.Length - 1; j++) {
                Order_data.Order_Data[j] = Order_data.Order_Data[j + 1];
            }

            // 减少乘客数目
            Order_data.Length--;

            printf("退票成功！\n");

            break; // 找到匹配的乘客后结束循环
        }
    }

    if (!found) {
        printf("未找到证件号为 %s 的乘客信息。\n", idNumberToDelete);
    }
    return Order_data;
}
// 高铁车次信息查询
void searchTrain(Data_List Rail_data) {
    // 用户选择查询条件
    int option;char trainToSearch[20];
    printf("欢迎进入列车查询系统：\n");
    printf("1. 车次\n");
    printf("2. 起点站\n");
    printf("3. 终到站\n");
    printf("4. 停靠站\n");
    printf("5. 发车时间\n");
    printf("请选择查询条件：");
    scanf_s("%d", &option);

    // 根据用户选择进行查询
    switch (option) {
    // 车次查询
    case 1: { 
        // 用户输入要查询的车次
        printf("请输入要查询的车次： ");
        scanf_s("%s", trainToSearch, sizeof(trainToSearch));
        // 遍历列车数组查找匹配的列车
        for (int i = 0; i < Rail_data.Length; i++) {
            if (strcmp(Rail_data.Rail_Data[i].trainNumber, trainToSearch) == 0) {
                // 输出匹配的列车信息
                // 可以根据实际需求输出其他信息
                printf("车次 %s 的信息：\n", Rail_data.Rail_Data[i].trainNumber);
                printf("起点站：%s\n", Rail_data.Rail_Data[i].startingStation);
                printf("终到站：%s\n", Rail_data.Rail_Data[i].destinationStation);
                printf("发车时间：%s\n", Rail_data.Rail_Data[i].departureTime);
                printf("到达时间：%s\n", Rail_data.Rail_Data[i].arriveTime);
                // 输出停靠站信息...
                printf("停靠站信息：\n");
                for (int j = 0; j < Rail_data.Rail_Data[i].allstationNumber; j++) {
                    printf("%s %s %s %d\n",
                        Rail_data.Rail_Data[i].stops[j].stationName,
                        Rail_data.Rail_Data[i].stops[j].arrivalTime,
                        Rail_data.Rail_Data[i].stops[j].departureTime,
                        Rail_data.Rail_Data[i].stops[j].distance
                    );
                }
                return;
            }
        }

        // 若未找到匹配的列车
        printf("未找到车次为 %s 的列车。\n", trainToSearch);
        break;
    }
    
    case 2: {
        // 用户输入
        printf("请输入要查询的起点站： ");
        scanf_s("%s", trainToSearch, sizeof(trainToSearch));
        // 遍历列车数组查找匹配的列车
        for (int i = 0; i < Rail_data.Length; i++) {
            if (strcmp(Rail_data.Rail_Data[i].startingStation, trainToSearch) == 0) {
                // 输出匹配的列车信息
                // 可以根据实际需求输出其他信息
                printf("车次 %s 的信息：\n", Rail_data.Rail_Data[i].trainNumber);
                printf("起点站：%s\n", Rail_data.Rail_Data[i].startingStation);
                printf("终到站：%s\n", Rail_data.Rail_Data[i].destinationStation);
                printf("发车时间：%s\n", Rail_data.Rail_Data[i].departureTime);
                printf("到达时间：%s\n", Rail_data.Rail_Data[i].arriveTime);
                // 输出停靠站信息...
                printf("停靠站信息：\n");
                for (int j = 0; j < Rail_data.Rail_Data[i].allstationNumber; j++) {
                    printf("%s %s %s %d\n",
                        Rail_data.Rail_Data[i].stops[j].stationName,
                        Rail_data.Rail_Data[i].stops[j].arrivalTime,
                        Rail_data.Rail_Data[i].stops[j].departureTime,
                        Rail_data.Rail_Data[i].stops[j].distance
                    );
                }
                return;
            }
        }

    }

    case 3: {
        // 用户输入
        printf("请输入要查询的终点站： ");
        scanf_s("%s", trainToSearch, sizeof(trainToSearch));
        // 遍历列车数组查找匹配的列车
        for (int i = 0; i < Rail_data.Length; i++) {
            if (strcmp(Rail_data.Rail_Data[i].destinationStation, trainToSearch) == 0) {
                // 输出匹配的列车信息
                // 可以根据实际需求输出其他信息
                printf("车次 %s 的信息：\n", Rail_data.Rail_Data[i].trainNumber);
                printf("起点站：%s\n", Rail_data.Rail_Data[i].startingStation);
                printf("终到站：%s\n", Rail_data.Rail_Data[i].destinationStation);
                printf("发车时间：%s\n", Rail_data.Rail_Data[i].departureTime);
                printf("到达时间：%s\n", Rail_data.Rail_Data[i].arriveTime);
                // 输出停靠站信息...
                printf("停靠站信息：\n");
                for (int j = 0; j < Rail_data.Rail_Data[i].allstationNumber; j++) {
                    printf("%s %s %s %d\n",
                        Rail_data.Rail_Data[i].stops[j].stationName,
                        Rail_data.Rail_Data[i].stops[j].arrivalTime,
                        Rail_data.Rail_Data[i].stops[j].departureTime,
                        Rail_data.Rail_Data[i].stops[j].distance
                    );
                }
            }
        }
        break;
    }

    case 4: {
        // 用户输入
        printf("请输入要查询的停靠站： ");
        scanf_s("%s", trainToSearch, sizeof(trainToSearch));
        // 遍历列车数组查找匹配的列车
        for (int i = 0; i < Rail_data.Length; i++) {
            for (int j = 0; j < Rail_data.Rail_Data[i].allstationNumber; j++) {
                if (strcmp(Rail_data.Rail_Data[i].stops[j].stationName, trainToSearch) == 0) {
                    // 输出匹配的列车信息
                    // 可以根据实际需求输出其他信息
                    printf("车次 %s 的信息：\n", Rail_data.Rail_Data[i].trainNumber);
                    printf("起点站：%s\n", Rail_data.Rail_Data[i].startingStation);
                    printf("终到站：%s\n", Rail_data.Rail_Data[i].destinationStation);
                    printf("发车时间：%s\n", Rail_data.Rail_Data[i].departureTime);
                    printf("到达时间：%s\n", Rail_data.Rail_Data[i].arriveTime);
                    // 输出停靠站信息...
                    printf("停靠站信息：\n");
                    for (int j = 0; j < Rail_data.Rail_Data[i].allstationNumber; j++) {
                        printf("%s %s %s %d\n",
                            Rail_data.Rail_Data[i].stops[j].stationName,
                            Rail_data.Rail_Data[i].stops[j].arrivalTime,
                            Rail_data.Rail_Data[i].stops[j].departureTime,
                            Rail_data.Rail_Data[i].stops[j].distance
                        );
                    }
                }
            }
            
        }
        break;
    }

    case 5: {
        // 用户输入
        printf("请输入要查询的出发时间： ");
        scanf_s("%s", trainToSearch, sizeof(trainToSearch));
        // 遍历列车数组查找匹配的列车
        for (int i = 0; i < Rail_data.Length; i++) {
            if (strcmp(Rail_data.Rail_Data[i].departureTime, trainToSearch) == 0) {
                // 输出匹配的列车信息
                // 可以根据实际需求输出其他信息
                printf("车次 %s 的信息：\n", Rail_data.Rail_Data[i].trainNumber);
                printf("起点站：%s\n", Rail_data.Rail_Data[i].startingStation);
                printf("终到站：%s\n", Rail_data.Rail_Data[i].destinationStation);
                printf("发车时间：%s\n", Rail_data.Rail_Data[i].departureTime);
                printf("到达时间：%s\n", Rail_data.Rail_Data[i].arriveTime);
                // 输出停靠站信息...
                printf("停靠站信息：\n");
                for (int j = 0; j < Rail_data.Rail_Data[i].allstationNumber; j++) {
                    printf("%s %s %s %d\n",
                        Rail_data.Rail_Data[i].stops[j].stationName,
                        Rail_data.Rail_Data[i].stops[j].arrivalTime,
                        Rail_data.Rail_Data[i].stops[j].departureTime,
                        Rail_data.Rail_Data[i].stops[j].distance
                    );
                }
                
            }
        }
        break;
    }
    default:
    {        printf("无效的选择。\n");
            break; 
    }

    }
    return;
}
// 乘客信息查询
void searchPassenger(Data_Passenger_List Passenger_data) {
    char searchKey[50];
    int found = 0;

    printf("请输入查询关键字（姓名、证件号、手机号、紧急联系人等）： ");
    scanf_s("%s", searchKey, sizeof(searchKey));

    printf("\n查询结果：\n");
    printf("证件号              乘客姓名       证件类别     联系电话      紧急联系人   紧急联系人电话\n");

    for (int i = 0; i < Passenger_data.Length; i++) {
        // 在每个字段中查找关键字
        if (strstr(Passenger_data.Passenger_Data[i].passengerName, searchKey) ||
            strstr(Passenger_data.Passenger_Data[i].idNumber, searchKey) ||
            strstr(Passenger_data.Passenger_Data[i].phoneNumber, searchKey) ||
            strstr(Passenger_data.Passenger_Data[i].emergencyContact, searchKey) ||
            strstr(Passenger_data.Passenger_Data[i].emergencyContactPhone, searchKey)) {

            printf("%-20s    %-6s    %-6s    %-12s    %-10s    %-12s\n",
                   Passenger_data.Passenger_Data[i].idNumber,
                   Passenger_data.Passenger_Data[i].passengerName,
                   Passenger_data.Passenger_Data[i].idType,
                   Passenger_data.Passenger_Data[i].phoneNumber,
                   Passenger_data.Passenger_Data[i].emergencyContact,
                   Passenger_data.Passenger_Data[i].emergencyContactPhone
                  );
            found = 1;
        }
    }

    if (!found) {
        printf("未找到匹配的乘客信息。\n");
    }
}
//打印一个订单
void Order_data_print(Data_Order_List Order_data, int i) {

    printf("订单号：%s\n", Order_data.Order_Data[i].orderNumber);
    printf("乘车日期：%s\n", Order_data.Order_Data[i].travelDate);
    printf("车次：%s\n", Order_data.Order_Data[i].trainNumber);
    printf("始发站：%s\n", Order_data.Order_Data[i].startingStation);
    printf("终到站：%s\n", Order_data.Order_Data[i].destinationStation);
    printf("证件类别：%s\n", Order_data.Order_Data[i].idType);
    printf("证件号：%s\n", Order_data.Order_Data[i].idNumber);
    printf("乘客姓名：%s\n", Order_data.Order_Data[i].passengerName);
    printf("开车时间：%s\n", Order_data.Order_Data[i].departureTime);
    printf("到达时间：%s\n", Order_data.Order_Data[i].arriveTime);
    printf("座位等级：%s\n", Order_data.Order_Data[i].seatClass);
    printf("座位号：%s\n", Order_data.Order_Data[i].seatNumber);
    printf("票价：%.2f\n", Order_data.Order_Data[i].ticketPrice);
}
void printOrderInfo_num(Data_Order_List Order_data) {
    int i=0;
    printf("当前共有%d个订单", Order_data.Length-1);
    printf("请输入订单：");
    scanf_s("%d", &i);
    Order_data_print(Order_data, i);
}
//订单信息查询
void searchOrder(Data_Order_List Order_data) {
    int option;
    char key[20];

    printf("欢迎进入订单查询系统：\n");
    printf("1. 订单号\n");
    printf("2. 乘车日期\n");
    printf("3. 车次\n");
    printf("4. 始发站\n");
    printf("5. 终到站\n");
    printf("6. 证件号\n");
    printf("7. 乘客姓名\n");
    printf("请选择查询条件：");
    scanf_s("%d", &option);

    // 根据用户选择进行查询
    switch (option) {
    case 1:
        printf("请输入要查询的订单号： ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 2:
        printf("请输入要查询的乘车日期： ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 3:
        printf("请输入要查询的车次： ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 4:
        printf("请输入要查询的始发站： ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 5:
        printf("请输入要查询的终到站： ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 6:
        printf("请输入要查询的证件号： ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 7:
        printf("请输入要查询的乘客姓名： ");
        scanf_s("%s", key, sizeof(key));
        break;
    default:
        printf("无效的选择。\n");



    }
    // 遍历订单数据进行查询
    for (int i = 0; i < Order_data.Length; i++) {
        switch (option) {
        case 1:
            if (strcmp(Order_data.Order_Data[i].orderNumber, key) == 0) {
                Order_data_print(Order_data, i);
                
            }
            break;
        case 2:
            if (strcmp(Order_data.Order_Data[i].travelDate, key) == 0) {
                Order_data_print(Order_data, i);
                
            }
            break;
        case 3:
            if (strcmp(Order_data.Order_Data[i].trainNumber, key) == 0) {
                Order_data_print(Order_data, i);
                
            }
            break;
        case 4:
            if (strcmp(Order_data.Order_Data[i].startingStation, key) == 0) {
                Order_data_print(Order_data, i);
                
            }
            break;
        case 5:
            if (strcmp(Order_data.Order_Data[i].destinationStation, key) == 0) {
                Order_data_print(Order_data, i);
                
            }
            break;
        case 6:
            if (strcmp(Order_data.Order_Data[i].idNumber, key) == 0) {
                Order_data_print(Order_data, i);
                
            }
            break;
        case 7:
            if (strcmp(Order_data.Order_Data[i].passengerName, key) == 0) {
                Order_data_print(Order_data, i);
                
            }
            break;
        }
    }
}
//余票查询
void checkRemainingSeats(Data_Order_List Order_data, Data_List Rail_data) {
    // 获取用户输入的车次和座位等级
    char trainNumber[20];
    char seatClass[20];
    int   remainingSeats = 0;
    printf("请输入车次：");
    scanf_s("%s", trainNumber, sizeof(trainNumber));
    printf("请输入座位等级（特等座、一等座、二等座）：");
    scanf_s("%s", seatClass, sizeof(seatClass));

    // 遍历订单数据，找到符合条件的订单信息
    for (int i = 0; i < Rail_data.Length; i++) {
        if (strcmp(Rail_data.Rail_Data[i].trainNumber, trainNumber) == 0) {
            // 找到符合条件的车次信息

            // 计算余票数
            if (strcmp(seatClass, "特等座") == 0) {
                remainingSeats = Rail_data.Rail_Data[i].principalSeat;
            }
            else if (strcmp(seatClass, "一等座") == 0) {
                remainingSeats = Rail_data.Rail_Data[i].firSeat;
            }
            else if (strcmp(seatClass, "二等座") == 0) {
                remainingSeats = Rail_data.Rail_Data[i].secSeat;
            }
            // 输出余票信息
            printf("车次：%s，座位等级：%s余票：%d\n", trainNumber, seatClass,remainingSeats);
            return;  // 查询完成，结束函数
        }
    }

    // 没有找到符合条件的订单信息
    printf("未找到符合条件的订单信息。\n");
}
// 修改高铁车次信息
Data_List modifyTrain(Data_List Rail_data) {
    // 用户输入要修改的车次
    char trainToModify[20];
    printf("请输入要修改信息的车次： ");
    scanf_s("%s", trainToModify, sizeof(trainToModify));

    // 遍历列车数组查找要修改的列车
    for (int i = 0; i < Rail_data.Length; i++) {
        if (strcmp(Rail_data.Rail_Data[i].trainNumber, trainToModify) == 0) {
            // 输出当前列车信息
            printf("当前 %s 列车的信息：\n", Rail_data.Rail_Data[i].trainNumber);
            printf("起点站：%s\n", Rail_data.Rail_Data[i].startingStation);
            printf("终到站：%s\n", Rail_data.Rail_Data[i].destinationStation);
            printf("发车时间：%s\n", Rail_data.Rail_Data[i].departureTime);
            // 输出其他信息...

            // 用户选择要修改的信息
            int option;
            
            printf("1. 起点站\n");
            printf("2. 终到站\n");
            printf("3. 发车时间\n");
            // 添加其他可修改信息的选项...
            printf("请选择要修改的信息：");
            scanf_s("%d", &option);

            // 根据用户选择进行修改
            switch (option) {
            case 1: // 修改起点站
                printf("请输入新的起点站： ");
                scanf_s("%s", Rail_data.Rail_Data[i].startingStation, sizeof(Rail_data.Rail_Data[i].startingStation));
                break;

            case 2: // 修改终到站
                printf("请输入新的终到站： ");
                scanf_s("%s", Rail_data.Rail_Data[i].destinationStation, sizeof(Rail_data.Rail_Data[i].destinationStation));
                break;

            case 3: // 修改发车时间
                printf("请输入新的发车时间： ");
                scanf_s("%s", Rail_data.Rail_Data[i].departureTime, sizeof(Rail_data.Rail_Data[i].departureTime));
                break;
            default:
                printf("无效的选择。\n");
                break;
            }
            return Rail_data;
        }
    }

    // 若未找到匹配的列车
    printf("未找到车次为 %s 的列车。\n", trainToModify);
}
// 乘客信息修改
Data_Passenger_List modifyPassenger(Data_Passenger_List Passenger_data) {
    char idNumberToModify[20];
    int found = 0;

    printf("请输入要修改信息的乘客证件号： ");
    scanf_s("%s", idNumberToModify, sizeof(idNumberToModify));

    for (int i = 0; i < Passenger_data.Length; i++) {
        if (strcmp(Passenger_data.Passenger_Data[i].idNumber, idNumberToModify) == 0) {
            found = 1;
            printf("\n乘客原信息：\n");
            printf("证件号              乘客姓名       证件类别     联系电话      紧急联系人   紧急联系人电话\n");
            printf("%-20s %-8s %-6s %-12s %-10s %-12s\n",
                Passenger_data.Passenger_Data[i].idNumber,
                Passenger_data.Passenger_Data[i].passengerName,
                Passenger_data.Passenger_Data[i].idType,
                Passenger_data.Passenger_Data[i].phoneNumber,
                Passenger_data.Passenger_Data[i].emergencyContact,
                Passenger_data.Passenger_Data[i].emergencyContactPhone);
            // 修改手机号
            printf("请输入新的联系电话： ");
            scanf_s("%s", Passenger_data.Passenger_Data[i].phoneNumber, sizeof(Passenger_data.Passenger_Data[i].phoneNumber));

            // 修改紧急联系人
            printf("请输入新的紧急联系人： ");
            scanf_s("%s", Passenger_data.Passenger_Data[i].emergencyContact, sizeof(Passenger_data.Passenger_Data[i].emergencyContact));

            // 修改紧急联系人电话
            printf("请输入新的紧急联系人电话： ");
            scanf_s("%s", Passenger_data.Passenger_Data[i].emergencyContactPhone, sizeof(Passenger_data.Passenger_Data[i].emergencyContactPhone));

            printf("乘客信息修改成功！\n");
            break; // 找到匹配的乘客后结束循环
        }
    }

    if (!found) {
        printf("未找到证件号为 %s 的乘客信息。\n", idNumberToModify);
    }

    return Passenger_data;
}
// 生成指定范围内的随机整数
int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}
//订票菜单函数
void OrdershowMenu() {
    printf("\n========高铁订票信息管理系统========\n");
    printf("1. 打印全部订单信息\n");
    printf("2. 打印某一个订单信息\n");
    printf("3. 余票查询\n");
    printf("4. 定票\n");
    printf("5. 退票\n");
    printf("0. 退出\n");
}
//列车菜单函数
void RailshowMenu() {
    printf("\n========高铁信息管理系统========\n");
    printf("1. 所有高铁信息\n");
    printf("2. 增开一趟列车\n");
    printf("3. 停开一趟列车\n");
    printf("4. 高铁车次信息查询\n");
    printf("5. 修改高铁车次信息\n");
    printf("0. 退出\n");
}
//乘客菜单函数
void PassengershowMenu() {
    //    // 用户菜单
         printf("\n========乘客信息管理系统========\n");
         printf("1. 增加一个乘客\n");
         printf("2. 所有乘客信息\n");
         printf("3. 乘客信息查询\n");
         printf("4. 修改乘客信息\n");
         printf("5. 删除乘客信息\n");
         printf("0. 退出\n");
}
//列车系统交互函数
void RailSYSTEM(Data_List Rail_data) {
    int choice;
    do {
        RailshowMenu();
        printf("请选择操作： ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printAllTrains(Rail_data, 1); // 输出所有高铁信息，包含运行情况
            break;

        case 2:
            Rail_data = addTrain(Rail_data); // 增开一趟列车
            break;

        case 3:
            Rail_data = stopTrain(Rail_data); // 停开一趟列车
            break;

        case 4:
            searchTrain(Rail_data); // 高铁车次信息查询
            break;

        case 5:
            Rail_data = modifyTrain(Rail_data); // 修改高铁车次信息
            break;

        case 0:
            printf("感谢使用，再见！\n");
            break;

        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }

    } while (choice != 0);// 交互式高铁信息管理系统

}
//乘客系统交互函数
void PassengerSYSTEM(Data_Passenger_List  Passenger_data) {
    int choice;

    do {
        PassengershowMenu();
        printf("请选择操作： ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            Passenger_data = addPassenger(Passenger_data);
            break;
        case 2:
            printAllPassengers(Passenger_data);
            break;
        case 3:
            searchPassenger(Passenger_data);
            break;
        case 4:
            Passenger_data = modifyPassenger(Passenger_data);
            break;
        case 5:
            Passenger_data = deletePassenger(Passenger_data);
            break;
        case 0:
            printf("感谢使用乘客信息管理系统！\n");
            break;
        default:
            printf("无效的选择，请重新输入。\n");
        }

    } while (choice != 0);// 交互式乘客信息管理系统

}
//订票系统交互函数
void OrderSYSTEM(Data_Order_List Order_data, Data_List Rail_data) {
    int choice;
    do {
        OrdershowMenu();
        printf("请选择操作： ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printAllOrders(Order_data);
            break;
        case 2:
            printOrderInfo_num(Order_data);
            break;
        case 3:
            checkRemainingSeats(Order_data, Rail_data);
            break;
        case 4:
            Order_data = reserveTicket(Order_data, Rail_data);
            break;
        case 5:
            Order_data = deleteOrder(Order_data);
            break;
        case 0:
            printf("感谢使用高铁订票信息管理系统！\n");
            break;
        default:
            printf("无效的选择，请重新输入。\n");
        }

    } while (choice != 0);


}
//总菜单函数
void ALLshowMenu() {
    printf("\n========高铁订票系统========\n");
    printf("1. 乘客信息管理系统\n");
    printf("2. 高铁信息管理系统\n");
    printf("3. 高铁订票信息管理系统\n");
    printf("0. 退出\n");
}
//
#endif // !_Rail_System_













