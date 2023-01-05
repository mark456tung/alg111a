# 期末報告 — 找質數

## 摘要
此程式為參考leetcode上面的解法 100%理解<br>
比較找質數未建表與建表的效能差異

## 找質數

### 質數(未建表)：[leetcode](https://leetcode.com/playground/PCYvUDEo)

#### 說明

未建表的找質數方法就是當要判斷該數是否為質數時，皆要確認該數是否有1與自己以外的因數，由於因數是成對的，因此只要從2~該數的平方中確認是否有因數即可，雖然這樣已經簡化許多了，但還是一樣耗時。

#### 複雜度

O(n^3/2)

#### 程式

```cpp
bool prime = true;
int sq = sqrt(i);
for (int j=2; j<=sq; j++)
    {
        if (i % j == 0)
        {
            prime = false;
            break;
        }
    }
if(prime)
    cout<<i<<endl;
```
#### 結果 — TLE
<img src=".\src\TLE.png" width = "40%">

### 質數(建表)：[leetcode](https://leetcode.com/playground/fuHr8LKN)

#### 說明

建表的找質數方法就是事先建立一個質數表，當需要判斷該數是否為質數時，便直接從表中確認是否為質數即可，根據建表方法的不同，執行時間也會有所不同，以下利用「厄拉托西尼篩法」進行舉例。

#### 複雜度

![equation](https://latex.codecogs.com/svg.image?O(n*log(log(n))))

#### 程式

利用 eratosthenes 函數建立一個質數表，首先，0、1皆非質數，接著當判斷2為質數時，2*1為自己，把下一個2的倍數開始，2*2、2*3、...、2*10000000都設為非質數；當判斷3為質數時，因為3*1為自己，3*2已經改過了，因此從下一個3的倍數開始，3*3、3*4、...、3*6666666都設為非質數，以此類推，便能建立一張0~20000000的質數表。

```cpp
bool prime[20000000];

void eratosthenes()
{
    for (int i=0; i<num; i++)
        prime[i] = true;
    prime[0] = false;
    prime[1] = false;
    
    int sq = sqrt(num);
    for (int i=2; i<sq; i++)
    {
        if (prime[i])
        {
            for (int j=i*i; j<num; j+=i)
                prime[j] = false;
        }
    }
}
```

當程式執行時，只需要呼叫一次 eratosthenes 函數即可快速建立一張質數表，要判斷該數是否為質數時只要從表中確認即可。

```cpp
int main() {
    eratosthenes();
    for (int i=0; i<num; i++)
    {
        if (prime[i])
            cout<<i<<endl;
    }
}
```
#### 結果 — Success
<img src=".\src\Success.png" width = "40%">

### 複雜度比較

<img src=".\src\O.png" width = "100%">

## 參考資料
[https://zh.wikipedia.org/wiki/%E5%9F%83%E6%8B%89%E6%89%98%E6%96%AF%E7%89%B9%E5%B0%BC%E7%AD%9B%E6%B3%95](https://zh.wikipedia.org/wiki/%E5%9F%83%E6%8B%89%E6%89%98%E6%96%AF%E7%89%B9%E5%B0%BC%E7%AD%9B%E6%B3%95)