#ifndef _SERVICE_MEDICINE_H_
#define _SERVICE_MEDICINE_H_


#include "repository_medicine.h"

/*
    Add a medicine in pharmacy
 */
int addMedicine(MedicineList *lst, int code, char *name, float concentration, int stock);

/*
    Modify a medicine name/concentration in pharmacy
 */
int modifyMedicine(MedicineList *lst, int code, char *name, float concentration);

/*
    Delete a medicine stock from pharmacy
 */
int deleteStockMedicine(MedicineList *lst, int code);

/*
    Get all the medicine ordered ascending or descending
 */
MedicineList getAllMedicineOrdered(MedicineList *lst, int sortType);

/*
    Get all the medicine with a higher stock than filter
 */
MedicineList getAllMedicineFilteredByStock(MedicineList *lst, int stockF);

/*
    Get all the medicine whose name starts with a letter
 */
MedicineList getAllMedicineFilteredByName(MedicineList *lst, char *nameF);

//tests
void testAddMedicine();

void testModifyMedicine();

void testDeleteStockMedicine();

void testGetAllMedicineOrdered();

void testGetAllMedicineFiltered();

#endif