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

   cout << "Inside LC" << endl;

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
void RemBadSplitGood(Node*& L1Head, Node*& L2Head, Node*& L3Head) {
   Node *dummyL1 = new Node;
   Node *dummyL2 = new Node;
   Node *dummyL3 = new Node;
   dummyL1->data = -99;
   dummyL2->data = -99;
   dummyL3->data = -99;
   dummyL1->link = 0;
   dummyL2->link = 0;
   dummyL3->link = 0;

   if (L1Head == 0) {
      L1Head = dummyL1;
      L2Head = dummyL2;
      L3Head = dummyL3;
      return;
   }

   cout << "L1Head: ";
   ShowAll(cout, L1Head);


   Node *current = L1Head;
   Node *prev = L1Head;
   Node *otherListPtr = 0;
   while (current != 0) {
      int l1data = current->data;
      int previous = prev->data;
      cout << "This node is " << l1data << endl;
      cout << "The prev node is " << previous << endl;
      cout << " " << endl;

      //out of bounds
      if ((l1data < 0) || (l1data > 9)) {
         cout << l1data << " is out of bounds: delete it." << endl;
         //delete it
         //if head
         if (current == L1Head) {
            L1Head = L1Head->link;
            Node *killMe = current;
            current = L1Head;
            prev = current;
            delete killMe;
         } else {
            //if body
            Node *killMe = current;
            prev->link = current->link;
            current = current->link;
            delete killMe;
         }

         cout << "L1Head: ";
         ShowAll(cout, L1Head);
         cout << "L2Head: ";
         ShowAll(cout, L2Head);
         cout << "L3Head: ";
         ShowAll(cout, L3Head);
      }

      // == 6
      if (l1data == 6) {
         cout << "This is 6. Keep it." << endl;
         current = current->link;
         // I may need to update previous pointer a 6 isn't at Head

         cout << "L1Head: ";
         ShowAll(cout, L1Head);
         cout << "L2Head: ";
         ShowAll(cout, L2Head);
         cout << "L3Head: ";
         ShowAll(cout, L3Head);
      }

      // 7-9
      if ((l1data >= 7) && (l1data <=9)) {
         cout << "On 7-9 entrance:" << endl;
         cout << "Previous: " << prev->data << endl;
         cout << "Current: " << current->data << endl;
         cout << "Next: " << current->link->data << endl;
         prev->link = current->link;
         cout << "Previous is still: " << prev->data << endl;
         cout << "Previous points to: " << prev->link->data << endl;
         otherListPtr = current;
         current = current->link;

         if (L3Head == 0) {
            L3Head = otherListPtr;
            L3Head->link = 0;
         } else {
            Node *cursorL3 = L3Head;
            while (cursorL3 != 0) {
               cout << "Looking for the tail for L3" << endl;
               cursorL3 = cursorL3->link;
            }
            cursorL3 = otherListPtr;
            cursorL3->link = 0;
         }

         cout << "Current is now: " << current->data << endl;
         cout << "Next is now: " << current->link->data << endl;

         cout << "L1Head: ";
         ShowAll(cout, L1Head);
         cout << "L2Head: ";
         ShowAll(cout, L2Head);
         cout << "L3Head: ";
         ShowAll(cout, L3Head);
      }


      // 0-5
      if ((l1data >= 0) && (l1data <= 5)) {
         cout << "On 0-5 entrance:" << endl;
         cout << "Previous: " << prev->data << endl;
         cout << "Current: " << current->data << endl;
//         cout << "Next: " << current->link->data << endl;
         prev->link = current->link;
//         cout << "Previous is still: " << prev->data << endl;
//         cout << "Previous points to: " << prev->link->data << endl;
         otherListPtr = current;
         cout << "Other list pointer: " << otherListPtr->data << endl;

         if (L2Head == 0) {
            L2Head = otherListPtr;
            L2Head->link = 0;
         } else {
            Node *cursorL2 = L2Head;
            while (cursorL2->link != 0) {
               cout << "Looking for the tail for L2" << endl;
               cout << cursorL2->data << endl;
               cursorL2 = cursorL2->link;
            }
//            cout << "The end of L2 is: " << cursorL2 << endl;
//            cout << "Other list pointer: " << otherListPtr->data << endl;
            otherListPtr->link = 0;
            cursorL2->link = otherListPtr;

            current = current->link;
//            break;

         }

         cout << "L1Head: ";
         ShowAll(cout, L1Head);
         cout << "L2Head: ";
         ShowAll(cout, L2Head);
         cout << "L3Head: ";
         ShowAll(cout, L3Head);
      }

   }

   cout << " " << endl;
   cout << "FINAL:" << endl;
   cout << "L1Head: ";
   ShowAll(cout, L1Head);
   cout << "L2Head: ";
   ShowAll(cout, L2Head);
   cout << "L3Head: ";
   ShowAll(cout, L3Head);
}


