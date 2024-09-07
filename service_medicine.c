#include "service_medicine.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/// Add a medicine in pharmacy
/// \param lst - MedicineList
/// \param code - int
/// \param name - char
/// \param concentration - float
/// \param stock - int
/// \return 1 if it is a validation error or 0 otherwise
int addMedicine(MedicineList *lst, int code, char *name, float concentration, int stock) {
    Medicine m = createMedicine(code, name, concentration, stock);

    //check if the element is valid
    int valid = validate(m);
    if (!valid) {
        //free memory
        destroyMedicine(&m);
        return 1;
    }

    add(lst, m);

    return 0;
}

/// Modify a medicine name/concentration in pharmacy
/// \param lst - MedicineList
/// \param code - int
/// \param name - char
/// \param concentration - float
/// \return 1 if it is a validation error or 0 otherwise
int modifyMedicine(MedicineList *lst, int code, char *name, float concentration) {
    Medicine m = createMedicine(code, name, concentration, 0);

    //check if the element is valid
    int valid = validate(m);
    if (!valid) {
        //free memory
        destroyMedicine(&m);
        return 1;
    }

    modify(lst, m);
    destroyMedicine(&m);

    return 0;
}

/// Delete a medicine stock from pharmacy
/// \param lst - MedicineList
/// \param code - int
/// \return 1 if it is a validation error or 0 otherwise
int deleteStockMedicine(MedicineList *lst, int code) {
    //check if the element code is valid
    int valid_code = validate_code(code);
    if (!valid_code)
        return 1;

    deleteStock(lst, code);

    return 0;
}

/// Compare two elements by attributes name and stock
/// \param a - ElemType
/// \param b - ElemType
/// \return 1 if a is bigger then b or 0 otherwise
int cmp(const ElemType *a, const ElemType *b) {
    if (strcmp(a->name, b->name) > 0) {
        return 1;
    } else {
        if (strcmp(a->name, b->name) == 0)
            if (a->stock < b->stock)
                return 1;
    }
    return 0;
}

/// Swaps two elements
/// \param a - ElemType
/// \param b - ElemType
void swap(ElemType *a, ElemType *b) {
    ElemType temp = *a;
    *a = *b;
    *b = temp;
}

/// Bubble sort for a list using a personalised compare function
/// \param the_list - MedicineList
/// \param cmp - int
/// \param reverse - int
void bubble_sort(MedicineList *the_list, int (*cmp)(const ElemType *, const ElemType *), int reverse) {
    int ok = 0;
    while (!ok) {
        ok = 1;
        for (int index = 0; index < size(the_list) - 1; index++) {
            if (cmp(&the_list->elems[index], &the_list->elems[index + 1]) * (reverse ? -1 : 1) > 0) {
                swap(&the_list->elems[index], &the_list->elems[index + 1]);
                ok = 0;
            }
        }
    }
}

/// Get all the medicine ordered ascending or descending
/// \param lst - MedicineList
/// \param sortType - int
/// \return An ordered copy of the list
MedicineList getAllMedicineOrdered(MedicineList *lst, int sortType) {
    MedicineList rez = createEmpty();
    for (int step = 0; step < size(lst); step++) {
        ElemType m = get(lst, step);
        add(&rez, m);
    }

    bubble_sort(&rez, cmp, sortType);
    return rez;
}

/// Get all the medicine with a higher stock than filter
/// \param lst - MedicineList
/// \param stockF - int
/// \return A filtered copy of the list
MedicineList getAllMedicineFilteredByStock(MedicineList *lst, int stockF) {
    MedicineList rez = createEmpty();
    for (int step = 0; step < size(lst); step++) {
        if (lst->elems[step].stock > stockF) {
            ElemType m = get(lst, step);
            add(&rez, m);
        }
    }
    return rez;
}

/// Get all the medicine whose name starts with a letter
/// \param lst - MedicineList
/// \param nameF - char
/// \return A filtered copy of the list
MedicineList getAllMedicineFilteredByName(MedicineList *lst, char *nameF) {
    MedicineList rez = createEmpty();
    for (int step = 0; step < size(lst); step++) {
        if (lst->elems[step].name[0] == nameF[0]) {
            ElemType m = get(lst, step);
            add(&rez, m);
        }
    }
    return rez;
}


//tests
void testAddMedicine() {
    MedicineList lst = createEmpty();

    int err = addMedicine(&lst, -1, "", 0, -2);
    assert(err == 1);

    err = addMedicine(&lst, 1, "paracetamol", 500, 20);
    assert(err == 0);
    destroy(&lst);
}

void testModifyMedicine() {
    MedicineList lst = createEmpty();
    addMedicine(&lst, 1, "paracetamol", 500, 20);

    int err = modifyMedicine(&lst, 1, "nurofen", 300);
    assert(err == 0);
    destroy(&lst);

    err = modifyMedicine(&lst, -1, "", 0);
    assert(err == 1);


}

void testDeleteStockMedicine() {
    MedicineList lst = createEmpty();
    addMedicine(&lst, 1, "paracetamol", 500, 20);

    int err = deleteStockMedicine(&lst, -1);
    assert(err == 1);

    err = deleteStockMedicine(&lst, 1);
    assert(err == 0);
    destroy(&lst);
}

void testGetAllMedicineOrdered() {
    MedicineList lst = createEmpty();
    addMedicine(&lst, 1, "paracetamol", 500, 20);
    addMedicine(&lst, 3, "aabc", 300, 2);
    addMedicine(&lst, 2, "aabc", 300, 4);


    MedicineList copy_list = getAllMedicineOrdered(&lst, 0);
    destroy_copy(&copy_list);
    destroy(&lst);
}

void testGetAllMedicineFiltered() {
    MedicineList lst = createEmpty();
    addMedicine(&lst, 1, "paracetamol", 500, 20);
    addMedicine(&lst, 3, "aabc", 300, 4);
    addMedicine(&lst, 2, "nurofen", 300, 2);

    MedicineList list = getAllMedicineFilteredByStock(&lst, 2);
    assert(size(&list) == 2);
    destroy_copy(&list);

    list = getAllMedicineFilteredByName(&lst, "a");
    assert(size(&list) == 1);
    destroy_copy(&list);

    destroy(&lst);
}