#include <iostream>
#include "CircularLinkedList.h"

using namespace std;

Node::Node() {

}

Node::Node(int key, int data) {

}

CircularLinkedList::CircularLinkedList() {

}

Node *CircularLinkedList::NodeExists(int) {

}

void CircularLinkedList::AppendNode(Node *newnode) {
  if (NodeExists(newnode->key) != NULL) {
    cout<<"Since node exists with key value : " <<newnode -> key;
    cout<<" so, node can't be prepended."<<endl;
  } else {
    if (head == NULL) {
      head = newnode;
      newnode->next = head;
      cout << "Node prepended at the head." << endl;
    } else {
      Node *pointer = head;
      while (pointer->next != head) {
        pointer = pointer -> next;
      }
      pointer -> next = newnode;
      newnode -> next = head;
      head = newnode;
      cout << "Node prepended." << endl;
    }
  }
}

void CircularLinkedList::PrependNode(Node *newnode) {
  if (NodeExists(newnode->key) != NULL) {
    cout<<"Since node exists with key value : " <<newnode->key;
    cout<<" so, node can't be prepended."<<endl;
  } else {
    if (head == NULL) {
      head = newnode;
      newnode->next = head;
      cout << "Node prepended at the head." << endl;
    } else {
      Node * pointer = head;
      while (pointer->next != head) {
        pointer = pointer->next;
      }
      pointer->next = newnode;
      newnode->next = head;
      head = newnode;
      cout << "Node prepended." << endl;
    }
  }
}

void CircularLinkedList::InsertNode(int k, Node *newnode) {
  Node * pointer = NodeExists(k);
  if (pointer == NULL) {
    cout << "Node does not exist with key:" << k << endl;
  } else {
    if (NodeExists(newnode->key) != NULL) {
      cout<< "Since node exists with key value : " << newnode->key;
      cout<< " so, node can't be inserted." <<endl;
    } else {
      if (pointer->next == head) {
        newnode->next = head;
        pointer->next = newnode;
        cout << "Node inserted at the end of the list." << endl;
      } else {
        newnode->next = pointer->next;
        pointer->next = newnode;
        cout << "Node inserted in between the list." << endl;
      }
    }
  }
}

void CircularLinkedList::DeleteNode(int k) {
  Node * pointer = NodeExists(k);
  if (pointer == NULL) {
    cout << "Node does not exist with key: " << k <<endl;
  } else {
    if (pointer == head) {
      if (head->next == head) {
        head = NULL;
        cout << "Head node is deleted and the list is now empty."<<endl;
      } else {
        Node * pointer1 = head;
        while (pointer1->next != head) {
          pointer1 = pointer1->next;
        }
        
        pointer1->next = head->next;
        head = head->next;
        cout << "Node deleted with key value : " << k << endl;
      }
    } else {
      Node *tmp = NULL;
      Node *prevpointer = head;
      Node *currentpointer = head->next;
      
      while (currentpointer != NULL) {
        if (currentpointer->key == k) {
          tmp = currentpointer;
          currentpointer = NULL;
        } else {
          prevpointer = prevpointer->next;
          currentpointer = currentpointer->next;
        }
      }

      prevpointer->next = tmp->next;
      cout << "Node deleted with key value : " << k << endl;
    }
  }
}

void CircularLinkedList::UpdateNode(int k, int newdata) {

}

void CircularLinkedList::DisplayList() {

}

void CircularLinkedList::CountList() {

}
