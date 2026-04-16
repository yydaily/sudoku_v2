// File: mouse_control.mm
#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h> // for usleep
#include <iostream>

// 1. 移动鼠标到指定位置
void moveMouse(int x, int y) {
    CGPoint point = CGPointMake(x, y);
    // 方法一：直接移动，常用于普通UI自动化
    CGEventRef moveEvent = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, point, kCGMouseButtonLeft);
    CGEventPost(kCGHIDEventTap, moveEvent);
    CFRelease(moveEvent);
    
    // 方法二：瞬间跳转，常用于遥控、游戏等需要绝对位置场景，区别是更直接
    // CGWarpMouseCursorPosition(point);
}

// 2. 执行点击通用函数
void clickAt(int x, int y, CGEventType downType, CGEventType upType, CGMouseButton button) {
    CGPoint point = CGPointMake(x, y);
    // 创建鼠标按下事件
    CGEventRef downEvent = CGEventCreateMouseEvent(NULL, downType, point, button);
    // 创建鼠标抬起事件
    CGEventRef upEvent = CGEventCreateMouseEvent(NULL, upType, point, button);
    
    CGEventPost(kCGHIDEventTap, downEvent);
    usleep(10000); // 10毫秒的短暂停，模拟真实点击，可提高兼容性
    CGEventPost(kCGHIDEventTap, upEvent);
    
    CFRelease(downEvent);
    CFRelease(upEvent);
}

// 3. 左键单击
void leftClick(int x, int y) {
    clickAt(x, y, kCGEventLeftMouseDown, kCGEventLeftMouseUp, kCGMouseButtonLeft);
}

// 4. 左键双击
void doubleClick(int x, int y) {
    leftClick(x, y);
    usleep(100000); // 100毫秒的间隔是模拟双击的关键
    leftClick(x, y);
}

// 5. 右键单击
void rightClick(int x, int y) {
    clickAt(x, y, kCGEventRightMouseDown, kCGEventRightMouseUp, kCGMouseButtonRight);
}

/*
int main(int argc, const char * argv[]) {
    // 指定屏幕坐标
    int targetX = 500;
    int targetY = 500;
    
    std::cout << "执行左键单击..." << std::endl;
    leftClick(targetX, targetY);
    
    sleep(1);
    
    std::cout << "执行左键双击..." << std::endl;
    doubleClick(targetX + 100, targetY);
    
    sleep(1);
    
    std::cout << "执行右键单击..." << std::endl;
    rightClick(targetX - 100, targetY);
    
    return 0;
}
*/
