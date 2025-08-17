#include "xml.h"

Xml::Xml() {}

void Xml::write() {
    QString file_path = "../../2d.xml";
    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);

    xml.writeStartDocument();
    xml.writeStartElement("Parking");

    for (int i = 0; i < 15; i++) {
        xml.writeStartElement("Floor");
        xml.writeAttribute("width", QString::number(1));
        xml.writeAttribute("length", QString::number(2));
        for (int j = 0; j < 10; j++) {
            xml.writeStartElement("Line");
            xml.writeAttribute("length", QString::number(3));
            for (int k = 0; k < 5; k++) {
                xml.writeStartElement("Spot");
                xml.writeAttribute("taken", QString::number(false));
                xml.writeEndElement(); //Spot
            }
            xml.writeEndElement(); //Line
        }
        xml.writeEndElement(); //Floor
    }

    xml.writeEndElement(); // Parking
    xml.writeEndDocument();

    file.close();
}
