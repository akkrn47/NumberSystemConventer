#include "entrypoint.h"
#include "logic.h"

void doOperation(Operation operation, AppContext* context){
    switch(operation){
    case Initialization:
        doInitialization(context);
        break;
    case Validation:
        doValidation(context);
        break;
    case Convertion:
        doConvertation(context);
        break;
    case ConvertionFromBinCode:
        doConvertationFromBinCode(context);
        break;
    case ConvertionEightSystemToBinCode:
        doConvertionEightSystemToBinCode(context);
        break;
    case Save:
        saveStrInBuffer(context);
        break;
    case CheckingConditionsForConvertion:
        checkConditionsToConvert(context);
        break;
    case CheckingEightSystemNumberIsDopCode:
        checkEightDopCode(context);
        break;
    case CheckingStrIsEmpty:
        checkStrIsEmpty(context);
        break;
    case CheckingInputIsIncorrect:
        checkInputIsIncorrect(context);
        break;
    case CheckingNumSystemsIsNotDefined:
        checkNumSystemsIsNotDefined(context);
        break;
    case CheckingStrIsIncorrect:
        checkStrIsIncorrect(context);
        break;
    };
}
