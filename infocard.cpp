#include "infocard.h"

InfoCard::InfoCard(QWidget* _parent) {
    setParent(_parent);
    plate_label = std::make_unique<QLabel>("plate: ", this);
    plate_label->setFixedSize(150, 30);
    model_label = std::make_unique<QLabel>("model: ", this);
    model_label->setFixedSize(150, 30);
    enter_time_label = std::make_unique<QLabel>("enter_time: ", this);
    enter_time_label->setFixedSize(150, 30);
    duration_label = std::make_unique<QLabel>("duration: ", this);
    duration_label->setFixedSize(150, 30);
    is_placed_correctly_label = std::make_unique<QLabel>("is_placed_correctly: ", this);
    is_placed_correctly_label->setFixedSize(150, 30);
    lvl_label = std::make_unique<QLabel>("level: ", this);
    lvl_label->setFixedSize(150, 30);
    row_label = std::make_unique<QLabel>("row: ", this);
    row_label->setFixedSize(150, 30);
    col_label = std::make_unique<QLabel>("column: ", this);
    col_label->setFixedSize(150, 30);

    plate_data = std::make_unique<QLabel>(this);
    plate_data->setFixedSize(150, 30);
    model_data = std::make_unique<QLabel>(this);
    model_data->setFixedSize(150, 30);
    enter_time_data = std::make_unique<QLabel>(this);
    enter_time_data->setFixedSize(150, 30);
    duration_data = std::make_unique<QLabel>(this);
    duration_data->setFixedSize(150, 30);
    is_placed_correctly_data = std::make_unique<QLabel>(this);
    is_placed_correctly_data->setFixedSize(150, 30);
    lvl_data = std::make_unique<QLabel>(this);
    lvl_data->setFixedSize(150, 30);
    row_data = std::make_unique<QLabel>(this);
    row_data->setFixedSize(150, 30);
    col_data = std::make_unique<QLabel>(this);
    col_data->setFixedSize(150, 30);

    button = std::make_unique<QPushButton>("Change", this);
    button->setFixedSize(300, 50);
    button->hide();
    connect(button.get(), SIGNAL(clicked()), parentWidget(), SLOT(changeVehiclesInternalHandler()));

    grid = std::make_unique<QGridLayout>(this);
    grid->addWidget(plate_label.get(), 0, 0, 1, 1);
    grid->addWidget(model_label.get(), 1, 0, 1, 1);
    grid->addWidget(enter_time_label.get(), 2, 0, 1, 1);
    grid->addWidget(duration_label.get(), 3, 0, 1, 1);
    grid->addWidget(is_placed_correctly_label.get(), 4, 0, 1, 1);
    grid->addWidget(lvl_label.get(), 5, 0, 1, 1);
    grid->addWidget(row_label.get(), 6, 0, 1, 1);
    grid->addWidget(col_label.get(), 7, 0, 1, 1);
    grid->addWidget(plate_data.get(), 0, 1, 1, 1);
    grid->addWidget(model_data.get(), 1, 1, 1, 1);
    grid->addWidget(enter_time_data.get(), 2, 1, 1, 1);
    grid->addWidget(duration_data.get(), 3, 1, 1, 1);
    grid->addWidget(is_placed_correctly_data.get(), 4, 1, 1, 1);
    grid->addWidget(lvl_data.get(), 5, 1, 1, 1);
    grid->addWidget(row_data.get(), 6, 1, 1, 1);
    grid->addWidget(col_data.get(), 7, 1, 1, 1);
    this->setLayout(grid.get());
    this->adjustSize();
}

void InfoCard::setCardData(Vehicle v, int i, int j, int k) {
    plate_data->setText(v.getPlate());
    model_data->setText(v.getModel());
    enter_time_data->setText(v.getEnterTime().toString());
    duration_data->setText(v.getDuration().toString());
    is_placed_correctly_data->setText(QString::number(v.getIsPlacedCorrectly()));
    lvl_data->setText(QString::number(i + 1));
    row_data->setText(QString::number(j + 1));
    col_data->setText(QString::number(k + 1));
}

void InfoCard::makeChangeable() {
    grid->addWidget(button.get(), 8, 0, 1, 2);
    button->show();
    this->setLayout(grid.get());
    this->adjustSize();
}

void InfoCard::makeUnchangeable() {
    grid->removeWidget(button.get());
    button->hide();
    this->setLayout(grid.get());
    this->adjustSize();
}
