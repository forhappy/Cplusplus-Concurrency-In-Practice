/*
 * ========================================================================
 *
 *       Filename:  hello-world.cc
 *
 *    Description:  std::thread hello world example.
 *
 *        Created:  09/14/2013 09:41:12 AM
 *
 *         Author:  Fu Haiping (forhappy), haipingf@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * ========================================================================
 */

#include <cstdio>
#include <cstdlib>
#include <iostream> // std::cout
#include <thread>   // std::thread

void thread_task() {
    std::cout << "hello thread" << std::endl;
}

int main(int argc, const char *argv[])
{
    std::thread t(thread_task);
    t.join();

    return EXIT_SUCCESS;
}
