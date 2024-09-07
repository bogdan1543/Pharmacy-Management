#ifndef _REPOSITORY_MEDICINE_H_
#define _REPOSITORY_MEDICINE_H_


#include "medicine.h"

/*
    Object MedicineList definition
 */
typedef Medicine ElemType;
typedef struct {
    ElemType *elems;
    int length;
    int capacity;
} MedicineList;

/*
    Create empty list
 */
MedicineList createEmpty();

/*
    Deallocate memory from list
 */
void destroy(MedicineList *lst);

/*
    Deallocate memory from a copy list
 */
void destroy_copy(MedicineList *lst);

/*
    Add an element to list
 */
void add(MedicineList *lst, ElemType el);

/*
    Modify an element from list
 */
void modify(MedicineList *lst, ElemType el);

/*
    Delete an element stock
 */
void deleteStock(MedicineList *lst, int code);

/*
    Get an element from a specified position
    return the element
 */
ElemType get(MedicineList *lst, int pos);

/*
    Return the number of elements in list
 */
int size(MedicineList *lst);


// tests
void testCreateList();

void testAdd();

void testModify();

void testDeleteStock();

void testUtilsRepo();

#endif