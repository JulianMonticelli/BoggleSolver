#pragma once
#include "DLBTrie.h"
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>

template <size_t columns, size_t rows>
void boggleSolve(char(&boggleBoard)[columns][rows], bool(&hasChecked)[columns][rows], char(&str)[columns*rows + 1], DLBTrie * dlb, int currentColumn, int currentRow, int markedChars);

void populateScrabbleDlb(DLBTrie * dlb);

template<size_t wordSize>
void addToList(char (&word)[wordSize]);