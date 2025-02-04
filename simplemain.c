

#include "deque.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void single_deque_simple_test()
{

        void *deque1 = NULL;
        uint16_t data_test = 0;

        create_deque(&deque1, sizeof(uint16_t), 0);

        printf("%u\n",check_deque_is_empty(deque1));
        

        data_test = 1;
        deque_push_back(deque1,(void*) &data_test);

        data_test = 2;
        deque_push_back(deque1,(void*) &data_test);
        
        data_test = 3;
        deque_push_back(deque1,(void*) &data_test);


        data_test = 4;
        deque_push_front(deque1,(void*) &data_test);       
        
  


        printf("%u\n", *((uint16_t*)check_deque_front(deque1)));
        deque_pop_front(deque1);

        printf("%u\n", *((uint16_t*)check_deque_front(deque1)));
        deque_pop_front(deque1);

        printf("%u\n", *((uint16_t*)check_deque_front(deque1)));


        printf("%u\n", *((uint16_t*)check_deque_back(deque1)));
        deque_pop_back(deque1);


        printf("%u\n", *((uint16_t*)check_deque_back(deque1)));
        printf("%u\n", *((uint16_t*)check_deque_front(deque1)));

        deque_pop_back(deque1);
        deque_pop_back(deque1);

        data_test = 70;
        deque_push_front(deque1,(void*) &data_test);     

        printf("%u\n", *((uint16_t*)check_deque_back(deque1)));
        printf("%u\n", *((uint16_t*)check_deque_front(deque1)));

        printf("%lu\n",check_deque_size(deque1));

        free_deque(deque1);

        return ;
}


/* High memory usage test */

void deque_stress_test1()
{
        void *deque1=NULL;
        uint16_t data1=0; 

        create_deque(&deque1,sizeof(uint16_t),100);

        // uint64_t n = 400000000;
        uint64_t n = 40000;
        
        while(0 < n)
        {
                
                if(NULL != check_deque_front(deque1))
                {
                        // printf("%lu",*((uint16_t*)check_deque_top(deque1)));
                }

                data1++;
                if(0 == (n & 1))
                        deque_push_back(deque1, (void*) &data1);
                else
                        deque_push_front(deque1, (void*) &data1);                        
                n--;

        }
        uint8_t oscilator = 0;
        while(!check_deque_is_empty(deque1))
        {
                if(oscilator)
                        deque_pop_back(deque1);
                else
                        deque_pop_front(deque1);

                oscilator ^= 1;
                // printf("%lu",check_deque_size(deque1));
        }

        free_deque(deque1);

}


void deque_stress_test2()
{
        void *deque1=NULL;
        void *deque2=NULL;
        uint16_t data1 =0;
        uint16_t data2 =0; 

        create_deque(&deque1,sizeof(uint16_t),5);
        create_deque(&deque2,sizeof(uint16_t),5);

        uint64_t n = 4000000;
        // uint64_t n = 4000000;
        
        while(0 < n)
        {
                deque_pop_back(deque1);
                deque_pop_back(deque2);
                data1++;
                data2++;
                deque_push_front(deque1, (void*) &data1);
                deque_push_front(deque2, (void*) &data2);
                n--;        
        }
        while(!check_deque_is_empty(deque1))
        {
                deque_pop_back(deque1);
                // printf("%lu",check_deque_size(deque1));
        }

        free_deque(deque1);
        free_deque(deque2);

}



/* Array of deque test */
void deque_stress_test3()
{
        void **deques=NULL;
        
        uint64_t num_of_deques = 20000;
        deques = (void **) malloc(num_of_deques* sizeof(void *));
        if(deques == NULL)
        {
                perror("");
                return ;
        }
        uint16_t data1=20;

        for(uint64_t i=0;i<num_of_deques;i++)
        {
                create_deque(&(deques[i]),sizeof(uint16_t),2);
                
                deque_push_back(deques[i], (void*) &data1);
                deque_push_back(deques[i], (void*) &data1);
        }

        for(uint64_t i=0;i<num_of_deques;i++)
        {

                while(!check_deque_is_empty(deques[i]))
                {
                if(NULL != check_deque_front(deques[i]))
                {
                        printf("%u ",*((uint16_t*)check_deque_front(deques[i])));
                }

                deque_pop_back(deques[i]);
                
                // printf("%lu",check_deque_size(deque1));
                }
        }

        for(uint64_t i=0;i<num_of_deques;i++)
        {
                free_deque(deques[i]);
        }        
        free(deques);
        
}



/* Random Operations test*/

void deque_stress_test4()
{
        void *deque1=NULL;
        uint16_t data1=0; 
        srand(time(NULL));                      
       
        create_deque(&deque1,sizeof(uint16_t),100);

        // uint64_t n = 400000000;
        uint64_t operations = 40000;

        

        while(0 < operations)
        {
                uint8_t op_to_do = rand() % 8;          
                switch (op_to_do)
                {
                case 0:                                         // deque_push_back
                        deque_push_back(deque1, (void*) &data1);
                        break;
                case 1:                                         // deque_push_front
                        deque_push_front(deque1, (void*) &data1);
                        break;                        
                case 2:                                         // deque_pop_back
                        deque_pop_back(deque1);
                        break; 
                case 3:                                         // deque_pop_front
                        deque_pop_front(deque1);
                        break; 
                case 4:                                         // check_deque_front
                       if(NULL != check_deque_front(deque1))
                        {
                                printf("deque front: %u\n",*((uint16_t*)check_deque_front(deque1)));
                        }
                        break; 
                case 5:
                        if(NULL != check_deque_back(deque1))
                        {
                                printf("deque back: %u\n",*((uint16_t*)check_deque_back(deque1)));
                        }
                        break; 
                case 6:                                         // check_deque_is_empty
                        printf("deque empty?: %u\n",check_deque_is_empty(deque1));
                        break; 
                case 7:                                         // check_deque_size
                        printf("deque size: %lu\n",check_deque_size(deque1));
                        break; 
                default:
                        break;
                }



                data1++;
                operations--;
        }

        free_deque(deque1);    


}



void tutorial()
{
        void *deque1 = NULL;
        create_deque(&deque1, sizeof(uint16_t),5);                              // create a deque of 5 elements of uint16_t size

        uint16_t data1 = 3;
        deque_push_front(deque1,(void*) &data1);                                      // Push a value onto the deque
        
        data1 = 20;
        deque_push_back(deque1,(void*) &data1);                                  // Push another value onto the deque

        if(!check_deque_is_empty(deque1))                                       // Checks if deque is not empty 
        {
                printf("%u\n",*((uint16_t*)check_deque_front(deque1)));         // prints top of deque
        }

        if(!check_deque_is_empty(deque1))                                       // Checks if deque is not empty 
        {
                printf("%u\n",*((uint16_t*)check_deque_back(deque1)));         // prints top of deque
        }


        deque_pop_back(deque1);                                                      // Pops a value from the deque

        printf("%lu\n",check_deque_size(deque1));                               // prints size of the deque

        deque_pop_front(deque1);                                                      // Pops a value from the deque

        free_deque(deque1);                                                     // frees the deque

        return ;



}


int main()
{

        // deque_stress_test1();
        // deque_stress_test2();
        // deque_stress_test3();
        // deque_stress_test4();
        tutorial();
        
        // single_deque_simple_test();
        
        return 0;  
}