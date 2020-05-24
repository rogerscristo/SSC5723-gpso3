#ifndef CIRCULAR_LINKED_LIST
#define CIRCULAR_LINKED_LIST

class Node {
  public:
		int key;
		int data;
		Node *next;
		Node();
		Node(int, int);
};

class CircularLinkedList {
	public:
		Node *head;
		CircularLinkedList();
		Node *NodeExists(int);
		void AppendNode(Node *);
		void PrependNode(Node *);
		void InsertNode(int, Node *);
		void DeleteNode(int);
		void UpdateNode(int, int);
		void DisplayList();
		void CountList();
};

#endif
