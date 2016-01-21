/**
 * @file   magiccube.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Sat Jan  9 11:09:26 2016
 * 
 * @brief  Magic Cube header file
 * 
 * 
 */

#ifndef MAGICCUBE_H
#define MAGICCUBE_H

#include <string>
#include <iostream>

enum CUBE_XYZ {
    CUBE_X,
    CUBE_Y,
    CUBE_Z,
};

class CUBE {
  public:
    CUBE();
    ~CUBE();

    /** 
     * print cube
     * 
     */
    void PrintCube();

    /** 
     * 
     * 
     * check cube finished or not
     * @return if finished , return true, otherwise return false
     */
    bool CheckCubeFinished();

    /** 
     * 打乱魔方
     * 
     */
    void ShuffleCube();

  private:
    void initCubeMatrix();
  private:
    CUBE_XYZ m_cubeMatrix[3][3][3];
};

/** 
 * 
 * 顺时针旋转魔方cube
 * @param xyz 旋转哪个轴, x, y, z
 * @param rows 旋转哪一行
 * @param rotates 旋转多少个面
 */
extern void rotate_cube(CUBE cube, CUBE_XYZ xyz, int rows, int rotates);

#endif /* MAGICCUBE_H */
