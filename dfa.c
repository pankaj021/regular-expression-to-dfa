#include<stdio.h>
#include<malloc.h>
#include<graphics.h>
#include<math.h>

int nfa_st_no=0,dfa_st_no=0,l=0,k=0,m=-1,no_of_ip_alph,no_of_eq_clss=0;
char alphabet[80],re[1875],path1[50],path2[55],take_str[10]="STRING",RE[1525],choice[30];
struct nfa_state{
  int state_name;
  char next_ip;
  struct nfa_state* next_trans1;
  struct nfa_state* next_trans2;    // for taking care of two epsilon moves from the state.
  int is_initial;
  int is_final;
  struct nfa_state* final_of_re;
  int visited_bfs;
  int visited_bfs2;
  int visited_dfs;
  struct node_list* e_closr_ptr;
  struct nfa_trans* trans_arr;
};

struct node_list{
  struct nfa_state* node;
  struct node_list* link;
};
struct nfa_trans{
  char ip_symbol;
  struct node_list *states;
  struct nfa_trans *link;
};
struct dfa_trans_node{
  char ip_symbol;
  struct dfa_state *next_state;
  struct dfa_trans_node *link;
};

struct dfa_state{
  int grp_head;
  int state_name;
  int is_initial;
  int is_final;
  struct dfa_trans_node *next_trans_ptr;
  int visited_bfs;
  int eq_class;
  struct dfa_state *link;
};
struct container_node{
  struct node_list *bulky_dfa_st;
  struct dfa_state *fair_dfa_st;
  struct container_node *link;
};
struct min_dfa{
  int color;
  int keep;
  int cen_x;
  int cen_y;
  int state_name;
  int is_initial;
  int is_final;
  struct trans_nod *next_trans_ptr;
  int visited_bfs;
};
struct trans_nod{
  char ip_symbol;
  struct min_dfa *next_state;
  struct trans_nod *link;
};

struct nfa_state* construct_nfa_with_e();
int L_paranthesis(char*,char*,struct nfa_state**);
int R_paranthesis(char*,char*,struct nfa_state**);
int union_optr(char*,char*,struct nfa_state**);
int concat_optr(char*,char*,struct nfa_state**);
int closure_optr(char*,char*,struct nfa_state**);
int dol_optr(char*,char*,struct nfa_state**);
struct nfa_state* r1_or_r2(struct nfa_state*,struct nfa_state*);
struct nfa_state* r1_concat_r2(struct nfa_state*,struct nfa_state*);
struct nfa_state* r_closure(struct nfa_state*);
struct nfa_state* a(char);
struct nfa_state* epsilon();
struct nfa_state* phi();
struct nfa_state* create_state();
int print_e_nfa(struct nfa_state*);
int fun_4_closr(struct nfa_state*);
int sort_and_insert_closr_list(struct node_list*,struct node_list*);
int nfa_without_e(struct nfa_state*);
int sort_and_insrt_trans_arr(struct node_list*,struct node_list*);
int bfs_trav_fun(struct nfa_state*);
struct nfa_trans *create_nfa_trans_node();
struct dfa_state *nfa_to_dfa(struct nfa_state*);
struct container_node* create_container_node();
struct dfa_trans_node *create_dfa_trans_node();
struct dfa_state *create_dfa_st();
struct container_node *matching_in_cont(struct container_node *,struct node_list *);
struct dfa_state *trap_state();
int free_d_space(struct nfa_state*);
int print_dfa_table(struct dfa_state*);
struct dfa_state* final_nonf_partn(struct dfa_state*);
struct dfa_state* minimization(struct dfa_state*);
struct dfa_state* partition_da_eq_class(struct dfa_state* );
int are_de_in_same_class(struct dfa_trans_node *,struct dfa_trans_node *);
struct dfa_state* put_in_partition(struct dfa_state*,struct dfa_state*);
struct min_dfa* print_dfa_table2(struct dfa_state*);
int finally_got(struct min_dfa*);
struct min_dfa* create_min_dfa();
struct trans_nod* create_min_trans_nod();
int search_string(struct min_dfa*);
int editing_text_file(struct min_dfa*);
int graphical_representation(struct min_dfa*,int);
int draw_arrows(struct min_dfa*,int);
int show_options();
int option_one();
int message_one();
int examine_ip_alphab();
int examine_RE();
int choice_validat();
int re_n_alph_edit();
int LOGIN_ids();

main(){
  char file_name[30],dup_file_name[35]="dup_";
  int lenght=0;
  FILE *fptr1,*fptr2;
  int i=0,choi;
  int columns,get;
  struct nfa_state *base_add;
  struct dfa_state * dfa_bs_add;
  struct min_dfa *bs_add;
  choi=show_options();
  while(!choi){
    printf("\n################################################################");
    printf("\n\n###  WARNING : You have entered wrong option, please retry.###");
    printf("\n################################################################\n");
    choi=show_options();
  }
  switch(choice[0]-48){
    case 1 :
      message_one();
      base_add=construct_nfa_with_e();
      print_e_nfa(base_add);
      bfs_trav_fun(base_add);
      dfa_bs_add=nfa_to_dfa(base_add);
      print_dfa_table(dfa_bs_add);
      final_nonf_partn(dfa_bs_add);
      dfa_bs_add=minimization(dfa_bs_add);
      bs_add=print_dfa_table2(dfa_bs_add);
      columns=finally_got(bs_add);
      search_string(bs_add);
      get=graphical_representation(bs_add,columns);
      if(get==10){
	printf("\n#################################################################");
	printf("\nSORRY,POPING WINDOW's width is not sufficient,cann't draw the DFA");
	printf("\n#################################################################");
        return 0;
      }
      break;
    case 2 :
      LOGIN_ids();
      base_add=construct_nfa_with_e();
      print_e_nfa(base_add);
      bfs_trav_fun(base_add);
      dfa_bs_add=nfa_to_dfa(base_add);
      print_dfa_table(dfa_bs_add);
      final_nonf_partn(dfa_bs_add);
      dfa_bs_add=minimization(dfa_bs_add);
      bs_add=print_dfa_table2(dfa_bs_add);
      columns=finally_got(bs_add);
      search_string(bs_add);
      break;
    case 3 :
      printf("\n\t=>  directory example: ./, Desktop/ ,Downloads/folder/  ");
      printf("\n\n<@@@@>  enter the directory which the file resides in : ");
      scanf("%s",path1);
      printf("\n\n<@@@@>  enter the file name : ");
      scanf("%s",file_name);
      strcpy(path2,path1);
      strcat(path1,file_name);
      strcat(dup_file_name,file_name);
      strcat(path2,dup_file_name);
      re_n_alph_edit();
      base_add=construct_nfa_with_e();
      print_e_nfa(base_add);
      bfs_trav_fun(base_add);
      dfa_bs_add=nfa_to_dfa(base_add);
      print_dfa_table(dfa_bs_add);
      final_nonf_partn(dfa_bs_add);
      dfa_bs_add=minimization(dfa_bs_add);
      bs_add=print_dfa_table2(dfa_bs_add);
      columns=finally_got(bs_add);
      editing_text_file(bs_add);
      break;
    case 4:
      printf("\n################################################################");
      printf("\n\t\t###  NOT AWAILBLE FOR NOW ###");
      printf("\n################################################################\n\n");
      return 0;
      break;
  }
}						// terminated main();

int choice_validat(){
  if(choice[0]!=48&&choice[0]!=49){
    printf("\n################################################################");
    printf("\n###  WARNING : WRONG INPUT, please retry. ###");
    printf("\n################################################################\n");
    printf("\n\n<@@@@>  ENTER YOUR CHOICE HERE (0/1): ");
    scanf("%s",choice);
    choice_validat();
  }
}

int show_options(){
  printf("\n\n\t=> OPTIONS AWAILBLE : ");
  printf("\n\t\t*  Regular Expression to Minimized DFA Conversion  (ENTER 1)  ");
  printf("\n\t\t*  LOGIN-ID Verification                           (ENTER 2)  ");
  printf("\n\t\t*  Pattern Searching in a Text File                (ENTER 3)  ");
  printf("\n\t\t*  Parsing a Program File                          (ENTER 4)  ");
  printf("\n\n<@@@@>  ENTER YOUR CHOICE HERE : ");
  scanf("%s",choice);
  if(choice[0]>52||choice[0]<49)
    return 0;
  else
    return choice[0]-48;
} 						// terminated show_options()

int message_one(){
  int i=0;
  printf("\n\t=>  INSTRUCTIONS  :");
  printf("\n\t\t*  DON'T USE SPACE or any SPECIAL CHARACTER.");
  printf("\n\t\t*  REPETITION of characters are not allowed.");
  printf("\n\n<@@@@>  ENTER INPUT ALPHABET Σ : ");
  scanf("%s",alphabet);
  examine_ip_alphab();
  printf("\n\t=>Entered INPUT ALPHABET is : Σ={ ");
  while(alphabet[i]!='\0'){
    printf("%c",alphabet[i]);
    i++;
    if(alphabet[i]!='\0')
    printf(",");
  }
  printf(" }");
  no_of_ip_alph=i;
  printf("\n\t=>  for ε enter ~ \tfor ∅  enter ^ ");
  printf("\n\n<@@@@>  Enter a VALID regular expression : ");
  scanf("%s",RE);
  examine_RE();
} 						//terminated message_one();

int examine_ip_alphab(){

}						//terminated examine_ip_alphab();

int examine_RE(){

}						//terminated examine_RE();

int re_n_alph_edit(){
  char Pattern[60],ch;
  int length,len2;
  printf("\n\t=>  INSTRUCTIONS  :");
  printf("\n\t\t*  DON'T USE SPACE,SPECIAL SYMBOLS.");
  printf("\n\t\t*  U can put '+' b/w two words for searching multiple word");
  printf("\n\t=>   NOT CASE-SENSITIVE SEARCH                            (PRESS 0)");
  printf("\n\t=>   CASE-SENSITIVE SEARCH                                (PRESS 1)");
  printf("\n\n<@@@@>  Enter UR CHOICE here (0/1): ");
  scanf("%s",choice);
  choice_validat();
  printf("\n\n<@@@@>  Enter Pattern to search in the file : ");
  scanf("%s",Pattern);
  if(choice[0]==49){
    char def[150]="(@+q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0+Q+W+E+R+T+Y+U+I+O+P+A+S+D+F+G+H+J+K+L+Z+X+C+V+B+N+M)*";
    ch='0';
    for(length=0;length<10;length++)
      alphabet[length]=ch++;
    ch='A';
    for(;length<36;length++)
      alphabet[length]=ch++;
    ch='a';
    for(;length<62;length++)
      alphabet[length]=ch++;
    alphabet[length]='@';
    alphabet[++length]='\0';
    no_of_ip_alph=length;
    strcpy(RE,def);
    strcat(RE,Pattern);
  }
  else{
    char def[150]="(@+q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)*";
    ch='0';
    for(length=0;length<10;length++)
      alphabet[length]=ch++;
    ch='a';
    for(;length<36;length++)
      alphabet[length]=ch++;
    alphabet[length]='@';
    alphabet[++length]='\0';
    no_of_ip_alph=length;
    strcpy(RE,def);
    for(length=0;Pattern[length]!='\0';length++){
      if(Pattern[length]>=65&&Pattern[length]<=90)
        Pattern[length]=Pattern[length]+32;
    }
    strcat(RE,Pattern);
  }
}					//terminated re_n_alph_edit();

int LOGIN_ids(){
  strcpy(take_str,"LOGIN-ID");
  printf("\n\t=>   IF U can enter RE of LOGIN-IDs                       (PRESS 0)");
  printf("\n\t=>   Continue with DEFAULT ????                           (PRESS 1)");
  printf("\n\n<@@@@>  Enter UR CHOICE here (0/1): ");
  scanf("%s",choice);
  choice_validat();
  if(choice[0]==49){
    char ch='0';
    int length;
    char temp[1525]="(q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)(q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)*(.(q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)(q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)*)*@(q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)(q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)*.(q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)(q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)*(.(q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)(q+w+e+r+t+y+u+i+o+p+a+s+d+f+g+h+j+k+l+z+x+c+v+b+n+m+1+2+3+4+5+6+7+8+9+0)*)*";
    for(length=0;length<10;length++)
      alphabet[length]=ch++;
    ch='a';
    for(;length<36;length++)
      alphabet[length]=ch++;
    alphabet[length]='@';
    alphabet[++length]='.';
    alphabet[++length]='\0';
    no_of_ip_alph=length;
    strcpy(RE,temp);
  }
  else{
    printf("\n\n<@@@@>  Enter ALPHABETs for your LOGIN-ID : ");
    scanf("%s",alphabet);
    no_of_ip_alph=strlen(alphabet);
    printf("\n\n<@@@@>  Enter RE for your LOGIN-ID : ");
    scanf("%s",RE);
  }
}

struct nfa_state* construct_nfa_with_e(){
  int i=0,j;
  char re[1825],stack_op[900];
  struct nfa_state *stack_alph[900];
  // now I am going to put ':' for concatination operation .
  for(j=0;RE[j]!='\0';j++){
    if((j!=0&&RE[j]!=')'&&RE[j]!='+'&&RE[j]!='*')&&(RE[j-1]!='('&&RE[j-1]!='+')){
      re[i]=':';
      i++;
    }
    re[i]=RE[j];
    i++;
  }
  re[i]='$';  					 // symbol for termination.
  stack_op[k]='$';
  while((re[l]=='$'&&stack_op[k]=='$')!=1){     // condition terminating the loop.
    //for pushing in operator stack
    if(re[l]=='('||re[l]==')'||re[l]=='+'||re[l]=='*'||re[l]==':'||re[l]=='$'){
      if(re[l]=='(')                		// checking for '('
      L_paranthesis(re,stack_op,stack_alph);
      else if(re[l]==')') 	      		//checking for ')'
      R_paranthesis(re,stack_op,stack_alph);
      else if(re[l]=='+')                 	//checking for '+'
      union_optr(re,stack_op,stack_alph);
      else if(re[l]==':')              		//checking for ':'
      concat_optr(re,stack_op,stack_alph);
      else if(re[l]=='*')          	   	//checking for '*'
      closure_optr(re,stack_op,stack_alph);
      else if(re[l]=='$')                       //RE has been travesed.
      dol_optr(re,stack_op,stack_alph);
    }        					// terminated operation over OPERATOR STACK.
    //push in operand stack.
    else{
       m++;
       stack_alph[m]=a(re[l]);
       l++;
    }                                   	//terminated operation over OPERAND STACK.
  }						//terminated while loop;
  return stack_alph[m];
}						//terminated construct_nfa_with_e();

int L_paranthesis(char* re,char* stack_op,struct nfa_state** stack_alph){
  k++;
  stack_op[k]=re[l];
  l++;
}						//terminated L_paranthesis();

int R_paranthesis(char* re,char* stack_op,struct nfa_state** stack_alph){
  while(stack_op[k]!='('){
    if(stack_op[k]=='+'){
      stack_alph[m-1]=r1_or_r2(stack_alph[m-1],stack_alph[m]);
      m--;
    }
    else if(stack_op[k]==':'){
      stack_alph[m-1]=r1_concat_r2(stack_alph[m-1],stack_alph[m]);
      m--;
    }
    else if(stack_op[k]=='*')
      stack_alph[m]=r_closure(stack_alph[m]);
    k--;
  }    					//while loop terminated.
  l++;
  k--;
}						//terminated R_paranthesis();

int union_optr(char* re,char* stack_op,struct nfa_state** stack_alph){
  if(stack_op[k]=='$'||stack_op[k]=='('){
    k++;
    stack_op[k]=re[l];
    l++;
  }
  else if(stack_op[k]=='+'){
    stack_alph[m-1]=r1_or_r2(stack_alph[m-1],stack_alph[m]);
    m--;
    k--;
  }
  else if(stack_op[k]==':'){
    stack_alph[m-1]=r1_concat_r2(stack_alph[m-1],stack_alph[m]);
    m--;
    k--;
  }
  else if(stack_op[k]=='*'){
    stack_alph[m]=r_closure(stack_alph[m]);
    k--;
  }
}						//terminated union_optr();

int concat_optr(char* re,char* stack_op,struct nfa_state** stack_alph){
  if(stack_op[k]=='$'|| stack_op[k]=='('||stack_op[k]=='+'){
    k++;
    stack_op[k]=re[l];
    l++;
  }
  else if(stack_op[k]==':'){
    stack_alph[m-1]=r1_concat_r2(stack_alph[m-1],stack_alph[m]);
    m--;
    k--;
  }
  else if(stack_op[k]=='*'){
    stack_alph[m]=r_closure(stack_alph[m]);
    k--;
  }
}						//terminated concat_optr();

int closure_optr(char* re,char* stack_op,struct nfa_state** stack_alph){
  if(stack_op[k]=='*'){
    stack_alph[m]=r_closure(stack_alph[m]);
    k--;
  }
  else{
    k++;
    stack_op[k]=re[l];
    l++;
  }
}						//terminated closure_optr();
int dol_optr(char* re,char* stack_op,struct nfa_state** stack_alph){
  while(stack_op[k]!='$'){
    if(stack_op[k]=='+'){
      stack_alph[m-1]=r1_or_r2(stack_alph[m-1],stack_alph[m]);
      m--;
    }
    else if(stack_op[k]==':'){
      stack_alph[m-1]=r1_concat_r2(stack_alph[m-1],stack_alph[m]);
      m--;
    }
    else
      stack_alph[m]=r_closure(stack_alph[m]);
  k--;
  }					//while loop is terminated
}						//terminated dol_optr();

 struct nfa_state* create_state(){
   struct nfa_state* ptr;
   nfa_st_no++;
   ptr=(struct nfa_state *)malloc(sizeof(struct nfa_state));
   ptr->state_name =nfa_st_no;
   ptr->next_ip='\0';
   ptr->next_trans1='\0';
   ptr->next_trans2='\0';
   ptr->is_initial=0;
   ptr->is_final=0;
   ptr->final_of_re='\0';
   ptr->visited_bfs=0;
   ptr->visited_bfs2=0;
   ptr->visited_dfs=0;
   return ptr;
}						//terminated create_state();

struct nfa_state* a(char ip_symbol){
  struct nfa_state *new_I,*new_F;       	// declaration for other than '~' and '^'
  if(ip_symbol=='~')
    return epsilon();
  else if(ip_symbol=='^')
    return phi();
  else{
    new_I=create_state();			//creating two new states.
    new_F=create_state();
    // finalizing transitions.
    new_I->next_trans1=new_F;
    new_I->next_ip=ip_symbol;
    new_I->is_initial=1;
    new_I->is_final=0;
    new_I->final_of_re=new_F;
    new_F->next_trans1='\0';
    new_F->next_ip='\0';
    new_F->is_initial=0;
    new_F->is_final=1;
    new_F->final_of_re='\0';
    return new_I;
  }
}						//termination of a();

struct nfa_state* epsilon(){
  struct nfa_state *new_I;
  new_I=create_state();
  //finalizing transitions.
  new_I->next_trans1='\0';
  new_I->next_ip='\0';
  new_I->is_initial=1;
  new_I->is_final=1;
  new_I->final_of_re=new_I;
  return new_I;
}						// terminated epsilon();

struct nfa_state* phi(){
  struct nfa_state* new_I;
  new_I=create_state();
  // finalizing transitions.
  new_I->next_trans1='\0';
  new_I->next_ip='\0';
  new_I->is_initial=1;
  new_I->is_final=0;
  new_I->final_of_re=new_I;
  return new_I;
}						//terminated phi();

struct nfa_state* r1_concat_r2(struct nfa_state* r1,struct nfa_state* r2){
  struct nfa_state *r1_final,*r2_final;
  //storing final state of r1 and r2 in variables.
  r1_final=r1->final_of_re;
  r2_final=r2->final_of_re;
  // reforming the transitions.
  r1_final->next_trans2=r2;
  r1_final->next_ip='~';
  r1_final->is_final=0;
  r1->final_of_re=r2_final;
  r2->is_initial=0;
  return r1;
} 				//terminated r1_concat_r2();

struct nfa_state* r1_or_r2(struct nfa_state* r1,struct nfa_state* r2){
  struct nfa_state *r1_final,*r2_final,*new_I,*new_F;
  //storing final state of r1 and r2 in variables.
  r1_final=r1->final_of_re;
  r2_final=r2->final_of_re;
  //creating new initial and new final states.
  new_I=create_state();
  new_F=create_state();
  // reforming the transitions.
  new_I->next_trans1=r1;
  new_I->next_trans2=r2;
  new_I->next_ip='~';
  new_I->is_initial=1;
  new_I->final_of_re=new_F;
  r1_final->next_trans2=new_F;
  r1_final->next_ip='~';
  r1_final->is_final=0;
  r2_final->next_trans2=new_F;
  r2_final->next_ip='~';
  r2_final->is_final=0;
  new_F->is_final=1;
  r1->is_initial=0;
  r2->is_initial=0;
  return new_I;
  }						//terminated r1_or_r2();

struct nfa_state* r_closure(struct nfa_state* r){
  struct nfa_state *r_final,*new_I,*new_F;
  //storing final state of r in variable.
  r_final=r->final_of_re;
  //creating new initial and new final states.
  new_I=create_state();
  new_F=create_state();
  // reforming the transitions.
  new_I->next_trans1=r;
  new_I->next_trans2=new_F;
  new_I->next_ip='~';
  new_I->is_initial=1;
  new_I->final_of_re=new_F;
  r_final->next_trans2=new_F;
  r_final->next_ip='~';
  r_final->is_final=0;
  new_F->next_trans1=new_I;
  new_F->is_final=1;
  new_F->next_ip='~';
  r->is_initial=0;
  return new_I;
  }  						// terminated r_closure();
int print_e_nfa(struct nfa_state* bs_add){
  int front=0,rear=0;
  struct nfa_state* que[nfa_st_no+1];
  que[rear]=bs_add;
  que[rear]->visited_bfs=1;
  //printf("\n\n\t\t");
  //printf("TRANSITION TABLE of NFA with EPSILON\n\t\t");
  //printf("------------------------------------");
  //printf("\n\n\t\t\t");
  while(front<=rear){
    if(que[front]->is_initial==1)
    //  printf("%c%c",'-','>');
    if(que[front]->is_final==1)
      //printf("%c",'#');
      //printf("%d\t",que[front]->state_name);
    if(que[front]->next_trans1!='\0'){
      //printf("%d(",(que[front]->next_trans1)->state_name);
      //printf("%c)\t",que[front]->next_ip);
    }
    if(que[front]->next_trans2!='\0'){
      //printf("%d",(que[front]->next_trans2)->state_name);
      //printf("(e)");
    }
    if(que[front]->next_trans1!='\0'&&(que[front]->next_trans1)->visited_bfs!=1){
      rear++;
      que[rear]=que[front]->next_trans1;
      que[rear]->visited_bfs=1;
    }
    if(que[front]->next_trans2!='\0'&&(que[front]->next_trans2)->visited_bfs!=1){
      rear++;
      que[rear]=que[front]->next_trans2;
      que[rear]->visited_bfs=1;
    }
    fun_4_closr(que[front]);
    front++;
  }						// while loop terminated.
  //printf("\n");
}						// terminated print_e_nfa();
 struct node_list* create_node_list(){
   struct node_list* ptr;
   ptr=(struct node_list *)malloc(sizeof(struct node_list));
   ptr->link='\0';
   ptr->node='\0';
   return ptr;
}
int fun_4_closr(struct nfa_state *current){
  struct nfa_state *stack[nfa_st_no+1],*head=current;
  int top=0,count=0;
  struct node_list *get,*temp;
  stack[top]=current;
  stack[top]->visited_dfs=1;
  get=create_node_list();
  get->node=stack[top];
  current->e_closr_ptr=get;
  while(top>-1){
    if(count!=0){
      temp=create_node_list();
      temp->node=current;
      sort_and_insert_closr_list(head->e_closr_ptr,temp);
    }
    count=1;
    if(current->next_ip=='~'){
      top--;
      if(current->next_trans1!='\0'&&current->next_trans1->visited_dfs!=1){
	top++;
	stack[top]=current->next_trans1;
	stack[top]->visited_dfs=1;
      }
       if(current->next_trans2!='\0'&&current->next_trans2->visited_dfs!=1){
	top++;
	stack[top]=current->next_trans2;
	stack[top]->visited_dfs=1;
      }
    }
    else
      top--;
    current=stack[top];
  }						//terminated while loop.
  temp=head->e_closr_ptr;
  //printf("\n");
 while(temp->link!='\0'){
  // printf("%d ",temp->node->state_name);
   temp->node->visited_dfs=0;
   temp=temp->link;
  }
//  printf("%d ",temp->node->state_name);
  temp->node->visited_dfs=0;
  //printf("\n\t\t\t");
}						//terminated fun_4_closr();

int sort_and_insert_closr_list(struct node_list *head_closr,struct node_list *insrt_node){
  struct node_list *temp;
  struct nfa_state *temp2;
  if(head_closr->node->state_name > insrt_node->node->state_name){
    temp=head_closr->link;
    temp2=head_closr->node;
    head_closr->node=insrt_node->node;
    head_closr->link=insrt_node;
    insrt_node->node=temp2;
    insrt_node->link=temp;
  }
  else{
    while(head_closr->node->state_name<insrt_node->node->state_name && head_closr->link!='\0'){
      temp=head_closr;
      head_closr=head_closr->link;
    } 						 //while loop closed.
    if(head_closr->node->state_name<insrt_node->node->state_name&&head_closr->link=='\0'){
      head_closr->link=insrt_node;
    }
    else{
      insrt_node->link=temp->link;
      temp->link=insrt_node;
    }
  }
}						//terminated sort_&_insert_closr_list();
int bfs_trav_fun(struct nfa_state* bs_add){
  int front=0,rear=0;
  struct nfa_state* que[nfa_st_no+1];
  struct node_list *temp;
  que[rear]=bs_add;
  que[rear]->visited_bfs2=1;
  while(front<=rear){
    //printf("\nloop bfs");
    if(que[front]->next_trans1!='\0'&&(que[front]->next_trans1)->visited_bfs2!=1){
      rear++;
      que[rear]=que[front]->next_trans1;
      que[rear]->visited_bfs2=1;
    }
    if(que[front]->next_trans2!='\0'&&(que[front]->next_trans2)->visited_bfs2!=1){
      rear++;
      que[rear]=que[front]->next_trans2;
      que[rear]->visited_bfs2=1;
    }
    nfa_without_e(que[front]);
    front++;
  }						// while loop terminated.
}						//terminated bfs_trav_fun();

struct nfa_trans *create_nfa_trans_node(){
  struct nfa_trans *ptr;
  ptr=(struct nfa_trans *)malloc(sizeof(struct nfa_trans ));
  ptr->ip_symbol='\0';
  ptr->states='\0';
  ptr->link='\0';
  return ptr;
}						//terminated nfa_trans_node();

int nfa_without_e(struct nfa_state *current){
  int i=0,count=1;
  struct node_list *temp;
  struct nfa_trans *array_head,*array_temp;
  while(i<no_of_ip_alph){
    temp=current->e_closr_ptr;
    if(count==1){
      array_temp=create_nfa_trans_node();
      array_head=array_temp;
    }
    else{
      array_temp->link=create_nfa_trans_node();
      array_temp=array_temp->link;
    }
    array_temp->ip_symbol=alphabet[i];
    array_temp->states=create_node_list();
    do{
      if(temp->node->is_final==1&&count==1)
	current->is_final=1;
      if(alphabet[i]==temp->node->next_ip)
	sort_and_insrt_trans_arr(array_temp->states,(temp->node->next_trans1)->e_closr_ptr);
      temp=temp->link;
      }while(temp!='\0');
      count=0;
      if(array_temp->states->node=='\0')
	array_temp->states='\0';
    i++;
  }						//terminated outer while loop.
  current->trans_arr=array_head;
  int h=0;
  struct node_list *dup;
 // printf("\n\n%d  :::",current->state_name);
  struct nfa_trans *travs=current->trans_arr;
  while(h<no_of_ip_alph){
  //printf("\n%c :",travs->ip_symbol);
  dup=travs->states;
  while(dup!='\0'){
    //printf(" %d ",dup->node->state_name);
    dup=dup->link;
  }
  travs=travs->link;
  h++;
  }
}						//terminated nfa_without_e();

int sort_and_insrt_trans_arr(struct node_list *head_st,struct node_list *head_closr){
  struct node_list *ptr_st=head_st,*ptr_clos=head_closr,*temp;
  temp=ptr_st;
  if(ptr_st->node=='\0'){
    while(ptr_clos!='\0'){
      temp=ptr_st;
      ptr_st->node=ptr_clos->node;
      ptr_st->link=create_node_list();
      ptr_st=ptr_st->link;
      ptr_clos=ptr_clos->link;
    }						//terminated first while loop.
    temp->link='\0';
  }
  else{
    while(ptr_clos!='\0'){
      if(temp->link=='\0'){
	ptr_st=temp;
        ptr_st->link=create_node_list();
	ptr_st=ptr_st->link;
	ptr_st->node=ptr_clos->node;
	ptr_clos=ptr_clos->link;
      }
      else{
        if(ptr_st->node->state_name==ptr_clos->node->state_name){
	  ptr_clos=ptr_clos->link;
	  temp=ptr_st;
	  ptr_st=ptr_st->link;
	}
	else if(ptr_st->node->state_name<ptr_clos->node->state_name){
	  temp=ptr_st;
	  ptr_st=ptr_st->link;
	}
	else{
	  temp=ptr_st;
	  ptr_st=create_node_list();
	  ptr_st->node=temp->node;
	  ptr_st->link=temp->link;
	  temp->node=ptr_clos->node;
	  temp->link=ptr_st;
	  ptr_clos=ptr_clos->link;
	  temp=ptr_st;
	}
      }
    }						//terminated second while loop.
  }
}						//terminated sort_and_insrt_trans_arr();

struct container_node* create_container_node(){
   struct container_node* ptr;
   ptr=(struct container_node *)malloc(sizeof(struct container_node ));
   ptr->bulky_dfa_st='\0';
   ptr->fair_dfa_st='\0';
   ptr->link='\0';
   return ptr;
}						//terminated create_container_node();

struct dfa_trans_node *create_dfa_trans_node(){
  struct dfa_trans_node *ptr;
  ptr=(struct dfa_trans_node *)malloc(sizeof(struct dfa_trans_node));
  ptr->ip_symbol='\0';
  ptr->next_state='\0';
  ptr->link='\0';
  return ptr;
}						//terminated create_dfa_trans_node();

struct dfa_state * create_dfa_st(){
  struct dfa_state *ptr;
  ptr=(struct dfa_state *)malloc(sizeof(struct dfa_state));
  dfa_st_no++;
  ptr->state_name=dfa_st_no;
  ptr->is_initial=0;
  ptr->is_final=0;
  ptr->next_trans_ptr='\0';
  ptr->link='\0';
  ptr->eq_class=0;
  ptr->grp_head=0;
}						//terminated create_dfa_st();

struct dfa_state *nfa_to_dfa(struct nfa_state *nfa_bs_add){
  struct container_node *head_cont,*last,*current,*returned;
  struct node_list *head_union_st,*temp;
  struct dfa_state *dfa_base,*dfa_temp,*dfa_trap;
  struct dfa_trans_node *array_head,*array_temp;
  struct nfa_trans *for_ip_match;
  int i,count,h=0,count2=1;
  head_cont=create_container_node();
  head_cont->bulky_dfa_st=create_node_list();
  head_cont->bulky_dfa_st->node=nfa_bs_add;
  dfa_base=create_dfa_st();
  head_cont->fair_dfa_st=dfa_base;
  head_cont->fair_dfa_st->is_initial=1;
  current=head_cont;
  last=head_cont;
  while(current!='\0'){
    i=0,count=1;
    dfa_temp=current->fair_dfa_st;
    array_head=create_dfa_trans_node();
    dfa_temp->next_trans_ptr=array_head;
    array_temp=array_head;
    while(i<no_of_ip_alph){
      temp=current->bulky_dfa_st;
      if(count!=1){
	array_temp->link=create_dfa_trans_node();
	array_temp=array_temp->link;
      }
      head_union_st=create_node_list();
      array_temp->ip_symbol=alphabet[i];
      while(temp!='\0'){
	if(count==1&&temp->node->is_final==1)
	  current->fair_dfa_st->is_final=1;
	for_ip_match=temp->node->trans_arr;
	for(h=0;h<i;h++)
	  for_ip_match=for_ip_match->link;
	if(for_ip_match->states!='\0')
          sort_and_insrt_trans_arr(head_union_st,for_ip_match->states);
        temp=temp->link;
      }						//terminated while loop 3
      count=0;
      if(head_union_st->node=='\0'){
        if(count2==1){
	count2=0;
	dfa_trap=trap_state();
        }
	array_temp->next_state=dfa_trap;
      }
      else{
	returned=matching_in_cont(head_cont,head_union_st);
	if(returned=='\0'){
	  last->link=create_container_node();
	  last=last->link;
	  last->bulky_dfa_st=head_union_st;
	  last->fair_dfa_st=create_dfa_st();
	  array_temp->next_state=last->fair_dfa_st;
	}
	else
	  array_temp->next_state=returned->fair_dfa_st;
      }
      i++;
    }						//terminated while loop 2
    current=current->link;
  }						//terminated while loop 1 ;
  free_d_space(nfa_bs_add);
  return dfa_base;
}						//terminated nfa_to_dfa();

int free_d_space(struct nfa_state* bs_add){
  int front=0,rear=0;
  struct nfa_state* que[nfa_st_no+1];
  struct node_list *temp;
  que[rear]=bs_add;
  que[rear]->visited_bfs2=0;
  while(front<=rear){
    //printf("\nloop bfs");
    if(que[front]->next_trans1!='\0'&&(que[front]->next_trans1)->visited_bfs2!=0){
      rear++;
      que[rear]=que[front]->next_trans1;
      que[rear]->visited_bfs2=0;
    }
    if(que[front]->next_trans2!='\0'&&(que[front]->next_trans2)->visited_bfs2!=0){
      rear++;
      que[rear]=que[front]->next_trans2;
      que[rear]->visited_bfs2=0;
    }
    //printf("\t%d",que[front]->state_name);
    free(que[front]);
    front++;
  }						// while loop terminated.
}						//terminated free_d_space();

struct dfa_state *trap_state(){
  int i=0;
  struct dfa_trans_node *array_head=create_dfa_trans_node(),*array_temp,*temp;
  struct dfa_state *ptr;
  ptr=(struct dfa_state *)malloc(sizeof(struct dfa_state));
  dfa_st_no++;
  ptr->state_name=dfa_st_no;
  ptr->is_initial=0;
  ptr->is_final=0;
  array_temp=array_head;
  while(i<no_of_ip_alph){
    temp=array_temp;
    array_temp->ip_symbol=alphabet[i];
    array_temp->next_state=ptr;
    array_temp->link=create_dfa_trans_node();
    array_temp=array_temp->link;
    i++;
  }
  array_temp='\0';
  temp->link='\0';
  ptr->next_trans_ptr=array_head;
  return ptr;
}						//terminated trap_state();

struct container_node *matching_in_cont(struct container_node *bs_cont,struct node_list *bs_union){
  struct node_list *temp_union,*hd_bulky;
  while(bs_cont!='\0'){
    hd_bulky=bs_cont->bulky_dfa_st;
    temp_union=bs_union;
    while((hd_bulky!='\0'&&temp_union!='\0')&&temp_union->node->state_name==hd_bulky->node->state_name){
      temp_union=temp_union->link;
      hd_bulky=hd_bulky->link;
    }						//terminated while loop2;
    if(temp_union=='\0'&&hd_bulky=='\0')
      break;
    else
    bs_cont=bs_cont->link;
  }						//terminated while loop1.
  return bs_cont;
}						//terminated matching_in_cont();

int print_dfa_table(struct dfa_state *bs_add){
  int front=0,rear=0,i=0,h=0;
  struct dfa_state *que[dfa_st_no+1];
  struct dfa_trans_node *temp;
  que[rear]=bs_add;
  que[rear]->visited_bfs=1;
  printf("\n\n\n\t");
  printf("TRANSITION TABLE of DFA(not minimized) \n\t");
  printf("--------------------------------------\n");
  printf("\n\tstates\t|\t");
  while(h<no_of_ip_alph){
    printf("%c\t",alphabet[h]);
    h++;
  }
   printf("\n\t");
  for(h=0;h<no_of_ip_alph+1;h++)
    printf("--------");
  while(front<=rear){
    printf("\n\t");
    if(que[front]->is_initial==1)
      printf("%c%c",'-','>');
    if(que[front]->is_final==1)
      printf("%c",'#');
    printf("%d\t|\t",que[front]->state_name);
    temp=que[front]->next_trans_ptr;
    for(i=0;i<no_of_ip_alph;i++){
      printf("%d\t",temp->next_state->state_name);
      if(temp->next_state->visited_bfs!=1){
	rear++;
	que[rear]=temp->next_state;
	que[rear]->visited_bfs=1;
      }
      temp=temp->link;
    }
    que[front]->link=que[front+1];
    front++;
    if(front>rear)
      que[front-1]->link='\0';
  }						// while loop terminated.
  printf("\n\n");
  //final_nonf_partn(bs_add);
}						//terminated print_dfa_table();

struct min_dfa* create_min_dfa(){
  struct min_dfa *ptr;
  int i;
  ptr=(struct min_dfa*)malloc(sizeof(struct min_dfa));
  ptr->keep=0;
  ptr->cen_x=0;
  ptr->cen_y=0;
  ptr->state_name=0;
  ptr->is_initial=0;
  ptr->is_final=0;
  ptr->next_trans_ptr='\0';
  ptr->visited_bfs=0;
  return ptr;
}

struct trans_nod* create_min_trans_nod(){
  struct trans_nod *ptr;
  ptr=(struct trans_nod*)malloc(sizeof(struct trans_nod));
  ptr->ip_symbol='\0';
  ptr->next_state='\0';
  ptr->link='\0';
  return ptr;
}						//terminated create_min_trans_nod();

struct min_dfa* print_dfa_table2(struct dfa_state *bs_add){
  int front=0,rear=0,i=0,put=0;
  //printf("\nno_of_eq_clss=%d\n",no_of_eq_clss);
  struct dfa_state *que[no_of_eq_clss+1];
  struct min_dfa *base_add,*ptr,*ptr2,*keep_all[no_of_eq_clss+1];
  struct trans_nod *temp_min;
  for(i=0;i<=no_of_eq_clss;i++){
    keep_all[i]='\0';
  }
  struct dfa_trans_node *temp;
  que[rear]=bs_add;
  que[rear]->visited_bfs=0;
  while(front<=rear){
    temp=que[front]->next_trans_ptr;
    for(i=0;i<no_of_ip_alph;i++){
      if(temp->next_state->eq_class!=0&&temp->next_state->visited_bfs!=0){
	rear++;
	que[rear]=temp->next_state;
	que[rear]->visited_bfs=0;
      }
      temp=temp->link;
    }
    //printf("\ngrphead= %d\t",que[front]->grp_head);
  if(keep_all[(que[front]->grp_head)-1]=='\0'){
    ptr=create_min_dfa();
    ptr->state_name=++put;
    keep_all[(que[front]->grp_head)-1]=ptr;
    if(que[front]->is_initial==1){
      ptr->is_initial=1;
      base_add=ptr;
    }
    if(que[front]->is_final==1)
      ptr->is_final=1;
  }
  else{
    ptr=keep_all[(que[front]->grp_head)-1];
  }
  temp=que[front]->next_trans_ptr;
  for(i=0;i<no_of_ip_alph;i++){
    if(keep_all[(temp->next_state->grp_head)-1]=='\0'){
      ptr2=create_min_dfa();
      ptr2->state_name=++put;
      if(temp->next_state->is_final==1)
        ptr2->is_final=1;
      keep_all[(temp->next_state->grp_head)-1]=ptr2;
    }
    if(i==0){
      temp_min=create_min_trans_nod();
      ptr->next_trans_ptr=temp_min;
    }
    else{
      temp_min->link=create_min_trans_nod();
      temp_min=temp_min->link;
    }
    temp_min->ip_symbol=temp->ip_symbol;
    temp_min->next_state=keep_all[(temp->next_state->grp_head)-1];
    temp=temp->link;
  }						// terminated for loop;
    front++;
  }						// while loop terminated.
return base_add;
}						//terminated print_dfa_table();

int finally_got(struct min_dfa *bs_add){
  int front=0,rear=0,rear2=1,columns=0,i=0,h=0,put=1;
  char ch='A';
  struct min_dfa *que[no_of_eq_clss+1];
  struct trans_nod *temp;
  que[rear]=bs_add;
  que[rear]->state_name=put;
  que[rear]->visited_bfs=1;
  printf("\n\n\n\t");
  printf("TRANSITION TABLE of DFA(MINIMIZED) \n\t");
  printf("--------------------------------------\n");
  printf("\n\tstates\t|\t");
  while(h<no_of_ip_alph){
    printf("%c\t",alphabet[h]);
    h++;
  }
   printf("\n\t");
  for(h=0;h<no_of_ip_alph+1;h++)
    printf("--------");
  while(front<=rear){
    //printf("\t\t take a look :%p \t\t",que[front]);
    printf("\n\t");
    if(que[front]->is_initial==1)
      printf("%c%c",'-','>');
    if(que[front]->is_final==1)
      printf("%c",'#');
    printf("%c\t|\t",que[front]->state_name+64);
    temp=que[front]->next_trans_ptr;
   // printf("\t\t look :%p \t\t",temp);
    for(i=0;i<no_of_ip_alph;i++){
      if(temp->next_state->visited_bfs!=1){
	rear++;
	put++;
	temp->next_state->state_name=put;
	que[rear]=temp->next_state;
	que[rear]->visited_bfs=1;
      }
      printf("%c\t",temp->next_state->state_name+64);
      temp=temp->link;
    }
    if(front==rear2){
      rear2=rear;
      columns++;
    }
    front++;
  }						// while loop terminated.
  printf("\n\n");
  return columns+1;
}

struct dfa_state *final_nonf_partn(struct dfa_state * bs_add){
  struct dfa_state *init_temp,*partition='\0',*part_temp;
  int count=1,put=1;
  init_temp=bs_add;
  bs_add->eq_class=++no_of_eq_clss;
  bs_add->grp_head=1;
  while(init_temp->link!='\0'){
    //printf("\n%d  ",init_temp->state_name);
    if(init_temp->is_final!=init_temp->link->is_final){
      if(count==1){
	count++;
	partition=init_temp->link;
	partition->eq_class=++no_of_eq_clss;
	partition->grp_head=++put;
        part_temp=partition;
	init_temp->link=part_temp->link;
	part_temp->link='\0';
      }
      else{
	part_temp->link=init_temp->link;
	part_temp=part_temp->link;
	part_temp->grp_head=put;
	init_temp->link=part_temp->link;
	part_temp->link='\0';
      }
    }
    else{
      init_temp=init_temp->link;
      init_temp->grp_head=1;
    }
  }						//terminated while loop.
  init_temp->link=partition;
  count=2;
  for( part_temp=bs_add;part_temp!='\0';part_temp=part_temp->link){
    if(part_temp->is_final==1&&count!=1){
     // printf("\nfinal states : ");
      count=1;
    }
    else if(part_temp->is_final!=1&&count!=3){
      //printf("\nnon_final states : ");
      count=3;
    }
     //printf("%d  ",part_temp->state_name);
  }
  //printf("\n");
  //printf("no of eqclass %d ",no_of_eq_clss);
  return bs_add;
}						//terminated final_nonf_partn();

struct dfa_state* minimization(struct dfa_state* bs_add){
  int i=0,put;
  struct dfa_state *eqcls_head,*temp2=bs_add;
 while(i!=no_of_eq_clss){
   i=no_of_eq_clss;
   eqcls_head=bs_add;
   while(eqcls_head!='\0')
     eqcls_head=partition_da_eq_class(eqcls_head);	//terminated while loop2;
   put=0;
   for(temp2=bs_add;temp2!='\0';temp2=temp2->link){
     if(temp2->eq_class!=0){
       put++;
     }
     temp2->grp_head=put;
  }						//terminated for loop;
}						//terminated while loop1;
return bs_add;
}						//terminated minimization();

struct dfa_state* partition_da_eq_class(struct dfa_state* eqcls_head){
  int check;
  struct dfa_state *eqc_temp=eqcls_head,*part_temp='\0',*partn_head='\0',*temp;
  while(eqc_temp->link!='\0'&&eqc_temp->link->eq_class==0){
    check=are_de_in_same_class(eqcls_head->next_trans_ptr,eqc_temp->link->next_trans_ptr);
    if(check==0){
      if(partn_head=='\0'){
	partn_head=eqc_temp->link;
	eqc_temp->link=eqc_temp->link->link;
	part_temp=partn_head;
	part_temp->eq_class=++no_of_eq_clss;
	part_temp->link='\0';
      }
      else{
	temp=eqc_temp->link;
	eqc_temp->link=temp->link;
	part_temp=put_in_partition(partn_head,temp);
      }
    }
    else{
      eqc_temp=eqc_temp->link;
    }
  }						//terminated while loop;
  if(part_temp=='\0')
    return eqc_temp->link;
  else{
    part_temp->link=eqc_temp->link;
    eqc_temp->link=partn_head;
    return part_temp->link;
  }
}						//terminated partition_da_eq_class();

int are_de_in_same_class(struct dfa_trans_node *first,struct dfa_trans_node *second){
  while(first!='\0'&&first->next_state->grp_head==second->next_state->grp_head){
    first=first->link;
    second=second->link;
  }
  if(first=='\0')
    return 1;
  else
    return 0;
}						//terminated are_de_in_same_class();

struct dfa_state* put_in_partition(struct dfa_state *partn_head,struct dfa_state *temp){
int check;
struct dfa_state *part_temp;
while(partn_head!='\0'){
  check=are_de_in_same_class(partn_head->next_trans_ptr,temp->next_trans_ptr);
  if(check==0){
    for(part_temp=partn_head;part_temp->link!='\0'&&part_temp->link->eq_class==0;part_temp=part_temp->link);
    if(part_temp->link=='\0'){
      part_temp->link=temp;
      part_temp=part_temp->link;
      part_temp->link='\0';
      part_temp->eq_class=++no_of_eq_clss;
      partn_head='\0';
      return part_temp;
    }
    else{
      partn_head=part_temp->link;
    }
  }
  else{
    for(part_temp=partn_head;part_temp->link!='\0'&&part_temp->link->eq_class==0;part_temp=part_temp->link);
    temp->link=part_temp->link;
    part_temp->link=temp;
    part_temp=part_temp->link;
for(;part_temp->link!='\0';part_temp=part_temp->link);
    return part_temp;
  }
}						//terminated while loop:
}						//terminated put_in_partition();

int search_string(struct min_dfa* base_add){
  struct trans_nod *temp;
  struct min_dfa* bs_add;
  char str[100];
  int i,y,z;
  if(take_str[0]=='S')
    printf("\n<@@@@>  Do U want to CHECK some %ss on this RE (PRESS 0/1) :  ",take_str);
  else
    printf("\n<@@@@>  Do U want to VERIFY FORMAT of some %ss now (PRESS 0/1) :  ",take_str);
  scanf("%s",choice);
  choice_validat();
  while(choice[0]==49){
  i=0;
  bs_add=base_add;
  if(take_str[0]=='S')
    printf("\n\t=>  YOUR RE is : %s",RE);
  printf("\n\n<@@@@>  ENTER YOUR %s to CHECK : ",take_str);
  scanf("%s",str);
  for(z=0;str[z]!='\0';z++){
    for(y=0;alphabet[y]!='\0';y++){
      if(str[z]==alphabet[y])
	break;
    }
    if(alphabet[y]=='\0'){
      printf("\n################################################################");
      printf("\n\t SORRY ! INVALID %s , NOT from the ALPHABET",take_str);
      printf("\n\t\t   Quitting.........");
      printf("\n################################################################");
      printf("\nSORRY\n\n");
      delay(5000);
      return 0;
    }
  }
  if(str[i]=='~'&&bs_add->is_final==1){
    printf("\n--------------------------------------------------------");
    printf("\n\t RESULT => Entered %s IS ACCEPTED ",take_str);
    printf("\n--------------------------------------------------------");
  }
  else{
  while(str[i]!='\0'){
    for(temp=bs_add->next_trans_ptr;temp->ip_symbol!=str[i];temp=temp->link);
    bs_add=temp->next_state;
    i++;
  }
  if(bs_add->is_final==1){
    printf("\n--------------------------------------------------------");
    printf("\n\t RESULT => Entered %s IS ACCEPTED ",take_str);
    printf("\n--------------------------------------------------------");
  }
  else{
    printf("\n################################################################");
    printf("\n\t SORRY ! Entered %s ISN'T ACCEPTED ",take_str);
    printf("\n################################################################");
  }
  }
  printf("\n\n<@@@@>  DO U WANT to CHECK more %ss (0/1)  :  ",take_str);
  scanf("%s",choice);
  choice_validat();
}
printf("\n\n");
}						//terminated search_string();

int graphical_representation(struct min_dfa * bs_add,int columns){
 // printf("\n\t\tcolumns=%d\n\n",columns);
  int front=0,rear=0,rear2=0,i=0,color=4;
  float x,y,r=35,count_cir=0;
  int gdriver = DETECT, gmode;
  char ch1[]="INPUT ALPHABET   = ",ch2[]="REGULAR EXPRESS = ";
  initgraph(&gdriver, &gmode,NULL);
  outtextxy(0,10,ch1);
  outtextxy(150,10,alphabet);
  outtextxy(0,25,ch2);
  outtextxy(150,25,RE);
  //outtext(&ch);
  float padding_x,padding_y,lenght=getmaxx()-30,width=getmaxy()-40;
  char arr='A';
  r=r/log(no_of_eq_clss+1);
  padding_x=(lenght-(3*columns-2)*2*r)/2;
  if(padding_x<0){
    printf("\n\nSORRY, WINDOWS length is not sufficient\n");
    r=(lenght-40)/((3*columns-2)*2);
    padding_x=20;
  }
  struct min_dfa *que[no_of_eq_clss+1];
  struct trans_nod *temp;
  que[rear]=bs_add;
  que[rear]->visited_bfs=0;
  que[rear]->color=2;
  x=padding_x+2*r;
  y=width/2;
  setcolor(2);
  circle(x,y,r);
  que[front]->cen_x=x;
  que[front]->cen_y=y;
  if(que[front]->is_final==1){
    que[rear]->color=4;
    setcolor(4);
    circle(x,y,r+2);
  }
  setfontcolor(2);
  outtextxy(x-2,y-2,&(arr));
  setcolor(2);
  line(x-r-20,y,x-r,y);
  line(x-r-10,y+5,x-r,y);
  line(x-r-10,y-5,x-r,y);
  //triangle(x-r-5,y-5,x-r-5,y+5,x-r,y);
  while(front<=rear){
    temp=que[front]->next_trans_ptr;
    for(i=0;i<no_of_ip_alph;i++){
      if(temp->next_state->visited_bfs!=0){
	rear++;
	que[rear]=temp->next_state;
	que[rear]->visited_bfs=0;
      }
      temp=temp->link;
    }
    if(rear2==front){
      count_cir=rear-front;
      rear2=rear;
      padding_y=(width-(3*count_cir-2)*2*r)/2;
      if(padding_y<0){
	return 10;
	//r=(width-40)/((3*count_cir-2)*2);
        //padding_y=40;
      }
      x=x+6*r;
      for(i=0;i<count_cir;i++){
	y=(padding_y+r)+i*6*r;
	if(color<15)
	  ++color;
	else
          color=5;
	que[front+i+1]->color=color;
	setcolor(color);
	circle(x,y,r);
        setfontcolor(color);
	outtextxy(x-2,y-2,&(++arr));
	if(que[front+i+1]->is_final==1){
	  que[front+i+1]->color=4;
          setfontcolor(4);
	  outtextxy(x-2,y-2,&(arr));
	  setcolor(4);
	  circle(x,y,r);
          circle(x,y,r+2);
	}
	que[front+i+1]->cen_x=x;
	que[front+i+1]->cen_y=y;
      }
    }
  front++;

  }
  front=0,rear=0;
  que[rear]=bs_add;
  que[rear]->visited_bfs=1;
  while(front<=rear){
    temp=que[front]->next_trans_ptr;;
    for(i=0;i<no_of_ip_alph;i++){
      if(temp->next_state->visited_bfs!=1){
	rear++;
	que[rear]=temp->next_state;
	que[rear]->visited_bfs=1;
      }
      temp=temp->link;
    }
    draw_arrows(que[front],r);
    front++;
  }						// while loop terminated.
  delay(2000);
  getch();
  closegraph();
}						//terminated graphical_representation();

int draw_arrows(struct min_dfa* ptr,int r){
  float from_x,from_y,to_x,to_y,mid_x,mid_y,flag;
  char ch=',',ip_symbol;
  int i;
  struct trans_nod *temp=ptr->next_trans_ptr;
  from_x=ptr->cen_x;
  from_y=ptr->cen_y;
  setfontcolor(ptr->color);
  setcolor(ptr->color);
  for(i=0;i<no_of_ip_alph;i++){
    ip_symbol=temp->ip_symbol;
    to_x=temp->next_state->cen_x;
    to_y=temp->next_state->cen_y;
    if(from_x==to_x &&from_y==to_y){		//self loop;
      if(temp->next_state->keep==0){
	ellipse(from_x,from_y-r/2,180,360,r,2*r);
        ++(temp->next_state->keep);
	outtextxy(from_x-r/2,from_y-2.9*r,&ip_symbol);
	line(from_x-r,from_y-r/2,from_x-r-7,from_y-r/2-7);
	line(from_x-r,from_y-r/2,from_x-r+4,from_y-r/2-9);
      }
      else{
	outtextxy(from_x-r/2+(temp->next_state->keep)*6,from_y-2.9*r,&ch);
	++(temp->next_state->keep);
	outtextxy(from_x-r/2+(temp->next_state->keep)*6,from_y-2.9*r,&(ip_symbol));
	++(temp->next_state->keep);
      }
    }
    else if(from_x==to_x &&from_y > to_y){	//virtical upward LHS;
      mid_x=from_x;
      mid_y=(from_y-to_y)/2;
      flag=mid_y/2;
      if(temp->next_state->keep==0){
	ellipse(from_x-r,from_y-mid_y,90,270,flag,mid_y);
         ++(temp->next_state->keep);
	outtextxy(from_x-r-flag+2,from_y-mid_y,&ip_symbol);
	line(from_x-r-flag/2,to_y+mid_y*0.134,from_x-r-flag/2-9,to_y+mid_y*0.134);
	line(from_x-r-flag/2,to_y+mid_y*0.134,from_x-r-flag/2,to_y+mid_y*0.134+9);
      }
      else{
	outtextxy(from_x-r-flag+2+(temp->next_state->keep)*6,from_y-mid_y,&ch);
	++(temp->next_state->keep);
	outtextxy(from_x-r-flag+2+(temp->next_state->keep)*6,from_y-mid_y,&(ip_symbol));
	++(temp->next_state->keep);
      }
    }
    else if(from_x==to_x &&from_y < to_y){	//virtical downward  RHS;
      mid_x=from_x;
      mid_y=(to_y-from_y)/2;
      flag=mid_y/2;
      if(temp->next_state->keep==0){
	ellipse(from_x+r,from_y+mid_y,270,90,flag,mid_y);
         ++(temp->next_state->keep);
	outtextxy(from_x+r+flag+2,from_y+mid_y,&ip_symbol);
 	line(from_x+r+flag/2,to_y-mid_y*0.134,from_x+r+flag/2+9,to_y-mid_y*0.134);
	line(from_x+r+flag/2,to_y-mid_y*0.134,from_x+r+flag/2,to_y-mid_y*0.134-9);
      }
      else{
	outtextxy(from_x+r+flag+2+(temp->next_state->keep)*6,from_y+mid_y,&ch);
	++(temp->next_state->keep);
	outtextxy(from_x+r+flag+2+(temp->next_state->keep)*6,from_y+mid_y,&(ip_symbol));
	++(temp->next_state->keep);
      }
    }
    else if(from_x<to_x&&from_y==to_y){		// horizen upper left to right
      mid_y=from_y;
      mid_x=(to_x-from_x)/2;
      flag=mid_x/2;
      if(temp->next_state->keep==0){
	ellipse(from_x+mid_x,from_y-r,180,360,mid_x,flag);
         ++(temp->next_state->keep);
	outtextxy(from_x+mid_x-0.5*r,from_y-r-flag-10,&ip_symbol);
 	line(to_x-mid_x*0.134,to_y-r-flag/2,to_x-mid_x*0.134,to_y-r-flag/2-7);
	line(to_x-mid_x*0.134,to_y-r-flag/2,to_x-mid_x*0.134-7,to_y-r-flag/2);
      }
      else{
	outtextxy(from_x+mid_x-0.5*r+(temp->next_state->keep)*6,from_y-r-flag-10,&ch);
	++(temp->next_state->keep);
	outtextxy(from_x+mid_x-0.5*r+(temp->next_state->keep)*6,from_y-r-flag-10,&(ip_symbol));
	++(temp->next_state->keep);
      }
    }
    else if(from_x<to_x &&from_y>to_y){  //inclind upper RHS;
      mid_y=from_y-r;
      mid_x=to_x-r;
      flag=mid_y-to_y;
      if(temp->next_state->keep==0){
	ellipse(mid_x,mid_y,180,270,mid_x-from_x,flag);
         ++(temp->next_state->keep);
	outtextxy(from_x+0.5*(to_x-from_x)-0.5*r,mid_y+2-0.866*flag,&ip_symbol);
 	line(mid_x,to_y,mid_x-7,to_y-7);
	line(mid_x,to_y,mid_x-7,to_y+7);
      }
      else{
	outtextxy(from_x+0.5*(to_x-from_x)-0.5*r+(temp->next_state->keep)*6,mid_y+2-0.866*flag,&ch);
	++(temp->next_state->keep);
	outtextxy(from_x+0.5*(to_x-from_x)-0.5*r+(temp->next_state->keep)*6,mid_y+2-0.866*flag,&(ip_symbol));
	++(temp->next_state->keep);
      }
    }
    else if(from_x<to_x &&from_y < to_y){	//inclind lower RHS;
      mid_y=from_y+r;
      mid_x=to_x-r;
      flag=to_y-mid_y;
      if(temp->next_state->keep==0){
	ellipse(mid_x,mid_y,90,180,mid_x-from_x,flag);
         ++(temp->next_state->keep);
	outtextxy(from_x+0.5*(to_x-from_x)-0.5*r,to_y-0.134*flag,&ip_symbol);
 	line(mid_x,to_y,mid_x-7,to_y-7);
	line(mid_x,to_y,mid_x-7,to_y+7);
      }
      else{
	outtextxy(from_x+0.5*(to_x-from_x)-0.5*r+(temp->next_state->keep)*6,to_y-0.134*flag,&ch);
	++(temp->next_state->keep);
	outtextxy(from_x+0.5*(to_x-from_x)-0.5*r+(temp->next_state->keep)*6,to_y-0.134*flag,&(ip_symbol));
	++(temp->next_state->keep);
      }
    }
   if(from_x>to_x&&from_y==to_y){		// horizen lower right to left
      mid_y=from_y;
      mid_x=(from_x-to_x)/2;
      flag=mid_x/2;
      if(temp->next_state->keep==0){
	ellipse(to_x+mid_x,from_y+r,0,180,mid_x,flag);
         ++(temp->next_state->keep);
	outtextxy(to_x+mid_x-0.5*r,from_y+r+flag+2,&ip_symbol);
 	line(to_x+mid_x*0.134,to_y+r+flag/2,to_x+mid_x*0.134,to_y+r+flag/2+7);
	line(to_x+mid_x*0.134,to_y+r+flag/2,to_x+mid_x*0.134+7,to_y+r+flag/2);
      }
      else{
	outtextxy(to_x+mid_x-0.5*r+(temp->next_state->keep)*6,from_y+r+flag+2,&ch);
	++(temp->next_state->keep);
	outtextxy(to_x+mid_x-0.5*r+(temp->next_state->keep)*6,from_y+r+flag+2,&(ip_symbol));
	++(temp->next_state->keep);
      }
    }
    else if(from_x>to_x &&from_y>to_y){		// inclind upper right to left
      mid_y=from_y;
      mid_x=to_x+r;
      flag=mid_y-to_y;
      if(temp->next_state->keep==0){
	ellipse(mid_x,mid_y,270,360,from_x-r-mid_x,flag);
         ++(temp->next_state->keep);
	outtextxy(to_x+0.5*(from_x-r-mid_x),mid_y-2-0.866*flag,&ip_symbol);
 	line(mid_x,to_y,mid_x+7,to_y-7);
	line(mid_x,to_y,mid_x+7,to_y+7);
      }
      else{
	outtextxy(to_x+0.5*(from_x-r-mid_x)+(temp->next_state->keep)*6,mid_y-2-0.866*flag,&ch);
	++(temp->next_state->keep);
	outtextxy(to_x+0.5*(from_x-r-mid_x)+(temp->next_state->keep)*6,mid_y-2-0.866*flag,&(ip_symbol));
	++(temp->next_state->keep);
      }
    }
    else if(from_x>to_x &&from_y < to_y){	//inclind lower right to left
      mid_y=from_y;
      mid_x=to_x+r;
      flag=to_y-mid_y;
      if(temp->next_state->keep==0){
	ellipse(mid_x,mid_y,0,90,from_x-r-mid_x,flag);
         ++(temp->next_state->keep);
	outtextxy(to_x+0.5*(from_x-r-mid_x),mid_y-2+0.866*flag,&ip_symbol);
 	line(mid_x+3,to_y,mid_x+10,to_y-7);
	line(mid_x+3,to_y,mid_x+10,to_y+7);
      }
      else{
	outtextxy(to_x+0.5*(from_x-r-mid_x)+(temp->next_state->keep)*6,mid_y-2+0.866*flag,&ch);
	++(temp->next_state->keep);
	outtextxy(to_x+0.5*(from_x-r-mid_x)+(temp->next_state->keep)*6,mid_y-2+0.866*flag,&(ip_symbol));
	++(temp->next_state->keep);
      }
    }
    temp=temp->link;
  }
  temp=ptr->next_trans_ptr;						//terminated for loop;
  for(i=0;i<no_of_ip_alph;i++){
    temp->next_state->keep=0;
    temp=temp->link;
  }
}						//terminated draw_arrows();

int editing_text_file(struct min_dfa* base_add){
  char user_ip[70];
  int c,usr_ip_len,j=0;
  FILE *fptr1,*fptr2;
  struct trans_nod *temp;
  struct min_dfa* bs_add=base_add;
  //printf("\nbase_add=  %d",base_add->state_name);
  int i=0;
  fptr1=fopen(path1,"r");
  fptr2=fopen(path2,"w+");
  if(fptr1==NULL){
    printf("\n#########################################################");
    printf("\n\t\t\tError!");
    printf("\nThere could be many reasons behind this ,for example - ");
    printf("\nfile does not exists or path is not mentioned correctly");
    printf("\n#########################################################\n");
    exit(1);
   }
  else{
    while(1){
      c=fgetc(fptr1);
      if(c==EOF){
         break;
      }
      else{
	fputc(char(c),fptr2);
      }
      if((c>=48&&c<=57)||(c>=65&&c<=90)||(c>=97&&c<=122)){
	for(temp=bs_add->next_trans_ptr;temp->ip_symbol!=char(c);temp=temp->link){
	 // printf("\n%c\t %c",temp->ip_symbol,char(c));
	};
        bs_add=temp->next_state;
	if(bs_add!=base_add){
	  user_ip[j]=char(c);
	  user_ip[++j]='\0';
	}
	if(bs_add->is_final==1){
	  ++i;
	  j=0;
	  usr_ip_len=strlen(user_ip);
	 // printf("\n\t==> matched %d",i);
	  bs_add=base_add;
	  fseek(fptr2,-usr_ip_len,1);
	  fputc('[',fptr2);
	  fputc('=',fptr2);
	  fputc('=',fptr2);
	  fputc('>',fptr2);
	  fputc(' ',fptr2);
	  fprintf(fptr2,"%s",user_ip);
	  fputc(' ',fptr2);
	  fputc('<',fptr2);
	  fputc('=',fptr2);
	  fputc('=',fptr2);
	  fputc(']',fptr2);
	}
      }
      else{
	j=0;
        bs_add=base_add;
      }
    }						//terminated while loop;
  }
  fclose(fptr1);
  fclose(fptr2);
  if(i>0){
    printf("\n\n\t\t---------------------------------------------");
    printf("\n\t\t\tno of times matched = %d",i);
    printf("\n\t\t  GO and find duplicate file in the directory");
    printf("\n\t\t---------------------------------------------\n\n");
  }
  else{
    printf("\n\n\t\t#####################################");
    printf("\n\t\t\tNOT FOUND!!!!!");
    printf("\n\t\t######################################\n\n");
  }
}						//terminated editing_text_file();
