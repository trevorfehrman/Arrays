#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array
{
  unsigned capacity; // How many elements can this array hold?
  unsigned count;    // How many states does the array currently hold?
  char **elements;   // The string elements contained in the array
} Array;

Array *create_array(unsigned capacity)
{
  // Allocate memory for the Array struct
  Array *arr = malloc(sizeof(Array));

  // Set initial values for capacity and count
  arr->capacity = capacity;
  arr->count = 0;

  // Allocate memory for elements
  arr->elements = malloc(capacity * sizeof(char *));

  return arr;
}

void destroy_array(Array *arr)
{

  // Free all elements
  for (int i = 0; i < arr->count; i++)
  {
    free(arr->elements[i]);
  }
  free(arr->elements);
  // Free array
  free(arr);
}

void resize_array(Array *arr)
{
  void *new_alloc = realloc(arr->elements, (arr->capacity * sizeof(char *) * 2));
  arr->elements = new_alloc;
  arr->capacity = arr->capacity * 2;
}

char *arr_read(Array *arr, unsigned index)
{

  // Throw an error if the index is greater or equal to than the current count
  if (index >= arr->count)
  {
    perror("Ya dun forked up");
    return NULL;
  }
  // Otherwise, return the element at the given index
  return arr->elements[index];
}

void arr_insert(Array *arr, char *element, unsigned index)
{

  // Throw an error if the index is greater than the current count
  if (index > arr->count)
  {
    perror("Nope.");
    // TODO try returning NULL here, see what happens.
    return;
  }
  // Resize the array if the number of elements is over capacity
  if (arr->count == arr->capacity)
  {
    resize_array(arr);
  }
  // Move every element after the insert index to the right one position
  for (int i = arr->count; i > index; i--)
  {
    arr->elements[i] = arr->elements[i - 1];
  }
  // Copy the element (hint: use `strdup()`) and add it to the array
  char *newElement = strdup(element);
  arr->elements[index] = newElement;
  // Increment count by 1
  arr->count++;
}

void arr_append(Array *arr, char *element)
{

  // Resize the array if the number of elements is over capacity
  if (arr->capacity == arr->count)
  {
    resize_array(arr);
  }
  // or throw an error if resize isn't implemented yet.

  // Copy the element and add it to the end of the array
  char *newElement = strdup(element);
  arr->elements[arr->count] = newElement;
  // Increment count by 1
  arr->count++;
}

void arr_remove(Array *arr, char *element)
{
  char *foundElement;
  int foundIndex;
  // Search for the first occurence of the element and remove it.
  for (int i = 0; i < arr->count; i++)
  {
    if (strcmp(arr->elements[i], element) == 0)
    {
      foundElement = arr->elements[i];
      foundIndex = i;
      arr->elements[i] = NULL;
    }
  }
  // Don't forget to free its memory!
  free(foundElement);

  // Shift over every element after the removed element to the left one position
  for (int i = foundIndex; i < arr->count - 1; i++)
  {
    arr->elements[i] = arr->elements[i + 1];
    arr->elements[i + 1] = NULL;
  }
  // Decrement count by 1
  arr->count--;
}

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr)
{
  printf("[");
  for (int i = 0; i < arr->count; i++)
  {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1)
    {
      printf(",");
    }
  }
  printf("]\n");
}

#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
