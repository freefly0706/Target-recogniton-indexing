//
// Created by zp on 17-7-27.
//

#include "ZCPSInfo.h"
#include "UCLPropertiesInfo.h"

ZCPSInfo::ZCPSInfo() {
    init();
}

void ZCPSInfo::init() {
    spaceLocMap[1] = "BDS";
    spaceLocMap[2] = "GPS";

    timeMap[1] = "BDS";
    timeMap[2] = "GPS";

    //几何轮廓受控映射表
    shapeMap[0] = "圆形";
    shapeMap[1] = "长方形";
    shapeMap[2] = "正方形";
    shapeMap[3] = "菱形";
    shapeMap[4] = "不规则图形";
    shapeMap[5] = "球";
    shapeMap[6] = "长方体";
    shapeMap[7] = "正方体";
    shapeMap[8] = "圆柱体";

    //电磁特性受控映射表
    phyElectricMap[0] = "反射电磁波";
    phyElectricMap[1] = "不反射电磁波";

    //声波特性受控映射表
    phySoundMap[0] = "反射声波";
    phySoundMap[1] = "不反射声波";

    //核生化特性受控映射表
    phyNuclearMap[0] = "产生核辐射";
    phyNuclearMap[1] = "不产生核辐射";

    //雷达特性受控映射表
    phyRadarMap[0] = "可被雷达检测";
    phyRadarMap[1] = "不可被雷达检测";

    //材质受控映射表
    materialMap[0] = "金属材质";
    materialMap[1] = "塑料材质";
    materialMap[2] = "木材质";
    materialMap[3] = "水泥材质";
    materialMap[4] = "石材质";
    materialMap[5] = "无机非金属材质";
    materialMap[6] = "有机高分子材质";
    materialMap[7] = "合成橡胶材质";
    materialMap[8] = "合成纤维";

    //通过程度受控映射表
    passAbiMap[0] = "不可通过";
    passAbiMap[1] = "可通过";

    motionFeaMap[1] = "速度单位为厘米每秒（cm/s），加速度单位为厘米每秒平方（cm/s2）";
    motionFeaMap[2] = "速度单位为米每秒（m/s），加速度单位为米每秒平方（m/s2）";
    motionFeaMap[3] = "速度单位为千米每小时（km/h），加速度单位为厘米每秒平方（km/h2）";
    motionFeaMap[4] = "速度单位为英里每小时（mile/h），加速度单位为英里每小时平方（mile/h2）";
}

void ZCPSInfo::setPropertyMap(map<int, string> &propertySetCategoryMap,
                              map<int, map<int, string>> &propertyCategoryMap) {
    propertySetCategoryMap[2] = "ZC目标对象描述属性集合";

    map<int, string> zcps;
    zcps[1] = "目标对象名称";
    zcps[2] = "空间位置信息";
    zcps[3] = "时间信息";
    zcps[4] = "目标外形";
    zcps[5] = "物理特性";
    zcps[6] = "目标材质";
    zcps[7] = "通过程度";
    zcps[8] = "空间敌我态势";
    zcps[11] = "绝对运动特性";
    zcps[12] = "相对运动特性";
    zcps[13] = "运行轨迹";
    propertyCategoryMap[2] = zcps;
}

string ZCPSInfo::getMapValue(map<int, string> m, int key) {
    if (m.find(key) == m.end()) {
        return "无该映射！！！";
    }
    return m[key];
}

void ZCPSInfo::showProperty(UCLPropertyBase property) {
    switch (property.getCategory()) {
        case 1:
            showName(property);
            break;
        case 2:
            showSpaceLoc(property);
            break;
        case 3:
            showTime(property);
            break;
        case 4:
            showShape(property);
            break;
        case 5:
            showPhysical(property);
            break;
        case 6:
            showMaterial(property);
            break;
        case 7:
            showPassingAbility(property);
            break;
        case 8:
            showSpaceEnemyS(property);
            break;
        case 11:
        case 12:
            showMotionFea(property);
            break;
        case 13:
            showTravellingPath(property);
            break;
        case 14:
            showBoundingBox(property);
    }
}

void ZCPSInfo::showName(UCLPropertyBase propertyBase) {
    cout << "名称: " << propertyBase.getVPart() << endl;
}

void ZCPSInfo::showSpaceLoc(UCLPropertyBase propertyBase) {
    int parse = propertyBase.getLPartHead(2, 5);
    cout << "坐标体系描述位置标准：" << getMapValue(spaceLocMap, parse) << endl;
    cout << "位置坐标：" << propertyBase.getVPart() << endl;
}

void ZCPSInfo::showTime(UCLPropertyBase propertyBase) {
    int parse = propertyBase.getLPartHead(2, 5);
    cout << "授时信息规则：" << getMapValue(timeMap, parse) << endl;
    cout << "时间：" << propertyBase.getVPart();
}

vector<string> ZCPSInfo::getShape(string vPart) {
    return UCLPropertiesInfo::split(vPart, DEFAULT_PATTERN);
}

void ZCPSInfo::showShape(UCLPropertyBase propertyBase) {
    vector<string> shapes = getShape(propertyBase.getVPart());
    string shape = shapes[0];
    string loc = shapes[1];

    cout << "几何轮廓: " << shape << ", " << getMapValue(shapeMap, atoi(shape.c_str())) << endl;
    cout << "投影边界: " << loc << endl;
}

vector<string> ZCPSInfo::getPhysical(string vPart) {
    return UCLPropertiesInfo::split(vPart, DEFAULT_PATTERN);
}

void ZCPSInfo::showPhysical(UCLPropertyBase propertyBase) {
    vector<string> physicals = getPhysical(propertyBase.getVPart());
    string electric = physicals[0];
    string sound = physicals[1];
    string nuclear = physicals[2];
    string radar = physicals[3];

    cout << "电磁特性: " << electric << ", " << getMapValue(phyElectricMap, atoi(electric.c_str())) << endl;
    cout << "声波特性: " << sound << ", " << getMapValue(phySoundMap, atoi(sound.c_str())) << endl;
    cout << "核生化特性: " << nuclear << ", " << getMapValue(phyNuclearMap, atoi(nuclear.c_str())) << endl;
    cout << "雷达特性: " << radar << ", " << getMapValue(phyRadarMap, atoi(radar.c_str())) << endl;
}

void ZCPSInfo::showMaterial(UCLPropertyBase propertyBase) {
    string value = propertyBase.getVPart();
    cout << "材质: " << value << ", " << getMapValue(materialMap, atoi(value.c_str())) << endl;
}

void ZCPSInfo::showPassingAbility(UCLPropertyBase propertyBase) {
    string value = propertyBase.getVPart();
    cout << "通过程度: " << value << ", " << getMapValue(passAbiMap, atoi(value.c_str())) << endl;
}

void ZCPSInfo::showSpaceEnemyS(UCLPropertyBase propertyBase) {
    vector<string> spaceStatus = getPhysical(propertyBase.getVPart());
    string group = spaceStatus[0];
    string sky = spaceStatus[1];
    string water = spaceStatus[2];

    cout << "地面敌我状态信息: " << group << endl;
    cout << "空中敌我环境信息: " << sky << endl;
    cout << "水下敌我状况信息: " << water << endl;
}

void ZCPSInfo::showMotionFea(UCLPropertyBase propertyBase) {
    int parse = propertyBase.getLPartHead(2, 5);
    vector<string> motions = getPhysical(propertyBase.getVPart());

    cout << "运动特性解析信息: " << getMapValue(motionFeaMap, parse) << endl;
    cout << "速度: " << motions[0] << endl;
    cout << "加速度: " << motions[1] << endl;
    cout << "运动轨迹: " << motions[2] << endl;
}

void ZCPSInfo::showTravellingPath(UCLPropertyBase propertyBase) {
    int parse = propertyBase.getLPartHead(2, 5);
    cout << "运动轨迹解析信息: " << getMapValue(spaceLocMap, parse) << endl;
    cout << "运动轨迹: " << propertyBase.getVPart() << endl;
}

vector<string> ZCPSInfo::getBoundingBox(string vPart) {
    return UCLPropertiesInfo::split(vPart, DEFAULT_PATTERN);
}

void ZCPSInfo::showBoundingBox(UCLPropertyBase propertyBase) {
    vector<string> info = getBoundingBox(propertyBase.getVPart());
    cout << "所属图片: " << info[0] << "    目标类别: " << info[1] << endl;
    cout << "相对位置: " << info[2] << endl;
    cout << "置信度: " << info[3] << endl;
}

