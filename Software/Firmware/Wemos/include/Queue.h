#pragma once
/**
 * @file       : Queue.h
 * @description: Implements a Queue based on templates, so different types can be used. The type and the total-1
 *               number of elements to hold are given. For example: Queue<uint8_t, 25>
 * @date       : 03-10-2021
 * @author     : Maurice Snoeren (MS)
 * @version    : 0.1
 * @todo       : 
 * @updates
 * 
 */
#include <stdint.h>

/* Template variables V is the variable type that is used and T is the amount of elements
   should be initially configured.
*/
template<typename V, uint8_t T>

/* Class: Queue
   The class queue implements a simple queue data type.
*/
class Queue {
private:
    /* This list contains the elements that are used to implement the queue with.
    */
    V list[T];

    /* This is the start pointer that points to the first element in the list.
    */
    uint8_t start;

    /* This is the pointer that points to the index in which the element should be placed in. When
       the start and pointer are equal, no elements are in the queue.
    */
    uint8_t pointer;

public:
   /* The constructor does not require any variables.
   */
   Queue() {
      this->start   = 0;
      this->pointer = 0;
   }

   /* Adds an element to the queue. The method returns false when the queue is full and no element
      could be added. When the flag overwrite is true, the method always returns true and always
      the element is added. The element that has been added first will be discarded, so only the
      newest element are in the queue.
   */
   uint8_t add(V element, uint8_t overwrite = false) {
      if ( this->space() > 1 ) { // If 0, the size becomes 0 because start==pointer
         this->list[this->pointer] = element;
         this->pointer = (this->pointer + 1) % T;
         return true;
      }
      
      if (overwrite) {
         this->list[this->pointer] = element;
         this->pointer = (this->pointer + 1) % T;
         this->start   = (this->start   + 1 ) % T;
         return true;
      }

      return false;
   }
   
   /* Pops an element from the queue and shrinks the list by one. When there are no element given,
      it just returns the element where the start pointer points at. Make sure you always check if
      any elements are in the queue.
   */
   V* pop() {
      if ( this->size() > 0 ) {
         V* element = &this->list[this->start];
         this->start = (this->start + 1) % T;
         return element;
      }

      return &this->list[this->start]; // The caller should check is something is in.
   }

   V* peek() {
      if ( this->size() > 0 ) {
         V* element = &this->list[this->start];
         return element;
      }

      return &this->list[this->start]; // The caller should check is something is in.
   }

   /* Returns the size of the queue.
   */
   uint8_t size() {
      if ( this->pointer >= this->start ) {
         return this->pointer - this->start;
      }

      return T - this->start + this->pointer;
   }

    /* Removes all the elements from the queue.
    */
    void empty() {
      this->start   = 0;
      this->pointer = 0;
   }
    
   /* Returns how much elements could be added to the queue.
   */
   uint8_t space() {
      return T - this->size() - 1;
   } 
};
