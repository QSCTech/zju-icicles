Car *ScanList(Car *headPointer, int searchID)
{
  Car *previous;
  Car *current;

  /* Point to start of list */
  previous = headPointer;
  current = headPointer->next;

  /* Traverse list -- scan until we find a node with a    */
  /* vehicleID greater than or equal to searchID          */
  while ((current != NULL) && 
         (current->vehicleID < searchID)) {
    previous = current;
    current  = current->next;
  }

  /* The variable previous points to node prior to the    */
  /* node being searched for. Either current->vehicleID   */  
  /* equals searchID or the node does not exist.          */
  return previous;
}
