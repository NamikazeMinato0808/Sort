#pragma once
#ifndef _SORT_H
#define _SORT_H

#include <iostream>
#include "LinkedList.h"
using namespace std;

void fInsertionSort1(int* A, int n);
void fSelectionSort1(int* A, int n);

void fBubbleSort1(int* A, int n);
void fHeapSort1(int* A, int n);
void fQuickSort1(int* A, int l, int r);

void fMergeSort1(int* A, int l, int r);


void fInsertionSort2(node*& head, node*&tail);
void fSelectionSort2(node* head, node* tail);
void fBubbleSort2(node* head, node* tail);

void fMergeSort2(node*& head, node*& tail);
void fQuickSort2(node*& head, node*& tail);




#endif