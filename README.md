# Binary search in a rotated sorted array
Given a sorted but rotated array of unsigned integer.

For example a `[0, 1, 2, 3, 4] >> 2` is `[3, 4, 0, 1, 2]`.

# The problem
This algorithm allows you to perform a binary search in this array with O(log(n)) time complexity in one pass, but it requires an extra branch unlike the traditional binary search albeit the complexity is still logarithmic.

# General description
This approach is based on a simple assumption that **each time after a bisection ether the lower (first) or a higher (second) part is sorted** and thus you may safely perform `is x in range [a, b]` operation in the sorted part.

# "is sorted" implementation
To determine whether `x is in range [a, b]` you need to determine whether the part is sorted. To do this you may simply compare the middle element to the first in the part. If current middle element is above the first, then the part is sorted, because in the sorted and rotated array there is no way for this condition to be satisfied for the unsorted half.
