# The problem
Given a sorted array of unsigned integers, the right circular shift operation `>>` and the left circular shift operation `<<`. The value of the shift amount is always a positive integer. For example:

> `[0, 1, 2, 3, 4] >> 2` is `[3, 4, 0, 1, 2]`
>
> `[0, 1, 2, 3, 4] << 2` is `[2, 3, 4, 0, 1]`
>
> `[0, 1, 2, 3, 4] >> 0` is `[0, 1, 2, 3, 4]`

The search function needs to return an index of a given number in the array or a `-1` if the array does not contain such number.

# The problem
There is a well-known [binary search algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm), that allows us to subdivide an already sorted (usually in the ascending order) array to quickly determine the index of the element. The algorithm performs a maximum of `O(log(n))` subdivisions and may be implemented either as a recursive function or as a loop and thus is very effective and easy to understand. The binary search can not be used in the sorted but circulary shifted array without modifications, because it has to know the starting search index, which could be determined in various techniques not to be discussed in this paper. If we however prove that any of it's half-range is sorted and it can be easily determined, we could easily check whether the element is in this range and select either **that** or **an another** range for further checks. Thus this approach could potentially operate with the same time complexity as the regular binary search.

# The proof
The set of possible circular right-shift rotations `R` of an arbirary array of `n` elements is `R=[0..n-1]`, thus the [amount of values in this set](https://en.wikipedia.org/wiki/Circular_shift) is `n` including zero. Let us determine a `mid` element by dividing it's length by `2`, thus `mid=n/2`. It is obvious that for the sorted array of `n` integer elements both of its `[0..mid]` and `[mid..n-1]` half-ranges are sorted. For the array `A` the higher half-range `A[mid..n-1]` of the array remains sorted until `A[mid] <= A[n-1]`, and the lower half-range `A[0..mid]` remains sorted until `A[0] <= A[mid]`. Following these two non-strict inequities we may form a rule:
> **Ether the lower (first) or a higher (second) half-range remains sorted no matter of the amoult of performed right-shift rotations**.
 
For an array of `n` elements, each right-shift rotation of `r` can be replaced with a corresponding left-shift rotation of `n-r`, thus this rule is also true for the left-shift rotations, so:
> **Whether or not the half-range is sorted can be determined in a single comparison with O(1) time complexity.**

# The algorithm
The algorithm could be implemented in either recursive or iterative approach. In search for element `e` in the array `A` is an array, `l` is 0, `h` is n-1:
```find(A[], e, l, h)
{
	if l > h: return -1
	mid = (l + h) / 2

	if A[mid] = e: return mid

	if A[l] <= A[mid]:
		if e in [A[l]..A[mid]]: return find(A, e, l, mid-1)
		otherwise: return find(A, e, mid+1, h)
	otherwise:
		if e in [A[mid]..A[h]]: return find(A, e, mid+1, h)
		otherwise: return find(A, e, l, mid-1)
}
```

# The interactive demo
For the sake of the demo, the array is filled with positive integers in range `[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]`. In this demo you will be prompted to input the rotation amount and the element to find. The demo outputs the current state of the array along with the recursion depth for each stage and the next action to be performed.

# Further improvements
Alghough the algorithm's complexity is still `O(log(n))`, it requires an increased number of comparisons and array accesses. The number of array accesses can be reduced by caching already fetched values into local variables. 

The number of comparisons and array accesses can be reduced by **marking the half-range as already sorted if the sorted half-range was chosen for further subdivision**. Once the half-range was marked, the further steps can be reduced to plain range checks as in the regular binary search.
