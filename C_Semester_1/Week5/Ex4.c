#include <stdio.h>
int main()
{
	int secs = 0;
	int mins = 0;
	int hours = 0;
    scanf("%d:%d:%d", &hours, &mins, &secs);

	if(hours < 10)
	{
		if (mins <= 58 && secs == 59)
		{
			printf("0%d:%d:00",hours,mins+1);
		}
		else if(mins >= 60 || secs >= 60)
		{
			printf("The time isn't valid");
		}
		else if (mins == 59 && secs == 59 && hours < 9)
		{
			printf("0%d:00:00",hours+1);
		}
		else if (mins == 59 && secs == 59 && hours == 9)
		{
			printf("%d:00:00",hours+1);
		}
		else if(secs < 59)
		{
			printf("0%d:%d:%d",hours,mins,secs+1);
		}
	}
	else if (hours >= 10 && hours<=23)
	{
		if (mins <= 58 && secs == 59)
		{
			printf("%d:%d:00",hours,mins+1);
		}
		else if(mins >= 60 || secs >= 60)
		{
			printf("The time isn't valid");
		}
		else if (mins == 59 && secs == 59 && hours == 23)
		{
			printf("00:00:00");
		}
		else if (mins == 59 && secs == 59)
		{
			printf("%d:00:00",hours+1);
		}
		else if(secs < 59)
		{
			printf("%d:%d:%d",hours,mins,secs+1);
		}
	}
	else
	{
		printf("The time isn't valid");
	}
    return 0;
}
