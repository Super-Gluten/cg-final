#ifndef TETRAHEDRON_PRISM_H
#define TETRAHEDRON_PRISM_H

#include "Geometry.h"

class Tetrahedron : public Geometry {
public:
    Tetrahedron(
        glm::vec3 bottomLeft = glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3 bottomRight= glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3 topLeft    = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 topRight   = glm::vec3(0.0f, 0.0f, 0.0f),
        float depth = 1.0f
    ): Geometry(TETRAHEDRON) {
        setSize(bottomLeft, bottomRight, topLeft, topRight, depth);
    }
    
    // 获取底面四个点和深度的公共接口
    glm::vec3 getbottomLeft() const { return bottomLeft_; }
    glm::vec3 getbottomRight() const { return bottomRight_; }
    glm::vec3 gettopLeft() const { return topLeft_; }
    glm::vec3 gettopRight() const { return topRight_; }
    float getDepth() const { return depth_; }
    
    // 主要接口：设置梯形四边形棱柱的参数接口，并会调用相应接口进行绘制
    void setSize(glm::vec3 bottomLeft, glm::vec3 bottomRight, glm::vec3 topLeft, glm::vec3 topRight, float depth) {
        bottomLeft_ = bottomLeft;
        bottomRight_= bottomRight;
        topLeft_    = topLeft;
        topRight_   = topRight;
        depth_      = depth;
        
        // 自动调用绘制函数
        generateGeometry();
    }
    
private:
    glm::vec3 bottomLeft_;
    glm::vec3 bottomRight_;
    glm::vec3 topLeft_;
    glm::vec3 topRight_;
    float depth_;

    // 工具函数：计算三角形面法线
    glm::vec3 calculateFaceNormal(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) {
        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        return glm::normalize(glm::cross(edge1, edge2));
    }
    
    void generateGeometry() {
        clear();
        
        auto& vertices = getVertices();
        auto& triangles = getTriangles();
        
        // 计算深度方向向量
        glm::vec3 depth = glm::vec3(0.0f, 0.0f, depth_);
        
        // 8个顶点位置
        glm::vec3 positions[8] = {
            // 底面左下角 -> 右下角 -> 右上角 -> 左上角
            bottomLeft_,
            bottomRight_,
            topRight_,
            topLeft_,
            
            
            // 顶面左下角 -> 右下角 -> 右上角 -> 左上角
            bottomLeft_ + depth,
            bottomRight_+ depth,
            topRight_   + depth,
            topLeft_    + depth,
        };

        // 纹理坐标
        glm::vec2 texCoords[4] = {
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f)
        };
        
        // 每个面的顶点索引（按顺时针顺序）
        int faceIndices[6][4] = {
            {0, 1, 2, 3},  // 前
            {5, 4, 7, 6},  // 后
            {4, 5, 1, 0},  // 下
            {3, 2, 6, 7},  // 上
            {4, 0, 3, 7},  // 左
            {1, 5, 6, 2}   // 右
        };
        
        // 先计算每个面的面法向量
        glm::vec3 faceNormal[6];
        for(int face = 0; face < 6; ++face) {
            faceNormal[face] = 
                calculateFaceNormal(
                    positions[faceIndices[face][0]],
                    positions[faceIndices[face][1]],
                    positions[faceIndices[face][2]]
            );
        }

        // 通过手动指定，计算每个点的顶点法向量
        glm::vec3 smoothNormals[8] = {
            glm::normalize(faceNormal[0] + faceNormal[2] + faceNormal[4]),
            glm::normalize(faceNormal[0] + faceNormal[2] + faceNormal[5]),
            glm::normalize(faceNormal[0] + faceNormal[3] + faceNormal[5]),
            glm::normalize(faceNormal[0] + faceNormal[3] + faceNormal[4]),

            glm::normalize(faceNormal[1] + faceNormal[2] + faceNormal[4]),
            glm::normalize(faceNormal[1] + faceNormal[2] + faceNormal[5]),
            glm::normalize(faceNormal[1] + faceNormal[3] + faceNormal[5]),
            glm::normalize(faceNormal[1] + faceNormal[3] + faceNormal[4])
        };

        // 为每个面生成4个顶点和2个三角形
        for (int face = 0; face < 6; ++face) {
            int baseIndex = vertices.size();
            
            // 添加4个顶点
            for (int i = 0; i < 4; ++i) {
                int posIdx = faceIndices[face][i];
                vertices.emplace_back(positions[posIdx], smoothNormals[posIdx], texCoords[i]);
            }
            
            // 添加2个三角形（逆时针）
            triangles.emplace_back(baseIndex, baseIndex + 1, baseIndex + 2);
            triangles.emplace_back(baseIndex, baseIndex + 2, baseIndex + 3);
        }
        if (mesh_.VAO != 0) {
            if (initBuffers()) {
                render();
            } 
            else {
                std::cout << "Error: Failed to init Tetraedron's Buffers" << std::endl;
            }
        }
    }
};

#endif
