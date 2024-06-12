void Add_Last(List &l, Node* new_ele){
    if (l.first == NULL) {
        l.first = new_ele;
        l.last = new_ele;
    } else {
        new_ele->next = l.first;
        l.first->prev = new_ele;
        l.first = new_ele;
    }
}

void Init_List(List &l){
    l.first = l.last = NULL;
}

// Get the maximum element in the list
int getMaxElement(List &list) {
    int maxVal = list.first->data.diemTrungBinh; // Replace with actual data structure as needed
    for (Node* current = list.first; current; current = current->next) {
        if (current->data.diemTrungBinh > maxVal)
            maxVal = current->data.diemTrungBinh;
    }
    return maxVal;
}

// Get the number of digits in the maximum element
int getNumbofDigit(int number) {
    int digits = 0;
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

// Get the k-th digit of a number
int GetDigit(int number, int k) {
    while (k--) {
        number /= 10;
    }
    return number % 10;
}

// Radix sort implementation for the list
void ListRadixSort(List &inputList) {
    List buckets[10]; // Array of buckets for radix sort
    Node* currentNode;
    int digitValue, numDigits, maxElement, i, digitIndex;

    if (inputList.first == nullptr || inputList.first == inputList.last) {
        return; // List is empty or has only one element
    }

    maxElement = getMaxElement(inputList); // Find the maximum element
    numDigits = getNumbofDigit(maxElement); // Get the number of digits in the maximum element

    for (i = 0; i < 10; ++i) {
        Init_List(buckets[i]);
    }

    for (digitIndex = 0; digitIndex < numDigits; ++digitIndex) {
        for (i = 0; i < 10; ++i) {
            Init_List(buckets[i]);
        }

        while (inputList.first) {
            currentNode = inputList.first;
            inputList.first = currentNode->next;
            currentNode->next = nullptr;
            digitValue = GetDigit(currentNode->data.diemTrungBinh, digitIndex);
            Add_Last(buckets[digitValue], currentNode);
        }

        inputList.first = nullptr;
        for (i = 0; i < 10; ++i) {
            if (buckets[i].first != nullptr) {
                if (inputList.first == nullptr) {
                    inputList.first = buckets[i].first;
                    inputList.last = buckets[i].last;
                } else {
                    inputList.last->next = buckets[i].first;
                    inputList.last = buckets[i].last;
                }
            }
        }
    }
}
