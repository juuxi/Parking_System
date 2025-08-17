#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Парковочная система");
    setWindowState(Qt::WindowMaximized);
    setupLoginUI();
    setupMainMenuUI();
    setupAccountUI();

    Level lvl;
    QVector<Level> vec;
    vec.push_back(lvl);
    vec.push_back(lvl);
    Xml xml;
    xml.write(vec);
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

void Widget::paintEvent(QPaintEvent*) {
    QPainter p;
}

void Widget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    repositionLoginUI();
    repositionMainMenuUI();
    repositionAccountUI();
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

Widget::~Widget() {
}
