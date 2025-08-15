#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Парковочная система");
    setWindowState(Qt::WindowMaximized);

    int mid_screen = 1180; //to be changed later via moves and resize event

    login_label = new QLabel("Введите имя пользователя и пароль", this);
    login_label->setGeometry(mid_screen - 130, 500, 260, 30);

    username_label = new QLabel("Имя пользователя: ", this);
    username_label->setGeometry(mid_screen - 280, 550, 150, 30);

    password_label = new QLabel("Пароль: ", this);
    password_label->setGeometry(mid_screen - 280, 600, 150, 30);

    username_line_edit = new QLineEdit(this);
    username_line_edit->setGeometry(mid_screen - 130, 550, 260, 30);

    password_line_edit = new QLineEdit(this);
    password_line_edit->setGeometry(mid_screen - 130, 600, 260, 30);

    login_push_button = new QPushButton("Log in", this);
    login_push_button->setGeometry(mid_screen - 130, 650, 260, 80);
    connect(login_push_button, SIGNAL(clicked()), this, SLOT(loginHandler()));

    DataBase db;
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter p;
    p.begin(this);
    tl.draw(&p);
    br.draw(&p);
    p.end();
}

void Widget::loginHandler() {
    if (username_line_edit->text() == "admin" && password_line_edit->text() == "admin_pwd") {
        login_label->setText("true");
        return;
    }
    login_label->setText("false");
}

Widget::~Widget() {
    delete login_label;
    delete username_label;
    delete password_label;
    delete login_push_button;
    delete username_line_edit;
    delete password_line_edit;
}
