#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>

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

    QLabel* login_label;
    QLabel* username_label;
    QLabel* password_label;
    QPushButton* login_push_button;
    QLineEdit* username_line_edit;
    QLineEdit* password_line_edit;

public:
    Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    ~Widget();
public slots:
    void loginHandler();
};
#endif // WIDGET_H
