# 3D几何体类库API文档
## 概述
该类库基于**OpenGL**和**glm数学库**实现，提供了3D几何体的抽象基类及具体实现（长方体、四棱柱、球体），封装了几何体的网格生成、空间变换、缓冲区管理和渲染功能，采用禁止拷贝、允许移动的资源管理策略，适用于3D图形渲染场景。

## 依赖说明
1.  第三方库：glm（需包含`<glm/glm.hpp>`和`<glm/gtc/matrix_transform.hpp>`）
2.  自定义类：`Mesh`（负责网格数据存储、VAO/VBO/EBO缓冲区管理和渲染）
3.  前置条件：所有涉及OpenGL缓冲区操作（`initBuffers()`、`render()`）的函数，必须在OpenGL上下文初始化完成后调用。

---

## 1. 抽象基类：`Geometry`
### 头文件
`Geometry.h`

### 类说明
`Geometry`是所有3D几何体的抽象基类，封装了几何体的公共属性（类型、网格、空间变换）和行为（缓冲区初始化、渲染、模型矩阵计算），定义了统一的接口规范，子类需实现具体几何体的网格生成逻辑。

### 枚举类型：`Geometry::Type`
| 枚举值 | 含义 | 对应子类 |
|--------|------|----------|
| `SPHERE` | 球体 | `Sphere` |
| `CUBOID` | 长方体（直棱柱） | `Cuboid` |
| `TETRAHEDRON` | 四棱柱（梯形四边形棱柱） | `Tetrahedron` |
| `UNKNOWN` | 未知几何体类型 | 无（默认值/移动后源对象） |

### 构造与析构函数
| 函数签名 | 功能说明 |
|----------|----------|
| `Geometry(Type type = UNKNOWN)` | 默认构造函数，初始化几何体类型，默认值为`UNKNOWN`；同时初始化空间变换参数（位置原点、缩放1.0f、旋转0.0f） |
| `virtual ~Geometry()` | 虚析构函数，自动清理`Mesh`对象中的OpenGL资源（VAO/VBO/EBO），保证子类析构时的多态正确性 |
| `Geometry(const Geometry&) = delete` | 禁用拷贝构造函数，原因：管理OpenGL独占资源，拷贝会导致资源重复释放或冲突 |
| `Geometry& operator=(const Geometry&) = delete` | 禁用拷贝赋值运算符，原因同拷贝构造函数 |
| `Geometry(Geometry&& other) noexcept` | 移动构造函数，实现资源所有权转移，转移后源对象类型被重置为`UNKNOWN` |
| `Geometry& operator=(Geometry&& other) noexcept` | 移动赋值运算符，实现资源所有权转移，转移前清理当前对象资源，转移后源对象类型被重置为`UNKNOWN` |

### 公共成员函数
#### （1）基础查询接口
| 函数签名 | 返回值 | 功能说明 |
|----------|--------|----------|
| `Type getType() const` | `Geometry::Type` | 获取几何体类型 |
| `const Mesh& getMesh() const` | 不可修改的`Mesh`引用 | 获取几何体的网格数据（顶点、三角形索引、缓冲区信息） |
| `glm::vec3 getPosition() const` | `glm::vec3` | 获取几何体当前世界空间位置 |
| `glm::vec3 getScale() const` | `glm::vec3` | 获取几何体当前缩放比例 |
| `glm::vec3 getRotation() const` | `glm::vec3` | 获取几何体当前欧拉角旋转值（X/Y/Z轴，单位：角度） |

#### （2）缓冲区与渲染接口
| 函数签名 | 返回值 | 功能说明 |
|----------|--------|----------|
| `bool initBuffers()` | `bool` | 初始化OpenGL缓冲区（VAO/VBO/EBO），将网格数据上传至GPU；成功返回`true`，失败返回`false` |
| `void render() const` | 无 | 渲染几何体，调用`Mesh`的渲染接口，绘制所有三角形网格 |
| `void clear()` | 无 | 清空几何体的网格数据（顶点、三角形索引），并清理`Mesh`中的OpenGL缓冲区资源 |

#### （3）空间变换接口
| 函数签名 | 功能说明 |
|----------|----------|
| `void setPosition(const glm::vec3& position)` | 设置几何体世界空间位置，设置后标记模型矩阵为"脏数据"，按需重新计算 |
| `void setScale(const glm::vec3& scale)` | 设置几何体缩放比例（X/Y/Z轴分别缩放），设置后标记模型矩阵为"脏数据"，按需重新计算 |
| `void setRotation(const glm::vec3& rotation)` | 设置几何体欧拉角旋转值（X/Y/Z轴，单位：角度），设置后标记模型矩阵为"脏数据"，按需重新计算 |
| `glm::mat4 getModelMatrix() const` | 计算并返回模型矩阵（平移→旋转→缩放的组合变换），采用"懒加载"策略：仅当模型矩阵为"脏数据"时重新计算，否则返回缓存值 |

### 保护成员
| 成员名称 | 类型 | 功能说明 |
|----------|------|----------|
| `type_` | `Geometry::Type` | 几何体类型，子类构造时初始化 |
| `mesh_` | `Mesh` | 网格数据容器，存储顶点、三角形索引及OpenGL缓冲区句柄 |
| `position_`/`scale_`/`rotation_` | `glm::vec3` | 空间变换参数（位置、缩放、旋转） |
| `modelMatrixDirty_` | `mutable bool` | 模型矩阵脏标记，`true`表示需重新计算模型矩阵 |
| `modelMatrix_` | `mutable glm::mat4` | 缓存的模型矩阵，避免重复计算 |
| `markModelMatrixDirty()` | 成员函数 | 标记模型矩阵为"脏数据"，触发后续`getModelMatrix()`的重新计算 |
| `virtual void calculateNormals()` | 虚函数 | 顶点法线计算接口，默认实现为计算平滑法线（子类可重写自定义逻辑） |

---

## 2. 长方体类：`Cuboid`
### 头文件
`Cuboid.h`

### 类说明
`Cuboid`继承自`Geometry`，实现了中心位于坐标原点、各面平行于坐标轴的长方体几何体，支持动态修改长宽高并重新生成网格。

### 构造函数
| 函数签名 | 功能说明 |
|----------|----------|
| `Cuboid(float width = 1.0f, float height = 1.0f, float depth = 1.0f)` | 构造函数，初始化长方体的宽度、高度、深度（默认值均为1.0f），自动调用`setSize()`生成网格数据，几何体类型标记为`CUBOID` |

### 公共查询接口
| 函数签名 | 返回值 | 功能说明 |
|----------|--------|----------|
| `float getWidth() const` | `float` | 获取长方体当前宽度（X轴方向尺寸） |
| `float getHeight() const` | `float` | 获取长方体当前高度（Y轴方向尺寸） |
| `float getDepth() const` | `float` | 获取长方体当前深度（Z轴方向尺寸） |

### 核心接口：`setSize`
| 函数签名 | `void setSize(float width, float height, float depth)` |
|----------|-------------------------------------------------------|
| 功能说明 | 设置长方体的宽度、高度、深度，自动清空原有网格数据并重新生成长方体网格（顶点、法线、纹理坐标、三角形索引）；若VAO已初始化，将自动更新OpenGL缓冲区并尝试渲染 |
| 参数说明 | 1. `width`：[输入] 长方体宽度（X轴方向），要求>0.0f<br>2. `height`：[输入] 长方体高度（Y轴方向），要求>0.0f<br>3. `depth`：[输入] 长方体深度（Z轴方向），要求>0.0f |
| 注意事项 | 1. 调用前会先执行`clear()`，清空原有网格数据，避免数据冗余<br>2. 生成的长方体中心位于坐标原点，顶点法线为平滑法线（相邻3个面法线的归一化平均值）<br>3. 若VAO未初始化（未调用`initBuffers()`），仅生成CPU端网格数据，不更新GPU缓冲区<br>4. 纹理坐标采用面映射，每个面的纹理UV范围为[0,0]~[1,1] |

---

## 3. 四棱柱类：`Tetrahedron`
### 头文件
`Tetrahedron_prism.h`

### 类说明
`Tetrahedron`继承自`Geometry`，实现了底面为任意四边形的直棱柱（沿Z轴延伸），支持动态修改底面顶点和延伸深度并重新生成网格，几何体类型标记为`TETRAHEDRON`。

### 构造函数
| 函数签名 | 功能说明 |
|----------|----------|
| `Tetrahedron(glm::vec3 bottomLeft = glm::vec3(0.0f), glm::vec3 bottomRight= glm::vec3(0.0f), glm::vec3 topLeft = glm::vec3(0.0f), glm::vec3 topRight = glm::vec3(0.0f), float depth = 1.0f)` | 构造函数，初始化四棱柱底面四个顶点和延伸深度，自动调用`setSize()`生成网格数据，几何体类型标记为`TETRAHEDRON` |

### 公共查询接口
| 函数签名 | 返回值 | 功能说明 |
|----------|--------|----------|
| `glm::vec3 getbottomLeft() const` | `glm::vec3` | 获取底面左下角顶点坐标 |
| `glm::vec3 getbottomRight() const` | `glm::vec3` | 获取底面右下角顶点坐标 |
| `glm::vec3 gettopLeft() const` | `glm::vec3` | 获取底面左上角顶点坐标 |
| `glm::vec3 gettopRight() const` | `glm::vec3` | 获取底面右上角顶点坐标 |
| `float getDepth() const` | `float` | 获取四棱柱沿Z轴的延伸深度 |

### 核心接口：`setSize`
| 函数签名 | `void setSize(glm::vec3 bottomLeft, glm::vec3 bottomRight, glm::vec3 topLeft, glm::vec3 topRight, float depth)` |
|----------|----------------------------------------------------------------------------------------------------------------|
| 功能说明 | 设置四棱柱的底面四个顶点和Z轴延伸深度，自动清空原有网格数据并重新生成四棱柱网格（顶点、法线、纹理坐标、三角形索引）；若VAO已初始化，将自动更新OpenGL缓冲区并尝试渲染 |
| 参数说明 | 1. `bottomLeft`：[输入] 底面左下角顶点3D坐标<br>2. `bottomRight`：[输入] 底面右下角顶点3D坐标<br>3. `topLeft`：[输入] 底面左上角顶点3D坐标<br>4. `topRight`：[输入] 底面右上角顶点3D坐标<br>5. `depth`：[输入] 沿Z轴正方向的延伸深度（可负，控制延伸方向） |
| 注意事项 | 1. 调用前会先执行`clear()`，清空原有网格数据，避免数据冗余<br>2. 顶面顶点由底面顶点沿Z轴平移`depth`生成（顶点坐标 + (0,0,depth)）<br>3. 先计算每个面的面法线，再通过相邻面法线累加归一化生成顶点平滑法线<br>4. 底面四个顶点建议按**顺时针/逆时针有序传入**，避免网格法线方向错误或渲染异常<br>5. 若VAO未初始化（未调用`initBuffers()`），仅生成CPU端网格数据，不更新GPU缓冲区<br>6. 每个面的纹理UV范围为[0,0]~[1,1]，映射规则与长方体一致 |

---

## 4. 球体类：`Sphere`
### 头文件
`Sphere.h`

### 类说明
`Sphere`继承自`Geometry`，实现了球心位于坐标原点的球体几何体，通过分段数控制网格精度，支持动态修改半径并重新生成网格，几何体类型标记为`SPHERE`。

### 构造函数
| 函数签名 | 功能说明 |
|----------|----------|
| `Sphere(float radius = 1.0f, int segments = 16)` | 构造函数，初始化球体半径（默认1.0f）和分段数（默认16，控制网格精度），自动调用`setRadius()`生成网格数据，几何体类型标记为`SPHERE` |

### 公共查询接口
| 函数签名 | 返回值 | 功能说明 |
|----------|--------|----------|
| `float getRadius() const` | `float` | 获取球体当前半径 |
| `int getSegments() const` | `int` | 获取球体当前分段数（网格精度） |

### 核心接口：`setRadius`
| 函数签名 | `void setRadius(float radius)` |
|----------|--------------------------------|
| 功能说明 | 设置球体的半径，自动清空原有网格数据并重新生成球体网格（顶点、法线、纹理坐标、三角形索引）；分段数保持构造时的值不变；若VAO已初始化，将自动更新OpenGL缓冲区并尝试渲染 |
| 参数说明 | `radius`：[输入] 球体半径，要求>0.0f，半径越大球体尺寸越大 |
| 注意事项 | 1. 调用前会先执行`clear()`，清空原有网格数据，避免数据冗余<br>2. 生成的球体球心位于坐标原点，顶点法线为从球心指向顶点的归一化向量（保证球面光照效果自然）<br>3. 纹理坐标采用UV映射：U轴对应经度（0~1），V轴对应纬度（0~1），覆盖整个球面<br>4. 网格精度由构造时的`segments`控制：分段数越大，网格越细腻，渲染开销也越高（建议取值16~64）<br>5. 网格生成时将每个四边形面拆分为两个**逆时针顺序的三角形**，符合OpenGL默认正面剔除规则<br>6. 若VAO未初始化（未调用`initBuffers()`），仅生成CPU端网格数据，不更新GPU缓冲区 |

---

## 全局注意事项
1.  所有类均支持移动语义，仅可通过移动构造/赋值转移资源，不可拷贝。
2.  空间变换操作（平移、旋转、缩放）仅修改模型矩阵，不改变原始顶点数据，保证顶点数据的可复用性。
3.  网格生成完成后，需调用`initBuffers()`将数据上传至GPU，否则无法进行渲染。
4.  当几何体参数（如长方体长宽高、球体半径）修改后，网格会自动重新生成，无需手动调用额外接口。