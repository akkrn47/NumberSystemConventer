#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"


enum Operation{
    Initialization,
    Validation,
    Convertion,
    ConvertionFromBinCode,
    ConvertionEightSystemToBinCode,
    Save,
    CheckingConditionsForConvertion,
    CheckingEightSystemNumberIsDopCode,
    CheckingStrIsEmpty,
    CheckingInputIsIncorrect,
    CheckingNumSystemsIsNotDefined,
    CheckingStrIsIncorrect

};

void doOperation(Operation operation, AppContext* context);

#endif // ENTRYPOINT_H
