#include <iostream>
#include <stack>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	stack<int> stack;
	int n, width, height, posters = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> width >> height;
		while (!stack.empty()) {
			if (stack.top() > height) {
				stack.pop();
			}
			else break;
		}
		if (stack.empty()) {
			posters++;
			stack.push(height);
		}
		else if (stack.top() < height) {
			posters++;
			stack.push(height);
		}
	}
	cout << posters;
	return 0;
}