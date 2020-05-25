RED BLACK TREE

The following program is used to implement a Red Black Tree with the help of some basic operations given below.
NOTE : Leaves are not expliciltly connected to Dummy Nodes to retain the black external node. It is considered implicitly.

     1. isEmpty(T) : Checks if the RBT T is empty and returns a integer accordingly.
     2. find(T,x) : Checks if a node with data x exists in the RBT T and returns a pointer accordingly.  
     3. inPred(T,x) : Finds the inorder predecessor of the node with data x in the RBT T, if it exists, and returns the pointer.
     4. inSucc(T,x) : Finds the inorder successor of the node with data x in the RBT T, if it exists, and returns the pointer.
     5. leftRotate(T,x) : Rotates in anticlockwise direction about the node with data x in RBT T, if it exists.
     6. rightRotate(T,x) : Rotates in clockwise direction about the node with data x in RBT T, if it exists.
     7. insert(T,x) : Inserts a node with data x into the RBT T, if it doesn't exist already in T, and restructures the tree appropriately. In default, a red node is inserted.
     8. delete(T,x) : Deletes a node with data x from the RBT T, if it exists and restructures the tree appropriately. 
     9. inOrder(T) : Prints the data in RBT T by using inorder traversal.
    10. blackH(T) : Returns the black height of the RBT T. (Including Dummy Nodes).
    11. colour(T,x) : Returns the number equivalent to the colour of the node with data x in T, if it exists.
    12. height(T) : Returns the height of the RBT T.
    13. range(T,x,y) : Returns a list of all the data in the RBT T in range [x,y]. Note : x<=y. 
    14. leafCount(T) : Returns the number of leaves (Not External Nodes i.e. Dummy Nodes) present in the RBT T.

Main asks the user to Enter the number of inputs for insertion (which can be given through the inputs.txt or directly) and then takes the data one by one all the while constructing the appropriate Red Black Tree with the given data sequence. After talking all the inputs, it will print out the data stored inside the Tree via inorder traversal.

AFTER EACH DATA EITHER 0 OR 1 IS GIVEN INDICATING RED OR BLACK NODE RESPECTIVELY.

It then gives the user 5 options namely:
1. Delete a node : Asks the user for data to be deleted and if it exists in the tree, it deletes it and restructures the tree appropriately. It then shows the data present in tree via inorder traversal.
2. Count the number of leaves : Gives the user number of leaves present (Not external nodes i.e. Dummy Nodes) present in the tree.
3. Find the height of the tree : Gives the user the height of the Tree.
4. Get the data within the range [a,b] : Gives the user all the data present in the Tree within the range [a,b].
5. Exit.

The options are given until the user chooses to exit from the program.

