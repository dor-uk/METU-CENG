#include "LinkedList.h"

template<class T>
LinkedList<T>::LinkedList()
{
    head=NULL;
    size=0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    head = NULL;
    size = 0;
    *this = obj;
}
template<class T>
LinkedList<T>::~LinkedList()
{
    if (head != NULL)
    {
        Node<T>* temp = head;
        Node<T>* temp_next = NULL;

        do
        {
            temp_next = temp->next;
            delete temp;
            temp = temp_next;
        }         
        while (temp != head);

    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if(this != &rhs)
    {
        removeAllNodes();
        
        Node<T>* curr = rhs.head;
        
        while(curr->next != rhs.head)
        {
            append(curr->data);
            curr = curr->next;
        }
        
        append(curr->data);
        
        size = rhs.size;
    }
    
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}


template<class T>
bool LinkedList<T>::isEmpty() const
{
    return (head == NULL);
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    Node<T>* temp = head;

    if(head == NULL)
    {
        return false;
    }
    
    if (temp == node)  /*temp->data == node->data*/
    {
        return true;
    }

    temp = temp->next;

    while (temp != head)
    {
        if (temp == node)
        {
            return true;
        }
        else
        {
            temp = temp->next;
        }
    }

    return false;
    
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    Node<T>* first = head;

    if (first == NULL)
    {
        return NULL;
    }
    else
    {
        return first;
    }
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    Node<T>* last = head;

    if (last == NULL)
    {
        return NULL;
    }

    else
    {
        last = last->prev;
        return last;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        Node<T>* temp = head;

        do
        {
            if (temp->data == data)
            {
                return temp;
            }
            temp = temp->next;
        }

        while (temp != head);

    }
    return NULL;

}
template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const  //geri don
{
    if((index<size) && (index>=0))
    {
        Node<T>*node = head;
        int i = 0;
        
        while(node->next != head)
        {
            if(i == index)
            {
                return node;
            }
            
            i++;
            node = node->next;
        }
        
        if(i == index)
        {
            return node;
        }
    }
    
    return NULL;
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    if (head == NULL)
    {
        Node<T>* new_node = new Node<T>(data);
        new_node->next = new_node->prev = new_node;
        head = new_node;
    }

    else
    {
        Node<T>* new_node = new Node<T>(data);

        Node<T>* last = head->prev;

        new_node->next = head;
        head->prev = new_node;
        new_node->prev = last;
        last->next = new_node;
    }
    size++;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    if (head == NULL)
    {
        Node<T>* new_node = new Node<T>(data);
        new_node->next = new_node->prev = new_node;
        head = new_node;
    }
    else
    {
        Node<T>* last = head->prev;   //segfault?????????????
        
        Node<T>* new_node = new Node<T>(data);
        
        new_node->next = head;
        new_node->prev = last;
        
        last->next = head->prev = new_node;
        
        head = new_node;
    }
    
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if(node != NULL)
    {
       if(this->containsNode(node))
       {
           
           size++;
           Node<T> *newNode = new Node<T>(data);
           
           if(node->next == node)
           {
               newNode->prev = head;
               newNode->next = head;
               
               head->next = newNode; 
               head->prev = newNode;
               
               
            }
           
           
           else
           {
               newNode->prev = node; 
               newNode->next = node->next; 
               
               node->next->prev = newNode;
               node->next = newNode; 
               
               
            }
           
           
        }
       
      
    }
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    int i, count;
    Node<T>* temp = head;
    
    count = 0;
    
    while (temp->next != head)
    {
        temp = temp->next;
        count++;
    }
    count++;
    
    if(temp == NULL || count<=index)
    {
        return;
    }
    
    if(index == 0)
    {
        if(temp == NULL)
        {
            Node<T>* new_node = new Node<T>(data);
            new_node->next = new_node->prev = new_node;
            head = new_node;
        }
        
        else
        {
            Node<T>* new_node = new Node<T>(data);
            while(temp->next != head) 
            {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->prev = temp;
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }
    else
    {
        Node<T>* current = head;
        Node<T>* new_node = new Node<T>(data);
        
        for(i = 0;i < (index-1);i++)
        {
            current = current->next;
        }
        
        new_node->next = current->next;
        (current->next)->prev = new_node;
        current->next = new_node;
        new_node->prev = current;
    }
    size++;
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    int index = 0;
    int control = 0;

    Node<T>* temp = head;

    if (temp != NULL)
    {
        while (temp->next != head)
        {
            if(temp == node)
            {
               control = 1;
               return index; 
            }
            
            index++;
            temp = temp->next;
        }

        if(temp == node)
        {
            control = 1;
            return index;
        }
        
        
        if (control == 0)
        {
            return -1; /*listenin icinde bulamadik*/
        }
    }
    else
    {
        return -1;  /*liste bos ise*/
    }
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    int j;
    if(currentIndex >= size)
    {
        
        return;
        
    }

    if(currentIndex == newIndex)
    {
        return;
    }
    
    if(currentIndex < 0)
    {
        return;
    }

    Node<T>* temp = head;
    Node<T>* current = head;

    for(j = 0;j < (currentIndex);j++)
    {
        temp = temp->next;
    }
    
    
    (temp->prev)->next = temp->next;
    (temp->next)->prev = temp->prev;
    
    
    if(currentIndex == 0)
    {
        head = head->next;

    }
    
    
    
    if(newIndex == size-1)  //infinite loop yapiyo  //halloldu
    {
        //std::cout<<1<<'\n';
        (head->prev)->next = temp;
        temp->prev = head->prev;
        temp->next = head;
        head->prev = temp;
        
        return;
    }

    
    
    if(newIndex == 0)
    {
        //std::cout<<1<<'\n';
        (head->prev)->next = temp;
        temp->prev = head->prev;
        temp->next = head;
        head->prev = temp;
        
        head = temp;
        return;
    }
    else
    {
        Node<T>* find_loc = head;
        int i = 0;
        
        while(find_loc->next != head)
        {
            if(i == newIndex)
            {
                break;
            }
            i++;
            find_loc = find_loc->next;
        }
        
        /*if(currentIndex == 0)
        {
            head = head->next;

            temp->next = find_loc->next;
            (temp->prev)->next = find_loc;
            temp->prev = find_loc;
            find_loc->next = temp;
            return; 

        }*/
        
        
        /*if(newIndex-currentIndex == 1)
        {
            temp->next = find_loc->next;
            (temp->prev)->next = find_loc;
            temp->prev = find_loc;
            find_loc->next = temp;
            return; 
        }*/

        

        (find_loc->prev)->next = temp;
        temp->prev = find_loc->prev;
        temp->next = find_loc;
        find_loc->prev = temp;
    }

    /*if((currentIndex<size)&&(currentIndex>-1)&&(currentIndex!=newIndex)&&(newIndex>-1)){
        if(newIndex<size){
            Node<T>* current=head;
            Node<T>* newin=head;
            Node<T>* p;
            Node<T>* a;
            int c=0,n=0;
            while(c!=currentIndex){
                current=current->next;
                c++;
            }
            while(n!=newIndex){
                newin=newin->next;
                n++;
            }
            if(currentIndex>newIndex){
                if(currentIndex== size-1 && newIndex==0){
                    head=current;
                }
                else if(currentIndex!= size-1 && newIndex==0){
                    a=current->prev;
                    p=newin->prev;
                    a->next=current->next;
                    current->next->prev=a;
                    p->next=current;
                    current->prev=p;
                    current->next=newin;
                    newin->prev=current;
                    head=current;
                }
                else{
                    a=current->prev;
                    p=newin->prev;
                    a->next=current->next;
                    current->next->prev=a;
                    p->next=current;
                    current->prev=p;
                    current->next=newin;
                    newin->prev=current;
                }
            }
            else{
                if(currentIndex==0 && newIndex!=size-1){
                    head=head->next;
                    a=current->prev;
                    p=newin->next;
                    a->next=current->next;
                    current->next->prev=a;
                    newin->next=current;
                    current->prev=newin;
                    current->next=p;
                    p->prev=current;
                }
                else if(currentIndex==0 && newIndex==size-1){
                    head=head->next;
                }
                else{
                    a=current->prev;
                    p=newin->next;
                    a->next=current->next;
                    current->next->prev=a;
                    newin->next=current;
                    current->prev=newin;
                    current->next=p;
                    p->prev=current;   
                }
            }
        }
        else{
            Node<T>* cur=head;
            Node<T>* cu=head;
            Node<T>* curre;
            int b=0;
            while(b!=currentIndex){
                b++;
                cur=cur->next;
            }
            while(cu->next!=head){
                cu=cu->next;
            }
            if(cur==head){
                head=head->next;
            }
            else if(cur!=head&&currentIndex!=size-1){
                curre=cur->prev;
                curre->next=cur->next;
                cur->next->prev=curre;
                cu->next=cur;
                cur->prev=cu;
                cur->next=head;
                head->prev=cur;
            }
        }
    }*/

}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if(head == NULL)
    {
        return;
    }
    
    Node<T>* current = head;
    Node<T>* first_prev = NULL;
    
    while(current != node)
    {
        if(current->next == head)
        {
            return;
        }
        
        first_prev = current;
        current = current->next;
    }
    
    if (current->next == head && first_prev == NULL) {
        head = NULL;
        delete (current);
        size -= 1;
        return;
    }
    
    if(current == head)
    {
        first_prev = head->prev;
        head = current->next;
        first_prev->next = head;
        head->prev = first_prev;
        
        delete  (current);
        size -= 1;
        
    }
    
    else if(current->next == head)
    {
        first_prev->next = head;
        head->prev = first_prev;
        
        delete (current);
        size -= 1; 
        
    }
    
    else
    {
        Node<T>* temp = current->next;
        
        first_prev->next = temp;
        temp->prev = first_prev;
        
        delete (current);
        size -= 1;
        
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) //geri don
{
    if(head)
    {
        Node<T>* current = head;
        
        while((data) != (current->data))
        {
            current = current->next;
        }
        
        if((data) == (current->data))
        {
            removeNode(current);
        }
    }
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)   // geri don
{
    if(index<size && (head != NULL))
    {
        Node<T>* current=head;
        int i = 0;
        
        while(i != index)
        {
            current = current->next;
            i++;
        }
        
        removeNode(current);
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    if(head == NULL)
    {
        return;
    }
    
    if (head != NULL)
    {
        Node<T>* curr = head->next;
        while (curr != NULL && curr != head)
        {
            Node<T>* temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete head;
        head = NULL;
    }
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}
