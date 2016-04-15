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
 *
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * ========================================================================
 */

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // cout
#include <thread>   // thread

using namespace std;

void thread_task() 
{
    cout << "hello thread" << endl;
}

int main(int argc, const char *argv[])
{
    thread t(thread_task);
    t.join();

    return EXIT_SUCCESS;
}
