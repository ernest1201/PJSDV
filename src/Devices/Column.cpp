//
// Created by ernest on 20-01-21.
//

#include "../device.h"

Column::Column(int fd, std::string clientName, std::string senderName){
    this->fd = fd;
    this->clientName = clientName;
    this->senderName = senderName;
    this->wemosType = "column";
}


Column::~Column(){

}

std::string Column::handleSensorUpdate(XmlReader* xml_r) {
    std::string destination;
    std::vector<double> sentStatus;
    std::vector<double> sendStatus;

    destination = xml_r->getSenderName();
    sentStatus = xml_r->getData();

    /*
        push button and gas sensor
        if pushbutton == 1 ---> LED = 1
        if gas sensor == 1 ---> buzzer = 1
    */
    if (std::round(sentStatus[0]) == 1) {
        sendStatus.push_back(1);
        stateLED = 1;
    } else {
        sendStatus.push_back(0);
        stateLED = 0;
    }

    if (std::round(sentStatus[1]) == 1) {
        sendStatus.push_back(1);
        stateBuzzer = 1;
    } else {
        sendStatus.push_back(0);
        stateBuzzer = 0;
    }

    XmlWriter xml_w("actuateBool", destination);
    xml_w.buildXMLActuate(sendStatus);
    std::string toBeReturned = xml_w.getXML();
    return toBeReturned;
}