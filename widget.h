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
#include <QGridLayout>
#include <QTime>

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

    std::shared_ptr<TrafficLight> tl;
    std::shared_ptr<Barrier> br;

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

    std::unique_ptr<QGroupBox> change_vehicles_card;
    std::unique_ptr<QLabel> change_vehicles_card_plate_label;
    std::unique_ptr<QLabel> change_vehicles_card_model_label;
    std::unique_ptr<QLabel> change_vehicles_card_enter_time_label;
    std::unique_ptr<QLabel> change_vehicles_card_duration_label;
    std::unique_ptr<QLabel> change_vehicles_card_is_placed_correctly_label;
    std::unique_ptr<QLabel> change_vehicles_card_lvl_label;
    std::unique_ptr<QLabel> change_vehicles_card_row_label;
    std::unique_ptr<QLabel> change_vehicles_card_col_label;
    std::unique_ptr<QLabel> change_vehicles_card_plate_data;
    std::unique_ptr<QLabel> change_vehicles_card_model_data;
    std::unique_ptr<QLabel> change_vehicles_card_enter_time_data;
    std::unique_ptr<QLabel> change_vehicles_card_duration_data;
    std::unique_ptr<QLabel> change_vehicles_card_is_placed_correctly_data;
    std::unique_ptr<QLabel> change_vehicles_card_lvl_data;
    std::unique_ptr<QLabel> change_vehicles_card_row_data;
    std::unique_ptr<QLabel> change_vehicles_card_col_data;
    std::unique_ptr<QPushButton> change_vehicles_card_button;
    std::unique_ptr<QGridLayout> change_vehicles_card_layout;

    std::unique_ptr<QPushButton> get_info_visual_button;
    std::unique_ptr<QPushButton> get_info_detailed_button;
    std::unique_ptr<QPushButton> get_info_detailed_levels_button;
    std::unique_ptr<QPushButton> get_info_detailed_full_button;
    std::unique_ptr<QPushButton> get_info_detailed_next_button;
    std::unique_ptr<QPushButton> get_info_detailed_prev_button;

    std::unique_ptr<QGroupBox> get_info_detailed_card;
    std::unique_ptr<QLabel> get_info_detailed_card_plate_label;
    std::unique_ptr<QLabel> get_info_detailed_card_model_label;
    std::unique_ptr<QLabel> get_info_detailed_card_enter_time_label;
    std::unique_ptr<QLabel> get_info_detailed_card_duration_label;
    std::unique_ptr<QLabel> get_info_detailed_card_is_placed_correctly_label;
    std::unique_ptr<QLabel> get_info_detailed_card_lvl_label;
    std::unique_ptr<QLabel> get_info_detailed_card_row_label;
    std::unique_ptr<QLabel> get_info_detailed_card_col_label;
    std::unique_ptr<QLabel> get_info_detailed_card_plate_data;
    std::unique_ptr<QLabel> get_info_detailed_card_model_data;
    std::unique_ptr<QLabel> get_info_detailed_card_enter_time_data;
    std::unique_ptr<QLabel> get_info_detailed_card_duration_data;
    std::unique_ptr<QLabel> get_info_detailed_card_is_placed_correctly_data;
    std::unique_ptr<QLabel> get_info_detailed_card_lvl_data;
    std::unique_ptr<QLabel> get_info_detailed_card_row_data;
    std::unique_ptr<QLabel> get_info_detailed_card_col_data;
    std::unique_ptr<QGridLayout> get_info_detailed_card_layout;

    std::unique_ptr<QPushButton> operate_close_level_button;
    std::unique_ptr<QLabel> operate_current_level;
    std::unique_ptr<QPushButton> operate_all_ce_button;

    std::unique_ptr<QGroupBox> operate_card;
    std::unique_ptr<QLabel> operate_card_type_label;
    std::unique_ptr<QLabel> operate_card_is_opened_label;
    std::unique_ptr<QLabel> operate_card_type_data;
    std::unique_ptr<QLabel> operate_card_is_opened_data;
    std::unique_ptr<QLabel> operate_card_number_label;
    std::unique_ptr<QLabel> operate_card_number_data;
    std::unique_ptr<QGridLayout> operate_card_layout;


    std::unique_ptr<QPushButton> account_back_button;

    std::unique_ptr<QPushButton> change_vehicles_back_button;

    std::unique_ptr<QPushButton> get_info_detailed_internal_back_button;
    std::unique_ptr<QPushButton> get_info_detailed_back_button;
    std::unique_ptr<QPushButton> get_info_visual_back_button;
    std::unique_ptr<QPushButton> get_info_back_button;

    std::unique_ptr<QPushButton> operate_back_button;

    void hideLoginUI();
    void hideMainMenuUI();
    void hideAccountUI();
    void hideChangeVehiclesUI();
    void hideGetInfoUI();
    void hideGetInfoVisualUI();
    void hideGetInfoDetailedUI();
    void hideGetInfoDetailedInternalUI();
    void hideOperateUI();
    void hideOperateAllCeUI();
    void showMainMenuUI();
    void showAccountUI();
    void showChangeVehiclesUI();
    void showGetInfoUI();
    void showGetInfoVisualUI();
    void showGetInfoDetailedUI();
    void showGetInfoDetailedInternalUI();
    void showOperateUI();
    void showOperateAllCeUI();

    void setCardData(Vehicle, int, int, int);
    void setChangeCardData(Vehicle, int, int, int);

    QVector<Level> levels;

public:
    Widget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    void setupLoginUI();
    void setupMainMenuUI();
    void setupAccountUI();
    void setupGetInfoUI();
    void setupChangeVehiclesUI();
    void setupOperateUI();
    void repositionLoginUI();
    void repositionMainMenuUI();
    void repositionAccountUI();
    void repositionGetInfoUI();
    void repositionOperateUI();

    ~Widget();
public slots:
    void loginHandler();
    void accountHandler();
    void accountChangeHandler();
    void accountBackHandler();
    void changeVehiclesHandler();
    void changeVehiclesInternalHandler();
    void changeVehiclesBackHandler();
    void getVehiclesInfoHandler();
    void getVehiclesInfoVisualHandler();
    void getVehiclesInfoDetailedHandler();
    void getVehiclesInfoDetailedFullHandler();
    void getVehiclesInfoDetailedNextFullHandler();
    void getVehiclesInfoDetailedPrevFullHandler();
    void getVehiclesInfoDetailedNextLevelsHandler();
    void getVehiclesInfoDetailedPrevLevelsHandler();
    void getVehiclesInfoDetailedLevelsHandler();
    void getVehiclesInfoBackHandler();
    void getVehiclesInfoVisualBackHandler();
    void getVehiclesInfoDetailedBackHandler();
    void getVehiclesInfoDetailedInternalBackHandler();
    void operateHandler();
    void operateCloseLevelHandler();
    void operateBackHandler();
    void operateAllCeHandler();
};
#endif // WIDGET_H
