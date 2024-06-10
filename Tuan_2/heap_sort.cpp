void Shift(float a[SIZE], int start, int end){
    int rootIndex = start;
    int childNode = rootIndex * 2 - 1;
    while(childNode <= end){
        if((childNode < end) && (a[childNode] < a[childNode+1])) childNode++;
        if(a[rootIndex] > a[childNode]) break;
        swap(a[rootIndex], a[childNode]);
        rootIndex = childNode;
        childNode = rootIndex * 2 + 1;
    }
}

void createHeap(float a[SIZE], int n=SIZE){
    int start = n - 1 / 2;
    while(start >= 0){
        Shift(a, start, n);
        start--;
    }
}

void heapSort(float a[SIZE], int n = SIZE){
    createHeap(a, n);
    int end = n - 1;
    while(end > 0){
        swap(a[0], a[end]);
        end--;
        Shift(a, 0, end);
    }
}
