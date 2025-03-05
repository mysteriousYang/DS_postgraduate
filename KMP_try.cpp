#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int distance(char* begin, char* end) {
	return end - begin;
}

void print_str(string& str) {
	std::copy(str.begin() + 1, str.end(),
		std::ostream_iterator<char>(cout, " "));
	cout << endl;
}

void print_vector(vector<int>& vec) {
	std::copy(vec.begin() + 1, vec.end(),
		std::ostream_iterator<int>(cout, " "));
	cout << endl;
}

vector<int> build_next_array(string& sub_str) {
	if (sub_str.size() < 2) {
		//扔进来一个空串直接返回
		return {};
	}

	vector<int> next(sub_str.size());//以字串的长度初始化一个next数组

	//这两种可以直接返回
	next[1] = 0;
	if (sub_str.size() == 2) {
		return next;
	}

	next[2] = 1;
	if (sub_str.size() == 3) {
		return next;
	}

	//开始检查字串
	for (int k = 3; k < sub_str.size(); ++k) {
		if (sub_str[k - 1] == sub_str[next[k - 1]]) {
			//这里使用了类似计数排序的思想,根据上个字符的情况处理这个字符
			//如果此处字符的前一个字符正好被上个字符的next需要,则该字符
			//的next相比上一个字符的增加1
			next[k] = next[k - 1] + 1;
		}
		else {
			//如果不被上个字符的next需要,则重置为1
			next[k] = 1;
		}
	}
	return next;
}

char* KMP_Match(string& main_str, string& sub_str) {
	auto next_array = build_next_array(sub_str);
	
	for (int i = 1, j = 1; i < main_str.size();) {
		if (j == 0 || main_str[i] == sub_str[j]) {
			if (j == sub_str.size() - 1) {
				//已完成查找
				return &main_str[i - j + 1];
			}
			++i;
			++j;
			continue;
		}
		else {
			//回溯j,再次查找
			j = next_array[j];
		}
	}
	//查找失败返回尾部指针
	return &main_str[main_str.size() - 1];
}

int main() {
	//这里使用了王道书的思想, 字符串起始下标为1
	string main_str = "$googlogoogoogle";
	string sub_str = "$google";

	cout << "主串:\t\t";
	print_str(main_str);
	cout << "模式串:\t\t";
	print_str(sub_str);

	auto next_array = build_next_array(sub_str);
	cout << "next数组:\t";
	print_vector(next_array);

	auto index = KMP_Match(main_str, sub_str);
	if (index != &main_str[main_str.size() - 1]) {
		//匹配成功
		printf("查找成功, 字串的起始下标为[%d]\n", distance(&main_str[0], index));
	}
	else {
		printf("匹配失败\n");
	}

	return EXIT_SUCCESS;
}