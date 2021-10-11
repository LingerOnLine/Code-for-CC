#ifndef __INT256_H__
#define __INT256_H__

//声明：头文件注释为抽象概念，具体注释请转至函数定义，如有不明之处可尝试联系编者.     Email ：lingeronline@126.com
//开个玩笑：本程序为 INT256 , 可完善，可优美，可降级使用，也可升级使用，更可无止境进化，如若参透本程序，汝将习得宇宙终级奥密，最终**（这是一个很小很小很小的秘密）. 
//Make a joy ： This program is named INT256 , it can improve, and grave, and return or update, and even to the endless evolution, if you see the all meanings, you will get the biggest secret of the universe...

/*
* 一个储存除法结果的结构.
*/
struct My256div_t {
	unsigned int quot[8];  //商.
	unsigned int rem[8];   //余.
};
typedef struct My256div_t my256div_t;
typedef unsigned int bint256[8];       //INT256
typedef unsigned int ubint256[8];      //INT256 和上面一行的本质上没有区别，要看怎么用, 本来想用来作无符号数据的，可能要到编译层面才能实现这一想法.

extern const char INT256C_MAX[79];     //字符表示的有符号INT256最大值.
extern const char INT256C_MIN[79];	   //字符表示的有符号INT256最小值.
extern const char UINT256C_MAX[79];    //字符表示的无符号INT256最大值.

extern const unsigned int MYUINT256_MAX[8];  //整型数组表示的（也可理解成二进制形式的）无符号 INT256 最大值.
extern const unsigned int MYINT256_MAX[8];   //整型数组表示的（也可理解成二进制形式的）有符号 INT256 最大值.
extern const unsigned int MYINT256_MIN[8];   //整型数组表示的（也可理解成二进制形式的）有符号 INT256 最小值.
extern const unsigned int MYINT256_ZERO[8];  //整型数组表示的（也可理解成二进制形式的）INT256 零值.
extern const unsigned int MYINT256__1[8];    //整型数组表示的（也可理解成二进制形式的) 有符号 INT256 值 -1 .
extern const unsigned int MYINT256_1[8];     //整型数组表示的（也可理解成二进制形式的) INT256 值 1 .

//======================================================================================================================================================各种转换
/*
* 一个将以字符信息表示的十进制的数据转化为以一个整形数组表示的二进制数据的函数，返回值为结果指针.
*/
extern unsigned int* CV256(char* allD, unsigned int* result);

/*
* 一个将以一个整形数组表示的二进制数据转化为一个以长长整形（相当于十进制分成数段表示）表示的数据的内部函数，返回值为结果指针.
*/
static unsigned long long* binToLL256(const unsigned int* value1, unsigned long long* result);

/*
* 一个将一个以长长整形（相当于十进制分成数段表示）表示的数据转化为以一个整形数组表示的二进制数据的内部函数，返回值为结果指针.
*/
static unsigned int* LLTobin256(unsigned long long* value1, unsigned int* result);

/*
* 一个将（符号省略，分五段）正数转化为一个以一个整形数组表示的二进制数据的内部函数，返回值为结果指针.
*/
static unsigned int* DV256(unsigned long long n4, unsigned long long n3, unsigned long long n2, unsigned long long n1, unsigned long long n0, unsigned int* result);

/*
* 一个将（符号省略，分五段）负数转化为一个以一个整形数组表示的二进制数据的内部函数，返回值为结果指针.
*/
static unsigned int* D_V256(unsigned long long n4, unsigned long long n3, unsigned long long n2, unsigned long long n1, unsigned long long n0, unsigned int* result);

//======================================================================================================================================================各种打印

/*
* 以有符号形式打印一个二进制数据，并将结果储存在一个字符数组中，返回值为结果指针. 
*/
extern char* printV256(const unsigned int* value1, char* result79);

/*
* 以无符号形式打印一个二进制数据，并将结果储存在一个字符数组中，返回值为结果指针.
*/
extern char* printVU256(const unsigned int* value1, char* result79);

/*
* 以二进制形式打印一个二进制数据，并将结果储存在一个字符数组中，返回值为结果指针.
*/
extern char* showBin256(const unsigned int* value1, char* result257);

//======================================================================================================================================================各种复制

/*
* 复制一个数据，返回值为结果指针.
*/
extern unsigned int* copyV256(unsigned int* value1, const unsigned int* value2);

/*
* 将一个整形数据复制成INT256，返回值为结果指针.
*/
extern unsigned int* copyVint256(unsigned int* value1, int value2);

/*
* 将一个长长整形数据复制成INT256，返回值为结果指针.
*/
extern unsigned int* copyVLL256(unsigned int* value1, long long value2);

//======================================================================================================================================================加减乘除取余


/*
* 将两个数据相加，并储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* add256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* 将一个数据减去一个数据，并储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* sub256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* 将两个数据相乘，并储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* mul256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* 将一个数据（无符号）除以一个数据（无符号），并将商储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* divU256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* 将一个数据（有符号）除以一个数据（有符号），并将商储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* div256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* 将一个数据（无符号）除以一个数据（无符号），并将余储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* modU256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* 将一个数据（有符号）除以一个数据（有符号），并将余储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* mod256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* 将一个数据（无符号）除以一个数据（无符号），并将结果储存在一个结构中，返回值为结果指针.
*/
extern my256div_t* divUAll256(const unsigned int* value1, const unsigned int* value2, my256div_t* result);

/*
* 将一个数据（有符号）除以一个数据（有符号），并将结果储存在一个结构中，返回值为结果指针.
*/
extern my256div_t* divAll256(const unsigned int* value1, const unsigned int* value2, my256div_t* result);

//======================================================================================================================================================位操作


/*
* 将一个数据以二进制形式按位取反，并储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* r256(const unsigned int* value1, unsigned int* result);

/*
* 将两个数据以二进制形式按位与，并储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* and256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* 将两个数据以二进制形式按位或，并储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* or256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* 将两个数据以二进制形式按位异或，并储存在一个结果中，返回值为结果指针.
*/
extern unsigned int* xor256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

//======================================================================================================================================================自操作


/*
* 将一个数按位与另一个数，并将结果储存在第一个数中，返回值为结果指针.
*/
extern unsigned int* iand256(unsigned int* self, const unsigned int* value2);

/*
* 将一个数按位或另一个数，并将结果储存在第一个数中，返回值为结果指针.
*/
extern unsigned int* ior256(unsigned int* self, const unsigned int* value2);

/*
* 将一个数按位异或另一个数，并将结果储存在第一个数中，返回值为结果指针.
*/
extern unsigned int* ixor256(unsigned int* self, const unsigned int* value2);

/*
* 将一个数按位取反，并将结果储存在自身中，返回值为结果指针.
*/
extern unsigned int* ir256(unsigned int* value1);

/*
* 自减，相当于--，返回值为结果指针.
*/
extern unsigned int* iss256(unsigned int* value1);

/*
* 自增，相当于++，返回值为结果指针.
*/
extern unsigned int* ipp256(unsigned int* value1);

/*
* 两数相加，并将结果储存在第一个数中， 相当于 += ，返回值为结果指针.
*/
extern unsigned int* ipa256(unsigned int* self, const unsigned int* value1);

/*
* 一个数减去一个数，并将结果储存在第一个数中， 相当于 -= ，返回值为结果指针.
*/
extern unsigned int* isa256(unsigned int* self, const unsigned int* value1);

/*
* 两数相乘，并将结果储存在第一个数中，相当于 *= ，返回值为结果指针.
*/
extern unsigned int* ima256(unsigned int* self, const unsigned int* value1);

/*
* 一个数（无符号）除以一个数（无符号），并将商储存在第一个数中，相当于 /= ，返回值为结果指针. 
*/
extern unsigned int* idaU256(unsigned int* self, const unsigned int* value1);

/*
* 一个数（有符号）除以一个数（有符号），并将商储存在第一个数中，相当于 /= ，返回值为结果指针.
*/
extern unsigned int* ida256(unsigned int* self, const unsigned int* value1);

/*
* 一个数（无符号）除以一个数（无符号），并将余储存在第一个数中，相当于 %= ，返回值为结果指针.
*/
extern unsigned int* imodaU256(unsigned int* self, const unsigned int* value1);

/*
* 一个数（有符号）除以一个数（有符号），并将余储存在第一个数中，相当于 %= ，返回值为结果指针.
*/
extern unsigned int* imoda256(unsigned int* self, const unsigned int* value1);

/*
* 将一个数据以二进制形式左移n位，右边出现的空位取0 ，返回值为结果指针.
*/
extern unsigned int* ilsn256(unsigned int* self, int n);

/*
* 将一个数据以二进制形式右移n位，右边出现的空位取值规则为：以有符号视角，若最高位为负值，则取1 ，否则取0 ，返回值为结果指针.
*/
extern unsigned int* irsn256(unsigned int* self, int n);

/*
* 将一个数据以二进制形式右移n位，右边出现的空位取0 ，返回值为结果指针.
*/
extern unsigned int* irsnU256(unsigned int* self, int n);

//======================================================================================================================================================左右移


/*
* 将一个数据以二进制形式左移n位，右边出现的空位取0 ，并将结果储存在结果中，返回值为结果指针.
*/
extern unsigned int* lefts256(const unsigned int* value, int n, unsigned int* result);

/*
* 将一个数据以二进制形式右移n位，右边出现的空位取值规则为：以有符号视角，若最高位为负值，则取1 ，否则取0 ，并将结果储存在结果中，返回值为结果指针.
*/
extern unsigned int* rights256(const unsigned int* value, int n, unsigned int* result);

/*
* 将一个数据以二进制形式右移n位，右边出现的空位取0 ，并将结果储存在结果中，返回值为结果指针.
*/
extern unsigned int* rightsU256(const unsigned int* value, int n, unsigned int* result);

//======================================================================================================================================================比较


/*
* 以有符号视角比较两个数据，两数相等返回 0 ，value1 < value2 返回 -1 ，value1 > value2 返回 1.
*/
extern int cmp256(const unsigned int* value1, const unsigned int* value2);

/*
* 以无符号视角比较两个数据，两数相等返回 0 ，value1 < value2 返回 -1 ，value1 > value2 返回 1.
*/
extern int cmpU256(const unsigned int* value1, const unsigned int* value2);

#endif // !__INT256_H__

//======================================================================================================================================================
