//
// Created by zp on 17-6-8.
//

#ifndef UCL_CPP_UCLPROPERTIESINFO_H
#define UCL_CPP_UCLPROPERTIESINFO_H

#include <string>
#include <map>
#include "../base/UCLPropertyBase.h"
#include "ZCPSInfo.h"

using namespace std;
/**
 * UCL属性部分受控映射表和控制台显示应用
 */
//ZCPS相关方法
static ZCPSInfo ZC = ZCPSInfo();

class UCLPropertiesInfo
{
private:
    //受控映射表
    map<int, string> propertyHeadMap;
    map<int, string> propertySetCategoryMap;
    map<int, map<int, string>> propertyCategoryMap;

    map<int, string> entity;
    map<int, string> promap; //provenance
    map<int, string> contentIdRulemap;
    map<int, string> seliMap;

    map<int, string> signatureMap;
    map<int, string> hash;
public:
    UCLPropertiesInfo();

    void initPropertyHeadMap();
    string getPropertyLangType(int type);

    //属性集合映射
    void initPropertySetCategoryMap();
    string getPropertySetCategory(int type);

    //属性映射
    void initPropertyCategroyMap();
    string getPropertyCategroy(int categroy, int proCategory);

    //初始化标准UCL属性部分受控映射表
    void initInfo();

    static vector<string> split(string str, string pattern);

    void showProperty(int category, UCLPropertyBase propertyBase);
    void showPropertyBase(UCLPropertyBase propertyBase);

    //CDPS
    void showCDPSKeywords(UCLPropertyBase keywords);
    void showCDPSAuthor(UCLPropertyBase author);
    void showCDPSEntity(UCLPropertyBase entity);
    void showCDPSTag(UCLPropertyBase tag);
    void showCDPSFileInfo(UCLPropertyBase fileInfo);
    void showCDPSRelatedUCL(UCLPropertyBase relatedUCL);

    //CGPS
    void showCGPSProvenance(UCLPropertyBase provenance);
    void showCGPSContentId(UCLPropertyBase content);
    void showCGPSPropagationPath(UCLPropertyBase propagationPath);
    void showCGPSSignatureContent(UCLPropertyBase sigContent);
    void showCGPSSELI(UCLPropertyBase seli);
    void showCGPSChainRespons(UCLPropertyBase cr);
    void showCGPSSignatureUP(UCLPropertyBase sup);

    //ZCPS
    //初始化ZCPS属性集合和属性映射
    void initZCPS();
};



#endif //UCL_CPP_UCLPROPERTIESINFO_H
