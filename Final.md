# Bellman–Ford演算法
參考自維基百科100%理解
## 一、簡介
&emsp;&emsp;求解單源最短路徑問題的一種演算法。
其優於dijkstra algorithm演算法的方面是邊的權值可以為負數、實現簡單，缺點是時間複雜度過高，高達O(|V||E|)。
演算法可以進行若干種最佳化，提高了效率。

### NOTE
> 複雜度
>1. 最壞時間複雜度	O(|V||E|)
>2. 最佳時間複雜度	Θ(|E|)
>3. 空間複雜度	O(|v|)

## 二、演算法
 
>1. 與dijkstra algorithm類似，都以release操作為基礎，即估計的最短路徑值漸漸地被更加準確的值替代，直至得到最佳解。
>2. 兩個演算法中，計算時每個邊之間的估計距離值都比真實值大，並且被新找到路徑的最小長度替代。
>3. dijkstra algorithm以greddy method選取未被處理的具有最小權值的節點，然後對其的出邊進行release操作。
>4. 在重複地計算中，已計算得到正確的距離的邊的數量不斷增加，直到所有邊都計算得到了正確的路徑。
>5. 這樣的策略使得Bellman-ford algorithm比dijkstra algorithm適用於更多種類的輸入。

### psudo code
```
procedure BellmanFord(list vertices, list edges, vertex source)
   // 讀入邊和節點的列表並對distance和predecessor寫入最短路徑

   // 初始化圖
   for each vertex v in vertices:
       if v is source then distance[v] := 0
       else distance[v] := infinity
       predecessor[v] := null

   // 對每一條邊重複操作
   for i from 1 to size(vertices)-1:
       for each edge (u, v) with weight w in edges:
           if distance[u] + w < distance[v]:
               distance[v] := distance[u] + w
               predecessor[v] := u

   // 檢查是否有負權重的回路
   for each edge (u, v) with weight w in edges:
       if distance[u] + w < distance[v]:
           error "圖包含負權重的回路"
```

## 三、原理
### (一)迴圈
>&emsp;&emsp;每次迴圈操作實際上是對相鄰節點的存取，第n次迴圈操作保證了所有深度為n的路徑最短。由於圖的最短路徑最長不會經過超過|V|-1條邊，所以可知bellman-ford algorithm所得為最短路徑。
### (二)負邊權操作
>&emsp;&emsp;與dijkstra algorithm不同的是，dijkstra algorithm的基本操作「拓展」是在深度上尋路，而「relase」操作則是在廣度上尋路，這就確定了bellman-ford algorithm可以對負邊進行操作而不會影響結果。
### (三)負權環判定
>&emsp;&emsp;因為負權環可以無限制的降低總花費，所以如果發現第n次操作仍可降低花銷，就一定存在負權環。

## 四、尋找負迴路
>&emsp;&emsp;當使用這個演算法尋找最短路徑時，有負迴路會使演算法找不到正確的答案。但是，由於在找到負迴路後會中止演算法，所以可以被用來尋找目標，例如在網路流分析中的消圈演算法

## 五、最佳化
>### 迴圈的提前跳出
>在實際操作中，bellman-ford algorithm經常會在未達到|V|-1次前就出解，|V|-1其實是最大值。於是可以在迴圈中設定判定，在某次迴圈不再進行release時，直接跳出迴圈，進行負權環判定。

## C++語言範例
```cpp
int SPFA(int s) {
	std::queue<int> q;
	bool inq[maxn] = {false};
	for(int i = 1; i <= N; i++) dis[i] = 2147483647;
	dis[s] = 0;
	q.push(s); inq[s] = true;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		inq[x] = false;
		for(int i = front[x]; i !=0 ; i = e[i].next) {
			int k = e[i].v;
			if(dis[k] > dis[x] + e[i].w) {
				dis[k] = dis[x] + e[i].w;
				if(!inq[k]) {
					inq[k] = true;
					q.push(k);
				}
			}
		}
	}
	for(int i =  1; i <= N; i++) std::cout << dis[i] << ' ';
	std::cout << std::endl;
	return 0;
}
```

### 參考資料
&emsp;&emsp;維基百科