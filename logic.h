#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>

#define ALPHABET "0123456789ABCDEF"

void doValidation(AppContext* context);
void doInitialization(AppContext* context);
void doConvertation(AppContext* context);
void doOverFlowChecking(AppContext* context);
void doConvertationFromBinCode(AppContext* context);
void doConvertionEightSystemToBinCode(AppContext* context);
void removeInsignificantZeros(AppContext* context);
void saveStrInBuffer(AppContext* context);
void addMinusToStr(AppContext* context);
void checkConditionsToConvert(AppContext* context);
void checkEightDopCode(AppContext* context);

void checkStrIsEmpty(AppContext* context);
void checkInputIsIncorrect(AppContext* context);
void checkNumSystemsIsNotDefined(AppContext* context);
void checkStrIsIncorrect(AppContext* context);

#endif // LOGIC_H

