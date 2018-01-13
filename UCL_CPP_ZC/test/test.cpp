//
// Created by zp on 17-6-10.
//
#include "test.h"
#include "../property/generate/GenCDPSProperty.h"
#include "../property/generate/GenCGPSProperty.h"
#include "../UCL/digSignNo.h"
#include "../property/generate/GenZCPSProperty.h"
#include "../code/header_file/XMLTools.h"

void testCommand()
{
    cout << "\n========== UCL test begin==========\n";
    UCL ucl;

    UCLCode code_test = generateCode();
    ucl.setUclCode(code_test);

    cout << "\n##############测试属性##############\n\n";
//    UCLPropertySet cdps = generateCDPS();
//    ucl.setPropertySet(cdps);

    UCLPropertySet cgps = generateCGPS();
    ucl.setPropertySet(cgps);

    UCLPropertySet zcps = generateZCPS();
    ucl.setPropertySet(zcps);

//    cout << "\n##############测试打包##############\n\n";
    cout << "--------------UCLPackage-------------- \n";
//    assert(ucl.pack() == ucl.pack());
    printPackString(ucl.pack());
    cout << "--------------显示UCL各部分关键信息--------------\n";
    ucl.showUCL();

    cout << "\n##############测试解包##############\n\n";
    UCL ucl2;
    ucl2.unpack(ucl.pack());
    cout << "--------------UCLPackage--------------\n";
    printPackString(ucl2.pack());
    cout << "--------------解包后UCL各部分关键信息--------------\n";
    ucl2.showUCL();

    cout << "========== UCL test end==========\n";
    cout << ucl.getUclPropertyHead().getTotalLength()+32 << endl;
    cout << ucl.getUclCode().getSizeOfContent();
}

void printPackString(string pack)
{
    for(int i=0; i < pack.size(); i++) {
        cout << setw(2) << setfill('0') << hex << ((uint16_t)pack[i] & 0xff) << "-";
    }
    cout << "\n\n";
}

UCLPropertySet generateCDPS()
{
    UCLPropertySet cdps;
    cdps.setHeadCategory(1);
    UCLPropertyBase title = GenCDPSProperty::genTitle("CDPS");
    UCLPropertyBase file = GenCDPSProperty::genFileDescription("文本;10M");
    UCLPropertyBase content = GenCDPSProperty::genContObject("农业工作推进会");
    cdps.setProperty(title);
    cdps.setProperty(file);
    cdps.setProperty(content);

    return cdps;
}

UCLPropertySet generateCGPS()
{
    UCLPropertySet cgps;
    cgps.setHeadCategory(15);
    UCLPropertyBase sigCon = GenCGPSProperty::genContSig("CGPS", NO_DIG, NO_SIG);
    cgps.setProperty(sigCon);
    UCLPropertyBase sigUCL = GenCGPSProperty::genUCLSig(NO_DIG, NO_SIG);
    cgps.setProperty(sigUCL);

    return cgps;
}

UCLPropertySet generateZCPS()
{
    UCLPropertySet zcps;
    zcps.setHeadCategory(2);

    UCLPropertyBase name = GenZCPSProperty::genName("战场");
    zcps.setProperty(name);

    UCLPropertyBase spaceLoc = GenZCPSProperty::genSpaceLoc("北纬N39°40′20.09″ 东经E116°32′13.51");
    zcps.setProperty(spaceLoc);

    time_t timer = time(NULL);
    struct tm * tblock;
    tblock = localtime(&timer);
    UCLPropertyBase time = GenZCPSProperty::genTime(asctime(tblock));
    zcps.setProperty(time);

    UCLPropertyBase shape = GenZCPSProperty::genShape("1;北纬N39°40′20.09″ 东经E116°32′13.51");
    zcps.setProperty(shape);

    UCLPropertyBase phy = GenZCPSProperty::genPhysical("0;;1;");
    zcps.setProperty(phy);

    UCLPropertyBase material = GenZCPSProperty::genMaterial("1");
    zcps.setProperty(material);

    UCLPropertyBase pass = GenZCPSProperty::genPassingAbility("1");
    zcps.setProperty(pass);

    UCLPropertyBase spaceEnemyS = GenZCPSProperty::genSpaceEnemyS("坦克;;潜艇");
    zcps.setProperty(spaceEnemyS);

    UCLPropertyBase amf = GenZCPSProperty::genAbsMotionFea("10;;北纬N39°40′20.09″ 东经E116°32′13.51");
    zcps.setProperty(amf);

    UCLPropertyBase rmf = GenZCPSProperty::genRelMotionFea("10;100;北纬N39°40′20.09″ 东经E116°32′13.51");
    zcps.setProperty(rmf);

    UCLPropertyBase tp = GenZCPSProperty::genTravellingPath("10;;北纬N39°40′20.09″ 东经E116°32′13.51");
    zcps.setProperty(tp);

    UCLPropertyBase bb = GenZCPSProperty::genBoundingBox("image09985;car;247 632 310 739 ;0.769765");
    zcps.setProperty(bb);

    return zcps;
}

UCLCode generateCode() {
    UCLCode code_test;

    code_test.setVersion(1);
    code_test.setTypeOfMedia(9);
    code_test.setPrioAndPoli(15);
    code_test.setFlag(0x4E); //01001110
    code_test.setParseRule(0xfff1);//ff1有效
    code_test.setSourOfCont(0xfffffff1);//ffffff1有效
    code_test.setCategory(255);
    code_test.setSubCategory(257);//0x01有效
    code_test.setTopic(0xffffff1);
    code_test.setCopyAndTypeOfCont(254);
    code_test.setSecuEnerLeveCode(251);
    code_test.setLanguage(253);
    code_test.setSizeOfContent(31);
    code_test.setTimeStamp(0x3fffffffff9f9);
    /*
     * serinal number and multiplex bytes test cases
     * 0xCff1f3 - 0x8fffff31; 0x8f1f - 0x1f3f5f7f9f; 0x4f - 0x1f3f5f7f9f48; 0xf - 0x1f3f5f7f9f48
     */
    code_test.setSerialNumber(0x4f);
    code_test.setMultiplexBytes(0x1f3f5f7f9f48);

    code_test.setVersion(3);//对于已经设置过的域重复设置

    return code_test;
}
