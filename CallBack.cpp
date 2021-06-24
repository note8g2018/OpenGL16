#include "CallBack.h"

void framebuffer_size_callback(GLFWwindow* window, int width_window,
    int height_window)
{
    glViewport(0, 0, width_window, height_window);
}

void key_callback(GLFWwindow* window, int key, int scancode,
    int action, int mods)
{
    if(mods == GLFW_MOD_SHIFT)
    {
        cout << "mods == shift" << endl;
        Camera::speed_factor = 50.0f;
    }
    else
    {
        cout << "mods != shift" << endl;
        Camera::speed_factor = 1.0f;
    }
    //if(key == GLFW_KEY_LEFT_SHIFT)
    //{
    //    switch(action)
    //    {
    //        case GLFW_PRESS:
    //            cout << "Press" << endl;
    //            Camera::speed_factor = 50.0f;
    //            break;
    //        case GLFW_REPEAT:
    //            cout << "Hold" << endl;
    //            Camera::speed_factor = 50.0f;
    //            break;
    //        case GLFW_RELEASE:
    //            cout << "RELEASE" << endl;
    //            Camera::speed_factor = 1.0f;
    //            break;
    //        default:
    //            break;
    //    }
    //    //Camera::speed_factor = 50.0f;
    //}
}