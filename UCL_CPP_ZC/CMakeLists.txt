cmake_minimum_required(VERSION 3.5.1)
project(UCL_CPP_ZC)

set(CMAKE_INSTALL_PREFIX /usr/share/ucl)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES test/main.cpp
        code/header_file/UCLCode.h
        code/header_file/UCLFormatV2.h
        code/UCLCode.cpp code/UCLCodeExtension.cpp
        code/header_file/UCLCodeExtension.h
        code/header_file/XMLTools.h
        code/header_file/UCLFormatMap.h
        code/UCLCode.cpp
        code/UCLCodeExtension.cpp
        code/XMLTools.cpp
        code/tinyxml/tinystr.cpp
        code/tinyxml/tinystr.h
        code/tinyxml/tinyxml.cpp
        code/tinyxml/tinyxml.h
        code/tinyxml/tinyxmlerror.cpp
        code/tinyxml/tinyxmlparser.cpp
        code/header_file/UCLXMLConf.h

        property/base/UCLPropertyBase.h
        property/base/UCLPropertyBase.cpp
        property/base/UCLPropertyHead.cpp
        property/base/UCLPropertyHead.h property/base/UCLPropertySet.h
        property/base/UCLPropertySet.cpp
        UCL/UCL.h
        UCL/UCL.cpp
        test/test.h
        tools/header/UCLMD5.h
        tools/digest/UCLMD5.cpp
        tools/header/UCLCRC32.h
        tools/digest/UCLCRC32.cpp
        tools/header/UCLSHA_256.h
        tools/digest/UCLSHA_256.cpp
        tools/header/UCLSHA_512.h
        tools/digest/UCLSHA_512.cpp
        property/info/UCLPropertiesInfo.h
        property/info/UCLPropertiesInfo.cpp
        test/test.cpp
        property/generate/GenCDPSProperty.h
        property/generate/GenCDPSProperty.cpp property/generate/GenCGPSProperty.cpp
        tools/signature/Base64Code.cpp
        tools/header/Base64Code.h
        tools/header/UCLRSA.h
        tools/signature/UCLRSA.cpp
        tools/header/UCLDSA.h
        tools/signature/UCLDSA.cpp
        UCL/digSignNo.h tools/header/UCLECDSA.h
        tools/signature/UCLECDSA.cpp property/generate/GenZCPSProperty.cpp
        property/generate/GenZCPSProperty.h
        property/info/ZCPSInfo.cpp
        property/info/ZCPSInfo.h
        )

INSTALL(
        DIRECTORY code/header_file DESTINATION ${CMAKE_INSTALL_PREFIX}/include/code/
)
INSTALL(
        FILES code/tinyxml/tinystr.h code/tinyxml/tinyxml.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/code/tinyxml
)


INSTALL(
        FILES property/base/UCLPropertyBase.h property/base/UCLPropertyHead.h property/base/UCLPropertySet.h DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/property/base
)
INSTALL(
        FILES property/generate/GenCDPSProperty.h property/generate/GenCGPSProperty.h property/generate/GenZCPSProperty.h DESTINATION
        ${CMAKE_INSTALL_PREFIX}/include/property/generate
)
INSTALL(
        FILES property/info/UCLPropertiesInfo.h property/info/ZCPSInfo.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/property/info
)

INSTALL(DIRECTORY tools/header DESTINATION ${CMAKE_INSTALL_PREFIX}/include/tools/)

INSTALL(
        FILES UCL/digSignNo.h UCL/UCL.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/UCL
)

INSTALL(
        FILES test/test.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/test
)

#注意:动态链接库生成和执行工程不能同时进行，需注释其中一个
#生成动态链接库
#add_library(UCL_CPP_ZC SHARED ${SOURCE_FILES})
#INSTALL(TARGETS UCL_CPP_ZC LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

#执行工程
add_executable(UCL_CPP_ZC ${SOURCE_FILES})

target_link_libraries(UCL_CPP_ZC ssl crypto)