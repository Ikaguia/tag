#ifndef LISTAHPP
#define LISTAHPP

class listIntNode{
public:
	int val;
	listIntNode* next;

	listIntNode(int v):val{v},next{nullptr}{}
};

class listInt{
public:
	int size;
	listIntNode* first;
	listIntNode* last;

	listInt():size{0},first{nullptr},last{nullptr}{}

	//empurra um elemento ao fim da lista
	void push(int val){
		if(size==0){
			last = new listIntNode(val);
			first = last;
		}
		else{
			last->next = new listIntNode(val);
			last = last->next;
		}
		size++;
	}
	//remove o primeiro elemento da lista
	void pop(){
		if(size>0){
			listIntNode* temp = first;
			first = first->next;
			delete temp;
			size--;
			if(size==0)last=nullptr;
		}
	}
	//encontra a referencia de val na lista e retorna nullptr se ela nao existe
	listIntNode* find(int val){
		listIntNode* it=first;
		while(it!=nullptr){
			if(it->val==val)break;
			it=it->next;
		}
		return it;
	}
	//limpa a lista
	void clear(){
		delete first;
		first=nullptr;
		last=nullptr;
		size=0;
	}
	//copia uma outra lista
	void copy(const listInt &other){
		clear();
		listIntNode* it = other.first;
		while(it!=nullptr){
			push(it->val);
			it=it->next;
		}
	}
};

#endif//LISTAHPP
