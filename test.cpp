#include <cmath>
#include <random>
#include <iostream>

using namespace std;

void test() {
    random_device rd;
    default_random_engine generator(rd());
    normal_distribution<double> distribution(0, 1);

    const int numSamples = 1000;
    int values[numSamples] = {0};

    for (int i = 0; i < numSamples; i++) {
        int randomNumber = static_cast<int>(distribution(generator));
        values[i] = randomNumber;
    }

    // 统计各个数值出现的频率
    int frequencies[10] = {0};
    for (int i = 0; i < numSamples; i++) {
        int value = values[i];
        frequencies[value + 5]++;
    }

    // 输出频率直方图
    for (int i = 0; i < 10; i++)
    {
        /* code */
        cout << i - 5 << ": ";
        for (int j = 0; j < frequencies[i]; j++) {
            cout << "*";
        }
        cout << endl;
    }
}

int zeroToOne() {
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution distribution(1, 5);
    int ans = 3;
    while(ans==3) {
        ans = distribution(generator);
    }
    return ans>3 ? 1:0;
}

int main(){

    random_device rd;
    default_random_engine generator(rd());;
    uniform_int_distribution distribution(0, 4);
    uniform_real_distribution distributionDouble(0.0, 1.0);
    normal_distribution<double> distributionNormal(0, 1);

    int count = 0;
    const int testCount = 10000000;
    for (int i = 0; i < testCount; i++)
    {
        /* code */
        // cout << distribution(generator) << endl;
        // cout << distributionDouble(generator) << endl;
        // cout << distributionNormal(generator) << endl;
        if(distributionDouble(generator) < 0.3)
            count++;
    }
    
    cout << (double)count / (double)testCount << endl;

    cout << "================================================================" << endl;

    count = 0;
    for (int i = 0; i < testCount; i++)
    {
        /* code */
        double a = distributionDouble(generator);
        double b = distributionDouble(generator);
        double c = distributionDouble(generator);
        // if(max(distributionDouble(generator), distributionDouble(generator)) < 0.9)
        if(max(a, max(b, c)) < 0.3)
            count++;
    }
    cout << (double)count / (double)testCount << endl;
    cout << pow(0.3, 3) << endl;
    
    cout << "================================================================" << endl;

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    for(int i = 0; i < testCount; i++) {
        int ran = distribution(generator);
        if ((ran) == 0)
        {
            a++;
        }
        else if ((ran) == 1) {
            b++;
        }
        else if (ran == 2) {
            c++;
        }
        else if (ran == 3) {
            d++;
        }
        else if (ran == 4) {
            e++;
        }
    }
    cout << (double)a / (double)testCount << endl;
    cout << (double)b / (double)testCount << endl;
    cout << (double)c / (double)testCount << endl;
    cout << (double)d / (double)testCount << endl;
    cout << (double)e / (double)testCount << endl;

    cout << "================================================================\n";

    a=0;b=0;c=0;
    for(int i=0; i<100; i++) {
        int ran = zeroToOne();
        if(ran==0) {
            a++;
        }
        else{
            b++;
        }
    }
    // cout << (double)a / (double)100 << endl;
    // cout << (double)b / (double)100 << endl;
    cout << a << endl;
    cout << b << endl;

    return 0;
}

