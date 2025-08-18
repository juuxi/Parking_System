#include "xml.h"

Xml::Xml() {}

void Xml::write(QVector<Level> levels) {
    QString file_path = "../../2d.xml";
    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);

    xml.writeStartDocument();
    xml.writeStartElement("Parking");

    for (const auto& level : levels) {
        xml.writeStartElement("Level");
        xml.writeAttribute("width", QString::number(level.lines.size()));
        xml.writeAttribute("length", QString::number(2));
        for (const auto& line: level.lines) {
            xml.writeStartElement("Line");
            xml.writeAttribute("length", QString::number(line.size()));
            for (const auto& v : line) {
                xml.writeStartElement("Spot");
                if (v.getDuration().isNull()) {
                    xml.writeAttribute("taken", "false");
                }
                else {
                    xml.writeAttribute("taken", "true");
                }
                xml.writeEndElement(); //Spot
            }
            xml.writeEndElement(); //Line
        }
        xml.writeEndElement(); //Level
    }

    xml.writeEndElement(); // Parking
    xml.writeEndDocument();

    file.close();
}
