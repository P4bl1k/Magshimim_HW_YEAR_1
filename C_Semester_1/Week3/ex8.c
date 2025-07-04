#include <stdio.h>

#define HOURS_PER_DAY 8.5  
#define DAYS_PER_MONTH 20  
#define PAYMENT_PER_HOUR 32.3  
#define MONTHS_PER_YEAR 12 

int main()
{
	
	const float NIS_TO_EURO = 3.96;
	const float FRANCE_DAYS = DAYS_PER_MONTH+4;
    float daily_salary = HOURS_PER_DAY * PAYMENT_PER_HOUR;      
    float monthly_salary = daily_salary * DAYS_PER_MONTH;
    float yearly_salary = monthly_salary * MONTHS_PER_YEAR;  

    printf("His salary in Israel:%.2f\n", yearly_salary);
    printf("His Salary in France Is:%.2f",(((yearly_salary/DAYS_PER_MONTH)*FRANCE_DAYS)/NIS_TO_EURO));

    return 0;
	
}
