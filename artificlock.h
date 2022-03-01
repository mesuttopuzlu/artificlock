/**
 * @file        artificlock.h
 * @author      Mesut Topuzlu
 * @version     1.0.0
 * @copyright   GNU Public License v2.0
 * @brief       This file is header file to artificlock.c
 *              and contains symbolic constants, options, type-aliases and function declarations.
 */

#ifndef ARTIFICLOCK_H_
#define ARTIFICLOCK_H_

//------------- symbolic consts -------------
#define Jan   1
#define Feb   2
#define Mar   3
#define Apr   4
#define May   5
#define Jun   6
#define Jul   7
#define Aug   8
#define Sept  9
#define Oct   10
#define Nov   11
#define Dec   12

#ifndef TRUE 
#define TRUE  1
#else
#warning TRUE has already defined!
#endif

#ifndef FALSE 
#define FALSE  1
#else
#warning FALSE has already defined!
#endif

//-------------------- options -------------------
#ifndef PRINT_ON 
#define PRINT_ON    0   /**< This option is used for enabling/disabling debug print. 
                             If you want to see error or warning messages thoose related to date/time checking just change 0 to 1 */
#else
#warning PRINT_ON has already defined!
#endif

//----------------- type aliases -----------------
typedef unsigned char FLAG; /**< This type-alias represents flag that changes in only 0 to 1 or 1 to 0. */

 /**
  * A structure to represent date and time.
  */
typedef struct _date_time {
    unsigned char second;       /**< It represents second that changes in 0 to 59 */
    unsigned char minute;       /**< It represents minute that changes in 0 to 59 */
    unsigned char hour24;       /**< It represents hour that changes in 0 to 23 */
    unsigned char dayOfMonth;   /**< It represents day of month that changes in 1 to 31(max) */
    unsigned char month;        /**< It represents month that changes in 1 to 12 */
    unsigned short year;        /**< It represents year that is minimum 1970 */
}date_time; 

//-------------- function decls -----------------
/**
 * @brief   This function checks if argument valid or not and set February days according to common or leap year.
 *          If the year is leap year February is set to 29 otherwise (for common year) 28.
 *          In addition, checks if argument is NULL or not.
 * @param   dt An read-only instance of date_time struct.
 * @return  Returns 1 if argument is not equal to NULL and date/time is valid otherwise returns 0.
 */
int init_time(const date_time *dt);

/**
 * @brief   This function increases argument's seconds value. When second reach max,  
 *          it is cleared and minute is increased one. The others are same.
 * @param   dt An instance of date_time struct.
 */
void tick_time(date_time *dt);

#endif /* ARTIFICLOCK_H_ */
