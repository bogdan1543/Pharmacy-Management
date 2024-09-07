#include "medicine.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/// Create a medicine object
/// \param code - int
/// \param name - char
/// \param concentration - float
/// \param stock - int
/// \return Medicine
Medicine createMedicine(int code, char *name, float concentration, int stock) {
    Medicine m;
    size_t nrC = strlen(name) + 1;
    m.name = malloc(nrC * sizeof(char));
    m.code = code;
    strcpy(m.name, name);
    m.concentration = concentration;
    m.stock = stock;

    return m;
}

/// Deallocate memory from medicine
/// \param m - Medicine
void destroyMedicine(Medicine *m) {
    free(m->name);
    m->code = -1;
    m->stock = -1;
    m->concentration = -1;
}

/// Validate medicine
/// \param m - Medicine
/// \return 1 if valid or 0 if invalid
int validate(Medicine m) {
    if (m.code < 1)
        return 0;
    if (strlen(m.name) == 0)
        return 0;
    if (m.concentration <= 0)
        return 0;
    if (m.stock < 0)
        return 0;
    return 1;
}

/// Validate medicine code
/// \param code - int
/// \return 1 if valid or 0 if invalid
int validate_code(int code) {
    if (code < 1)
        return 0;
    return 1;
}


// tests
void testCreateDestroy() {
    Medicine m = createMedicine(1, "paracetamol", 500, 20);
    assert(m.code == 1);
    assert(strcmp(m.name, "paracetamol") == 0);
    assert(m.concentration == 500.0);
    assert(m.stock == 20);

    destroyMedicine(&m);
}

void testValidate() {
    Medicine m = createMedicine(1, "paracetamol", 500, 20);
    assert(validate(m) == 1);
    destroyMedicine(&m);
    m = createMedicine(-1, "", 0, -2);
    assert(validate(m) == 0);
    destroyMedicine(&m);
    m = createMedicine(1, "", 0, -2);
    assert(validate(m) == 0);
    destroyMedicine(&m);
    m = createMedicine(1, "abc", 0, -2);
    assert(validate(m) == 0);
    destroyMedicine(&m);
    m = createMedicine(1, "abc", 3, -2);
    assert(validate(m) == 0);
    destroyMedicine(&m);

}

void testValidate_code() {
    Medicine m = createMedicine(-1, "", 0, -2);
    assert(validate_code(m.code) == 0);
    m.code = 3;
    assert(validate_code(m.code) == 1);
    destroyMedicine(&m);
}