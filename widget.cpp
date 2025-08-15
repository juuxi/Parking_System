#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Парковочная система");
    setWindowState(Qt::WindowMaximized);

    login_label = new QLabel("Введите имя пользователя и пароль", this);
    login_label->setFixedSize(260, 30);

    username_label = new QLabel("Имя пользователя: ", this);
    username_label->setFixedSize(150, 30);

    password_label = new QLabel("Пароль: ", this);
    password_label->setFixedSize(150, 30);

    username_line_edit = new QLineEdit(this);
    username_line_edit->setFixedSize(260, 30);

    password_line_edit = new QLineEdit(this);
    password_line_edit->setFixedSize(260, 30);

    login_push_button = new QPushButton("Log in", this);
    login_push_button->setFixedSize(260, 80);
    connect(login_push_button, SIGNAL(clicked()), this, SLOT(loginHandler()));


    account_button = new QPushButton("Account", this);
    account_button->hide();

    change_vehicles_info_button = new QPushButton("Change Vehicles", this);
    change_vehicles_info_button->hide();

    get_vehicles_info_button = new QPushButton("Get Vehicles Info", this);
    get_vehicles_info_button->hide();

    operate_button = new QPushButton("Operate", this);
    operate_button->hide();
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

    login_label->move(mid_screen - 130, 500);
    username_label->move(mid_screen - 280, 550);
    password_label->move(mid_screen - 280, 600);

    username_line_edit->move(mid_screen - 130, 550);
    password_line_edit->move(mid_screen - 130, 600);

    login_push_button->move(mid_screen - 130, 650);
}

void Widget::RepositionMainMenuUI() {
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

void Widget::hideLoginUI() {
    login_label->hide();
    username_label->hide();
    password_label->hide();
    username_line_edit->hide();
    password_line_edit->hide();
    login_push_button->hide();
}

void Widget::showMainMenuUI() {
    account_button->show();
    change_vehicles_info_button->show();
    get_vehicles_info_button->show();
    operate_button->show();
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

Widget::~Widget() {
    delete login_label;
    delete username_label;
    delete password_label;
    delete login_push_button;
    delete username_line_edit;
    delete password_line_edit;

    delete account_button;
    delete change_vehicles_info_button;
    delete get_vehicles_info_button;
    delete operate_button;
}
