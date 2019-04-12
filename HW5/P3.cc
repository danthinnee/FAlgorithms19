/* Elisa Danthinne
 * HW5
 * P3.cpp
 */


#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include <tgmath.h>
using namespace std;

// initialize global variables
int moves = 0;
int comps = 0;

// Selection sort
int findIndexOfLargest(const int theArray[], int size){ // find largest item in an array and return location
    int indexSoFar = 0;
    for(int currentIndex = 1; currentIndex < size; currentIndex++){
            comps++;
            if(theArray[currentIndex] > theArray[indexSoFar]){
                                      indexSoFar = currentIndex;
            }
    }
    return indexSoFar;
}
void selectionSort(int theArray[], int n){ 
     // last = index of the last item in the subarray of items yet to be sorted;
    // largest = index of the largest item found
    for(int last=n-1; last >=1; last--)
    {
        // At this point, theArray[last+1..n-1] is sorted, and its
        // entries are greater than those in theArray[0..last].
        // Select the largest entry in theArray[0..last]
        int largest = findIndexOfLargest(theArray, last+1);
        // Swap the largest entry, theArray[largest], with theArray[last]
        comps++;
        if (largest != last){
           std::swap(theArray[largest], theArray[last]);
           moves = moves+3;
        }
    } // end for
} // end selectionSort

// Bubble sort
void bubbleSort(int theArray[], int n){
     bool sorted = false; // false when swaps occur
     int pass = 1;
     while(!sorted && (pass < n)){
                   // At this point, theArray[n+1-pass..n-1] is sorted
                   // and all of its entries are > the entries in theArray[0..n-pass]
                   sorted = true; // assume sorted
                   for(int index = 0; index < n-pass; index++){
                           // At this point, all entries in theArray[0..index-1]
                           // are <= theArray[index]
                           int nextIndex = index+1;
                           comps++;
                           if(theArray[index] > theArray[nextIndex]){
                                              // exchange entries
                                              std::swap(theArray[index], theArray[nextIndex]);
                                              moves = moves+3;
                                              sorted = false; // signal exchange
                           } // endif
                   } // endfor
                   // Assertion: theArray[0..n-pass-1]< theArray[n-pass]
                   pass++;
     } // end while
} // end bubbleSort

// Insertion sort
void insertionSort(int theArray[], int n)
{
     // unsorted = first index of the unsorted region,
    // loc = index of insertion in the sorted region,
    // nextItem = next item in the unsorted region.
    // Initially, sorted region is theArray[0], unsorted region is theArray[1..n-1].
    // In general, sorted region is theArray[0..unsorted-1], unsorted region theArray[unsorted..n-1]
     for(int unsorted=1; unsorted < n; unsorted ++){
             // At this point, theArray[0..unsorted-1] is sorted.
            // Find the right position (loc) in theArray[0..unsorted]
            // for theArray[unsorted], which is the first entry in the
            // unsorted region; shift, if necessary, to make room
             int nextItem = theArray[unsorted];
             moves++;
             int loc = unsorted;
             comps++;
             while((loc>0) && (theArray[loc-1]>nextItem)){
             // Shift theArray[loc - 1] to the right
                     comps++;
                     theArray[loc] = theArray[loc - 1];
                     moves++;
                     loc--;        
             }
             // At this point, theArray[loc] is where nextItem belongs
             if(loc != unsorted){
                    theArray[loc] = nextItem; //Insert nextItem into sorted region
                    moves++;
             } // endif
     } // endfor
} // end insertionSort

// Merge sort
/** Merges two sorted arrays theArray[first..mid] and theArray[mid+1..last] into one sorted array.
@pre first <= mid <= last. The subarrays theArray[first..mid] and theArray[mid+1..last] are sorted.
@post theArray[first..last] is sorted.
@param theArray The given array.
@param first The index of the beginning of the first segment in theArray.
@param mid The index of the end of the 1st segment; mid + 1 the beginning of the 2nd segment.
@param last The index of the last element in the second segment in theArray.
@note two subarrays are merged into a temp array. The result is copied into the original array */
const int MAX_SIZE = 1000;
void merge(int theArray[], int first, int mid, int last)
{
     int tempArray[MAX_SIZE];
     
     int first1 = first; // beginning of first subarray
     int last1 = mid; // end of first subarray
     int first2 = mid + 1; // beginning of second subarray
     int last2 = last; // end of second subarray
     // While both subarrays are not empty, copy the
     //smaller item into the temporary array
     int index = first1;
     comps=comps+2;
     while((first1 <=last1) && (first2 <=last2)){
                   comps=comps+2;
                   // At this point, tempArray[first..index-1] is in order
                   comps++;
                   if(theArray[first1] <= theArray[first2]){
                                       tempArray[index] = theArray[first1];
                                       moves++;
                                       first1++;
                   }
                   else {
                        tempArray[index] = theArray[first2];
                        moves++;
                        first2++;
                        } // endif
                   index++;
     } // end while
     // Finish off the first subarray, if necessary
     while(first1 <= last1){
                  // At this point, tempArray[first..index-1] is in order
                  moves++;
                  tempArray[index] = theArray[first1];
                  first1++;
                  index++;
     } // end while
     // Finish off the second subarray, if necessary
     while(first2 <= last2){
                  // At this point, tempArray[first..index-1] is in order
                  moves++;
                  tempArray[index] = theArray[first2];
                  first2++;
                  index++;
     } // end while
     // Copy the result back into the original array
     for(index = first; index <= last; index++){
               theArray[index] = tempArray[index];
               moves++;
     }
}
void mergeSort(int theArray[], int first, int last){
     if(first < last){
              int mid = first + (last - first)/2;
              mergeSort(theArray, first, mid);
              mergeSort(theArray, mid+1, last);
              merge(theArray, first, mid, last);
     }
}

// Quick sort
static const int MIN_SIZE = 10;
void order(int theArray[], int i, int j){
    if(theArray[i] > theArray[j])
        std::swap(theArray[i], theArray[j]);
}
int sortFirstMiddleLast(int theArray[], int first, int last){
    int mid = first+(last- first)/2;
    order(theArray, first, mid); // Make theArray[first] <= theArray[mid]
    order(theArray, mid, last); // Make theArray[mid] <= theArray[last]
    order(theArray, first, mid); // Make theArray[first] <= theArray[mid]
    return mid;
}
int partition(int theArray[], int first, int last){ // Choose pivot using median
    int pivotIndex= sortFirstMiddleLast(theArray, first, last);
    // Reposition pivot so it is last in the array
    std::swap(theArray[pivotIndex], theArray[last-1]);
    moves = moves+3; 
    pivotIndex= last-1;
    int pivot = theArray[pivotIndex];
    // moves++;
    // Determine the regions S1 and S2
    int indexFromLeft= first+1;
    int indexFromRight= last-2;
    bool done= false;
    while(!done)
    {
        // Locate first entry on left that is >= pivot
        comps++;
        while(theArray[indexFromLeft] < pivot){
                                      comps++;
                                      indexFromLeft= indexFromLeft+1;
	}
        // Locate first entry on right that is <= pivot
        comps++;
        while(theArray[indexFromRight] > pivot){
                                       comps++;
                                       indexFromRight= indexFromRight-1;
        }
        
        if(indexFromLeft< indexFromRight)
        {
            std::swap(theArray[indexFromLeft], theArray[indexFromRight]);
            moves = moves+3;
            indexFromLeft= indexFromLeft+1;
            indexFromRight= indexFromRight-1; }
        else done= true;
    } // end while
    // Place pivot in proper position between S1 and S2, and mark its new location
    std::swap(theArray[pivotIndex], theArray[indexFromLeft]);
    moves = moves+3;
    pivotIndex=indexFromLeft;
    return pivotIndex;
}
void quickSort(int theArray[], int first, int last)
{
    int sz= last-first+ 1;
    if(sz< MIN_SIZE)
        insertionSort(theArray+first,sz);
    else
    {
        int pivotIndex= partition(theArray, first, last);
        // Sort subarrays S1 and S2
        quickSort(theArray, first, pivotIndex-1);
        quickSort(theArray, pivotIndex+1, last);
    } // end if
}

// RESET ARRAYS
void reinitialize(int test[], int theArray[]){ // before testing each algorithm, reinitialize arrays as copies of originals
     for(int i=0; i<1000; i++){
	     int a = theArray[i];
             test[i] = a;
     }
}
// TEST ARRAYS
bool testSort(int theArray[]){ // verify array is sorted
     // confirm each element i in the array has a value less than or equal to 
     // the value in element i+1
     for(int i=0; i<1000-1; i=i+2){
//cout << theArray[i] << "\n";
           if(theArray[i] > theArray[i+1])
                          return false;
     }
     return true;
     }

void heapRebuild(int root, int items[], int itemCount){
	if(2*root+2 <= itemCount){ // if root has a leaf
		int largerChildIndex = 2*root + 1;
		if(2*root+3 <= itemCount){ // if roo has a right child
			int rightChildIndex = 2*root+2;
			comps++;
			if(items[rightChildIndex] > items[largerChildIndex]){
				largerChildIndex = rightChildIndex;
			}
		}
		comps++;
		if(items[root] < items[largerChildIndex]){
			std::swap(items[root],items[largerChildIndex]);
			moves = moves+3;
			heapRebuild(largerChildIndex,items,itemCount);
		}
	}
}
void heapCreate(int items[], int itemCount){ // converts arry content into a heap
	// rebuild heap starting from the last non-leaf node, index of first leaf is [n/2]
	for(int index = (itemCount/2)-1; index >=0; index--){
		heapRebuild(index, items, itemCount);
	}
}
// heap sort
void heapSort(int theArray[], int n){
	int heapSize = n;
	heapCreate(theArray, heapSize); // converts array content into a heap
	while(heapSize > 1){
		std::swap(theArray[0], theArray[heapSize-1]);
		moves = moves+3;
		heapSize--;
		heapRebuild(0,theArray,heapSize);
	}
}

// MAIN FUNCTION
int main(){    
    /* Create 3 arrays of 1000 integers */
    // BST has 1000 integers already sorted in ascending order
    int bst[1000];
    for(int i=0; i<1000; i++){
            bst[i] = (i+1)*10;
    }
    // AVG has 1000 randomly generated integers, where each integer is between 0 and 100,000
    int avg[1000];
    srand(time(NULL));
    for(int i=1; i<1000; i++){
            avg[i] = rand() % 100001;
    }    
    // WST has 1000 integers sorted in descending order
    int wst[1000];
    for(int i=0; i<1000; i++){
            wst[i] = (1000-i)*10;
    }
    
    // open output file
    ofstream outf;
    outf.open("sort.txt");
    if (outf.fail()) {
        cerr << "Error: Could not open output file\n";
        exit(1);
    }
    outf << "Array Name\t" << "Sorting Algorithm\t" << "Number of Moves" << "\t" << "Number of Comparisons" << "\n";
    /* Create copies of 1000int arrays to be used for testing */
    int tbst[1000];
    int tavg[1000];
    int twst[1000];
    
    /* Selection Sort */
    reinitialize(tbst,bst); // reinitialize arrays
    reinitialize(tavg,avg);
    reinitialize(twst,wst);

    cout << "---\n" << "SELECTION SORT:\n";

    moves=0; comps=0;
    selectionSort(tbst,1000);
    cout << "BST is sorted? " << testSort(tbst) << "\n"; // verify sorted
    outf << "BST\t\t" << "Selection Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    selectionSort(tavg,1000);
    cout << "AVG is sorted? " << testSort(tavg) << "\n";
    outf << "AVG\t\t" << "Selection Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    selectionSort(twst,1000);
    cout << "WST is sorted? " << testSort(twst) << "\n";
    outf << "WST\t\t" << "Selection Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    
    /* Bubble Sort */
    reinitialize(tbst,bst); 
    reinitialize(tavg,avg);
    reinitialize(twst,wst);

    cout << "---\n" << "BUBBLE SORT:\n";

    moves = 0; comps = 0;
    bubbleSort(tbst,1000); // run sort algorithm
    cout << "BST is sorted? " << testSort(tbst) << "\n"; // verify sorted
    outf << "BST\t\t" << "Bubble Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    bubbleSort(tavg,1000);
    cout << "AVG is sorted? " << testSort(tavg) << "\n";
    outf << "AVG\t\t" << "Bubble Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    bubbleSort(twst,1000);
    cout << "WST is sorted? " << testSort(twst) << "\n";
    outf << "WST\t\t" << "Bubble Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    
    /* Insertion Sort */
    reinitialize(tbst,bst); // reinitialize arrays
    reinitialize(tavg,avg);
    reinitialize(twst,wst);

    cout << "---\n" << "INSERTION SORT:\n";

    moves=0; comps=0;
    insertionSort(tbst,1000);
    cout << "BST is sorted? " << testSort(tbst) << "\n"; // verify sorted
    outf << "BST\t\t" << "Insertion Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    insertionSort(tavg,1000);
    cout << "AVG is sorted? " << testSort(tavg) << "\n";
    outf << "AVG\t\t" << "Insertion Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    insertionSort(twst,1000);
    cout << "WST is sorted? " << testSort(twst) << "\n";
    outf << "WST\t\t" << "Insertion Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file

    // Merge Sort 
    reinitialize(tbst,bst); // reinitialize arrays
    reinitialize(tavg,avg);
    reinitialize(twst,wst);

    cout << "---\n" << "MERGE SORT:\n";

    moves = 0; comps = 0; 
    mergeSort(tbst,0,1000); // run sort algorithm
    cout << "BST is sorted? " << testSort(tbst) << "\n"; // verify sorted
    outf << "BST\t\t" << "Merge Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    mergeSort(tavg,0,1000);
    cout << "AVG is sorted? " << testSort(tavg) << "\n";
    outf << "AVG\t\t" << "Merge Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    mergeSort(twst,0,1000);
    cout << "WST is sorted? " << testSort(twst) << "\n";
    outf << "WST\t\t" << "Merge Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    
    // Quick Sort 
    reinitialize(tbst,bst); // reinitialize arrays
    reinitialize(tavg,avg);
    reinitialize(twst,wst);

    cout << "---\n" << "QUICK SORT: \n";

    moves = 0; comps = 0;
    quickSort(tbst,0,1000);
    cout << "BST is sorted? " << testSort(tbst) << "\n"; // verify sorted
    outf << "BST\t\t" << "Quick Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    quickSort(tavg,0,1000);
    cout << "AVG is sorted? " << testSort(tavg) << "\n"; // verify sorted
    outf << "AVG\t\t" << "Quick Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    quickSort(twst,0,1000);
    cout << "WST is sorted? " << testSort(twst) << "\n";
    outf << "WST\t\t" << "Quick Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
                   
    // Heap Sort 
    reinitialize(tbst,bst); // reinitialize arrays
    reinitialize(tavg,avg);
    reinitialize(twst,wst);

    cout << "---\n" << "HEAP SORT: \n";

    moves = 0; comps = 0;
    heapSort(tbst,1000);
    cout << "BST is sorted? " << testSort(tbst) << "\n"; // verify sorted
    outf << "BST\t\t" << "Heap Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    heapSort(tavg,1000);
    cout << "AVG is sorted? " << testSort(tavg) << "\n"; // verify sorted
    outf << "AVG\t\t" << "Heap Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
    moves=0; comps=0;
    heapSort(twst,1000);
    cout << "WST is sorted? " << testSort(twst) << "\n";
    outf << "WST\t\t" << "Heap Sort\t\t" << moves << "\t\t" << comps << "\n"; // print to output file
 
    outf.close(); //Close the file at the end of program

    return 0;
}
