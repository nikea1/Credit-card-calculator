#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Calculate how many months until credit card bill is payed off
//Assuming no more credit card charges at this point
//This is just a rough estimate 

int main(){
	
	time_t currentTime;
	time(&currentTime);
	

	struct tm *myTime = localtime(&currentTime);
	printf("%d/%d/%d\n", myTime->tm_mon + 1, myTime->tm_mday, myTime->tm_year + 1900);

	float money_owed = 1240.35, apr = -1, pay = 0, intrest, avg_money_owed;
	int flag = 0,days_in_year = 365, year, month, payperiod,billpay_day,end_of_pay_period, start_of_pay_period, num_months_til_payed_off = 0;

	int days_in_month [12] = {31,28,31,30,31,30,31, 31, 30,31,30,31};


	year = myTime->tm_year + 1900;
	//month = myTime->tm_mon;
	month = 0;
	
	//get amount to pay every pay period
	printf("Input amount owed to credit card: ");
	scanf("%f", &money_owed);
	printf("\n");
	
	//amount pay per month
	do{
	  printf("Input payment amount (must be more than 0): ");
	  scanf("%f", &pay);
	  printf("\n");
	}
	while(pay <= 0);

	//apr to find intrest
	do{
	  printf("Input current APR or interest rate in decimal format (Ex. 22.99%% would be 0.2299 in decimal format): ");
	  scanf("%f", &apr);
	  printf("\n");
	}while(apr < 0);

	//bill date
	do{
	  printf("Input date when bill is payed (Ex. If date is '%d/%d/%d' then input '%d'): \n", (month+1), myTime->tm_mday, year, myTime->tm_mday);
	  scanf("%d",&billpay_day);
	  printf("\n");
	}while(billpay_day < 0 && billpay_day > 32);

	//end of pay period
	do{
	  printf("Input end of pay period date (Ex. If date is '%d/%d/%d' then input '%d'): \n", (month+1), myTime->tm_mday, year, myTime->tm_mday);
	  scanf("%d", &end_of_pay_period);
	  printf("\n");
	}while(end_of_pay_period < 0 && end_of_pay_period > 32);

	start_of_pay_period = (end_of_pay_period+1)%31;

	while(money_owed > 0){
	  //if day of bill pay is the same as the start of the billing period
	  if(start_of_pay_period == billpay_day){
		
		money_owed -= pay;
		avg_money_owed = money_owed;
	  }
	  //if date of bill pay is less than start of pay period date
	  else if((start_of_pay_period) > billpay_day){
	  	avg_money_owed = money_owed*(days_in_month[month] - end_of_pay_period + billpay_day);
	  	money_owed -= pay;
	  	avg_money_owed += money_owed*(end_of_pay_period - billpay_day);
	  	avg_money_owed /= days_in_month[month];
	  }
	  //if date of bill pay is greater than start of pay period date
	  else{
	  	avg_money_owed = money_owed*(billpay_day - end_of_pay_period );
	  	money_owed -= pay;
	  	avg_money_owed += money_owed*(days_in_month[month] - billpay_day + end_of_pay_period);
	  	avg_money_owed /= days_in_month[month];
	  }


	 // printf("The new amount is $%.2f\n", money_owed);
	 // printf("The avg amount is $%.2f\n", avg_money_owed);

	  if(money_owed > 0){
	  //calculate intrest
	  payperiod = days_in_month[month];

	  //if leap year
	  if((year%100)%4==0){
	  	days_in_year = 366;
	  	if(month == 1){
		  payperiod+=1;
	    }
	  }
	  else{
	  	days_in_year = 365;
	  }

	 // printf("Payperiod is %d\n", payperiod);
	 // printf("APR is %f\n", apr);

	  intrest = avg_money_owed * payperiod * apr / days_in_year;

	 // printf("The intrest is $%.2f\n", intrest);

	  if(intrest >= pay){
		printf("The amount given is not enough to pay back credit card.\n");
		flag = 1;
		break;
	  }

	  money_owed += intrest;

	 //  printf("The new amount w/ intrest is $%.2f\n", money_owed);
	}
	else{
		break;
	}

	  num_months_til_payed_off++;
	  month++;
	  
	  //keep track of years for leap year check
	  month%=12;
	  if(month == 0){
		year++;
	  }


	}//end of while loop
	if(flag == 0)
		printf("It would take about %d month(s) to completely pay off the credit card\n", num_months_til_payed_off);


	return 0;
}