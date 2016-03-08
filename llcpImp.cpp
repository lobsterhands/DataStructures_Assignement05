#include <iostream>
#include <cstdlib>
#include "llcpInt.h"
using namespace std;

int FindListLength(Node* headPtr)
{
   int length = 0;

   while (headPtr != 0)
   {
      ++length;
      headPtr = headPtr->link;
   }

   return length;
}

bool IsSortedUp(Node* headPtr)
{
   if (headPtr == 0 || headPtr->link == 0) // empty or 1-node
      return true;
   while (headPtr->link != 0) // not at last node
   {
      if (headPtr->link->data < headPtr->data)
         return false;
      headPtr = headPtr->link;
   }
   return true;
}

void InsertAsHead(Node*& headPtr, int value)
{
   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   newNodePtr->link = headPtr;
   headPtr = newNodePtr;
}

void InsertAsTail(Node*& headPtr, int value)
{
   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   newNodePtr->link = 0;
   if (headPtr == 0)
      headPtr = newNodePtr;
   else
   {
      Node *cursor = headPtr;

      while (cursor->link != 0) // not at last node
         cursor = cursor->link;
      cursor->link = newNodePtr;
   }
}

void InsertSortedUp(Node*& headPtr, int value)
{
   Node *precursor = 0,
        *cursor = headPtr;

   while (cursor != 0 && cursor->data < value)
   {
      precursor = cursor;
      cursor = cursor->link;
   }

   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   newNodePtr->link = cursor;
   if (cursor == headPtr)
      headPtr = newNodePtr;
   else
      precursor->link = newNodePtr;

   ///////////////////////////////////////////////////////////
   /* using-only-cursor (no precursor) version
   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   //newNodePtr->link = 0;
   //if (headPtr == 0)
   //   headPtr = newNodePtr;
   //else if (headPtr->data >= value)
   //{
   //   newNodePtr->link = headPtr;
   //   headPtr = newNodePtr;
   //}
   if (headPtr == 0 || headPtr->data >= value)
   {
      newNodePtr->link = headPtr;
      headPtr = newNodePtr;
   }
   //else if (headPtr->link == 0)
   //   head->link = newNodePtr;
   else
   {
      Node *cursor = headPtr;
      while (cursor->link != 0 && cursor->link->data < value)
         cursor = cursor->link;
      //if (cursor->link != 0)
      //   newNodePtr->link = cursor->link;
      newNodePtr->link = cursor->link;
      cursor->link = newNodePtr;
   }

   ////////////////// commented lines removed //////////////////

   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   if (headPtr == 0 || headPtr->data >= value)
   {
      newNodePtr->link = headPtr;
      headPtr = newNodePtr;
   }
   else
   {
      Node *cursor = headPtr;
      while (cursor->link != 0 && cursor->link->data < value)
         cursor = cursor->link;
      newNodePtr->link = cursor->link;
      cursor->link = newNodePtr;
   }
   */
   ///////////////////////////////////////////////////////////
}

bool DelFirstTargetNode(Node*& headPtr, int target)
{

   Node *precursor = 0,
        *cursor = headPtr;

   while (cursor != 0 && cursor->data != target)
   {
      precursor = cursor;
      cursor = cursor->link;
   }
   if (cursor == 0)
   {
      cout << target << " not found." << endl;
      return false;
   }
   if (cursor == headPtr) //OR precursor == 0
      headPtr = headPtr->link;
   else
      precursor->link = cursor->link;
   delete cursor;
   return true;
}

bool DelNodeBefore1stMatch(Node*& headPtr, int target)
{
   if (headPtr == 0 || headPtr->link == 0 || headPtr->data == target) return false;
   Node *cur = headPtr->link, *pre = headPtr, *prepre = 0;
   while (cur != 0 && cur->data != target)
   {
      prepre = pre;
      pre = cur;
      cur = cur->link;
   }
   if (cur == 0) return false;
   if (cur == headPtr->link)
   {
      headPtr = cur;
      delete pre;
   }
   else
   {
      prepre->link = cur;
      delete pre;
   }
   return true;
}

void ShowAll(ostream& outs, Node* headPtr)
{
   while (headPtr != 0)
   {
      outs << headPtr->data << "  ";
      headPtr = headPtr->link;
   }
   outs << endl;
}

void FindMinMax(Node* headPtr, int& minValue, int& maxValue)
{
   if (headPtr == 0)
   {
      cerr << "FindMinMax() attempted on empty list" << endl;
      cerr << "Minimum and maximum values not set" << endl;
   }
   else
   {
      minValue = maxValue = headPtr->data;
      while (headPtr->link != 0)
      {
         headPtr = headPtr->link;
         if (headPtr->data < minValue)
            minValue = headPtr->data;
         else if (headPtr->data > maxValue)
            maxValue = headPtr->data;
      }
   }
}

double FindAverage(Node* headPtr)
{
   if (headPtr == 0)
   {
      cerr << "FindAverage() attempted on empty list" << endl;
      cerr << "An arbitrary zero value is returned" << endl;
      return 0.0;
   }
   else
   {
      int sum = 0,
          count = 0;

      while (headPtr != 0)
      {
         ++count;
         sum += headPtr->data;
         headPtr = headPtr->link;
      }

      return double(sum) / count;
   }
}

void ListClear(Node*& headPtr, int noMsg)
{
   int count = 0;

   Node *cursor = headPtr;

   count = 0;
   while (headPtr != 0)
   {
      headPtr = headPtr->link;
      delete cursor;
      cursor = headPtr;
      ++count;
   }
   if (noMsg) return;
   clog << "Dynamic memory for " << count << " nodes freed"
        << endl;
}

// definition of RemBadSplitGood of Assignment 5 Part 1
void RemBadSplitGood(Node*& L1Head, Node*& L2Head, Node*& L3Head)
{
   // If L1Head is empty, there is nothing to process. Simply create three
   // nodes with the proper empty flag (-99) and a null pointer and point each
   // list to its respective node.
   if (L1Head == 0) {
      Node *dummyL1 = new Node;
      Node *dummyL2 = new Node;
      Node *dummyL3 = new Node;

      dummyL1->data = dummyL2->data = dummyL3->data = -99;
      dummyL1->link = dummyL2->link = dummyL3->link = 0;

      L1Head = dummyL1;
      L2Head = dummyL2;
      L3Head = dummyL3;
      return;
   }

   // If L1Head is not empty
   Node *current = L1Head; // Create a pointer to track the current node
   Node *prev = L1Head; // Create a pointer to track the previous node
   Node *reassignPtr = 0; // Create a pointer to track node for reassignment
   while (current != 0) { // Traverse List 1
      int thisData = current->data;

      // Numbers out of bounds will be deleted from List 1
      if ((thisData < 0) || (thisData > 9)) {
         Node *killNode = current; // Create a pointer to the node for deletion

         if (current == L1Head) {
            L1Head = L1Head->link;
            current = L1Head;
            prev = current;
         } else {
            prev->link = current->link;
            current = current->link;
         }

         delete killNode;
      }

      // All 6's remain in List 1
      if (thisData == 6) {
         if (prev->link == current) {
            prev = current;
         }
         current = current->link;
      }

      // If data is in the range [0,5] or [7,9], process it
      if ((thisData >= 0 && thisData <= 5) || (thisData >= 7 && thisData <= 9))
      {
         prev->link = current->link;
         reassignPtr = current;

         if (current == L1Head) {
            L1Head = current->link;
            prev = L1Head;
         }

         current = current->link;

         // Data in the range [0,5] go into List 2
         if ((thisData >= 0) && (thisData <= 5))
         {
            if (L2Head == 0)
            {
               L2Head = reassignPtr;
               L2Head->link = 0;
            } else {
               Node *cursorL2 = L2Head;
               while (cursorL2->link != 0) { // Find the last node
                  cursorL2 = cursorL2->link;
               }
               reassignPtr->link = 0;
               cursorL2->link = reassignPtr;
            }
         }

         // Data in the range [7,9] go into List 3
         if ((thisData >= 7) && (thisData <=9))
         {
            if (L3Head == 0)
            {
               L3Head = reassignPtr;
               L3Head->link = 0;
            } else {
               Node *cursorL3 = L3Head;
               while (cursorL3->link != 0) { // Find the last node
                  cursorL3 = cursorL3->link;
               }
               reassignPtr->link = 0;
               cursorL3->link = reassignPtr;
            }
         }

      }
   }

   // After List1 processing, check each list; if a list is empty, create a new
   // node with the empty flag (-99) and a null pointer for that list.
   if (L1Head == 0)
   {
      Node *dummyL1 = new Node;
      dummyL1->data = -99;
      dummyL1->link = 0;
      L1Head = dummyL1;
   }

   if (L2Head == 0)
   {
      Node *dummyL2 = new Node;
      dummyL2->data = -99;
      dummyL2->link = 0;
      L2Head = dummyL2;
   }

   if (L3Head == 0)
   {
      Node *dummyL3 = new Node;
      dummyL3->data = -99;
      dummyL3->link = 0;
      L3Head = dummyL3;
   }
}
