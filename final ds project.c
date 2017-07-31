#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
struct screen{
	int board_n;
	int no_of_zones ;
	int **board ;
	int **next ;
};

struct ZONE{
	long int live_rule;
	long int dead_rule;
	long int inclusion;
};

struct node{
    int data;
    struct node *next;
    struct node *child;
}*zone_trees[3];

struct node *make_tree(long int inclus,int gr){
	struct node *tree=malloc(sizeof(struct node *));
	long int temp=inclus;
	int r;
	int tra=gr*gr-1;
	while(tra>=0){
		r=temp%10;
		if(r==1){
			int vertical=tra/gr;
			int horizontal=tra%gr;
			struct node *new1=malloc(sizeof(struct node *));
			struct node *new2=malloc(sizeof(struct node *));
			new1->data=vertical;
			new2->data=horizontal;
			new2->next=NULL;
			new2->child=NULL;
			new1->child=new2;
			if(tree->child==NULL){
				tree->child=new1;
				new1->next=NULL;
			}
			else{
				struct node *t;
				t=tree->child;
				while(t->next!=NULL){
					t=t->next;
				}
				new1->next=NULL;
				t->next=new1;
			}
		}
	tra=tra-1;
	temp=temp/10;
	}
return tree;
}

struct node *make_tree1(long int inclus,int gr){
	struct node *tree=malloc(sizeof(struct node *));
	long int temp=inclus;
	int r;
	int tra=gr*gr-1;
	while(tra>=0){
		r=1;
		if(r==1){
			int vertical=tra/gr;
			int horizontal=tra%gr;
			struct node *new1=malloc(sizeof(struct node *));
			struct node *new2=malloc(sizeof(struct node *));
			new1->data=vertical;
			new2->data=horizontal;
			new2->next=NULL;
			new2->child=NULL;
			new1->child=new2;
			if(tree->child==NULL){
				tree->child=new1;
				new1->next=NULL;
			}
			else{
				struct node *t;
				t=tree->child;
				while(t->next!=NULL){
					t=t->next;
				}
				new1->next=NULL;
				t->next=new1;
			}
		}
	tra=tra-1;
	
	}
return tree;
}
int getNextState(int x1, int y1, struct screen *context, struct ZONE zone)
{	int sum=0;
     int x = x1+1, y = y1+1;
     
     sum = context->board[x-1][y-1]+context->board[x-1][y]+context->board[x-1][y+1]+context->board[x][y-1]+context->board[x][y+1]+context->board[x+1][y-1]+context->board[x+1][y]+context->board[x+1][y+1];
          
	if(context->board[x][y]==1){
		long int temp;
		temp=zone.live_rule;
		int i=8;
		while(i>sum){
			temp/= 10;
			i--;
		}
		return temp%10;
	}
	else{
		long int temp;
		temp=zone.dead_rule;
		int i=8;
		while(i>sum){
			temp/= 10;
			i--;
		}
		return temp%10 ;
	}
	return 0;
}

void getNext(struct screen *context,struct ZONE zone)
{
	int i;
	//iterate through zones
	for(i=0;i<context->no_of_zones;i++)
	{
		//run getNextState for each cell in the tree, with the correct zone(context->zones[i])
		struct node* curr = zone_trees[i];
		curr=curr->child;
		while(curr!=NULL)
		{
			context->next[curr->data+1][(curr->child)->data+1] = getNextState(curr->data,(curr->child)->data,context,zone);
			curr=curr->next;
		}
	}
	int** temp = context->next;
	context->next = context->board;
	context->board = temp;
}
void display(struct screen *context){
	int i,j;
	printf("\n");
	for(i=0;i<context->board_n+2;i++){
        for(j=0;j<context->board_n+2;j++){
           printf(" %d ",context->board[i][j]);
        }
        printf("\n");
     }
}

void standard(){

	struct screen *project=malloc(sizeof(struct screen));

	int i;int j;
	project->board_n=20;


	//allocating memory
	project->board=(int**)malloc(sizeof(int*)*(project->board_n+2));
	for(i=0;i<project->board_n+2;i++){
		project->board[i]=(int *)malloc(sizeof(int)*(project->board_n+2));
	}
	
	project->next=(int**)malloc(sizeof(int*)*(project->board_n+2));
	for(i=0;i<project->board_n+2;i++){
		project->next[i]=(int *)malloc(sizeof(int)*(project->board_n+2));
	}
	for(i=0;i<project->board_n+2;i++){
			for(j=0;j<project->board_n+2;j++){
				project->next[i][j]=0;
				project->board[i][j]=0;
			}
	}
	printf("\tINITIAL STATES -\n\t1-FLIP FLOP\n\t2-GLIDER\n\t3-FLOWER PATTERN\n\t4-SPACE SHIP\n\t5-BOAT(stable)\n");
	int st;scanf("%d",&st);
	if(st==1){
		project->board[11+1][10+1]=1;
		project->board[11+1][11+1]=1;
		project->board[11+1][12+1]=1;
	}
	else if(st==2){
		project->board[10+1][10+1]=1;
		project->board[10+1][11+1]=1;
		project->board[10+1][12+1]=1;
		project->board[11+1][10+1]=1;
		project->board[12+1][11+1]=1;
	}
	else if(st==3){
		project->board[8+1][5+1]=1;
		project->board[8+1][6+1]=1;
		project->board[8+1][7+1]=1;
		project->board[7+1][6+1]=1;
	}
	else if(st==4){
		project->board[10+1][11+1]=1;
		project->board[10+1][14+1]=1;
		project->board[11+1][10+1]=1;
		project->board[12+1][10+1]=1;
		project->board[12+1][14+1]=1;
		project->board[13+1][10+1]=1;
		project->board[13+1][11+1]=1;
		project->board[13+1][12+1]=1;
		project->board[13+1][13+1]=1;
	}
	else if(st==5){
		project->board[10+1][10+1]=1;
		project->board[10+1][11+1]=1;
		project->board[11+1][10+1]=1;
		project->board[12+1][11+1]=1;
	}


	int z,j1;project->no_of_zones=1;
	zone_trees[project->no_of_zones];
	struct ZONE zone[project->no_of_zones];

	for(i=0;i<project->no_of_zones;i++){
		printf("enter zone live_rule and dead_rule bit strings - \n");
		scanf("%ld",&zone[i].live_rule);
		scanf("%ld",&zone[i].dead_rule);
		zone[i].inclusion=11;

		zone_trees[i]=make_tree1(zone[i].inclusion,project->board_n);
	}
	for(j1=0;j1<300;j1++){
		display(project);
		system("clear");
		usleep(250000);
		for(i=0;i<project->no_of_zones;i++){
			getNext(project,zone[i]);
		}
	}
}
void user(){

	struct screen *project=malloc(sizeof(struct screen));

	printf("enter the board size = ");
	int i;int j;
	scanf("%d",&project->board_n);


	//allocating memory
	project->board=(int**)malloc(sizeof(int*)*(project->board_n+2));
	for(i=0;i<project->board_n+2;i++){
		project->board[i]=(int *)malloc(sizeof(int)*(project->board_n+2));
	}
	
	project->next=(int**)malloc(sizeof(int*)*(project->board_n+2));
	for(i=0;i<project->board_n+2;i++){
		project->next[i]=(int *)malloc(sizeof(int)*(project->board_n+2));
	}
	for(i=0;i<project->board_n+2;i++){
			for(j=0;j<project->board_n+2;j++){
				project->next[i][j]=0;
				project->board[i][j]=0;
			}
	}
	
	printf("\tPROVIDE THE INITIAL STATES \nnumber of states that are high are = ");
	int m,c1,c2;scanf("%d",&m);
	for(int i=0;i<m;i++){
		printf("enter x & y co-ordinates = ");
		scanf("%d %d",&c1,&c2);
		project->board[c1+1][c2+1]=1;
	}


	printf("enter number of zones = ");
	int z;
	scanf("%d",&project->no_of_zones);
	zone_trees[project->no_of_zones];
	struct ZONE zone[project->no_of_zones];

	for(i=0;i<project->no_of_zones;i++){
		printf("enter zone live_rule and dead_rule bit strings - \n");
		scanf("%ld",&zone[i].live_rule);
		scanf("%ld",&zone[i].dead_rule);
		printf("enter inclusion rule bit string - \n");
		scanf("%ld",&zone[i].inclusion);

		zone_trees[i]=make_tree(zone[i].inclusion,project->board_n);
	}
	for(j=0;j<300;j++){
		display(project);
		system("clear");
		usleep(250000);
		for(i=0;i<project->no_of_zones;i++){
			getNext(project,zone[i]);
		}
	}
}
void main(){
	printf("\tWELCOME TO THE GAME OF LIFE\n\tPLAY OPTIONS -\n\n");
	printf("\t1-STANDARD GAME OF LIFE RULES (sir.micheal convoy)\n\t2-USER DEFINED RULES\n");
	int choice;scanf("%d",&choice);
	if(choice==1){
		standard();
	}
	else if(choice==2){
		user();
	}
	else{
		printf("IN-VALID CHOICE--PLEASE try AGAIN !\n");
	}
}