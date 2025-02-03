
/*******************************************************************************************************
* NAME: deque.h                                                              
*                                                                                                       
* PURPOSE: This file defines the function prototypes for a deque implementation                                                                      
*                                                                                                       
* GLOBAL VARIABLES: None                                                                                
*                                                                                                       
*                                                                                                       
* DEVELOPMENT HISTORY:                                                                                  
*                                                                                                       
* Date          Author          Change Id       Release         Description Of Change                   
* ----------    --------------- ---------       -------         -----------------------------------     
* 03-02-2025    Tiago Rodrigues                       1         File preparation and prototype functions      
*                                                                                                      
*******************************************************************************************************/
#ifndef DEQUE_H
#define DEQUE_H

/* 0 copyright/licensing */
/**********************************************************************
*
* 2025 Tiago Filipe Rodrigues tiagorodrigues1590@hotmail.com
*
***********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif



/* 1 includes */
/*****************************************************/
#include <stdint.h>

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


/*****************************************************/


/* 6 function prototypes */
/*****************************************************/


/******************************************************************
*
* FUNCTION NAME: create_deque
*
* PURPOSE: Allocates the needed memory for the deque wanted
*
* ARGUMENTS:
*
* ARGUMENT 	        TYPE	        I/O	DESCRIPTION
* --------              ----            ---     ------------
* id_of_deque	        void**	        I/O	pointer to the memory position of the deque to implement
* size_of_datatype      uint64_t        I       byte size of datatype to place in the deque
* elements_to_allocate  uint64_t        I       number of elements to allocate for the deque
*
* RETURNS: void
*
*
*
*****************************************************************/
void create_deque(void** id_of_deque, uint64_t size_of_datatype, uint64_t elements_to_allocate);


/******************************************************************
*
* FUNCTION NAME: check_deque_front
*
* PURPOSE: Returns the memory position of the element that is currently on the front of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* --------      ----            ---     ------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
* 
*
* RETURNS: void* (pointer to the memory position of the element at the front of the deque)
*
*
*
*****************************************************************/
void* check_deque_front(void* id_of_deque);




/******************************************************************
*
* FUNCTION NAME: check_deque_back    
*
* PURPOSE: Returns the memory position of the element that is currently on the back of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* --------      ----            ---     ------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
* 
*
* RETURNS: void* (pointer to the memory position of the element at the back of the deque)
*
*
*
*****************************************************************/
void* check_deque_back(void* id_of_deque);


/******************************************************************
*
* FUNCTION NAME: deque_pop_front
*
* PURPOSE: Removes one position from the front of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* --------      ----            ---     ------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to pop from
*
*
* RETURNS: void
*
*
*
*****************************************************************/
void deque_pop_front(void* id_of_deque);

/******************************************************************
*
* FUNCTION NAME: deque_pop_back
*
* PURPOSE: Removes one position from the back of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* --------      ----            ---     ------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to pop from
*
*
* RETURNS: void
*
*
*
*****************************************************************/
void deque_pop_back(void* id_of_deque);



/******************************************************************
*
* FUNCTION NAME: deque_push_front
*
* PURPOSE: Pushes an element to the front of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* --------      ----            ---     ------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to which the element is being push to
* data_to_push  void*	        I	pointer to the memory position of the data to push into the deque
*
*
* RETURNS: void
*
*
*
*****************************************************************/
void deque_push_front(void* id_of_deque, void* data_to_push);


/******************************************************************
*
* FUNCTION NAME: deque_push_back
*
* PURPOSE: Pushes an element to the back of the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* --------      ----            ---     ------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to which the element is being push to
* data_to_push  void*	        I	pointer to the memory position of the data to push into the deque
*
*
* RETURNS: void
*
*
*
*****************************************************************/
void deque_push_back(void* id_of_deque, void* data_to_push);


/******************************************************************
*
* FUNCTION NAME: check_deque_is_empty
*
* PURPOSE: Checks if the deque is empty or not
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* --------      ----            ---     ------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
*
*
* RETURNS: uint8_t
*
*
*
*****************************************************************/
uint8_t check_deque_is_empty(void* id_of_deque);



/******************************************************************
*
* FUNCTION NAME: check_deque_size
*
* PURPOSE: Will return the current element count in the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* --------      ----            ---     ------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to check
*
*
* RETURNS: uint64_t (size of the deque)
*
*
*
*****************************************************************/
uint64_t check_deque_size(void* id_of_deque);


/******************************************************************
*
* FUNCTION NAME: free_deque
*
* PURPOSE: Frees the memory allocated for the deque
*
* ARGUMENTS:
*
* ARGUMENT 	TYPE	        I/O	DESCRIPTION
* --------      ----            ---     ------------
* id_of_deque   void*	        I	pointer to the memory position of the deque to free
*
*
* RETURNS: void
*
*
*
*****************************************************************/
void free_deque(void* id_of_deque);





#ifdef __cplusplus
}
#endif


#endif

























