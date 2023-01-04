# Midterm
程式碼的部分用 ChatGPT 產生後，看懂了，修改格式後就繳交了，在提問時若問ChatGPT frcational knapsack problem如何解給出的答案會是錯的，他會給出與0/1同樣的code，也就是一樣使用dp策略，需要引導它用greedy策略解才會給正確的程式碼。

除了程式碼的部分，其他為讀參考資料吸收後自己想的。
## knapsack problem
knapsack problem 就是背包問題，旨在探討如何在限定條件下，使得背包內容物的部分屬性達到最大值/最小值。

最常見的問題為給定一些物品，不同物品的重量與價值不一樣，再給定一個背包，限制其可以負荷的重量，在滿足負荷重量的條件下，尋求價值的最大值。

在上述條件下又分為fractional以及0/1的背包問題
* fractional如同名字所述，物品是可以拆分的，所以不必拿完整的(不過還是可以拿完整的)
* 0/1 亦即每一個物品必須完整的拿，不可以是分數

## Fractional knapsack
使用greedy 策略 
算出價值/重量比之後，優先選價值/重量比高的物品，直到選完為止
```python
def fractional_knapsack(weights, values, capacity):
    # 計算每個物品的價值/重量比
    ratio = [v / w for v, w in zip(values, weights)]
    # 按照價值/重量比從大到小排序
    items = sorted(zip(ratio, weights, values), key=lambda x: x[0], reverse=True)
    
    max_value = 0
    for r, w, v in items:
        if capacity >= w:
            # 背包容量夠放下整個物品，將物品全部放入背包
            capacity -= w
            max_value += v
        else:
            # 背包容量不夠放下整個物品，只能放一部分
            max_value += capacity * r
            break
    
    return max_value

weights = [1, 2, 3]
values = [6, 10, 12]
capacity = 5
max_value = knapsack(weights, values, capacity)
print(max_value)  # 輸出 22

```

## 0/1 knapsack
使用dp策略
```python
def knapsack(weights, values, capacity):
    # 創建一個二維數組 dp，其中 dp[i][j] 表示考慮前 i 個物品，且背包容量為 j 時的最大價值。
    dp = [[0] * (capacity + 1) for _ in range(len(weights) + 1)]

    for i in range(1, len(weights) + 1):
        for j in range(1, capacity + 1):
            if j >= weights[i - 1]:
                # 背包容量夠放下第 i 個物品，比較放和不放的情況
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + values[i - 1])
            else:
                # 背包容量不夠放下第 i 個物品，只能不放
                dp[i][j] = dp[i - 1][j]
    
    return dp[-1][-1]

weights = [1, 2, 3]
values = [6, 10, 12]
capacity = 5
max_value = knapsack(weights, values, capacity)
print(max_value)  # 輸出 22
```

要注意的是，使用dp後的0/1 knapsack 看起來是 O(n*W)是polymial實際上是錯的

是pseudo-polynomial才對(n是物品的數量，W是容量的最大值)

* n是輸入的物品數亦即n本身就是input size

* W為容量大小，但W本身並非input size，要用binary轉換後才是實際的input size(計算機底層使用 binary)，也就是當W為10的時候，實際的input size為1024

所以實際的complexity為 O(n*2^x)

因此0/1knapsack 是NPC問題

------
## 參考資料
http://www.derf.net/knapsack/#KnapNP
https://stackoverflow.com/questions/3907545/how-to-understand-the-knapsack-problem-is-np-complete
https://www.zhihu.com/question/20686504
https://web.ntnu.edu.tw/~algo/KnapsackProblem.html