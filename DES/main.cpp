#include<iostream>
#include<string>
using namespace std;

struct Varchar{
	int length; //比特总长
	unsigned char *charstream; //字符流
};

int IPtable[] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

int invIPtable[] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};

int shiftTable[] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

int PC_1[] = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

int PC_2[] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

int Etable[] = {
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

int Ptable[] = {
	16, 7, 20, 21,
	29, 12, 28, 17,
	1, 15, 23, 26,
	5, 18, 31, 10,
	2, 8, 24, 14,
	32, 27, 3, 9,
	19, 13, 30, 6,
	22, 11, 4, 25
};

int Stable[32][16] = {
		{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 }, { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
		{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 }, { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
		{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 }, { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
		{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 }, { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },
		{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 }, { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
		{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 }, { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
		{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 }, { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
		{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 }, { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
		{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 }, { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
		{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 }, { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
		{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 }, { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
		{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 }, { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
		{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 }, { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
		{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 }, { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
		{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 }, { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
		{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 }, { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } 
};

static struct des_test_case {
	int num, mode; // mode 1 = encrypt
	unsigned char key[8], txt[8], out[8];
} cases[] = {
		{ 1, 1, { 0x10, 0x31, 0x6E, 0x02, 0x8C, 0x8F, 0x3B, 0x4A },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x82, 0xDC, 0xBA, 0xFB, 0xDE, 0xAB, 0x66, 0x02 } },
		{ 2, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x95, 0xF8, 0xA5, 0xE5, 0xDD, 0x31, 0xD9, 0x00 },
		{ 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 3, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0xDD, 0x7F, 0x12, 0x1C, 0xA5, 0x01, 0x56, 0x19 },
		{ 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 4, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x2E, 0x86, 0x53, 0x10, 0x4F, 0x38, 0x34, 0xEA },
		{ 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 5, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x4B, 0xD3, 0x88, 0xFF, 0x6C, 0xD8, 0x1D, 0x4F },
		{ 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 6, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x20, 0xB9, 0xE7, 0x67, 0xB2, 0xFB, 0x14, 0x56 },
		{ 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 7, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x55, 0x57, 0x93, 0x80, 0xD7, 0x71, 0x38, 0xEF },
		{ 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 8, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x6C, 0xC5, 0xDE, 0xFA, 0xAF, 0x04, 0x51, 0x2F },
		{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 9, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x0D, 0x9F, 0x27, 0x9B, 0xA5, 0xD8, 0x72, 0x60 },
		{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 10, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0xD9, 0x03, 0x1B, 0x02, 0x71, 0xBD, 0x5A, 0x0A },
		{ 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },

		{ 1, 0, { 0x10, 0x31, 0x6E, 0x02, 0x8C, 0x8F, 0x3B, 0x4A },
		{ 0x82, 0xDC, 0xBA, 0xFB, 0xDE, 0xAB, 0x66, 0x02 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 2, 0, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x95, 0xF8, 0xA5, 0xE5, 0xDD, 0x31, 0xD9, 0x00 } },
		{ 3, 0, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xDD, 0x7F, 0x12, 0x1C, 0xA5, 0x01, 0x56, 0x19 } },
		{ 4, 0, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x2E, 0x86, 0x53, 0x10, 0x4F, 0x38, 0x34, 0xEA } },
		{ 5, 0, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x4B, 0xD3, 0x88, 0xFF, 0x6C, 0xD8, 0x1D, 0x4F } },
		{ 6, 0, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x20, 0xB9, 0xE7, 0x67, 0xB2, 0xFB, 0x14, 0x56 } },
		{ 7, 0, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x55, 0x57, 0x93, 0x80, 0xD7, 0x71, 0x38, 0xEF } },
		{ 8, 0, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x6C, 0xC5, 0xDE, 0xFA, 0xAF, 0x04, 0x51, 0x2F } },
		{ 9, 0, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x0D, 0x9F, 0x27, 0x9B, 0xA5, 0xD8, 0x72, 0x60 } },
		{ 10, 0, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xD9, 0x03, 0x1B, 0x02, 0x71, 0xBD, 0x5A, 0x0A } }

};

des_test_case avalanche[] = {
		{ 1, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x82, 0xDC, 0xBA, 0xFB, 0xDE, 0xAB, 0x66, 0x02 } },
		{ 2, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 },
		{ 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 3, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03 },
		{ 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 4, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07 },
		{ 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 5, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F },
		{ 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 6, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F },
		{ 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 7, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F },
		{ 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 8, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F },
		{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 9, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF },
		{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },

};

des_test_case avalanche2[] = {
		{ 1, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
		{ 0x00, 0x04, 0x00, 0xF0, 0x00, 0x00, 0x10, 0x01 },
		{ 0x82, 0xDC, 0xBA, 0xFB, 0xDE, 0xAB, 0x66, 0x02 } },
		{ 2, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03 },
		{ 0x00, 0x04, 0x00, 0xF0, 0x00, 0x00, 0x10, 0x01 },
		{ 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 3, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x07 },
		{ 0x00, 0x04, 0x00, 0xF0, 0x00, 0x00, 0x10, 0x01 },
		{ 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 4, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0F },
		{ 0x00, 0x04, 0x00, 0xF0, 0x00, 0x00, 0x10, 0x01 },
		{ 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 5, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1F },
		{ 0x00, 0x04, 0x00, 0xF0, 0x00, 0x00, 0x10, 0x01 },
		{ 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 6, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x3F },
		{ 0x00, 0x04, 0x00, 0xF0, 0x00, 0x00, 0x10, 0x01 },
		{ 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 7, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7F },
		{ 0x00, 0x04, 0x00, 0xF0, 0x00, 0x00, 0x10, 0x01 },
		{ 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 8, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF },
		{ 0x00, 0x04, 0x00, 0xF0, 0x00, 0x00, 0x10, 0x01 },
		{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
		{ 9, 1, { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00 },
		{ 0x00, 0x04, 0x00, 0xF0, 0x00, 0x00, 0x10, 0x01 },
		{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },

};

Varchar myTest();
Varchar sampleTest();

void testAvalanche_changeTxt();
void testAvalanche_changeKey();
void testDES();

bool getBit(unsigned char *c, int r){
	unsigned char p = c[r / 8];
	bool b = (p >> (7 - r % 8)) & 1;
	return b;
}
void setBit(unsigned char *c, int r, bool b){
	unsigned char s = 1 << (7 - r % 8);
	if (b){
		c[r / 8] = c[r / 8] | s;
	}
	else{
		s = ~s;
		c[r / 8] = c[r / 8] & s;
	}
	return;
}

Varchar initIP(Varchar);
Varchar invIP(Varchar);

Varchar roundEncode(Varchar, Varchar, int);
Varchar extend(Varchar);
Varchar select(Varchar);
Varchar substitute(Varchar);
Varchar XOR(Varchar, Varchar);

Varchar keyGenerator(Varchar, int);

Varchar substituteSelect(Varchar, bool);//bool值0代表PC-1，1代表PC-2
Varchar leftShift(Varchar, int);

Varchar LRexchange(Varchar);

Varchar ECB_DESencode(Varchar, Varchar);
Varchar ECB_DESdecode(Varchar, Varchar);
Varchar _DESencode(Varchar, Varchar);
Varchar _DESdecode(Varchar, Varchar);

void printVarchar(Varchar);



int main(){
	
	//testDES();
	//testAvalanche_changeTxt();
	testAvalanche_changeKey();

	system("pause");
	return 0;
}

void testAvalanche_changeTxt(){
	cout << "测试雪崩效应↓" << endl;
	Varchar k;
	k.length = 8;
	Varchar c_list[9];
	for (int i = 0; i < 9; i++){
		bool en = avalanche[i].mode;
		
		printf("第%d次测试：\n", avalanche[i].num);
		if (!en){
			Varchar c;
			cout << "解密密文" << endl;
			c.length = 8;
			c.charstream = (unsigned char *)avalanche[i].txt;
			k.charstream = (unsigned char *)avalanche[i].key;
			Varchar m = ECB_DESdecode(c, k);
			cout << "解密后的结果：" << endl;
			printVarchar(m);
		}
		else{
			Varchar p;
			cout << "加密明文" << endl;
			p.length = 8;
			p.charstream = (unsigned char *)avalanche[i].txt;
			k.charstream = (unsigned char *)avalanche[i].key;
			Varchar c = ECB_DESencode(p, k);
			cout << "加密后的结果：" << endl;;
			printVarchar(c);
			c_list[i] = c;
		}
	}
	double sum = 0;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < c_list[i].length * 8; j++){
			if (getBit(c_list[i].charstream, j) == getBit(c_list[i+1].charstream, j))
				sum++;
		}
	}

	for (int i = 0; i < 9; i++){
		c_list[i].charstream = NULL;
	}

	cout << "平均位数改变：" << sum / 8 << endl;

}

void testAvalanche_changeKey(){
	cout << "测试雪崩效应↓" << endl;
	Varchar k;
	k.length = 8;
	Varchar c_list[9];
	for (int i = 0; i < 9; i++){
		bool en = avalanche2[i].mode;

		printf("第%d次测试：\n", avalanche2[i].num);
		if (!en){
			Varchar c;
			cout << "解密密文" << endl;
			c.length = 8;
			c.charstream = (unsigned char *)avalanche2[i].txt;
			k.charstream = (unsigned char *)avalanche2[i].key;
			Varchar m = ECB_DESdecode(c, k);
			cout << "解密后的结果：" << endl;
			printVarchar(m);
		}
		else{
			Varchar p;
			cout << "加密明文" << endl;
			p.length = 8;
			p.charstream = (unsigned char *)avalanche2[i].txt;
			k.charstream = (unsigned char *)avalanche2[i].key;
			Varchar c = ECB_DESencode(p, k);
			cout << "加密后的结果：" << endl;;
			printVarchar(c);
			c_list[i] = c;
		}
	}
	double sum = 0;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < c_list[i].length * 8; j++){
			if (getBit(c_list[i].charstream, j) == getBit(c_list[i + 1].charstream, j))
				sum++;
		}
	}

	for (int i = 0; i < 9; i++){
		c_list[i].charstream = NULL;
	}

	cout << "平均位数改变：" << sum / 8 << endl;
}

void testDES(){
	cout << "测试DES加密解密正确性↓" << endl;
	Varchar k;
	k.length = 8;
	for (int i = 0; i < 20; i++){
		bool en = cases[i].mode;
		printf("第%d次测试：\n", cases[i].num);
		if (!en){
			Varchar c;
			cout << "解密密文" << endl;
			c.length = 8;
			c.charstream = (unsigned char *)cases[i].txt;
			k.charstream = (unsigned char *)cases[i].key;
			Varchar m = ECB_DESdecode(c, k);
			cout << "解密后的结果：" << endl;
			printVarchar(m);
		}
		else{
			Varchar p;
			cout << "加密明文" << endl;
			p.length = 8;
			p.charstream = (unsigned char *)cases[i].txt;
			k.charstream = (unsigned char *)cases[i].key;
			Varchar c = ECB_DESencode(p, k);
			cout << "加密后的结果：" << endl;;
			printVarchar(c);
		}

	}
}

Varchar myTest(){
	cout << "输入想要加密的文本：" << endl;
	char str[200];
	cin.getline(str, 200);
	int len = strlen(str);
	Varchar input;
	input.length = len;
	input.charstream = (unsigned char*)malloc(len);
	memcpy(input.charstream, str, len);
	return input;
}

Varchar sampleTest(){
	Varchar input;
	input.length = 8;
	input.charstream = (unsigned char *)malloc(input.length);
	unsigned char ct[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	memcpy(input.charstream, ct, input.length);
	return input;
}

Varchar initIP(Varchar p){
	unsigned char *pot = p.charstream, *temp = (unsigned char *)malloc(p.length);
	memset(temp, 0, p.length);
	for (int i = 0; i < p.length * 8; i++){
		setBit(temp, i, getBit(pot, IPtable[i] - 1));
	}
	memcpy(pot, temp, p.length);
	free(temp);
	return p;
}

Varchar invIP(Varchar e){
	unsigned char *pot = e.charstream, *temp = (unsigned char *)malloc(e.length);
	memset(temp, 0, e.length);
	for (int i = 0; i < e.length * 8; i++){
		setBit(temp, i, getBit(pot, invIPtable[i] - 1));
	}
	memcpy(pot, temp, e.length);
	free(temp);
	return e;
}

Varchar roundEncode(Varchar e, Varchar k, int r){
	Varchar Le, Re;
	Le.length = Re.length = e.length / 2;
	Le.charstream = e.charstream;
	Re.charstream = e.charstream + Le.length;

	Varchar t1;
	t1.length = Re.length;
	t1.charstream = (unsigned char *)malloc(t1.length);
	memcpy(t1.charstream, Re.charstream, t1.length);


	t1 = extend(t1);
	t1 = XOR(t1, k);
	t1 = select(t1);
	t1 = substitute(t1); 
	Le = XOR(Le, t1);

	LRexchange(e);
	return e;
}

Varchar extend(Varchar p){
	p.length = 6;
	unsigned char *t = (unsigned char*)malloc(p.length), *pot=(unsigned char*)p.charstream;

	memset(t, 0, p.length);
	for (int i = 0; i < p.length * 8; i++){
		setBit(t, i, getBit(pot, Etable[i] - 1));
	}
	p.charstream = (unsigned char*)t;
	return p;
}

Varchar XOR(Varchar A, Varchar B){
	unsigned char *potA = A.charstream, *potB = B.charstream;
	for (int i = 0; i < A.length; i++){
		potA[i] = potA[i] ^ potB[i];
	}
	return A;
}

Varchar select(Varchar p){
	unsigned char *pot = p.charstream;
	p.length = 4;
	unsigned char *t = (unsigned char*)malloc(p.length), *temp = t;
	memset(t, 0, p.length);
	for (int i = 0; i < 8; i++){
		int row = 0, column = 0;
		row = (int(getBit(pot, 0 + i * 6)) << 1) + int(getBit(pot, 5 + i * 6));
		column = (int(getBit(pot, 1 + i * 6)) << 3) + (int(getBit(pot, 2 + i * 6)) << 2) + (int(getBit(pot, 3 + i * 6)) << 1) + (int(getBit(pot, 4 + i * 6)));
		int out = Stable[(i << 2) + row][column];
		setBit(temp, 0 + i * 4, out >> 3);
		setBit(temp, 1 + i * 4, (out & 4) >> 2);
		setBit(temp, 2 + i * 4, (out & 2) >> 1);
		setBit(temp, 3 + i * 4, out & 1);
	}
	p.charstream = (unsigned char*)t;
	return p;
}

Varchar substitute(Varchar p){
	unsigned char *pot = p.charstream, *temp = (unsigned char *)malloc(p.length);
	memset(temp, 0, p.length);
	for (int i = 0; i < p.length * 8; i++){
		setBit(temp, i, getBit(pot, Ptable[i] - 1));
	}
	memcpy(pot, temp, p.length);
	free(temp);
	return p;
}

Varchar substituteSelect(Varchar k, bool which){
	unsigned char *pot = (unsigned char *)k.charstream, *temp = (unsigned char *)malloc(k.length);
	memset(temp, 0, k.length);
	Varchar rt;
	if (which){
		for (int i = 0; i < k.length * 8; i++){
			setBit(temp, i, getBit(pot, PC_2[i] - 1));
		}
		rt.length = 6;
	}
	else{
		for (int i = 0; i < k.length * 8; i++){
			setBit(temp, i, getBit(pot, PC_1[i] - 1));
		}
		rt.length = 7;
	}
	rt.charstream = temp;
	return rt;
}

Varchar leftShift(Varchar k, int r){
	int shift = shiftTable[r - 1];
	unsigned char *temp = (unsigned char*)malloc(k.length), *pot=(unsigned char*)k.charstream;
	memset(temp, 0, k.length);
	int i;
	for (i = 0; i < 28 - shift; i++){
		setBit(temp, i, getBit(pot, i + shift));
	}
	for (int j = 0; j < shift; j++){
		setBit(temp, i++, getBit(pot, j));
	}
	for (i = 28; i < 56 - shift; i++){
		setBit(temp, i, getBit(pot, i + shift));
	}
	for (int j = 28; j < 28 + shift; j++){
		setBit(temp, i++, getBit(pot, j));
	}
	memcpy(k.charstream, temp, k.length);
	return k;
}

Varchar ECB_DESencode(Varchar p, Varchar k){
	unsigned char *pos = p.charstream;
	for (int i = 0; i < p.length; i += 8){
		Varchar temp;
		temp.length = 8;
		temp.charstream = pos;
		pos += 8;
		_DESencode(temp, k);
	}
	return p;
}

Varchar ECB_DESdecode(Varchar c, Varchar k){
	unsigned char *pos = c.charstream;
	for (int i = 0; i < c.length; i += 8){
		Varchar temp;
		temp.length = 8;
		temp.charstream = pos;
		pos += 8;
		_DESdecode(temp, k);
	}
	return c;
}

void printVarchar(Varchar p){
	cout << "比特流长度为：" << p.length * 8 << endl;
	
	/*
	cout << "ASCII码查看加密结果：" << endl;
	for (int i = 0; i < p.length; i++){
		cout << p.charstream[i];
	}
	cout << "---------------" << endl;
	*/
	
	cout << "二进制查看加密结果：" << endl;
	unsigned char *pot = p.charstream;
	for (int i = 0; i < p.length * 8; i++){
		if (i % 8 == 0) cout << " ";
		cout << getBit(pot, i);
		
	}
	cout << endl;
	cout << "------------------------------------------------" << endl;

	cout << "十六进制查看加密结果：" << endl;
	for (int i = 0; i < p.length; i++){
		int hexBit = 0;
		for (int j = i * 8; j < i * 8 + 8; j++){
			hexBit = hexBit << 1;
			hexBit |= getBit(pot, j);
		}
		printf("0X%02x ", hexBit);
	}
	cout << endl;
	cout << "################################################" << endl;
	cout << endl;
}

Varchar _DESencode(Varchar p, Varchar k){
	p = initIP(p);
	k = substituteSelect(k, 0);
	k.length = 7;
	Varchar sk;
	for (int i = 1; i <= 16; i++){
		sk = keyGenerator(k, i);
		p = roundEncode(p, sk, i);
	}
	p = LRexchange(p);
	p = invIP(p);
	return p;
}

Varchar _DESdecode(Varchar p, Varchar k){
	p = initIP(p);
	k = substituteSelect(k, 0);
	k.length = 7;
	Varchar keys[16], sk;
	for (int i = 0; i < 16; i++){
		keys[i] = keyGenerator(k, i + 1);
	}
	for (int i = 1; i <= 16; i++){
		sk = keys[16 - i];
		p = roundEncode(p, sk, i);
	}
	p = LRexchange(p);
	p = invIP(p);
	return p;
}

Varchar LRexchange(Varchar p){
	int len = p.length / 2;
	unsigned char *temp = (unsigned char*)malloc(len);
	memset(temp, 0, len);
	memcpy(temp, p.charstream, len);
	memcpy(p.charstream, p.charstream + len, len);
	memcpy(p.charstream + len, temp, len);
	free(temp);
	return p;
}

Varchar keyGenerator(Varchar k, int r){
	leftShift(k, r);
	Varchar ik;
	ik = substituteSelect(k, 1);
	return ik;
}

