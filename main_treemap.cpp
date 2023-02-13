#include <iostream>

#include "TreeMap.h"

int main() {

    TreeMap<std::string, int> treeMap;

    //treeMap.print();

    treeMap.update("james", 37468000);
    treeMap.update("david", 28514000);
    treeMap.update("elizabeth", 25582000);
    treeMap.update("mary", 21650000);
    treeMap.update("john", 21581000);
    treeMap.update("jennifer", 20076000);
    treeMap.update("robert", 19980000);
    treeMap.update("linda", 19618000);
    treeMap.update("particia", 19578000);
    treeMap.update("michael", 19281000);
    std::vector<KeyValuePair<std::string, int> > k = treeMap.subMap("david", "david");
    for (int i=0; i<k.size(); i++)
    {
    	std::cout<< k[i] <<std::endl;
    }

    //treeMap.print();
    //std::cout<<treeMap.<<std::endl;
    //std::cout<<"tesekkur ederim"<<std::endl;
    return 0;
}
