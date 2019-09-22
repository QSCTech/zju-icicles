/*
** This function returns the position of 'item' if it exists
** between list[start] and list[end], or -1 if it does not.
*/
int BinarySearch(int item, int list[], int start, int end)
{
  int middle = (end + start) / 2;

  /* Did we not find what we are looking for? */
  if (end < start) 
    return -1;

  /* Did we find the item */
  else if (list[middle] == item)
    return middle;

  /* Should we search the first half of the array? */
  else if (item < list[middle])
    return BinarySearch(item, list, start, middle - 1);

  /* Or should we search the second half of the array? */
  else 
    return BinarySearch(item, list, middle + 1, end);
}
