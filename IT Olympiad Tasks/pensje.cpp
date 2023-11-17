#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

int numberOfNodes(vector<int>* sons, int start);

void markTheSalaries(vector<int>* sons, vector<int>* M, int v, int *salary);

int main() {
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	int* parent = new int[n+1];
	int* salary = new int[n+1];
	bool* inputSalaries = new bool[n + 1];
	bool* inconclusive = new bool[n + 1];
	vector<pair<int, int>> tree;
	parent[0] = -1, salary[0] = -1;
	for (int i = 1; i <= n; i++) {
		cin >> parent[i] >> salary[i];
		inputSalaries[i] = false;
		inconclusive[i] = false;
	}
	int supervisor;
	for (int i = 1; i <= n; i++) {
		supervisor = parent[i];
		if (supervisor == i) salary[supervisor] = n;
		if (salary[supervisor] != 0 && salary[i] == 0) {
			tree.push_back(make_pair(salary[supervisor], i));
		}
	}
	sort(tree.begin(), tree.end()); 
	stack<int> P, K;
	for (int i = 1; i <= n; i++) {
		inputSalaries[salary[i]] = true;
	}
	for (int i = n; i >0; i--) {
		if (!inputSalaries[i]) {
			P.push(i);
			K.push(i);
		}
	}
	vector<int>* sons = new vector<int>[n + 1];
	for (int i = 1; i <= n; i++) {
		if (i != parent[i]) sons[parent[i]].push_back(i);
	}
	vector<int> M;
	int t;
	for (int i = 0; i < tree.size(); i++) {
		t = numberOfNodes(sons, tree.at(i).second);
		for (int j = 0; j < t; j++) {
			if (K.size() > 0) { 
				M.push_back(K.top());
				K.pop();
			}
		}
		if (K.empty() || K.top() > tree.at(i).first) {
			markTheSalaries(sons, &M, tree.at(i).second, salary);
		}
		while (!P.empty() && P.top() < tree.at(i).first) {
			if(!K.empty() && K.top() <= tree.at(i).first) inconclusive[P.top()] = true;
			P.pop();
		}
	}
	for (int i = 1; i <= n; i++) {
		if (inconclusive[salary[i]]) cout << 0 << "\n";
		else cout << salary[i] << "\n";
	}
	delete[] parent;
	delete[] salary;
	delete[] inconclusive;
	delete[] inputSalaries;
	delete[] sons;
}

int numberOfNodes(vector<int>* sons, int start) {
	int output = 1;
	for (int i = 0; i < sons[start].size(); i++) {
		output += numberOfNodes(sons, sons[start].at(i));
	}
	return output;
}

void markTheSalaries(vector<int>* sons, vector<int>* M, int start, int* salary) {
	salary[start] = M->back();
	M->pop_back();
	if (sons[start].size() == 1) {
		markTheSalaries(sons, M, sons[start].at(0), salary);
	}
}