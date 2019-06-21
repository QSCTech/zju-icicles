void AddEntry(Car *headPointer)
{
  Car *newNode;       /* Points to the new car info       */
  Car *nextNode;      /* Points to car to follow new one  */
  Car *prevNode;      /* Points to car before this one    */
  
  /* Dynamically allocate memory for this new entry.      */
  newNode = (Car *) malloc(sizeof(Car));

  if (newNode == NULL) {
     printf("Error: could not allocate a new node\n");
     exit(1);
  }

  printf("Enter the following info about the car.\n");
  printf("Separate each field by whitespace:\n");
  printf("vehicle_id make model year mileage cost\n");

  scanf("%d %s %s %d %d %lf", 
        &newNode->vehicleID, newNode->make, newNode->model,
        &newNode->year, &newNode->mileage, &newNode->cost);

  prevNode = ScanList(headPointer, newNode->vehicleID);
  nextNode = prevNode->next;

  if ((nextNode == NULL) || 
      (nextNode->vehicleID != newNode->vehicleID)) {
    prevNode->next = newNode;
    newNode->next = nextNode;
    printf("Entry added.\n\n");
  }
  else {
    printf("That car already exists in the Database!\n");
    printf("Entry not added.\n\n");
    free(newNode);
  }
}
