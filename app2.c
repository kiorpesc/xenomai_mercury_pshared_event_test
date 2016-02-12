#include <alchemy/event.h>
#include <alchemy/task.h>
#include <errno.h>
#include <stdio.h>


// app2: open the shared event and loop until killed, signalling the event once per second
int main(void) {
	int eRc;
	unsigned int temp_flags;
	RT_EVENT hEventHandle;

	// bind the existing event	
	eRc = rt_event_bind(&hEventHandle, "MYTEST", TM_NONBLOCK);
	if (eRc)
	{
		printf("Failed to open event\n");
		return 2;
	}

	printf("Entering loop\n");
	while(1)
	{
		// sleep one second
		eRc = rt_task_sleep((RTIME)1000000000);
		if (eRc)
		{
			printf("Sleep problem\n");
			break;
		}
		
		// set the event
		printf("Setting event\n");
		eRc = rt_event_signal(&hEventHandle, 0x1);
		if (eRc)
		{
			printf("Error setting event\n");
			break;
		}
	}


	return 0;
}
