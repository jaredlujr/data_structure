
#include "seq_queue.hpp"
#include "link_queue.hpp"



int main(void)
{

    LinkQueue <int> q1;
    SeqQueue <int> q2;
    int tmp;
    int i;
    for(i=0;i<15;i++)
        q1.enQueue(i); 
    while(!q1.isEmpty()) 
    {   
        tmp = q1.deQueue();
        std::cout<< tmp<< "\t";
        //q1.deQueue();
    }
    std::cout << "########" <<std::endl;

    return 0;
}

