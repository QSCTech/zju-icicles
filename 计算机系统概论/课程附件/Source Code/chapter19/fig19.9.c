void DeleteEntry(Car *headPointer)
{
  int vehicleID;
  Car *delNode;       /* Points to node to delete         */
  Car *prevNode;      /* Points to node prior to delNode  */

  printf("Enter the vehicle ID of the car to delete:\n");
  scanf("%d", &vehicleID);

  prevNode = ScanList(headPointer, vehicleID);
  delNode  = prevNode->next;

  /* Either there is the car does not exist or            */  
  /* delNode points to the car to be deleted.             */
  if (delNode != NULL && delNode->vehicleID == vehicleID) {
    prevNode->next = delNode->next;
    printf("Vehicle with id %d deleted.\n\n", vehicleID);    
    free(delNode);
  }
  else 
    printf("The vehicle was not found in the database.\n");
}
