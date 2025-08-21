#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), levels(6) {
    setWindowTitle("Парковочная система");
    setWindowState(Qt::WindowMaximized);
    setupLoginUI();
    setupMainMenuUI();
    setupAccountUI();
    setupGetInfoUI();

    is_getting_vehicles_info = false;

    Vehicle v;
    v.updateDuration();
    levels[0].lines[4][2] = v;
    levels[0].lines[4][5] = v;
}

void Widget::setupLoginUI() {
    login_label = std::make_unique<QLabel>("Введите имя пользователя и пароль", this);
    login_label.get()->setFixedSize(260, 30);

    username_label = std::make_unique<QLabel>("Имя пользователя: ", this);
    username_label.get()->setFixedSize(150, 30);

    password_label = std::make_unique<QLabel>("Пароль: ", this);
    password_label.get()->setFixedSize(150, 30);

    username_line_edit = std::make_unique<QLineEdit>(this);
    username_line_edit.get()->setFixedSize(260, 30);

    password_line_edit = std::make_unique<QLineEdit>(this);
    password_line_edit.get()->setFixedSize(260, 30);

    login_push_button = std::make_unique<QPushButton>("Log in", this);
    login_push_button.get()->setFixedSize(260, 80);
    connect(login_push_button.get(), SIGNAL(clicked()), this, SLOT(loginHandler()));
}

void Widget::setupMainMenuUI() {
    account_button = std::make_unique<QPushButton>("Account", this);
    account_button.get()->hide();
    connect(account_button.get(), SIGNAL(clicked()), this, SLOT(accountHandler()));

    change_vehicles_info_button = std::make_unique<QPushButton>("Change Vehicles", this);
    change_vehicles_info_button.get()->hide();

    get_vehicles_info_button = std::make_unique<QPushButton>("Get Vehicles Info", this);
    get_vehicles_info_button.get()->hide();
    connect(get_vehicles_info_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoHandler()));

    operate_button = std::make_unique<QPushButton>("Operate", this);
    operate_button.get()->hide();
}

void Widget::setupAccountUI() {
    account_name_label = std::make_unique<QLabel>("ФИО: ", this);
    account_name_label.get()->setFixedSize(150, 50);

    account_birth_date_label = std::make_unique<QLabel>("Дата рождения: ", this);
    account_birth_date_label.get()->setFixedSize(150, 50);

    account_phone_label = std::make_unique<QLabel>("Номер телефона: ", this);
    account_phone_label.get()->setFixedSize(150, 50);

    account_email_label = std::make_unique<QLabel>("Email: ", this);
    account_email_label.get()->setFixedSize(150, 50);

    account_current_name = std::make_unique<QLabel>("1", this);
    account_current_name.get()->setFixedSize(250, 50);

    account_current_birth_date = std::make_unique<QLabel>("2", this);
    account_current_birth_date.get()->setFixedSize(250, 50);

    account_current_phone = std::make_unique<QLabel>("3", this);
    account_current_phone.get()->setFixedSize(250, 50);

    account_current_email = std::make_unique<QLabel>("4", this);
    account_current_email.get()->setFixedSize(250, 50);

    account_change_button = std::make_unique<QPushButton>("Изменить", this);
    account_change_button.get()->setFixedSize(200, 50);
    connect(account_change_button.get(), SIGNAL(clicked()), this, SLOT(accountChangeHandler()));
    hideAccountUI();
}

void Widget::setupGetInfoUI() {
    get_info_visual_button = std::make_unique<QPushButton>("Визуальное представление", this);
    connect(get_info_visual_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoVisualHandler()));

    get_info_detailed_button = std::make_unique<QPushButton>("Подробная информация", this);
    connect(get_info_detailed_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedHandler()));

    get_info_detailed_levels_button = std::make_unique<QPushButton>("По этажам", this);
    connect(get_info_detailed_levels_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedLevelsHandler()));

    get_info_detailed_full_button = std::make_unique<QPushButton>("Все ТС", this);
    connect(get_info_detailed_full_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedFullHandler()));

    get_info_detailed_next_button = std::make_unique<QPushButton>("Next >", this);
    get_info_detailed_next_button.get()->setFixedSize(75, 30);

    get_info_detailed_prev_button = std::make_unique<QPushButton>("< Prev", this);
    get_info_detailed_prev_button.get()->setFixedSize(75, 30);

    get_info_detailed_card = std::make_unique<QGroupBox>("Инофрмация о ТС", this);

    get_info_detailed_card_plate_label = std::make_unique<QLabel>("plate: ", this);
    get_info_detailed_card_model_label = std::make_unique<QLabel>("model: ", this);
    get_info_detailed_card_enter_time_label = std::make_unique<QLabel>("enter_time: ", this);
    get_info_detailed_card_duration_label = std::make_unique<QLabel>("duration: ", this);
    get_info_detailed_card_is_placed_correctly_label = std::make_unique<QLabel>("is_placed_correctly: ", this);
    get_info_detailed_card_lvl_label = std::make_unique<QLabel>("level: ", this);
    get_info_detailed_card_row_label = std::make_unique<QLabel>("row: ", this);
    get_info_detailed_card_col_label = std::make_unique<QLabel>("column: ", this);

    get_info_detailed_card_plate_data = std::make_unique<QLabel>(this);
    get_info_detailed_card_model_data = std::make_unique<QLabel>(this);
    get_info_detailed_card_enter_time_data = std::make_unique<QLabel>(this);
    get_info_detailed_card_duration_data = std::make_unique<QLabel>(this);
    get_info_detailed_card_is_placed_correctly_data = std::make_unique<QLabel>(this);
    get_info_detailed_card_lvl_data = std::make_unique<QLabel>(this);
    get_info_detailed_card_row_data = std::make_unique<QLabel>(this);
    get_info_detailed_card_col_data = std::make_unique<QLabel>(this);

    get_info_detailed_card_layout = std::make_unique<QGridLayout>(this);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_plate_label.get(), 0, 0, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_model_label.get(), 1, 0, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_enter_time_label.get(), 2, 0, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_duration_label.get(), 3, 0, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_is_placed_correctly_label.get(), 4, 0, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_lvl_label.get(), 5, 0, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_row_label.get(), 6, 0, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_col_label.get(), 7, 0, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_plate_data.get(), 0, 1, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_model_data.get(), 1, 1, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_enter_time_data.get(), 2, 1, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_duration_data.get(), 3, 1, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_is_placed_correctly_data.get(), 4, 1, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_lvl_data.get(), 5, 1, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_row_data.get(), 6, 1, 1, 1);
    get_info_detailed_card_layout.get()->addWidget(get_info_detailed_card_col_data.get(), 7, 1, 1, 1);
    get_info_detailed_card.get()->setLayout(get_info_detailed_card_layout.get());

    hideGetInfoUI();
    hideGetInfoDetailedUI();
    hideGetInfoDetailedFullUI();
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter p;
    p.begin(this);
    if (is_getting_vehicles_info) {
        Level lvl;
        Vehicle v;
        v.updateDuration();
        lvl.add_vehicle(v, 4, 2);
        lvl.draw(&p);
    }
    p.end();
}

void Widget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    repositionLoginUI();
    repositionMainMenuUI();
    repositionAccountUI();
    repositionGetInfoUI();
}

void Widget::repositionLoginUI() {
    int mid_screen = this->width() / 2;

    login_label.get()->move(mid_screen - 130, 500);
    username_label.get()->move(mid_screen - 280, 550);
    password_label.get()->move(mid_screen - 280, 600);

    username_line_edit.get()->move(mid_screen - 130, 550);
    password_line_edit.get()->move(mid_screen - 130, 600);

    login_push_button.get()->move(mid_screen - 130, 650);
}

void Widget::repositionMainMenuUI() {
    int mid_width = this->width() / 2;
    int mid_height = this->height() / 2;

    account_button.get()->setFixedSize(mid_width, mid_height);
    change_vehicles_info_button.get()->setFixedSize(mid_width, mid_height);
    get_vehicles_info_button.get()->setFixedSize(mid_width, mid_height);
    operate_button.get()->setFixedSize(mid_width, mid_height);

    account_button.get()->move(0, 0);
    change_vehicles_info_button.get()->move(mid_width, 0);
    get_vehicles_info_button.get()->move(0, mid_height);
    operate_button.get()->move(mid_width, mid_height);
}

void Widget::repositionAccountUI() {
    int mid_width = this->width() / 2;
    int mid_height = this->height() / 2;

    account_name_label.get()->move(mid_width - 150, mid_height - 75);
    account_birth_date_label.get()->move(mid_width - 150, mid_height - 25);
    account_phone_label.get()->move(mid_width - 150, mid_height + 25);
    account_email_label.get()->move(mid_width - 150, mid_height + 75);

    account_current_name.get()->move(mid_width + 50, mid_height - 75);
    account_current_birth_date.get()->move(mid_width + 50, mid_height - 25);
    account_current_phone.get()->move(mid_width + 50, mid_height + 25);
    account_current_email.get()->move(mid_width + 50, mid_height + 75);

    account_change_button.get()->move(mid_width - 100, mid_height + 125);
}

void Widget::repositionGetInfoUI() {
    int screen_width = this->width();
    int screen_height = this->height();

    get_info_visual_button->setFixedSize(screen_width / 2, screen_height / 4);
    get_info_detailed_button->setFixedSize(screen_width / 2, screen_height / 4);
    get_info_detailed_levels_button->setFixedSize(screen_width / 2, screen_height / 4);
    get_info_detailed_full_button->setFixedSize(screen_width / 2, screen_height / 4);

    get_info_visual_button->move(screen_width / 4, screen_height / 4);
    get_info_detailed_button->move(screen_width / 4, screen_height / 2);
    get_info_detailed_levels_button->move(screen_width / 4, screen_height / 4);
    get_info_detailed_full_button->move(screen_width / 4, screen_height / 2);

    get_info_detailed_next_button->move(3 * screen_width / 4, 3 * screen_height / 4);
    get_info_detailed_prev_button->move(screen_width / 4, 3 * screen_height / 4);
    get_info_detailed_card->move(screen_width / 2 - get_info_detailed_card->width() / 2, screen_height / 2 - get_info_detailed_card->height() / 2);
}

void Widget::hideLoginUI() {
    login_label.get()->hide();
    username_label.get()->hide();
    password_label.get()->hide();
    username_line_edit.get()->hide();
    password_line_edit.get()->hide();
    login_push_button.get()->hide();
}

void Widget::hideMainMenuUI() {
    account_button.get()->hide();
    change_vehicles_info_button.get()->hide();
    get_vehicles_info_button.get()->hide();
    operate_button.get()->hide();
}

void Widget::hideAccountUI() {
    account_name_label.get()->hide();
    account_birth_date_label.get()->hide();
    account_phone_label.get()->hide();
    account_email_label.get()->hide();

    account_current_name.get()->hide();
    account_current_birth_date.get()->hide();
    account_current_phone.get()->hide();
    account_current_email.get()->hide();

    account_change_button.get()->hide();
}

void Widget::hideGetInfoUI() {
    get_info_visual_button.get()->hide();
    get_info_detailed_button.get()->hide();
}

void Widget::hideGetInfoDetailedUI() {
    get_info_detailed_levels_button.get()->hide();
    get_info_detailed_full_button.get()->hide();
}

void Widget::hideGetInfoDetailedFullUI() {
    get_info_detailed_next_button->hide();
    get_info_detailed_prev_button->hide();
    get_info_detailed_card->hide();
}

void Widget::showMainMenuUI() {
    account_button.get()->show();
    change_vehicles_info_button.get()->show();
    get_vehicles_info_button.get()->show();
    operate_button.get()->show();
}

void Widget::showAccountUI() {
    account_name_label.get()->show();
    account_birth_date_label.get()->show();
    account_phone_label.get()->show();
    account_email_label.get()->show();

    account_current_name.get()->show();
    account_current_birth_date.get()->show();
    account_current_phone.get()->show();
    account_current_email.get()->show();

    account_change_button.get()->show();
}

void Widget::showGetInfoUI() {
    get_info_visual_button.get()->show();
    get_info_detailed_button.get()->show();
}

void Widget::showGetInfoDetailedUI() {
    get_info_detailed_levels_button.get()->show();
    get_info_detailed_full_button.get()->show();
}

void Widget::showGetInfoDetailedInternalUI() {
    get_info_detailed_next_button->show();
    get_info_detailed_prev_button->show();
    get_info_detailed_card->show();
}

void Widget::loginHandler() {
    DataBase db;
    bool is_correct = db.check_login(username_line_edit.get()->text(), password_line_edit.get()->text());
    login_label.get()->setText(QString::number(is_correct));
    if (is_correct) {
        hideLoginUI();
        showMainMenuUI();
    }
    else {
        QMessageBox::critical(this, tr("Error"), tr("Wrong Username/Password"));
    }
}

void Widget::accountHandler() {
    hideMainMenuUI();
    showAccountUI();
}

void Widget::accountChangeHandler() {
    const QStringList items{tr("ФИО"), tr("Дата рождения"), tr("Номер телефона"), tr("Email")};

    bool ok{};
    QString item;
    QInputDialog dlg;
    dlg.setWindowTitle("Изменение информации аккаунта");
    dlg.setLabelText("Что изменить?");
    dlg.setComboBoxItems(items);
    dlg.resize(400, 300); //проблемы с местом появления
    if (dlg.exec() == QDialog::Accepted) {
        item = dlg.textValue();
    }
    else {
        return;
    }

    QInputDialog internal_dlg;
    if (item == "ФИО") {
        internal_dlg.setWindowTitle("Изменение ФИО");
        internal_dlg.setLabelText("Новое ФИО:");
        internal_dlg.resize(300, 300);
        if (internal_dlg.exec() == QDialog::Accepted) {
            account_current_name->setText(internal_dlg.textValue());
        }
        else {
            return;
        }
    }

    if (item == "Дата рождения") {
        internal_dlg.setWindowTitle("Изменение даты рождения");
        internal_dlg.setLabelText("Новая дата рождения:");
        internal_dlg.resize(300, 300);
        if (internal_dlg.exec() == QDialog::Accepted) {
            account_current_birth_date->setText(internal_dlg.textValue());
        }
        else {
            return;
        }
    }

    if (item == "Номер телефона") {
        internal_dlg.setWindowTitle("Изменение номера телефона");
        internal_dlg.setLabelText("Новый номер телефона:");
        internal_dlg.resize(300, 300);
        if (internal_dlg.exec() == QDialog::Accepted) {
            account_current_phone->setText(internal_dlg.textValue());
        }
        else {
            return;
        }
    }

    if (item == "Email") {
        internal_dlg.setWindowTitle("Изменение Email");
        internal_dlg.setLabelText("Новый Email:");
        internal_dlg.resize(300, 300);
        if (internal_dlg.exec() == QDialog::Accepted) {
            account_current_email->setText(internal_dlg.textValue());
        }
        else {
            return;
        }
    }
}

void Widget::getVehiclesInfoHandler() {
    hideMainMenuUI();
    showGetInfoUI();
}

void Widget::getVehiclesInfoVisualHandler() {
    hideGetInfoUI();
    is_getting_vehicles_info = true;
    update();
}

void Widget::getVehiclesInfoDetailedHandler() {
    hideGetInfoUI();
    showGetInfoDetailedUI();
}

void Widget::getVehiclesInfoDetailedFullHandler() {
    hideGetInfoDetailedUI();
    showGetInfoDetailedInternalUI();
    connect(get_info_detailed_next_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedNextFullHandler()));
    connect(get_info_detailed_prev_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedPrevFullHandler()));

    bool flag = false;
    for (int i = 0; i < levels.size(); i++) {
        Level lvl = levels[i];
        for (int j = 0; j < lvl.lines.size(); j++) {
            for (int k = 0; k < lvl.lines[j].size(); k++) {
                if (!lvl.lines[j][k].getDuration().isNull()) {
                    Vehicle v = lvl.lines[j][k];
                    setCardData(v, i, j, k);
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
    }
}

void Widget::getVehiclesInfoDetailedNextFullHandler() {
    bool flag = false;
    for (int i = get_info_detailed_card_lvl_data->text().toInt() - 1; i < levels.size(); i++) {
        Level lvl = levels[i];
        for (int j = get_info_detailed_card_row_data->text().toInt() - 1; j < lvl.lines.size(); j++) {
            for (int k = get_info_detailed_card_col_data->text().toInt(); k < lvl.lines[j].size(); k++) {
                if (!lvl.lines[j][k].getDuration().isNull()) {
                    Vehicle v = lvl.lines[j][k];
                    setCardData(v, i, j, k);
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
    }
}

void Widget::getVehiclesInfoDetailedPrevFullHandler() {
    bool flag = false;
    for (int i = get_info_detailed_card_lvl_data->text().toInt() - 1; i >= 0; i--) {
        Level lvl = levels[i];
        for (int j = get_info_detailed_card_row_data->text().toInt() - 1; j >= 0; j--) {
            for (int k = get_info_detailed_card_col_data->text().toInt() - 2; k >= 0; k--) {
                if (!lvl.lines[j][k].getDuration().isNull()) {
                    Vehicle v = lvl.lines[j][k];
                    setCardData(v, i, j, k);
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
    }
}

void Widget::setCardData(Vehicle v, int i, int j, int k) {
    get_info_detailed_card_plate_data->setText(v.getPlate());
    get_info_detailed_card_model_data->setText(v.getModel());
    get_info_detailed_card_enter_time_data->setText(v.getEnterTime().toString());
    get_info_detailed_card_duration_data->setText(v.getDuration().toString());
    get_info_detailed_card_is_placed_correctly_data->setText(QString::number(v.getIsPlacedCorrectly()));
    get_info_detailed_card_lvl_data->setText(QString::number(i + 1));
    get_info_detailed_card_row_data->setText(QString::number(j + 1));
    get_info_detailed_card_col_data->setText(QString::number(k + 1));
}

void Widget::getVehiclesInfoDetailedLevelsHandler() {
    bool ok{};
    int level = QInputDialog::getInt(this, "Выберите этаж", "Этаж", 1, 1, levels.size(), 1, &ok) - 1;
    if (!ok) {
        return;
    }
    hideGetInfoDetailedUI();
    showGetInfoDetailedInternalUI();
    connect(get_info_detailed_next_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedNextLevelsHandler()));
    connect(get_info_detailed_prev_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedPrevLevelsHandler()));

    bool flag = false;
    Level lvl = levels[level];
    for (int j = 0; j < lvl.lines.size(); j++) {
        for (int k = 0; k < lvl.lines[j].size(); k++) {
            if (!lvl.lines[j][k].getDuration().isNull()) {
                Vehicle v = lvl.lines[j][k];
                setCardData(v, level, j, k);
                flag = true;
                break;
            }
        }
        if (flag) {
            break;
        }
    }
}


void Widget::getVehiclesInfoDetailedNextLevelsHandler() {
    bool flag = false;
    int level = get_info_detailed_card_lvl_data->text().toInt() - 1;
    Level lvl = levels[level];
    for (int j = get_info_detailed_card_row_data->text().toInt() - 1; j < lvl.lines.size(); j++) {
        for (int k = get_info_detailed_card_col_data->text().toInt(); k < lvl.lines[j].size(); k++) {
            if (!lvl.lines[j][k].getDuration().isNull()) {
                Vehicle v = lvl.lines[j][k];
                setCardData(v, level, j, k);
                flag = true;
                break;
            }
        }
        if (flag) {
            break;
        }
    }
}

void Widget::getVehiclesInfoDetailedPrevLevelsHandler() {
    bool flag = false;
    int level = get_info_detailed_card_lvl_data->text().toInt() - 1;
    Level lvl = levels[level];
    for (int j = get_info_detailed_card_row_data->text().toInt() - 1; j >= 0; j--) {
        for (int k = get_info_detailed_card_col_data->text().toInt() - 2; k >= 0; k--) {
            if (!lvl.lines[j][k].getDuration().isNull()) {
                Vehicle v = lvl.lines[j][k];
                setCardData(v, level, j, k);
                flag = true;
                break;
            }
        }
        if (flag) {
            break;
        }
    }
}


Widget::~Widget() {
}
