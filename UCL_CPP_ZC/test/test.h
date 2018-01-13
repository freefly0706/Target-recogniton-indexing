//
// Created by zp on 12/20/16.
//

#ifndef UCL_CPP_TEST_H
#define UCL_CPP_TEST_H

#include <iomanip>
#include <fstream>
#include <iostream>
#include "../property/base/UCLPropertyHead.h"
#include "../property/base/UCLPropertySet.h"
#include "../UCL/UCL.h"
#include <sstream>

void testCommand();
void printPackString(string pack);

// 生成code部分
UCLCode generateCode();
// 生成CDPS部分
UCLPropertySet generateCDPS();
// 生成CGPS部分
UCLPropertySet generateCGPS();
// 生成ZCPS部分
UCLPropertySet generateZCPS();

#endif //UCL_CPP_TEST_H
