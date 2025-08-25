#ifndef INFOCARD_H
#define INFOCARD_H

#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include "vehicle.h"

#include <memory>

class InfoCard : public QGroupBox {
public:
    std::unique_ptr<QLabel> plate_label;
    std::unique_ptr<QLabel> model_label;
    std::unique_ptr<QLabel> enter_time_label;
    std::unique_ptr<QLabel> duration_label;
    std::unique_ptr<QLabel> is_placed_correctly_label;
    std::unique_ptr<QLabel> lvl_label;
    std::unique_ptr<QLabel> row_label;
    std::unique_ptr<QLabel> col_label;

    std::unique_ptr<QLabel> plate_data;
    std::unique_ptr<QLabel> model_data;
    std::unique_ptr<QLabel> enter_time_data;
    std::unique_ptr<QLabel> duration_data;
    std::unique_ptr<QLabel> is_placed_correctly_data;
    std::unique_ptr<QLabel> lvl_data;
    std::unique_ptr<QLabel> row_data;
    std::unique_ptr<QLabel> col_data;

    std::unique_ptr<QPushButton> button;

    std::unique_ptr<QGridLayout> grid;

    InfoCard(QWidget*);
    void setCardData(Vehicle, int, int, int);
    void makeChangeable();
    void makeUnchangeable();
};

#endif // INFOCARD_H
