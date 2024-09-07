#ifndef LAB2_4_MEDICINE_H
#define LAB2_4_MEDICINE_H


/*
    Object Medicine definition
 */
typedef struct {
    int code;
    char *name;
    float concentration;
    int stock;
} Medicine;

/*
    Create a new medicine
 */
Medicine createMedicine(int code, char *name, float concentration, int stock);

/*
    Destroy medicine
 */
void destroyMedicine(Medicine *m);

/*
    Validate medicine
 */
int validate(Medicine m);

/*
    Validate a medicine code
 */
int validate_code(int code);


// tests
void testCreateDestroy();

void testValidate();

void testValidate_code();

#endif //LAB2_4_MEDICINE_H
