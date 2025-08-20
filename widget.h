#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <QGroupBox>
#include <QVBoxLayout>

#include <memory>

#include "trafficlight.h"
#include "barrier.h"
#include "ticket.h"
#include "level.h"
#include "database.h"
#include "xml.h"

class Widget : public QWidget
{
    Q_OBJECT

    TrafficLight tl;
    Barrier br;

    bool is_getting_vehicles_info;

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

    std::unique_ptr<QLabel> account_name_label;
    std::unique_ptr<QLabel> account_birth_date_label;
    std::unique_ptr<QLabel> account_phone_label;
    std::unique_ptr<QLabel> account_email_label;
    std::unique_ptr<QLabel> account_current_name;
    std::unique_ptr<QLabel> account_current_birth_date;
    std::unique_ptr<QLabel> account_current_phone;
    std::unique_ptr<QLabel> account_current_email;
    std::unique_ptr<QPushButton> account_change_button;

    std::unique_ptr<QPushButton> get_info_visual_button;
    std::unique_ptr<QPushButton> get_info_detailed_button;
    std::unique_ptr<QPushButton> get_info_detailed_levels_button;
    std::unique_ptr<QPushButton> get_info_detailed_full_button;
    std::unique_ptr<QPushButton> get_info_detailed_next_button;
    std::unique_ptr<QPushButton> get_info_detailed_prev_button;

    std::unique_ptr<QGroupBox> info;
    std::unique_ptr<QLabel> plate;
    std::unique_ptr<QLabel> model;
    std::unique_ptr<QLabel> enter_time;
    std::unique_ptr<QLabel> duration;
    std::unique_ptr<QLabel> is_placed_correctly;
    std::unique_ptr<QVBoxLayout> vbox;

    void hideLoginUI();
    void hideMainMenuUI();
    void hideAccountUI();
    void hideGetInfoUI();
    void hideGetInfoDetailedUI();
    void hideGetInfoDetailedFullUI();
    void showMainMenuUI();
    void showAccountUI();
    void showGetInfoUI();
    void showGetInfoDetailedUI();
    void showGetInfoDetailedFullUI();

public:
    Widget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    void setupLoginUI();
    void setupMainMenuUI();
    void setupAccountUI();
    void setupGetInfoUI();
    void repositionLoginUI();
    void repositionMainMenuUI();
    void repositionAccountUI();
    void repositionGetInfoUI();

    ~Widget();
public slots:
    void loginHandler();
    void accountHandler();
    void accountChangeHandler();
    void getVehiclesInfoHandler();
    void getVehiclesInfoVisualHandler();
    void getVehiclesInfoDetailedHandler();
    void getVehiclesInfoDetailedFullHandler();
};
#endif // WIDGET_H
