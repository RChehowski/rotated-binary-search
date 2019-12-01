# The problem
Given a sorted but rotated array of unsigned integers. For example a `[0, 1, 2, 3, 4] >> 2` is `[3, 4, 0, 1, 2]`.

The search function needs to return an index of a number in the array or a `-1` if the array does not contain such a number.


# The problem
There is a well-known [binary search algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm), that allows us to subdivide an already sorted (usually in the ascending order) array to quickly determine the index of the element. The algorithm performs a maximum of `O(log(n))` subdivisions and may be implemented either as a recursive function or as a loop and thus is very effective. The binary search can not be used in the sorted but shifted array without modifications, yet it has to know the starting seach index, which could be determined in various techniques not to be disclosed in this paper.

# The proof
The set of possible circular right-shift rotations **R** of an arbirary array of **n** elements is **R=[0, n-1]**, thus the [amount of values in this set](https://en.wikipedia.org/wiki/Circular_shift) is **n**. It is obvious that in the sorted array of **n** integer elements both of its parts are sorted. Let us determine a **mid** element by dividing it's length by **2**, thus **mid=n/2**. In an array **A** the higher half **[mid, n-1]** of the array remains sorted until **A[mid] <= A[n-1]**, and the lower half **[0, mid]** remains sorted until **A[0] <= A[mid]**. Following these two non-strict inequities we may form a rule:
 |> Ether the lower (first) or a higher (second) range remains sorted no matter of the amoult of circular shifts
 
In the array of **n** elements, each right-shift rotation of **r** could be replaced with a corresponding left-shift rotation of **[n-r]**, thus this rule remais its strength for the left-shift rotations as well.


# The algorithm
This algorithm allows you to perform a binary search in this array with O(logn) time complexity in one pass, but it requires an extra branch unlike the traditional binary search albeit the complexity is still logarithmic.

This approach is based on a simple assumption that **each time after a bisection ether the lower (first) or a higher (second) part is sorted** and thus you may safely perform `is x in range [a, b]` operation in the sorted part.

# "is sorted" implementation
To determine whether `x is in range [a, b]` you need to determine whether the part is sorted. To do this you may simply compare the middle element to the first in the part. If current middle element is above the first, then the part is sorted, because in the sorted and rotated array there is no way for this condition to be satisfied for the unsorted half.
