//
// Created by ernest on 20-01-21.
//

#include "../device.h"

Fridge::Fridge(int fd, std::string clientName, std::string senderName) {
    this-> fd = fd;
    this-> clientName = clientName;
    this->senderName = senderName;
    this-> wemosType = "fridge";
}
Fridge::~Fridge() {
}

std::string Fridge::handleSensorUpdate(XmlReader * xml_r) {
    /* init variables to be used */
    std::string destination;
    std::vector<float> sentStatus;
    std::vector<float> sendStatus;

    destination = xml_r->getSenderName();
    sentStatus = xml_r->getData();

    std::string toBeReturned;

    /*
        Sensors order:
        1: switch
        2: NTC (koelkast)
        3: NTC (peltier)

        Actuators:
        1. fan peltier
        2. peltier

        Logic:
            if switch == false
                peltier = 0
            else if switch == true && NTC (koelkast) > -30
                peltier = 1
            else if switch == true && NTC (koelkast) < -35
                peltier = 0

            if NTC (peltier) > 60
                fan = 1
            else
                fan = 0
    */

    if((int)std::round(sentStatus[0]) == false){
        sendStatus.push_back(0);
    }else if((int)std::round(sentStatus[1]) == true && sentStatus[2] >= -30){
        sendStatus.push_back(1);
    }else if((int)std::round(sentStatus[1]) == true && sentStatus[2] <= -35){
        sendStatus.push_back(0);
    }else{
        sendStatus.push_back(1);
    }

    if(sentStatus[2] > 60){
        sendStatus.push_back(1);
    }else{
        sendStatus.push_back(0);
    }


    XmlWriter xml_w("actuateBool", destination);
    xml_w.buildXMLActuate(sendStatus);
    toBeReturned = xml_w.getXML();
    xml_w.~XmlWriter();
    return toBeReturned;
}

std::string Fridge::handleWebsiteUpdate(XmlReader * xml_r, int i) {
    std::vector<float> data;
    std::string destination;
    destination = xml_r->getClientName();
    std::string toBeSend;

    if (i == 1){
        data.push_back(1);
        data.push_back(1);
    }else {
        data.push_back(0);
        data.push_back(0);
    }

    XmlWriter xml_w("actuateBool", destination);
    xml_w.buildXMLActuate(data);
    toBeSend = xml_w.getXML();
    xml_w.~XmlWriter();
    return toBeSend;
}
