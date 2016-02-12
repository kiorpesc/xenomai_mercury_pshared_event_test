#include <alchemy/event.h>
#include <errno.h>
#include <stdio.h>


// app1: create an event to be shared with app2
//   wait for app2 to signal the event
//   clear the event
//   rinse and repeat until killed
int main(void)
{
	int eRc;
	unsigned int temp_flags;
	RT_EVENT hEventHandle;

	// create the event
	eRc = rt_event_create(&hEventHandle, "MYTEST", 0, EV_PRIO);
	if (eRc)
	{
		printf("Failed to create event\n");
		return 2;
	}

	// reset the event
	eRc = rt_event_clear(&hEventHandle, 0xFFFFFFFu, &temp_flags);
	if (eRc)
	{
		printf("Problem with initial event clear\n");
		return 2;
	}

	printf("Created event, entering wait loop\n");

	while (1)    // loop until killed
	{
		// wait forever for the signal from app2
		eRc = rt_event_wait(&hEventHandle, 0x1, &temp_flags, EV_ALL, TM_INFINITE);
		if (eRc)
		{
			printf("Failure during wait!\n");
			break;
		}
		printf("Event signalled\n");

		// reset the event
		eRc = rt_event_clear(&hEventHandle, 0xFFFFFFFFu, &temp_flags);
		if (eRc)
		{
			printf("Unable to clear event\n");
			break;
		}
	}	

	return 0;
}



