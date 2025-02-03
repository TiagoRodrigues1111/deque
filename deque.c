/*******************************************************************************************************************
* FILE NAME: deque.c
*                                                                                                               
* PURPOSE: This file implements the functions defined in deque.h, with an array
*                                                                                                               
* FILE REFERENCES:                                                                                              
*                                                                                                               
* Name                          I/O                     Description                                             
* ----                          ---                     -----------                                             
* none     
                                                                                                          
* EXTERNAL VARIABLES:                                                                                           
*                                                                                        
*                                                                                                               
* Name          Type            I/O                     Description                                             
* ----          ----            ---                     -----------                                             
* none
*
*                                                                                                             
* EXTERNAL REFERENCES:                                                                                          
* Name                          Description                                                                     
* ----                          -----------                                                                     
* malloc                        allocates memory space                                                          https://man7.org/linux/man-pages/man3/free.3.html
* realloc                       reallocates memory space                                                        https://man7.org/linux/man-pages/man3/realloc.3p.html
* memcpy                        copies x number of bytes from one memory position to another memory position    https://man7.org/linux/man-pages/man3/memcpy.3.html
* fprintf                       writes formatted data to a stream                                               https://man7.org/linux/man-pages/man3/fprintf.3p.html
*     
* ABNORMAL TERMINATION CONDITIONS, ERROR AND WARNING MESSAGES:                                                  
*             
*                                                                                                  
* ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS:                                                                       
*  It is assumed that the deque will never have more than 2^64 elements.                               
*  It is assumed that the user will grab only 1 element size from the memory position returned from check_deque_front and check_deque_back
*
*
*
* NOTES:                                                                                                        
*
*
* REQUIREMENTS/FUNCTIONAL SPECIFICATIONS REFERENCES:                                                            
*
*                                                                                                               
* DEVELOPMENT HISTORY:                                                                                          
*                                                                                                               
* Date          Author                  Change Id       Release         Description Of Change                   
* ----------    ---------------         ---------       -------         ---------------------   
* 03-02-2025    Tiago Rodrigues                               1         File preparation and functions  
*                                                                                                               
* ALGORITHM (PDL)
*    
*
*                                                                                                           
****************************************************************************************************************/


/* 0 copyright/licensing */
/***************************************************************************************************************/
/*
*       2025 Tiago Filipe Rodrigues tiagorodrigues1590@hotmail.com
*/
/***************************************************************************************************************/


/* 1 includes */
/*****************************************************/

#include "deque.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*****************************************************/


/* 2 defines */
/*****************************************************/
#define INITIAL_ALLOC 3

/*****************************************************/


/* 3 external declarations */
/*****************************************************/

/*****************************************************/


/* 4 typedefs */
/*****************************************************/


/*****************************************************/


/* 5 global variable declarations */
/*****************************************************/


struct deque
{
        int64_t deque_front;                                    //zero is the first position of the data_back
        int64_t deque_back;
        uint64_t deque_size;    
        uint64_t deque_size_allocated_front;                    
        uint64_t deque_size_allocated_back;                                     
        uint64_t datatype_size;                                 // num_of_bytes
        uint64_t k_aux_front;                                 // auxiliary 4 bytes for reallocation      
        uint64_t k_aux_back;                                 // auxiliary 4 bytes for reallocation      
        void *deque_data_front;
        void *deque_data_back;
};


/*****************************************************/


/* 6 function prototypes */
/*****************************************************/

/*****************************************************/



/* 7 function declarations */
/*****************************************************/




/******************************************************************
*
* FUNCTION NAME: create_deque       
*
* PURPOSE: Allocates the needed memory for the deque wanted
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* id_of_deque	        void**	        I/O	pointer to the memory position of the deque to implement
* size_of_datatype      uint64_t        I       byte size of datatype to place in the deque
* elements_to_allocate  uint64_t        I       number of elements to allocate for the deque
*
* RETURNS: void
*
*
*
*****************************************************************/
void create_deque(void** id_of_deque, uint64_t size_of_datatype, uint64_t elements_to_allocate)
{
        /* LOCAL VARIABLES:
        *  Variable        Type    Description
        *  --------        ----    -----------
        *  None
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "Deque pointer location is null\n");
                return ;
        }
                

        // Allocation of a deque struct
        (*id_of_deque) = malloc(1*sizeof(struct deque));                       
        if(NULL == *id_of_deque)
        {
                perror("Memory allocation failed");
                return ;
        }

        if(0 == elements_to_allocate)
        {
                ((struct deque*)(*id_of_deque))->deque_size_allocated_front = INITIAL_ALLOC;      // assumed that the number of elements to allocate initially is INITIAL_ALLOC (3 by default)
                ((struct deque*)(*id_of_deque))->deque_size_allocated_back = INITIAL_ALLOC;      // assumed that the number of elements to allocate initially is INITIAL_ALLOC (3 by default)
        }
        else
        {
                ((struct deque*)(*id_of_deque))->deque_size_allocated_front = elements_to_allocate;
                ((struct deque*)(*id_of_deque))->deque_size_allocated_back = elements_to_allocate;
                
        }
        ((struct deque*)(*id_of_deque))->deque_front = 0;
        ((struct deque*)(*id_of_deque))->deque_back = 0;
        ((struct deque*)(*id_of_deque))->deque_size = 0;
        ((struct deque*)(*id_of_deque))->datatype_size = size_of_datatype;
        ((struct deque*)(*id_of_deque))->k_aux_front = 1;
        ((struct deque*)(*id_of_deque))->k_aux_back = 1;
        
        // Allocate space in the deque for the array of values
        ((struct deque*)(*id_of_deque))->deque_data_front = (void*) malloc(((struct deque*)(*id_of_deque))->deque_size_allocated_front*((struct deque*)(*id_of_deque))->datatype_size);     
        if(NULL == ((struct deque*)(*id_of_deque))->deque_data_front)
        {
                perror("Memory allocation failed");
                return ;
        }
        ((struct deque*)(*id_of_deque))->deque_data_back = (void*) malloc(((struct deque*)(*id_of_deque))->deque_size_allocated_back*((struct deque*)(*id_of_deque))->datatype_size);     
        if(NULL == ((struct deque*)(*id_of_deque))->deque_data_back)
        {
                perror("Memory allocation failed");
                return ;
        }

        return ;        
}



/******************************************************************
*
* FUNCTION NAME: check_deque_front
*
* PURPOSE: Returns the memory position of the element that is currently on the front of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
* 
*
* RETURNS: void* (pointer to the memory position of the element at the front of the deque)
*
*
*
*****************************************************************/
void* check_deque_front(void* id_of_deque)
{
        /* LOCAL VARIABLES:
        *  Variable        Type    Description
        *  --------        ----    -----------
        *  None
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "Deque pointer location is null\n");
                return NULL;
        }
               

        if(check_deque_is_empty(id_of_deque))                       
                return NULL;

        if (((struct deque*)id_of_deque)->deque_front <= 0)
        {
                return (void *) &((uint8_t*)(((struct deque*)id_of_deque)->deque_data_back))[(-(((struct deque*)id_of_deque)->deque_front))*((struct deque*)id_of_deque)->datatype_size];   
        }
        else
        {
                return (void *) &((uint8_t*)(((struct deque*)id_of_deque)->deque_data_front))[((((struct deque*)id_of_deque)->deque_front)-1)*((struct deque*)id_of_deque)->datatype_size];   
        }
        
            



}

/******************************************************************
*
* FUNCTION NAME: check_deque_back    
*
* PURPOSE: Returns the memory position of the element that is currently on the back of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
* 
*
* RETURNS: void* (pointer to the memory position of the element at the back of the deque)
*
*
*
*****************************************************************/
void* check_deque_back(void* id_of_deque)
{
        /* LOCAL VARIABLES:
        *  Variable        Type    Description
        *  --------        ----    -----------
        *  None
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "deque pointer location is null\n");
                return NULL;
        }
               

        if(check_deque_is_empty(id_of_deque))                       
                return NULL;



        if (((struct deque*)id_of_deque)->deque_back >= 0)
        {
                return (void *) &((uint8_t*)(((struct deque*)id_of_deque)->deque_data_back))[((((struct deque*)id_of_deque)->deque_back))*((struct deque*)id_of_deque)->datatype_size];   
        }
        else
        {
                return (void *) &((uint8_t*)(((struct deque*)id_of_deque)->deque_data_front))[(-(((struct deque*)id_of_deque)->deque_back)-1)*((struct deque*)id_of_deque)->datatype_size];   
        }
        

}




/******************************************************************
*
* FUNCTION NAME: deque_pop_front
*
* PURPOSE: Removes one position from the front of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* id_of_deque   void*	        I	pointer to the memory position of the deque to pop from
*
*
* RETURNS: void
*
*
*
*****************************************************************/
void deque_pop_front(void* id_of_deque)
{
        /* LOCAL VARIABLES:
        *  Variable        Type    Description
        *  --------        ----    -----------
        *  None
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "deque pointer location is null\n");
                return ;
        }   
        if(!check_deque_is_empty(id_of_deque))
        {
                ((struct deque*)id_of_deque)->deque_size--;
                if(!check_deque_is_empty(id_of_deque))
                        ((struct deque*)id_of_deque)->deque_front--;                            // TODO: if front is at end of array, front is decremented instead
        }
        return;
}


/******************************************************************
*
* FUNCTION NAME: deque_pop_back
*
* PURPOSE: Removes one position from the back of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* id_of_deque   void*	        I	pointer to the memory position of the deque to pop from
*
*
* RETURNS: void
*
*
*
*****************************************************************/
void deque_pop_back(void* id_of_deque)
{
        /* LOCAL VARIABLES:
        *  Variable        Type    Description
        *  --------        ----    -----------
        *  None
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "deque pointer location is null\n");
                return ;
        }   
        if(!check_deque_is_empty(id_of_deque))
        {
                ((struct deque*)id_of_deque)->deque_size--;
                if(!check_deque_is_empty(id_of_deque))
                        ((struct deque*)id_of_deque)->deque_back--;                            // TODO: if front is at end of array, front is decremented instead
        }
        return;
}





/******************************************************************
*
* FUNCTION NAME: deque_push_front
*
* PURPOSE: Pushes an element to the front of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* id_of_deque   void*	        I	pointer to the memory position of the deque to which the element is being push to
* data_to_push  void*	        I	pointer to the memory position of the data to push into the deque
*
*
* RETURNS: void
*
*
*
*****************************************************************/
void deque_push_front(void* id_of_deque, void* data_to_push)
{
       /* LOCAL VARIABLES:
        *  Variable     Type    Description
        *  --------     ----    -----------
        *  deque_aux    void*   auxiliary pointer for the realloc operation
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "deque pointer location is null\n");
                return ;
        }
        if(INT64_MAX == ((struct deque*)id_of_deque)->deque_front)
        {
                fprintf(stderr, "deque full, can't add more elements\n");
                return ;
        }
        if(NULL == data_to_push)
        {
                fprintf(stderr, "Data pointer is null\n");
                return ;
        }


        if(!check_deque_is_empty(id_of_deque))                                  //caution (left == right will not work, because they are the same for 1 element)
                 ((struct deque*)id_of_deque)->deque_front++;
        
        ((struct deque*)id_of_deque)->deque_size++;
       

        if(((struct deque*)id_of_deque)->deque_front > (int64_t)((struct deque*)id_of_deque)->deque_size_allocated_front)               // TODO: better implementation to prevent uncontrollable increase in empty deque space
        {

                void* deque_aux = NULL;
                if(1 == (((struct deque*)id_of_deque)->k_aux_front))
                {
                        deque_aux = realloc(((struct deque*)id_of_deque)->deque_data_front, (((struct deque*)id_of_deque)->deque_size_allocated_front + ((struct deque*)id_of_deque)->deque_size_allocated_front)*((struct deque*)id_of_deque)->datatype_size);
                        if(NULL != deque_aux)                   // this is not needed, and could be placed after the while, however the shift left is a bit faster than the addition
                        {
                                ((struct deque*)id_of_deque)->deque_size_allocated_front <<= 1;
                        }
                }
                else
                {
                        while (NULL == deque_aux)
                        {
                                perror("Memory reallocation failed");
                                printf("Attempting smaller reallocation\n");
                                (((struct deque*)id_of_deque)->k_aux_front)<<=1;                              // always times 2 (TODO: might be faster to shift at the end again, and add 1 (check the lim->))
                                 
                                if(0 == (((struct deque*)id_of_deque)->deque_size_allocated_front/(((struct deque*)id_of_deque)->k_aux_front)))
                                {
                                        fprintf(stderr, "Impossible to reallocate deque\n");
                                        //perror("Impossible to reallocate deque");
                                        return ;
                                }
                                deque_aux = realloc(((struct deque*)id_of_deque)->deque_data_front, (((struct deque*)id_of_deque)->deque_size_allocated_front + (((struct deque*)id_of_deque)->deque_size_allocated_front / (((struct deque*)id_of_deque)->k_aux_front)))*((struct deque*)id_of_deque)->datatype_size);
                        }

                        ((struct deque*)id_of_deque)->deque_size_allocated_front += (((struct deque*)id_of_deque)->deque_size_allocated_front/(((struct deque*)id_of_deque)->k_aux_front));          
                }
                
                ((struct deque*)id_of_deque)->deque_data_front = deque_aux;

        }

        memcpy(check_deque_front(id_of_deque), data_to_push, ((struct deque*)id_of_deque)->datatype_size);

        return ;

}



/******************************************************************
*
* FUNCTION NAME: deque_push_back
*
* PURPOSE: Pushes an element to the back of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* id_of_deque   void*	        I	pointer to the memory position of the deque to which the element is being push to
* data_to_push  void*	        I	pointer to the memory position of the data to push into the deque
*
*
* RETURNS: void
*
*
*
*****************************************************************/
void deque_push_back(void* id_of_deque, void* data_to_push)
{
       /* LOCAL VARIABLES:
        *  Variable     Type    Description
        *  --------     ----    -----------
        *  deque_aux    void*   auxiliary pointer for the realloc operation
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "deque pointer location is null\n");
                return ;
        }
        if(INT64_MAX == ((struct deque*)id_of_deque)->deque_back)
        {
                fprintf(stderr, "deque full, can't add more elements\n");
                return ;
        }
        if(NULL == data_to_push)
        {
                fprintf(stderr, "Data pointer is null\n");
                return ;
        }


        if(!check_deque_is_empty(id_of_deque))                                  //caution (left == right will not work, because they are the same for 1 element)
                 ((struct deque*)id_of_deque)->deque_back++;
        
        ((struct deque*)id_of_deque)->deque_size++;
       

        if(((struct deque*)id_of_deque)->deque_back >= (int64_t)((struct deque*)id_of_deque)->deque_size_allocated_back)               // TODO: better implementation to prevent uncontrollable increase in empty deque space
        {
                void* deque_aux = NULL;
                if(1 == (((struct deque*)id_of_deque)->k_aux_back))
                {
                        deque_aux = realloc(((struct deque*)id_of_deque)->deque_data_back, (((struct deque*)id_of_deque)->deque_size_allocated_back + ((struct deque*)id_of_deque)->deque_size_allocated_back)*((struct deque*)id_of_deque)->datatype_size);
                        if(NULL != deque_aux)                   // this is not needed, and could be placed after the while, however the shift left is a bit faster than the addition
                        {
                                ((struct deque*)id_of_deque)->deque_size_allocated_back <<= 1;
                        }
                }
                else
                {
                        while (NULL == deque_aux)
                        {
                                perror("Memory reallocation failed");
                                printf("Attempting smaller reallocation\n");
                                (((struct deque*)id_of_deque)->k_aux_back)<<=1;                              // always times 2 (TODO: might be faster to shift at the end again, and add 1 (check the lim->))
                                 
                                if(0 == (((struct deque*)id_of_deque)->deque_size_allocated_back/(((struct deque*)id_of_deque)->k_aux_back)))
                                {
                                        fprintf(stderr, "Impossible to reallocate deque\n");
                                        //perror("Impossible to reallocate deque");
                                        return ;
                                }
                                deque_aux = realloc(((struct deque*)id_of_deque)->deque_data_back, (((struct deque*)id_of_deque)->deque_size_allocated_back + (((struct deque*)id_of_deque)->deque_size_allocated_back / (((struct deque*)id_of_deque)->k_aux_back)))*((struct deque*)id_of_deque)->datatype_size);
                        }

                        ((struct deque*)id_of_deque)->deque_size_allocated_back += (((struct deque*)id_of_deque)->deque_size_allocated_back/(((struct deque*)id_of_deque)->k_aux_back));          
                }
                
                ((struct deque*)id_of_deque)->deque_data_back = deque_aux;

        }

        memcpy(check_deque_back(id_of_deque), data_to_push, ((struct deque*)id_of_deque)->datatype_size);

        return ;

}





/******************************************************************
*
* FUNCTION NAME: check_deque_is_empty
*
* PURPOSE: Checks if the deque is empty or not
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
*
*
* RETURNS: uint8_t
*
*
*
*****************************************************************/
uint8_t check_deque_is_empty(void* id_of_deque)
{
        /* LOCAL VARIABLES:
        *  Variable        Type    Description
        *  --------        ----    -----------
        *  None
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "deque pointer location is null\n");
                return 0;
        }
                
        if(0 == ((struct deque*)id_of_deque)->deque_size)
                return 1;
        else
                return 0;


}


/******************************************************************
*
* FUNCTION NAME: check_deque_size
*
* PURPOSE: Will return the current element count in the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
*
*
* RETURNS: uint64_t (size of the deque)
*
*
*
*****************************************************************/
uint64_t check_deque_size(void* id_of_deque)
{
        /* LOCAL VARIABLES:
        *  Variable        Type    Description
        *  --------        ----    -----------
        *  None
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "deque pointer location is null\n");
                return 0;
        }

        return ((struct deque*)id_of_deque)->deque_size;



}

/******************************************************************
*
* FUNCTION NAME: free_deque
*
* PURPOSE: Frees the memory allocated for the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* id_of_deque   void*	        I	pointer to the memory position of the deque to free
*
*
* RETURNS: void
*
*
*
*****************************************************************/
void free_deque(void* id_of_deque)
{

        /* LOCAL VARIABLES:
        *  Variable        Type    Description
        *  --------        ----    -----------
        *  None
        */
        if(NULL == id_of_deque)
                return;

        if(NULL != ((struct deque*)id_of_deque)->deque_data_back)
                free(((struct deque*)id_of_deque)->deque_data_back);


        if(NULL != ((struct deque*)id_of_deque)->deque_data_front)
                free(((struct deque*)id_of_deque)->deque_data_front);

        free(id_of_deque);
        return ;


}