//
//  Project3.cpp
//  Project
//
//  Created by Conghui Deng on 2/16/20.
//  Copyright © 2020 Conghui Deng. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string>
using namespace std;

class listNode{
    public: string data;
          int count;
          listNode* next;
    
    listNode(string str,int num, listNode* node){
        data=str;
        count=num;
        next=node;
    }
    void printNode(listNode *Node,ofstream &outFile){

        if(Node->next==NULL){
            outFile<<"("<<Node->data<<", "<<Node->count<<",NULL)->NULL"<<endl;
        }
        else
        outFile<<"("<<Node->data<<", "<<Node->count<<","<<Node->next->data<<")->";
    }
};

class hashTable{
public:
    int static const bucketSize=29;
    listNode* hashTableAry[bucketSize];
    hashTable(){
        
    }
    void createHashAry(){
        for(int i=0;i<bucketSize;i++){
            hashTableAry[i]=new listNode("dummy",0,NULL);
        }
    }
        void storeDataIntoHashTable(ifstream &in, ofstream &out){
        string data;
        int index=0;
            while(in>>data){
        listNode* newNode=new listNode(data,1,NULL);
        index=Doit(data);
        listNode* listHead=hashTableAry[index];
        listInsert(listHead,newNode);
        printList(index,out);
            }
   }
    
    int Doit(string data){
        unsigned int val=1;
        for(int i=0;i<data.length();i++){
            val=val*32+(int)data[i];
        }
        //cout<<val%29;
        int c=val%bucketSize;
        return c;
    }
    void listInsert(listNode* listHead,listNode* newNode){
        listNode *Spot=findSpot(listHead,newNode);
        if(Spot!=NULL){
        newNode->next=Spot->next;
        Spot->next=newNode;
        }
    }
    listNode* findSpot(listNode *listHead, listNode *newNode){
          listNode *temp=listHead;
           while(temp->next!=NULL && temp->next->data.compare(newNode->data)<0){
               temp=temp->next;
           }
        if(temp->next!=NULL && temp->next->data==newNode->data){
            temp->next->count++;
            temp=NULL;
        }
            
           return temp;
    }
    void printList(int index,ofstream &out){
        out<<"hashTable["<<index<<"]->";
        listNode* printSpot=hashTableAry[index];
        while(printSpot!=NULL){
            printSpot->printNode(printSpot,out);
            printSpot=printSpot->next;
        }
//        out<<"NULL"<<endl;
    }
    void printHashTable(ofstream &out){
        int index=0;
        
        while(index<bucketSize){
            printList(index,out);
            index++;
        }
    }
};

int main(int argc, const char *argv[]){
    
    ifstream inFile(argv[1]);
    ofstream outFile1(argv[2]);
    ofstream outFile2(argv[3]);
    
    hashTable* ht=new hashTable();
    ht->createHashAry();
    ht->storeDataIntoHashTable(inFile,outFile2);
    ht->printHashTable(outFile1);
    inFile.close();
    outFile1.close();
    outFile2.close();
}
