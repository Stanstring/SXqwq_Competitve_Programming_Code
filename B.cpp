#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

// 计算序列的最大值，按照左到右的顺序插入加号或乘号
long long calculate_max_value(const vector<int>& a) {
    int n = a.size();
    long long dp = a[0];
    dp %= MOD;
    for(int i = 1; i < n; ++i){
        long long add_op = (dp + (long long)a[i]) % MOD;
        long long mul_op = (dp * (long long)a[i]) % MOD;
        dp = max(add_op, mul_op);
    }
    return dp;
}

// 计算重新排列序列后的最大值
long long calculate_reordered_max(vector<int> a) {
    // 分离所有的1
    vector<int> ones;
    vector<int> others;
    for(auto x : a){
        if(x == 1){
            ones.push_back(x);
        }
        else{
            others.push_back(x);
        }
    }
    // 将其他元素按降序排列
    sort(others.begin(), others.end(), [&](const int &x, const int &y) -> bool {
        return x > y;
    });
    // 合并序列：先所有的1，然后按降序的其他元素
    vector<int> reordered;
    for(auto x : ones){
        reordered.push_back(x);
    }
    for(auto x : others){
        reordered.push_back(x);
    }
    // 计算重新排列后的最大值
    int n = reordered.size();
    long long dp = reordered[0];
    dp %= MOD;
    for(int i = 1; i < n; ++i){
        long long add_op = (dp + (long long)reordered[i]) % MOD;
        long long mul_op = (dp * (long long)reordered[i]) % MOD;
        dp = max(add_op, mul_op);
    }
    return dp;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        int n, k;
        cin >> n;
        // 根据您最初的问题描述的输入格式，读取n对(l_i, r_i)
        // 然而，后续讨论涉及不同的问题（运算符插入），因此假设当前问题是运算符插入
        // 请根据具体问题调整输入部分
        // 这里假设当前问题是运算符插入，并且输入为单个序列
        // 如果有多组测试数据，请确保每组输入格式一致
        
        // 由于用户的测试用例中没有涉及(l_i, r_i)，假设读取一个序列长度和序列
        // 这里忽略k，因为k与当前的运算符插入问题无关
        // 如果k有特殊意义，请根据题意调整
        // 因为存在混淆，以下代码仅针对运算符插入问题
        
        // 读取序列
        vector<int> a(n);
        for(int i = 0; i < n; ++i){
            cin >> a[i];
        }
        // 计算原始序列的最大值
        long long max_original = calculate_max_value(a);
        // 计算重新排列后的最大值
        long long max_reordered = calculate_reordered_max(a);
        // 输出结果
        cout << max_original << " " << max_reordered << "\n";
    }
    return 0;
}