/*
 *  Created on: 2017-7-22
 *      Author: Oneway
 */



#ifndef XMLTOOLS_H
#define XMLTOOLS_H
#include <iostream>
#include <stdio.h>
#include "../tinyxml/tinyxml.h"
#include "./UCLXMLConf.h"
#include "./UCLCode.h"
#include <ctime>
#include <iomanip>

using namespace std;



/**
 * filePath: xml file path
 * write element to xml file and save it
 */
void writeXml(const char* filePath);



/**
 * fieldName: the name of the field:
 * mbuOrder: the order of the mbu in the field
 * mbuValue: the value of mbu
 * xmlFilePath: the path of xml file
 * show the value of the mbu from xml file
 * if read the correct value from xml return true, else return false
 */
bool showMBUFromXml(const char* fieldName, uint8_t mbuOrder, uint64_t mbuValue, const char* xmlFilePath);



/**
 * fieldName: the name of the field:
 * mbuOrder: the order of the mbu in the field
 * mbuValue: the value of mbu
 * show the value of the mbu from the default xml file(XML_PATH)
 * if read the correct value from xml return true, else return false
 */
bool showMBUFromXml(const char* fieldName, uint8_t mbuOrder, uint64_t mbuValue);



/**
 * fieldName: the name of the field
 * code: the reference of an UCLCode object
 * return the value from xml file of the given field
 */
void showFieldFromXML(const char* fieldName, const UCLCode &code);



/**
 * code: the reference of an UCLCode object
 * return the value from xml file of UCL code
 */
void showCodeFromXML(const UCLCode &code);//根据xml的配置解析并显示各个字段的含义



/**
 * unit testing
 */
void test_code_xml();



#endif //XMLTOOLS_H
