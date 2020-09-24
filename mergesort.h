template<typename T> 
void mergeSort(std::vector<T> &data, unsigned int firstToSort, unsigned int lastToSort);

template<typename T>
void Merge(std::vector<T> &numbers, int i, int j, int k) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   //int* mergedNumbers = nullptr;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   std::vector<T> mergedNumbers(mergedSize);      // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (numbers.at(leftPos) < numbers.at(rightPos)) {
         mergedNumbers.at(mergePos) = numbers.at(leftPos);
         ++leftPos;
      }
      else {
         mergedNumbers.at(mergePos) = numbers.at(rightPos);
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers.at(mergePos) = numbers.at(leftPos);
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers.at(mergePos) = numbers.at(rightPos);
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers.at(i + mergePos) = mergedNumbers.at(mergePos);
   }
   
}
template<typename T>
void mergeSort(std::vector<T> &data, unsigned int firstToSort, unsigned int lastToSort) {
   int j;
   
   if (firstToSort < lastToSort) {
      j = (firstToSort + lastToSort) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      mergeSort(data, firstToSort, j);
      mergeSort(data, j + 1, lastToSort);
      
      // Merge left and right partition in sorted order
    Merge(data, firstToSort, j, lastToSort);
   }
}
