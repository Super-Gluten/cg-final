# 重构说明

1. 重构几何体基类，使用 标准化坐标（NDC）绘制模型，确定模型具体位置，应该在局部 -> 世界的矩阵中实现。
矩阵实现流程：
局部矩阵(local) -- 坐标变换(transform) --> 世界矩阵(model) -- 观察(view) --> 观察者矩阵 -- 投影矩阵(projection) --> 屏幕矩阵

2. 重构模型绘制，将原坐标的坐标变换放入 transform 矩阵之中。



## VAO/VBO/EBO 的调用方式

Mesh.h 中的 `setupBuffers()` 方法创建并配置了 OpenGL 缓冲区：

数据流：

```
你的Vertex结构体 (位置+法线+纹理坐标)
    ↓
存储在 vertices 向量中
    ↓
VBO 上传这些顶点数据到GPU
    ↓
Triangle 结构体定义如何连接顶点形成三角形
    ↓
转换为索引数组 [v0, v1, v2, v0, v2, v3...]
    ↓
EBO 上传这些索引到GPU
```

### 为什么需要Triangle结构体：

1. **数据分离**：`vertices` 存储唯一顶点，`triangles` 存储连接关系
2. **顶点复用**：多个三角形可以共享同一个顶点，节省内存
   - 比如一个立方体有8个顶点，但需要12个三角形（36个索引）
   - 如果没有索引/EBO，需要存储36个顶点（大量重复）
3. **逻辑清晰**：Triangle结构体使代码更易理解和操作

OpenGL使用EBO中的索引来从VBO中查找对应的顶点数据。

## Vertex结构体在EBO中的作用


1. **VBO存储Vertex数据**：EBO只是告诉OpenGL按什么顺序连接顶点
2. **顶点属性配置**：`setupBuffers()`使用了你的`positionOffset()`, `normalOffset()`, `texCoordOffset()`来配置顶点属性
3. **内存布局**：你的Vertex结构体确保了正确内存对齐，这对OpenGL正确解析数据至关重要

## 总结

- `Vertex.h`：定义了单个顶点的数据结构和内存布局
- `Mesh.h`：利用 Vertex 结构体，组织顶点和三角形关系，管理OpenGL资源
- `Triangle`结构体：在EBO系统中依然有意义，它定义了网格的拓扑结构