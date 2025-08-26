#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), levels(6), card(this) {
    setWindowTitle("Парковочная система");
    setWindowState(Qt::WindowMaximized);
    setupLoginUI();
    setupMainMenuUI();
    setupAccountUI();
    setupChangeVehiclesUI();
    setupGetInfoUI();
    setupOperateUI();

    is_getting_vehicles_info = false;

    Vehicle v;
    v.updateDuration();
    levels[0].lines[4][2] = v;
    levels[0].lines[4][5] = v;

    tl = std::make_shared<TrafficLight>();
    br = std::make_shared<Barrier>();

    for (Level& level : levels) {
        level.add_control_element(tl);
        level.add_control_element(br);
    }
}

void Widget::setupLoginUI() {
    login_label = std::make_unique<QLabel>("Введите имя пользователя и пароль", this);
    login_label->setFixedSize(260, 30);

    username_label = std::make_unique<QLabel>("Имя пользователя: ", this);
    username_label->setFixedSize(150, 30);

    password_label = std::make_unique<QLabel>("Пароль: ", this);
    password_label->setFixedSize(150, 30);

    username_line_edit = std::make_unique<QLineEdit>(this);
    username_line_edit->setFixedSize(260, 30);

    password_line_edit = std::make_unique<QLineEdit>(this);
    password_line_edit->setFixedSize(260, 30);

    login_push_button = std::make_unique<QPushButton>("Log in", this);
    login_push_button->setFixedSize(260, 80);
    connect(login_push_button.get(), SIGNAL(clicked()), this, SLOT(loginHandler()));
}

void Widget::setupMainMenuUI() {
    account_button = std::make_unique<QPushButton>("Account", this);
    account_button->hide();
    connect(account_button.get(), SIGNAL(clicked()), this, SLOT(accountHandler()));

    change_vehicles_info_button = std::make_unique<QPushButton>("Change Vehicles", this);
    change_vehicles_info_button->hide();
    connect(change_vehicles_info_button.get(), SIGNAL(clicked()), this, SLOT(changeVehiclesHandler()));

    get_vehicles_info_button = std::make_unique<QPushButton>("Get Vehicles Info", this);
    get_vehicles_info_button->hide();
    connect(get_vehicles_info_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoHandler()));

    operate_button = std::make_unique<QPushButton>("Operate", this);
    operate_button->hide();
    connect(operate_button.get(), SIGNAL(clicked()), this, SLOT(operateHandler()));
}

void Widget::setupAccountUI() {
    account_name_label = std::make_unique<QLabel>("ФИО: ", this);
    account_name_label->setFixedSize(150, 50);

    account_birth_date_label = std::make_unique<QLabel>("Дата рождения: ", this);
    account_birth_date_label->setFixedSize(150, 50);

    account_phone_label = std::make_unique<QLabel>("Номер телефона: ", this);
    account_phone_label->setFixedSize(150, 50);

    account_email_label = std::make_unique<QLabel>("Email: ", this);
    account_email_label->setFixedSize(150, 50);

    account_current_name = std::make_unique<QLabel>("1", this);
    account_current_name->setFixedSize(250, 50);

    account_current_birth_date = std::make_unique<QLabel>("2", this);
    account_current_birth_date->setFixedSize(250, 50);

    account_current_phone = std::make_unique<QLabel>("3", this);
    account_current_phone->setFixedSize(250, 50);

    account_current_email = std::make_unique<QLabel>("4", this);
    account_current_email->setFixedSize(250, 50);

    account_change_button = std::make_unique<QPushButton>("Изменить", this);
    account_change_button->setFixedSize(200, 50);
    connect(account_change_button.get(), SIGNAL(clicked()), this, SLOT(accountChangeHandler()));

    account_back_button = std::make_unique<QPushButton>("Back", this);
    account_back_button->setGeometry(10, 10, 50, 20);
    connect(account_back_button.get(), SIGNAL(clicked()), this, SLOT(accountBackHandler()));

    account_internal_dlg = std::make_unique<QInputDialog>(this);
    account_dlg = std::make_unique<QInputDialog>(this);

    hideAccountUI();
}

void Widget::setupChangeVehiclesUI()  {

    change_vehicles_back_button = std::make_unique<QPushButton>("Back", this);
    change_vehicles_back_button->setGeometry(10, 10, 50, 20);
    connect(change_vehicles_back_button.get(), SIGNAL(clicked()), this, SLOT(changeVehiclesBackHandler()));

    hideChangeVehiclesUI();
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
    get_info_detailed_next_button->setFixedSize(75, 30);

    get_info_detailed_prev_button = std::make_unique<QPushButton>("< Prev", this);
    get_info_detailed_prev_button->setFixedSize(75, 30);

    get_info_back_button = std::make_unique<QPushButton>("Back", this);
    get_info_back_button->setGeometry(10, 10, 50, 20);
    connect(get_info_back_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoBackHandler()));

    get_info_detailed_back_button = std::make_unique<QPushButton>("Back", this);
    get_info_detailed_back_button->setGeometry(10, 10, 50, 20);
    connect(get_info_detailed_back_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedBackHandler()));

    get_info_detailed_internal_back_button = std::make_unique<QPushButton>("Back", this);
    get_info_detailed_internal_back_button->setGeometry(10, 10, 50, 20);
    connect(get_info_detailed_internal_back_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedInternalBackHandler()));

    get_info_visual_back_button = std::make_unique<QPushButton>("Back", this);
    get_info_visual_back_button->setGeometry(10, 10, 50, 20);
    connect(get_info_visual_back_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoVisualBackHandler()));

    hideGetInfoUI();
    hideGetInfoVisualUI();
    hideGetInfoDetailedUI();
    hideGetInfoDetailedInternalUI();
}

void Widget::setupOperateUI() {
    operate_close_level_button = std::make_unique<QPushButton>("Закрыть этаж", this);
    connect(operate_close_level_button.get(), SIGNAL(clicked()), this, SLOT(operateCloseLevelHandler()));
    operate_close_level_button->setFixedSize(400, 100);

    operate_back_button = std::make_unique<QPushButton>("Back", this);
    connect(operate_back_button.get(), SIGNAL(clicked()), this, SLOT(operateBackHandler()));
    operate_back_button->setGeometry(10, 10, 50, 20);

    operate_all_ce_button = std::make_unique<QPushButton>("Все УЭ", this);
    connect(operate_all_ce_button.get(), SIGNAL(clicked()), this, SLOT(operateAllCeHandler()));
    operate_all_ce_button->setFixedSize(400, 100);

    operate_current_level = std::make_unique<QLabel>(this);
    operate_current_level->setFixedSize(60, 30);

    operate_card = std::make_unique<QGroupBox>("УЭ", this);

    operate_card_type_label = std::make_unique<QLabel>("Тип", this);
    operate_card_type_label->setFixedSize(100, 30);
    operate_card_type_data = std::make_unique<QLabel>(this);
    operate_card_type_data->setFixedSize(100, 30);

    operate_card_is_opened_label = std::make_unique<QLabel>("Открыт", this);
    operate_card_is_opened_label->setFixedSize(100, 30);
    operate_card_is_opened_data = std::make_unique<QLabel>(this);
    operate_card_is_opened_data->setFixedSize(100, 30);

    operate_card_number_label = std::make_unique<QLabel>("Номер", this);
    operate_card_number_label->setFixedSize(100, 30);
    operate_card_number_data = std::make_unique<QLabel>(this);
    operate_card_number_data->setFixedSize(100, 30);

    operate_close_ce_button = std::make_unique<QPushButton>("Закрыть", this);
    connect(operate_close_ce_button.get(), SIGNAL(clicked()), this, SLOT(operateCloseCeHandler()));
    operate_close_ce_button->setFixedSize(100, 50);

    operate_open_ce_button = std::make_unique<QPushButton>("Открыть", this);
    connect(operate_open_ce_button.get(), SIGNAL(clicked()), this, SLOT(operateOpenCeHandler()));
    operate_open_ce_button->setFixedSize(100, 50);

    operate_next_ce_button = std::make_unique<QPushButton>("Next >", this);
    connect(operate_next_ce_button.get(), SIGNAL(clicked()), this, SLOT(operateNextCeHandler()));
    operate_next_ce_button->setFixedSize(75, 30);

    operate_prev_ce_button = std::make_unique<QPushButton>("< Prev", this);
    connect(operate_prev_ce_button.get(), SIGNAL(clicked()), this, SLOT(operatePrevCeHandler()));
    operate_prev_ce_button->setFixedSize(75, 30);

    operate_card_layout = std::make_unique<QGridLayout>(this);
    operate_card_layout->addWidget(operate_card_type_label.get(), 0, 0, 1, 1);
    operate_card_layout->addWidget(operate_card_type_data.get(), 0, 1, 1, 1);
    operate_card_layout->addWidget(operate_card_is_opened_label.get(), 1, 0, 1, 1);
    operate_card_layout->addWidget(operate_card_is_opened_data.get(), 1, 1, 1, 1);
    operate_card_layout->addWidget(operate_card_number_label.get(), 2, 0, 1, 1);
    operate_card_layout->addWidget(operate_card_number_data.get(), 2, 1, 1, 1);
    operate_card->setLayout(operate_card_layout.get());

    operate_all_ce_back_button = std::make_unique<QPushButton>("Back", this);
    connect(operate_all_ce_back_button.get(), SIGNAL(clicked()), this, SLOT(operateAllCeBackHandler()));
    operate_all_ce_back_button->setGeometry(10, 10, 50, 20);

    operate_add_vehilce_button = std::make_unique<QPushButton>("Добавить ТС", this);
    connect(operate_add_vehilce_button.get(), SIGNAL(clicked()), this, SLOT(operateAddVehicleHandler()));
    operate_add_vehilce_button->setFixedSize(400, 100);

    operate_add_ce_button = std::make_unique<QPushButton>("Добавить УЭ", this);
    connect(operate_add_ce_button.get(), SIGNAL(clicked()), this, SLOT(operateAddCeHandler()));
    operate_add_ce_button->setFixedSize(400, 100);

    operate_dlg = std::make_unique<QInputDialog>(this);

    hideOperateUI();
}

void Widget::paintEvent(QPaintEvent* event) {
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
    repositionOperateUI();
}

void Widget::repositionLoginUI() {
    int mid_screen = this->width() / 2;

    login_label->move(mid_screen - 130, 500);
    username_label->move(mid_screen - 280, 550);
    password_label->move(mid_screen - 280, 600);

    username_line_edit->move(mid_screen - 130, 550);
    password_line_edit->move(mid_screen - 130, 600);

    login_push_button->move(mid_screen - 130, 650);
}

void Widget::repositionMainMenuUI() {
    int mid_width = this->width() / 2;
    int mid_height = this->height() / 2;

    account_button->setFixedSize(mid_width, mid_height);
    change_vehicles_info_button->setFixedSize(mid_width, mid_height);
    get_vehicles_info_button->setFixedSize(mid_width, mid_height);
    operate_button->setFixedSize(mid_width, mid_height);

    account_button->move(0, 0);
    change_vehicles_info_button->move(mid_width, 0);
    get_vehicles_info_button->move(0, mid_height);
    operate_button->move(mid_width, mid_height);
}

void Widget::repositionAccountUI() {
    int mid_width = this->width() / 2;
    int mid_height = this->height() / 2;

    account_name_label->move(mid_width - 150, mid_height - 75);
    account_birth_date_label->move(mid_width - 150, mid_height - 25);
    account_phone_label->move(mid_width - 150, mid_height + 25);
    account_email_label->move(mid_width - 150, mid_height + 75);

    account_current_name->move(mid_width + 50, mid_height - 75);
    account_current_birth_date->move(mid_width + 50, mid_height - 25);
    account_current_phone->move(mid_width + 50, mid_height + 25);
    account_current_email->move(mid_width + 50, mid_height + 75);

    account_change_button->move(mid_width - 100, mid_height + 125);

    account_dlg->move(mid_width / 2 - account_dlg->width() / 2, mid_height / 2 - account_dlg->height() / 2);
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
    card.move(screen_width / 2 - card.width() / 2, screen_height / 2 - card.height() / 2);
}

void Widget::repositionOperateUI() {
    int screen_width = this->width();
    int screen_height = this->height();
    operate_close_level_button->move(screen_width / 2 - operate_close_level_button->width() / 2,
                                     screen_height / 4);

    operate_all_ce_button->move(screen_width / 2 - operate_all_ce_button->width() / 2,
                                3 * screen_height / 8);

    operate_add_vehilce_button->move(screen_width / 2 - operate_all_ce_button->width() / 2,
                                     screen_height / 2);

    operate_add_ce_button->move(screen_width / 2 - operate_all_ce_button->width() / 2,
                                     5 * screen_height / 8);

    operate_current_level->move(screen_width / 2 - operate_current_level->width() / 2,
                                screen_height / 8 - operate_current_level->height() / 2);

    operate_card->move(screen_width / 2 - operate_card->width() / 2,
                       screen_height / 4 - operate_card->height() / 2);

    operate_dlg->move(screen_width / 2 - operate_dlg->width() / 2,
                      screen_height / 2 - operate_dlg->height() / 2);


    operate_close_ce_button->move(5 * screen_width / 8, 5 * screen_height / 8);
    operate_open_ce_button->move(3 * screen_width / 8, 5 * screen_height / 8);

    operate_next_ce_button->move(3 * screen_width / 4, 3 * screen_height / 4);
    operate_prev_ce_button->move(screen_width / 4, 3 * screen_height / 4);
}

void Widget::hideLoginUI() {
    login_label->hide();
    username_label->hide();
    password_label->hide();
    username_line_edit->hide();
    password_line_edit->hide();
    login_push_button->hide();
}

void Widget::hideMainMenuUI() {
    account_button->hide();
    change_vehicles_info_button->hide();
    get_vehicles_info_button->hide();
    operate_button->hide();
}

void Widget::hideAccountUI() {
    account_name_label->hide();
    account_birth_date_label->hide();
    account_phone_label->hide();
    account_email_label->hide();

    account_current_name->hide();
    account_current_birth_date->hide();
    account_current_phone->hide();
    account_current_email->hide();

    account_change_button->hide();

    account_back_button->hide();
}

void Widget::hideChangeVehiclesUI() {
    card.makeUnchangeable();
    card.hide();
    change_vehicles_back_button->hide();
}

void Widget::hideGetInfoUI() {
    get_info_visual_button->hide();
    get_info_detailed_button->hide();
    get_info_back_button->hide();
}

void Widget::hideGetInfoVisualUI() {
    get_info_visual_back_button->hide();
}

void Widget::hideGetInfoDetailedUI() {
    get_info_detailed_levels_button->hide();
    get_info_detailed_full_button->hide();
    get_info_detailed_back_button->hide();
}

void Widget::hideGetInfoDetailedInternalUI() {
    get_info_detailed_next_button->hide();
    get_info_detailed_prev_button->hide();
    card.hide();
    get_info_detailed_internal_back_button->hide();
}

void Widget::hideOperateUI() {
    operate_close_level_button->hide();
    operate_current_level->hide();
    operate_back_button->hide();
    operate_all_ce_button->hide();
    operate_add_vehilce_button->hide();
    operate_add_ce_button->hide();
    hideOperateAllCeUI();
}

void Widget::hideOperateAllCeUI() {
    operate_card->hide();
    operate_close_ce_button->hide();
    operate_open_ce_button->hide();
    operate_next_ce_button->hide();
    operate_prev_ce_button->hide();
    operate_all_ce_back_button->hide();
}

void Widget::showMainMenuUI() {
    account_button->show();
    change_vehicles_info_button->show();
    get_vehicles_info_button->show();
    operate_button->show();
}

void Widget::showAccountUI() {
    account_name_label->show();
    account_birth_date_label->show();
    account_phone_label->show();
    account_email_label->show();

    account_current_name->show();
    account_current_birth_date->show();
    account_current_phone->show();
    account_current_email->show();

    account_change_button->show();

    account_back_button->show();
}

void Widget::showChangeVehiclesUI() {
    card.show();
    card.makeChangeable();
    change_vehicles_back_button->show();
}

void Widget::showGetInfoUI() {
    get_info_visual_button->show();
    get_info_detailed_button->show();
    get_info_back_button->show();
}

void Widget::showGetInfoVisualUI() {
    get_info_visual_back_button->show();
}

void Widget::showGetInfoDetailedUI() {
    get_info_detailed_levels_button->show();
    get_info_detailed_full_button->show();
    get_info_detailed_back_button->show();
}

void Widget::showGetInfoDetailedInternalUI() {
    get_info_detailed_next_button->show();
    get_info_detailed_prev_button->show();
    card.show();
    get_info_detailed_internal_back_button->show();
}

void Widget::showOperateUI() {
    operate_close_level_button->show();
    operate_current_level->show();
    operate_back_button->show();
    operate_all_ce_button->show();
    operate_add_vehilce_button->show();
    operate_add_ce_button->show();
}

void Widget::showOperateAllCeUI() {
    operate_card->show();
    operate_close_ce_button->show();
    operate_open_ce_button->show();
    operate_next_ce_button->show();
    operate_prev_ce_button->show();
    operate_all_ce_back_button->show();
}

void Widget::loginHandler() {
    DataBase db;
    bool is_correct = db.check_login(username_line_edit->text(), password_line_edit->text());
    login_label->setText(QString::number(is_correct));
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
    account_dlg->setWindowTitle("Изменение информации аккаунта");
    account_dlg->setLabelText("Что изменить?");
    account_dlg->setComboBoxItems(items);
    account_dlg->resize(400, 300);
    if (account_dlg->exec() == QDialog::Accepted) {
        item = account_dlg->textValue();
    }
    else {
        return;
    }

    if (item == "ФИО") {
        account_internal_dlg->setWindowTitle("Изменение ФИО");
        account_internal_dlg->setLabelText("Новое ФИО:");
        account_internal_dlg->resize(300, 300);
        if (account_internal_dlg->exec() == QDialog::Accepted && !account_internal_dlg->textValue().isNull()) {
            QString input = account_internal_dlg->textValue();
            account_current_name->setText(input);
        }
        else {
            return;
        }
    }

    if (item == "Дата рождения") {
        while (true) {
            account_internal_dlg->setWindowTitle("Изменение даты рождения");
            account_internal_dlg->setLabelText("Новая дата рождения:");
            account_internal_dlg->resize(300, 300);
            if (account_internal_dlg->exec() == QDialog::Accepted && !account_internal_dlg->textValue().isNull()) {
                QString input = account_internal_dlg->textValue();
                if (!account_supervisor.accountIsBirthDateCorrect(input)) {
                    continue;
                }
                account_current_birth_date->setText(input);
                return;
            }
            else {
                return;
            }
        }
    }

    if (item == "Номер телефона") {
        while (true) {
            account_internal_dlg->setWindowTitle("Изменение номера телефона");
            account_internal_dlg->setLabelText("Новый номер телефона:");
            account_internal_dlg->resize(300, 300);
            if (account_internal_dlg->exec() == QDialog::Accepted && !account_internal_dlg->textValue().isNull()) {
                QString input = account_internal_dlg->textValue();
                if (!account_supervisor.accountIsNumberCorrect(input)) {
                    continue;
                }
                account_current_phone->setText(account_internal_dlg->textValue());
                return;
            }
            else {
                return;
            }
        }
    }

    if (item == "Email") {
        while (true) {
            account_internal_dlg->setWindowTitle("Изменение Email");
            account_internal_dlg->setLabelText("Новый Email:");
            account_internal_dlg->resize(300, 300);
            if (account_internal_dlg->exec() == QDialog::Accepted && !account_internal_dlg->textValue().isNull()) {
                QString input = account_internal_dlg->textValue();
                if (!account_supervisor.accountIsEmailCorrect(input)) {
                    continue;
                }
                account_current_email->setText(input);
                return;
            }
            else {
                return;
            }
        }
    }
}

void Widget::accountBackHandler() {
    hideAccountUI();
    showMainMenuUI();
}

void Widget::changeVehiclesHandler() {
    hideMainMenuUI();
    QMessageBox msgBox;
    msgBox.setText("Insert known data and click OK. For unknown data click Cancel or don't insert and click OK");
    msgBox.exec();
    bool ok{};
    QString plate = "UNDEFINED", model = "UNDEFINED";
    int lvl = INT_MAX, row = INT_MAX, col = INT_MAX;

    QString input = QInputDialog::getText(this, "Insert data", "plate:", QLineEdit::Normal, QString(), &ok);
    if (!input.isEmpty() && ok) {
        plate = input;
    }

    input = QInputDialog::getText(this, "Insert data", "model:", QLineEdit::Normal, QString(), &ok);
    if (!input.isEmpty() && ok) {
        model = input;
    }

    int num = QInputDialog::getInt(this, "Insert Data", "level", 1, 1, levels.size(), 1, &ok);
    if  (ok) {
        lvl = num - 1;
    }

    num = QInputDialog::getInt(this, "Insert Data", "row", 1, 1, 6, 1, &ok); //если не введен lvl - блокировать дальше?
    if  (ok) {
        row = num - 1;
    }

    num = QInputDialog::getInt(this, "Insert Data", "col", 1, 1, 30, 1, &ok);
    if  (ok) {
        col = num - 1;
    }

    bool flag = false;
    for (int i = 0; i < levels.size(); i++) {
        Level level = levels[i];
        for (int j = 0; j < level.lines.size(); j++) {
            for (int k = 0; k < level.lines[j].size(); k++) {
                Vehicle v = level.lines[j][k];
                if (v.getPlate() == plate) {
                    card.setCardData(v, i, j, k);
                    flag = true;
                    break;
                }
                if (v.getModel() == model) {
                    card.setCardData(v, i, j, k);
                    flag = true;
                    break;
                }
                if (i == lvl && j == row && k == col && !v.getDuration().isNull()) {
                    card.setCardData(v, i, j, k);
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        if (flag) {
            break;
        }
    }
    showChangeVehiclesUI();
}

void Widget::changeVehiclesInternalHandler() {
    QMessageBox msgBox;
    msgBox.setText("Insert data if you want to change it, don't insert or click Cancel otherwise");
    msgBox.exec();

    int curr_lvl = card.lvl_data->text().toInt() - 1;
    int curr_row = card.row_data->text().toInt() - 1;
    int curr_col = card.col_data->text().toInt() - 1;
    Vehicle v = levels[curr_lvl].lines[curr_row][curr_col];

    QString plate, model;
    int lvl, row, col;
    bool ok{};
    QString input = QInputDialog::getText(this, "Insert data", "plate:", QLineEdit::Normal, QString(), &ok);
    if (!input.isEmpty() && ok) {
        v.setPlate(input);
        levels[curr_lvl].lines[curr_row][curr_col] = v;
        card.plate_data->setText(input);
    }

    input = QInputDialog::getText(this, "Insert data", "model:", QLineEdit::Normal, QString(), &ok);
    if (!input.isEmpty() && ok) {
        v.setModel(input);
        levels[curr_lvl].lines[curr_row][curr_col] = v;
        card.model_data->setText(input);
    }

    int num = QInputDialog::getInt(this, "Insert Data", "level", 1, 1, levels.size(), 1, &ok);
    if  (ok) {
        lvl = num - 1;
        levels[lvl].lines[curr_row][curr_col] = v;
        levels[curr_lvl].lines[curr_row][curr_col] = Vehicle();
        curr_lvl = lvl;
        card.lvl_data->setText(QString::number(num));
    }

    num = QInputDialog::getInt(this, "Insert Data", "row", 1, 1, 6, 1, &ok); //если не введен lvl - блокировать дальше?
    if  (ok) {
        row = num - 1;
        levels[curr_lvl].lines[row][curr_col] = v;
        levels[curr_lvl].lines[curr_row][curr_col] = Vehicle();
        curr_row = row;
        card.row_data->setText(QString::number(num));
    }

    num = QInputDialog::getInt(this, "Insert Data", "col", 1, 1, 30, 1, &ok);
    if  (ok) {
        col = num - 1;
        levels[curr_lvl].lines[curr_row][col] = v;
        levels[curr_lvl].lines[curr_row][curr_col] = Vehicle();
        card.col_data->setText(QString::number(num));
    }
}

void Widget::changeVehiclesBackHandler() {
    hideChangeVehiclesUI();
    showMainMenuUI();
}

void Widget::getVehiclesInfoHandler() {
    hideMainMenuUI();
    showGetInfoUI();
}

void Widget::getVehiclesInfoVisualHandler() {
    hideGetInfoUI();
    is_getting_vehicles_info = true;
    update();
    showGetInfoVisualUI();
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
                    card.setCardData(v, i, j, k);
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        if (flag) {
            break;
        }
    }
}

void Widget::getVehiclesInfoDetailedNextFullHandler() { //если мы ушли хотя бы на row дальше чем предыдущее - нужно начинать с начала row/col
    bool flag = false;
    for (int i = card.lvl_data->text().toInt() - 1; i < levels.size(); i++) {
        Level lvl = levels[i];
        int j;
        if (i == card.lvl_data->text().toInt() - 1) {
            j = card.row_data->text().toInt() - 1;
        }
        else {
            j = 0;
        }
        for (; j < lvl.lines.size(); j++) {
            int k;
            if (i == card.lvl_data->text().toInt() - 1 && j == card.row_data->text().toInt() - 1) {
                k = card.col_data->text().toInt();
            }
            else {
                k = 0;
            }
            for (; k < lvl.lines[j].size(); k++) {
                if (!lvl.lines[j][k].getDuration().isNull()) {
                    Vehicle v = lvl.lines[j][k];
                    card.setCardData(v, i, j, k);
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        if (flag) {
            break;
        }
    }
}

void Widget::getVehiclesInfoDetailedPrevFullHandler() {
    bool flag = false;
    for (int i = card.lvl_data->text().toInt() - 1; i >= 0; i--) {
        Level lvl = levels[i];
        int j;
        if (i == card.lvl_data->text().toInt() - 1) {
            j = card.row_data->text().toInt() - 1;
        }
        else {
            j = lvl.lines.size() - 1;
        }
        for (; j >= 0; j--) {
            int k;
            if (i == card.lvl_data->text().toInt() - 1 && j == card.row_data->text().toInt() - 1) {
                k = card.col_data->text().toInt() - 2;
            }
            else {
                k = lvl.lines[j].size() - 1;
            }
            for (; k >= 0; k--) {
                if (!lvl.lines[j][k].getDuration().isNull()) {
                    Vehicle v = lvl.lines[j][k];
                    card.setCardData(v, i, j, k);
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        if (flag) {
            break;
        }
    }
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
                card.setCardData(v, level, j, k);
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
    int level = card.lvl_data->text().toInt() - 1;
    Level lvl = levels[level];
    for (int j = card.row_data->text().toInt() - 1; j < lvl.lines.size(); j++) {
        for (int k = card.col_data->text().toInt(); k < lvl.lines[j].size(); k++) {
            if (!lvl.lines[j][k].getDuration().isNull()) {
                Vehicle v = lvl.lines[j][k];
                card.setCardData(v, level, j, k);
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
    int level = card.lvl_data->text().toInt() - 1;
    Level lvl = levels[level];
    for (int j = card.row_data->text().toInt() - 1; j >= 0; j--) {
        for (int k = card.col_data->text().toInt() - 2; k >= 0; k--) {
            if (!lvl.lines[j][k].getDuration().isNull()) {
                Vehicle v = lvl.lines[j][k];
                card.setCardData(v, level, j, k);
                flag = true;
                break;
            }
        }
        if (flag) {
            break;
        }
    }
}

void Widget::getVehiclesInfoBackHandler() {
    hideGetInfoUI();
    showMainMenuUI();
}

void Widget::getVehiclesInfoVisualBackHandler() {
    hideGetInfoVisualUI();
    showGetInfoUI();
    is_getting_vehicles_info = false;
    update();
}

void Widget::getVehiclesInfoDetailedBackHandler() {
    hideGetInfoDetailedUI();
    showGetInfoUI();
}

void Widget::getVehiclesInfoDetailedInternalBackHandler() {
    hideGetInfoDetailedInternalUI();
    showGetInfoDetailedUI();

    disconnect(get_info_detailed_next_button.get(), nullptr, this, nullptr);
    disconnect(get_info_detailed_prev_button.get(), nullptr, this, nullptr);
}

void Widget::operateHandler() {
    bool ok{};
    int level = QInputDialog::getInt(this, "Выберите этаж", "Этаж", 1, 1, levels.size(), 1, &ok);
    if (!ok) {
        return;
    }
    QString s = "Этаж: ";
    s += QString::number(level);
    operate_current_level->setText(s);
    hideMainMenuUI();
    showOperateUI();
}

void Widget::operateCloseLevelHandler() {
    QString s = operate_current_level->text(); //работает только если этаж - одна цирфа
    int curr_lvl = s.back().digitValue() - 1;
    levels[curr_lvl].close();
}

void Widget::operateAllCeHandler() {
    hideOperateUI();
    showOperateAllCeUI();
    QString s = operate_current_level->text(); //работает только если этаж - одна цирфа
    int curr_lvl = s.back().digitValue() - 1;
    std::shared_ptr<ControlElement> curr_ce = levels[curr_lvl].get_control_elements()[0];
    if (curr_ce->type == TRAFFIC_LIGHT) {
        operate_card_type_data->setText("Traffic Light");
    }
    else {
        operate_card_type_data->setText("Barrier");
    }
    if (curr_ce->get_is_opened()) {
        operate_card_is_opened_data->setText("true");
    }
    else {
        operate_card_is_opened_data->setText("false");
    }
    operate_card_number_data->setText(QString::number(1));
}

void Widget::operateBackHandler() {
    hideOperateUI();
    showMainMenuUI();
}

void Widget::operateCloseCeHandler() {
    QString s = operate_current_level->text(); //работает только если этаж - одна цирфа
    int curr_lvl = s.back().digitValue() - 1;
    int curr_ce = operate_card_number_data->text().toInt() - 1;
    std::shared_ptr<ControlElement> ce = levels[curr_lvl].get_control_elements()[curr_ce];
    ce->close();
    operate_card_is_opened_data->setText("false");
}

void Widget::operateOpenCeHandler() {
    QString s = operate_current_level->text(); //работает только если этаж - одна цирфа
    int curr_lvl = s.back().digitValue() - 1;
    int curr_ce = operate_card_number_data->text().toInt() - 1;
    std::shared_ptr<ControlElement> ce = levels[curr_lvl].get_control_elements()[curr_ce];
    ce->open();
    operate_card_is_opened_data->setText("true");
}

void Widget::operateNextCeHandler() {
    QString s = operate_current_level->text(); //работает только если этаж - одна цирфа
    int curr_lvl = s.back().digitValue() - 1;
    int curr_ce = operate_card_number_data->text().toInt();
    if (curr_ce >= levels[curr_lvl].get_control_elements().size()) {
        return;
    }
    std::shared_ptr<ControlElement> ce = levels[curr_lvl].get_control_elements()[curr_ce];

    if (ce->type == TRAFFIC_LIGHT) {
        operate_card_type_data->setText("Traffic Light");
    }
    else {
        operate_card_type_data->setText("Barrier");
    }
    if (ce->get_is_opened()) {
        operate_card_is_opened_data->setText("true");
    }
    else {
        operate_card_is_opened_data->setText("false");
    }
    operate_card_number_data->setText(QString::number(curr_ce + 1));
}

void Widget::operatePrevCeHandler() {
    QString s = operate_current_level->text(); //работает только если этаж - одна цирфа
    int curr_lvl = s.back().digitValue() - 1;
    int curr_ce = operate_card_number_data->text().toInt() - 2;
    if (curr_ce < 0) {
        return;
    }
    std::shared_ptr<ControlElement> ce = levels[curr_lvl].get_control_elements()[curr_ce];

    if (ce->type == TRAFFIC_LIGHT) {
        operate_card_type_data->setText("Traffic Light");
    }
    else {
        operate_card_type_data->setText("Barrier");
    }
    if (ce->get_is_opened()) {
        operate_card_is_opened_data->setText("true");
    }
    else {
        operate_card_is_opened_data->setText("false");
    }
    operate_card_number_data->setText(QString::number(curr_ce + 1));
}

void Widget::operateAddVehicleHandler() {
    QMessageBox msgBox;
    msgBox.setText("Insert known data and click OK. For unknown data click Cancel or don't insert and click OK");
    msgBox.exec();
    bool ok{};
    QString plate = "UNDEFINED", model = "UNDEFINED";
    int row = INT_MAX, col = INT_MAX;

    QString input = QInputDialog::getText(this, "Insert data", "plate:", QLineEdit::Normal, QString(), &ok);
    if (!input.isEmpty() && ok) {
        plate = input;
    }

    input = QInputDialog::getText(this, "Insert data", "model:", QLineEdit::Normal, QString(), &ok);
    if (!input.isEmpty() && ok) {
        model = input;
    }

    int num = QInputDialog::getInt(this, "Insert Data", "row", 1, 1, 6, 1, &ok); //если не введен lvl - блокировать дальше?
    if  (ok) {
        row = num - 1;
    }

    num = QInputDialog::getInt(this, "Insert Data", "col", 1, 1, 30, 1, &ok);
    if  (ok) {
        col = num - 1;
    }

    Vehicle v;
    v.setModel(model);
    v.setPlate(plate);
    v.updateDuration();
    int lvl = operate_current_level->text().back().digitValue() - 1;
    levels[lvl].lines[row][col] = v;
}

void Widget::operateAddCeHandler() {
    const QStringList items{tr("Светофор"), tr("Шлагбаум")};

    bool ok{};
    QString item;
    operate_dlg->setWindowTitle("Выбор типа УЭ");
    operate_dlg->setComboBoxItems(items);
    operate_dlg->resize(400, 300);
    if (operate_dlg->exec() == QDialog::Accepted) {
        item = operate_dlg->textValue();
    }
    else {
        return;
    }

    if (item == "Светофор") {
        auto ce = std::make_shared<TrafficLight>();
        int lvl = operate_current_level->text().back().digitValue() - 1;
        levels[lvl].add_control_element(ce);
    }

    if (item == "Шлагбаум") {
        auto ce = std::make_shared<Barrier>();
        int lvl = operate_current_level->text().back().digitValue() - 1;
        levels[lvl].add_control_element(ce);
    }
}

void Widget::operateAllCeBackHandler() {
    hideOperateAllCeUI();
    showOperateUI();
}

Widget::~Widget() {
}
