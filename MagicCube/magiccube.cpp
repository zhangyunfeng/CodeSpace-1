/**
 * @file   magiccube.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Sun Jan 10 14:39:56 2016
 * 
 * @brief  implement of magiccube.hpp
 * 
 * 
 */

#include "magiccube.hpp"

CUBE::CUBE() {
    //TODO: init m_cubeMatrix[3][3][3];
    initCubeMatrix();
}

CUBE::~CUBE() {
    
}

/** 
 * init cube matrix
 * 
 */
void CUBE::initCubeMatrix() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                m_cubeMatrix[i][j][k] = 0;
            }
        }
    }
}


void CUBE::PrintCube() {
    
}

bool CUBE::CheckCubeFinished() {
    return false;
}

void CUBE::ShuffleCube() {
    
}


