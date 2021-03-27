/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library.h                                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET1
#define _234218_WET1

#ifdef __cplusplus
extern "C" {
#endif

/* Return Values
 * ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;


void *Init();

StatusType AddCourse (void *DS, int courseID, int numOfClasses);

StatusType RemoveCourse(void *DS, int courseID);

StatusType WatchClass(void *DS, int courseID, int classID, int time);

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed);

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes);

void Quit(void** DS);

#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1 */