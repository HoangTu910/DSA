void Init_List(List &l){
    l.first = l.last = NULL;
}

int getMaxElement(List list) {
    int max = list.first->data.diemTrungBinh; 
    Node* current = list.first->next; 
    while (current != NULL) {
        if (current->data.diemTrungBinh > max) {
            max = current->data.diemTrungBinh; 
        }
        current = current->next; 
    }
    return max;
}

int getNumbofDigit(int num) {
    if (num == 0) {
        return 1;
    }
    int count = 0;
    while (num != 0) {
        num /= 10; 
        count++;    
    } 
    return count;
}

int GetDigit(unsigned long N, int k) { 
	switch (k) 
	{ 
        case 0: return (N % 10); 
        case 1: return ((N/10) % 10); 
        case 2: return ((N/100) % 10); 
        case 3: return ((N/1000) % 10); 
        case 4: return ((N/10000) % 10); 
        case 5: return ((N/100000) % 10); 
        case 6: return ((N/1000000) % 10); 
        case 7: return ((N/10000000) % 10); 
        case 8: return ((N/100000000) % 10); 
        case 9: return ((N/1000000000) % 10);
        default: break; 
	} 
}

void ListRadixSort(List &iList){
    List B[10];
    Node* p;
    int i, k;
    if(iList.first == NULL || iList.first == iList.last){
        return; 
    }
    int max = getMaxElement(iList);
    int m = getNumbofDigit(max);
    for(i = 0; i < 10; ++i){
        Init_List(B[i]);
    }
    for(k = 0; k < m; ++k){
        for(i = 0; i < 10; ++i){
            Init_List(B[i]);
        }
        while(iList.first){
            p = iList.first;
            iList.first = p->next;
            p->next = NULL;
            i = GetDigit(p->data.diemTrungBinh, k);
            Add_Last(B[i], p);
        }
        iList.first = NULL; 
        for(i = 0; i < 10; ++i){
            if(B[i].first != NULL){ 
                if(iList.first == NULL){ 
                    iList.first = B[i].first;
                    iList.last = B[i].last;
                } else { 
                    iList.last->next = B[i].first;
                    iList.last = B[i].last;
                }
            }
        }
    }
}
