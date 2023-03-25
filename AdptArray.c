#include "AdptArray.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct AdptArray_
{
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;

    int size;
    PElement *elements;
    int createdSucc;

};


void init(COPY_FUNC c, DEL_FUNC d, PRINT_FUNC p, PAdptArray pArray){

    pArray->copy_func = c;
    pArray->del_func = d;
    pArray->print_func = p;
    pArray->size = 0;
    pArray->elements[0] = NULL;
    pArray->createdSucc = 0;
}


PAdptArray CreateAdptArray(COPY_FUNC a, DEL_FUNC b,PRINT_FUNC c){

    PAdptArray pArray = (PAdptArray)malloc(sizeof(struct AdptArray_)); 

    if(!pArray){
        pArray->createdSucc = 0;
        return NULL;
    }

    pArray->elements = (PElement)malloc(sizeof(PElement));

    if(!pArray->elements){
        pArray->createdSucc = 0;
        return NULL;
    }

    pArray->createdSucc = 1;
    init(a ,b ,c ,pArray);
    return pArray;
}

void DeleteAdptArray(PAdptArray pArray){
    
    if(pArray->size > 0){
        for(int i = 0; i < pArray->size; ++i){
            if(pArray->elements[i] !=NULL){
                pArray->del_func(pArray->elements[i]);
            }
        }
        free(pArray);
    }
    
}

Result SetAdptArrayAt(PAdptArray pArray, int i, PElement e){

    if(pArray->size < i){
        int sizeToAllocation = i - pArray->size + 1;

        PElement* newElement = (PElement*)realloc(pArray->elements, sizeToAllocation * (sizeof(PElement))); 

        if(i - pArray->size >= 1){
            for(int index = pArray->size; index < i; ++index){
                newElement[i] = NULL;
            }
        }
        pArray->elements = newElement;
        pArray->size = pArray->size + sizeToAllocation;
    }

    if(pArray->elements[i] != NULL){
        pArray->del_func(pArray->elements[i]);
    }

    pArray->elements[i] = pArray->copy_func(e);

    if(pArray->elements[i] == e){
        return SUCCESS;
    }

    return FAIL;
}

PElement GetAdptArrayAt(PAdptArray pArray, int i){

    if(pArray->size <= i || i < 0){
        return NULL;
    }

    if(pArray->elements[i] != NULL){
       PElement e_copy = pArray->copy_func(pArray->elements[i]);
       return e_copy;
    }

    return NULL;
}

int GetAdptArraySize(PAdptArray pArray){

    return pArray->size;
}

void PrintDB(PAdptArray pArray){

    for(int i = 0; i < pArray->size; ++i){
        if(pArray->elements[i] == NULL) continue;
        pArray->print_func(pArray->elements[i]);
    }
}