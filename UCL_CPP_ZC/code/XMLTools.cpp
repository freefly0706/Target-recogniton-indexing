/*
 *  Created on: 2017-7-22
 *      Author: Oneway
 */


#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "header_file/XMLTools.h"
#include "header_file/UCLFormatMap.h"


const char* XML_PATH = "../code/zc_conf_xml/zcConf.xml";
const char* UNDF_INFO = "Undefined";



/**
 * filePath: xml file path
 * write element to xml file and save it
 */
void writeXml(const char* filePath) {
		TiXmlDocument doc(filePath);
		bool loadOkay = doc.LoadFile();
		// faile to load 'phonebookdata.xml'.
		if (!loadOkay) {
			printf( "Could not load test file %s. Error='%s'. Exiting.\n", filePath,doc.ErrorDesc() );
			exit( 1 );
		}

	// Add information to xml file and save it.
	TiXmlElement* writeRoot = doc.RootElement();
	TiXmlNode* newNode = new TiXmlElement("item");

	const TiXmlNode* name4NewNode = new TiXmlElement("name");
	newNode->InsertEndChild(*name4NewNode)->InsertEndChild(TiXmlText("pipi"));

	writeRoot->InsertEndChild(*newNode);
	doc.SaveFile();
}



/**
 * fieldName: the name of the field:
 * mbuOrder: the order of the mbu in the field
 * mbuValue: the value of mbu
 * xmlFilePath: the path of xml file
 * show the value of the mbu from xml file
 * if read the correct value from xml return true, else return false
 */
bool showMBUFromXml(const char* fieldName, uint8_t mbuOrder, uint64_t mbuValue, const char* xmlFilePath)
{
	bool result = false;
    const char* filePath = xmlFilePath;// define xml file path
    //const char* tiXmlNodeUndefined = UNDF_INFO;

    TiXmlDocument doc(filePath);
    bool loadOkay = doc.LoadFile();
    // failed to load the xml file.
    if (!loadOkay) {
        printf( "Could not load xml file %s. Error='%s'. Exiting.\n", filePath,doc.ErrorDesc() );
        return result;
    }

    TiXmlElement* root = doc.RootElement();

    const int buffSize = 64;
    int width = 32;
    char buff[buffSize];
    memset(buff, 0, sizeof(char)*buffSize);

    char buffFieldName[buffSize];
    memset(buffFieldName, 0, sizeof(char)*buffSize);

    //get the xml element's name of the filed from CODE_NAME
    sprintf(buff, "%s_NAME", fieldName);
	if(CODE_NAME.find(buff) == CODE_NAME.end()) {
		cout << buff << " is not in CODE_NAME!!!" << endl;
		return result;
	} else {
		strcpy(buffFieldName, CODE_NAME.find(buff)->second.c_str());
	}

	//get the xml element according to the name
    TiXmlNode*  item = root->FirstChild( buffFieldName );
    if(item == NULL)  {
    	cout << "Node is not in xml file" << endl;
    	return result;
    }

    //get the xml element's initial string
    memset(buffFieldName, 0, sizeof(char)*buffSize);
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s_INITIAL", fieldName);
	if(CODE_NAME.find(buff) == CODE_NAME.end()) {
		cout << buff << " is not in CODE_NAME!!!" << endl;
		return result;
	} else {
		strcpy(buffFieldName, CODE_NAME.find(buff)->second.c_str());
	}

	/**
	 * constitute the full name of xml element according to arguments
	 * if the element existed in xml file display the value from xml file according the full name
	 * else display the mbu value
	 */
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s_%u_%llu", buffFieldName, mbuOrder, mbuValue);
    TiXmlNode* pTXNode = item->FirstChild(buff);
    cout << setfill(' ') << setw(width) << fieldName << " : ";
    if(pTXNode != NULL) {
    	cout << pTXNode ->ToElement()->GetText() << "\n";
    } else {//if the mbu is not defined in xml, display it's binary value
    	//cout << tiXmlNodeUndefined << "\n";
    	char* binaryString = new char[65];

        //get the mbu length
        memset(buffFieldName, 0, sizeof(char)*buffSize);
        memset(buff, 0, sizeof(char)*buffSize);
        sprintf(buff, "%s_MBU_%u_BIT_LENGTH", fieldName, mbuOrder);
    	if(MBU.find(buff) == MBU.end()) {
    		cout << buff << " is not in MBU!!!" << endl;
    		return result;
    	} else {
    		width = MBU.find(buff)->second;
    	}

        cout << hex << mbuValue
    			<< "(B)\n" << setfill(' ');
    	delete[] binaryString;
    }

    result = true;
    return result;
}



/**
 * fieldName: the name of the field:
 * mbuOrder: the order of the mbu in the field
 * mbuValue: the value of mbu
 * show the value of the mbu from the default xml file(XML_PATH)
 * if read the correct value from xml return true, else return false
 */
bool showMBUFromXml(const char* fieldName, uint8_t mbuOrder, uint64_t mbuValue)
{
	const char* filePath = XML_PATH;
	return showMBUFromXml(fieldName, mbuOrder, mbuValue, filePath);
}



/**
 * fieldName: the name of the field
 * code: the reference of an UCLCode object
 * return the value from xml file of the given field
 */
void showFieldFromXML(const char* fieldName, const UCLCode &code)
{
	uint64_t* fieldArr = code.getField(fieldName);
	for(unsigned int i = 1; i < fieldArr[0]; ++i) {
		showMBUFromXml(fieldName, i, fieldArr[i]);
	}
	delete[] fieldArr;
}



/**
 * code: the reference of an UCLCode object
 * return the value from xml file of UCL code
 */
void showCodeFromXML(const UCLCode &code)
{
    int width = 32;
cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	showFieldFromXML("VERSION", code);
	showFieldFromXML("TYPEOFMEDIA", code);
	showFieldFromXML("PRIOANDPOLI", code);
	showFieldFromXML("FLAG", code);

	showFieldFromXML("PARSERULE", code);
	//cout << setfill(' ') << setw(width) << "PARSERULE" << " : " << code.getParseRule() << "\n";

	showFieldFromXML("SOUROFCONT", code);
	showFieldFromXML("CATEGORY", code);

	showFieldFromXML("SUBCATEGORY", code);
	//cout << setfill(' ') << setw(width) << "SUBCATEGORY" << " : " << code.getSubCategory() << "\n";

	showFieldFromXML("TOPIC", code);
	showFieldFromXML("COPYANDTYPEOFCONT", code);
	showFieldFromXML("SECUENERLEVECODE", code);
	showFieldFromXML("LANGUAGE", code);
	showFieldFromXML("SIZEOFCONTENT", code);

	const time_t t = code.getTimeStamp();
	cout << setfill(' ') << setw(width) << "TIMESTAMP" << " : " << t << "\t";
	struct tm* st = localtime(&t);
	cout << setfill(' ') << setw(width) << "TIME" << " : "
			<< st->tm_year + 1900 << "-"
			<< st->tm_mon + 1 << "-"
			<< st->tm_mday << " "
			<< st->tm_hour << ":"
			<< st->tm_min << ":"
			<< st->tm_sec
			<< "\n";

	cout << setfill(' ') << setw(width) << "SERIALNUMBER" << " : " << code.getSerialNumber() << "\n";
	cout << setfill(' ') << setw(width) << "MULTIPLEXBYTES" << " : " << code.getMultiplexBytes() << "\n";
	cout << setfill(' ') << setw(width) << "CODECHECK" << " : " << code.getCodeCheck() << "\n";
	//showFieldFromXML("CODECHECK", code);
cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}



/**
 * unit testing
 */
void test_code_xml()
{
    UCLCode code_test;

    cout << "new a UCLCode:\n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    //set the value into UCLCode object
    code_test.setVersion(1);
    code_test.setTypeOfMedia(0);
    code_test.setPrioAndPoli(1);
    code_test.setFlag(0x4A);
    code_test.setParseRule(0xfff1);//ff1
    code_test.setSourOfCont(0x6000000);//ffffff1
    code_test.setCategory(1);
    code_test.setSubCategory(0x01);//0x01
    code_test.setTopic(0x101);
    code_test.setCopyAndTypeOfCont(0x46);
    code_test.setSecuEnerLeveCode(0x1B);
    code_test.setLanguage(0x20);
    code_test.setSizeOfContent(31);
    code_test.setTimeStamp(time(NULL));
    /*
     * serinal number and multiplex bytes test cases
     * 0xCff1f3 - 0x8fffff31; 0x8f1f - 0x1f3f5f7f9f; 0x4f - 0x1f3f5f7f9f48; 0xf - 0x1f3f5f7f9f48
     */
    code_test.setSerialNumber(0x4f);
    code_test.setMultiplexBytes(0x1f3f5f7f9f48);

    string s = code_test.pack(); //pack

    code_test.showCodeHex(s);// show the UCLCode object in hexadecimal form
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    code_test.showCode();//// show the UCLCode object in decimal form
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    cout << "result from xml : " << endl;
    showCodeFromXML(code_test);//show the value of the UCLCode from default xml file(XML_PATH)
    cout << endl;

}



