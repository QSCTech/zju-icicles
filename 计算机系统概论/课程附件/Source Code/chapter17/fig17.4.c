/* 
** Inputs
**   diskNumber is the disk to be moved (disk1 is smallest)
**   startPost is the post the disk is currently on
**   endPost is the post we want the disk to end on
**   midPost is the intermediate post
*/
MoveDisk(diskNumber, startPost, endPost, midPost)
{
   if (diskNumber > 1) {
       /* Move n-1 disks off the current disk on         */
       /* startPost and put them on the midPost          */
       MoveDisk(diskNumber-1, startPost, midPost, endPost); 

       /* Move the largest disk.                         */
       printf("Move disk %d from post %d to post %d.\n", 
               diskNumber, startPost, endPost);

       /* Move all n-1 disks from midPost onto endPost   */
       MoveDisk(diskNumber-1, midPost, endPost, startPost);
   }
   else 
       printf("Move disk 1 from post %d to post %d.\n", 
               startPost, endPost);      
}
