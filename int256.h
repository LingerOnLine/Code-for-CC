#ifndef __INT256_H__
#define __INT256_H__

//������ͷ�ļ�ע��Ϊ����������ע����ת���������壬���в���֮���ɳ�����ϵ����.     Email ��lingeronline@126.com
//������Ц��������Ϊ INT256 , �����ƣ����������ɽ���ʹ�ã�Ҳ������ʹ�ã�������ֹ��������������͸�������꽫ϰ�������ռ����ܣ�����**������һ����С��С��С�����ܣ�. 
//Make a joy �� This program is named INT256 , it can improve, and grave, and return or update, and even to the endless evolution, if you see the all meanings, you will get the biggest secret of the universe...

/*
* һ�������������Ľṹ.
*/
struct My256div_t {
	unsigned int quot[8];  //��.
	unsigned int rem[8];   //��.
};
typedef struct My256div_t my256div_t;
typedef unsigned int bint256[8];       //INT256
typedef unsigned int ubint256[8];      //INT256 ������һ�еı�����û������Ҫ����ô��, �������������޷������ݵģ�����Ҫ������������ʵ����һ�뷨.

extern const char INT256C_MAX[79];     //�ַ���ʾ���з���INT256���ֵ.
extern const char INT256C_MIN[79];	   //�ַ���ʾ���з���INT256��Сֵ.
extern const char UINT256C_MAX[79];    //�ַ���ʾ���޷���INT256���ֵ.

extern const unsigned int MYUINT256_MAX[8];  //���������ʾ�ģ�Ҳ�����ɶ�������ʽ�ģ��޷��� INT256 ���ֵ.
extern const unsigned int MYINT256_MAX[8];   //���������ʾ�ģ�Ҳ�����ɶ�������ʽ�ģ��з��� INT256 ���ֵ.
extern const unsigned int MYINT256_MIN[8];   //���������ʾ�ģ�Ҳ�����ɶ�������ʽ�ģ��з��� INT256 ��Сֵ.
extern const unsigned int MYINT256_ZERO[8];  //���������ʾ�ģ�Ҳ�����ɶ�������ʽ�ģ�INT256 ��ֵ.
extern const unsigned int MYINT256__1[8];    //���������ʾ�ģ�Ҳ�����ɶ�������ʽ��) �з��� INT256 ֵ -1 .
extern const unsigned int MYINT256_1[8];     //���������ʾ�ģ�Ҳ�����ɶ�������ʽ��) INT256 ֵ 1 .

//======================================================================================================================================================����ת��
/*
* һ�������ַ���Ϣ��ʾ��ʮ���Ƶ�����ת��Ϊ��һ�����������ʾ�Ķ��������ݵĺ���������ֵΪ���ָ��.
*/
extern unsigned int* CV256(char* allD, unsigned int* result);

/*
* һ������һ�����������ʾ�Ķ���������ת��Ϊһ���Գ������Σ��൱��ʮ���Ʒֳ����α�ʾ����ʾ�����ݵ��ڲ�����������ֵΪ���ָ��.
*/
static unsigned long long* binToLL256(const unsigned int* value1, unsigned long long* result);

/*
* һ����һ���Գ������Σ��൱��ʮ���Ʒֳ����α�ʾ����ʾ������ת��Ϊ��һ�����������ʾ�Ķ��������ݵ��ڲ�����������ֵΪ���ָ��.
*/
static unsigned int* LLTobin256(unsigned long long* value1, unsigned int* result);

/*
* һ����������ʡ�ԣ�����Σ�����ת��Ϊһ����һ�����������ʾ�Ķ��������ݵ��ڲ�����������ֵΪ���ָ��.
*/
static unsigned int* DV256(unsigned long long n4, unsigned long long n3, unsigned long long n2, unsigned long long n1, unsigned long long n0, unsigned int* result);

/*
* һ����������ʡ�ԣ�����Σ�����ת��Ϊһ����һ�����������ʾ�Ķ��������ݵ��ڲ�����������ֵΪ���ָ��.
*/
static unsigned int* D_V256(unsigned long long n4, unsigned long long n3, unsigned long long n2, unsigned long long n1, unsigned long long n0, unsigned int* result);

//======================================================================================================================================================���ִ�ӡ

/*
* ���з�����ʽ��ӡһ�����������ݣ��������������һ���ַ������У�����ֵΪ���ָ��. 
*/
extern char* printV256(const unsigned int* value1, char* result79);

/*
* ���޷�����ʽ��ӡһ�����������ݣ��������������һ���ַ������У�����ֵΪ���ָ��.
*/
extern char* printVU256(const unsigned int* value1, char* result79);

/*
* �Զ�������ʽ��ӡһ�����������ݣ��������������һ���ַ������У�����ֵΪ���ָ��.
*/
extern char* showBin256(const unsigned int* value1, char* result257);

//======================================================================================================================================================���ָ���

/*
* ����һ�����ݣ�����ֵΪ���ָ��.
*/
extern unsigned int* copyV256(unsigned int* value1, const unsigned int* value2);

/*
* ��һ���������ݸ��Ƴ�INT256������ֵΪ���ָ��.
*/
extern unsigned int* copyVint256(unsigned int* value1, int value2);

/*
* ��һ�������������ݸ��Ƴ�INT256������ֵΪ���ָ��.
*/
extern unsigned int* copyVLL256(unsigned int* value1, long long value2);

//======================================================================================================================================================�Ӽ��˳�ȡ��


/*
* ������������ӣ���������һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* add256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* ��һ�����ݼ�ȥһ�����ݣ���������һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* sub256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* ������������ˣ���������һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* mul256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* ��һ�����ݣ��޷��ţ�����һ�����ݣ��޷��ţ��������̴�����һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* divU256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* ��һ�����ݣ��з��ţ�����һ�����ݣ��з��ţ��������̴�����һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* div256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* ��һ�����ݣ��޷��ţ�����һ�����ݣ��޷��ţ��������ഢ����һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* modU256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* ��һ�����ݣ��з��ţ�����һ�����ݣ��з��ţ��������ഢ����һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* mod256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* ��һ�����ݣ��޷��ţ�����һ�����ݣ��޷��ţ����������������һ���ṹ�У�����ֵΪ���ָ��.
*/
extern my256div_t* divUAll256(const unsigned int* value1, const unsigned int* value2, my256div_t* result);

/*
* ��һ�����ݣ��з��ţ�����һ�����ݣ��з��ţ����������������һ���ṹ�У�����ֵΪ���ָ��.
*/
extern my256div_t* divAll256(const unsigned int* value1, const unsigned int* value2, my256div_t* result);

//======================================================================================================================================================λ����


/*
* ��һ�������Զ�������ʽ��λȡ������������һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* r256(const unsigned int* value1, unsigned int* result);

/*
* �����������Զ�������ʽ��λ�룬��������һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* and256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* �����������Զ�������ʽ��λ�򣬲�������һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* or256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

/*
* �����������Զ�������ʽ��λ��򣬲�������һ������У�����ֵΪ���ָ��.
*/
extern unsigned int* xor256(const unsigned int* value1, const unsigned int* value2, unsigned int* result);

//======================================================================================================================================================�Բ���


/*
* ��һ������λ����һ������������������ڵ�һ�����У�����ֵΪ���ָ��.
*/
extern unsigned int* iand256(unsigned int* self, const unsigned int* value2);

/*
* ��һ������λ����һ������������������ڵ�һ�����У�����ֵΪ���ָ��.
*/
extern unsigned int* ior256(unsigned int* self, const unsigned int* value2);

/*
* ��һ������λ�����һ������������������ڵ�һ�����У�����ֵΪ���ָ��.
*/
extern unsigned int* ixor256(unsigned int* self, const unsigned int* value2);

/*
* ��һ������λȡ����������������������У�����ֵΪ���ָ��.
*/
extern unsigned int* ir256(unsigned int* value1);

/*
* �Լ����൱��--������ֵΪ���ָ��.
*/
extern unsigned int* iss256(unsigned int* value1);

/*
* �������൱��++������ֵΪ���ָ��.
*/
extern unsigned int* ipp256(unsigned int* value1);

/*
* ������ӣ�������������ڵ�һ�����У� �൱�� += ������ֵΪ���ָ��.
*/
extern unsigned int* ipa256(unsigned int* self, const unsigned int* value1);

/*
* һ������ȥһ������������������ڵ�һ�����У� �൱�� -= ������ֵΪ���ָ��.
*/
extern unsigned int* isa256(unsigned int* self, const unsigned int* value1);

/*
* ������ˣ�������������ڵ�һ�����У��൱�� *= ������ֵΪ���ָ��.
*/
extern unsigned int* ima256(unsigned int* self, const unsigned int* value1);

/*
* һ�������޷��ţ�����һ�������޷��ţ��������̴����ڵ�һ�����У��൱�� /= ������ֵΪ���ָ��. 
*/
extern unsigned int* idaU256(unsigned int* self, const unsigned int* value1);

/*
* һ�������з��ţ�����һ�������з��ţ��������̴����ڵ�һ�����У��൱�� /= ������ֵΪ���ָ��.
*/
extern unsigned int* ida256(unsigned int* self, const unsigned int* value1);

/*
* һ�������޷��ţ�����һ�������޷��ţ��������ഢ���ڵ�һ�����У��൱�� %= ������ֵΪ���ָ��.
*/
extern unsigned int* imodaU256(unsigned int* self, const unsigned int* value1);

/*
* һ�������з��ţ�����һ�������з��ţ��������ഢ���ڵ�һ�����У��൱�� %= ������ֵΪ���ָ��.
*/
extern unsigned int* imoda256(unsigned int* self, const unsigned int* value1);

/*
* ��һ�������Զ�������ʽ����nλ���ұ߳��ֵĿ�λȡ0 ������ֵΪ���ָ��.
*/
extern unsigned int* ilsn256(unsigned int* self, int n);

/*
* ��һ�������Զ�������ʽ����nλ���ұ߳��ֵĿ�λȡֵ����Ϊ�����з����ӽǣ������λΪ��ֵ����ȡ1 ������ȡ0 ������ֵΪ���ָ��.
*/
extern unsigned int* irsn256(unsigned int* self, int n);

/*
* ��һ�������Զ�������ʽ����nλ���ұ߳��ֵĿ�λȡ0 ������ֵΪ���ָ��.
*/
extern unsigned int* irsnU256(unsigned int* self, int n);

//======================================================================================================================================================������


/*
* ��һ�������Զ�������ʽ����nλ���ұ߳��ֵĿ�λȡ0 ��������������ڽ���У�����ֵΪ���ָ��.
*/
extern unsigned int* lefts256(const unsigned int* value, int n, unsigned int* result);

/*
* ��һ�������Զ�������ʽ����nλ���ұ߳��ֵĿ�λȡֵ����Ϊ�����з����ӽǣ������λΪ��ֵ����ȡ1 ������ȡ0 ��������������ڽ���У�����ֵΪ���ָ��.
*/
extern unsigned int* rights256(const unsigned int* value, int n, unsigned int* result);

/*
* ��һ�������Զ�������ʽ����nλ���ұ߳��ֵĿ�λȡ0 ��������������ڽ���У�����ֵΪ���ָ��.
*/
extern unsigned int* rightsU256(const unsigned int* value, int n, unsigned int* result);

//======================================================================================================================================================�Ƚ�


/*
* ���з����ӽǱȽ��������ݣ�������ȷ��� 0 ��value1 < value2 ���� -1 ��value1 > value2 ���� 1.
*/
extern int cmp256(const unsigned int* value1, const unsigned int* value2);

/*
* ���޷����ӽǱȽ��������ݣ�������ȷ��� 0 ��value1 < value2 ���� -1 ��value1 > value2 ���� 1.
*/
extern int cmpU256(const unsigned int* value1, const unsigned int* value2);

#endif // !__INT256_H__

//======================================================================================================================================================
