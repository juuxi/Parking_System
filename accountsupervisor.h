#ifndef ACCOUNTSUPERVISOR_H
#define ACCOUNTSUPERVISOR_H

#include <QString>

struct AccountSupervisor {

    bool accountIsNumberCorrect(QString input) {
        if (!input[0].isDigit() && input[0] != '+') {
            return false;
        }
        for (int i = 1; i < input.size(); i++) {
            if (!input[i].isDigit()) {
                return false;
            }
        }
        return true;
    }

    bool accountIsBirthDateCorrect(QString input) {
        if (input.size() != 10) {
            return false;
        }
        for (int i = 0; i < 10; i++) { //dd.mm.yyyy doesn't check correct day/month, maybe Msg w/ correct format?
            if (i == 2 || i == 5) {
                if (input[i] != '.') {
                    return false;
                }
            }
            else {
                if (!input[i].isDigit()) {
                    return false;
                }
            }
        }
        return true;
    }

    bool accountIsEmailCorrect(QString input) {
        int at = input.indexOf('@');
        int dot = input.lastIndexOf('.');
        if (at == -1 || dot == -1) {
            return false;
        }
        if (dot >= input.size() - 1) {
            return false;
        }
        if (at > dot) {
            return false;
        }
        return true;
    }

};

#endif // ACCOUNTSUPERVISOR_H
