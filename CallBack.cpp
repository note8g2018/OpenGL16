#include "CallBack.h"

void framebuffer_size_callback(GLFWwindow* window, int width_window,
    int height_window)
{
    glViewport(0, 0, width_window, height_window);
}

void key_callback(GLFWwindow* window, int key, int scancode,
    int action, int mods)
{
    //cout << key << endl;
    //cout << scancode << endl;
    //cout << action << endl;
    //cout << mods << endl;
    /*if(key == GLFW_KEY_LEFT_SHIFT && action == GLFW_REPEAT)
    {
        Camera::speed_factor = 50.0f;
    }*/
    if(mods == GLFW_MOD_SHIFT)
    {
        Camera::speed_factor = 50.0f;
    }
    else if(mods != GLFW_MOD_SHIFT)
    {
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