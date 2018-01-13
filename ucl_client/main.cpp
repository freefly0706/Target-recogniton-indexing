#include "tools/UCLSend.h"

int main() {
    vector<string> imageList;
    for (int i = 0; i < 1000; i ++) {
        char imageName[6];
        sprintf(imageName, "%06d", i);
        imageList.emplace_back(imageName);
    }
    genSendUCL(imageList);
    return 0;
}
