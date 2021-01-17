#pragma once

#include "wrapper.h"
#include "xmlreader.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

class XmlWriter{
private:
    //Support variables
    std::string function;
    std::string senderName;
    std::string receiverName;
    std::string clientName;

    //RapidXML variables
    rapidxml::xml_document<> *doc;
    rapidxml::xml_node<> *root_node;
    rapidxml::xml_node<> *header_node;
    rapidxml::xml_node<> *sender_node;
    rapidxml::xml_node<> *receiver_node;
    rapidxml::xml_node<> *function_node;
    rapidxml::xml_node<> *context_node;

    //Different function context builders
    void buildHeader();
    void buildAckContext();
    void buildActuateBoolContext(std::string actuatorName, int status);

public:
    XmlWriter();
    /* Type is the function that is sent in the final message, 
    dest is the sendername from whence your message came*/
    XmlWriter(std::string type, std::string dest);
    XmlWriter(XmlReader &xml_r);

    ~XmlWriter();

    void buildXMLAck();

    void buildXMLActuateBool(std::string actuatorName, bool status);
    //Getters
    std::string getXML();
};