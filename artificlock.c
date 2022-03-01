/**
 * @file        artificlock.c
 * @author      Mesut Topuzlu
 * @version     1.0.0
 * @copyright   GNU Public License v2.0
 * @brief       This file is a source file and contains some of function definitions.
 */

#include "artificlock.h"

#if PRINT_ON
#include <stdio.h>
#endif

//------------- symbolic consts -------------
#define SECOND_MIN     0
#define SECOND_MAX     59

#define MINUTE_MIN     0
#define MINUTE_MAX     59

#define HOUR_MIN       0
#define HOUR_MAX       23

#define DAY_MIN        1
#define DAY_MAX        31

#define MONTH_MIN      1
#define MONTH_MAX      12

#define YEAR_MIN       1000

#define FEB_28         28
#define FEB_29         29

//------------- static variables ---------------
static unsigned char months_of_year[MONTH_MAX] = {
    31, //Jan
    '?', //Feb (FEB_28 or FEB_29)
    31, //Mar
    30, //Apr
    31, //May
    30, //Jun
    31, //Jul
    31, //Aug
    30, //Sept
    31, //Oct
    30, //Nov
    31, //Dec
};

//------------- static func decls ---------------
static unsigned char is_leap_year(unsigned short year);
static void set_feb(unsigned short year);

int init_time(const date_time *dt)
{
    if(!dt){
#if PRINT_ON
        printf("Argument is NULL!\n");
#endif
        return 0;
    }
    
    if(!(SECOND_MIN <= dt->second && dt->second <= SECOND_MAX)){
#if PRINT_ON
        printf("Second is out of range (%u - %u)!\n", SECOND_MIN, SECOND_MAX);
#endif        
        return 0;
    }
    
    if(!(MINUTE_MIN <= dt->minute && dt->minute <= MINUTE_MAX)){
#if PRINT_ON
        printf("Minute is out of range (%u - %u)!\n", MINUTE_MIN, MINUTE_MAX);
#endif        
        return 0;
    }
    
    if(!(HOUR_MIN <= dt->hour24 && dt->hour24 <= HOUR_MAX)){
#if PRINT_ON
        printf("Hour is out of range (%u - %u)!\n", HOUR_MIN, HOUR_MAX);
#endif        
        return 0;
    }
    
    if(!(DAY_MIN <= dt->dayOfMonth && dt->dayOfMonth <= DAY_MAX)){
#if PRINT_ON
        printf("Day of month is out of range (%u - %u)!\n", DAY_MIN, DAY_MAX);
#endif        
        return 0;
    }
    
    if(!(DAY_MIN <= dt->dayOfMonth && dt->dayOfMonth <= DAY_MAX)){
#if PRINT_ON
        printf("Day of month is out of range (%u - %u)!\n", DAY_MIN, DAY_MAX);
#endif        
        return 0;
    }
    
    if(!(MONTH_MIN <= dt->month && dt->month <= MONTH_MAX)){
#if PRINT_ON
        printf("Month is out of range (%u - %u)!\n", MONTH_MIN, MONTH_MAX);
#endif        
        return 0;
    }
    
    if(!(YEAR_MIN <= dt->year)){
#if PRINT_ON
        printf("Year is out of range (%u - )!\n", YEAR_MIN);
#endif        
        return 0;
    }
    
    set_feb(dt->year);

    if(!(dt->dayOfMonth <= months_of_year[dt->month - 1])){
#if PRINT_ON
        printf("Day of month can not be %u for this month!\n", dt->dayOfMonth);
#endif
        return 0;
    }
    
    return 1;
}

void tick_time(date_time *dt)
{
    FLAG second_compl = 0;
    if(dt->second < SECOND_MAX){
        dt->second++;
    }
    else{
        dt->second = SECOND_MIN;
        second_compl = 1;
    }
    
    FLAG minute_compl = 0;
    if(second_compl)
    {
        if(dt->minute < MINUTE_MAX){
            dt->minute++;
        }
        else{
            dt->minute = MINUTE_MIN;
            minute_compl = 1;
        }
    }
    
    FLAG hour_compl = 0;
    if(minute_compl)
    {
        if(dt->hour24 < HOUR_MAX){
            dt->hour24++;
        }
        else{
            dt->hour24 = HOUR_MIN;
            hour_compl = 1;
        }
    }
    
    FLAG dayOfMonth_compl = 0;
    if(hour_compl)
    {
        if(dt->dayOfMonth < months_of_year[dt->month - 1]) {
            dt->dayOfMonth++;
        }
        else{
            dt->dayOfMonth = DAY_MIN;
            dayOfMonth_compl = 1;
        }
    }
    
    FLAG month_compl = 0;
    if(dayOfMonth_compl)
    {
        if(dt->month < MONTH_MAX){
            dt->month++;
        }
        else{
            dt->month = MONTH_MIN;
            month_compl = 1;
        }
    }
    
    if(month_compl)
    {
        dt->year++;
        set_feb(dt->year);
    }
}

static unsigned char is_leap_year(unsigned short year)
{
    if(year % 4 != 0){
        return 0;
    }
    
    if(year % 100 != 0){
        return 1;
    }
    
    if(year % 400 != 0){
        return 0;
    }
    
    if(year % 4000 != 0){
        return 1;
    }
    
    return 0;
}

static void set_feb(unsigned short year)
{
    if(!is_leap_year(year)){
        months_of_year[1] = FEB_28;
    }
    else{
        months_of_year[1] = FEB_29;
    }
}
