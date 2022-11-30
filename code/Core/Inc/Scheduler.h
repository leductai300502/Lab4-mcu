/*
 * Scheduler.h
 *
 *  Created on: Nov 30, 2022
 *      Author: ASUS
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"
typedef struct{

	void (* pTask)(void);

	uint32_t Delay;

	uint32_t Period;

	uint8_t RunMe;

	uint32_t TaskID;
	uint32_t Prev_ID;

	uint32_t Next_ID;

}sTask;
#define MAX_TASK  40
void SCH_Init(void);

//void SCH_Delete_Task(uint32_t TASK_IDX);

void SCH_Add_Task(void(* pFunction)(), uint32_t DELAY, uint32_t PERIOD);

void SCH_Update(void);

void SCH_Dispatch_Task(void);


#endif /* INC_SCHEDULER_H_ */
