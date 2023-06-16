#include <qrunnable.h>

class MyRunnable : public QRunnable {
public:
    MyRunnable(std::function<void()> func) : m_func(func) {}

    void run() override {
        if (m_func) {
            m_func();  // call the function
        }
    }

private:
    std::function<void()> m_func;
};