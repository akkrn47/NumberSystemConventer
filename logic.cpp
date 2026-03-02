#include "logic.h"

void doConvertation(AppContext* context){
    int signInStr = NO;
    int len = strlen(context->initialValueFromLineEdit);
    if ((context->initialValueFromLineEdit[0] == '+') || (context->initialValueFromLineEdit[0] == '-'))
        signInStr = YES;

    context->result = strtol(context->initialValueFromLineEdit, NULL, context->currentNumSystem);
    int strDuplicate = context->result;

    if (context->currentNumSystem == context->toNumSystem){
        context->resultStr[0] = '\0';
        strcpy(context->resultStr, context->initialValueFromLineEdit);
        if ((context->initialValueFromLineEdit[0] == '+')){
            int i = 0;
            while (context->resultStr[i]){
                context->resultStr[i] = context->resultStr[i + 1];
                i++;
            }
            removeInsignificantZeros(context);
        }

        if (context->initialValueFromLineEdit[0] == '-'){
            int i = 0;
            while (context->resultStr[i]){
                context->resultStr[i] = context->resultStr[i + 1];
                i++;
            }
            removeInsignificantZeros(context);
            addMinusToStr(context);
        }
        removeInsignificantZeros(context);

    }

    else if (strDuplicate == 0 && context->initialValueFromLineEdit[0] != '\0'){ // Если пользователь ввёл нулевую строку
        context->resultStr[0] = '0';
        context->resultStr[1] = '\0';
    }

    else if (context->initialValueFromLineEdit[0] == '\0')
        context->resultStr[0] = '\0';

    else{
        if (context->initialValueFromLineEdit[0] == '-')
            strDuplicate = (unsigned) strDuplicate;
        while (strDuplicate){
            char curNum[2] = "";
            curNum[0] = ALPHABET[strDuplicate % context->toNumSystem];
            strcat(context->resultStr, curNum);
            strDuplicate = strDuplicate/context->toNumSystem;
        }
        strrev(context->resultStr);
    }


    if ((len == 1) && (signInStr == YES)){
        context->resultStr[0] = '\0';
    }

}


void doValidation(AppContext* context){
    int startIndex = 0;
    context->longLongStr = strtoll(context->initialValueFromLineEdit, NULL, context->currentNumSystem);
    if((context->initialValueFromLineEdit[0] == '-' || context->initialValueFromLineEdit[0] == '+') && (context->currentNumSystem == 10)){
        startIndex++;
        context->inputStatus = CORRECT_INPUT;
    }
    for (int i = startIndex; context->initialValueFromLineEdit[i]; i++){
        short currentElemChecking = INCORRECT_INPUT;
        for(int j = 0; j < context->currentNumSystem; j++){
            if (context->initialValueFromLineEdit[i] == ALPHABET[j]){
                currentElemChecking = CORRECT_INPUT;

            }
        }
        doOverFlowChecking(context);
        if ((currentElemChecking == INCORRECT_INPUT) || (context->overFlowState == YES) || (context->currentNumSystem == 0) || (context->toNumSystem == 0)){
            context->inputStatus = INCORRECT_INPUT;
            break;
        } 
    }
    if (((context->currentNumSystem == 0) || (context->toNumSystem == 0)))
        context->inputStatus = CORRECT_INPUT;

}

void doInitialization(AppContext* context){
    context->inputStatus = CORRECT_INPUT;
    context->overFlowState = NO;
    free(context->resultStr);
    context->resultStr =(char*) calloc (MAX_SIZE, sizeof(char));
    context->initialValueFromLineEdit[0] = '\0';
    context->serviceStr[0] = '\0';
}

void doOverFlowChecking(AppContext* context){
    if (((context->longLongStr > LONG_MAX) || (context->longLongStr < LONG_MIN)) && context->currentNumSystem != 2)
        context->overFlowState = YES;
    if ((context->currentNumSystem == 8) && (strlen(context->initialValueFromLineEdit) == 11) && (context->initialValueFromLineEdit[0] == '3'))
        context->overFlowState = NO;
    if ((context->currentNumSystem == 0) || (context->toNumSystem == 0))
        context->overFlowState = NO;

}

void removeInsignificantZeros(AppContext* context){
    int firstNotZeroElemIndex = 0;
    int index = 0;
    int j = 0;
    for (int i = 0; context->resultStr[i] == '0'; i++){
        firstNotZeroElemIndex = firstNotZeroElemIndex + 1;
    }
    index = firstNotZeroElemIndex;
    if (strlen(context->resultStr) == index){
        context->resultStr[0] = '0';
        context->resultStr[1] = '\0';
    }
    else{
        for (int i = index; context->resultStr[i] != '\0'; i++){
            context->resultStr[j] = context->resultStr[i];
            j = j+1;
        }
        context->resultStr[j] = '\0';

    }

}

void doConvertationFromBinCode(AppContext *context){

    char localServiceStr[MAX_SIZE] = "\0";
    if (context->currentNumSystem == 2)
        strcat_s(context->serviceStr, context->initialValueFromLineEdit);

    strcat_s(localServiceStr, context->serviceStr);
    context->serviceStr[0] = '\0';
    int len = DEFAULT_VALUE;
    for (int i = 0; localServiceStr[i]; i++){
        if ((localServiceStr[i]) != '\0')
            len++;
    }
    if ((len == 32) && (localServiceStr[0] == '1') && (context->currentNumSystem != context->toNumSystem)){
        for (int i = 0; i < len; i++){
            if (localServiceStr[i] == '1')
                localServiceStr[i] = '0';
            else
                localServiceStr[i] = '1';
        }
        int oneWasInsertedСhecker = WAS_NOT_INSERTED;
        for (int i = len - 1; i >= 0; i--){
            if ((localServiceStr[i] == '0') && (oneWasInsertedСhecker == WAS_NOT_INSERTED)){
                localServiceStr[i] = '1';
                oneWasInsertedСhecker = WAS_INSERTED;
                break;
            }
            else if (localServiceStr[i] == '1' && oneWasInsertedСhecker == WAS_NOT_INSERTED)
                localServiceStr[i] = '0';
        }
        if (oneWasInsertedСhecker == WAS_NOT_INSERTED){
            memmove(localServiceStr + 1, localServiceStr, len+1);
            localServiceStr[0] = '1';
        }


        int newStr = strtol(localServiceStr, NULL, context->currentNumSystem);
        char strInDecimalSystem[MAX_SIZE + 1] = "\0";
        strInDecimalSystem[0] = '-';
        char resultStrWithoutMinus[MAX_SIZE] = "\0";
        snprintf(resultStrWithoutMinus, sizeof(resultStrWithoutMinus), "%d", newStr);
        strcat(strInDecimalSystem, resultStrWithoutMinus);

        free(context->resultStr);
        context->resultStr = (char*) calloc (MAX_SIZE+1, sizeof(char));

        if (context->toNumSystem == 10)
            strcat(context->resultStr, strInDecimalSystem);

        else{
            int intStrInDecimalSystem = strtol(strInDecimalSystem, NULL, 10);
            int unsStr = (unsigned) intStrInDecimalSystem;
            while (unsStr){
                char curNum[2] = "";
                snprintf(curNum, sizeof(curNum), "%d", (unsStr % context->toNumSystem));
                strcat(context->resultStr, curNum);
                unsStr = unsStr/context->toNumSystem;

            }
            strrev(context->resultStr);
        }

    }

}

void doConvertionEightSystemToBinCode(AppContext* context){
    char* triads[TRIADS_SIZE] = {"000", "001", "010", "011", "100", "101", "110", "111"};

    for (int i = 0; context->initialValueFromLineEdit[i]; i++){
        char curNumInTriads[4] = "\0";
        char symbolFromStr[2] = "\0";
        symbolFromStr[0] = context->initialValueFromLineEdit[i];
        int symbolFromStrToInt = strtol(symbolFromStr,NULL,8);

        strcat_s(curNumInTriads, *(triads + symbolFromStrToInt));
        strcat_s(context->serviceStr, curNumInTriads);


    }

    int firstNoZeroIndex = 0;
    int index = 0;
    int j = 0;
    for (int i = 0; context->serviceStr[i] == '0'; i++){
        firstNoZeroIndex = firstNoZeroIndex + 1;
    }
    index = firstNoZeroIndex;
    if (strlen(context->serviceStr) == index){
        context->serviceStr[0] = '0';
        context->serviceStr[1] = '\0';
    }
    else{
        for (int i = index; context->serviceStr[i] != '\0'; i++){
            context->serviceStr[j] = context->serviceStr[i];
            j = j + 1;
        }
        context->serviceStr[j] = '\0';
    }

}

void saveStrInBuffer(AppContext *context){
    int len = DEFAULT_VALUE;
    strcat(context->bufStr, context->resultStr);
    for(int i = 0; context->bufStr[i];i++)
        if(context->bufStr[i])
            len++;
    len++;
    HANDLE hmem = GlobalAlloc(GMEM_MOVEABLE, len);
    char *pmem = (char*) GlobalLock(hmem);
    strcpy_s(pmem, len, context->bufStr);
    GlobalUnlock(hmem);
    if (OpenClipboard(NULL)) {
        EmptyClipboard();
        if (SetClipboardData(CF_TEXT, hmem))
            hmem = NULL;
        CloseClipboard();
    }
    GlobalFree(hmem);
}

void addMinusToStr(AppContext *context){
    char servStr[MAX_SIZE] = "\0";
    strcat(servStr, context->resultStr);
    context->resultStr[1] = '\0';
    int i = 0;
    while (context->resultStr[i]){
        context->resultStr[i] = '\0';
        i = i + 1;
    }
    context->resultStr[0] = '-';
    strcat(context->resultStr, servStr);
    //printf("%s", context->resultStr);
}

void checkConditionsToConvert(AppContext *context){
    context->conditionsCompliance = NO;
    if ((context->currentNumSystem != 0) && (context->toNumSystem != 0) && (context->inputStatus == CORRECT_INPUT) && (context->initialValueFromLineEdit[0] != '\0'))
        context->conditionsCompliance = YES;
}

void checkEightDopCode(AppContext *context){
    context->conditionsCompliance = NO;
    if ((context->serviceStr[0] == '1') && (context->serviceStr[1] == '1') && (strlen(context->serviceStr) == 32))
        context->conditionsCompliance = YES;
}


void checkStrIsEmpty(AppContext *context){
    context->strIsEmpty = NO;
    if (context->initialValueFromLineEdit[0] == '\0')
        context->strIsEmpty = YES;
}


void checkInputIsIncorrect(AppContext *context){
    context->strIsIncorrect = NO;
    if (context->inputStatus == INCORRECT_INPUT)
        context->strIsIncorrect = YES;
}

void checkNumSystemsIsNotDefined(AppContext *context){
    context->numSystemsIsNotDefined = NO;
    if ((context->currentNumSystem == 0) || (context->toNumSystem == 0))
        context->numSystemsIsNotDefined = YES;
}

void checkStrIsIncorrect(AppContext *context){
    context->strIsIncorrect = NO;
    if ((context->inputStatus == INCORRECT_INPUT) || (context->overFlowState == YES))
        context->strIsIncorrect = YES;
}




