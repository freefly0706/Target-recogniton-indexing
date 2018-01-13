//
// Created by fly on 11/1/17.
//

#include "UCLSend.h"
#include "property/generate/GenCGPSProperty.h"
#include "UCL/digSignNo.h"
#include "property/generate/GenZCPSProperty.h"
#include "dbHelper.h"

UCLCode generateCode(uint64_t timeStamp) {
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
    code_test.setTimeStamp(timeStamp);
    /*
     * serinal number and multiplex bytes test cases
     * 0xCff1f3 - 0x8fffff31; 0x8f1f - 0x1f3f5f7f9f; 0x4f - 0x1f3f5f7f9f48; 0xf - 0x1f3f5f7f9f48
     */
    code_test.setSerialNumber(0x4f);
    code_test.setMultiplexBytes(0x1f3f5f7f9f48);

    code_test.setVersion(3);//对于已经设置过的域重复设置

    return code_test;
}

UCLPropertySet generateCGPS() {
    UCLPropertySet cgps;
    cgps.setHeadCategory(15);
    UCLPropertyBase sigCon = GenCGPSProperty::genContSig("CGPS", NO_DIG, NO_SIG);
    cgps.setProperty(sigCon);
    UCLPropertyBase sigUCL = GenCGPSProperty::genUCLSig(MD5, ECDSA);
    cgps.setProperty(sigUCL);
    return cgps;
}

UCLPropertySet generateZCPS(uint8_t headCategory, const string &boundingBox) {
    UCLPropertySet zcps;
    zcps.setHeadCategory(headCategory);

    UCLPropertyBase name = GenZCPSProperty::genName("战场");
    zcps.setProperty(name);
//    UCLPropertyBase spaceLoc = GenZCPSProperty::genSpaceLoc("北纬N39°40′20.09″ 东经E116°32′13.51");
//    zcps.setProperty(spaceLoc);
//
//    time_t timer = time(NULL);
//    struct tm *tblock;
//    tblock = localtime(&timer);
//    UCLPropertyBase time = GenZCPSProperty::genTime(asctime(tblock));
//    zcps.setProperty(time);
//
//    UCLPropertyBase shape = GenZCPSProperty::genShape("1;北纬N39°40′20.09″ 东经E116°32′13.51");
//    zcps.setProperty(shape);
//
//    UCLPropertyBase phy = GenZCPSProperty::genPhysical("0;;1;");
//    zcps.setProperty(phy);
//
//    UCLPropertyBase material = GenZCPSProperty::genMaterial("1");
//    zcps.setProperty(material);
//
//    UCLPropertyBase pass = GenZCPSProperty::genPassingAbility("1");
//    zcps.setProperty(pass);
//
//    UCLPropertyBase spaceEnemyS = GenZCPSProperty::genSpaceEnemyS("坦克;;潜艇");
//    zcps.setProperty(spaceEnemyS);
//
//    UCLPropertyBase amf = GenZCPSProperty::genAbsMotionFea("10;;北纬N39°40′20.09″ 东经E116°32′13.51");
//    zcps.setProperty(amf);
//
//    UCLPropertyBase rmf = GenZCPSProperty::genRelMotionFea("10;100;北纬N39°40′20.09″ 东经E116°32′13.51");
//    zcps.setProperty(rmf);
//
//    UCLPropertyBase tp = GenZCPSProperty::genTravellingPath("10;;北纬N39°40′20.09″ 东经E116°32′13.51");
//    zcps.setProperty(tp);

    UCLPropertyBase bb = GenZCPSProperty::genBoundingBox(boundingBox);
    zcps.setProperty(bb);

    return zcps;
}

void socketSend(string ucl, int len) {
    int sock_cli;
    //定义sockfd
    sock_cli = socket(AF_INET, SOCK_STREAM, 0);
    //定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr(IP);  ///服务器ip

    //连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("connect");
        exit(1);
    }
    char sendbuf[len];
    for (int i = 0; i < len; i++) {
        sendbuf[i] = ucl[i];
    }
    send(sock_cli, sendbuf, len, 0); //发送
    memset(sendbuf, 0, sizeof(len));
    close(sock_cli);
}

string int2Hex(uint64_t num) {
    string res = "";
    char _16[] = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };
    // 16进制,除以16
    const int radix = 16;
    while (num) {
        uint i = num % radix;          // 余数
        res = _16[i] + res;   // 将余数对应的十六进制数字加入结果
        num /= radix;                 // 除以16获得商，最为下一轮的被除数
    }
    return res;
}

string BinToHex(const string &strBin, bool IsUpper = false) {
    string strHex;
    strHex.resize(strBin.size() * 2);
    for (size_t i = 0; i < strBin.size(); i++) {
        uint8_t cTemp = strBin[i];
        for (size_t j = 0; j < 2; j++) {
            uint8_t cCur = (cTemp & 0x0f);
            if (cCur < 10) {
                cCur += '0';
            } else {
                cCur += ((IsUpper ? 'A' : 'a') - 10);
            }
            strHex[2 * i + 1 - j] = cCur;
            cTemp >>= 4;
        }
    }
    return strHex;
}

void genSendUCL(const vector<string> &imageList) {
    cout << "数据发送开始…………" << endl;

    DBHelper dbHelper = DBHelper();
    dbHelper.getConn(); //获取数据库连接
    dbHelper.createdbTable(); // 创建ucl_bt数据表
    vector<vector<string>> item;  //存储一张图片所有的目标数据
    int count = 1;
    for (int i = 0; i < imageList.size(); i++) {
        bool imageExist = false;
        int waitTime = 0;
        while (!imageExist) {  //数据库中没有输入图片的数据则循环等待
            if (waitTime > 1000) {  //等待时间超过10s则终止程序的运行
                cout << "程序运行结束！" << endl;
                dbHelper.closeConn();  //关闭数据库连接
                exit(0);
            }
            try {
                item = dbHelper.getData(imageList[i]);
                imageExist = true;
            } catch (const char *s) {  //捕获到异常表明数据库中没有输入图片的相应数据
                usleep(10000);
                waitTime++;
            }
        }  //至此,读取数据完成

        UCL ucl;

        struct timeb t1;  //获取系统时间（毫秒数）
        ftime(&t1);
        uint64_t timeStamp = (uint64_t) t1.time * 1000 + t1.millitm;

        UCLCode code_test = generateCode(timeStamp);
        ucl.setUclCode(code_test);

        UCLPropertySet cgps = generateCGPS();
        ucl.setPropertySet(cgps);

        if (item[0][0] == "1") {
            string temp = imageList[i];
            for (int j = 0; j < item.size(); j++) {
                temp.append(";").append(item[j][1]).append(";");
                for (int k = 2; k < item[j].size() - 1; k++) {
                    temp.append(item[j][k]).append(" ");
                }
                temp.append(";").append(item[j][item[j].size() - 1]);
                UCLPropertySet zcps = generateZCPS(j + 2, temp);
                ucl.setPropertySet(zcps);
                temp = imageList[i];
            }
        }

        string str_ucl = ucl.pack();

        string uclSign = ucl.getValue(15, 15);
        uint32_t uclByte = ucl.getUclPropertyHead().getTotalLength() + 32;
        string uclTimeStamp = int2Hex(timeStamp);
        string ucl_bt = BinToHex(str_ucl);

        if(dbHelper.search(imageList[i])){
            dbHelper.update(imageList[i], ucl_bt, uclSign,uclByte, uclTimeStamp);
        }else{
            dbHelper.insert(imageList[i], ucl_bt, uclSign,uclByte, uclTimeStamp);
        }

        printf("正在发送第%d条UCL：", count++);
        printPackString(str_ucl);
//        socketSend(str_ucl, str_ucl.length());
//        usleep(1000000);

    }
    dbHelper.closeConn();  //关闭数据库连接
}