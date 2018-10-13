#include <stdio.h>
#include <stdlib.h>

struct index{
	int a;
	int b;
};

int find_pivot_index(int *L, int l, int r){
	int a, b, c;
	
	/* debug */
	//printf("[debug] finding key... %d\n", r-l+1);
	
	/* 랜덤한 인덱스 */
	a = rand()%(r-l+1)+l;
	b = rand()%(r-l+1)+l;
	c = rand()%(r-l+1)+l;
	while(b == a)
		b = rand()%(r-l+1)+l;
	while(c == a || c == b)
		c = rand()%(r-l+1)+l;
	
	/* debug */
	//printf("[debug] a = %d, b = %d c = %d\n", a, b, c);
	
	/* 중간값 반환 */
	if(L[a] < L[b])
		if(L[a] < L[c])
			return L[b] < L[c] ? b : c;
		else
			return a;
	else if(L[a] > L[c])
		return L[b] > L[c] ? b : c;
	else
		return a;
}

void swap(int *L, int s, int d){
	int tmp;
	
	tmp = L[s];
	L[s] = L[d];
	L[d] = tmp;
}

struct index inPlacePartition(int *L, int l, int r, int k){
	
	/* debug */
	/*
	printf("[debug] inPlacePartition l = %d, r = %d, k = %d, key = %d\n", l, r, k, L[k]);
	int debug = 0;
	printf("[debug] ");
	for(debug = l; debug <= r; debug++){
		printf(" %d", L[debug]);
	}
	puts("");
	*/
	
	struct index R;
	int pivot = L[k];
	int i = l, j = r-1;
	
	swap(L, k, r);
	k = r;
	
	while(i <= j){
		
		/* i 또는 j가 k와 같을 경우 */
		if(L[i] == L[k]){
			if(j == k-1)
				j--;
			swap(L, i, --k);
		}
		if(L[j] == L[k]){
			if(j == k-1)
				j--;
			else
				swap(L, j, --k);
		}
		
		/* i 와 j 가 규칙을 배반할 경우 */
		if(L[i] > L[k] && L[j] < L[k])
			swap(L, i, j);
		
		/* i 또는 j가 규칙을 만족할 경우 */
		if(L[i] < L[k])
			i++;
		if(L[j] > L[k])
			j--;
		
		/* debug */
		/*
		printf("[debug] i = %d, j = %d, k = %d\n", i, j, k);
		printf("[debug] ");
		for(debug = l; debug <= r; debug++){
			printf(" %d", L[debug]);
		}
		puts("");
		*/
	}
	
	R.a = i;
	
	/* 피벗 위치 복구 */
	while(k <= r){
		swap(L, i++, k++);
	}
	R.b = i-1;
	
	/* debug */
	/*
	printf("[debug] ");
	for(debug = l; debug <= r; debug++){
		printf(" %d", L[debug]);
	}
	puts("");
	*/
	
	return R;
}

void inPlaceQuickSort(int *L, int l, int r){
	
	/* debug */
	//printf("[debug] QuickSort l = %d, r = %d\n", l, r);
	
	if(l+1 == r){
		if(L[l] > L[r])
			swap(L, l, r);
		return;
	}
	
	if(l >= r)
		return;
	
	int k;
	struct index I;
	
	k = find_pivot_index(L, l, r);
	
	/* debug */
	//printf("[debug] key = %d\n", k);
	
	I = inPlacePartition(L, l, r, k);
	
	inPlaceQuickSort(L, l, I.a-1);
	inPlaceQuickSort(L, I.b+1, r);
}

int main(){
	int N, i;
	int data;
	int *L;
	
	srand(time(NULL));
	
	scanf("%d", &N);
	
	L = (int *)malloc(N*sizeof(int));
	
	for(i = 0; i < N; i++){
		scanf("%d", &data);
		L[i] = data;
	}
	
	inPlaceQuickSort(L, 0, N-1);
	
	for(i = 0; i < N; i++)
		printf(" %d", L[i]);
	puts("");
}