/*******************************************************************************************************************
* FILE NAME: deque_ll.c
*                                                                                                               
* PURPOSE: This file implements the functions defined in deque.h, with a linked list
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
* memcpy                        copies x number of bytes from one memory position to another memory position    https://man7.org/linux/man-pages/man3/memcpy.3.html
* fprintf                       writes formatted data to a stream                                               https://man7.org/linux/man-pages/man3/fprintf.3p.html
* 
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
* 14-01-2025    Tiago Rodrigues                               1         File preparation     
* 23-01-2025    Tiago Rodrigues                               1         Implementation of deque using a linked list     
* 27-01-2025    Tiago Rodrigues                               1         Added Comments to functions  
* 03-02-2025    Tiago Rodrigues                               1         Added fix to data being NULL bug
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

/*****************************************************/


/* 3 external declarations */
/*****************************************************/

/*****************************************************/


/* 4 typedefs */
/*****************************************************/


/*****************************************************/


/* 5 global variable declarations */
/*****************************************************/

struct data
{
        void* data_element;
        struct data* next;
        struct data* previous;        
};


struct deque
{
        uint64_t datatype_size;                         
        uint64_t deque_size;                                    // needed for the check_size(otherwise O(k))
        struct data* deque_front;
        struct data* deque_back; 

        // struct data *deque_data;
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
* --------	-----------	---	--------------------------
* id_of_deque	        void**	        I/O	pointer to the memory position of the deque to implement
* size_of_datatype      uint64_t        I       byte size of datatype to place in the deque
* elements_to_allocate  uint64_t        I       number of elements to allocate for the deque
*
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
                fprintf(stderr, "deque pointer location is null\n");
                return ;
        }
                

        // Allocation of a deque struct
        (*id_of_deque) = malloc(1*sizeof(struct deque));                       
        if(NULL == *id_of_deque)
        {
                perror("Memory allocation failed");
                return ;
        }

        ((struct deque*)(*id_of_deque))->deque_front = NULL;
        ((struct deque*)(*id_of_deque))->deque_back = NULL;
        ((struct deque*)(*id_of_deque))->deque_size = 0;
        ((struct deque*)(*id_of_deque))->datatype_size = size_of_datatype;
        
        
        return ;        
}



/******************************************************************
*
* FUNCTION NAME: check_deque_front
*
* PURPOSE: Returns the memory position of the element that is currently on the front of the deque
*
* ARGUMENTS: Returns the memory position of the element that is currently on the front of the deque
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* --------	-----------	---	--------------------------
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
                fprintf(stderr, "deque pointer location is null\n");
                return NULL;
        }


        if(check_deque_is_empty(id_of_deque))                       
                return NULL;

        if(NULL != ((struct deque*)id_of_deque)->deque_front)
                return ((struct deque*)id_of_deque)->deque_front->data_element;
  
        return NULL;
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
* --------	-------------	---	--------------------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
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


        if(NULL != ((struct deque*)id_of_deque)->deque_back)
                return ((struct deque*)id_of_deque)->deque_back->data_element;


        return NULL;
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
* --------	-----------	---	--------------------------
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
        *  Variable        Type         Description
        *  --------        ----         -----------
        *  aux_ptr         struct data* pointer to data node to be removed
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "Deque pointer location is null\n");
                return ;
        }   
        if(!check_deque_is_empty(id_of_deque))
        {
                

                struct data *aux_ptr = ((struct deque*)id_of_deque)->deque_front;

                ((struct deque*)id_of_deque)->deque_front = ((struct deque*)id_of_deque)->deque_front->next;
                if(NULL != ((struct deque*)id_of_deque)->deque_front)
                        ((struct deque*)id_of_deque)->deque_front->previous = NULL;                

                free(aux_ptr->data_element);
                free(aux_ptr);

                ((struct deque*)id_of_deque)->deque_size--;

                if(0 == ((struct deque*)id_of_deque)->deque_size)
                        ((struct deque*)id_of_deque)->deque_back = NULL;                        // TODO: check if there are other places where this might be a problem

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
* --------	-----------	---	--------------------------
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
        *  Variable        Type         Description
        *  --------        ----         -----------
        *  aux_ptr         struct data* pointer to data node to be removed
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "Deque pointer location is null\n");
                return ;
        }   
        if(!check_deque_is_empty(id_of_deque))
        {
                

                struct data *aux_ptr = ((struct deque*)id_of_deque)->deque_back;

                ((struct deque*)id_of_deque)->deque_back = ((struct deque*)id_of_deque)->deque_back->previous;
                if(NULL != ((struct deque*)id_of_deque)->deque_back)
                        ((struct deque*)id_of_deque)->deque_back->next = NULL;                

                free(aux_ptr->data_element);
                free(aux_ptr);

                ((struct deque*)id_of_deque)->deque_size--;

                if(0 == ((struct deque*)id_of_deque)->deque_size)
                        ((struct deque*)id_of_deque)->deque_front = NULL;                        // TODO: check if there are other places where this might be a problem

        }
        return;

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
* --------	-------------	---	--------------------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to which the element is being push to
* data_to_push  void*	        I	pointer to the memory position of the data to push into the deque
*
* RETURNS: void
*
*
*
*****************************************************************/
void deque_push_back(void* id_of_deque, void* data_to_push)
{
       /* LOCAL VARIABLES:
        *  Variable     Type            Description
        *  --------     ------------    -----------
        *  aux_data_ptr struct data*    pointer to the new node to allocate and push into the deque
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "Deque pointer location is null\n");
                return ;
        }
        if(UINT64_MAX == check_deque_size(id_of_deque))
        {
                fprintf(stderr, "Deque full, can't add more elements\n");
                return ;
        }
        if(NULL == data_to_push)
        {
                fprintf(stderr, "Data pointer is null\n");
                return ;
        }
       
        // Allocate space in the deque for the array of values
        struct data *aux_data_ptr = (struct data*) malloc(1*sizeof(struct data));   
        if(NULL == aux_data_ptr)
        {
                perror("Memory allocation failed");
                return ;
        }

        aux_data_ptr->data_element = (void*) malloc(1*((struct deque*)id_of_deque)->datatype_size);
        if(NULL == aux_data_ptr->data_element)
        {
                perror("Memory allocation failed");
                return ;
        }
        
        memcpy(aux_data_ptr->data_element, data_to_push, ((struct deque*)id_of_deque)->datatype_size);
        aux_data_ptr->next = NULL;
        aux_data_ptr->previous = NULL;

        if(0 == ((struct deque*)id_of_deque)->deque_size)
        {
                ((struct deque*)id_of_deque)->deque_front = aux_data_ptr;
                ((struct deque*)id_of_deque)->deque_back = aux_data_ptr;
        }
        else
        {
                ((struct deque*)id_of_deque)->deque_back->next = aux_data_ptr;
                aux_data_ptr->previous = ((struct deque*)id_of_deque)->deque_back;
                ((struct deque*)id_of_deque)->deque_back = ((struct deque*)id_of_deque)->deque_back->next;
        }

        ((struct deque*)id_of_deque)->deque_size++;


        return ;

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
* --------	-------------	---	--------------------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to which the element is being push to
* data_to_push  void*	        I	pointer to the memory position of the data to push into the deque
*
* RETURNS: void
*
*
*
*****************************************************************/
void deque_push_front(void* id_of_deque, void* data_to_push)
{
       /* LOCAL VARIABLES:
        *  Variable     Type            Description
        *  --------     ------------    -----------
        *  aux_data_ptr struct data*    pointer to the new node to allocate and push into the deque
        */
        if(NULL == id_of_deque)
        {
                fprintf(stderr, "Deque pointer location is null\n");
                return ;
        }
        if(UINT64_MAX == check_deque_size(id_of_deque))
        {
                fprintf(stderr, "Deque full, can't add more elements\n");
                return ;
        }
        if(NULL == data_to_push)
        {
                fprintf(stderr, "Data pointer is null\n");
                return ;
        }
       
        // Allocate space in the deque for the array of values
        struct data *aux_data_ptr = (struct data*) malloc(1*sizeof(struct data));   
        if(NULL == aux_data_ptr)
        {
                perror("Memory allocation failed");
                return ;
        }

        aux_data_ptr->data_element = (void*) malloc(1*((struct deque*)id_of_deque)->datatype_size);
        if(NULL == aux_data_ptr->data_element)
        {
                perror("Memory allocation failed");
                return ;
        }
        
        memcpy(aux_data_ptr->data_element, data_to_push, ((struct deque*)id_of_deque)->datatype_size);
        aux_data_ptr->next = NULL;
        aux_data_ptr->previous = NULL;

        if(0 == ((struct deque*)id_of_deque)->deque_size)
        {
                ((struct deque*)id_of_deque)->deque_front = aux_data_ptr;
                ((struct deque*)id_of_deque)->deque_back = aux_data_ptr;
        }
        else
        {
                aux_data_ptr->next = ((struct deque*)id_of_deque)->deque_front;
                ((struct deque*)id_of_deque)->deque_front->previous = aux_data_ptr;
                ((struct deque*)id_of_deque)->deque_front = aux_data_ptr;
        }

        ((struct deque*)id_of_deque)->deque_size++;


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
* --------	-------------	---	--------------------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
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
                fprintf(stderr, "Deque pointer location is null\n");
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
* --------	-------------	---	--------------------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
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
                fprintf(stderr, "Deque pointer location is null\n");
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
* --------	-------------	---	--------------------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to free
*
* RETURNS: void
*
*
*
*****************************************************************/
void free_deque(void* id_of_deque)
{

        /* LOCAL VARIABLES:
        *  Variable        Type         Description
        *  --------        ------------ -----------
        *  aux_data_ptr    struct data* auxiliary pointer to data node to deallocate
        */
        if(NULL == id_of_deque)
                return;

        struct data *aux_data_ptr = ((struct deque*)id_of_deque)->deque_front; 

        while(NULL != (((struct deque*)id_of_deque)->deque_front))
        {
                ((struct deque*)id_of_deque)->deque_front = ((struct deque*)id_of_deque)->deque_front->next;
                free(aux_data_ptr->data_element);
                free(aux_data_ptr);
                aux_data_ptr = ((struct deque*)id_of_deque)->deque_front;
        }

        free(id_of_deque);
        return ;


}