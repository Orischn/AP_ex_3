#include "settingsCommand.hpp"

AlgoSettingsCMD::AlgoSettingsCMD(DefaultIO* dio) {
    this->description = "algorithm settings";
    this->dio = dio;
}

AlgoSettingsCMD& AlgoSettingsCMD::getInstance(DefaultIO* dio) {
    if (!this) {
        return new AlgoSettingsCMD(dio);
    }
    return this;
}

int AlgoSettingsCMD::getK() {
    return k;
}

std::string AlgoSettingsCMD::getDistanceFunc() {
    return distanceFunc;
}

void AlgoSettingsCMD::execute() {
    dio->write("The current KNN parameters are: " + this->getK() + ", distance metric = " + this->getDistanceFunc() + "\n");
    while (true) {
        std::string input = dio->read();
        try {
            std::string kValueString = input.substr(0, input.find(' '));
            std::string distFuncString = input.substr(input.find(' ') + 1, input.length());
            int kValue = std::stoi(kValueString);
            if (kValue < 1 || kValue > 10) {
                dio->write("Invalid value for K");
                continue;
            }
            if (distanceFuncString.compare("CHE") != 0 && distanceFuncString.compare("MAN") != 0 && distanceFuncString.compare("EUC") != 0) {
                dio->write("Invalid value for distance function");
                continue;
            }
            this->k = kValue;
            this->distanceFunc = distFuncString;
        }
        catch (const std::exception&) {
            dio->write("Invalid input syntax");
            continue;
        }
        break;
    }
}
