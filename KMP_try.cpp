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
		//�ӽ���һ���մ�ֱ�ӷ���
		return {};
	}

	vector<int> next(sub_str.size());//���ִ��ĳ��ȳ�ʼ��һ��next����

	//�����ֿ���ֱ�ӷ���
	next[1] = 0;
	if (sub_str.size() == 2) {
		return next;
	}

	next[2] = 1;
	if (sub_str.size() == 3) {
		return next;
	}

	//��ʼ����ִ�
	for (int k = 3; k < sub_str.size(); ++k) {
		if (sub_str[k - 1] == sub_str[next[k - 1]]) {
			//����ʹ�������Ƽ��������˼��,�����ϸ��ַ��������������ַ�
			//����˴��ַ���ǰһ���ַ����ñ��ϸ��ַ���next��Ҫ,����ַ�
			//��next�����һ���ַ�������1
			next[k] = next[k - 1] + 1;
		}
		else {
			//��������ϸ��ַ���next��Ҫ,������Ϊ1
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
				//����ɲ���
				return &main_str[i - j + 1];
			}
			++i;
			++j;
			continue;
		}
		else {
			//����j,�ٴβ���
			j = next_array[j];
		}
	}
	//����ʧ�ܷ���β��ָ��
	return &main_str[main_str.size() - 1];
}

int main() {
	//����ʹ�����������˼��, �ַ�����ʼ�±�Ϊ1
	string main_str = "$googlogoogoogle";
	string sub_str = "$google";

	cout << "����:\t\t";
	print_str(main_str);
	cout << "ģʽ��:\t\t";
	print_str(sub_str);

	auto next_array = build_next_array(sub_str);
	cout << "next����:\t";
	print_vector(next_array);

	auto index = KMP_Match(main_str, sub_str);
	if (index != &main_str[main_str.size() - 1]) {
		//ƥ��ɹ�
		printf("���ҳɹ�, �ִ�����ʼ�±�Ϊ[%d]\n", distance(&main_str[0], index));
	}
	else {
		printf("ƥ��ʧ��\n");
	}

	return EXIT_SUCCESS;
}