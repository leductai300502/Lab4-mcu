/*
 * Scheduler.c
 *
 *  Created on: Nov 30, 2022
 *      Author: ASUS
 */
#include "Scheduler.h"
//#include "stm32f1xx_hal.h"
#include "string.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task;

// SCH_Init set current_index_task = 0
void SCH_Init()
{
	current_index_task =0;
}
// SCH_Add_Task add new task in SCH_tasks_G with SCH_tasks_G.length = current_index_task
void SCH_Add_Task ( void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){

		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period =  PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;


		current_index_task++;
	}
}
// SCH_Update refresh new delay time of task while timer interrupt and enable run Task when delay = 0
void SCH_Update(void) {

	for(int i = 0; i < current_index_task; i++){
			if (SCH_tasks_G[i].Delay > 0){
				SCH_tasks_G[i].Delay --;
			}else{
				SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
				SCH_tasks_G[i].RunMe += 1;
			}
		}
}
// SCH_Dispatch_Tasks run tasks
void SCH_Dispatch_Tasks(void){
	for(int i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();

			if (SCH_tasks_G[i].Period == 0) {
				SCH_Delete_Task(i);
			}
		}
	}
}

void SCH_Delete_Task(uint32_t taskID) {
	int i = 0;
	while (i < taskID) {
		i++;
	}
	for (; i < current_index_task; i++) {
		SCH_tasks_G[i] = SCH_tasks_G[i + 1];
		SCH_tasks_G[i].TaskID = i;
	}
	current_index_task--;
}
