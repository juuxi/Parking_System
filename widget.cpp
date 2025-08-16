#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Парковочная система");
    setWindowState(Qt::WindowMaximized);

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


    account_button = std::make_unique<QPushButton>("Account", this);
    account_button.get()->hide();

    change_vehicles_info_button = std::make_unique<QPushButton>("Change Vehicles", this);
    change_vehicles_info_button.get()->hide();

    get_vehicles_info_button = std::make_unique<QPushButton>("Get Vehicles Info", this);
    get_vehicles_info_button.get()->hide();

    operate_button = std::make_unique<QPushButton>("Operate", this);
    operate_button.get()->hide();
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter p;
}

void Widget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    RepositionLoginUI();
    RepositionMainMenuUI();
}

void Widget::RepositionLoginUI() {
    int mid_screen = this->width() / 2;

    login_label.get()->move(mid_screen - 130, 500);
    username_label.get()->move(mid_screen - 280, 550);
    password_label.get()->move(mid_screen - 280, 600);

    username_line_edit.get()->move(mid_screen - 130, 550);
    password_line_edit.get()->move(mid_screen - 130, 600);

    login_push_button.get()->move(mid_screen - 130, 650);
}

void Widget::RepositionMainMenuUI() {
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

void Widget::hideLoginUI() {
    login_label.get()->hide();
    username_label.get()->hide();
    password_label.get()->hide();
    username_line_edit.get()->hide();
    password_line_edit.get()->hide();
    login_push_button.get()->hide();
}

void Widget::showMainMenuUI() {
    account_button.get()->show();
    change_vehicles_info_button.get()->show();
    get_vehicles_info_button.get()->show();
    operate_button.get()->show();
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

Widget::~Widget() {
}
