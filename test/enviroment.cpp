// #include <glad/gl.h>

// OpenGL 固定管线 API
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

// ImGui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// GLM
#include <glm/glm.hpp>

#include <iostream>

void glfwErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

int main() {
    // 初始化GLFW
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) return -1;

    // 配置OpenGL 3.3 Core Profile（匹配glad_add_library的配置）
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __MINGW32__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "Glad Official CMake Demo", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // // 初始化Glad（官方2.x接口）
    // int gladVer = gladLoadGL(glfwGetProcAddress);
    // if (gladVer == 0) {
    //     std::cerr << "Failed to load Glad!" << std::endl;
    //     glfwDestroyWindow(window);
    //     glfwTerminate();
    //     return -1;
    // }
    // std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(gladVer) << "." << GLAD_VERSION_MINOR(gladVer) << std::endl;

    // 初始化ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core"); // 匹配OpenGL 3.3

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // ImGui绘制
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Glad Official CMake");
        ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));
        ImGui::Text("GLFW Version: %s", glfwGetVersionString());
        ImGui::Text("ImGui Version: %s", IMGUI_VERSION);
        ImGui::End();

        // 渲染
        ImGui::Render();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // 清理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}