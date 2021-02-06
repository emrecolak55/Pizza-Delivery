#include <iostream>
#include <string>
#include <stdlib.h>
#define MAX_DRINKS 10
# define INGREDIENT_NUM 6
/*
Murat Emre Çolak
150180061
Hatice Köse
*/
/*
1. Chicken Pizza: mozarella, chicken, mushroom, corn, onion, tomato
2. Broccoli Pizza: mozarella, broccoli, pepperoni, olive, corn, onion
3. Sausage Pizza: mozarella, sausage, tomato, olive, mushroom, corn
*/

using namespace std;

	class Pizza{
	
	string name;
	string size;
	string crust_type;
	string* ingredients; 
	Pizza *next;
	
	public:
	bool istherenext(Pizza*);
	void printpizza(Pizza*);
	void nextpointer(Pizza*&);
	void pointnext(Pizza*,Pizza*);
	string printsize() {
		return size;
	}
	Pizza(){
		size = "medium";
		crust_type = "normal";
		ingredients = new string [INGREDIENT_NUM];
		ingredients[0] = "mozarella";
		next=NULL;
	}
	Pizza(string, string, int);
	Pizza(const Pizza&);
	~Pizza();
		
	};
	
	class Order {
		string name;
		Pizza *pizza;
		Order *next;
		int* drink;
		
		public:
		float getPrice();
		void printOrder(Order*);	
		void nextpointer(Order*&);
		void pointnext(Order*,Order*);
		void golastnode(Order*&);
		void gotopizza(Pizza*,Order*);
		void movingnext(Order*,Order*);
		bool istherenext(Order*);
		bool checkname(Order*,string);
		bool checkpointer(Order*,Order*);
		Order(string givenName, Pizza *givenPizza, int* givenDrink){
			name = givenName;
			pizza = givenPizza;
			next = NULL;
			drink = new int[MAX_DRINKS]; 
			for( int i=0; i<MAX_DRINKS;i++){
				drink[i] = givenDrink[i]; 
			}
		}
		Order(string givenName, Pizza *givenPizza){
			name = givenName;
			pizza = givenPizza;
			next = NULL;
			drink = NULL;
		}
		~Order();
	};
	
	class OrderList {
		int n;
		Order *head;
		
		public:
		void takeOrder();
		void listOrders();
		void deliverOrders();
		
		OrderList(){
			n=0;
			head= NULL;
		}
		~OrderList();
		
	};
	
	
	
	int main() {
		OrderList creator;
		int x;	
	
		while(x!=4) {
			cout<< "Welcome to Emre Pizza"<< endl;
			cout << "1. Add an order" << endl;
			cout << "2. List orders"<< endl;
			cout << "3. Deliver orders" << endl ;
			cout << "4. Exit" << endl; 
		
			cin >>x;
			if ( x ==1) {
				creator.takeOrder();
			}
			if(x == 2) {
				creator.listOrders();
			}
			if(x==3) {
				creator.deliverOrders();
			}
			if ( x== 4) {
				return 0;
			}
		}
		return 0;
	}
	

		
	void OrderList::deliverOrders(){
		listOrders();
		string promotion;
		char a;
		string name;
		float price;
		cout << endl << "Please choose order which you want to deliver. Name: ";
		cin >> name;
		cout << endl << "Following order is delivering...";
		Order* temp = head;
		while(temp->istherenext(temp)) {
			if(temp->checkname(temp,name)) {
				temp->printOrder(temp);
				break;
			}
			temp->nextpointer(temp);
		}

		price = temp->getPrice();
		cout << "Total Price: " << price;
		cout << endl << "Do you have a promotion code?(y/n) ";
		cin >> a;
		if( a == 'n') {
			cout << "The order is delivered successfully.";
		}
		else if(a == 'y') {
			cout << "Enter your code: ";
			cin.ignore();
			getline(cin,promotion);
			if (promotion == "I am student") {
				price = (price*9)/10;
				cout << endl << "New Price: " << price;
				cout << endl << "Your order is delivered successfully";
			}
		}
		else {
			cout << "You didnt enter y or n. There will be no discount" << endl;
			cout << "Order delivered successfully ";
		}
		if(temp == head) {
			head->nextpointer(head);
			free(temp);
		}
		else  {
			Order* traverse = head;
			while(!traverse->checkpointer(traverse,temp)) {
				traverse->nextpointer(traverse);
			}
			traverse->movingnext(traverse,temp);
			free(temp);
		}
		
		
	}


void OrderList::takeOrder(){
		int pizzatype,amount;
		string crust_type,size,name;
		int *drink;
		Order *orderptr;
		Order *ordertemp;
		Pizza *temp;
	cout << "1. Chicken Pizza: mozarella, chicken, mushroom, corn, onion, tomato" << endl;
	cout <<	"2. Broccoli Pizza: mozarella, broccoli, pepperoni, olive, corn, onion" << endl;
	cout <<	"3. Sausage Pizza: mozarella, sausage, tomato, olive, mushroom, corn"<<endl;
	cout << "Enter pizza type: " << endl;
	cin >> pizzatype;
	cout << "Select size small15 medium20 big25 ";
	cin >> size;
	cout << " Select crust type thin normal thick";
	cin >> crust_type;
	cout << "Enter the amount of pizzas";
	cin >> amount;
	Pizza *ptr = new Pizza(size,crust_type,pizzatype);
	
	if ( amount > 1) {
		for(int i=1 ; i<amount ; i++){
			temp = ptr;
			Pizza *ptr2 = new Pizza(*ptr);
				while(temp->istherenext(temp)){
			ptr->nextpointer(temp);
			}
		ptr->pointnext(temp,ptr2);
		
		}
	}

	drink = new int[MAX_DRINKS];
	cout << "Please choose your drink" << endl;
	cout << "0- No Drink" << endl;
	cout << "1- Cola 4 TL"<< endl;
	cout << "2- Soda 2 TL"<< endl;
	cout << "3- Ice Tea 3 TL"<< endl;
	cout << "4- Fruit Juice 3.5 TL"<< endl;
	cout << "Press -1 to save your order"<< endl; 
	int drink2;
	for( int i=0; i<100 ; i++) { 
		cin >> drink2;
		if ( drink2 == -1) { break; }
		drink[i] = drink2;
	}
	cout << "Please enter your name";
	cin >> name;
	cout << endl << "Your order is saved" << endl; 
	
	if(!drink[0] ) {
		orderptr = new Order(name , ptr);
		delete [] drink;
	}
	else {
		orderptr = new Order(name , ptr, drink);
		delete [] drink; 
	}
	
	if( head == NULL) {
		head = orderptr;
	}
	else {
		ordertemp = head; 
		ordertemp->golastnode(ordertemp); 
		
		ordertemp->pointnext(ordertemp, orderptr);
	}
	orderptr->printOrder(orderptr);
}
	
	void OrderList::listOrders(){
		Order *temporary = head;
		Pizza *traverse;
		while(temporary){

			temporary->printOrder(temporary);

			temporary->nextpointer(temporary);

		}

	}
	///////////////////////////////// ORDERLIST FUNCTIONS OVER ///////////////////////////////////////////
	
	Pizza::Pizza(const Pizza& copied) {
		name= copied.name;
		size= copied.size;
		crust_type= copied.crust_type;
		ingredients = new string [6];
			for(int i=0;i<6;i++){
				ingredients[i]= copied.ingredients[i];
		}
		next=NULL;
		cout << "Enter the number of ingredient you want to remove from your pizza" << endl;
			
		for(int i=0;i<INGREDIENT_NUM;i++)
			cout << i+1 << "."<<copied.ingredients[i]<<endl;
		cout << "Press 0 to exit"<< endl;
		int i;
		while(1) {
			cin >> i;
			if( !i){break;}
				ingredients[i-1] = "\0";
		}
	
	}
	
	void Pizza::nextpointer(Pizza* &givenpointer) {
		givenpointer = givenpointer->next;
		
	}
	void Pizza::pointnext(Pizza *temp,Pizza *ptr) {
		temp->next=ptr;
	}
	
	void Pizza::printpizza(Pizza *print){

		cout << print->name << "(";
		for(int j=0; j<INGREDIENT_NUM; j++){
			if(ingredients[j] == "\0" ) {
				continue;
			}
			cout << print->ingredients[j] << ", ";
		
		}
		cout << ")" << endl;
		cout << "size: " << print->size<< " ";
		cout << "crust: " << print->crust_type<<endl << endl;
	}
	
	bool Pizza::istherenext(Pizza *check){
		if(check->next) {
			return 1;
		}
		else{
			return 0;
		}
	}
		Pizza::Pizza(string givenSize, string givenCrust_type, int givenPizza_type){ 
		size = givenSize;
		crust_type = givenCrust_type;
		next=NULL;
		switch (givenPizza_type) {
		
			case 1:
				name = "Chicken Pizza";
				ingredients = new string [6];
				ingredients[0] = "mozarella";
				ingredients[1] = "chicken";
				ingredients[2] = "mushroom";
				ingredients[3] = "corn";
				ingredients[4] = "onion";
				ingredients[5] = "tomato";
				break;
			case 2:
				name = "Broccoli Pizza";
				ingredients = new string [6];
				ingredients[0] = "mozarella";
				ingredients[1] = "broccoli";
				ingredients[2] = "pepperoni";
				ingredients[3] = "olive";
				ingredients[4] = "corn";
				ingredients[5] = "onion";
				break;
			case 3:
				name = "Sausage Pizza";
				ingredients = new string [6];
				ingredients[0] = "mozarella";
				ingredients[1] = "sausage";
				ingredients[2] = "tomato";
				ingredients[3] = "olive";
				ingredients[4] = "mushroom";
				ingredients[5] = "corn";
				break;
			}
	}
////////////////////////////////////////////////////////// PIZZA FUNCTIONS OVER //////////////////////////////////	
	void Order::nextpointer(Order* &givenpointer) {
		givenpointer = givenpointer->next;
		
	}
	void Order::pointnext(Order *temp,Order *ptr) {
		temp->next=ptr;
	}
	
	void Order::gotopizza(Pizza *ptr1 , Order *ptr2) {
		ptr1=ptr2->pizza;
	}
	
	void Order::golastnode(Order *&ptr){
		while(ptr->next) {
			ptr=ptr->next;
		}
	} 
	
		bool Order::istherenext(Order *check){
		if(check->next) {
			return 1;
		}
		else{
			return 0;
		}
	}
	
		bool Order::checkname(Order* check, string name) {
			if(check->name == name) {
				return 1;
			}
			else {
				return 0;
			}
		}
		bool Order::checkpointer(Order* ptr1, Order* ptr2) {
			if(ptr1->next == ptr2 ) {
				return 1;
			}
			else {
				return 0;
			}
		}
		
		void Order::movingnext(Order* ptr1, Order* ptr2){
			ptr1->next = ptr2->next;
		}
	
	void Order::printOrder(Order *print){
		cout << "-----------------" << endl;
		cout<< "Name: "<<print->name << endl<<endl;
		Pizza *firstpizza = print->pizza;
		firstpizza->printpizza(firstpizza);
		
		while(firstpizza->istherenext(firstpizza)) {
			firstpizza->nextpointer(firstpizza);
			firstpizza->printpizza(firstpizza);

		}	
		
		string* drinks; 
			drinks = new string[4];
			drinks[0] = "Cola";
			drinks[1] = "Soda";
			drinks[2] = "Ice Tea";
			drinks[3] = "Fruit Juice";
		
		if( !print->drink) { 
			delete [] drinks;
			return;
		 }
		
		for ( int i=0; i<10 ; i++)
		 {
		 	if( !print->drink[i]) { break; }
	
			cout << drinks[print->drink[i]-1] << ", ";
		}
		delete [] drinks;
		cout << endl <<  "---------------------";
	}
	
	float Order::getPrice(){
		
		float price=0;
		
		for(int k=0; k<MAX_DRINKS ; k++) {
			if ( !drink) { break; }
			cout << drink[k] ;
				switch (drink[k] ){
				case 0:
				break;
				
				case 1:
				price+= 4;
				break;
				
				case 2:
				price+=2;
				break;
				
				case 3:
				price+=3;
				break;
				
				case 4:
				price+=3.5;
				break;
				
				
			}
	
		
		
		}
		
	while(pizza) {
			
		if ( pizza->printsize() == "small") {
			price+=15;
		}
		else if(pizza->printsize()== "medium") {
			price+=20;
		}
		else {
			price+=25;
		}
	
		
			
		pizza->nextpointer(pizza);
	}
	return price;
}
///////////////////////////////////////////////// ORDER FUNCS OVER /////////////////////////////////


	Pizza::~Pizza(){
		delete next;
		delete [] ingredients;
	}
	Order::~Order(){
		delete [] drink;
		delete next;
		delete pizza;
	}
	OrderList::~OrderList(){
		delete head;
	}
