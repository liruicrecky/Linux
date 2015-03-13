/*************************************************************************
	> File Name: main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Fri 13 Mar 2015 02:39:10 PM CST
 ************************************************************************/

#include<iostream>

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

void addTwoNumbers(ListNode *l1, ListNode *l2) {
	
//	if(!l1)
	//	return l2;
//	if(!l2)
	//	return l1;

	ListNode *resHead = new ListNode(0);
    	ListNode *p = NULL, *s = NULL;
    	ListNode *pl1 = l1, *pl2 = l2;
    	int add = 0;
    
    	p = resHead;
    
    	while(pl1 != NULL && pl2 != NULL){
    		
    		s = new ListNode(pl1 -> val + pl2 -> val + add);
    		
    		add = s -> val / 10;
    		s -> val %= 10;
    
    		p -> next = s;
    		p = s;

    		pl1 = pl1 -> next;
    		pl2 = pl2 -> next;
    	}
    
    	while(pl1){
    		s = new ListNode(pl1 -> val + add);
    		add = s -> val / 10;
    		s -> val %= 10;
    		p -> next = s;
    		p = s;
    		pl1 = pl1 -> next;
    	}
    
    	while(pl2){
    		s = new ListNode(pl2 -> val + add);
    		add = s -> val / 10;
    		s -> val %= 10;
    		p -> next = s;
    		p = s;
    		pl2 = pl2 -> next;
    	}
    	
    	if(add > 0){
    	    s = new ListNode(add);
    	    p -> next = s;
    	}

	ListNode *tmp = resHead -> next;
	while(tmp){
		std::cout << tmp -> val << " -> ";
		tmp = tmp -> next;
	}

	while(resHead){
		ListNode *del = resHead;
		resHead = resHead -> next;
		delete del;
	}

}

int main(void)
{
	ListNode *l1, *l2;

	ListNode *tmp = new ListNode(4);
	l1 = tmp;
	tmp = NULL;
	tmp = new ListNode(6);
	l1 -> next = tmp;

	tmp = NULL;
	tmp = new ListNode(0);
	l2 = tmp;




	tmp = l1;
	while(tmp){
		std::cout << tmp -> val << " -> ";
		tmp = tmp -> next;
	}

	std::cout << std::endl;

	tmp = l2;
	while(tmp){
		std::cout << tmp -> val << " -> ";
		tmp = tmp -> next;
	}

	std::cout << std::endl;

	addTwoNumbers(l1, l2);	

	while(l1){
		ListNode *del = l1;
		l1 = l1 -> next;
		delete del;
	}
	l1 = NULL;

	while(l2){
		ListNode *del = l2;
		l2 = l2 -> next;
		delete del;
	}
	l2 = NULL;

	return 0;
}
