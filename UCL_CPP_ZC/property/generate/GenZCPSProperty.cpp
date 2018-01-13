//
// Created by zp on 17-7-21.
//

#include <assert.h>
#include "GenZCPSProperty.h"

//name
UCLPropertyBase GenZCPSProperty::genName(string vPart, uint8_t helper) {
    UCLPropertyBase name;
    name.setProperty(0x1, helper, vPart);

    return name;
}

//space location
UCLPropertyBase GenZCPSProperty::genSpaceLoc(string vPart, uint8_t parse, uint8_t helper) {
    UCLPropertyBase spaceLoc;
    spaceLoc.setLPartHead(2, 5, parse);
    spaceLoc.setProperty(0x2, helper, vPart);

    return spaceLoc;
}

//Time
UCLPropertyBase GenZCPSProperty::genTime(string vPart, uint8_t parse, uint8_t helper) {
    UCLPropertyBase time;
    time.setLPartHead(2, 5, parse);
    time.setProperty(0x3, helper, vPart);

    return time;
}

//Author
UCLPropertyBase GenZCPSProperty::genShape(string vPart, uint8_t helper) {
    UCLPropertyBase shape;
    shape.setProperty(0x4, helper, vPart);

    return shape;
}

//Physical
UCLPropertyBase GenZCPSProperty::genPhysical(string vPart, uint8_t helper) {
    UCLPropertyBase physical;
    physical.setProperty(0x5, helper, vPart);

    return physical;
}

//Material
UCLPropertyBase GenZCPSProperty::genMaterial(string vPart, uint8_t helper) {
    UCLPropertyBase material;
    material.setProperty(0x6, helper, vPart);

    return material;
}

//Passing ability
UCLPropertyBase GenZCPSProperty::genPassingAbility(string vPart, uint8_t helper) {
    UCLPropertyBase pass;
    pass.setProperty(0x7, helper, vPart);

    return pass;
}

//Space status
UCLPropertyBase GenZCPSProperty::genSpaceEnemyS(string vPart, uint8_t helper) {
    UCLPropertyBase spaceStatus;
    spaceStatus.setProperty(0x8, helper, vPart);

    return spaceStatus;
}

//Absolute motion features
UCLPropertyBase GenZCPSProperty::genAbsMotionFea(string vPart, uint8_t parse, uint8_t helper) {
    UCLPropertyBase absMontionFea;
    absMontionFea.setLPartHead(2, 5, parse);
    absMontionFea.setProperty(11, helper, vPart);

    return absMontionFea;
}

//Relative motion features
UCLPropertyBase GenZCPSProperty::genRelMotionFea(string vPart, uint8_t parse, uint8_t helper) {
    UCLPropertyBase relMontionFea;
    relMontionFea.setLPartHead(2, 5, parse);
    relMontionFea.setProperty(12, helper, vPart);

    return relMontionFea;
}

//Travelling Path
UCLPropertyBase GenZCPSProperty::genTravellingPath(string vPart, uint8_t parse, uint8_t helper) {
    UCLPropertyBase travellingPath;
    travellingPath.setLPartHead(2, 5, parse);
    travellingPath.setProperty(13, helper, vPart);

    return travellingPath;
}

UCLPropertyBase GenZCPSProperty::genBoundingBox(string vPart, uint8_t helper) {
    UCLPropertyBase BoundingBox;
    BoundingBox.setProperty(14, helper, vPart);

    return BoundingBox;
}