/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Winter 2019-2020                                     */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
    NONE_CMD = -2,
    COMMENT_CMD = -1,
    INIT_CMD = 0,
    ADDCOURSE_CMD = 1,
    REMOVECOURSE_CMD = 2,
    WATCHCLASS_CMD = 3,
    TIMEVIEWED_CMD = 4,
    GETMOSTVIEWEDCLASSES_CMD = 5,
    QUIT_CMD = 6
} commandType;

static const int numActions = 9;
static const char *commandStr[] = {
        "Init",
        "AddCourse",
        "RemoveCourse",
        "WatchClass",
        "TimeViewed",
        "GetMostViewedClasses",
        "Quit" };

static const char* ReturnValToStr(int val) {
    switch (val) {
        case SUCCESS:
            return "SUCCESS";
        case ALLOCATION_ERROR:
            return "ALLOCATION_ERROR";
        case FAILURE:
            return "FAILURE";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        default:
            return "";
    }
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
    error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString,ErrorParams) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString, ErrorParams); return error; }

static bool isInit = false;

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {

    char buffer[MAX_STRING_INPUT_SIZE];

    // Reading commands
    while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
        fflush(stdout);
        if (parser(buffer) == error)
            break;
    };
    return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
                                const char** const command_arg) {
    if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
        return (NONE_CMD);
    if (StrCmp("#", command)) {
        if (strlen(command) > 1)
            printf("%s", command);
        return (COMMENT_CMD);
    };
    for (int index = 0; index < numActions; index++) {
        if (StrCmp(commandStr[index], command)) {
            *command_arg = command + strlen(commandStr[index]) + 1;
            return ((commandType)index);
        };
    };
    return (NONE_CMD);
}

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddCourse(void* DS, const char* const command);
static errorType OnRemoveCourse(void* DS, const char* const command);
static errorType OnWatchClass(void* DS, const char* const command);
static errorType OnTimeViewed(void* DS, const char* const command);
static errorType OnGetMostViewedClasses(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) {
    static void *DS = NULL; /* The general data structure */
    const char* command_args = NULL;
    errorType rtn_val = error;

    commandType command_val = CheckCommand(command, &command_args);

    switch (command_val) {

        case (INIT_CMD):
            rtn_val = OnInit(&DS, command_args);
            break;
        case (ADDCOURSE_CMD):
            rtn_val = OnAddCourse(DS, command_args);
            break;
        case (REMOVECOURSE_CMD):
            rtn_val = OnRemoveCourse(DS, command_args);
            break;
        case (WATCHCLASS_CMD):
            rtn_val = OnWatchClass(DS, command_args);
            break;
        case (TIMEVIEWED_CMD):
            rtn_val = OnTimeViewed(DS, command_args);
            break;
        case (GETMOSTVIEWEDCLASSES_CMD):
            rtn_val = OnGetMostViewedClasses(DS, command_args);
            break;
        case (QUIT_CMD):
            rtn_val = OnQuit(&DS, command_args);
            break;

        case (COMMENT_CMD):
            rtn_val = error_free;
            break;
        case (NONE_CMD):
            rtn_val = error;
            break;
        default:
            assert(false);
            break;
    };
    return (rtn_val);
}

static errorType OnInit(void** DS, const char* const command) {
    if (isInit) {
        printf("init was already called.\n");
        return (error_free);
    };
    isInit = true;

    ValidateRead(0, 0, "%s failed.\n", commandStr[INIT_CMD]);
    *DS = Init();

    if (*DS == NULL) {
        printf("init failed.\n");
        return error;
    };

    printf("init done.\n");
    return error_free;
}

static errorType OnAddCourse(void* DS, const char* const command) {
    int courseID, numOfClasses;
    ValidateRead(sscanf(command, "%d %d", &courseID, &numOfClasses), 2, "%s failed.\n", commandStr[ADDCOURSE_CMD]);
    StatusType res = AddCourse(DS, courseID, numOfClasses);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[ADDCOURSE_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[ADDCOURSE_CMD], ReturnValToStr(res));
    return error_free;
}

static errorType OnRemoveCourse(void* DS, const char* const command) {
    int courseID;
    ValidateRead(sscanf(command, "%d", &courseID), 1, "%s failed.\n", commandStr[REMOVECOURSE_CMD]);
    StatusType res = RemoveCourse(DS, courseID);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[REMOVECOURSE_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[REMOVECOURSE_CMD], ReturnValToStr(res));
    return error_free;
}

static errorType OnWatchClass(void* DS, const char* const command) {
    int courseID, classID, time;
    ValidateRead(sscanf(command, "%d %d %d", &courseID, &classID, &time), 3, "%s failed.\n", commandStr[WATCHCLASS_CMD]);
    StatusType res = WatchClass(DS, courseID, classID, time);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[WATCHCLASS_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[WATCHCLASS_CMD], ReturnValToStr(res));
    return error_free;
}

static errorType OnTimeViewed(void* DS, const char* const command) {
    int courseID, classID, timeViewed;
    ValidateRead(sscanf(command, "%d %d", &courseID, &classID), 2, "%s failed.\n", commandStr[TIMEVIEWED_CMD]);
    StatusType res = TimeViewed(DS, courseID, classID, &timeViewed);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[TIMEVIEWED_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %d\n", commandStr[TIMEVIEWED_CMD], timeViewed);
    return error_free;
}

static errorType OnGetMostViewedClasses(void* DS, const char* const command) {
    int numOfClasses;
    int *courses = NULL, *classes = NULL;
    StatusType res = SUCCESS;

    ValidateRead(sscanf(command, "%d", &numOfClasses), 1, "%s failed.\n", commandStr[GETMOSTVIEWEDCLASSES_CMD]);
    if (numOfClasses > 0) {
        courses = (int *)malloc(numOfClasses * sizeof(int));
        classes = (int *)malloc(numOfClasses * sizeof(int));
        if (courses == NULL || classes == NULL) {
            res = ALLOCATION_ERROR;
        }
    }

    if (res != ALLOCATION_ERROR) {
        res = GetMostViewedClasses(DS, numOfClasses, courses, classes);
    }

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[GETMOSTVIEWEDCLASSES_CMD], ReturnValToStr(res));
        if (courses != NULL) free(courses);
        if (classes != NULL) free(classes);
        return error_free;
    }

    printf("%s: %s\n", commandStr[GETMOSTVIEWEDCLASSES_CMD], ReturnValToStr(res));

    printf("Course\t|\tClass\n");

    for (int i = 0; i < numOfClasses; i++)
    {
        printf("%d\t|\t%d\n", courses[i], classes[i]);
    }

    printf("--End of most viewed classes--\n");

    if (courses != NULL) free(courses);
    if (classes != NULL) free(classes);

    return error_free;
}

static errorType OnQuit(void** DS, const char* const command) {
    Quit(DS);
    if (*DS != NULL) {
        printf("quit failed.\n");
        return error;
    };

    isInit = false;
    printf("quit done.\n");
    return error_free;
}

#ifdef __cplusplus
}
#endif