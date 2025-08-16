#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

#include <memory>

#include "trafficlight.h"
#include "barrier.h"
#include "ticket.h"
#include "level.h"
#include "database.h"

class Widget : public QWidget
{
    Q_OBJECT

    TrafficLight tl;
    Barrier br;

    std::unique_ptr<QLabel> login_label;
    std::unique_ptr<QLabel> username_label;
    std::unique_ptr<QLabel> password_label;
    std::unique_ptr<QPushButton> login_push_button;
    std::unique_ptr<QLineEdit> username_line_edit;
    std::unique_ptr<QLineEdit> password_line_edit;

    std::unique_ptr<QPushButton> account_button;
    std::unique_ptr<QPushButton> change_vehicles_info_button;
    std::unique_ptr<QPushButton> get_vehicles_info_button;
    std::unique_ptr<QPushButton> operate_button;

    void hideLoginUI();
    void showMainMenuUI();

public:
    Widget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    void RepositionLoginUI();
    void RepositionMainMenuUI();

    ~Widget();
public slots:
    void loginHandler();
};
#endif // WIDGET_H
