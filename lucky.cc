/*
计算从1开始到指定最大值内，的个位数字为指定值的幸运数字之和。
函数第2个参数为最大值范围，第3个参数指定个位数字（0..9）之间的数字。
*/
#include<iostream>
#include<chrono>
#include<ctime>
#include<cstdlib>

using std::cout;
using std::endl;

unsigned long sum_lucky_1(unsigned long max_val, unsigned int lucky_magic)
{
	unsigned long sum = 0;
	unsigned long i;

	cout << "max_val=" << max_val << " luck_magic = " << lucky_magic << endl;
	for (i = 0; i < max_val; i++) {
		if ((i >= lucky_magic) && ((i - lucky_magic) % 10) == 0) {
			sum += i;
		}
	}

	cout << "sum =" <<sum << endl;
	return sum;
}

unsigned long sum_lucky_2(unsigned long max_val, unsigned int lucky_magic)
{
	int a1 = 10*1-(10-lucky_magic);
	unsigned long  an = 10*(max_val/10)-(10-lucky_magic);

	unsigned long sum = 0;

	cout << "max_val=" << max_val << " luck_magic = " << lucky_magic << endl;

	sum = ((a1 + an) * (max_val/10))/2;

	cout << "sum =" <<sum << endl;
	return sum;
}

/*
本文提供了2种方法，当然第1种还可以优化。
第2种方法秒杀了方法1了。
*/
int main(int argc, char *argv[])
{
	cout << "usage: lucky 100 8 " << endl;

	if (argc != 3) {
		cout << "fail to input parameter" << endl;
		return 0;
	}
	unsigned long arg1 = atol(argv[1]);
	unsigned int arg2 = atoi(argv[2]);

	auto now = std::chrono::high_resolution_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::cout << "当前时间: " << std::ctime(&now_c);
	sum_lucky_1(arg1, arg2);

	auto now2 = std::chrono::high_resolution_clock::now();
	std::time_t now_c2 = std::chrono::system_clock::to_time_t(now2);
	std::cout << "当前时间: " << std::ctime(&now_c2);
	sum_lucky_2(arg1, arg2);

	auto now3 = std::chrono::high_resolution_clock::now();
	std::time_t now_c3 = std::chrono::system_clock::to_time_t(now3);
	std::cout << "当前时间: " << std::ctime(&now_c3);
}
