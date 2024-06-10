void ShellSort(float a[], int n, unsigned int h[], int k){
    for(int gapIndex = 0; gapIndex < k; gapIndex++){
        int gap = h[gapIndex];
        for(int i = gap; i < n; i++){
            float temp = a[i];
            int pos = i - gap;
            while(pos >= 0 && a[pos] > temp){
                a[pos + gap] = a[pos];
                pos -= gap;
            }
            a[pos + gap] = temp;
        }
    }
}
