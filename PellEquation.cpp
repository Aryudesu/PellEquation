#include <iostream>
#include <string>
#include <cmath>
#include <vector>

/************************************************************************************
数値入力部
************************************************************************************/
int input(void) {
	int num;
	//ちゃんと数値が入るまで
	while (true) {
		std::cout << "\nx^2 - by^2 = 1　のbの値を入力 > ";
		//数値入ったかどうか
		if (std::cin >> num){
			//正の数値のときにループから出る
			if (num > 0){break;}else{std::cout << "正の整数を入力してください\n";}
		}
		else{
			//数字じゃなかった場合
			std::cout << "数字じゃないじゃん！\n";
		}
		//正しく入力されなかった場合入力をリセット
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
	return num;
}

/************************************************************************************
x^2 - Ay^2 = 1の解を計算
アルゴリズムについては
ペル方程式
http://izumi-math.jp/sanae/MyText/number/number_05.pdf
を参照
************************************************************************************/
bool calc(std::vector<int> ans, int num, unsigned long long *a, unsigned long long *b) {
	unsigned long long pn, qn, pn1=1, qn1=0;
	//周期計算
	int loop, cycle = ans.size() - 1;
	//周期が奇数であるとき = 1の解は2m-1計算しないといけない．偶数であるときはm-1でよい
	loop = ((cycle % 2) == 1) ? 2 * cycle - 1 : cycle - 1;
	for (int i = loop-1; i >= 0; i--) {
		pn = ans[i%cycle + 1] * pn1 + qn1;
		qn = pn1;
		pn1 = pn;
		qn1 = qn;
	}
	//最後に整数部分
	*a = ans[0] * pn1 + qn1;
	*b = pn1;
	//x^2 - Ay^2 = -1の解が存在するかどうか
	return (cycle % 2) == 1;
}

/************************************************************************************
x^2 - Ay^2 = -1の解を計算
アルゴリズムについては
ペル方程式
http://izumi-math.jp/sanae/MyText/number/number_05.pdf
を参照
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
/連分数展開
アルゴリズムについては
Lagrange による連分数展開のアルゴリズムの一般化の試み
http://www.kurims.kyoto-u.ac.jp/~kyodo/kokyuroku/contents/pdf/1199-22.pdf
を参照
************************************************************************************/
std::vector<int> continued_fraction(int num) {
	int Pk = 0, Pk1, Qk = 1, Qk1, ak, TP, TQ, rootnum;
	std::vector<int> ans;
	bool f = true;
	//整数部分を計算
	rootnum = (int)sqrt(num);
	ak = rootnum;
	//数値保存
	ans.push_back(ak);
	//計算部
	while (true) {
		Pk1 = ak*Qk - Pk;
		Qk1 = (num - Pk1*Pk1) / Qk;
		if (f) {
			//循環する場合最初に戻るので最初の値を保存
			TP = Pk1, TQ = Qk1;
			f = false;
		} else {
			//循環した場合ループから抜ける
			if (TP == Pk1 && TQ == Qk1) break;
		}
		ak = (int)((Pk1 + rootnum) / Qk1);
		Pk = Pk1;
		Qk = Qk1;
		//数値保存
		ans.push_back(ak);
	}
	return ans;
}

//計算本体
void pell(int num){
	std::vector<int> ans;
	//連分数を計算
	ans = continued_fraction(num);
	unsigned long long pn, qn;
	//ペル方程式の解を計算
	bool other = calc(ans, num, &pn, &qn);
	std::cout << "x^2 - " + std::to_string(num) + "y^2 = 1の非自明最小解(x,y)は\n(" + std::to_string(pn) + "," + std::to_string(qn) + ")\nです" << std::endl;
	//x^2 - Ay^2 = -1の解が存在する場合計算 
	if (other){
		calc_other(ans, num, &pn, &qn);
		std::cout << "また，x^2 - " + std::to_string(num) + "y^2 = -1の非自明最小解(x,y)は\n(" + std::to_string(pn) + "," + std::to_string(qn) + ")\nです" << std::endl;
	}
}

//計算
void solution(int num){
	//平方根の整数部分
	int c = (int)sqrt(num);
	if (c*c == num) {
		//入力値が平方数の場合
		std::cout << "非自明解はありません" << std::endl;
	}
	else {
		//入力値が平方数でない場合
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
