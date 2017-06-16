#include <iostream>
#include <string>
#include <cmath>
#include <vector>

/************************************************************************************
���l���͕�
************************************************************************************/
int input(void) {
	int num;
	//�����Ɛ��l������܂�
	while (true) {
		std::cout << "\nx^2 - by^2 = 1�@��b�̒l����� > ";
		//���l���������ǂ���
		if (std::cin >> num){
			//���̐��l�̂Ƃ��Ƀ��[�v����o��
			if (num > 0){break;}else{std::cout << "���̐�������͂��Ă�������\n";}
		}
		else{
			//��������Ȃ������ꍇ
			std::cout << "��������Ȃ������I\n";
		}
		//���������͂���Ȃ������ꍇ���͂����Z�b�g
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
	return num;
}

/************************************************************************************
x^2 - Ay^2 = 1�̉����v�Z
�A���S���Y���ɂ��Ă�
�y��������
http://izumi-math.jp/sanae/MyText/number/number_05.pdf
���Q��
************************************************************************************/
bool calc(std::vector<int> ans, int num, unsigned long long *a, unsigned long long *b) {
	unsigned long long pn, qn, pn1=1, qn1=0;
	//�����v�Z
	int loop, cycle = ans.size() - 1;
	//��������ł���Ƃ� = 1�̉���2m-1�v�Z���Ȃ��Ƃ����Ȃ��D�����ł���Ƃ���m-1�ł悢
	loop = ((cycle % 2) == 1) ? 2 * cycle - 1 : cycle - 1;
	for (int i = loop-1; i >= 0; i--) {
		pn = ans[i%cycle + 1] * pn1 + qn1;
		qn = pn1;
		pn1 = pn;
		qn1 = qn;
	}
	//�Ō�ɐ�������
	*a = ans[0] * pn1 + qn1;
	*b = pn1;
	//x^2 - Ay^2 = -1�̉������݂��邩�ǂ���
	return (cycle % 2) == 1;
}

/************************************************************************************
x^2 - Ay^2 = -1�̉����v�Z
�A���S���Y���ɂ��Ă�
�y��������
http://izumi-math.jp/sanae/MyText/number/number_05.pdf
���Q��
************************************************************************************/
void calc_other(std::vector<int> ans, int num, unsigned long long *a, unsigned long long *b) {
	unsigned long long pn, qn, pn1, qn1;
	int loop, cycle = ans.size() - 1;
	loop = cycle - 1;
	pn1 = 1;
	qn1 = 0;
	for (int i = loop - 1; i >= 0; i--) {
		pn = ans[i%cycle + 1] * pn1 + qn1;
		qn = pn1;
		pn1 = pn;
		qn1 = qn;
	}
	*a = ans[0] * pn1 + qn1;
	*b = pn1;
}

/************************************************************************************
/�A�����W�J
�A���S���Y���ɂ��Ă�
Lagrange �ɂ��A�����W�J�̃A���S���Y���̈�ʉ��̎���
http://www.kurims.kyoto-u.ac.jp/~kyodo/kokyuroku/contents/pdf/1199-22.pdf
���Q��
************************************************************************************/
std::vector<int> continued_fraction(int num) {
	int Pk = 0, Pk1, Qk = 1, Qk1, ak, TP, TQ, rootnum;
	std::vector<int> ans;
	bool f = true;
	//�����������v�Z
	rootnum = (int)sqrt(num);
	ak = rootnum;
	//���l�ۑ�
	ans.push_back(ak);
	//�v�Z��
	while (true) {
		Pk1 = ak*Qk - Pk;
		Qk1 = (num - Pk1*Pk1) / Qk;
		if (f) {
			//�z����ꍇ�ŏ��ɖ߂�̂ōŏ��̒l��ۑ�
			TP = Pk1, TQ = Qk1;
			f = false;
		} else {
			//�z�����ꍇ���[�v���甲����
			if (TP == Pk1 && TQ == Qk1) break;
		}
		ak = (int)((Pk1 + rootnum) / Qk1);
		Pk = Pk1;
		Qk = Qk1;
		//���l�ۑ�
		ans.push_back(ak);
	}
	return ans;
}

//�v�Z�{��
void pell(int num){
	std::vector<int> ans;
	//�A�������v�Z
	ans = continued_fraction(num);
	unsigned long long pn, qn;
	//�y���������̉����v�Z
	bool other = calc(ans, num, &pn, &qn);
	std::cout << "x^2 - " + std::to_string(num) + "y^2 = 1�̔񎩖��ŏ���(x,y)��\n(" + std::to_string(pn) + "," + std::to_string(qn) + ")\n�ł�" << std::endl;
	//x^2 - Ay^2 = -1�̉������݂���ꍇ�v�Z 
	if (other){
		calc_other(ans, num, &pn, &qn);
		std::cout << "�܂��Cx^2 - " + std::to_string(num) + "y^2 = -1�̔񎩖��ŏ���(x,y)��\n(" + std::to_string(pn) + "," + std::to_string(qn) + ")\n�ł�" << std::endl;
	}
}

//�v�Z
void solution(int num){
	//�������̐�������
	int c = (int)sqrt(num);
	if (c*c == num) {
		//���͒l���������̏ꍇ
		std::cout << "�񎩖����͂���܂���" << std::endl;
	}
	else {
		//���͒l���������łȂ��ꍇ
		pell(num);
	}
	std::cout << "\n";
}


int main(void) {

	while (true){
		int num = input();
		if (num < 0)break;
		solution(num);
	}

	return 0;
}
