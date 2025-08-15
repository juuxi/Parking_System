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
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter p;
}

void Widget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    RepositionUI();
}

void Widget::RepositionUI() {
    int mid_screen = this->width() / 2;

    login_label->move(mid_screen - 130, 500);
    username_label->move(mid_screen - 280, 550);
    password_label->move(mid_screen - 280, 600);

    username_line_edit->move(mid_screen - 130, 550);
    password_line_edit->move(mid_screen - 130, 600);

    login_push_button->move(mid_screen - 130, 650);
}

void Widget::loginHandler() {
    DataBase db;
    bool is_correct = db.check_login(username_line_edit->text(), password_line_edit->text());
    login_label->setText(QString::number(is_correct));
}

Widget::~Widget() {
    delete login_label;
    delete username_label;
    delete password_label;
    delete login_push_button;
    delete username_line_edit;
    delete password_line_edit;
}
