#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include"int256.h"

const char INT256C_MAX[79] = "57896044618658097711785492504343953926634992332820282019728792003956564819967";       //有符号INT256最大值.
const char INT256C_MIN[79] = "-57896044618658097711785492504343953926634992332820282019728792003956564819968";      //有符号INT256最小值.
const char UINT256C_MAX[79] = "115792089237316195423570985008687907853269984665640564039457584007913129639935";     //无符号INT256最大值.

const unsigned int MYUINT256_MAX[8] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff }; //整形数组表示的无符号 INT256 最大值.
const unsigned int MYINT256_MAX[8] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 2147483647U }; //整形数组表示的有符号 INT256 最大值.
const unsigned int MYINT256_MIN[8] = { 0, 0, 0, 0, 0, 0, 0, 2147483648U };                                                                //整形数组表示的无符号 INT256 最小值.
const unsigned int MYINT256_ZERO[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };                                                                         //整形数组表示的 INT256 零值.
const unsigned int MYINT256__1[8] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff };   //整形数组表示的有符号 INT256 值 -1 .
const unsigned int MYINT256_1[8] = { 1,0,0,0,0,0,0,0 };																					  //整形数组表示的有符号 INT256 值 1 .
const unsigned int pp = 0xffffffff;                      //有可能是 -1 ，也有可能是无符号整形最大值. 
const unsigned int pfd = 0x80000000;                     //10000000,00000000,00000000,00000000（二进制）   用于与某个整形数据按位与，确定其最高位是否为1 .
const unsigned long long ppp = 0xffffffffffffffff;       //UINT_MAX
const unsigned long long pv = 1000000000000000000U;      //可以这么说，此数据用于1000000000000000000（十进制字符表示）（好像也可以读作仟仟兆，反正我知道它有多大）进制计算，逢仟仟兆进一 .

static unsigned long long* binToLL256(const unsigned int* value1, unsigned long long* result) {

	int i = 0;
	unsigned int tem1[8] = { value1[0],value1[1],value1[2],value1[3],value1[4],value1[5],value1[6],value1[7] };  //复制被操作数的值. 
	unsigned int tem2[8] = { 0,0,0,0,0,0,0,0 };																	 //准备用于储存对应的 pv 值. 
	*((unsigned long long*)(&tem2[0])) = pv;
	i = 4;											//115792, 089237316195423570, 985008687907853269, 984665640564039457, 584007913129639935	五段
	int k;
	my256div_t tem;
	for (; i >= 0; i--) {
		divUAll256(tem1, tem2, &tem);									//辗转除以取余. 
		result[i] = *((unsigned long long*)(&(tem.rem[0])));			//储存得到的余数. 
		for (k = 0; k < 8; k++) tem1[k] = (tem.quot)[k];				//重新设置被除数. 有待优化. 
	}
	return result;
}

static unsigned int* LLTobin256(unsigned long long* value1, unsigned int* result) {

	int i = 0;
	for (; i < 8; i += 2) *((long long*)(&result[i])) = 0;    //结果置零. 
	i = 3;													  //循环处理unsigned long long 高四位(相对的，你看到的低也可能是一种高)，首位无需循环，直接处理. 
	unsigned int tem2[8] = { 0,0,0,0,0,0,0,0 };
	*((unsigned long long*)(&tem2[0])) = pv;
	unsigned int tem3[8] = { 0,0,0,0,0,0,0,0 };
	*((unsigned long long*)(&tem3[0])) = pv;
	unsigned int tss[8] = { 0,0,0,0,0,0,0,0 };
	*((unsigned long long*)(&tss[0])) = value1[4];
	ipa256(result, tss);
	unsigned int tem4[8];
	for (; i >= 0; i--) {
		*((unsigned long long*)(&tss[0])) = value1[i];
		ipa256(result, mul256(tem2, tss, tem4));             //提示：value1[4] + value1[3] * pv + value1[2] * pv 的 2 次方...
		ima256(tem2, tem3);
	}
	return result;
}

unsigned int* DV256(unsigned long long n4, unsigned long long n3, unsigned long long n2, unsigned long long n1, unsigned long long n0, unsigned int* result) {
	return LLTobin256((unsigned long long[5]) { n4, n3, n2, n1, n0 }, result);          //我猜应该不用我解释了吧. 
}
unsigned int* D_V256(unsigned long long n4, unsigned long long n3, unsigned long long n2, unsigned long long n1, unsigned long long n0, unsigned int* result) {
	int i = 0;
	LLTobin256((unsigned long long[5]) { n4, n3, n2, n1, n0 }, result);                 //思考一下怎么用二进制补码表示一个负数. 
	iss256(result);							//以及学会怎么将一个有符号的用字符表示的负数转化为二进制形式，不懂可参考 "编码：隐匿在计算机软硬件背后的语言.pdf".很可能教会谈恋爱哦.  
	for (; i < 8; i += 2) *(long long*)(&result[i]) = ~(*(long long*)(&result[i]));     //高性能取反一个整形数组表示的二进制数. 
	return result;
}

char* printV256(const unsigned int* value1, char* result79) {
	
	if (value1 && result79) {
		int i = 0;
		int j = 0;
		for (; j < 79; j++) result79[j] = 0;						//字符数组置零. 
		j = 0;
		unsigned int tem[8] = { value1[0], value1[1], value1[2], value1[3] , value1[4], value1[5] , value1[6], value1[7] };  //复制要操作的数. 
		if (value1[7] > (unsigned int)INT_MAX) {      //判断最高位，以确定是否为一个负数. 
			iss256(tem);							  //如果为负数，就去掉符号，把它转化为一个正数.
			for (; i < 8; i += 2) *(long long*)(&tem[i]) = ~(*(long long*)(&tem[i]));
			printf_s("-");
			j = sprintf_s(result79, 79, "-");		  //打印减号. 
		}
		unsigned long long tt[5];					  //五段. 
		binToLL256(tem, tt);						  //二进制转五段. 
		for (i = 0; i < 5; i++) {					  //循环寻找五段中的首个不为零的段. 
			if (tt[i]) {
				printf_s("%llu", tt[i]);			  //打印，段中的空位（为零的）不打印. 
				j += sprintf_s(&(result79[j]), 79 - j, "%llu", tt[i]);
				break;
			}
		}

		if (i == 5) {								  //判断是否为一个零值，如何是零，就直接打印一个十进值符号 0 . 
			printf_s("0");
			j += sprintf_s(result79, 79, "0");
		}
		else {
			for (i = i + 1; i < 5; i++) {			  //循环打印剩余的段. 记得每段最高的位（为零的）也要明显. 
				printf_s("%018llu", tt[i]);
				j += sprintf_s(&(result79[j]), 79 - j, "%018llu", tt[i]);
			}
		}
	}
	
	return result79;
}

char* printVU256(const unsigned int* value1, char* result79) {
	
	if (value1 && result79) {
		unsigned long long tem[5];					  //道理和上面的差不多一样. 
		binToLL256(value1, tem);
		int i = 0;
		int j = 0;
		for (; j < 79; j++) result79[j] = 0;
		j = 0;
		for (; i < 5; i++) {
			if (tem[i]) {
				j = printf_s("%llu", tem[i]);
				sprintf_s(result79, 79, "%llu", tem[i]);
				break;
			}
		}
		if (i == 5) {
			printf_s("0");
			j += sprintf_s(result79, 79, "0");
		}
		else {
			for (i = i + 1; i < 5; i++) {
				printf_s("%018llu", tem[i]);
				j += sprintf_s(&(result79[j]), 79 - j, "%018llu", tem[i]);
			}
		}
	}
	return result79;
}

unsigned int* CV256(char* allD, unsigned int *result) {

	if (allD && result) {
		int j = 0;
		for (; j < 8; j += 2) *((long long*)(&result[j])) = 0;    //结果置零.
		unsigned long long tem[5] = { 0,0,0,0,0 };				  //用于储存拆分的五段. 
		int len = (int)strlen(allD);
		div_t ln = div(len, 18);								  //这两行应该
		if (ln.rem) ln.quot++;									  //是多余的, 可以注释掉. 
		int ifn = ((allD[0] == '-') ? 1 : 0);					  //判断是否为负. 
		j = ((ifn) ? 1 : 0);									  //等于 ifn 可以用 ifn 代替. 

		if (len > 78 || len == 0 || (ifn && len == 78 && (strncmp(INT256C_MIN, allD, 78) == -1)) || (!ifn && len == 78 && (strncmp(UINT256C_MAX, allD, 78) == -1))) {
			puts("CV256 error : out of range, return ZERO!");     //判断输入字符是否超出范围. 
			return result;
		}
		int i = len - 1;										  //字符个数，从 0 开始. 
		int k;
		int p = 4;												  //五段. 
		char temc[19];											  //用于储存将每段转化后得到的字符. 
		temc[18] = '\0';										  //末位置零, 保证其为一个字符串. 

		for (; i >= 17 + j; i -= 18, p--) {
			for (k = 17; k >= 0; k--) temc[k] = allD[i + k - 17]; //从字符数组的末尾向高位，每 18 取段，首段不处理. 
			tem[p] = (unsigned long long)atoll(temc);			  //将取得的段转化为阿拉伯数字，并储存在一个unsigned long long类型的变量. 
		}

		for (k = j; k <= i; k++) temc[k - j] = allD[k];           //处理剩下首段.
		temc[k - j] = '\0';										  //因为首段可能没有满. 所以要添加一个零值, 以确保往后的处理正常进行. 
		tem[p] = (unsigned long long)atoll(temc);                 //转化. 
		if (ifn) return D_V256(tem[0], tem[1], tem[2], tem[3], tem[4], result);   //以负数方式处理，返回结果. 
		return DV256(tem[0], tem[1], tem[2], tem[3], tem[4], result);			  //以正数方式处理，返回结果.
	}
	
	return result;
}

char* showBin256(const unsigned int* value1, char* result257) {
	
	if (value1 && result257) {
		int i = 7;											  //7 到 0 .
		int j;
		int k = 0;
		for (; i >= 0; i--) {

			for (j = 0; j < 32; j++) {						  //从高位开始，不断向右移数组的每位，并判断是1还是0，并打印. 
				if (((value1[i] << j) & pfd)) {
					putchar('1');
					k += sprintf_s(result257, 257 - k, "1");
				}
				else {
					putchar('0');
					k += sprintf_s(result257, 257 - k, "0");
				}
			}
		}
	}
	
	return result257;
}

unsigned int* copyV256(unsigned int* value1, const unsigned int* value2) {
	for (int i = 0; i < 8; i += 2) *(unsigned long long*)(&value1[i]) = *(unsigned long long*)(&value2[i]); //高性能复制一个以整形数组表示的 INT256 .
	return value1;
}

unsigned int* copyVint256(unsigned int* value1, int value2) {
	value1[0] = value2;
	value1[1] = 0;
	*(unsigned long long*)(&value1[2]) = 0;
	*(unsigned long long*)(&value1[4]) = 0;
	*(unsigned long long*)(&value1[6]) = 0;
	return value1;
}

unsigned int* copyVLL256(unsigned int* value1, long long value2) {
	*(unsigned long long*)(&value1[0]) = value2;
	*(unsigned long long*)(&value1[2]) = 0;
	*(unsigned long long*)(&value1[4]) = 0;
	*(unsigned long long*)(&value1[6]) = 0;
	return value1;
}

//===================================================================================================Shihting


unsigned int* lefts256(const unsigned int* value, int n, unsigned int* result) {
	
	if (value && result) {
		int i = 0;
		for (; i < 8; i += 2) *((long long*)(&result[i])) = 0;                           //高性能置零. 
		int n32 = n / 32;																 //整体思想是 n 位是移几个 INT 再加上不足一个 INT 的动作. 
		int r32 = n % 32;
		i = 7 - n32;
		if ((n < 256) && (n >= 0)) {
			if (r32) {
				for (; i > 0; i--) {
					result[i + n32] = (value[i] << r32) + (value[i - 1] >> (32 - r32));
				}
				result[n32] = value[0] << r32;
			} 
			else {

				for (; i >= 0; i--) {
					result[i + n32] = value[i];
				}
			}

		}
	}
	
	return result;
}

unsigned int* rights256(const unsigned int* value, int n, unsigned int* result) {
	
	if (value && result) {
		int n32 = n / 32;															     //整体思想是 n 位是移几个 INT 再加上不足一个 INT 的动作.
		int r32 = n % 32;																 //作为有符号数据处理，右移产生的空位这样处理：负数取 1 ，正数置 0 . 
		int i = 0;
		for (; i < 8; i += 2) *((long long*)(&result[i])) = 0;
		i = n32;
		unsigned int filler = 0;
		if ((n < 256) && (n >= 0)) {
			if (value[7] > (unsigned int)INT_MAX) filler = pp;
			if (r32) {
				for (; i < 7; i++) {
					result[i - n32] = (value[i] >> r32) + (value[i + 1] << (32 - r32));
				}
				result[7 - n32] = (unsigned int)(((signed int)value[7]) >> r32);
			}
			else {
				for (; i < 8; i++) {
					result[i - n32] = value[i];
				}
			}

			if (filler) { for (i = 8 - n32; i < 8; i++) result[i] = filler; }
		}
	}

	return result;
}

unsigned int* rightsU256(const unsigned int* value, int n, unsigned int* result) {
	
	if (value && result) {															      //整体思想是 n 位是移几个 INT 再加上不足一个 INT 的动作.
		int n32 = n / 32;															      //作为无符号数据处理，右移产生的空位这样处理：置 0 .
		int r32 = n % 32;
		int i = 0;
		for (; i < 8; i += 2) *((long long*)(&result[i])) = 0;
		i = n32;

		if ((n < 256) && (n >= 0)) {
			if (r32) {
				for (; i < 7; i++) {
					result[i - n32] = (value[i] >> r32) + (value[i + 1] << (32 - r32));
				}
				result[7 - n32] = value[7] >> r32;
			}
			else {
				for (; i < 8; i++) {
					result[i - n32] = value[i];
				}
			}

		}
	}
	
	return result;
}

//===================================================================================================addSubMulDivMod


unsigned int* add256(const unsigned int* value1, const unsigned int* value2, unsigned int* result) {
	if (value1 && value2 && result) {
		int i = 0;																		  //逐位相加，并判断进位. 
		unsigned int carry = 0;															  //不懂的朋友可继续参考 "编码：隐匿在计算机软硬件背后的语言.pdf". 
		for (; i < 8; i++) {
			result[i] = value1[i] + value2[i] + carry;
			if (carry == 1) {
				if (value1[i] == pp) {
					;
				}
				else {
					carry = (value1[i] + 1 > (pp - value2[i]) ? 1 : 0);
				}
			}
			else {
				carry = (value1[i] > (pp - value2[i]) ? 1 : 0);
			}
		}

	}
	return result;
}

unsigned int* sub256(const unsigned int* value1, const unsigned int* value2, unsigned int* result) {
	
	if (value1 && value2 && result) {
		unsigned int carry = 0;														       //减法，也可以称为补码加法，
		int i = 1;																		   //逐位相加，并判断进位. 
		unsigned int tt;																   //不懂的朋友可继续参考 "编码：隐匿在计算机软硬件背后的语言.pdf".
		result[0] = value1[0] + (~value2[0] + 1);
		if (~value2[0] == pp || (~value2[0] + 1 > (pp - value1[0]))) carry = 1;

		for (; i < 8; i++) {
			tt = ~value2[i];
			result[i] = value1[i] + tt + carry;
			if (carry == 1) {
				if (value1[i] == pp) {
					;
				}
				else {
					carry = (value1[i] + 1 > (pp - tt) ? 1 : 0);
				}
			}
			else {
				carry = (value1[i] > (pp - tt) ? 1 : 0);
			}
		}
	}
	return result;
}

unsigned int* mul256(const unsigned int* value1, const unsigned int* value2, unsigned int* result) {
	
	if (value1 && value2 && result) {
		int i = 0;			//思路：（A7 * 2^(32 * 7) + A6 * 2^(32 * 6) + A5 * 2^(32 * 5) + A4 * 2^(32 * 4) + A3 * 2^(32 * 3) + A2 * 2^(32 * 2) + A1 * 2^32 + A0）
		int j;					 //*（B7 * 2^(32 * 7) + B6 * 2^(32 * 6) + B5 * 2^(32 * 5) + B4 * 2^(32 * 4) + B3 * 2^(32 * 3) + B2 * 2^(32 * 2) + B1 * 2^32 + B0）
		unsigned int carry0 = 0;   //展开，合并同类项，再结合移位和加法，摒弃那些超出范围的计算过程, 要考虑是否有进位产生，调整结果，并返回结果指针. 
		unsigned int carry1 = 0;
		unsigned int carry[8] = { 0,0,0,0,0,0,0,0 };
		unsigned long long* tt0;
		unsigned long long tt1;
		for (; i < 8; i += 2) *((long long*)(&result[i])) = 0;
		for (i = 0; i < 7; i++) {
			tt0 = (unsigned long long*)(&result[i]);
			for (j = 0; j <= i; j++) {
				tt1 = (unsigned long long)value1[j] * (unsigned long long)value2[i - j];
				if ((i + 2 < 8) && (tt1 > ppp - *tt0)) carry[i + 2]++;
				*tt0 += tt1;
			}
		}

		for (j = 0; j <= i; j++) {
			tt1 = (unsigned long long)value1[j] * (unsigned long long)value2[i - j];
			result[7] += (unsigned int)tt1;
		}

		for (i = 2; i < 8; i++) {
			if (carry1 == 1) {
				if (result[i] == pp) {
					;
				}
				else {
					carry1 = (result[i] + 1 > (pp - carry[i]) ? 1 : 0);
				}
			}
			else {
				carry1 = (result[i] > (pp - carry[i]) ? 1 : 0);
			}
			result[i] += (carry[i] + carry0);
			carry0 = carry1;
		}
	}

	return result;
}

unsigned int* divU256(const unsigned int* value1, const unsigned int* value2, unsigned int* result) {

	if (value1 && value2 && result) {
		
		if (!cmpU256(value2, MYINT256_ZERO)) return NULL;
		int i = 0;
		for (; i < 8; i += 2) *((long long*)(&result[i])) = 0;
		i = cmpU256(value1, value2);
		if (i == -1) return result;
		if (i == 0) {		//以无符号视角，先判断 value1 是否大于 value2 ，如果不，直接处理，返回结果指针，
			result[i] = 1;	//接下来的思路：两数尽量如下对齐,除数右移（假设16位，实际256位）：  1010101110110110
			return result;	//															         101010111101100
		}					//然后被除数循环减去右移的除数，直至被除数小于除数，将得到的累差（减的次数）处理（移位），重新右移除数使对齐，相似处理，直至被除数小于不移右的除数. 
																																				   //最后的被除数即余数. 
		int ddn2 = 0;
		int ddr2 = 0;
		int ddn1 = 7;
		int ddr1 = 31;
		int mdd;
		unsigned int remd[8] = { value1[0], value1[1], value1[2], value1[3], value1[4], value1[5], value1[6], value1[7] };
		unsigned int tem[8] = { value2[0], value2[1], value2[2], value2[3], value2[4], value2[5], value2[6], value2[7] };
		
		for (i = 7; i >= 0; i--) {
			if (value2[i]) {
				ddn2 = i;
				break;
			}
		}

		if (value2[ddn2] & pfd) {
			ddr2 = 31;
		}
		else {
			for (i = 1; i < 32; i++) {
				if (((value2[ddn2] << i) & pfd)) {
					ddr2 = 31 - i;
					break;
				}
			}
		}
		do {
			mdd = 0;
			for (i = ddn1; i >= 0; i--) {
				if (remd[i]) {
					ddn1 = i;
					break;
				}
			}

			if (remd[ddn1] & pfd) {
				ddr1 = 31;
			}
			else {
				for (i = 1; i < 32; i++) {
					if (((remd[ddn1] << i) & pfd)) {
						ddr1 = 31 - i;
						break;
					}
				}
			}

			if ((mdd = (ddn1 - ddn2) * 32)) {
				mdd += (ddr1 - ddr2 - 1);
			}
			else {
				if ((mdd = ddr1 - ddr2)) {
					mdd--;
				}
			}
			ilsn256(tem, mdd);
			for (i = 1; i < 5; i++) {
				if (cmpU256(isa256(remd, tem), tem) == -1) break;
			}
			div_t mdds = div(mdd, 32);
			if (mdds.quot == 7) { result[mdds.quot] += (unsigned int)i << (mdds.rem); }
			else *((unsigned long long*)(&result[mdds.quot])) += ((unsigned long long)i << (mdds.rem));
			for (i = 0; i < 8; i += 2) *(unsigned long long *)(&tem[i]) = *(unsigned long long *)(&value2[i]);
		} while (cmpU256(remd, value2) != -1);
	}

	return result;
}

unsigned int* div256(const unsigned int* value1, const unsigned int* value2, unsigned int* result) {

	if (value1 && value2 && result) {                       //根据被除数和除数的情况，分为四种情况，若不全为正数，转化为正数，以无符号视角处理，再考虑符号，返回结果指针. 
		if (!cmpU256(value2, MYINT256_ZERO)) return NULL;
		int i = 0;
		if (value1[7] > (unsigned int)INT_MAX) {
			unsigned int tem1[8] = { value1[0], value1[1], value1[2], value1[3], value1[4], value1[5], value1[6], value1[7] };
			iss256(tem1);
			for (; i < 8; i += 2) *(long long*)(&tem1[i]) = ~(*(long long*)(&tem1[i]));
			if (value2[7] > (unsigned int)INT_MAX) {
				unsigned int tem2[8] = { value2[0], value2[1], value2[2], value2[3], value2[4], value2[5], value2[6], value2[7] };
				iss256(tem2);
				for (i = 0; i < 8; i += 2) *(long long*)(&tem2[i]) = ~(*(long long*)(&tem2[i]));
				return divU256(tem1, tem2, result);
			}
			else {
				divU256(tem1, value2, result);
				for (i = 0; i < 8; i += 2) *(long long*)(&result[i]) = ~(*(long long*)(&result[i]));
				return ipp256(result);
			}
		}
		else if (value2[7] > (unsigned int)INT_MAX) {
			unsigned int tem2[8] = { value2[0], value2[1], value2[2], value2[3], value2[4], value2[5], value2[6], value2[7] };
			iss256(tem2);
			for (; i < 8; i += 2) *(long long*)(&tem2[i]) = ~(*(long long*)(&tem2[i]));
			divU256(value1, tem2, result);
			for (i = 0; i < 8; i += 2) *(long long*)(&result[i]) = ~(*(long long*)(&result[i]));
			return ipp256(result);
		}
		else {
			return divU256(value1, value2, result);
		}
	}
	
	return result;
}


unsigned int* modU256(const unsigned int* value1, const unsigned int* value2, unsigned int* result) {

	if (value1 && value2 && result) {       //思路与上面的除法相似，结果取余. 返回结果指针. 
		int i = 0;
		for (; i < 8; i += 2) *((long long*)(&result[i])) = 0;

		i = cmpU256(value1, value2);
		if (!cmpU256(value2, MYINT256_ZERO)) return NULL;
		if (i == 0) return result;
		for (int j = 0; j < 8; j += 2) *(unsigned long long*)(&result[j]) = *(unsigned long long*)(&value1[j]);
		if (i == -1) return result;

		int ddn2 = 0;
		int ddr2 = 0;
		int ddn1 = 7;
		int ddr1 = 31;
		int mdd;
		unsigned int tem[8] = { value2[0], value2[1], value2[2], value2[3], value2[4], value2[5], value2[6], value2[7] };
		for (i = 7; i >= 0; i--) {
			if (value2[i]) {
				ddn2 = i;
				break;
			}
		}

		if (value2[ddn2] & pfd) {
			ddr2 = 31;
		}
		else {
			for (i = 1; i < 32; i++) {
				if (((value2[ddn2] << i) & pfd)) {
					ddr2 = 31 - i;
					break;
				}
			}
		}
		do {
			mdd = 0;
			for (i = ddn1; i >= 0; i--) {
				if (result[i]) {
					ddn1 = i;
					break;
				}
			}

			if (result[ddn1] & pfd) {
				ddr1 = 31;
			}
			else {
				for (i = 1; i < 32; i++) {
					if (((result[ddn1] << i) & pfd)) {
						ddr1 = 31 - i;
						break;
					}
				}
			}

			if ((mdd = (ddn1 - ddn2) * 32)) {
				mdd += (ddr1 - ddr2 - 1);
			}
			else {
				if ((mdd = ddr1 - ddr2)) {
					mdd--;
				}
			}
			ilsn256(tem, mdd);
			for (i = 1; i < 5; i++) {
				if (cmpU256(isa256(result, tem), tem) == -1) break;
			}
			for (i = 0; i < 8; i += 2) *(unsigned long long *)(&tem[i]) = *(unsigned long long *)(&value2[i]);
		} while (cmpU256(result, value2) != -1);
	}
	
	return result;
}

unsigned int* mod256(const unsigned int* value1, const unsigned int* value2, unsigned int* result) {

	if (value1 && value2 && result) {
		if (!cmpU256(value2, MYINT256_ZERO)) return NULL; //根据被除数和除数的情况，分为四种情况，若不全为正数，转化为正数，以无符号视角处理，再考虑符号，返回结果指针，细细思考. 
		int i = 0;
		if (value1[7] > (unsigned int)INT_MAX) {
			unsigned int tem1[8] = { value1[0], value1[1], value1[2], value1[3], value1[4], value1[5], value1[6], value1[7] };
			iss256(tem1);
			for (; i < 8; i += 2) *(long long*)(&tem1[i]) = ~(*(long long*)(&tem1[i]));
			if (value2[7] > (unsigned int)INT_MAX) {
				unsigned int tem2[8] = { value2[0], value2[1], value2[2], value2[3], value2[4], value2[5], value2[6], value2[7] };
				iss256(tem2);
				for (i = 0; i < 8; i += 2) *(long long*)(&tem2[i]) = ~(*(long long*)(&tem2[i]));
				modU256(tem1, tem2, result);
				for (i = 0; i < 8; i += 2) *(long long*)(&result[i]) = ~(*(long long*)(&result[i]));
				return ipp256(result);
			}
			else {
				modU256(tem1, value2, result);
				for (i = 0; i < 8; i += 2) *(long long*)(&result[i]) = ~(*(long long*)(&result[i]));
				return ipp256(result);
			}
		}
		else if (value2[7] > (unsigned int)INT_MAX) {
			unsigned int tem2[8] = { value2[0], value2[1], value2[2], value2[3], value2[4], value2[5], value2[6], value2[7] };
			iss256(tem2);
			for (; i < 8; i += 2) *(long long*)(&tem2[i]) = ~(*(long long*)(&tem2[i]));
			return modU256(value1, tem2, result);
		}
		else {
			return modU256(value1, value2, result);
		}
	}
	
	return result;

}


my256div_t* divUAll256(const unsigned int* value1, const unsigned int* value2, my256div_t* result) {
	
	if (value1 && value2 && result) {															//将无符号整数除法的两个结果（商和余）储存在一个结构中，并返回指针，思路请参考上面. 
		

		if (!cmpU256(value2, MYINT256_ZERO)) return NULL;
		int i = 0;
		for (; i < 8; i += 2) {
			*(long long*)(&(result->quot)[i]) = 0;
			*(unsigned long long*)(&(result->rem)[i]) = *(unsigned long long*)(&value1[i]);
		}

		i = cmpU256(value1, value2);

		if (i == -1) return result;

		if (i == 0) {
			(result->quot)[0] = 1;
			for (; i < 8; i += 2) *(long long *)(&(result->rem)[i]) = 0;
			return result;
		}

		int ddn2 = 0;
		int ddr2 = 0;
		int ddn1 = 7;
		int ddr1 = 31;
		int mdd;
		unsigned int tem[8] = { value2[0], value2[1], value2[2], value2[3], value2[4], value2[5], value2[6], value2[7] };
		for (i = 7; i >= 0; i--) {
			if (value2[i]) {
				ddn2 = i;
				break;
			}
		}

		if (value2[ddn2] & pfd) {
			ddr2 = 31;
		}
		else {
			for (i = 1; i < 32; i++) {
				if (((value2[ddn2] << i) & pfd)) {
					ddr2 = 31 - i;
					break;
				}
			}
		}
		do {
			mdd = 0;
			for (i = ddn1; i >= 0; i--) {
				if ((result->rem)[i]) {
					ddn1 = i;
					break;
				}
			}

			if ((result->rem)[ddn1] & pfd) {
				ddr1 = 31;
			}
			else {
				for (i = 1; i < 32; i++) {
					if ((((result->rem)[ddn1] << i) & pfd)) {
						ddr1 = 31 - i;
						break;
					}
				}
			}

			if ((mdd = (ddn1 - ddn2) * 32)) {
				mdd += (ddr1 - ddr2 - 1);
			}
			else {
				if ((mdd = ddr1 - ddr2)) {
					mdd--;
				}
			}
			ilsn256(tem, mdd);
			for (i = 1; i < 5; i++) {
				if (cmpU256(isa256((result->rem), tem), tem) == -1) break;
			}
			div_t mdds = div(mdd, 32);
			if (mdds.quot == 7) { (result->quot)[mdds.quot] += (unsigned int)i << (mdds.rem);
			}
			else{
				*((unsigned long long*)(&((result->quot)[mdds.quot]))) += ((unsigned long long)i << (mdds.rem));
			}
			for (i = 0; i < 8; i += 2) *(unsigned long long *)(&tem[i]) = *(unsigned long long *)(&value2[i]);
		} while (cmpU256((result->rem), value2) != -1);
	}
	
	return result;

}

my256div_t* divAll256(const unsigned int* value1, const unsigned int* value2, my256div_t* result) {
	
	if (value1 && value2 && result) {
		if (!cmpU256(value2, MYINT256_ZERO)) return NULL;      //将有符号整数除法的两个结果（商和余）储存在一个结构中，并返回指针，思路请参考上面. 
		int i = 0;

		if (value1[7] > (unsigned int)INT_MAX) {
			unsigned int tem1[8] = { value1[0], value1[1], value1[2], value1[3], value1[4], value1[5], value1[6], value1[7] };
			iss256(tem1);
			for (; i < 8; i += 2) *(long long *)(&tem1[i]) = ~(*(long long *)(&tem1[i]));
			if (value2[7] > (unsigned int)INT_MAX) {
				unsigned int tem2[8] = { value2[0], value2[1], value2[2], value2[3], value2[4], value2[5], value2[6], value2[7] };
				iss256(tem2);
				for (i = 0; i < 8; i += 2) *(long long*)(&tem2[i]) = ~(*(long long*)(&tem2[i]));
				divUAll256(tem1, tem2, result);
				for (i = 0; i < 8; i += 2) *(long long *)(&(result->rem)[i]) = ~(*(long long *)(&(result->rem)[i]));
				ipp256(result->rem);
			}
			else {
				divUAll256(tem1, value2, result);
				for (i = 0; i < 8; i += 2) {
					*(long long *)(&(result->quot)[i]) = ~(*(long long *)(&(result->quot)[i]));
					*(long long *)(&(result->rem)[i]) = ~(*(long long *)(&(result->rem)[i]));
				}
				ipp256(result->quot);
				ipp256(result->rem);
			}
		}
		else if (value2[7] > (unsigned int)INT_MAX) {
			unsigned int tem2[8] = { value2[0], value2[1], value2[2], value2[3], value2[4], value2[5], value2[6], value2[7] };
			iss256(tem2);
			for (; i < 8; i += 2) *(long long*)(&tem2[i]) = ~(*(long long*)(&tem2[i]));
			divUAll256(value1, tem2, result);
			for (i = 0; i < 8; i += 2) *(long long *)(&(result->quot)[i]) = ~(*(long long *)(&(result->quot)[i]));
			ipp256(result->quot);
		}
		else {
			return divUAll256(value1, value2, result);
		}
	}
	
	return result;
}

//===================================================================================================AndOrXorR

unsigned int* r256(const unsigned int* value1, unsigned int* result) {
	if (value1 && result) {
		for (int i = 0; i < 8; i += 2) *(long long *)(&result[i]) = ~(*(long long *)(&value1[i]));  //高性能快速按位取反. 
	}
	return result;
}

unsigned int* and256(const unsigned int* value1, const unsigned int* value2, unsigned int* result) {
	
	if (value1 && value2 && result) {
		for (int i = 0; i < 8; i += 2) *(unsigned long long*)(&result[i]) = *(unsigned long long*)(&value1[i]) & *(unsigned long long*)(&value2[i]);  //高性能快速按位与.
	}
	return result;
}

unsigned int* or256(const unsigned int* value1, const unsigned int* value2, unsigned int* result) {

	if (value1 && value2 && result) {
		for (int i = 0; i < 8; i += 2) *(unsigned long long*)(&result[i]) = *(unsigned long long*)(&value1[i]) | *(unsigned long long*)(&value2[i]);  //高性能快速按位或.
	}
	return result;
}

unsigned int* xor256(const unsigned int* value1, const unsigned int* value2, unsigned int* result) {

	if (value1 && value2 && result) {
		for (int i = 0; i < 8; i += 2) *(unsigned long long*)(&result[i]) = *(unsigned long long*)(&value1[i]) ^ *(unsigned long long*)(&value2[i]);  //高性能快速按位异或.
	}
	return result;
}

//===================================================================================================selfOperating

unsigned int* ir256(unsigned int* self) {
	if(self){ for (int i = 0; i < 8; i += 2) *(long long *)(&self[i]) = ~(*(long long *)(&self[i])); }                                             //高性能快速自取反.
	
	return self;
}

unsigned int* iand256(unsigned int* self, const unsigned int* value2) {

	if (self && value2) {
		for (int i = 0; i < 8; i += 2) *(unsigned long long*)(&self[i]) = *(unsigned long long*)(&self[i]) & *(unsigned long long*)(&value2[i]);  //高性能快速自与一个数.
	}
	return self;

}

unsigned int* ior256(unsigned int* self, const unsigned int* value2) {

	if (self && value2) {
		for (int i = 0; i < 8; i += 2) *(unsigned long long*)(&self[i]) = *(unsigned long long*)(&self[i]) | *(unsigned long long*)(&value2[i]);  //高性能快速自或一个数.
	}
	return self;

}

unsigned int* ixor256(unsigned int* self, const unsigned int* value2) {

	if (self && value2) {
		for (int i = 0; i < 8; i += 2) *(unsigned long long*)(&self[i]) = *(unsigned long long*)(&self[i]) ^ *(unsigned long long*)(&value2[i]);  //高性能快速自异或一个数.
	}
	return self;

}

unsigned int* iss256(unsigned int* value1) {
	unsigned int carry0 = 0;                                                     //自减，记得考虑进位. 
	unsigned int carry = 0;
	int i = 0;

	if (value1) {
		for (; i < 8; i++) {
			carry = ((value1[i] == 0 && carry0 == 0) ? 0 : 1);
			value1[i] = value1[i] + pp + carry0;
			carry0 = carry;
		}

	}
	return value1;
}
unsigned int* ipp256(unsigned int* value1) {
	unsigned int carry = 1;                                                     //自加，记得考虑进位. 
	unsigned int carry2 = 0;
	int i = 0;
	if (value1) {
		for (; i < 8; i++) {
			if (!carry) break;
			carry2 = (value1[i] == pp ? 1 : 0);
			value1[i] += carry;
			carry = carry2;
		}
	}
	return value1;
}

unsigned int* ipa256(unsigned int* self, const unsigned int* value1) {          //自加一个数，记得考虑进位. 
	if (self && value1) {
		int i = 0;
		unsigned int carry0 = 0;
		unsigned int carry = 0;

		for (; i < 8; i++) {
			if (carry == 1) {
				if (self[i] == pp) {
					;
				}
				else {
					carry = (self[i] + 1 > (pp - value1[i]) ? 1 : 0);
				}
			}
			else {
				carry = (self[i] > (pp - value1[i]) ? 1 : 0);
			}
			self[i] += (value1[i] + carry0);
			carry0 = carry;
		}
	}
	
	return self;
}

unsigned int* isa256(unsigned int* self, const unsigned int* value1) {         //自减一个数，记得考虑进位.
	
	if (self && value1) {
		unsigned int carry0 = 0;
		unsigned int carry = 0;
		int i = 1;
		unsigned int tt;

		if (~value1[0] == pp || (~value1[0] + 1 > (pp - self[0]))) { carry0 = 1; carry = 1; }
		self[0] += (~value1[0] + 1);

		for (; i < 8; i++) {
			tt = ~value1[i];
			if (carry == 1) {
				if (tt == pp) {
					;
				}
				else {
					carry = (tt + 1 > (pp - self[i]) ? 1 : 0);
				}
			}
			else {
				carry = (tt > (pp - self[i]) ? 1 : 0);
			}
			self[i] += (tt + carry0);
			carry0 = carry;
		}
	}
	
	return self;
}

unsigned int* ima256(unsigned int* self, const unsigned int* value1) {        //自乘一个数，记得考虑进位.

	if (self && value1) {
		unsigned int result[8] = { 0,0,0,0,0,0,0,0 };
		int i = 0;
		int j;
		unsigned int carry0 = 0;
		unsigned int carry1 = 0;
		unsigned int carry[8] = { 0,0,0,0,0,0,0,0 };
		unsigned long long* tt0;
		unsigned long long tt1;
		for (; i < 7; i++) {
			tt0 = (unsigned long long*)(&result[i]);
			for (j = 0; j <= i; j++) {
				tt1 = (unsigned long long)self[j] * (unsigned long long)value1[i - j];
				if ((i + 2 < 8) && (tt1 > ppp - *tt0)) carry[i + 2]++;
				*tt0 += tt1;
			}
		}

		for (j = 0; j <= i; j++) {
			tt1 = (unsigned long long)self[j] * (unsigned long long)value1[i - j];
			result[7] += (unsigned int)tt1;
		}

		for (i = 2; i < 8; i++) {
			if (carry1 == 1) {
				if (result[i] == pp) {
					;
				}
				else {
					carry1 = (result[i] + 1 > (pp - carry[i]) ? 1 : 0);
				}
			}
			else {
				carry1 = (result[i] > (pp - carry[i]) ? 1 : 0);
			}
			result[i] += (carry[i] + carry0);
			carry0 = carry1;
		}
		for (i = 0; i < 8; i += 2) *(unsigned long long *)(&self[i]) = *(unsigned long long *)(&result[i]);
	}

	return self;
}

unsigned int* idaU256(unsigned int* self, const unsigned int* value1) {     //以无符号视角，自除以一个数.
	if (self && value1) {
		
		if (!cmpU256(value1, MYINT256_ZERO)) return NULL;
		int i = cmpU256(self, value1);
		unsigned int remd[8] = { self[0], self[1], self[2], self[3], self[4], self[5], self[6], self[7] };
		for (int j = 0; j < 8; j += 2) *(long long *)(&self[j]) = 0;

		if (i == -1) return self;
		if (i == 0) {
			self[0] = 1;
			return self;
		}

		int ddn2 = 0;
		int ddr2 = 0;
		int ddn1 = 7;
		int ddr1 = 31;
		int mdd;
		unsigned int tem[8] = { value1[0], value1[1], value1[2], value1[3], value1[4], value1[5], value1[6], value1[7] };
		
		for (i = 7; i >= 0; i--) {
			if (value1[i]) {
				ddn2 = i;
				break;
			}
		}

		if (value1[ddn2] & pfd) {
			ddr2 = 31;
		}
		else {
			for (i = 1; i < 32; i++) {
				if (((value1[ddn2] << i) & pfd)) {
					ddr2 = 31 - i;
					break;
				}
			}
		}
		do {
			mdd = 0;
			for (i = ddn1; i >= 0; i--) {
				if (remd[i]) {
					ddn1 = i;
					break;
				}
			}

			if (remd[ddn1] & pfd) {
				ddr1 = 31;
			}
			else {
				for (i = 1; i < 32; i++) {
					if (((remd[ddn1] << i) & pfd)) {
						ddr1 = 31 - i;
						break;
					}
				}
			}

			if ((mdd = (ddn1 - ddn2) * 32)) {
				mdd += (ddr1 - ddr2 - 1);
			}
			else {
				if ((mdd = ddr1 - ddr2)) {
					mdd--;
				}
			}
			ilsn256(tem, mdd);
			for (i = 1; i < 5; i++) {
				if (cmpU256(isa256(remd, tem), tem) == -1) break;
			}
			div_t mdds = div(mdd, 32);
			if (mdds.quot == 7) {
				self[mdds.quot] += (unsigned int)i << (mdds.rem);
			}
			else {
				*((unsigned long long*)(&self[mdds.quot])) += ((unsigned long long)i << (mdds.rem));
			}
			for (i = 0; i < 8; i += 2) *(unsigned long long *)(&tem[i]) = *(unsigned long long *)(&value1[i]);
		} while (cmpU256(remd, value1) != -1);
	}
	
	return self;
}

unsigned int* ida256(unsigned int* self, const unsigned int* value1) {       //以有符号视角，自除以一个数.
	if (self && value1) {
		if (!cmpU256(value1, MYINT256_ZERO)) return NULL;
		int i = 0;
		if (self[7] > (unsigned int)INT_MAX) {
			iss256(self);
			for (; i < 8; i += 2) *(long long *)(&self[i]) = ~(*(long long *)(&self[i]));
			if (value1[7] > (unsigned int)INT_MAX) {
				unsigned int tem2[8] = { value1[0], value1[1], value1[2], value1[3], value1[4], value1[5], value1[6], value1[7] };
				iss256(tem2);
				for (i = 0; i < 8; i += 2) *(long long *)(&tem2[i]) = ~(*(long long*)(&tem2[i]));
				return idaU256(self, tem2);
			}
			else {
				idaU256(self, value1);
				for (i = 0; i < 8; i += 2) *(long long*)(&self[i]) = ~(*(long long*)(&self[i]));
				return ipp256(self);
			}
		}
		else if (value1[7] > (unsigned int)INT_MAX) {
			unsigned int tem2[8] = { value1[0], value1[1], value1[2], value1[3], value1[4], value1[5], value1[6], value1[7] };
			iss256(tem2);
			for (; i < 8; i += 2) *(long long*)(&tem2[i]) = ~(*(long long*)(&tem2[i]));
			idaU256(self, tem2);
			for (i = 0; i < 8; i += 2) *(long long*)(&self[i]) = ~(*(long long*)(&self[i]));
			return ipp256(self);
		}
		else {
			return idaU256(self, value1);
		}
	}
	
	return self;
}

unsigned int* imodaU256(unsigned int* self, const unsigned int* value1) {    //以无符号视角，自除余一个数.

	if (self && value1) {
		int i = cmpU256(self, value1);

		if (!cmpU256(value1, MYINT256_ZERO)) return NULL;
		if (i == -1) {
			return self;
		}
		if (i == 0) {
			for (int j = 0; j < 8; j += 2) *(long long *)(&self[j]) = 0;
			return self;
		}

		int ddn2 = 0;
		int ddr2 = 0;
		int ddn1 = 7;
		int ddr1 = 31;
		int mdd;
		unsigned int tem[8] = { value1[0], value1[1], value1[2], value1[3], value1[4], value1[5], value1[6], value1[7] };
		for (i = 7; i >= 0; i--) {
			if (value1[i]) {
				ddn2 = i;
				break;
			}
		}

		if (value1[ddn2] & pfd) {
			ddr2 = 31;
		}
		else {
			for (i = 1; i < 32; i++) {
				if (((value1[ddn2] << i) & pfd)) {
					ddr2 = 31 - i;
					break;
				}
			}
		}
		do {
			mdd = 0;
			for (i = ddn1; i >= 0; i--) {
				if (self[i]) {
					ddn1 = i;
					break;
				}
			}

			if (self[ddn1] & pfd) {
				ddr1 = 31;
			}
			else {
				for (i = 1; i < 32; i++) {
					if (((self[ddn1] << i) & pfd)) {
						ddr1 = 31 - i;
						break;
					}
				}
			}

			if ((mdd = (ddn1 - ddn2) * 32)) {
				mdd += (ddr1 - ddr2 - 1);
			}
			else {
				if ((mdd = ddr1 - ddr2)) {
					mdd--;
				}
			}
			ilsn256(tem, mdd);
			for (i = 1; i < 5; i++) {
				if (cmpU256(isa256(self, tem), tem) == -1) break;
			}
			for (i = 0; i < 8; i++) tem[i] = value1[i];
		} while (cmpU256(self, value1) != -1);
	}

	return self;
}

unsigned int* imoda256(unsigned int* self, const unsigned int* value1) {       //以有符号视角，自除余一个数.

	if (self && value1) {
		if (!cmpU256(value1, MYINT256_ZERO)) return NULL;
		int i = 0;
		if (self[7] > (unsigned int)INT_MAX) {
			iss256(self);
			for (; i < 8; i += 2) *(long long*)(&self[i]) = ~(*(long long*)(&self[i]));
			if (value1[7] > (unsigned int)INT_MAX) {
				unsigned int tem2[8] = { value1[0], value1[1], value1[2], value1[3], value1[4], value1[5], value1[6], value1[7] };
				iss256(tem2);
				for (i = 0; i < 8; i += 2) *(long long*)(&tem2[i]) = ~(*(long long*)(&tem2[i]));
				imodaU256(self, tem2);
				for (i = 0; i < 8; i += 2) *(long long*)(&self[i]) = ~(*(long long*)(&self[i]));
				return ipp256(self);
			}
			else {
				imodaU256(self, value1);
				for (i = 0; i < 8; i += 2) *(long long*)(&self[i]) = ~(*(long long*)(&self[i]));
				return ipp256(self);
			}
		}
		else if (value1[7] > (unsigned int)INT_MAX) {
			unsigned int tem2[8] = { value1[0], value1[1], value1[2], value1[3], value1[4], value1[5], value1[6], value1[7] };
			iss256(tem2);
			for (; i < 8; i += 2) *(long long*)(&tem2[i]) = ~(*(long long*)(&tem2[i]));
			return imodaU256(self, tem2);
		}
		else {
			return imodaU256(self, value1);
		}
	}
	
	return self;
}

unsigned int* ilsn256(unsigned int* self, int n) {                           //自左移 n 位. 
	unsigned int result[8] = { 0,0,0,0,0,0,0,0 };
	int i;
	if (self && (n < 256) && (n >= 0)) {
		int n32 = n / 32;
		int r32 = n % 32;
		
		i = 7 - n32;

		if (r32) {

			for (; i > 0; i--) {
				result[i + n32] = (self[i] << r32) + (self[i - 1] >> (32 - r32));
			}
			result[n32] = self[0] << r32;
		}
		else {

			for (; i >= 0; i--) {
				result[i + n32] = self[i];
			}
		}
		
	}
	if (self) { for (i = 0; i < 8; i += 2) *(unsigned long long*)(&self[i]) = *(unsigned long long*)(&result[i]); }
	return self;
}

unsigned int* irsn256(unsigned int* self, int n) {                           //以有符号视角，自右移 n 位.
	unsigned int result[8] = { 0,0,0,0,0,0,0,0 };
	int i;
	if (self && (n < 256) && (n >= 0)) {
		int n32 = n / 32;
		int r32 = n % 32;
		
		i = n32;
		unsigned int filler = 0;

		if (self[7] > (unsigned int)INT_MAX) filler = pp;
		if (r32) {

			for (; i < 7; i++) {
				result[i - n32] = (self[i] >> r32) + (self[i + 1] << (32 - r32));
			}
			result[7 - n32] = (unsigned int)(((signed int)self[7]) >> r32);
		}
		else {
			for (; i < 8; i++) {
				result[i - n32] = self[i];
			}
		}

		if (filler) {
			for (i = 8 - n32; i < 8; i++) result[i] = filler;
		}
		
	}
	if(self){ for (i = 0; i < 8; i += 2) *(unsigned long long*)(&self[i]) = *(unsigned long long*)(&result[i]); }
	return self;
}

unsigned int* irsnU256(unsigned int* self, int n) {                       //以无符号视角，自右移 n 位.
	unsigned int result[8] = { 0,0,0,0,0,0,0,0 };
	int i;
	if (self && (n < 256) && (n >= 0)) {
		int n32 = n / 32;
		int r32 = n % 32;
		unsigned int result[8] = { 0,0,0,0,0,0,0,0 };
		i = n32;

		if (r32) {

			for (; i < 7; i++) {
				result[i - n32] = (self[i] >> r32) + (self[i + 1] << (32 - r32));
			}
			result[7 - n32] = self[7] >> r32;
		}
		else {

			for (; i < 8; i++) {
				result[i - n32] = self[i];
			}
		}
	}
	if (self) { for (i = 0; i < 8; i += 2) *(unsigned long long*)(&self[i]) = *(unsigned long long*)(&result[i]); }
	return self;
}

//===================================================================================================cmp


int cmp256(const unsigned int* value1, const unsigned int* value2) {
	if (value1 && value2) {
		if (value1[7] != value2[7]) {                                  //思路：先判断最高位，确定是否为负， 然后不用我说了吧. 
			if ((signed int)value1[7] > (signed int)value2[7]) {
				return 1;
			}
			else {
				return -1;
			}
		}
		else if (value1[7] > (unsigned int)INT_MAX) {

			for (int i = 6; i >= 0; i--) {
				if (value1[i] > value2[i]) {
					return -1;
				}
				else if (value1[i] > value2[i]) {
					return 1;
				}
			}
			return 0;
		}
		else {
			for (int i = 6; i >= 0; i--) {
				if (value1[i] > value2[i]) {
					return 1;
				}
				else if (value1[i] > value2[i]) {
					return -1;
				}
			}
			return 0;
		}
	}
	return -2;
}
int cmpU256(const unsigned int* value1, const unsigned int* value2) {
	if (value1 && value2) {
		for (int i = 7; i >= 0; i--) {									//思路：逐位比较，直至肯定.  				
			if (value1[i] > value2[i]) {
				return 1;
			}
			else if (value1[i] < value2[i]) return -1;
		}
		return 0;
	}
	return -2;
}

