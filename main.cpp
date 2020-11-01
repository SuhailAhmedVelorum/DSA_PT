#include<iostream>
#include<string.h>
#include<fstream>
#include<stdio.h>
#include<cstdio>
#include<random>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>
#include "koolplot.h"

#define MIN(x,y) ((x) < (y) ? (x) : (y));
using namespace std;

class elements{
    char name[40];      //1
    char symbol[4];
    int atomicNo;       //2
    int period;         //3
    int group;          //4
    char block;         //5
    float mp;           //6
    float bp;           //7
    int yod;            //8   //Year of discovery
    char state[20];          //State at room temp
    float atomicWeight; //9

    public:

    void enter(){
        cout<<"Enter Element Details: \n";
        cout<<"Name: ";cin>>name;
        cout<<"Symbol: ";cin>>symbol;
        cout<<"Atomic Number: ";cin>>atomicNo;
        cout<<"Atomic Weight: ";cin>>atomicWeight;
        cout<<"Period: ";cin>>period;
        cout<<"Group: ";cin>>group;
        cout<<"Block: ";cin>>block;
        cout<<"Melting Point: ";cin>>mp;
        cout<<"Boiling Point: ";cin>>bp;
        cout<<"Year of Discovery: ";cin>>yod;
        cout<<"State at Room Temperature: ";cin>>state;


    }

    char* retSymbol(){
    return symbol;}

    char* retName(){
    return name;}

    int retYear(){
    return yod;}

    char retBlock(){
    return block;}

    int retNo(){
    return atomicNo;}

    float retmp(){
    return mp;}

    float retbp(){
    return bp;}

    int retPeriod(){
    return period;}

    void display(){

        cout<<"\nName: "<<name<<endl;
        cout<<"Symbol: "<<symbol<<endl;
        cout<<"Atomic Number: "<<atomicNo<<endl;
        cout<<"Atomic Weight: "<<atomicWeight<<endl;
        cout<<"Period: "<<period<<endl;
        cout<<"Group: "<<group<<endl;
        cout<<"Block: "<<block<<endl;
        cout<<"Melting Point: "<<mp<<endl;
        cout<<"Boiling Point: "<<bp<<endl;
        cout<<"Year of Discovery: "<<yod<<endl;
        cout<<"State at Room Temperature: "<<state<<endl;

    }

    void store(elements obj){
        ofstream fout("elements.txt", ios::out|ios::app|ios::binary);
        fout.write((char*)&obj,sizeof(obj));
        fout.close();
    }

    void fetchElements(){
        elements obj;
        ifstream fin("elements.txt", ios::in|ios::binary);
        while(fin.read((char*)&obj,sizeof(obj)))
            obj.display();
        fin.close();
    }
};

//Questions class
class questions
{
    char question[100];
    int ansType;

    public:
        char* retq(){
        return question;}

        int retAns(){
        return ansType;}

        void enter(){
        cout<<"\nEnter the question: ";
        gets(question);
        cout<<"Enter the answer type(1-9): ";
        cin>>ansType;
        }

        void store(){
        questions obj;
        obj.enter();
        ofstream fout("questions.txt",ios::out|ios::app|ios::binary);
        fout.write((char*)&obj,sizeof(obj));
        fout.close();
        }

        void getQuestion(){
            questions obj;
            elements pbj;
        srand(time(0));
        int q = rand()%100;q=q%3;
        int count = 0;
        ifstream fin("questions.txt", ios::in|ios::binary);
            while(fin.read((char*)&obj,sizeof(obj))){
                if(q == count)
                    break;
                count++;
            }
        fin.close();
        int element = rand()%10 + 1;
        ifstream fin2("elements.txt", ios::in|ios::binary);
            while(fin2.read((char*)&pbj,sizeof(pbj))){
                if(pbj.retNo() == element)
                    break;
            }
        cout<<obj.retq()<<" "<<pbj.retName()<<endl;
        fin2.close();
        cout<<"Your answer: ";
        int ans1,check = 0;
        char ans2[20];
        float ans3;
        switch(obj.retAns()){
            case 1:
                cin>>ans1;
                if(ans1 == pbj.retNo())
                    check = 1;
                break;

            case 6:
                cin>>ans3;
                if(ans3 == pbj.retmp())
                    check = 1;
                break;

            case 8:
                cin>>ans1;
                if(ans1 == pbj.retYear())
                    check = 1;
                break;

            }
        if(check == 1)
            cout<<"\nYour answer is correct!";
        else
            cout<<"\nThat was the wrong answer!";

        }


};
//End of Questions Class

//Computes the Lavenshtiens distance between the two input words
int edit_dist(char* s1, char* s2){

    int i,j,l1,l2,t,track;
    int dist[50][50];

    l1 = strlen(s1);
    l2 = strlen(s2);

    for(i = 0; i <= l1; i++){
       dist[0][i] = i;
    }

    for(j = 0; j <= l2; j++){
       dist[j][0] = j;
    }

    for(j = 1; j <= l1; j++){
       for(i = 1; i <= l2; i++){
          if(s1[i-1] == s2[j-1]){
             track = 0;
          }
          else{
             track = 1;
          }
          t = MIN((dist[i-1][j] + 1),(dist[i][j-1] + 1));
          dist[i][j] = MIN(t,(dist[i-1][j-1] + track));
       }
    }
   return dist[l2][l1];
}


//Delete Function
void deleteElement(){
    cout<<"\nEnter the symbol of the Element you wan to delete: ";
    char sym[4];
    cin>>sym;
    elements obj;
    ofstream fin("temp.txt", ios::out|ios::binary);
    fstream fout("elements.txt", ios::in|ios::app|ios::binary);
    while(fout.read((char*)&obj,sizeof(obj))){
        if(strcmp(sym, obj.retSymbol())!=0){
            fin.write((char*)&obj,sizeof(obj));
        }
    }
    remove("elements.txt");
    cout<<rename("temp.txt", "elements.txt");
    fout.close();
    fin.close();
}



//Search Functions
void searchChoice(int ans){
    ifstream fout("elements.txt", ios::in|ios::binary);
    ifstream fin("elements.txt", ios::in|ios::binary);
    elements obj;
    elements viable;
    int mind = 100000;
    switch(ans){
        case 1:
                cout<<"Enter the Symbol: ";
                char sym[4]; cin>>sym;
                while(fout.read((char*)&obj,sizeof(obj))){
                    if(strcmp(sym, obj.retSymbol())==0){
                        obj.display();
                        break;
                    }
                }
                fout.close();break;


        case 2:
                cout<<"Enter the Name of the Element: ";
                char ele[40]; cin>>ele;
                while(fout.read((char*)&obj, sizeof(obj))){
                    if(edit_dist(ele, obj.retName()) < mind){
                        viable = obj;
                        mind = edit_dist(ele, obj.retName());
                    }
                }
                viable.display();
                fout.close();
               /* cout<<"Enter the Name of the Element: ";
                char ele[40];
                cin>>ele;
                while(fout.read((char*)&obj,sizeof(obj))){
                    if(strcmp(ele, obj.retName())==0){
                        obj.display();
                        break;
                    }
                }
                fout.close();break;
                */

        case 3:
                cout<<"Enter the Starting Year: ";
                int d1, d2; cin>>d1;
                cout<<"Enter the Ending Year: ";
                cin>>d2;
                while(fin.read((char*)&obj,sizeof(obj))){
                    if(obj.retYear()>=d1 && obj.retYear()<=d2)
                            cout<<obj.retSymbol()<<endl<<obj.retYear()<<endl;
                }
                fin.close();break;

        case 4:
                int d3; cout<<"Enter the Year: ";cin>>d3;
                while(fin.read((char*)&obj,sizeof(obj))){
                    if(obj.retYear()==d3){
                            cout<<obj.retSymbol()<<endl<<obj.retYear()<<endl;
                            break;
                    }
                }
                fin.close();break;


        case 5:
                char block;
                cout<<"Enter the Block: ";cin>>block;
                while(fin.read((char*)&obj, sizeof(obj))){
                    if(obj.retBlock() == block)
                        cout<<obj.retName()<<endl;
                }
                fin.close();break;

    }
}

//graph function

void points(int p){
    elements obj;
    double mp[20], bp[20],a[20];
    int k = 0,n;

    ifstream fin("elements.txt", ios::in | ios::binary);
    while(fin.read((char*)&obj, sizeof(obj))){
      if(p==obj.retPeriod()){
          cout<<obj.retName()<<"\n";
          a[k] = obj.retNo();
          cout<<"Atomic Number:"<< a[k]<<"\n";
          mp[k] = obj.retmp()/10;
          cout<<"Melting Point"<<mp[k]*10<<"\n";
          bp[k] = obj.retbp()/10;
          cout<<"Boiling Point"<<bp[k]*10<<"\n\n";

          k++;
      }
      else{
      }
    }
    n=k;
fin.close();

            plotdata x,y,w,z;
            insert(x,a,n);
            insert(y, mp, n);//kill me
            for(int i=0;i<n;i++){
                addMark(x, y,a[i],mp[i]);
            }


            insert(w,a,n);
            insert(z, bp, n);//kill me
            for(int i=0;i<n;i++){
                addMark(x, y,a[i],bp[i]);
            }
            setColor(x,y,RED);
            x<<w;
            y<<z;
            plot(x,y,BLUE,"Plot of Melting point and Boiling Point(reduced by a factor of 10");


}
int main(){

    elements obj;
    questions pbj;
    loop:
    system("cls");
    cout<<"1. Enter an Element\n2. Delete an Element\n3. Search for an element\n4. Take a Quiz\n5. Plot Temperatures\nYour Choice: ";
    int choice;
    cin>>choice;
    switch(choice){
        case 0: exit(0);
        case 1: obj.enter(); obj.store(obj);break;
        case 2: deleteElement();break;
        case 3: {
            cout<<"1. Search by Element Symbol\n2. Search by Element Name\n3. Search by Date Range\n4. Search by Year Discovered\n5. Search by Block\nYour Choice: ";
            int ans;
            cin>>ans;
            searchChoice(ans);
            break;
        }
        case 4: pbj.getQuestion();break;
        case 5: {
                int p;
                cout<<"Enter Period to view: ";
                cin>>p;
                points(p);
                goto loop;
                    }

    }
    cout<<endl;
    system("pause");
    goto loop;


    return 0;

}
