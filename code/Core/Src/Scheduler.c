/*
 * Scheduler.c
 *
 *  Created on: Nov 30, 2022
 *      Author: ASUS
 */
#include "Scheduler.h"
#include "stm32f1xx_hal.h"
#include "string.h"

sTask SCH_TASK[MAX_TASK];

uint8_t current_index_task = 0;
int Head=0;
int Tail=0;
//static unsigned char SCH_Reset_Task(const int TASK_IDX)
//{
//	unsigned char Return_code;
//
//	if(SCH_TASK[TASK_IDX].pTask==0)
//	{
//		Errorcode= ERROR_SCH_CANNOT_DELETE_TASK;
//		return ERROR;
//	}
//	else{
//		Return_code= NORMAL;
//	}
//
//	SCH_TASK[TASK_IDX].pTask = 0x0000;
//	SCH_TASK[TASK_IDX].Delay = 0;
//	SCH_TASK[TASK_IDX].Period = 0;
//	SCH_TASK[TASK_IDX].RunMe = 0;
//
//	return Return_code;
//}
void SCH_Init(void){
	Head =0;
	Tail =0;
	current_index_task = 0;

	unsigned char i;

		for(i=0; i < MAX_TASK ; i++)
		{
			SCH_TASK[i].TaskID=i;
			SCH_TASK[i].Prev_ID = i-1;
			SCH_TASK[i].Next_ID= i+1;
		}
}
void SCH_Add_Task(void (pFunction)() , uint32_t DELAY , uint32_t PERIOD ){
	if(current_index_task < MAX_TASK)
	{
		SCH_TASK[current_index_task].pTask = pFunction;
		SCH_TASK[current_index_task].Delay = DELAY;
		SCH_TASK[current_index_task].Period = PERIOD;
		SCH_TASK[current_index_task].RunMe = 0;

//		SCH_TASK[current_index_task].TaskID = current_index_task;
		current_index_task++;
	}
}
void SCH_Update(void){
	for(int i =0 ; i<current_index_task ; i++)
	{
		if(SCH_TASK[i].Delay > 0)
		{
			SCH_TASK[i].Delay --;
		}
		else{
			SCH_TASK[i].Delay = SCH_TASK[i].Period;
			SCH_TASK[i].RunMe += 1;
		}
	}
}
void SCH_Dispatch_Task(void){
	for(int i =0 ; i< current_index_task ; i++)
	{
		if(SCH_TASK[i].RunMe > 0)
		{
			SCH_TASK[i].RunMe --;
			(*SCH_TASK[i].pTask)();
			if( SCH_TASK[i].Period == 0){
				SCH_Delete_Task(SCH_TASK[i].TaskID);
			}

		}
	}
}
//void SCH_Delete_Task(uint32_t TASK_IDX){
//	unsigned char Return_code;
//
//		Return_code = SCH_Reset_Task(TASK_IDX);
//
//		if(Return_code==NORMAL)
//		{
//			current_index_task--;
//
//			if(Tail==Head)return Return_code;
//
//			if(Tail==TASK_IDX)
//			{
//				Tail=SCH_TASK[TASK_IDX].Prev_ID;
//				return Return_code;
//			}
//
//			if(Head==TASK_IDX)
//			{
//				Head=SCH_TASK[TASK_IDX].Next_ID;
//				SCH_TASK[Head].Prev_ID=-1;
//			}
//			else
//			{
//				SCH_TASK[SCH_TASK[TASK_IDX].Prev_ID].Next_ID=SCH_TASK[TASK_IDX].Next_ID;
//				SCH_TASK[SCH_TASK[TASK_IDX].Next_ID].Prev_ID=SCH_TASK[TASK_IDX].Prev_ID;
//			}
//
//			SCH_TASK[TASK_IDX].Next_ID=SCH_TASK[Tail].Next_ID;
//			SCH_TASK[SCH_TASK[TASK_IDX].Next_ID].Prev_ID=TASK_IDX;
//			SCH_TASK[TASK_IDX].Prev_ID=Tail;
//			SCH_TASK[Tail].Next_ID=TASK_IDX;
//		}
//
//		return Return_code;
//}
