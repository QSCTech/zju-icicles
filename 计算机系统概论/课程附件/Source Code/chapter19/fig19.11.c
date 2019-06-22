void Search(CarNode *headPointer)
{
  int vehicleID;
  CarNode *searchNode;    /* Points to node to delete to follow */
  CarNode *prevNode;      /* Points to car before one to delete */

  printf("Enter the vehicle ID number of the car to search for:\n");
  scanf("%d", &vehicleID);

  prevNode = ScanList(headPointer, vehicleID);
  searchNode  = prevNode->next;

  /* Either there is the car does not exist in the list or      */  
  /* searchNode points to the car we are looking for.           */
  if (searchNode != NULL && searchNode->vehicleID == vehicleID) {
    printf("vehicle ID : %d\n", searchNode->vehicleID);
    printf("make       : %s\n", searchNode->make);
    printf("model      : %s\n", searchNode->model);
    printf("year       : %d\n", searchNode->year);
    printf("mileage    : %d\n", searchNode->mileage);

    /* The following printf has a field width specification on  */
    /* %f specification.  The 10.2 indicates that the floating  */
    /* point number should be printed in a 10 character field   */
    /* with two units after the decimal displayed.              */
    printf("cost       : $%10.2f\n\n", searchNode->cost);
  }
  else {
    printf("The vehicle id %d was not found in the database.\n\n", 
           vehicleID);
  }
}
