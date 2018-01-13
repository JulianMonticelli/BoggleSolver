#include "DLBTrie.h"


CharNode::CharNode(char c)
{
	character = c;
	if (c != '\0')
	{
		child = new DLBNode();
	}
}
CharNode::~CharNode()
{

}

	


DLBNode::DLBNode()
{
	// No constructor required?
}
DLBNode::~DLBNode()
{
	// delete code not implemented
}


// This function will return true if a character node exists in
// the sublist and false if there is no such node
bool DLBNode::hasCharNode(char c)
{
	CharNode * curr = head;
	while (curr != NULL)
	{
		if (curr->character == c)
		{
			return true;
		}
		curr = curr->next;
	}
	return false;
}

// This function only returns an existing CharNode
// or NULL
CharNode * DLBNode::getCharNode(char c)
{
	CharNode * curr = head;
	while (curr != NULL)
	{
		if (curr->character == c)
		{
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

// This function will return the existing character node
// or create a new one, placed in sorted order, and return it
CharNode * DLBNode::getOrCreateCharNode(char c)
{
	if (head == NULL)
	{
		head = new CharNode(c);
		return head;
	}
	CharNode * curr = head;
	while (curr != NULL)
	{
		if (curr->character == c)
		{
			return curr;
		}
		if (curr->character < c && (curr->next == NULL || curr->next->character > c))
		{
			CharNode * temp = curr->next;
			CharNode * newCharNode = new CharNode(c);

			// Patch linked list to insert inbetween
			curr->next = newCharNode;
			newCharNode->next = temp;

			return newCharNode;
		}
		curr = curr->next;
	}
	return NULL; // This should never happen
}

DLBTrie::DLBTrie()
{
	root = new DLBNode();
}
DLBTrie::~DLBTrie()
{
	// delete code not implemented
}
	
	

void DLBTrie::addWord(std::string word)
{
	DLBNode * curr = root;

	for (char c: word)
	{
		curr = curr->getOrCreateCharNode(c)->child;
		if (curr == NULL) // Children of '\0' will be null
		{
			return;
		}
	}
	curr->getOrCreateCharNode('\0');
}

