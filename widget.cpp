#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), levels(6) {
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
    connect(change_vehicles_info_button.get(), SIGNAL(clicked()), this, SLOT(changeVehiclesHandler()));

    get_vehicles_info_button = std::make_unique<QPushButton>("Get Vehicles Info", this);
    get_vehicles_info_button.get()->hide();
    connect(get_vehicles_info_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoHandler()));

    operate_button = std::make_unique<QPushButton>("Operate", this);
    operate_button.get()->hide();
    connect(operate_button.get(), SIGNAL(clicked()), this, SLOT(operateHandler()));
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

    account_back_button = std::make_unique<QPushButton>("Back", this);
    account_back_button.get()->setGeometry(10, 10, 50, 20);
    connect(account_back_button.get(), SIGNAL(clicked()), this, SLOT(accountBackHandler()));

    account_internal_dlg = std::make_unique<QInputDialog>(this);
    account_dlg = std::make_unique<QInputDialog>(this);

    hideAccountUI();
}

void Widget::setupChangeVehiclesUI()  {
    change_vehicles_card = std::make_unique<QGroupBox>("Инофрмация о ТС", this);

    change_vehicles_card_plate_label = std::make_unique<QLabel>("plate: ", this);
    change_vehicles_card_model_label = std::make_unique<QLabel>("model: ", this);
    change_vehicles_card_enter_time_label = std::make_unique<QLabel>("enter_time: ", this);
    change_vehicles_card_duration_label = std::make_unique<QLabel>("duration: ", this);
    change_vehicles_card_is_placed_correctly_label = std::make_unique<QLabel>("is_placed_correctly: ", this);
    change_vehicles_card_lvl_label = std::make_unique<QLabel>("level: ", this);
    change_vehicles_card_row_label = std::make_unique<QLabel>("row: ", this);
    change_vehicles_card_col_label = std::make_unique<QLabel>("column: ", this);

    change_vehicles_card_plate_data = std::make_unique<QLabel>(this);
    change_vehicles_card_model_data = std::make_unique<QLabel>(this);
    change_vehicles_card_enter_time_data = std::make_unique<QLabel>(this);
    change_vehicles_card_duration_data = std::make_unique<QLabel>(this);
    change_vehicles_card_is_placed_correctly_data = std::make_unique<QLabel>(this);
    change_vehicles_card_lvl_data = std::make_unique<QLabel>(this);
    change_vehicles_card_row_data = std::make_unique<QLabel>(this);
    change_vehicles_card_col_data = std::make_unique<QLabel>(this);

    change_vehicles_card_button = std::make_unique<QPushButton>("Change", this);
    connect(change_vehicles_card_button.get(), SIGNAL(clicked()), this, SLOT(changeVehiclesInternalHandler()));

    change_vehicles_card_layout = std::make_unique<QGridLayout>(this);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_plate_label.get(), 0, 0, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_model_label.get(), 1, 0, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_enter_time_label.get(), 2, 0, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_duration_label.get(), 3, 0, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_is_placed_correctly_label.get(), 4, 0, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_lvl_label.get(), 5, 0, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_row_label.get(), 6, 0, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_col_label.get(), 7, 0, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_plate_data.get(), 0, 1, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_model_data.get(), 1, 1, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_enter_time_data.get(), 2, 1, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_duration_data.get(), 3, 1, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_is_placed_correctly_data.get(), 4, 1, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_lvl_data.get(), 5, 1, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_row_data.get(), 6, 1, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_col_data.get(), 7, 1, 1, 1);
    change_vehicles_card_layout.get()->addWidget(change_vehicles_card_button.get(), 8, 1, 1, 2);
    change_vehicles_card.get()->setLayout(change_vehicles_card_layout.get());

    change_vehicles_back_button = std::make_unique<QPushButton>("Back", this);
    change_vehicles_back_button.get()->setGeometry(10, 10, 50, 20);
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

    get_info_back_button = std::make_unique<QPushButton>("Back", this);
    get_info_back_button.get()->setGeometry(10, 10, 50, 20);
    connect(get_info_back_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoBackHandler()));

    get_info_detailed_back_button = std::make_unique<QPushButton>("Back", this);
    get_info_detailed_back_button.get()->setGeometry(10, 10, 50, 20);
    connect(get_info_detailed_back_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedBackHandler()));

    get_info_detailed_internal_back_button = std::make_unique<QPushButton>("Back", this);
    get_info_detailed_internal_back_button.get()->setGeometry(10, 10, 50, 20);
    connect(get_info_detailed_internal_back_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoDetailedInternalBackHandler()));

    get_info_visual_back_button = std::make_unique<QPushButton>("Back", this);
    get_info_visual_back_button.get()->setGeometry(10, 10, 50, 20);
    connect(get_info_visual_back_button.get(), SIGNAL(clicked()), this, SLOT(getVehiclesInfoVisualBackHandler()));

    hideGetInfoUI();
    hideGetInfoVisualUI();
    hideGetInfoDetailedUI();
    hideGetInfoDetailedInternalUI();
}

void Widget::setupOperateUI() {
    operate_close_level_button = std::make_unique<QPushButton>("Закрыть этаж", this);
    connect(operate_close_level_button.get(), SIGNAL(clicked()), this, SLOT(operateCloseLevelHandler()));
    operate_close_level_button->setFixedSize(200, 50);

    operate_back_button = std::make_unique<QPushButton>("Back", this);
    connect(operate_back_button.get(), SIGNAL(clicked()), this, SLOT(operateBackHandler()));
    operate_back_button.get()->setGeometry(10, 10, 50, 20);

    operate_all_ce_button = std::make_unique<QPushButton>("Все УЭ", this);
    connect(operate_all_ce_button.get(), SIGNAL(clicked()), this, SLOT(operateAllCeHandler()));
    operate_all_ce_button.get()->setFixedSize(200, 50);

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
    operate_close_ce_button.get()->setFixedSize(100, 50);

    operate_open_ce_button = std::make_unique<QPushButton>("Открыть", this);
    connect(operate_open_ce_button.get(), SIGNAL(clicked()), this, SLOT(operateOpenCeHandler()));
    operate_open_ce_button.get()->setFixedSize(100, 50);

    operate_next_ce_button = std::make_unique<QPushButton>("Next >", this);
    connect(operate_next_ce_button.get(), SIGNAL(clicked()), this, SLOT(operateNextCeHandler()));
    operate_next_ce_button.get()->setFixedSize(75, 30);

    operate_prev_ce_button = std::make_unique<QPushButton>("< Prev", this);
    connect(operate_prev_ce_button.get(), SIGNAL(clicked()), this, SLOT(operatePrevCeHandler()));
    operate_prev_ce_button.get()->setFixedSize(75, 30);

    operate_card_layout = std::make_unique<QGridLayout>(this);
    operate_card_layout->addWidget(operate_card_type_label.get(), 0, 0, 1, 1);
    operate_card_layout->addWidget(operate_card_type_data.get(), 0, 1, 1, 1);
    operate_card_layout->addWidget(operate_card_is_opened_label.get(), 1, 0, 1, 1);
    operate_card_layout->addWidget(operate_card_is_opened_data.get(), 1, 1, 1, 1);
    operate_card_layout->addWidget(operate_card_number_label.get(), 2, 0, 1, 1);
    operate_card_layout->addWidget(operate_card_number_data.get(), 2, 1, 1, 1);
    operate_card.get()->setLayout(operate_card_layout.get());

    operate_all_ce_back_button = std::make_unique<QPushButton>("Back", this);
    connect(operate_all_ce_back_button.get(), SIGNAL(clicked()), this, SLOT(operateAllCeBackHandler()));
    operate_all_ce_back_button.get()->setGeometry(10, 10, 50, 20);

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

void Widget::repositionOperateUI() {
    int screen_width = this->width();
    int screen_height = this->height();
    operate_close_level_button->move(screen_width / 2 - operate_close_level_button->width() / 2,
                                     screen_height / 2 - operate_close_level_button->height());

    operate_all_ce_button->move(screen_width / 2 - operate_all_ce_button->width() / 2,
                                screen_height / 2);

    operate_current_level->move(screen_width / 2 - operate_current_level->width() / 2,
                                screen_height / 4 - operate_current_level->height() / 2);

    operate_card->move(screen_width / 2 - operate_card->width() / 2,
                       screen_height / 4 - operate_card->height() / 2);


    operate_close_ce_button->move(5 * screen_width / 8, 5 * screen_height / 8);
    operate_open_ce_button->move(3 * screen_width / 8, 5 * screen_height / 8);

    operate_next_ce_button->move(3 * screen_width / 4, 3 * screen_height / 4);
    operate_prev_ce_button->move(screen_width / 4, 3 * screen_height / 4);
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

    account_back_button.get()->hide();
}

void Widget::hideChangeVehiclesUI() {
    change_vehicles_card->hide();
    change_vehicles_back_button->hide();
}

void Widget::hideGetInfoUI() {
    get_info_visual_button.get()->hide();
    get_info_detailed_button.get()->hide();
    get_info_back_button.get()->hide();
}

void Widget::hideGetInfoVisualUI() {
    get_info_visual_back_button->hide();
}

void Widget::hideGetInfoDetailedUI() {
    get_info_detailed_levels_button.get()->hide();
    get_info_detailed_full_button.get()->hide();
    get_info_detailed_back_button.get()->hide();
}

void Widget::hideGetInfoDetailedInternalUI() {
    get_info_detailed_next_button->hide();
    get_info_detailed_prev_button->hide();
    get_info_detailed_card->hide();
    get_info_detailed_internal_back_button->hide();
}

void Widget::hideOperateUI() {
    operate_close_level_button->hide();
    operate_current_level->hide();
    operate_back_button->hide();
    operate_all_ce_button->hide();
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

    account_back_button.get()->show();
}

void Widget::showChangeVehiclesUI() {
    change_vehicles_card->show();
    change_vehicles_back_button->show();
}

void Widget::showGetInfoUI() {
    get_info_visual_button.get()->show();
    get_info_detailed_button.get()->show();
    get_info_back_button.get()->show();
}

void Widget::showGetInfoVisualUI() {
    get_info_visual_back_button->show();
}

void Widget::showGetInfoDetailedUI() {
    get_info_detailed_levels_button.get()->show();
    get_info_detailed_full_button.get()->show();
    get_info_detailed_back_button.get()->show();
}

void Widget::showGetInfoDetailedInternalUI() {
    get_info_detailed_next_button->show();
    get_info_detailed_prev_button->show();
    get_info_detailed_card->show();
    get_info_detailed_internal_back_button->show();
}

void Widget::showOperateUI() {
    operate_close_level_button->show();
    operate_current_level->show();
    operate_back_button->show();
    operate_all_ce_button->show();
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
    account_dlg.get()->setWindowTitle("Изменение информации аккаунта");
    account_dlg.get()->setLabelText("Что изменить?");
    account_dlg.get()->setComboBoxItems(items);
    account_dlg.get()->resize(400, 300);
    account_dlg.get()->move(1000, 500);
    if (account_dlg.get()->exec() == QDialog::Accepted) {
        item = account_dlg.get()->textValue();
    }
    else {
        return;
    }

    if (item == "ФИО") {
        account_internal_dlg.get()->setWindowTitle("Изменение ФИО");
        account_internal_dlg.get()->setLabelText("Новое ФИО:");
        account_internal_dlg.get()->resize(300, 300);
        if (account_internal_dlg.get()->exec() == QDialog::Accepted && !account_internal_dlg.get()->textValue().isNull()) {
            QString input = account_internal_dlg.get()->textValue();
            account_current_name->setText(input);
        }
        else {
            return;
        }
    }

    if (item == "Дата рождения") {
        while (true) {
            account_internal_dlg.get()->setWindowTitle("Изменение даты рождения");
            account_internal_dlg.get()->setLabelText("Новая дата рождения:");
            account_internal_dlg.get()->resize(300, 300);
            if (account_internal_dlg.get()->exec() == QDialog::Accepted && !account_internal_dlg.get()->textValue().isNull()) {
                QString input = account_internal_dlg.get()->textValue();
                if (!accountIsBirthDateCorrect(input)) {
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
            account_internal_dlg.get()->setWindowTitle("Изменение номера телефона");
            account_internal_dlg.get()->setLabelText("Новый номер телефона:");
            account_internal_dlg.get()->resize(300, 300);
            if (account_internal_dlg.get()->exec() == QDialog::Accepted && !account_internal_dlg.get()->textValue().isNull()) {
                QString input = account_internal_dlg.get()->textValue();
                if (!accountIsNumberCorrect(input)) {
                    continue;
                }
                account_current_phone->setText(account_internal_dlg.get()->textValue());
                return;
            }
            else {
                return;
            }
        }
    }

    if (item == "Email") {
        while (true) {
            account_internal_dlg.get()->setWindowTitle("Изменение Email");
            account_internal_dlg.get()->setLabelText("Новый Email:");
            account_internal_dlg.get()->resize(300, 300);
            if (account_internal_dlg.get()->exec() == QDialog::Accepted && !account_internal_dlg.get()->textValue().isNull()) {
                QString input = account_internal_dlg.get()->textValue();
                if (!accountIsEmailCorrect(input)) {
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

bool Widget::accountIsNumberCorrect(QString input) {
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

bool Widget::accountIsBirthDateCorrect(QString input) {
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

bool Widget::accountIsEmailCorrect(QString input) {
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
                    setChangeCardData(v, i, j, k);
                    flag = true;
                    break;
                }
                if (v.getModel() == model) {
                    setChangeCardData(v, i, j, k);
                    flag = true;
                    break;
                }
                if (i == lvl && j == row && k == col && !v.getDuration().isNull()) {
                    setChangeCardData(v, i, j, k);
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

void Widget::setChangeCardData(Vehicle v, int i, int j, int k) {
    change_vehicles_card_plate_data->setText(v.getPlate());
    change_vehicles_card_model_data->setText(v.getModel());
    change_vehicles_card_enter_time_data->setText(v.getEnterTime().toString());
    change_vehicles_card_duration_data->setText(v.getDuration().toString());
    change_vehicles_card_is_placed_correctly_data->setText(QString::number(v.getIsPlacedCorrectly()));
    change_vehicles_card_lvl_data->setText(QString::number(i + 1));
    change_vehicles_card_row_data->setText(QString::number(j + 1));
    change_vehicles_card_col_data->setText(QString::number(k + 1));
}

void Widget::changeVehiclesInternalHandler() {
    QMessageBox msgBox;
    msgBox.setText("Insert data if you want to change it, don't insert or click Cancel otherwise");
    msgBox.exec();

    int curr_lvl = change_vehicles_card_lvl_data->text().toInt() - 1;
    int curr_row = change_vehicles_card_row_data->text().toInt() - 1;
    int curr_col = change_vehicles_card_col_data->text().toInt() - 1;
    Vehicle v = levels[curr_lvl].lines[curr_row][curr_col];

    QString plate, model;
    int lvl, row, col;
    bool ok{};
    QString input = QInputDialog::getText(this, "Insert data", "plate:", QLineEdit::Normal, QString(), &ok);
    if (!input.isEmpty() && ok) {
        v.setPlate(input);
        levels[curr_lvl].lines[curr_row][curr_col] = v;
        change_vehicles_card_plate_data->setText(input);
    }

    input = QInputDialog::getText(this, "Insert data", "model:", QLineEdit::Normal, QString(), &ok);
    if (!input.isEmpty() && ok) {
        v.setModel(input);
        levels[curr_lvl].lines[curr_row][curr_col] = v;
        change_vehicles_card_model_data->setText(input);
    }

    int num = QInputDialog::getInt(this, "Insert Data", "level", 1, 1, levels.size(), 1, &ok);
    if  (ok) {
        lvl = num - 1;
        levels[lvl].lines[curr_row][curr_col] = v;
        levels[curr_lvl].lines[curr_row][curr_col] = Vehicle();
        curr_lvl = lvl;
        change_vehicles_card_lvl_data->setText(QString::number(num));
    }

    num = QInputDialog::getInt(this, "Insert Data", "row", 1, 1, 6, 1, &ok); //если не введен lvl - блокировать дальше?
    if  (ok) {
        row = num - 1;
        levels[curr_lvl].lines[row][curr_col] = v;
        levels[curr_lvl].lines[curr_row][curr_col] = Vehicle();
        curr_row = row;
        change_vehicles_card_row_data->setText(QString::number(num));
    }

    num = QInputDialog::getInt(this, "Insert Data", "col", 1, 1, 30, 1, &ok);
    if  (ok) {
        col = num - 1;
        levels[curr_lvl].lines[curr_row][col] = v;
        levels[curr_lvl].lines[curr_row][curr_col] = Vehicle();
        change_vehicles_card_col_data->setText(QString::number(num));
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
    if (curr_ce.get()->type == TRAFFIC_LIGHT) {
        operate_card_type_data->setText("Traffic Light");
    }
    else {
        operate_card_type_data->setText("Barrier");
    }
    if (curr_ce.get()->get_is_opened()) {
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
    ce.get()->close();
    operate_card_is_opened_data->setText("false");
}

void Widget::operateOpenCeHandler() {
    QString s = operate_current_level->text(); //работает только если этаж - одна цирфа
    int curr_lvl = s.back().digitValue() - 1;
    int curr_ce = operate_card_number_data->text().toInt() - 1;
    std::shared_ptr<ControlElement> ce = levels[curr_lvl].get_control_elements()[curr_ce];
    ce.get()->open();
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

    if (ce.get()->type == TRAFFIC_LIGHT) {
        operate_card_type_data->setText("Traffic Light");
    }
    else {
        operate_card_type_data->setText("Barrier");
    }
    if (ce.get()->get_is_opened()) {
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

    if (ce.get()->type == TRAFFIC_LIGHT) {
        operate_card_type_data->setText("Traffic Light");
    }
    else {
        operate_card_type_data->setText("Barrier");
    }
    if (ce.get()->get_is_opened()) {
        operate_card_is_opened_data->setText("true");
    }
    else {
        operate_card_is_opened_data->setText("false");
    }
    operate_card_number_data->setText(QString::number(curr_ce + 1));
}

void Widget::operateAllCeBackHandler() {
    hideOperateAllCeUI();
    showOperateUI();
}

Widget::~Widget() {
}
