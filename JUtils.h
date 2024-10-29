//
// Created by yudek on 10/23/24.
//

#ifndef JUTILS_H
#define JUTILS_H
#pragma once
#include <jni.h>
#include <vector>


struct JUtils {
private:
    static jclass getIntArrClass(JNIEnv *env) {
        return env->FindClass("[I");
    }

public:
    static jobjectArray to_int2d_jobject_array(std::vector<std::vector<int>> const& vec, JNIEnv *env) {
        auto jarr = env->NewObjectArray(static_cast<jsize>(vec.size()),JUtils::getIntArrClass(env),nullptr);

        int rowNumber = 0;

        for (auto & row : vec) {
            auto rowJ = env->NewIntArray(static_cast<jsize>(row.size()));

            int rowArr[row.size()];
            int i = 0;
            while (i<row.size()) {
                rowArr[i] = row[i];
                i++;
            }

            env->SetIntArrayRegion(rowJ,0,static_cast<jsize>(row.size()),rowArr);

            env->SetObjectArrayElement(jarr,rowNumber,rowJ);

            rowNumber++;
        }

        return jarr;
    }
};



#endif //JUTILS_H
