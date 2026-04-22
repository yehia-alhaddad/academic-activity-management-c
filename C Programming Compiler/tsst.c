//Operating and maintaining a list
#include <stdio.h>
// void insertion();
// void deletion();
// void createlist();
// void display();
// int option,element,placefound;
// void menu();

// struct node
// {
// 	int data;
// 	struct node *next;
// }*newnode,*list,*prev,*temp,*tmpdisplay;

// void main(){	
// 	createlist();
// 	do {
// 		menu();
// 		switch (option){
// 		case 1: insertion();break;
// 		case 2: deletion();break;
// 		case 3: display();break;
// 		case 4: break;
// 		}
// 	}while (option !=4);
// }

// void createlist(){
// 	list=NULL;
// }
// void menu(){
// 	printf(" linked list\n");
// 	printf("1-- Insertion\n");
// 	printf("2-- Deletion\n");
// 	printf("3-- Display\n");
// 	printf("select your option\n");
// 	scanf("%d",&option);
// }

// void insertion(){
// 	newnode=(struct node*) malloc (sizeof(struct node));
// 	printf("enter the element:");
// 	scanf("%d",&element);
// 	newnode->data=element;
// 	newnode->next=NULL;
// 	if (list==NULL)
// 		list=newnode;
// 	else if(element<list->data){
// 			newnode->next=list;
// 			list=newnode;
// 		}else{
// 			temp=list;placefound=0;
// 			while(temp!=NULL && placefound==0){
// 				if(element>temp->data){
// 					prev=temp;
// 					temp=temp->next;
// 				} else
// 					placefound=1;
// 			}
// 			newnode->next=prev->next;
// 			prev->next=newnode;
// 		}
// }

// void deletion(){
// 	if (list==NULL)
// 		printf("list is empty");
// 		else if (element==list->data)
// 			list=list->next;
// 		else {
// 			temp=list;
// 			while(temp->data!=element){
// 				prev=temp;
// 				temp=temp->next;
// 			}
// 			prev->next=prev->next->next;
// 		}
// }

// void display()
// {
// 	if (list==NULL)
// 		printf("\n\nList is empty");
// 	else
// 	{
// 		tmpdisplay=list;
// 		while(tmpdisplay!=NULL)
// 		{
// 			printf("%d\n",tmpdisplay->data);
// 			tmpdisplay=tmpdisplay->next;
// 		}
// 	}
// }

#include <stdio.h>

int main(){
	int a[5], largest;
	
	printf("Enter 5 values to find the largest one:");
	for(int i=0;i<5;i++){
		scanf("%d", &a[i]);
	}
	for(int j=0;j<5;j++){
	if(a[j+1]>a[j]){
		largest = a[j+1];
		}
	}
	printf("the largest number is: %d", largest);
}