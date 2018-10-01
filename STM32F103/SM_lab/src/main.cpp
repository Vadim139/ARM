/*
 * main.cpp
 *
 *  Created on: 28 paü 2017
 *      Author: Vadim
 *
 *  Alarm system created for SM lab.
 */


#include "main.h"
#include "Timer.h"
#include "BlinkLed.h"
#include "ESP8266.h"
#include "SIM800L.h"
#include "NET.h"
#include "RTC.h"
#include "Atmega.h"
#include "md5.h"
#include "DataBase.h"
#include "RS485.h"
#include "NTC.h"
#include "ADC.h"
#include "EE_memory.h"
#include "Other.h"


// Pragmas
#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-parameter"
//#pragma GCC diagnostic ignored "-Wmissing-declarations"
//#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wwrite-strings"


Timer timer;
ESP8266 ESP;
SIM800L SIM;
NET Net;
IRTC RTC1;
Atmega Atm644;
Data_Base Base;
MD5 Md5;
NTC Ntc;
User* user;
Sensor* sensor;
Output* output;

User* user_t;
Sensor* sensor_t;
Output* output_t;
char *num_t;
char WIFIName_t[19];
char WIFIPass_t[20];
uint8_t del_t[4];
uint8_t Net_s_t;
uint8_t Net_on_t;

GPIO_IO Led(GPIOC,GPIO_Pin_13,1);

GPIO_IO Out[4] = { GPIO_IO(O1_GPIO,O1_PIN,1),
				   GPIO_IO(O2_GPIO,O2_PIN,1),
				   GPIO_IO(O3_GPIO,O3_PIN,1),
				   GPIO_IO(O4_GPIO,O4_PIN,1)};

GPIO_IO WD[5] = {GPIO_IO(W1_GPIO,W1_PIN,0),
				 GPIO_IO(W2_GPIO,W2_PIN,0),
				 GPIO_IO(W3_GPIO,W3_PIN,0),
				 GPIO_IO(W4_GPIO,W4_PIN,0),
				 GPIO_IO(W5_GPIO,W5_PIN,0)};

GPIO_IO Mot[5] = {GPIO_IO(M1_GPIO,M1_PIN,0),
				  GPIO_IO(M2_GPIO,M2_PIN,0),
				  GPIO_IO(M3_GPIO,M3_PIN,0),
				  GPIO_IO(M4_GPIO,M4_PIN,0),
				  GPIO_IO(M5_GPIO,M5_PIN,0)};


GPIO_IO IN12(IN12_GPIO,IN12_PIN,0);

char DataTime[30];
volatile uint8_t rec = 0;
volatile bool rec_flag_ESP = false;
volatile bool rec_flag_SIM = false;
volatile uint8_t err = 0;
char num[] = "530787836";
volatile int p = 0;
volatile bool init_flag = false;
volatile bool net_read_flag = false;
char string[101];
char hash[17];

extern uint16_t Users_addr[10];
extern uint16_t Sensors_addr[10];
extern uint16_t Numbers_addr[10];
extern uint16_t Outputs_addr[4];
	Output o1;
	int TEMP1;
int main()
{

	/////////////////////////////////
	// Initialization of all needed things
	/////////////////////////////////

	trace_printf("Starting initialization...\n");

	memset(DataTime,0,30);
	memset(string,0,101);

	user_t = 0;
	sensor_t = 0;
	output_t = 0;
	memset(WIFIName_t,0,19);
	memset(WIFIPass_t,0,20);
	del_t[0] = 0;
	del_t[1] = 0;
	del_t[2] = 0;
	del_t[3] = 0;
	Net_s_t = 0;
	Net_on_t = 0;
//	memset(num_t,0,10);

	for(int i = 0; i<10; i++)
	{
		Users_addr[i] = USERS_BASE_ADDR+(i*USER_SIZE);
		Sensors_addr[i] = SENSORS_BASE_ADDR+(i*SENSOR_SIZE);
		Numbers_addr[i] = NUMBERS_BASE_ADDR+(i*NUMBERS_SIZE);
		if(i<4)
			Outputs_addr[i] = OUTPUTS_BASE_ADDR+(i*OUTPUT_SIZE);
	}

	// Relay out
	for(int i = 0; i<4; i++)
		Out[i].Init();

    // Motion sensors
    for(int i = 0; i<5; i++){
    	Mot[i].Mode = GPIO_Mode_IPD;
    	Mot[i].Init();
    }

    // Window/door sensors
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE; // Makro to turn off JTAG

    for(int i = 0; i<5; i++)
    	WD[i].Init();

    // Board LED
    Led.Init();
    Led.Set_low();

    // Input to check external 12V
    IN12.Mode = GPIO_Mode_IPD;
    IN12.Init();

    /////////////////////////////////
	// Initialization of periphery
    /////////////////////////////////

    trace_printf("Initialization of periphery...\n");

    // Init of sys timer
	timer.start();
//	NVIC_GetPriority(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 0);
	trace_printf("System clock: %u Hz\n", SystemCoreClock);

	// Init RS485
    RS485_Init();

//    // Init panel
//    if(!(Atm644.Init()))
//    {
    	/*Atm644.IsConnected = true;
    	Atm644.Run();
    	timer.sleep(50);
    	Atm644.LCD_Clr();
    	timer.sleep(50);
    	Atm644.LCD_Put(0,0,"Initialization..");*/
//    	Atm644.Halt();
//    }

    err = 0;


	// Init Timer 1 (10Hz)
	TIM_Config(TIM1, 7200, 1000);
	NVIC_SetPriority(TIM1_UP_IRQn, 10);
	trace_printf("SysTick priority: %d\nTim1 priority: %d\n",NVIC_GetPriority(SysTick_IRQn),NVIC_GetPriority(TIM1_UP_IRQn));

	// Flash init
	FEE_Init();

   	timer.sleep(100);
//   	FEE_ReadAll();

//   	Base.Change_WIFIName("Vadim123");
//   	Base.Change_WIFIPass("12345678qwertyui");
	// Init ESP
	/*for(int i = 0; i<5; i++)
		if(!(err = ESP.Init()))
			break;

	if(err && Atm644.IsConnected){
		Atm644.LCD_Put(0,1,"WIFI INIT FAILED");
		err = 0;
	}*/

	// Init SIM
	for(int i = 0; i<5; i++)
		if(!(err = SIM.Init()))
			break;

	if(err && Atm644.IsConnected){
		Atm644.LCD_Put(0,1,"GSM INIT FAILED ");
		err = 0;
	}


    // Init RTC
    RTC1.RTC_Config();
    RTC1.IT_Config();

    // Init NTC
    Ntc.Init();
    ADCx_Init(ADC1, 0);


	timer.sleep(10000);

    Net.Connect();

//    if(Net.IsWIFI())
//    	trace_printf("WIFI connected!\n");
//    else
//    	trace_printf("Connection failed!!");

    while(!Net.IsGSM());
    	trace_printf("GSM connected!\n");
//    else
//    	trace_printf("Connection failed!!\n");
    RTC1.Set_From_Net();
//    if(Atm644.IsConnected){
    	Atm644.Run();
    	Atm644.LCD_Clr();
    	timer.sleep(50);
    	Atm644.LCD_Put(0,1,"Done");
//    }


    // TODO
//
//       	    for(int i = 0; i< 2000; i++)
//       	    	FEE_WriteDataByte(i,0);


//
//       	    User u1;
//       	    u1.Access_lvl = 1;
//            Md5.Get_MD5("1234",u1.PIN);
//            Md5.Get_MD5("4567",u1.RFID_Num);
//       		strcpy(u1.Strefy,"1,2");
//       		strcpy(u1.User_Name,"Kinga");
//       	   	u1.User_ID = 0;
//
//       	    User u2;
//       	    u2.Access_lvl = 2;
//            Md5.Get_MD5("1234",u2.PIN);
//            Md5.Get_MD5("4567",u2.RFID_Num);
//       	    strcpy(u2.Strefy,"1,3");
//       	    strcpy(u2.User_Name,"Adam");
//       	   	u2.User_ID = 0;
//       	//   	Base.Update_User(u2,2);
//       	    User u3;
//       	    u3.Access_lvl = 1;
//       	    strcpy(u3.PIN,"QWERTYUIOPASDFGHJKLZXCVBNMQWERTY");
//       		strcpy(u3.RFID_Num,"ABCDABCD1234ZZZZZZZZZZ876543AD");
//       		strcpy(u3.Strefy,"8,2");
//       		strcpy(u3.User_Name,"Magda");
//       	   	u3.User_ID = 0;
//
//
//       	   	Sensor s1;
//       	   	s1.IN = 1;
//       	   	s1.Sensor_ID = 0;
//       	    strcpy(s1.Sensor_Name,"Okno_schody");
//       	   	s1.Strefa = 1;
//
//       	   	Sensor s2;
//       	   	s2.IN = 2;
//       	   	s2.Sensor_ID = 0;
//       	    strcpy(s2.Sensor_Name,"Czujka_korytarz");
//       	   	s2.Strefa = 1;
//
//       	   	Sensor s3;
//       	   	s3.IN = 6;
//       	   	s3.Sensor_ID = 0;
//       	    strcpy(s3.Sensor_Name,"Czujka_wejscie");
//       	   	s3.Strefa = 2;
//
//       	   	Output o1;
//       	   	o1.Schedule[0] = 0;
//       	   	o1.Schedule[1] = 30;
//       	   	o1.Schedule[2] = 2;
//       	   	o1.Schedule[3] = 55;
//       	   	o1.Schedule[4] = 14;
//       	   	o1.Schedule[5] = 0;
//       	   	o1.Schedule[6] = 18;
//       	   	o1.Schedule[7] = 0;
//       	   	o1.Output_ID = 1;
//       	   	o1.Type = 2;
//
//       	   	Output o2;
//       	   	o2.Schedule[0] = 5;
//       	   	o2.Schedule[1] = 5;
//       	   	o2.Schedule[2] = 6;
//       	   	o2.Schedule[3] = 30;
//       	   	o2.Schedule[4] = 23;
//       	   	o2.Schedule[5] = 55;
//       	   	o2.Schedule[6] = 0;
//       	   	o2.Schedule[7] = 0;
//       	   	o2.Output_ID = 3;
//       	   	o2.Type = 1;
//
//       	   	Output o3;
//       	   	o3.Schedule[0] = 0;
//       	   	o3.Schedule[1] = 30;
//       	   	o3.Schedule[2] = 2;
//       	   	o3.Schedule[3] = 20;
//       	   	o3.Schedule[4] = 0;
//       	   	o3.Schedule[5] = 0;
//       	   	o3.Schedule[6] = 0;
//       	   	o3.Schedule[7] = 30;
//       	   	o3.Output_ID = 2;
//       	   	o3.Type = 0;
////
//       	   	char n1[] = "530787836";
//       	   	char n2[] = "501467971";
//
//
//       	   	FEE_Write_Settings();
//       	   	Base.Add_User(u1);
//       	   	Base.Add_User(u2);
//       	   	Base.Add_User(u3);
//           	Base.Add_Sensor(s1);
//       	   	Base.Add_Sensor(s2);
//       	   	Base.Add_Sensor(s3);
//       	   	Base.Add_Output(o1);
//       	   	Base.Add_Output(o2);
//       	   	Base.Add_Output(o3);
//       	   	Base.Add_GSM(n1,"0");
//       	   	Base.Add_GSM(n2,"0");

    		Base.Read_Outputs();
    		output = Base.Get_Output(0);
    		TEMP1 = output->Schedule[1];

    	   	o1.Schedule[0] = 0;
    	   	o1.Schedule[1] = 30;
    	   	o1.Schedule[2] = 2;
    	   	o1.Schedule[3] = 20;
    	   	o1.Schedule[4] = 0;
    	   	o1.Schedule[5] = 0;
    	   	o1.Schedule[6] = 0;
    	   	o1.Schedule[7] = 0;
    	   	o1.Output_ID = 3;
    	   	o1.Type = 0;
//    	Base.Update_Output(o1,1);

       	   	init_flag = true;



           	trace_printf("Initialization end...\n");
//           	FEE_Erase();
//           	Base.Read_All();
//			for(int i = 0; i< Base.Get_User_num();i++)
//			{
//				FEE_Add_User(*(Base.Get_User(i)));
//			}
//			for(int i = 0; i< Base.Get_Sensor_num();i++)
//			{
//				FEE_Add_Sensor(*(Base.Get_Sensor(i)));
//			}
//			for(int i = 0; i< Base.Get_Output_num();i++)
//			{
//				FEE_Add_Output(*(Base.Get_Output(i)));
//			}
//			for(int i = 0; i< Base.Get_GSM_num();i++)
//			{
//				FEE_Add_Number(i+1,Base.Get_GSM(i));
//			}
//				FEE_Write_Settings();
//				FEE_WriteData(1,b1,200);
			trace_printf("Saved!\n");
//        	Atm644.LCD_Clr();
//        	Atm644.LCD_Put(0,0,"Initialization..");
//
//
//        	Atm644.LCD_Clr();
//        	Atm644.LCD_Put(0,1,"Blabla..");

    while(1)
    {
    	switch (rec) {
			case 1:
				RTC1.Set_From_Net();
				rec = 0;
				break;
			case 2:
				if(Base.Get_GSM_num() != 0)
					if((err = SIM.GSM_SendSMS(Base.Get_GSM(0),"Alarm!! Naruszenie strefy 1")))
	    		    	trace_printf("Cannot send SMS!! Error code: %u\n", err);
	    		    else
	    		    	trace_printf("SMS sended!\n");
				rec = 0;
	    		break;
			case 3:
    			Md5.Get_MD5("1234",hash);
	    		trace_puts(hash);
	    		timer.sleep(100);
	    		rec = 0;
				break;
			case 4:
				net_read_flag = true;
				trace_printf("Czas: %u:%u:%u\n", RTC1.Time_s.Hour, RTC1.Time_s.Minute, RTC1.Time_s.Second);
	    		Base.Read_All();
	    		trace_printf("Czas: %u:%u:%u\n", RTC1.Time_s.Hour, RTC1.Time_s.Minute, RTC1.Time_s.Second);
	    		net_read_flag = false;
	    		rec = 0;
	    		break;
			case 5:
				trace_printf("Czas: %u:%u:%u\n", RTC1.Time_s.Hour, RTC1.Time_s.Minute, RTC1.Time_s.Second);
	    		Base.Update_Sensor(1,0);
	    		trace_printf("Czas: %u:%u:%u\n", RTC1.Time_s.Hour, RTC1.Time_s.Minute, RTC1.Time_s.Second);
	    		rec = 0;
	    		break;
			case 6:
				trace_printf("Czas: %u:%u:%u\n", RTC1.Time_s.Hour, RTC1.Time_s.Minute, RTC1.Time_s.Second);
	    		Base.Update_Sensor(1,1);
	    		trace_printf("Czas: %u:%u:%u\n", RTC1.Time_s.Hour, RTC1.Time_s.Minute, RTC1.Time_s.Second);
	    		rec = 0;
	    		break;
			case 7:
//				RS_Transfer(0,WD[2].read_state());
				trace_printf("Czujki okien: %d %d %d %d %d\n", WD[0].read_state(), WD[1].read_state(), WD[2].read_state(), WD[3].read_state(), WD[4].read_state());
				rec = 0;
				break;
			case 8:
				trace_printf("Czujki okien: %d %d %d %d %d\n", Mot[0].read_state(), Mot[1].read_state(), Mot[2].read_state(), Mot[3].read_state(), Mot[4].read_state());
				rec = 0;
				break;
			case 9:
	    		if((err = SIM.Get_operator()))
	    		    	trace_printf("Connection failed!! Error code: %u\n", err);
	    		    else
	    		    	trace_printf("Operator: ");
	    		trace_puts(SIM.Operator);
	    		rec = 0;
	    		break;
			case 10:
	    		Net.Connect_GSM();
	    		 if(Net.IsGSM())
	    	    	trace_printf("GSM connected!\n");
	    	    else
	    	    	trace_printf("Connection failed!!");

	    			if((err = SIM.GSM_GetConfig()))
	    			    	trace_printf("Can't get config!! Error code: %u\n", err);
	    			    else
	    			    	Net.IsGSM(1);
//	    			    	trace_printf("Config saved!\n");

//	    			trace_puts(SIM.IP_TCP);
	    		 rec = 0;
				break;
			case 11:
				Base.WATCHING[0] = true;
				Base.WATCHING[1] = true;
				Base.WATCHING[2] = true;
				Base.WATCHING[3] = true;
				Base.WATCHING[4] = true;
	    		 rec = 0;
				break;
			case 12:
				Base.WATCHING[0] = false;
				Base.WATCHING[1] = false;
				Base.WATCHING[2] = false;
				Base.WATCHING[3] = false;
				Base.WATCHING[4] = false;
				Base.ALARM = false;
	    		 rec = 0;
				break;
			case 13:
				SIM.GSM_Call("530787836");
	    		 rec = 0;
				break;
			case 14:
				SIM.GSM_Cancel_call();
	    		 rec = 0;
				break;
			case 15:
				for(int i = 0; i< Base.Get_User_num();i++)
				{
					FEE_Add_User(*(Base.Get_User(i)));
				}
				for(int i = 0; i< Base.Get_Sensor_num();i++)
				{
					FEE_Add_Sensor(*(Base.Get_Sensor(i)));
				}
				for(int i = 0; i< Base.Get_Output_num();i++)
				{
					FEE_Add_Output(*(Base.Get_Output(i)));
				}
				for(int i = 0; i< Base.Get_GSM_num();i++)
				{
					FEE_Add_Number(i+1,Base.Get_GSM(i));
				}
					FEE_Write_Settings();
//				FEE_WriteData(1,b1,200);
				trace_printf("Saved!\n");
	    		 rec = 0;
				break;
			case 16:
//				for()
//				FEE_Add_User(u1);
//				FEE_WriteData(1,b2,600);
				trace_printf("Saved!\n");
	    		 rec = 0;
				break;
			default:
				break;
		}
    	timer.sleep(500);
    	Led.Toggle();
    }

    return 0;
}

void delayms(uint32_t ms)
{
	timer.sleep(ms);
}



void USART1_IRQHandler(void)
{
    if ((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
    {
    	uint8_t ch;

    	ch = USART_ReceiveData(USART1);

    	ESP.ESP_recdata(&ch);
    	if(ESP.State == false)
    		rec_flag_ESP = true;

    }

}


void USART2_IRQHandler(void)
{
    if ((USART2->SR & USART_FLAG_RXNE) != (u16)RESET)
    {
    	uint8_t ch;

    	ch = USART_ReceiveData(USART2);

    	SIM.SIM_recdata(&ch);
    	if(SIM.State == false)
    		rec_flag_SIM = true;

    }

}

volatile uint8_t temp_rec;
void USART3_IRQHandler(void)
{
    if ((USART3->SR & USART_FLAG_RXNE) != (u16)RESET)
    {
    	temp_rec = RS_Receive();

    	if(Atm644.receive == 0 && temp_rec == 253)
    	{
    		Atm644.receive = 2;
    	}
    	else if(Atm644.receive == 2)
    	{
    		rec = temp_rec;
    		Atm644.receive = 0;
    	}
    	else if(Atm644.receive == 0 && temp_rec == 254)
    	{
    		Atm644.Write_point = 0;
    		Atm644.receive = 1;
    	}
    	else if(Atm644.receive == 1 && temp_rec != 254)
    	{
    		Atm644.Rec_data((uint8_t*)&temp_rec);
    	}
    	else if(Atm644.receive == 1 && temp_rec == 254 && !Atm644.proc)
    	{
    		Atm644.Read_point = 0;
    		Atm644.receive = 0;
    		Atm644.proc = true;
    		Atm644.Atm_proc();
    		Atm644.Write_point = 0;
    		Atm644.Read_point = 0;


    	}
    }
}

int cE = 0, cS = 0;
//uint8_t ID[6];
volatile uint8_t tim1 = 0, tim2 = 0;
uint16_t tim3 = 0, tim4 = 0;
volatile bool Alarm_flag = false;
volatile bool Sch1 = false, Sch2 = false;

char temp[10];

void TIM1_UP_IRQHandler() {
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {

		if (init_flag && !net_read_flag) {
//			timer.sleep(50);
			if (tim1 >= 10) { // 1 Hz

				tim1 = 0;
			} else if (tim2 >= 100) { // 0.1 Hz

//		    if(!Atm644.IsConnected)
//		        if(!(Atm644.Init()))
//		        	Atm644.IsConnected = true;

				/*if (!Net.IsWIFI() && (Base.Get_Net_s() != 2)) {
					Net.Connect_WIFI();
					if (Net.IsWIFI())
						trace_printf("WIFI connected!\n");
					else
						trace_printf("Connection failed!!");
				}*/

				if (!Net.IsGSM() && (Base.Get_Net_s() != 1)) {
//		    	rec = 10;
					Net.Connect_GSM();
					if (Net.IsGSM())
						trace_printf("GSM connected!\n");
					else
						trace_printf("Connection failed!!");
				}


				o1.Schedule[1] = (int)Ntc.Get_temp();
				Base.Update_Output(o1,3);
				Base.Read_Output1();
	    		output = Base.Get_Output(0);
	    		TEMP1 = output->Schedule[1];

				tim2 = 0;
			} else if (tim4 >= 3600){
				RTC1.Set_From_Net();
				tim4 = 0;
			}else {
				tim1++;
				tim2++;
				tim4++;
			}

			if(Base.ALARM && Alarm_flag)
			{
				if (Base.Get_GSM_num() != 0){
					if(tim3%150 == 0 && tim3/150<Base.Get_GSM_num()){
						SIM.GSM_Cancel_call();
						SIM.GSM_Call(Base.Get_GSM(tim3/150));
					}else if(tim3%150 == 0 && tim3/150 >= Base.Get_GSM_num())
					{
						SIM.GSM_Cancel_call();
						tim3 = 1023;
						Alarm_flag = false;
					}
					tim3++;
				}

			}

			if (rec_flag_ESP == true) {
				if (cE >= 4) {
					cE = 0;
					rec_flag_ESP = false;
				} else
					cE++;
			}
			if (rec_flag_SIM == true) {
				if (cS >= 4) {
					cS = 0;
					rec_flag_SIM = false;
				} else
					cS++;
			}

			for (int i = 0; i < Base.Get_Sensor_num(); i++) {
				sensor = Base.Get_Sensor(i);

				if (sensor->IN <= 5) {
					if (!sensor->Status) {
						if (Mot[sensor->IN - 1].read_state()) {
							Base.Update_Sensor(i, 1);
							if (!Base.ALARM && Base.WATCHING[sensor->Strefa]) {
								Base.ALARM = true;
								Alarm_flag = true;
								if (Base.Get_GSM_num() != 0)
									for (int i = 0; i < Base.Get_GSM_num(); i++)
										if ((err = SIM.GSM_SendSMS(
												Base.Get_GSM(i),
												"Alarm!! Naruszenie strefy 1")))
											SIM.GSM_SendSMS(Base.Get_GSM(i),
													"Alarm!! Naruszenie strefy 1");

							}
						}
					} else {
						if (!Mot[sensor->IN - 1].read_state()
								&& sensor->Status > 0 ) {
							Base.Update_Sensor(i, 0);
						}
					}
				} else {
					if (!sensor->Status) {
						if (!(WD[sensor->IN - 1 - 5].read_state())) {
							Base.Update_Sensor(i, 1);
							if (!Base.ALARM && Base.WATCHING[sensor->Strefa]) {
								Base.ALARM = true;
								Alarm_flag = true;
								if (Base.Get_GSM_num() != 0)
									for (int i = 0; i < Base.Get_GSM_num(); i++)
										if ((err = SIM.GSM_SendSMS(
												Base.Get_GSM(i),
												"Alarm!! Naruszenie strefy 1")))
											SIM.GSM_SendSMS(Base.Get_GSM(i),
													"Alarm!! Naruszenie strefy 1");
							}
						}

					} else {
						if (WD[sensor->IN - 1 - 5].read_state()
								&& sensor->Status > 0) {
							Base.Update_Sensor(i, 0);
						}
					}
				}
			}

			////////////
			// Outputs
			for (int i = 0; i < 4; i++) {
				if ((output = Base.Get_Output(i))) {
					switch (output->Type) {
					case 0:
						if (output->Status)
							Out[output->Output_ID - 1].Set_low();
						break;
					case 1:
						if (Base.ALARM){
							Out[output->Output_ID - 1].Set_high();
							output->Type = 0;
						}
						else
							Out[output->Output_ID - 1].Set_low();
						break;
					case 2:
						if(((output->Schedule[2]*60)+(output->Schedule[3])) > ((output->Schedule[0]*60)+(output->Schedule[1]))) //22-23
						{
							if((((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) >= (output->Schedule[0]*60)+(output->Schedule[1])) && (((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) <= (output->Schedule[2]*60)+(output->Schedule[3])))
							{
								if((output->Status != 1) || (o1.Schedule[1]>=TEMP1)){
									if(o1.Schedule[1]<=TEMP1){
									Out[output->Output_ID - 1].Set_high();
//									output->Status = 1;
									Base.Update_Output(output->Output_ID,1);
									Sch1 = true;
									}else{
										Out[output->Output_ID - 1].Set_low();
	//									output->Status = 0;
										Base.Update_Output(output->Output_ID,0);
										Sch1 = false;
									}
								}
							}else //if(((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) < (output->Schedule[0]*60)+(output->Schedule[1])){
							{
								if(output->Status == 1 && !Sch2){
									Out[output->Output_ID - 1].Set_low();
//									output->Status = 0;
									Base.Update_Output(output->Output_ID,0);
									Sch1 = false;
								}
							}
						}else //23-02
						{
							if(((((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) >= (output->Schedule[0]*60)+(output->Schedule[1])) && (((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) <= 1440)) || ((((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) <= (output->Schedule[2]*60)+(output->Schedule[3])) && (((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) >= 0)))
							{
								if((output->Status != 1) || (o1.Schedule[1]>TEMP1)){
									if(o1.Schedule[1]<=TEMP1){
									Out[output->Output_ID - 1].Set_high();
//									output->Status = 1;
									Base.Update_Output(output->Output_ID,1);
									Sch1 = true;
									}else if(output->Status != 0){
										Out[output->Output_ID - 1].Set_low();
	//									output->Status = 0;
										Base.Update_Output(output->Output_ID,0);
										Sch1 = false;
									}
								}
							}else //if(((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) < (output->Schedule[0]*60)+(output->Schedule[1])){
								if(output->Status == 1 && !Sch2){
									Out[output->Output_ID - 1].Set_low();
//									output->Status = 0;
									Base.Update_Output(output->Output_ID,0);
									Sch1 = false;
								}
						}

						if(((output->Schedule[6]*60)+(output->Schedule[7])) > ((output->Schedule[4]*60)+(output->Schedule[5]))) //22-23
						{
							if((((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) >= (output->Schedule[4]*60)+(output->Schedule[5])) && (((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) <= (output->Schedule[6]*60)+(output->Schedule[7])))
							{
								if(output->Status != 1){
									Out[output->Output_ID - 1].Set_high();
//									output->Status = 1;
									Base.Update_Output(output->Output_ID,1);
									Sch2 = true;
								}
							}else //if(((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) < (output->Schedule[0]*60)+(output->Schedule[1])){
							{
								if(output->Status == 1 && !Sch1){
									Out[output->Output_ID - 1].Set_low();
//									output->Status = 0;
									Base.Update_Output(output->Output_ID,0);
									Sch2 = false;
								}
							}
						}else //23-02
						{
							if(((((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) >= (output->Schedule[0]*60)+(output->Schedule[1])) && (((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) <= 0)) || ((((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) <= (output->Schedule[6]*60)+(output->Schedule[7])) && (((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) > 0)))
							{
								if(output->Status != 1){
									Out[output->Output_ID - 1].Set_high();
//									output->Status = 1;
									Base.Update_Output(output->Output_ID,1);
									Sch2 = true;
								}
							}else //if(((RTC1.Time_s.Hour*60)+RTC1.Time_s.Minute) < (output->Schedule[0]*60)+(output->Schedule[1])){
								if(output->Status == 1 && !Sch1){
									Out[output->Output_ID - 1].Set_low();
//									output->Status = 0;
									Base.Update_Output(output->Output_ID,0);
									Sch2 = false;
								}
						}


//						if ((RTC1.Time_s.Hour == output->Schedule[0]
//								|| RTC1.Time_s.Hour == output->Schedule[4])
//								&& (RTC1.Time_s.Minute == output->Schedule[1]
//										|| RTC1.Time_s.Minute
//												== output->Schedule[5]))
//							Out[output->Output_ID - 1].Set_high();
//
//						if ((RTC1.Time_s.Hour == output->Schedule[2]
//								|| RTC1.Time_s.Hour == output->Schedule[6])
//								&& (RTC1.Time_s.Minute == output->Schedule[3]
//										|| RTC1.Time_s.Minute
//												== output->Schedule[7]))
//							Out[output->Output_ID - 1].Set_low();
						break;
					default:
						break;
					}
				}
			}

		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}

}


void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0))
	{

		delay_ms(100);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}


#define RTC_LSB_MASK     ((uint32_t)0x0000FFFF)  /*!< RTC LSB Mask */

char buff[34];
void RTC_IRQHandler(void)
{

	if(RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		//sprawdzenie czy RTC siÍ nie przekrÍci≥ 24h
		if(RTC_GetCounter() >= (86400))
		{
			RTC_SetCounter(RTC_GetCounter() % (86400 - 1));
			RTC1.Day_inc();
		}

		//pobieranie aktualnego czasu tylko gdy nie jest przeprwadzane ustawiane czasu/alarmu
		if(RTC1.set == 0)
		{
			RTC1.time = RTC_GetCounter();
			RTC1.Time_s.Hour = (int)RTC1.time/3600;
			RTC1.Time_s.Minute = (int)(RTC1.time%3600)/60;
			RTC1.Time_s.Second = (int)(RTC1.time%3600)%60;
			//RTC1.alarm = RTC->ALRL | (RTC->ALRH << 16);

//			trace_printf("Czas: %u:%u:%u\n", RTC1.Time_s.Hour, RTC1.Time_s.Minute, RTC1.Time_s.Second);
//			Ntc.Get_temp(temp);
//			trace_printf("Temp: %s\n\n",temp);

			//			adc = ADC_GetConversionValue(ADC1);
			//			adcv = adc * 3.3f / 4096.0f;
			//			temp = ((4148.88*298.15)/((log((21690*adcv)/((3.3-adcv)*10000))*298.15)+4148.88));
			//			sprintf(adcs,"Adc = %d %s V  T: %s\n\r", adc, floatToString(adcv,4),floatToString(temp-273.15,4));


//			sprintf(buff,"Data: %d-%d-%d Czas: %d:%d:%d\n\r", (int)RTC1.Date_s.Day, (int)RTC1.Date_s.Month, (long)RTC1.Date_s.Year,(int)RTC1.time/3600, (int)(RTC1.time%3600)/60, (int)(RTC1.time%3600)%60);
//			RS_TransferMulti(0,0,(unsigned char*)buff,strlen(buff));


		}

		RTC_WaitForLastTask();
		//wyczyszczenie bitu generujacego przerwanie

		RTC_ClearITPendingBit(RTC_IT_SEC);
	}
}

void RTCAlarm_IRQHandler(void)
{

	if(EXTI_GetITStatus(EXTI_Line17) != RESET)
	{
		//wyczyszczenie flagi przerwania
		EXTI_ClearITPendingBit(EXTI_Line17);
		//ustawienie zmiennej do øπdania generowania sygna≥u alarmu
		RTC1.alarm_reg = 1;

		//odczekanie na zakoÒczenie operacji na RTC
		RTC_WaitForLastTask();
		//wyczyszczenie flagi przerwania
		RTC_ClearITPendingBit(RTC_IT_ALR);
		//odczekanie na zakoÒczenie operacji na RTC
		RTC_WaitForLastTask();
	}
}




#pragma GCC diagnostic pop



//    for(int i = 0; i< 2000; i++)
//    	FEE_WriteDataByte(i,0);



//    User u1;
//    u1.Access_lvl = 1;
//    strcpy(u1.PIN,"ABCDABCD12345345678909876543AD");
//	strcpy(u1.RFID_Num,"ABCDABCD1234AAAAAAAAAA876543AD");
//	strcpy(u1.Strefy,"1,2");
//	strcpy(u1.User_Name,"Kinga");
//   	u1.User_ID = 0;
//
//    User u2;
//    u2.Access_lvl = 8;
//    strcpy(u2.PIN,"ABCDABCD12345345678909876543AD");
//    strcpy(u2.RFID_Num,"ABCDABCD1234AAAAAAAAAA876543AD");
//    strcpy(u2.Strefy,"1,3");
//    strcpy(u2.User_Name,"Adam");
//   	u2.User_ID = 0;
////   	Base.Update_User(u2,2);
//    User u3;
//    u3.Access_lvl = 1;
//    strcpy(u3.PIN,"QWERTYUIOPASDFGHJKLZXCVBNMQWERTY");
//	strcpy(u3.RFID_Num,"ABCDABCD1234ZZZZZZZZZZ876543AD");
//	strcpy(u3.Strefy,"8,2");
//	strcpy(u3.User_Name,"Magda");
//   	u3.User_ID = 0;
////
//
//   	Sensor s1;
//   	s1.IN = 1;
//   	s1.Sensor_ID = 0;
//    strcpy(s1.Sensor_Name,"Okno_schody");
//   	s1.Strefa = 1;
//
//   	Sensor s2;
//   	s2.IN = 2;
//   	s2.Sensor_ID = 0;
//    strcpy(s2.Sensor_Name,"Czujka_korytarz");
//   	s2.Strefa = 1;
//
//   	Sensor s3;
//   	s3.IN = 5;
//   	s3.Sensor_ID = 0;
//    strcpy(s3.Sensor_Name,"Czujka_wejscie");
//   	s3.Strefa = 2;
//
//   	Output o1;
//   	o1.Schedule[0] = 0;
//   	o1.Schedule[1] = 30;
//   	o1.Schedule[2] = 2;
//   	o1.Schedule[3] = 20;
//   	o1.Schedule[4] = 0;
//   	o1.Schedule[5] = 0;
//   	o1.Schedule[6] = 0;
//   	o1.Schedule[7] = 0;
//   	o1.Output_ID = 1;
//   	o1.Type = 1;
//Base.Update_Output(o2,2);
//   	Output o2;
//   	o2.Schedule[0] = 5;
//   	o2.Schedule[1] = 5;
//   	o2.Schedule[2] = 6;
//   	o2.Schedule[3] = 30;
//   	o2.Schedule[4] = 23;
//   	o2.Schedule[5] = 55;
//   	o2.Schedule[6] = 0;
//   	o2.Schedule[7] = 0;
//   	o2.Output_ID = 3;
//   	o2.Type = 2;
//
//   	Output o3;
//   	o3.Schedule[0] = 0;
//   	o3.Schedule[1] = 30;
//   	o3.Schedule[2] = 2;
//   	o3.Schedule[3] = 20;
//   	o3.Schedule[4] = 0;
//   	o3.Schedule[5] = 0;
//   	o3.Schedule[6] = 0;
//   	o3.Schedule[7] = 30;
//   	o3.Output_ID = 3;
//   	o3.Type = 0;
//
//   	char n1[] = "530787836";
//   	char n2[] = "123456789";
//   	char n3[] = "999887771";

//   	FEE_Write_Settings();
//   	Base.Add_User(u1);
//   	Base.Add_User(u2);
//   	Base.Add_Sensor(s1);
//   	Base.Add_Sensor(s2);
//   	Base.Add_Output(o1);
//   	Base.Add_Output(o2);
//   	Base.Add_GSM(n1,"0");
//   	Base.Add_GSM(n2,"0");



//   	Base.Update_User(u3,1);
//   	Base.Update_User(u2,2);
//   	Base.Update_Sensor(s3,1);
//   	Base.Update_Sensor(s2,2);
//   	Base.Update_Output(o3,3);
//   	Base.Update_Output(o2,2);
//   	Base.Update_GSM(n3,n2);
//   	Base.Update_GSM(n2,"0");

   	//    uint8_t mem1 = 0;
//    trace_printf("%d\n",mem1);
//    mem1 = FEE_ReadDataByte(1);
//    trace_printf("%d\n",mem1);
//    FEE_WriteDataByte(1,123);
//    FEE_WriteDataByte(2,456);
//    mem1 = FEE_ReadDataByte(1);
//    trace_printf("%d\n",mem1);
//    if(FEE_ReadDataByte(1) == mem1)
//    	FEE_Erase();
// ----------------------------------------------------------------------------
