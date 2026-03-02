#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <stdlib.h>


#define MAX_SIZE 33
#define CORRECT_INPUT 1
#define INCORRECT_INPUT 0
#define YES 1
#define NO 0
#define CONST_BASE10 10
#define DEFAULT_VALUE 0
#define WAS_NOT_INSERTED 0
#define WAS_INSERTED 1
#define TRIADS_SIZE 9



struct AppContext{
    long result = DEFAULT_VALUE;
    char initialValueFromLineEdit[MAX_SIZE] = "\0";
    char serviceStr[MAX_SIZE + 1] = "\0";
    short inputStatus = CORRECT_INPUT;
    short overFlowState = NO;
    short conditionsCompliance = NO;
    unsigned currentNumSystem = 0;
    unsigned toNumSystem = 0;
    unsigned constForBase10 = CONST_BASE10;
    char* resultStr = (char*) calloc(1, sizeof(char*));
    long long longLongStr = 0;
    char bufStr[MAX_SIZE] = "\0";

    short strIsEmpty = NO;
    short inputIsIncorrect = NO;
    short numSystemsIsNotDefined = NO;
    short strIsIncorrect = NO;


};

struct InterfaceElementsState{
    short fromNumSystemButtonSelected = NO;
    short toNumSystemButtonSelected = NO;
    short textInInputFieldEntered = NO;
};


#endif // APPCONTEXT_H
