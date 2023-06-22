#include <iostream>
#include <random>
#include <map>
#include <unordered_map>
// #include <unordered_multimap>
using namespace std;

static random_device rd;
static default_random_engine generator(rd());
const int testCount = 10000000;

int zeroToOne()
{

    uniform_int_distribution distribution(1, 5);
    int ans = 3;
    while (ans == 3)
    {
        ans = distribution(generator);
    }
    return ans > 3 ? 1 : 0;
}

// 得到000-111做到等概率
int zeroToSeven()
{
    int ans = (zeroToOne() << 2) + (zeroToOne() << 1) + zeroToOne();
    return ans;
}

int oneToSix()
{
    int ans = 7;
    // 如果是7重新随机
    while (ans == 7)
    {
        ans = zeroToSeven();
    }
    // ans [0-6]

    // 返回结果[1-7]
    return ans + 1;
}

void test1()
{

    int a[7] = {0};
    for (int i = 0; i < testCount; i++)
    {
        /* code */
        int num = oneToSix();
        a[num]++;
    }

    for (int i = 1; i < 7; i++)
    {
        /* code */
        cout << double(a[i]) / (double)testCount << endl;
    }
}

// 不等概率的随机数
int f1()
{
    uniform_real_distribution<double> distribution(0, 1);
    double d = distribution(generator);
    return d < 0.85 ? 0 : 1;
}

int zeroToOneEql()
{
    int ans = 0;
    do
    {
        ans = f1();
    } while (ans == f1());

    return ans;
}

void test2()
{
    int a = 0;
    for (int i = 0; i < testCount; i++)
    {
        /* code */
        if (zeroToOneEql() == 0)
            a++;
    }
    cout << (double)a / (double)testCount << endl;
    cout << (double)(testCount - a) / (double)testCount << endl;
}

int mostLeftIndex(int a[], int num, int target)
{
    if (a == nullptr || num == 0)
        return -1;

    int left = 0;
    int right = num - 1;
    int t = -1;
    while (left <= right)
    {
        int mid = (right + left) / 2;
        if (a[mid] > target)
        {
            right = mid - 1;
            // t = mid;
        }
        else if (a[mid] <= target)
        {
            left = mid + 1;
            t = mid;
        }
    }

    return t;
}

// >= num最左侧 or <= num左右侧
void test3()
{
    int a[9] = {0, 1, 2, 2, 2, 2, 6, 7, 8};

    cout << mostLeftIndex(a, 9, 2) << endl;
}

// 无序 相邻不等
int minPart(int a[], int num)
{
    if (a == nullptr)
        return -1;
    else if (num == 1)
        return a[0];

    if (a[0] < a[1])
        return 0;
    else if (a[num - 1] < a[num - 2])
        return num - 1;

    int min = 1;
    for (int i = 2; i < num; ++i)
    {
        if (a[i] > a[min])
        {
            // min = i;
            break;
        }
        else if (a[i] < a[min])
        {
            min = i;
        }
    }

    return min;
}

int minPartBS(int a[], int num)
{
    if (a == nullptr || num == 0)
        return -1;
    else if (num == 1)
        return 0;

    if (a[0] < a[1])
        return 0;
    else if (a[num - 1] < a[num - 2])
        return num - 1;

    int l = 0;
    int r = num - 1;
    int ans = -1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (a[mid] < a[mid - 1] && a[mid] < a[mid + 1])
        {
            ans = mid;
            break;
        }
        else if (a[mid] > a[mid - 1])
        {
            r = mid - 1;
        }
        else if (a[mid] > a[mid + 1])
        {
            l = mid + 1;
        }
    }
    return ans;
}

// 返回一个局部最小
void test4()
{
    int a[10] = {8, 7, 6, 5, 4, 3, 2, 1, 8, 9};

    // cout << minPart(a, 10);
    cout << minPartBS(a, 10);
}

void test5()
{
    map<string, string> mmap;
    string a = "aaa";
    mmap.insert(pair<string, string>("aaa", "b"));
    auto r = mmap.find(a);
    cout << r->second << endl;

    int a1 = 123456;
    int a2 = 123456;
    cout << (&a1 == &a2) << endl;
}

class Node
{
    int value;

public:
    Node(int value) : value(value) {}

    bool operator<(const Node &other) const
    {
        return value < other.value;
    }
};

void test6()
{
    map<Node, int> mmap;
    Node node1 = Node(1);
    mmap.insert(pair<Node, int>(node1, 1));
}

class BitMap
{
    long *bits;

public:
    BitMap(int max)
    {
        bits = new long[(max + 64) >> 6];
    }
    ~BitMap()
    {
        delete[] bits;
    }

    void add(int num)
    {
        bits[num >> 6] |= (1l << (num & 63));
    }

    void remove(int num)
    {
        bits[num >> 6] &= ~(1l << (num & 63));
    }

    bool contains(int num)
    {
        return ((bits[num >> 6]) & (1l << (num & 63))) != 0;
    }
};

void test7()
{
    BitMap bitmap(100);

    // 添加数字 3
    bitmap.add(3);

    // 检查数字 3 是否存在
    bool containsThree = bitmap.contains(3);
    std::cout << "Contains 3: " << std::boolalpha << containsThree << std::endl;

    // 检查数字 5 是否存在
    bool containsFive = bitmap.contains(5);
    std::cout << "Contains 5: " << std::boolalpha << containsFive << std::endl;

    // 移除数字 3
    bitmap.remove(3);

    // 再次检查数字 3 是否存在
    containsThree = bitmap.contains(3);
    std::cout << "Contains 3: " << std::boolalpha << containsThree << std::endl;
}

// int add(int a, int b) {
//     while (b != 0) {
//         int carry = (unsigned int)(a & b) << 1;
//         a = a ^ b;
//         b = carry;
//     }
//     return a;
// }
int add(int x, int y)
{
    int sum = x;
    while (y != 0)
    {
        // 异或运算
        sum = x ^ y;
        // 与运算找进位
        y = (x & y) << 1;
        x = sum;
    }
    return sum;
}

int neg(int x, int y)
{
    return add(x, add(~y, 1));
}

int mult(int x, int y)
{
    int ans = 0;
    bool negative = false;

    if ((x < 0 && y > 0) || (x > 0 && y < 0))
    {
        negative = true;
    }

    if (x < 0)
    {
        x = neg(0, x); // 取负数的绝对值
    }

    if (y < 0)
    {
        y = neg(0, y); // 取负数的绝对值
    }

    while (y != 0)
    {
        if (y & 1)
        {
            ans = add(ans, x);
        }
        x <<= 1;
        y >>= 1;
    }

    if (negative)
    {
        ans = neg(0, ans); // 将结果转换回原来的符号表示
    }

    return ans;
}

bool isNeg(int n)
{
    return n < 0;
}

int divi(int a, int b)
{
    int x = isNeg(a) ? neg(0, a) : a;
    int y = isNeg(b) ? neg(0, b) : b;
    int res = 0;

    for (int i = 30; i >= 0; i = neg(i, 1))
    {
        if ((x >> i) >= y)
        {
            res |= (1 << i);
            x = neg(x, y << i);
        }
    }
    return isNeg(a) ^ isNeg(b) ? neg(0, res) : res;
}

// 处理所有情况
// 尤其包含系统最小值INT_MIN这种情况，因为INT_MIN的绝对值比INT_MAX大1
int divide(int x, int y)
{
    // 如果2个都是系统最小值返回1
    if (x == INT_MIN && y == INT_MIN)
        return 1;
    // 如果y是系统最小值返回0
    else if (y == INT_MIN)
        return 0;
    // 如果x是系统最小值
    else if (x == INT_MIN)
    {
        if (y == neg(0, 1))
            return INT_MAX;
        else
        {
            int c = divi(add(x, 1), y);
            return add(c, divi(neg(x, mult(c, y)), y));
        }
    }
    // 两个都不是系统最小值
    else
    {
        return divi(x, y);
    }
}

void test8()
{
    cout << "================================\n";
    cout << add(46, 20) << endl;
    cout << neg(46, 20) << endl;
    cout << mult(46, -20) << endl;
    cout << divide(-2147483648, 1) << endl;

    cout << INT_MIN << endl;
    cout << -INT_MIN << endl;
}

void mergeSort(vector<int>& v1, int l, int r) {
    if(l == r) return;
    int mid = l + (l-r)>>1;
    mergeSort(v1, l, mid);
    mergeSort(v1, mid+1, r);
    merge(v1, l, mid, r);
}

void merge(vector<int>& v1, int l, int m, int r) {
    vector<int> help(r-l+1);
    int i = 0;
    int p1 = l;
    int p2 = m + 1;
    while(p1<=m && p2<=r) {
        help[i++] = v1[p1]<=v1[p2] ? v1[p1++]:v1[p2++];
    }
    while(p1<=m)
        help[i++]=v1[p1++];
    while (p2<=r)
        help[i++]=v1[p2++];
    for(int i=0; i<help.size(); ++i)
        v1[l+i] = help[i];
    
}

void test9() {
    
}

int main()
{

    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    // test7();
    // test8();

    // cout << sizeof(int)*8 << endl;
    // cout << sizeof(long)*8 << endl;

    return 0;
}
