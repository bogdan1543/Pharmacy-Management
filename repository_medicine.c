#include "repository_medicine.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/// Create an empty list
/// \return List
MedicineList createEmpty() {
    MedicineList lst;
    lst.capacity = 50;
    lst.elems = malloc(sizeof(Medicine) * lst.capacity);
    lst.length = 0;
    return lst;
}

/// Deallocate memory from the list
/// \param lst - MedicineList
void destroy(MedicineList *lst) {
    for (int i = 0; i < lst->length; i++) {
        ElemType m = lst->elems[i];
        destroyMedicine(&m);
    }
    lst->length = 0;
    free(lst->elems);
}

/// Deallocate memort from a copied list
/// \param lst - MedicineList
void destroy_copy(MedicineList *lst) {
    lst->length = 0;
    free(lst->elems);
}

/// Verify if an element exists
/// \param lst - MedicineList
/// \param code - int
/// \return Position of the element in list or -1 if it does not exist
int elem_exists(MedicineList *lst, int code) {
    for (int i = 0; i < lst->length; i++)
        if (lst->elems[i].code == code)
            return i;
    return -1;
}

/// Add an element to list
/// \param lst - MedicineList
/// \param el - ElemType
void add(MedicineList *lst, ElemType el) {
    //alocate a bigger capacity
    if (lst->capacity <= lst->length) {
        ElemType *aux = malloc(sizeof(ElemType) * (lst->capacity + 5));
        for (int i = 0; i < lst->length; i++) {
            aux[i] = lst->elems[i];
        }
        free(lst->elems);
        lst->elems = aux;
        lst->capacity += 5;
    }

    if (elem_exists(lst, el.code) != -1) {
        if (strcmp(lst->elems[elem_exists(lst, el.code)].name, el.name) == 0 &&
            lst->elems[elem_exists(lst, el.code)].concentration == el.concentration)
            lst->elems[elem_exists(lst, el.code)].stock += el.stock;
        else {
            printf("Medicine code already exists and has other attributes");
        }
    } else {
        lst->elems[lst->length] = el;
        lst->length++;
    }
}

/// Modify an element from list
/// \param lst - MedicineList
/// \param el - ElemType
void modify(MedicineList *lst, ElemType el) {
    if (elem_exists(lst, el.code) == -1)
        printf("Non-existent medicine!");
    else {
        strcpy(lst->elems[elem_exists(lst, el.code)].name, el.name);
        lst->elems[elem_exists(lst, el.code)].concentration = el.concentration;
    }

}

/// Delete an element stock
/// \param lst - MedicineList
/// \param code - int
void deleteStock(MedicineList *lst, int code) {
    if (elem_exists(lst, code) == -1) {
        printf("Non-existent medicine!");
    } else {
        lst->elems[elem_exists(lst, code)].stock = 0;
    }
}

/// Get an element from a specified position in the list
/// \param lst - MedicineList
/// \param pos - int
/// \return Element from position pos
ElemType get(MedicineList *lst, int pos) {
    return lst->elems[pos];
}

/// Get the size of the list
/// \param lst - MedicineList
/// \return Number of elements in the list
int size(MedicineList *lst) {
    return lst->length;
}


// tests
void testCreateList() {
    MedicineList lst = createEmpty();
    assert(size(&lst) == 0);
    destroy(&lst);
}

void testAdd() {
    MedicineList lst = createEmpty();
    assert(size(&lst) == 0);
    lst.capacity = 1;
    Medicine m = createMedicine(1, "paracetamol", 500, 20);
    add(&lst, m);
    assert(size(&lst) == 1);

    m = createMedicine(1, "paracetamol", 500, 20);
    add(&lst, m);
    assert(get(&lst, 0).stock == 40);
    destroyMedicine(&m);

    m = createMedicine(1, "nurofen", 500, 20);
    add(&lst, m);
    assert(get(&lst, 0).stock == 40);
    destroyMedicine(&m);


    m = createMedicine(1, "paracetamol", 300, 20);
    add(&lst, m);
    assert(get(&lst, 0).stock == 40);
    destroyMedicine(&m);


    m = createMedicine(2, "nurofen", 500, 20);
    add(&lst, m);
    assert(get(&lst, 1).stock == 20);
    assert(size(&lst) == 2);
    destroy(&lst);
}

void testModify() {
    MedicineList lst = createEmpty();
    add(&lst, createMedicine(1, "paracetamol", 500, 20));
    Medicine m = createMedicine(1, "nurofen", 300, 0);
    modify(&lst, m);
    assert(strcmp(get(&lst, 0).name, "nurofen") == 0);
    assert(get(&lst, 0).concentration == 300);
    destroyMedicine(&m);

    m = createMedicine(2, "nuro", 30, 0);
    modify(&lst, m);
    assert(size(&lst) == 1);
    assert(elem_exists(&lst, m.code) == -1);
    destroyMedicine(&m);
    destroy(&lst);

}

void testDeleteStock() {
    MedicineList lst = createEmpty();
    add(&lst, createMedicine(1, "paracetamol", 500, 20));
    deleteStock(&lst, 2);
    assert(get(&lst, 0).stock == 20);
    deleteStock(&lst, 1);
    assert(get(&lst, 0).stock == 0);
    assert(size(&lst) == 1);
    Medicine m = createMedicine(2, "nuro", 30, 0);
    assert(elem_exists(&lst, m.code) == -1);
    destroyMedicine(&m);
    destroy(&lst);
}

void testUtilsRepo() {
    MedicineList lst = createEmpty();
    Medicine m = createMedicine(1, "paracetamol", 500, 20);
    add(&lst, m);
    int code = 1;
    assert(elem_exists(&lst, code) == 0);
    assert(get(&lst, elem_exists(&lst, m.code)).code == m.code);
    assert(strcmp(get(&lst, elem_exists(&lst, m.code)).name, m.name) == 0);
    assert(get(&lst, elem_exists(&lst, m.code)).concentration == m.concentration);
    assert(get(&lst, elem_exists(&lst, m.code)).stock == m.stock);
    destroy(&lst);
}