#include "drivers/Driver.h"

void Driver::setDataInvalid() {
    this->dataValid = false;
}

void Driver::setDataValid() {
    this->dataValid = true;
}

bool Driver::isDataValid() {
    return this->dataValid;
}

