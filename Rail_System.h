#ifndef  _Rail_System_
#define  _Rail_System_
#define _CRT_SECURE_NO_WARNINGS
#define MaxSize        100//�洢��󳤶�
//״̬����
#define   TRUE           1
#define   FALSE          0
#define   OK             1
#define   ERROR          0
#define   INFEASIBLE    -1
#define   OVERFLOW      -2

int      allraildataNum = 0;


typedef struct {
	char  trainNumber[20];         // ����
	char  startingStation[50];     // ʼ��վ
	char  destinationStation[50];  // �յ�վ
	int   alldistance;         // ����̣���λ���
	char  isServiceAvailable[50];  // ����������Ƿ�ͣ�ˣ�
	char  departureTime[10];   // ����ʱ��
	char  arriveTime[10];      // �ﵽʱ��
	int   allstationNumber;         //ͣ��վ��
	int   principalSeat; //�ص���
	int   firSeat; //1����
	int   secSeat; //2����
	// ͣ����վ����Ϣ
	struct {
		char stationName[50];  // ��վ��
		char arrivalTime[10];   // ��վʱ��
		char departureTime[10]; // ��վʱ��
		int distance;         // ��̣���λ���
	       }stops[20];  // ���洢10��ͣ����վ����Ϣ
}Data_Type; //�г��������Ͷ���
typedef struct {
    char passengerName[50];
    char idType[20];  // ֤�����
    char idNumber[20];  // ֤����
    char phoneNumber[20];//��ϵ�绰
    char emergencyContact[50];  // ������ϵ��
    char emergencyContactPhone[20];// ������ϵ����ϵ�绰
} Passenger;//�˿��������Ͷ���
typedef struct {
    char orderNumber[20]; // ������
    char travelDate[20]; // �˳�����
    char trainNumber[20]; // ����
    char startingStation[50]; // ʼ��վ
    char destinationStation[50]; // �յ�վ
    char idType[20]; // ֤�����
    char idNumber[20]; // ֤����
    char passengerName[50]; // �˿�����
    char departureTime[10]; // ����ʱ��
    char arriveTime[10]; // ����ʱ��
    char seatClass[20]; // ��λ�ȼ� �ص���	һ����	������
    char seatNumber[10]; // ��λ��
    float ticketPrice; // Ʊ��
} Order; // �����������Ͷ���




typedef struct {
	Data_Type  *Rail_Data;  //�洢�ռ����ַ
	int         Length; //��ǰ��
}Data_List; //�����г����Ա���������
typedef struct {
    Passenger  * Passenger_Data;  //�洢�ռ����ַ
    int         Length; //��ǰ��
}Data_Passenger_List; //�����г����Ա���������
typedef struct {
    Order *Order_Data; // �洢�ռ����ַ
    int Length; // ��ǰ��
} Data_Order_List; // ���嶩�����Ա���������




//��ʼ�����Ա�
int Init_List(Data_List* list)
{//��ʼ��˳���
	list->Rail_Data = (Data_Type*)malloc(sizeof(Data_Type) * MaxSize);//Ϊ˳���ڴ����
	if (!list->Rail_Data)
	{
		return  OVERFLOW;             //����ʧ��
	}
	list->Length = 0;                                            //��ʼ����
	return OK;                                                   //��ʼ���ɹ�
}
//���ػ����ݴ�TXT
Data_List Open_Rail_data(Data_List Rail_data) {
    int count = 0;
    FILE* file;
    char line[1024];
    int result = 0;
    long int read_rail_data_index = 0, index_num = 0;
    errno_t err = fopen_s(&file, "C:\\Rail_system\\Rail_System\\train.txt", "r");
    if (err == 0) {

        printf("�г����ݼ��سɹ�\n");
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
            //ͣ��վ����
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
//���س˿����ݴ�TXT
Data_Passenger_List Open_Passenger_data(Data_Passenger_List Passenger_data) {
    int count = 0;
    FILE* file;
    char line[1024];
    int result = 0;
    long int read_rail_data_index = 0, index_num = 0;
    errno_t err = fopen_s(&file, "C:\\Rail_system\\Rail_System\\passenger.txt", "r");
    if (err == 0) {

        printf("�˿����ݼ��سɹ�\n");
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
//���ض������ݴ�TXT
Data_Order_List Open_Order_data(Data_Order_List Order_data) {
    int count = 0;
    FILE* file;
    char line[1024];
    int result = 0;
    long int read_order_data_index = 0, index_num = 0;
    errno_t err = fopen_s(&file, "C:\\Rail_system\\Rail_System\\booking.txt", "r");
    if (err == 0) {
        printf("�������ݼ��سɹ�\n");
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
//�����г�
Data_List addTrain(Data_List Rail_data){
        // ��ȡ���г�����Ϣ
        printf("��ǰ����%d��������Ϣ\n", Rail_data.Length);
        printf("���������г�����Ϣ��\n");
        printf("���Σ�");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].trainNumber, sizeof(Rail_data.Rail_Data[Rail_data.Length].trainNumber));
        printf("ʼ��վ��");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].startingStation, sizeof(Rail_data.Rail_Data[Rail_data.Length].startingStation));
        printf("�յ�վ��");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].destinationStation, sizeof(Rail_data.Rail_Data[Rail_data.Length].destinationStation));
        printf("�����(��λ����)��");
        scanf_s("%d", &Rail_data.Rail_Data[Rail_data.Length].alldistance);
        printf("�������(�Ƿ�ͣ��)��");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].isServiceAvailable, sizeof(Rail_data.Rail_Data[Rail_data.Length].isServiceAvailable));
        printf("����ʱ�䣺");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].departureTime, sizeof(Rail_data.Rail_Data[Rail_data.Length].departureTime));
        printf("����ʱ�䣺");
        scanf_s("%s", Rail_data.Rail_Data[Rail_data.Length].arriveTime, sizeof(Rail_data.Rail_Data[Rail_data.Length].arriveTime));
        printf("ͣ��վ����");
        scanf_s("%d", &Rail_data.Rail_Data[Rail_data.Length].allstationNumber);
        printf("�ص���������");
        scanf_s("%d", &Rail_data.Rail_Data[Rail_data.Length].principalSeat);
        printf("һ����������");
        scanf_s("%d", &Rail_data.Rail_Data[Rail_data.Length].firSeat);
        printf("������������");
        scanf_s("%d", &Rail_data.Rail_Data[Rail_data.Length].secSeat);
        // ����ͣ��վ��Ϣ��Ŀ
        for (int i = 0; i < Rail_data.Rail_Data[Rail_data.Length].allstationNumber; i++) {
            printf("�������%dվ��Ϣ(վ�� ��վʱ�� ��վʱ�� ���)��",i+1);
            scanf_s("%s %s %s %d", Rail_data.Rail_Data[Rail_data.Length].stops[i].stationName,sizeof(Rail_data.Rail_Data[Rail_data.Length].stops[i].stationName),
                                   Rail_data.Rail_Data[Rail_data.Length].stops[i].arrivalTime, sizeof(Rail_data.Rail_Data[Rail_data.Length].stops[i].arrivalTime),
                                   Rail_data.Rail_Data[Rail_data.Length].stops[i].departureTime, sizeof(Rail_data.Rail_Data[Rail_data.Length].stops[i].departureTime),
                                   &Rail_data.Rail_Data[Rail_data.Length].stops[i].distance
                 );       
        }
        Rail_data.Length++;
        printf("�г���ӳɹ���\n");
        printf("��ǰ����%d��������Ϣ\n", Rail_data.Length);
        return Rail_data;
}
// ���һ���˿ͣ����룩
Data_Passenger_List addPassenger(Data_Passenger_List Passenger_data) {
        // ��ȡ�³˿͵���Ϣ
        printf("�������³˿͵���Ϣ��\n");
        printf("������");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].passengerName,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].passengerName));
        printf("֤�����");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].idType,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].idType));
        printf("֤���ţ�");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].idNumber,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].idNumber));
        printf("�ֻ��ţ�");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].phoneNumber,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].phoneNumber));
        printf("������ϵ�ˣ�");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].emergencyContact,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].emergencyContact));
        printf("������ϵ�˵绰��");
        scanf_s("%s", Passenger_data.Passenger_Data[Passenger_data.Length].emergencyContactPhone,
            sizeof(Passenger_data.Passenger_Data[Passenger_data.Length].emergencyContactPhone));

        printf("�˿���ӳɹ���\n");
        Passenger_data.Length++;
        return Passenger_data;
}
//��Ʊ�����룩
Data_Order_List reserveTicket(Data_Order_List Order_data, Data_List Rail_data) {
    Data_Order_List old_Order_data;
    old_Order_data = Order_data;
    Order_data.Length = Order_data.Length + 1;

    int distance = 0;
   // ��ȡϵͳ��ǰʱ��
    time_t currentTime;
    time(&currentTime);
    struct tm tmInfo;
    localtime_s(&tmInfo, &currentTime);
    // ʹ�� strftime ��ʽ�����
    char buffer[80];  // �㹻�������ɸ�ʽ������ַ���
    if (strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tmInfo) != 0) {
        printf("��ǰʱ�䣺%s���޶������������ڵĳ�Ʊ\n", buffer);
    }
    else {
        printf("���ڻ�ȡʧ�ܣ�\n");
    }


    // ��д�¶����������Ϣ
    printf("�����붩Ʊʱ�䣺\n");
    printf("�˳�����(��ʽ��20230101)��");
    scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].travelDate, sizeof(Order_data.Order_Data[Order_data.Length].orderNumber));
    Order_data.Order_Data[Order_data.Length].ticketPrice = 0.0;
    // ���������º��ʱ��
    struct tm twoMonthsLater;
    if (localtime_s(&twoMonthsLater, &currentTime) == 0) {
        twoMonthsLater.tm_mon += 2;
        time_t twoMonthsLaterTime = mktime(&twoMonthsLater);
        // ���û�����������ַ���ת��Ϊ�ṹ��
        int year, month, day;
        sscanf_s(Order_data.Order_Data[Order_data.Length-1].travelDate, "%4d%2d%2d", &year, &month, &day);
        // ����ṹ��
        struct tm inputDate = { 0 };
        inputDate.tm_year = year - 1900;  // ��ݼ�ȥ1900
        inputDate.tm_mon = month - 1;  // �·ݴ�0��ʼ
        inputDate.tm_mday = day;
        time_t inputDateTime = mktime(&inputDate);
        // ����Ƿ�����������
        if (difftime(inputDateTime, twoMonthsLaterTime) > 0) {
            printf("ֻ��Ԥ���������ڵĳ�Ʊ��Ԥ��ʧ�ܣ�\n");
            
        }
        else {
            printf("��������ض�Ʊ��Ϣ\n");
            printf("ʼ��վ��");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].startingStation, sizeof(Order_data.Order_Data[Order_data.Length].startingStation));
            printf("�յ�վ��");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].destinationStation, sizeof(Order_data.Order_Data[Order_data.Length].destinationStation));
            printf("֤�����(���֤ ����)��");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].idType, sizeof(Order_data.Order_Data[Order_data.Length].idType));
            printf("֤���ţ�");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].idNumber, sizeof(Order_data.Order_Data[Order_data.Length].idNumber));
            printf("�˿�������");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].passengerName, sizeof(Order_data.Order_Data[Order_data.Length].passengerName));
            printf("��λ�ȼ�(�ص���	һ����	������)��");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].seatClass, sizeof(Order_data.Order_Data[Order_data.Length].seatClass));
            for (int count = 0; count < Rail_data.Length; count++) {
                if (strcmp(Rail_data.Rail_Data[count].isServiceAvailable, "����") != 0) {
                    continue;  // ����г�״̬�����������������г�
                }
                // �������г���ͣ��վ��Ϣ
                for (int i = 0; i < Rail_data.Rail_Data[count].allstationNumber; i++) {
                    // ����Ƿ�����û������ʼ��վ
                    if (strcmp(Order_data.Order_Data[Order_data.Length-1].startingStation, Rail_data.Rail_Data[count].stops[i].stationName) == 0) {
                        // ��������յ�վ
                        for (int j = i + 1; j < Rail_data.Rail_Data[count].allstationNumber; j++) {
                            if (strcmp(Order_data.Order_Data[Order_data.Length-1].destinationStation, Rail_data.Rail_Data[count].stops[j].stationName) == 0) {
                                // ��ӡ�����������г���Ϣ
                                printf("���������ĳ��Σ�%s\n", Rail_data.Rail_Data[count].trainNumber);
                                printf("ʼ��վʱ�䣺%s\n", Rail_data.Rail_Data[count].stops[i].arrivalTime);
                                printf("�յ�վʱ�䣺%s\n", Rail_data.Rail_Data[count].stops[j].departureTime);
                                printf("�յ�վ���룺%d\n", Rail_data.Rail_Data[count].stops[j].distance - Rail_data.Rail_Data[count].stops[i].distance);
                                printf("\n");
                                break;  // �ҵ������������г��������ڲ�ѭ��
                            }
                        }
                    }
                }
            }
            printf("��������г�ѡ�񳵴Σ�");
            scanf_s("%s", Order_data.Order_Data[Order_data.Length-1].trainNumber, sizeof(Order_data.Order_Data[Order_data.Length].trainNumber));
            for (int i = 0; i < Rail_data.Length-1; i++) {
                if (strcmp(Rail_data.Rail_Data[i].trainNumber, Order_data.Order_Data[Order_data.Length-1].trainNumber) == 0){
                    for (int j = 0; j < Rail_data.Rail_Data[i].allstationNumber; j++) {
                        // ����Ƿ�����û������ʼ��վ
                        if (strcmp(Order_data.Order_Data[Order_data.Length-1].startingStation, Rail_data.Rail_Data[i].stops[j].stationName) == 0) {
                            // ��������յ�վ
                            for (int u = j + 1; u < Rail_data.Rail_Data[i].allstationNumber; u++) {
                                if (strcmp(Order_data.Order_Data[Order_data.Length-1].destinationStation, Rail_data.Rail_Data[i].stops[u].stationName) == 0) {
                                    // ��ӡ�����������г���Ϣ
                                    printf("������ĳ��Σ�%s����%4d��%2d��%2d�շ���\n", Rail_data.Rail_Data[i].trainNumber,year,month,day);
                                    printf("ʼ��վʱ�䣺%s\n", Rail_data.Rail_Data[i].stops[j].arrivalTime);
                                    strcpy_s(Order_data.Order_Data[Order_data.Length-1].departureTime, sizeof(Order_data.Order_Data[Order_data.Length].departureTime), Rail_data.Rail_Data[i].stops[j].arrivalTime);
                                    printf("�յ�վʱ�䣺%s\n", Rail_data.Rail_Data[i].stops[u].departureTime);
                                    strcpy_s(Order_data.Order_Data[Order_data.Length-1].arriveTime, sizeof(Order_data.Order_Data[Order_data.Length].arriveTime), Rail_data.Rail_Data[i].stops[u].departureTime);
                                    printf("�յ�վ���룺%d\n", Rail_data.Rail_Data[i].stops[u].distance - Rail_data.Rail_Data[i].stops[j].distance);
                                    distance = Rail_data.Rail_Data[i].stops[u].distance - Rail_data.Rail_Data[i].stops[j].distance;                                    
                                    if (strcmp(Order_data.Order_Data[Order_data.Length-1].seatClass, "�ص���") == 0) {
                                        Order_data.Order_Data[Order_data.Length].ticketPrice = (double)distance * 1.2;
                                        printf("Ʊ�ۣ�%.2f\n", Order_data.Order_Data[Order_data.Length-1].ticketPrice);
                                    }
                                    else if (strcmp(Order_data.Order_Data[Order_data.Length-1].seatClass, "һ����") == 0) {
                                        Order_data.Order_Data[Order_data.Length-1].ticketPrice = (double)distance * 0.6;

                                        printf("Ʊ�ۣ�%.2f\n", Order_data.Order_Data[Order_data.Length-1].ticketPrice);
                                    }
                                    else if (strcmp(Order_data.Order_Data[Order_data.Length-1].seatClass, "������") == 0) {
                                        Order_data.Order_Data[Order_data.Length-1].ticketPrice = (double)distance * 0.46;
                                        printf("��%d\n", Order_data.Length-1);
                                        printf("Ʊ�ۣ�%.2f\n", Order_data.Order_Data[Order_data.Length-1].ticketPrice);
                                    }
                                    printf("Ʊ�ۣ�%.2f\n", Order_data.Order_Data[Order_data.Length - 1].ticketPrice);
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
//��ӡ��ǰ���г���
void printAllTrains(Data_List Rail_data, int state){
    printf("��ǰ����%d��������Ϣ\n", Rail_data.Length);
    printf("����    ����վ   �յ�վ   �ܾ���   �������  ����ʱ��  ����ʱ��\n");
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
// ���һ���г������г˿͵���Ϣ
void printAllPassengers(Data_Passenger_List Passenger_data) {
    printf("֤����              �˿�����       ֤�����     ��ϵ�绰      ������ϵ��   ������ϵ�˵绰\n");
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
//��ӡ���г�Ʊ��Ϣ
void printAllOrders(Data_Order_List Order_data) {
    printf("���ж�����Ϣ���£�\n");
    printf("     ������       �˳�����    ����     ʼ��վ       �յ�վ     ֤�����     ֤����        �˿�����  ����ʱ��  ����ʱ�� ��λ�ȼ� ��λ��   Ʊ��\n");

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
//ͣ���г�
Data_List stopTrain(Data_List Rail_data) {
    // �����û�����Ҫͣ�˵��г��ĳ���
    char trainToStop[20];
    printf("������Ҫͣ�˵��г��ĳ��Σ� ");
    scanf_s("%s", trainToStop, sizeof(trainToStop));
    // �����г��������Ҫͣ�˵��г�
    for (int i = 0; i < Rail_data.Length; i++) {
        if (strcmp(Rail_data.Rail_Data[i].trainNumber, trainToStop) == 0) {
            // �ҵ�ƥ����г�����������������Ϊͣ��
            strcpy_s(Rail_data.Rail_Data[i].isServiceAvailable, sizeof(Rail_data.Rail_Data[i].isServiceAvailable),"ͣ��");
            printf("�г� %s ��ͣ�ˡ�\n", Rail_data.Rail_Data[i].trainNumber);
            return  Rail_data; // ͣ���г���ֱ�ӷ���
        }
    }
    // ��δ�ҵ�ƥ����г�
    printf("δ�ҵ�����Ϊ %s ���г���\n", trainToStop);
}
// ɾ��һ���˿�
Data_Passenger_List deletePassenger(Data_Passenger_List Passenger_data) {
    char idNumberToDelete[20];
    int found = 0;

    printf("������Ҫɾ���ĳ˿�֤���ţ� ");
    scanf_s("%s", idNumberToDelete, sizeof(idNumberToDelete));

    for (int i = 0; i < Passenger_data.Length; i++) {
        if (strcmp(Passenger_data.Passenger_Data[i].idNumber, idNumberToDelete) == 0) {
            found = 1;

            printf("\nɾ���˿���Ϣ��\n");
            printf("֤����              �˿�����       ֤�����     ��ϵ�绰      ������ϵ��   ������ϵ�˵绰\n");
            printf("%-20s %-8s %-6s %-12s %-10s %-12s\n",
                Passenger_data.Passenger_Data[i].idNumber,
                Passenger_data.Passenger_Data[i].passengerName,
                Passenger_data.Passenger_Data[i].idType,
                Passenger_data.Passenger_Data[i].phoneNumber,
                Passenger_data.Passenger_Data[i].emergencyContact,
                Passenger_data.Passenger_Data[i].emergencyContactPhone);

            // ��ɾ���ĳ˿���Ϣ�ú���ĳ˿���Ϣ����
            for (int j = i; j < Passenger_data.Length - 1; j++) {
                Passenger_data.Passenger_Data[j] = Passenger_data.Passenger_Data[j + 1];
            }

            // ���ٳ˿���Ŀ
            Passenger_data.Length--;

            printf("�˿���Ϣɾ���ɹ���\n");

            break; // �ҵ�ƥ��ĳ˿ͺ����ѭ��
        }
    }

    if (!found) {
        printf("δ�ҵ�֤����Ϊ %s �ĳ˿���Ϣ��\n", idNumberToDelete);
    }

    return Passenger_data;
}
//��Ʊ
Data_Order_List deleteOrder(Data_Order_List Order_data) {
    char idNumberToDelete[20];
    int found = 0;

    printf("������Ҫ��Ʊ��֤���ţ� ");
    scanf_s("%s", idNumberToDelete, sizeof(idNumberToDelete));

    for (int i = 0; i < Order_data.Length; i++) {
        if (strcmp(Order_data.Order_Data[i].idNumber, idNumberToDelete) == 0) {
            found = 1;

            printf("\n������Ϣ��\n");
            printf("     ������       �˳�����    ����     ʼ��վ       �յ�վ     ֤�����     ֤����        �˿�����  ����ʱ��  ����ʱ�� ��λ�ȼ� ��λ��   Ʊ��\n");
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
            // ��ɾ���ĳ˿���Ϣ�ú���ĳ˿���Ϣ����
            for (int j = i; j < Order_data.Length - 1; j++) {
                Order_data.Order_Data[j] = Order_data.Order_Data[j + 1];
            }

            // ���ٳ˿���Ŀ
            Order_data.Length--;

            printf("��Ʊ�ɹ���\n");

            break; // �ҵ�ƥ��ĳ˿ͺ����ѭ��
        }
    }

    if (!found) {
        printf("δ�ҵ�֤����Ϊ %s �ĳ˿���Ϣ��\n", idNumberToDelete);
    }
    return Order_data;
}
// ����������Ϣ��ѯ
void searchTrain(Data_List Rail_data) {
    // �û�ѡ���ѯ����
    int option;char trainToSearch[20];
    printf("��ӭ�����г���ѯϵͳ��\n");
    printf("1. ����\n");
    printf("2. ���վ\n");
    printf("3. �յ�վ\n");
    printf("4. ͣ��վ\n");
    printf("5. ����ʱ��\n");
    printf("��ѡ���ѯ������");
    scanf_s("%d", &option);

    // �����û�ѡ����в�ѯ
    switch (option) {
    // ���β�ѯ
    case 1: { 
        // �û�����Ҫ��ѯ�ĳ���
        printf("������Ҫ��ѯ�ĳ��Σ� ");
        scanf_s("%s", trainToSearch, sizeof(trainToSearch));
        // �����г��������ƥ����г�
        for (int i = 0; i < Rail_data.Length; i++) {
            if (strcmp(Rail_data.Rail_Data[i].trainNumber, trainToSearch) == 0) {
                // ���ƥ����г���Ϣ
                // ���Ը���ʵ���������������Ϣ
                printf("���� %s ����Ϣ��\n", Rail_data.Rail_Data[i].trainNumber);
                printf("���վ��%s\n", Rail_data.Rail_Data[i].startingStation);
                printf("�յ�վ��%s\n", Rail_data.Rail_Data[i].destinationStation);
                printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].departureTime);
                printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].arriveTime);
                // ���ͣ��վ��Ϣ...
                printf("ͣ��վ��Ϣ��\n");
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

        // ��δ�ҵ�ƥ����г�
        printf("δ�ҵ�����Ϊ %s ���г���\n", trainToSearch);
        break;
    }
    
    case 2: {
        // �û�����
        printf("������Ҫ��ѯ�����վ�� ");
        scanf_s("%s", trainToSearch, sizeof(trainToSearch));
        // �����г��������ƥ����г�
        for (int i = 0; i < Rail_data.Length; i++) {
            if (strcmp(Rail_data.Rail_Data[i].startingStation, trainToSearch) == 0) {
                // ���ƥ����г���Ϣ
                // ���Ը���ʵ���������������Ϣ
                printf("���� %s ����Ϣ��\n", Rail_data.Rail_Data[i].trainNumber);
                printf("���վ��%s\n", Rail_data.Rail_Data[i].startingStation);
                printf("�յ�վ��%s\n", Rail_data.Rail_Data[i].destinationStation);
                printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].departureTime);
                printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].arriveTime);
                // ���ͣ��վ��Ϣ...
                printf("ͣ��վ��Ϣ��\n");
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
        // �û�����
        printf("������Ҫ��ѯ���յ�վ�� ");
        scanf_s("%s", trainToSearch, sizeof(trainToSearch));
        // �����г��������ƥ����г�
        for (int i = 0; i < Rail_data.Length; i++) {
            if (strcmp(Rail_data.Rail_Data[i].destinationStation, trainToSearch) == 0) {
                // ���ƥ����г���Ϣ
                // ���Ը���ʵ���������������Ϣ
                printf("���� %s ����Ϣ��\n", Rail_data.Rail_Data[i].trainNumber);
                printf("���վ��%s\n", Rail_data.Rail_Data[i].startingStation);
                printf("�յ�վ��%s\n", Rail_data.Rail_Data[i].destinationStation);
                printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].departureTime);
                printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].arriveTime);
                // ���ͣ��վ��Ϣ...
                printf("ͣ��վ��Ϣ��\n");
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
        // �û�����
        printf("������Ҫ��ѯ��ͣ��վ�� ");
        scanf_s("%s", trainToSearch, sizeof(trainToSearch));
        // �����г��������ƥ����г�
        for (int i = 0; i < Rail_data.Length; i++) {
            for (int j = 0; j < Rail_data.Rail_Data[i].allstationNumber; j++) {
                if (strcmp(Rail_data.Rail_Data[i].stops[j].stationName, trainToSearch) == 0) {
                    // ���ƥ����г���Ϣ
                    // ���Ը���ʵ���������������Ϣ
                    printf("���� %s ����Ϣ��\n", Rail_data.Rail_Data[i].trainNumber);
                    printf("���վ��%s\n", Rail_data.Rail_Data[i].startingStation);
                    printf("�յ�վ��%s\n", Rail_data.Rail_Data[i].destinationStation);
                    printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].departureTime);
                    printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].arriveTime);
                    // ���ͣ��վ��Ϣ...
                    printf("ͣ��վ��Ϣ��\n");
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
        // �û�����
        printf("������Ҫ��ѯ�ĳ���ʱ�䣺 ");
        scanf_s("%s", trainToSearch, sizeof(trainToSearch));
        // �����г��������ƥ����г�
        for (int i = 0; i < Rail_data.Length; i++) {
            if (strcmp(Rail_data.Rail_Data[i].departureTime, trainToSearch) == 0) {
                // ���ƥ����г���Ϣ
                // ���Ը���ʵ���������������Ϣ
                printf("���� %s ����Ϣ��\n", Rail_data.Rail_Data[i].trainNumber);
                printf("���վ��%s\n", Rail_data.Rail_Data[i].startingStation);
                printf("�յ�վ��%s\n", Rail_data.Rail_Data[i].destinationStation);
                printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].departureTime);
                printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].arriveTime);
                // ���ͣ��վ��Ϣ...
                printf("ͣ��վ��Ϣ��\n");
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
    {        printf("��Ч��ѡ��\n");
            break; 
    }

    }
    return;
}
// �˿���Ϣ��ѯ
void searchPassenger(Data_Passenger_List Passenger_data) {
    char searchKey[50];
    int found = 0;

    printf("�������ѯ�ؼ��֣�������֤���š��ֻ��š�������ϵ�˵ȣ��� ");
    scanf_s("%s", searchKey, sizeof(searchKey));

    printf("\n��ѯ�����\n");
    printf("֤����              �˿�����       ֤�����     ��ϵ�绰      ������ϵ��   ������ϵ�˵绰\n");

    for (int i = 0; i < Passenger_data.Length; i++) {
        // ��ÿ���ֶ��в��ҹؼ���
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
        printf("δ�ҵ�ƥ��ĳ˿���Ϣ��\n");
    }
}
//��ӡһ������
void Order_data_print(Data_Order_List Order_data, int i) {

    printf("�����ţ�%s\n", Order_data.Order_Data[i].orderNumber);
    printf("�˳����ڣ�%s\n", Order_data.Order_Data[i].travelDate);
    printf("���Σ�%s\n", Order_data.Order_Data[i].trainNumber);
    printf("ʼ��վ��%s\n", Order_data.Order_Data[i].startingStation);
    printf("�յ�վ��%s\n", Order_data.Order_Data[i].destinationStation);
    printf("֤�����%s\n", Order_data.Order_Data[i].idType);
    printf("֤���ţ�%s\n", Order_data.Order_Data[i].idNumber);
    printf("�˿�������%s\n", Order_data.Order_Data[i].passengerName);
    printf("����ʱ�䣺%s\n", Order_data.Order_Data[i].departureTime);
    printf("����ʱ�䣺%s\n", Order_data.Order_Data[i].arriveTime);
    printf("��λ�ȼ���%s\n", Order_data.Order_Data[i].seatClass);
    printf("��λ�ţ�%s\n", Order_data.Order_Data[i].seatNumber);
    printf("Ʊ�ۣ�%.2f\n", Order_data.Order_Data[i].ticketPrice);
}
void printOrderInfo_num(Data_Order_List Order_data) {
    int i=0;
    printf("��ǰ����%d������", Order_data.Length-1);
    printf("�����붩����");
    scanf_s("%d", &i);
    Order_data_print(Order_data, i);
}
//������Ϣ��ѯ
void searchOrder(Data_Order_List Order_data) {
    int option;
    char key[20];

    printf("��ӭ���붩����ѯϵͳ��\n");
    printf("1. ������\n");
    printf("2. �˳�����\n");
    printf("3. ����\n");
    printf("4. ʼ��վ\n");
    printf("5. �յ�վ\n");
    printf("6. ֤����\n");
    printf("7. �˿�����\n");
    printf("��ѡ���ѯ������");
    scanf_s("%d", &option);

    // �����û�ѡ����в�ѯ
    switch (option) {
    case 1:
        printf("������Ҫ��ѯ�Ķ����ţ� ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 2:
        printf("������Ҫ��ѯ�ĳ˳����ڣ� ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 3:
        printf("������Ҫ��ѯ�ĳ��Σ� ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 4:
        printf("������Ҫ��ѯ��ʼ��վ�� ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 5:
        printf("������Ҫ��ѯ���յ�վ�� ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 6:
        printf("������Ҫ��ѯ��֤���ţ� ");
        scanf_s("%s", key, sizeof(key));
        break;
    case 7:
        printf("������Ҫ��ѯ�ĳ˿������� ");
        scanf_s("%s", key, sizeof(key));
        break;
    default:
        printf("��Ч��ѡ��\n");



    }
    // �����������ݽ��в�ѯ
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
//��Ʊ��ѯ
void checkRemainingSeats(Data_Order_List Order_data, Data_List Rail_data) {
    // ��ȡ�û�����ĳ��κ���λ�ȼ�
    char trainNumber[20];
    char seatClass[20];
    int   remainingSeats = 0;
    printf("�����복�Σ�");
    scanf_s("%s", trainNumber, sizeof(trainNumber));
    printf("��������λ�ȼ����ص�����һ����������������");
    scanf_s("%s", seatClass, sizeof(seatClass));

    // �����������ݣ��ҵ����������Ķ�����Ϣ
    for (int i = 0; i < Rail_data.Length; i++) {
        if (strcmp(Rail_data.Rail_Data[i].trainNumber, trainNumber) == 0) {
            // �ҵ����������ĳ�����Ϣ

            // ������Ʊ��
            if (strcmp(seatClass, "�ص���") == 0) {
                remainingSeats = Rail_data.Rail_Data[i].principalSeat;
            }
            else if (strcmp(seatClass, "һ����") == 0) {
                remainingSeats = Rail_data.Rail_Data[i].firSeat;
            }
            else if (strcmp(seatClass, "������") == 0) {
                remainingSeats = Rail_data.Rail_Data[i].secSeat;
            }
            // �����Ʊ��Ϣ
            printf("���Σ�%s����λ�ȼ���%s��Ʊ��%d\n", trainNumber, seatClass,remainingSeats);
            return;  // ��ѯ��ɣ���������
        }
    }

    // û���ҵ����������Ķ�����Ϣ
    printf("δ�ҵ����������Ķ�����Ϣ��\n");
}
// �޸ĸ���������Ϣ
Data_List modifyTrain(Data_List Rail_data) {
    // �û�����Ҫ�޸ĵĳ���
    char trainToModify[20];
    printf("������Ҫ�޸���Ϣ�ĳ��Σ� ");
    scanf_s("%s", trainToModify, sizeof(trainToModify));

    // �����г��������Ҫ�޸ĵ��г�
    for (int i = 0; i < Rail_data.Length; i++) {
        if (strcmp(Rail_data.Rail_Data[i].trainNumber, trainToModify) == 0) {
            // �����ǰ�г���Ϣ
            printf("��ǰ %s �г�����Ϣ��\n", Rail_data.Rail_Data[i].trainNumber);
            printf("���վ��%s\n", Rail_data.Rail_Data[i].startingStation);
            printf("�յ�վ��%s\n", Rail_data.Rail_Data[i].destinationStation);
            printf("����ʱ�䣺%s\n", Rail_data.Rail_Data[i].departureTime);
            // ���������Ϣ...

            // �û�ѡ��Ҫ�޸ĵ���Ϣ
            int option;
            
            printf("1. ���վ\n");
            printf("2. �յ�վ\n");
            printf("3. ����ʱ��\n");
            // ����������޸���Ϣ��ѡ��...
            printf("��ѡ��Ҫ�޸ĵ���Ϣ��");
            scanf_s("%d", &option);

            // �����û�ѡ������޸�
            switch (option) {
            case 1: // �޸����վ
                printf("�������µ����վ�� ");
                scanf_s("%s", Rail_data.Rail_Data[i].startingStation, sizeof(Rail_data.Rail_Data[i].startingStation));
                break;

            case 2: // �޸��յ�վ
                printf("�������µ��յ�վ�� ");
                scanf_s("%s", Rail_data.Rail_Data[i].destinationStation, sizeof(Rail_data.Rail_Data[i].destinationStation));
                break;

            case 3: // �޸ķ���ʱ��
                printf("�������µķ���ʱ�䣺 ");
                scanf_s("%s", Rail_data.Rail_Data[i].departureTime, sizeof(Rail_data.Rail_Data[i].departureTime));
                break;
            default:
                printf("��Ч��ѡ��\n");
                break;
            }
            return Rail_data;
        }
    }

    // ��δ�ҵ�ƥ����г�
    printf("δ�ҵ�����Ϊ %s ���г���\n", trainToModify);
}
// �˿���Ϣ�޸�
Data_Passenger_List modifyPassenger(Data_Passenger_List Passenger_data) {
    char idNumberToModify[20];
    int found = 0;

    printf("������Ҫ�޸���Ϣ�ĳ˿�֤���ţ� ");
    scanf_s("%s", idNumberToModify, sizeof(idNumberToModify));

    for (int i = 0; i < Passenger_data.Length; i++) {
        if (strcmp(Passenger_data.Passenger_Data[i].idNumber, idNumberToModify) == 0) {
            found = 1;
            printf("\n�˿�ԭ��Ϣ��\n");
            printf("֤����              �˿�����       ֤�����     ��ϵ�绰      ������ϵ��   ������ϵ�˵绰\n");
            printf("%-20s %-8s %-6s %-12s %-10s %-12s\n",
                Passenger_data.Passenger_Data[i].idNumber,
                Passenger_data.Passenger_Data[i].passengerName,
                Passenger_data.Passenger_Data[i].idType,
                Passenger_data.Passenger_Data[i].phoneNumber,
                Passenger_data.Passenger_Data[i].emergencyContact,
                Passenger_data.Passenger_Data[i].emergencyContactPhone);
            // �޸��ֻ���
            printf("�������µ���ϵ�绰�� ");
            scanf_s("%s", Passenger_data.Passenger_Data[i].phoneNumber, sizeof(Passenger_data.Passenger_Data[i].phoneNumber));

            // �޸Ľ�����ϵ��
            printf("�������µĽ�����ϵ�ˣ� ");
            scanf_s("%s", Passenger_data.Passenger_Data[i].emergencyContact, sizeof(Passenger_data.Passenger_Data[i].emergencyContact));

            // �޸Ľ�����ϵ�˵绰
            printf("�������µĽ�����ϵ�˵绰�� ");
            scanf_s("%s", Passenger_data.Passenger_Data[i].emergencyContactPhone, sizeof(Passenger_data.Passenger_Data[i].emergencyContactPhone));

            printf("�˿���Ϣ�޸ĳɹ���\n");
            break; // �ҵ�ƥ��ĳ˿ͺ����ѭ��
        }
    }

    if (!found) {
        printf("δ�ҵ�֤����Ϊ %s �ĳ˿���Ϣ��\n", idNumberToModify);
    }

    return Passenger_data;
}
// ����ָ����Χ�ڵ��������
int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}
//��Ʊ�˵�����
void OrdershowMenu() {
    printf("\n========������Ʊ��Ϣ����ϵͳ========\n");
    printf("1. ��ӡȫ��������Ϣ\n");
    printf("2. ��ӡĳһ��������Ϣ\n");
    printf("3. ��Ʊ��ѯ\n");
    printf("4. ��Ʊ\n");
    printf("5. ��Ʊ\n");
    printf("0. �˳�\n");
}
//�г��˵�����
void RailshowMenu() {
    printf("\n========������Ϣ����ϵͳ========\n");
    printf("1. ���и�����Ϣ\n");
    printf("2. ����һ���г�\n");
    printf("3. ͣ��һ���г�\n");
    printf("4. ����������Ϣ��ѯ\n");
    printf("5. �޸ĸ���������Ϣ\n");
    printf("0. �˳�\n");
}
//�˿Ͳ˵�����
void PassengershowMenu() {
    //    // �û��˵�
         printf("\n========�˿���Ϣ����ϵͳ========\n");
         printf("1. ����һ���˿�\n");
         printf("2. ���г˿���Ϣ\n");
         printf("3. �˿���Ϣ��ѯ\n");
         printf("4. �޸ĳ˿���Ϣ\n");
         printf("5. ɾ���˿���Ϣ\n");
         printf("0. �˳�\n");
}
//�г�ϵͳ��������
void RailSYSTEM(Data_List Rail_data) {
    int choice;
    do {
        RailshowMenu();
        printf("��ѡ������� ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printAllTrains(Rail_data, 1); // ������и�����Ϣ�������������
            break;

        case 2:
            Rail_data = addTrain(Rail_data); // ����һ���г�
            break;

        case 3:
            Rail_data = stopTrain(Rail_data); // ͣ��һ���г�
            break;

        case 4:
            searchTrain(Rail_data); // ����������Ϣ��ѯ
            break;

        case 5:
            Rail_data = modifyTrain(Rail_data); // �޸ĸ���������Ϣ
            break;

        case 0:
            printf("��лʹ�ã��ټ���\n");
            break;

        default:
            printf("��Ч��ѡ�����������롣\n");
            break;
        }

    } while (choice != 0);// ����ʽ������Ϣ����ϵͳ

}
//�˿�ϵͳ��������
void PassengerSYSTEM(Data_Passenger_List  Passenger_data) {
    int choice;

    do {
        PassengershowMenu();
        printf("��ѡ������� ");
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
            printf("��лʹ�ó˿���Ϣ����ϵͳ��\n");
            break;
        default:
            printf("��Ч��ѡ�����������롣\n");
        }

    } while (choice != 0);// ����ʽ�˿���Ϣ����ϵͳ

}
//��Ʊϵͳ��������
void OrderSYSTEM(Data_Order_List Order_data, Data_List Rail_data) {
    int choice;
    do {
        OrdershowMenu();
        printf("��ѡ������� ");
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
            printf("��лʹ�ø�����Ʊ��Ϣ����ϵͳ��\n");
            break;
        default:
            printf("��Ч��ѡ�����������롣\n");
        }

    } while (choice != 0);


}
//�ܲ˵�����
void ALLshowMenu() {
    printf("\n========������Ʊϵͳ========\n");
    printf("1. �˿���Ϣ����ϵͳ\n");
    printf("2. ������Ϣ����ϵͳ\n");
    printf("3. ������Ʊ��Ϣ����ϵͳ\n");
    printf("0. �˳�\n");
}
//
#endif // !_Rail_System_













