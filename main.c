#include "medicine.h"
#include "repository_medicine.h"
#include "service_medicine.h"

#include <stdio.h>
#include <stdlib.h>


/// Add a medicine to the list
/// \param lst - MedicineList
void uiAddMedicine(MedicineList *lst) {
    printf("Code:");
    int code;
    scanf("%d", &code);
    printf("Name:");
    char name[30];
    scanf("%s", name);
    printf("Concentration:");
    float concentration;
    scanf("%f", &concentration);
    printf("Stock:");
    int stock;
    scanf("%d", &stock);
    int error = addMedicine(lst, code, name, concentration, stock);
    if (error != 0) {
        printf("Invalid medicine.\n");
    }
}

/// Modify a medicine name and concentration
/// \param lst - MedicineList
void uiModifyMedicine(MedicineList *lst) {
    printf("Code:");
    int code;
    scanf("%d", &code);
    printf("Name:");
    char name[20];
    scanf("%s", name);
    printf("Concentration:");
    float concentration;
    scanf("%f", &concentration);
    int error = modifyMedicine(lst, code, name, concentration);
    if (error != 0) {
        printf("Invalid medicine.\n");
    }
}

/// Delete a medicine stock
/// \param lst - MedicineList
void uiDeleteStockMedicine(MedicineList *lst) {
    printf("Code:");
    int code;
    scanf("%d", &code);
    int error = deleteStockMedicine(lst, code);
    if (error != 0) {
        printf("Invalid medicine.\n");
    }
}

/// Print all the medicine
/// \param lst - MedicineList
void uiPrintAllMedicine(MedicineList *lst) {
    for (int i = 0; i < size(lst); i++) {
        ElemType m = get(lst, i);
        printf("(%d , %s , %f , %d)\n", m.code, m.name, m.concentration, m.stock);
    }
}

/// Print all the medicine ordered ascending or descending
/// \param lst - MedicineList
void uiPrintAllMedicineOrdered(MedicineList *lst) {
    printf("0 - Ascending\n1 - Descending\nCommand:");
    int sortType;
    scanf("%d", &sortType);
    MedicineList copy_list = getAllMedicineOrdered(lst, sortType);
    for (int i = 0; i < size(&copy_list); i++) {
        ElemType m = get(&copy_list, i);
        printf("(%d , %s , %f , %d)\n", m.code, m.name, m.concentration, m.stock);
    }
    destroy_copy(&copy_list);
}

/// Print all the medicine that have the stock higher
/// \param lst - MedicineList
void uiPrintAllMedicineFilteredByStock(MedicineList *lst) {
    printf("Stocks greater than:");
    int stockF;
    scanf("%d", &stockF);
    MedicineList lstOrd = getAllMedicineFilteredByStock(lst, stockF);
    for (int i = 0; i < size(&lstOrd); i++) {
        ElemType m = get(&lstOrd, i);
        printf("(%d , %s , %f , %d)\n", m.code, m.name, m.concentration, m.stock);
    }
    destroy_copy(&lstOrd);
}

/// Print all the medicine that starts with a certain letter
/// \param lst - MedicineList
void uiPrintAllMedicineFilteredByName(MedicineList *lst) {
    printf("Medicine that starts with:");
    char nameF[1];
    scanf("%s", nameF);
    MedicineList lstOrd = getAllMedicineFilteredByName(lst, nameF);
    for (int i = 0; i < size(&lstOrd); i++) {
        ElemType m = get(&lstOrd, i);
        printf("(%d , %s , %f , %d)\n", m.code, m.name, m.concentration, m.stock);
    }
    destroy_copy(&lstOrd);
}


/// Console run
void run() {
    MedicineList lst = createEmpty();
    int running = 1;
    while (running) {
        printf("1 Add\n"
               "2 Modify\n"
               "3 Delete stock\n"
               "4 Print medicine\n"
               "5 Ordered\n"
               "6 Filtered - greater stocks\n"
               "7 Filtered - starts with letter\n"
               "0 Exit\n"
               "Command:");
        int cmd = 0;
        scanf("%d", &cmd);
        switch (cmd) {
            case 1:
                uiAddMedicine(&lst);
                break;
            case 2:
                uiModifyMedicine(&lst);
                break;
            case 3:
                uiDeleteStockMedicine(&lst);
                break;
            case 4:
                uiPrintAllMedicine(&lst);
                break;
            case 5:
                uiPrintAllMedicineOrdered(&lst);
                break;
            case 6:
                uiPrintAllMedicineFilteredByStock(&lst);
                break;
            case 7:
                uiPrintAllMedicineFilteredByName(&lst);
                break;
            case 0:
                running = 0;
                break;
            default:
                printf("Invalid command!!!\n");
        }
    }
    destroy(&lst);
}

//tests
void testAll() {
    testCreateDestroy();
    testCreateList();
    testAdd();
    testModify();
    testAddMedicine();
    testModifyMedicine();
    testDeleteStock();
    testDeleteStockMedicine();
    testValidate();
    testValidate_code();
    testUtilsRepo();
    testGetAllMedicineOrdered();
    testGetAllMedicineFiltered();
}

int main() {
    //testAll();
    run();
    return 0;
}