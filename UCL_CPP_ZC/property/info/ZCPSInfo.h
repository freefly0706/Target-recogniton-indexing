//
// Created by zp on 17-7-27.
//

#ifndef UCL_CPP_ZCPSINFO_H
#define UCL_CPP_ZCPSINFO_H
#include <iostream>
#include <map>
#include <vector>
#include "../base/UCLPropertyBase.h"

using namespace std;

static string DEFAULT_PATTERN = ";";
/**
 * ZCPS相关映射及显示
 */
class ZCPSInfo {
private:
    //ZCPS受控映射表
    map<int, string> spaceLocMap;
    map<int, string> timeMap;
    map<int, string> shapeMap;
    map<int, string> phyElectricMap;
    map<int, string> phySoundMap;
    map<int, string> phyNuclearMap;
    map<int, string> phyRadarMap;
    map<int, string> materialMap;
    map<int, string> passAbiMap;
    map<int, string> motionFeaMap;
public:
    ZCPSInfo();

    //初始化受控映射表
    void init();

    void setPropertyMap(map<int, string> &propertySetCategoryMap,
                        map<int, map<int, string>> &propertyCategoryMap);
    string getMapValue(map<int, string> m, int key);

    void showProperty(UCLPropertyBase propertyBase);

    void showName(UCLPropertyBase propertyBase);
    void showSpaceLoc(UCLPropertyBase propertyBase);
    void showTime(UCLPropertyBase propertyBase);

    vector<string> getShape(string vPart);
    void showShape(UCLPropertyBase propertyBase);

    vector<string> getPhysical(string vPart);
    void showPhysical(UCLPropertyBase propertyBase);

    void showMaterial(UCLPropertyBase propertyBase);
    void showPassingAbility(UCLPropertyBase propertyBase);
    void showSpaceEnemyS(UCLPropertyBase propertyBase);
    void showMotionFea(UCLPropertyBase propertyBase);
    void showTravellingPath(UCLPropertyBase propertyBase);
    vector<string> getBoundingBox(string vPart);
    void showBoundingBox(UCLPropertyBase propertyBase);
};

#endif //UCL_CPP_ZCPSINFO_H
