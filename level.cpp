#include "level.h"

Level::Level() : serial_number(0), lines(5, QVector<Vehicle>(30, Vehicle())), is_opened(true) {}

Level::Level(int num) : serial_number(num), is_opened(true) {}

void Level::add_vehicle(Vehicle v, int line, int pos) {
    lines[line][pos] = v;
}

void Level::remove_vehicle(Vehicle v) {
    for (int row = 0; row < lines.size(); row++) {
        for (int col = 0; col < lines[row].size(); col++) {
            if (lines[row][col] == v) {
                lines[row][col] = Vehicle();
            }
        }
    }
}

void Level::add_control_element(std::shared_ptr<ControlElement> ce) {
    control_elements.push_back(ce);
}

void Level::remove_control_element(std::shared_ptr<ControlElement> ce) {
    const auto to_del = std::find(control_elements.begin(), control_elements.end(), ce);
    if (to_del != control_elements.end()) {
        control_elements.erase(to_del);
    }
}

void Level::drawLine(const QVector<Vehicle>& line, int index, QPainter* p) {
    int line_height = p->device()->height() / lines.size();
    int spot_width = p->device()->width() / line.size();
    for (int i = 0; i < line.size(); i++) {
        if (line[i].getDuration().isNull()) {
            p->setBrush(QBrush(QColor(0, 255, 0)));
        }
        else {
            p->setBrush(QBrush(QColor(255, 0, 0)));
        }
        p->drawRect(i * spot_width, line_height * index, spot_width, line_height);
    }
}

void Level::draw(QPainter* p) {
    int index = 0;
    for (const auto& line : lines) {
        drawLine(line, index, p);
        index++;
    }
}
