# cg-final
2025年中山大学计算机图形学作业

📚 Ready to Development
建议首先阅读并完善 [docs](/docs) 中的文档

关于使用 GitHub 合作的注意事项，请阅读 [Git_Guide.md](/docs/Git_Guide.md) 和 [PR_WorkFlow.md](/docs/PR_WorkFlow.md)

## 🛠️ Installation

Clone this repo:

```
git clone https://github.com/Super-Gluten/cg-final.git
```

关于环境配置的详细信息和配置步骤，请阅读 [Install.md](/docs/Install.md)

## 📂 概览

以下为项目结构示例：

```
.
├─docs/                        
│   ├── Git_Guide.md           # Github 命令行使用手册
│   ├── Install.md             # 安装环境文档
│   └── PR_WorkFlow.md         # PR和协作手册
|
├─src/                         
│   ├── Buildings/             # 建筑相关功能模块
│   ├── Light_System/          # 光照系统功能模块
│   ├── Scene_Component/       # 场景部件功能模块
│   └── main.cpp               
|
├─test/                        
│   └── environment.cpp        # 环境检测功能代码
|
├── CMakeLists.txt             # CMake 项目构建配置文件
```